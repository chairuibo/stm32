#ifndef _HARDWARE_I2C_1_H_
#define _HARDWARE_I2C_1_H_
#include "stm32f10x.h"
void I2C_1_Config(void);
void I2C_Master_SingleWrite(uint8_t SlaveAddress,uint8_t Reg_Address, uint8_t Data);
void I2C_Master_BufferRead(uint8_t SlaveAddress,uint8_t* pBuffer, uint8_t Reg_Address, uint16_t NumByteToRead);
#endif
