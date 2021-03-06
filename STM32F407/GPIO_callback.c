/* Includes ------------------------------------------------------------------*/
#include "GPIO_callback.h"
/*----------------------------------------------------------------------------*/
//使用PA6进行测试时钟的输入
/*----------------------------------------------------------------------------*/
extern uint8_t SendRTCData[4];
extern uint8_t i;
/*----------------------------------------------------------------------------*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	static uint8_t j=0;
	if(GPIO_Pin == GPIO_PIN_6)
	{
	/*
		e15--7
		e14--6
		e13--5
		e12--4
		e11--3	
		e10--2
		e9 --1
		e8 --0
	*/
		//GPIOE->ODR=(((uint16_t)(0x46))<<8);
		GPIOE->ODR=(((uint16_t)(SendRTCData[i]))<<8);
		j++;
		if(j>3)
		{
			i++;
			j=0;
		}
		if(i>3)
		{
			i=0;
		}
	}
};

