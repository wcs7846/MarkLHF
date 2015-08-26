#ifndef	__DATAPACKET_H
#define __DATAPACKET_H
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "delay.h"
#include "sys.h"
#include "display.h"
/*----------------------------------------------------------------------------*/

void DataPack(uint8_t* NeedPack, uint8_t* Packed);
void DataUnpack(uint8_t* Packed, uint8_t* PData);
void DataConversion(uint8_t* Packed, uint8_t* temp);
uint8_t JudgeData(uint8_t* NeedJudge);

#endif


