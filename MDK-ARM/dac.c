#include "dac.h"

DAC_HandleTypeDef hdac1;

void MX_DAC1_Init(void)
{
  DAC_ChannelConfTypeDef sConfig = {0};
  hdac1.Instance = DAC1;
  if (HAL_DAC_Init(&hdac1) != HAL_OK)
  {
    while(1);
  }
  sConfig.DAC_SampleAndHold = DAC_SAMPLEANDHOLD_DISABLE;
  sConfig.DAC_Trigger = DAC_TRIGGER_NONE;
  sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
  sConfig.DAC_ConnectOnChipPeripheral = DAC_CHIPCONNECT_DISABLE;
  sConfig.DAC_UserTrimming = DAC_TRIMMING_FACTORY;
  if (HAL_DAC_ConfigChannel(&hdac1, &sConfig, DAC_CHANNEL_1) != HAL_OK)
  {
    while(1);
  }
}

HAL_StatusTypeDef DAC_Start(void)
{
	return HAL_DAC_Start(&hdac1, DAC_CHANNEL_1);
}


HAL_StatusTypeDef DAC_Stop(void)
{
	return HAL_DAC_Stop(&hdac1, DAC_CHANNEL_1);
}


HAL_StatusTypeDef DAC_SetValue(float vvalue)
{
	DAC_Start();
	uint8_t a;
	a=(uint8_t)((vvalue/(float)3.0)*255);
	DAC_Stop();
	return HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_1, DAC_ALIGN_8B_R, a);
}


uint32_t DAC_GetValue(void)
{
	return HAL_DAC_GetValue(&hdac1, DAC_CHANNEL_1);
}
