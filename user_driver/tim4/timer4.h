#ifndef _TIMER2_H
#define _TIMER2_H
#include "stm32f10x.h"

#define Timer4_Channel_2_Pin			GPIO_Pin_7
#define Timer4_Channel_2_Pin_Port		GPIOB
#define Timer4_Channel_2_Pin_Rcc		RCC_APB2Periph_GPIOB
#define Timer4_Channel_2_OCPolarity		TIM_OCPolarity_High
#define Timer4_Channel_2_Init_Pulse		1000


void timer4_File_Config(u8 Prescaler,u32 Period);
void timer4_Mode_Config(u8 Prescaler,u32 Period);
void timer4_GPIO_Config(void);
#endif   //end file...
