#ifndef PWM_H
#define PWM_H

#include "stm32g0xx_hal.h"

void MX_TIM2_Init(void);

void PWM_Start(uint32_t dutyCyclePWM);

#endif
