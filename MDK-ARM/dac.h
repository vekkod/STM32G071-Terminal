#ifndef DAC_H
#define DAC_H

#include "stm32g0xx_hal.h"

void MX_DAC1_Init(void);

HAL_StatusTypeDef DAC_Start(void);
 
HAL_StatusTypeDef DAC_Stop(void);
 
HAL_StatusTypeDef DAC_SetValue(float p_fl_ValVolt);
 
uint32_t DAC_GetValue(void);

#endif
