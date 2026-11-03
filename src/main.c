#include "stm32f1xx.h"
#include "main.h"
#include "adc.h"
#include "watchdog.h"
#include "servo.h"

volatile int hello = 0;
void SystemInit(void)
{
    /*
        Initalize the system clock to 8Mhz.
        Initialize the watchdog timer to a timeout of 1 second.
        Initialize GPIO pins to be ADC controlled
        Initialize the ADC for analog input reading.


        1. Initialize the system clock to 1Mhz.
    */
    RCC->CFGR = (RCC->CFGR & ~RCC_CFGR_HPRE) | RCC_CFGR_HPRE_DIV4;

    /*  2. Initialize the watchdog timer to a timeout of 1 second. */
    WATCHDOG_INIT();

    /*  3. Initialize GPIO pins to be ADC controlled */
    RCC->CFGR &= ~RCC_CFGR_ADCPRE; // PCLK2 / 2 = 1 MHz if APB2 is /1
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_ADC1EN;

    GPIOA->CRL &= ~(GPIO_CRL_MODE7 | GPIO_CRL_CNF7);

    ADC1->SQR1 &= ~ADC_SQR1_L; // One conversion per sequence
    ADC1->SQR3 = 7U;           // SQ1 = channel 7
    ADC1->SMPR2 |= 7U << 21;   // Channel 7: 239.5 ADC cycles

    ADC1->CR2 = ADC_CR2_CONT;  // Continuous mode, right-aligned results
    ADC1->CR2 |= ADC_CR2_ADON; // First ADON write powers on the ADC

    for (unsigned i = 0; i < 8; ++i)
    {
        __NOP(); // At least 4 µs at 2 MHz HCLK
    }

    ADC1->CR2 |= ADC_CR2_RSTCAL;
    while (ADC1->CR2 & ADC_CR2_RSTCAL)
    {
    }

    ADC1->CR2 |= ADC_CR2_CAL;
    while (ADC1->CR2 & ADC_CR2_CAL)
    {
    }

    ADC1->CR1 |= ADC_CR1_EOCIE;
    NVIC_EnableIRQ(ADC1_2_IRQn);

    ADC1->CR2 |= ADC_CR2_ADON; // Second ADON write starts conversion

    /*  4. Initialize the Servo */
    SERVO_INIT();
}

int main(void)
{
    // Basic infinite loop for an embedded target
    while (1)
    {
        SERVO_SET_ANGLE(adc_value);
    }
}
