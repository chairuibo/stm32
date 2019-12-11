#ifndef _DELAY_H
#define _DELAY_H
#include "stm32f10x.h"
void SysTick_Init(void);
void delay_10us(__IO u32 nTime);
void TimingDelay_Decrement(void);
#define delay_ms(x) delay_10us(100*x)	 //µ¥Î»ms
//#define delay_us(x) delay_10us(x/10)
#endif
