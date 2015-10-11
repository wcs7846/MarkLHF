/* Includes ------------------------------------------------------------------*/
#include "delay.h"
/*----------------------------------------------------------------------------*/
volatile uint8_t delayOK;

void Delay_us(uint32_t i)
{
	//查询法
//	uint8_t temp;
//	TIM3->ARR = (i);
//	TIM3->CNT = 0x00;
//	HAL_TIM_Base_Start(&htim3);
//	do 
//	{
//		temp = TIM3->CNT;
//	}while(temp<(i));
//	HAL_TIM_Base_Stop(&htim3);
	//中断法
	htim3.Instance->ARR = i-2;
	HAL_TIM_Base_Start(&htim3);
	delayOK = 0;
	while(0==delayOK);
};
//如果需要延时1ms则直接使用HAL_Delay函数即可
//也可以用Delay_us函数重新编写一份

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim == &htim3)
		delayOK = 1;
	HAL_TIM_Base_Stop(&htim3);
}
