#include "stm32g0xx_hal.h"
#include "uart.h"


UART_HandleTypeDef huart2;

void MX_USART2_UART_Init(void)
{
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    while(1);
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart2, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    while(1);
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart2, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    while(1);
  }
  if (HAL_UARTEx_DisableFifoMode(&huart2) != HAL_OK)
  {
    while(1);
  }
}

HAL_StatusTypeDef UART_Transmit(uint8_t *p_pui_Data, uint16_t p_ui_Size, uint32_t p_ui_Timeout)
{
  HAL_StatusTypeDef retStatus;
	retStatus = HAL_UART_Transmit(&huart2, p_pui_Data, p_ui_Size, p_ui_Timeout);
	if(retStatus != HAL_OK)
	{
		HAL_GPIO_TogglePin(GPIOA, 5);
	}
	return retStatus;
}

HAL_StatusTypeDef UART_Receive(uint8_t *p_pui_Data,uint16_t p_ui_Size, uint32_t p_ui_Timeout)
{
  HAL_StatusTypeDef retStatus;
	retStatus = HAL_UART_Receive(&huart2, p_pui_Data, p_ui_Size, p_ui_Timeout);
	if(retStatus != HAL_OK)
	{
		HAL_GPIO_TogglePin(GPIOA, 5);
	}
	return retStatus;
}
