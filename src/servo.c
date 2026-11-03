#include "servo.h"

#define MIN_SERVO_ANGLE 1000U
#define MID_SERVO_ANGLE 1500U
#define MAX_SERVO_ANGLE 2000U

void SERVO_INIT(void)
{
    // Initialize the servo control pin and any necessary timers
    /*Using PA 6 and timer 3 CH1*/
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; // Enable GPIOA clock
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN; // Enable TIM3 clock

    GPIOA->CRL &=~ (0xF << (4 * 6)); // Clear the existing configuration for PA6

    GPIOA->CRL |= (0xA << (4 * 6)); // Set PA6 as alternate function push-pull output 2MHz output freq.

    TIM3->PSC  = 1U;       // 2 MHz / (1 + 1) = 1 MHz
    TIM3->ARR  = 19999U;   // 20 ms frame
    TIM3->CCR1 = 1500U;    // Center pulse

    TIM3->CCMR1 = (6U << 4) | TIM_CCMR1_OC1PE;  // PWM mode 1, CCR1 preload
    TIM3->CR1 = TIM_CR1_ARPE;
    TIM3->EGR = TIM_EGR_UG;    // Load the prescaler and preload values
    TIM3->CCER = TIM_CCER_CC1E;
    TIM3->CR1 |= TIM_CR1_CEN;
}

void SERVO_SET_ANGLE(uint16_t adc_sample)
{
    uint32_t pulse_us;

    if (adc_sample <= 409U) {
        uint32_t x = adc_sample;
        pulse_us = 1000U + (100U * x) / 409U;
    } else if (adc_sample <= 1228U) {
        uint32_t x = adc_sample - 409U;
        pulse_us = 1100U + (400U * x) / 819U;
    } else if (adc_sample <= 2047U) {
        uint32_t x = adc_sample - 1228U;
        pulse_us = 1500U + (250U * x) / 819U;
    } else if (adc_sample <= 4093U) {
        uint32_t x = adc_sample - 2047U;
        pulse_us = 1750U + (250U * x) / 2046U;
    } else {
        pulse_us = 2000U;
    }

    TIM3->CCR1 = pulse_us;
}