/* Includes ------------------------------------------------------------------*/
#include "I2C.h"

extern I2C_HandleTypeDef hi2c1;

void I2C_WriteByte(unsigned char dev,unsigned char reg,unsigned char data) {
	HAL_I2C_Mem_Write(&hi2c1, dev, reg, 1, &data, 1, HAL_MAX_DELAY);
}
unsigned char I2C_ReadByte(unsigned char dev, unsigned char reg) {
	uint8_t data;
	HAL_I2C_Mem_Read(&hi2c1, dev, reg, 1, &data, 1, HAL_MAX_DELAY);
	return data;
}
