#ifndef __AD9959_H
#define __AD9959_H
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
/*----------------------------------------------------------------------------*/
//User function:
#include "delay.h"
#include "sys.h"
/*----------------------------------------------------------------------------*/
/*  REMAP AND SYSTEM CONTROL  */

#define REMAPBASE 	(*(volatile unsigned long *) 	0XFFFF0200)
#define REMAP 		(*(volatile unsigned long *) 	0XFFFF0220)
#define RSTSTA 		(*(volatile unsigned long *) 	0XFFFF0230)
#define RSTCLR 		(*(volatile unsigned long *) 	0XFFFF0234)

/*  PLL AND OSCILLATOR CONTROL  */

#define PLLBASE 	(*(volatile unsigned long *) 	0XFFFF0400)
#define PLLSTA	 	(*(volatile unsigned long *) 	0XFFFF0400)
#define POWKEY1		(*(volatile unsigned long *) 	0XFFFF0404)
#define POWCON 		(*(volatile unsigned long *) 	0XFFFF0408)
#define POWKEY2		(*(volatile unsigned long *) 	0XFFFF040C)
#define PLLKEY1		(*(volatile unsigned long *) 	0XFFFF0410)
#define PLLCON 		(*(volatile unsigned long *) 	0XFFFF0414)
#define PLLKEY2		(*(volatile unsigned long *) 	0XFFFF0418)

/*  POWER SUPPLY MONITOR   */

#define PSMBASE 	(*(volatile unsigned long *) 	0XFFFF0440)
#define PSMCON 		(*(volatile unsigned long *) 	0XFFFF0440)
#define CMPCON 		(*(volatile unsigned long *) 	0XFFFF0444)

/*	Band Gap Reference */

#define REFBASE 	(*(volatile unsigned long *) 	0XFFFF0480)
#define REFCON 		(*(volatile unsigned long *) 	0XFFFF048C)

/*  ADC INTERFACE REGISTERS   */

#define ADCBASE 	(*(volatile unsigned long *)	0XFFFF0500)
#define ADCCON 		(*(volatile unsigned long *) 	0XFFFF0500)
#define ADCCP 		(*(volatile unsigned long *) 	0XFFFF0504)
#define ADCCN 		(*(volatile unsigned long *) 	0XFFFF0508)
#define ADCSTA 		(*(volatile unsigned long *) 	0XFFFF050C)
#define ADCDAT 		(*(volatile unsigned long *) 	0XFFFF0510)
#define ADCRST 		(*(volatile unsigned long *) 	0XFFFF0514)
#define ADCGN 		(*(volatile unsigned long *) 	0XFFFF0530)
#define ADCOF 		(*(volatile unsigned long *) 	0XFFFF0534)

/* EXTERNAL MEMORY REGISTERS */

#define XMBASE		(*(volatile unsigned long *)	0XFFFFF000)
#define XMCFG		(*(volatile unsigned long *)	0XFFFFF000)
#define XM0CON		(*(volatile unsigned long *)	0XFFFFF010)
#define XM1CON		(*(volatile unsigned long *)	0XFFFFF014)
#define XM2CON		(*(volatile unsigned long *)	0XFFFFF018)
#define XM3CON		(*(volatile unsigned long *)	0XFFFFF01C)
#define XM0PAR		(*(volatile unsigned long *)	0XFFFFF020)
#define XM1PAR		(*(volatile unsigned long *)	0XFFFFF024)
#define XM2PAR		(*(volatile unsigned long *)	0XFFFFF028)
#define XM3PAR		(*(volatile unsigned long *)	0XFFFFF02C)
/*  SERIAL PORT INTERFACE PERIPHERAL  */

#define SPIBASE 	(*(volatile unsigned long *) 	0XFFFF0A00)
#define SPISTA  	(*(volatile unsigned long *) 	0XFFFF0A00)
#define SPIRX 		(*(volatile unsigned long *) 	0XFFFF0A04)
#define SPITX 		(*(volatile unsigned long *) 	0XFFFF0A08)
#define SPIDIV 		(*(volatile unsigned long *) 	0XFFFF0A0C)
#define SPICON 		(*(volatile unsigned long *) 	0XFFFF0A10)

/*----------------------------------------------------------------------------*/
//PC0--SDIO0_OUT
#define SDIO0_OUT   PCout(0)
//PC0--SDIO0_IN
#define SDIO0_IN    PCin(0)
//PC1--SDIO1
#define SDIO1   PCout(1)
//PC2--SDIO2
#define SDIO2   PCout(2)
//PC3--SDIO3
#define SDIO3   PCout(3)
//PC0--SDA_OUT
#define SDA_OUT {GPIOC->MODER&=0xfffffffc;GPIOC->MODER|=0x00000001;}
//PC0--SDA_IN
#define SDA_IN  {GPIOC->MODER&=0xfffffffc;GPIOC->MODER|=0x00000000;} 
/*----------------------------------*/
//PD7--RST
#define AD9959_RST     PDout(7)
//PD6--CLK
#define AD9959_CLK     PDout(6)
//PD5--CS
#define AD9959_CS     PDout(5)
//PD4--IOUP
#define AD9959_IOUP      PDout(4)
/*----------------------------------*/
#define P0      PDout(8)
#define P1      PDout(9)
#define P2      PDout(10)
#define P3      PDout(11)
/*----------------------------------------------------------------------------*/
#define CH0 0x01
#define CH1 0x02
#define CH2 0x04
#define CH3 0x08
/*----------------------------------------------------------------------------*/
#define FRE_REF    8.5904963602764   //频率参考
#define POW_REF    45.51111111   //相位补偿参考
//User function:
void AD9959_Init(void);
void AD9959_Write_SPI(uint8_t RegisterAddress, uint8_t NumberofRegisters, uint8_t *RegisterData);
void AD9959_Read_SPI (uint8_t RegisterAddress, uint8_t NumberofRegisters, uint8_t *RegisterData);
void IO_Update(void);
void RST(void);
void delay(uint16_t i);
//
void AD9959Test(void);
void AD9959ChannelEnable(uint8_t Channel);
void AD9959ClockConfig(void);
void AD9959SendConfirmed(uint64_t frequence);
//
void AD9959FrequenceSweepConfig(uint8_t Channel,uint32_t FreS,uint32_t FreE,double FTstep,double RTstep,uint32_t FFstep,uint32_t RFstep,uint8_t DWELL);
void AD9959_Modulation_Off(uint8_t Channel);
void AD9959_Sweep_Trigger(uint8_t Channel, uint32_t delay);
#endif
