#ifndef	__FIFO_H
#define __FIFO_H
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "delay.h"
#include "sys.h"
/*----------------------------------------------------------------------------*/
/*
	wrclk---PC6(PE8)
	wrreq---PC7(PE9)
	wrfull--PC8(PE10)
	data----PC9(PE11)
*/
#define wrclk  PCout(6)//PEout(8)
#define wrreq  PCout(7)//PEout(9)
#define wrfull PCin(8) //PEin(10)
#define data   PCout(9)//PEout(11)
/*
	rdclk----PE12
	rdreq----PE13
	rdempty--PE14
	q--------PE15
*/
#define rdclk   PEout(12)
#define rdreq   PEout(13)
#define rdempty PEin(14)
#define q       PEin(15)
void FIFOWriteData(uint8_t Data);
uint8_t FIFOReadData(void);
#endif
