#ifndef UART_H
#define UART_H

void MX_USART2_UART_Init(void);

HAL_StatusTypeDef UART_Transmit (uint8_t *p_pui_Data, uint16_t p_ui_Size, uint32_t p_ui_Timeout);

HAL_StatusTypeDef UART_Receive (uint8_t *p_pui_Data, uint16_t p_ui_Size, uint32_t p_ui_Timeout);

#endif
