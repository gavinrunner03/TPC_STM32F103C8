#ifndef ADC_H
#define ADC_H
#include "stm32f1xx.h"

extern volatile uint16_t adc_value;
void ADC1_2_IRQHandler(void);

#endif // ADC_H