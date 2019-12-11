#ifndef _HARDWARE_I2C_2_H_
#define _HARDWARE_I2C_2_H_
#include "stm32f10x.h"

#define I2C1_SlaveAddr 0x40

void I2C_2_Config(void);
void Single_Write(uint8_t SlaveAddress,uint8_t* pBuffer, uint32_t NumByteToWrite);
void I2C_Master_BufferRead(uint8_t SlaveAddress,int8_t* pBuffer, uint16_t NumByteToRead);
#endif
