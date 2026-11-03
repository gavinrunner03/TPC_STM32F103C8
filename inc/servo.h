#ifndef SERVO_H
#define SERVO_H
#include "stm32f1xx.h"

void SERVO_INIT(void);
void SERVO_SET_ANGLE(uint16_t adc_sample);

#endif // SERVO_H   