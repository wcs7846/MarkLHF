#ifndef __OLED_I2C_H
#define	__OLED_I2C_H
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
/*----------------------------------------------------------------------------*/
//User function:
#include "delay.h"
#include "sys.h"
#include "codetab.h"
//#include "IIC.h"
#include "I2C.h"
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
#define OLED_ADDRESS	0x78 //通过调整0R电阻,屏可以0x78和0x7A两个地址 -- 默认0x78

void OLED_Init(void);
void OLED_SetPos(unsigned char x, unsigned char y);
void OLED_Fill(unsigned char fill_Data);
void OLED_CLS(void);
void OLED_ON(void);
void OLED_OFF(void);
void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize);
void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N);
void OLED_ShowNum(unsigned char x, unsigned char y, unsigned char N);
//x:1-128  y:0-8
void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,const unsigned char *BMP);
uint8_t OLED_ShowString(unsigned char ch[]);

extern const uint8_t PICTURE[];
#endif
