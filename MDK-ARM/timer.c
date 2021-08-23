#include "timer.h"


TIM_HandleTypeDef htim16;


float time;

void SysTick_Handler(void)
{
  HAL_IncTick();
	time=(HAL_GetTick());
  time/= (float)636.74694822;
}


void MX_TIM16_Init(void)
{
  htim16.Instance = TIM16;
  htim16.Init.Prescaler = 16000;
  htim16.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim16.Init.Period = 0;
  htim16.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim16.Init.RepetitionCounter = 0;
  htim16.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim16) != HAL_OK)
  {
    while(1);
  }
}


HAL_StatusTypeDef TIMER_Start(void)
{
	HAL_TIM_IC_Start_IT(&htim16, TIM_CHANNEL_1);
	HAL_TIM_Base_Start(&htim16);
	return HAL_TIM_Base_Start_IT(&htim16);
}



float TIMER_time(void)
{
		return time;
}
