#ifndef __GPIO_CALLBACK
#define __GPIO_CALLBACK
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx_it.h"
#include "sys.h"
#include "delay.h"
#include <stdio.h>
#include "display.h"
#include "DataPacket.h"
#include "rtc.h"
/*----------------------------------------------------------------------------*/

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

#endif
