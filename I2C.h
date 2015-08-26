#ifndef __I2C_H__
#define __I2C_H__
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
/*----------------------------------------------------------------------------*/


void I2C_WriteByte(unsigned char,unsigned char,unsigned char);
unsigned char I2C_ReadByte(unsigned char , unsigned char);


#endif
