/********************************************************************
**������һ��ģ���������Ϊ�ƶ��Ĳ���
**2019-04-12   �����ĵ�
**���ߣ�����
********************************************************************/
#ifndef _MIGONG_02_H
#define _MIGONG_02_H

#include "stm32f10x.h"
#include "stm32f10x_i2c.h"
#include "delay.h"
#include "usart.h"
#include "iic_driver.h"
#include "key.h"
#include "allFunctions.h"
#include "oled.h"
#include "stdio.h"
//#define LEFT_MODEL
#define RIGHT_MODEL
//#define FRONT_MODEL
//#define BACK_MODEL

void MiGong_02_App(void);
static void SwitchFunction(int32_t data);

#endif
