#ifndef ADC_H
#define ADC_H

#include "stm32g0xx_hal.h"
#include "stm32g0xx_hal_adc.h"
#include <stdio.h>
#include <stdlib.h>


void MX_ADC1_Init(void);

void ADC_Start(void);

void ADC_Stop(void);

uint32_t ADC_GetValue(uint32_t p_ui_Time);

void ADC_DMA_Start_Acquisition(uint32_t* p_ui_Data, uint32_t Lenth);

void ADC_DMA_Stop_Acquisition(void);

#endif
