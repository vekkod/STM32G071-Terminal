#ifndef I2C_H
#define I2C_H

#include "stm32g0xx.h"

void MX_I2C1_Init(void);

HAL_StatusTypeDef memWrite(uint16_t DeviceAddress, uint16_t MemoryAddress, uint8_t* Data, uint16_t Size);

HAL_StatusTypeDef memRead(uint16_t DeviceAddress, uint16_t MemoryAddress, uint8_t* Data, uint16_t Size);

#endif
