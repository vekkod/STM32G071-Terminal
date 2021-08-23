#include "dac.h"

I2C_HandleTypeDef hi2c1;

void MX_I2C1_Init(void)
{
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x00303D5B;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    while(1);
  }
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    while(1);
  }
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    while(1);
  }
}

HAL_StatusTypeDef memWrite(uint16_t DeviceAddress, uint16_t MemoryAddress, uint8_t* Data, uint16_t Size)
{
	return HAL_I2C_Mem_Write(&hi2c1, (DeviceAddress << 1), MemoryAddress, I2C_MEMADD_SIZE_16BIT, Data, Size, HAL_MAX_DELAY);
}

HAL_StatusTypeDef memRead(uint16_t DeviceAddress, uint16_t MemoryAddress, uint8_t* Data, uint16_t Size)
{
	return HAL_I2C_Mem_Read(&hi2c1, (DeviceAddress << 1), MemoryAddress, I2C_MEMADD_SIZE_16BIT, Data, Size, HAL_MAX_DELAY);
}
