#ifndef _TIMER5_H
#define _TIMER5_H
#include "stm32f10x.h"

#define Timer5_CHANNEL_1_OC_Enable
#define Timer5_CHANNEL_2_OC_Enable
#define Timer5_CHANNEL_3_OC_Enable
#define Timer5_CHANNEL_4_OC_Enable

#define Timer5_Channel_1_Pin			GPIO_Pin_0
#define Timer5_Channel_1_Pin_Port		GPIOA
#define Timer5_Channel_1_Pin_Rcc		RCC_APB2Periph_GPIOA
#define Timer5_Channel_1_OCPolarity		TIM_OCPolarity_High
#define Timer5_Channel_1_Init_Pulse		5

#define Timer5_Channel_2_Pin			GPIO_Pin_1
#define Timer5_Channel_2_Pin_Port		GPIOA
#define Timer5_Channel_2_Pin_Rcc		RCC_APB2Periph_GPIOA
#define Timer5_Channel_2_OCPolarity		TIM_OCPolarity_High
#define Timer5_Channel_2_Init_Pulse		5

#define Timer5_Channel_3_Pin			GPIO_Pin_2
#define Timer5_Channel_3_Pin_Port		GPIOA
#define Timer5_Channel_3_Pin_Rcc		RCC_APB2Periph_GPIOA
#define Timer5_Channel_3_OCPolarity		TIM_OCPolarity_High
#define Timer5_Channel_3_Init_Pulse		5

#define Timer5_Channel_4_Pin			GPIO_Pin_3
#define Timer5_Channel_4_Pin_Port		GPIOA
#define Timer5_Channel_4_Pin_Rcc		RCC_APB2Periph_GPIOA
#define Timer5_Channel_4_OCPolarity		TIM_OCPolarity_High
#define Timer5_Channel_4_Init_Pulse		5

void timer5_File_Config(u8 Prescaler,u32 Period);
void timer5_Mode_Config(u8 Prescaler,u32 Period);
void timer5_GPIO_Config(void);
#endif   //end file...
