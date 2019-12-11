#ifndef _CSB_IIC_DRIVER_H
#define _CSB_IIC_DRIVER_H

#include "stm32f10x.h"
#include "stm32f10x_i2c.h"
#include "delay.h"
#include "usart.h"
#include "stdbool.h"


#define FALSE 0
#define TRUE  1

#define SCL_H         GPIOB->BSRR = GPIO_Pin_13
#define SCL_L         GPIOB->BRR  = GPIO_Pin_13
#define SDA_H         GPIOB->BSRR = GPIO_Pin_14
#define SDA_L         GPIOB->BRR  = GPIO_Pin_14
#define SCL_read      GPIOB->IDR  & GPIO_Pin_13
#define SDA_read      GPIOB->IDR  & GPIO_Pin_14

#define I2C1_OWN_ADDRESS7 0xA0
#define I2C_Speed 100000
#define KS103_Addr    0xd6// 0xe8  //0x74
void i2c_Config(void);
void I2C_delay(void);
bool I2C_Start(void);
void I2C_Stop(void);
void I2C_Ack(void);
void I2C_NoAck(void);
bool I2C_WaitAck(void) 	;
void I2C_SendByte(u8 SendByte) ;
uint8_t I2C_ReadByte(void);
void Single_Write(unsigned char SlaveAddress,unsigned char* REG_Address,unsigned char REG_data);
void Init_KS103(void);
void change_addr(unsigned char old_addr,unsigned char new_addr);
unsigned char Single_Read(unsigned char SlaveAddress,unsigned char REG_Address);

#endif
