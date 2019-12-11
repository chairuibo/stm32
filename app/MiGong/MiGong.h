/********************************************************************
**自身输入数据作为移动的步数
**2019-04-12   修改iic发送字符数
**作者：柴锐波
********************************************************************/
#ifndef _MIGONG_H
#define _MIGONG_H

#include "stm32f10x.h"
#include "stm32f10x_i2c.h"
#include "delay.h"
#include "usart.h"
#include "iic_driver.h"
#include "key.h"
#include "allFunctions.h"
#include "oled.h"
#include "stdio.h"

#define I2C1_SlaveAddr 0x40

#define LEFT_MODEL
//#define RIGHT_MODEL
//#define FRONT_MODEL
//#define BACK_MODEL


static int32_t DataFunction(u8 data[4],u8 xunhuan_count);
void MiGong_App(void);
void And_minu(u8* value,u8 x);
#endif
