#ifndef __DELAY_H
#define __DELAY_H
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx_it.h"
/*----------------------------------------------------------------------------*/
//before use the function must enable the TIM3
extern TIM_HandleTypeDef htim3;
/*----------------------------------------------------------------------------*/
void Delay_us(uint32_t i);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
	
#endif
