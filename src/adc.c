#include "adc.h"
#include "watchdog.h"

volatile uint16_t adc_value = 0;

void ADC1_2_IRQHandler(void)
{
    IWDG->KR = 0xAAAA; // Reload the counter
    if (ADC1->SR & ADC_SR_EOC) {
        adc_value = ADC1->DR;  // Reading DR also clears EOC
    }
}
