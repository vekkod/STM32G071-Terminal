#ifndef TIMER_H
#define TIMER_H

#include "stm32g0xx_hal.h"


void SysTick_Handler(void);

 
void MX_TIM16_Init(void);

 
HAL_StatusTypeDef TIMER_Start(void);

 
float TIMER_time(void);

#endif
