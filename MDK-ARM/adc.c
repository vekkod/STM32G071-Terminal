#include "main.h"
#include "stm32g0xx_hal.h"
#include "stm32g0xx_hal_adc.h"
#include <stdio.h>
#include <stdlib.h>
#include "adc.h"

ADC_HandleTypeDef hadc1;



void MX_ADC1_Init(void)
{
  ADC_ChannelConfTypeDef sConfig = {0};
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc1.Init.LowPowerAutoWait = DISABLE;
  hadc1.Init.LowPowerAutoPowerOff = DISABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.DMAContinuousRequests = ENABLE;
  hadc1.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  hadc1.Init.SamplingTimeCommon1 = ADC_SAMPLETIME_1CYCLE_5;
  hadc1.Init.SamplingTimeCommon2 = ADC_SAMPLETIME_1CYCLE_5;
  hadc1.Init.OversamplingMode = DISABLE;
  hadc1.Init.TriggerFrequencyMode = ADC_TRIGGER_FREQ_HIGH;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    while(1);
  }
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLINGTIME_COMMON_1;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    while(1);
  }
}

void ADC_Start(void)
{
	HAL_ADC_Start(&hadc1);
};


void ADC_Stop(void)
{
	HAL_ADC_Stop(&hadc1);
}

uint32_t ADC_GetValue(uint32_t time)
{
	while(1)
	{
		ADC_Start();
		if(HAL_ADC_PollForConversion(&hadc1, time)==HAL_OK)
		{
			return HAL_ADC_GetValue(&hadc1);
		}
		ADC_Stop();
	}
}

void ADC_DMA_Start_Acquisition(uint32_t* p_ui_Data, uint32_t Lenth)
{
    HAL_ADC_Start_DMA(&hadc1, p_ui_Data, Lenth);
      
}


void ADC_DMA_Stop_Acquisition(void)
{
		HAL_ADC_Stop_DMA(&hadc1);
}
