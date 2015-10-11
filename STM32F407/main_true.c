/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx_it.h"
/*----------------------------------------------------------------------------*/
//User function:
#include "delay.h"
#include "rtc.h"
#include "ad9959.h"
//#include "pwm.h"
#include "sys.h"
//#include "dds.h"
//#include "ltc1420.h"
//#include "dac904.h"
#include "I2C.h"
#include "OLED_I2C.h"
#include <stdio.h>
#include "fifo.h"
#include "display.h"
#include "DataPacket.h"
#include "GPIO_callback.h"
/*----------------------------------------------------------------------------*/
extern TIM_HandleTypeDef htim4;
extern UART_HandleTypeDef huart1;
/*----------------------------------------------------------------------------*/
uint8_t SendRTCData[4];
uint8_t i=0;
/*----------------------------------------------------------------------------*/
void main_true(void)
{
/*----------------------------------------------------------------------------*/
//中间变量
	uint8_t RTCTime[3];
	uint8_t RTCDate[3];

	uint8_t PData[3];
//	uint8_t i=0;
//	uint8_t Data[4]={1,1,1,1};
//{0x0E,0x38,0xE3,0x8E},//10MHz
//{0x00,0x03,0xA4,0x11},//10KHz--945.38KHz
	
//	DAC904_Init();
//	LTC1420_Init();
//	for(i=0;i<4;i++)
//		printf("%d\t",Data[i]);
//	printf("\r\n");
/*----------------------------------------------------------------------------------------------------------*/
	//开启TIM3的中断
	HAL_TIM_Base_Start_IT(&htim3);
	HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
/*----------------------------------------------------------------------------------------------------------*/
//OLED初始化
	OLED_Init();
//OLED显示
	OLED_Fill(0xff);
	HAL_Delay(200);
	OLED_Fill(0x00);
//显示格式--RTC	
	RTC_Config();

	OLED_ShowStr(0,7,"FIFOData:",1);
	//DDS:AD9959初始化
/*----------------------------------------------------------------------------------------------------------*/
//扫频
	AD9959_Init();
	AD9959SendConfirmed(8000000);
//	AD9959FrequenceSweepConfig(CH1,8000000,100000000,5000,5000,10000,10000,1);
	IO_Update();
		
		//IO_Update();
/*----------------------------------------------------------------------------------------------------------*/
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
	while (1)
  {
		//完成一帧的结构为70--秒钟；80--分钟；90--时钟
		RTC_DateShow(RTCDate);
		RTC_TimeShow(RTCTime);
		DataPack(RTCTime,SendRTCData);
		DisplayNum3(9,7,SendRTCData[i]);
//		AD9959_Sweep_Trigger(CH1,33);
//		HAL_Delay(10);
	}
/*----------------------------------------------------------------------------------------------------------*/
//	吕洋上位机使用的数据发送格式
//	putchar(0xAA);
//	putchar(0xEE);
//	HAL_UART_Transmit(&huart1, (unsigned char*)&temp1, 4, HAL_MAX_DELAY);
//	HAL_UART_Transmit(&huart1, (unsigned char*)&temp1, 4, HAL_MAX_DELAY);
//	HAL_UART_Transmit(&huart1, (unsigned char*)&temp1, 4, HAL_MAX_DELAY);
//	HAL_UART_Transmit(&huart1, (unsigned char*)&temp1, 4, HAL_MAX_DELAY);	
/*----------------------------------------------------------------------------------------------------------*/
}

#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)	  
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

PUTCHAR_PROTOTYPE
{
	while((USART1->SR&0X40)==0); //Send till fin.  
    USART1->DR = (unsigned char) ch; 
	return ch;
}

