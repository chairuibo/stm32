#ifndef _TIMER3_H
#define _TIMER3_H
#include "stm32f10x.h"

#define Timer3_CHANNEL_1_OC_Enable		1
#define Timer3_CHANNEL_2_OC_Enable		0
#define Timer3_CHANNEL_3_OC_Enable		0
#define Timer3_CHANNEL_4_OC_Enable		0

#define Timer3_Channel_1_Pin			GPIO_Pin_6
#define Timer3_Channel_1_Pin_Port		GPIOA
#define Timer3_Channel_1_Pin_Rcc		RCC_APB2Periph_GPIOA
#define Timer3_Channel_1_OCPolarity		TIM_OCPolarity_High
#define Timer3_Channel_1_Init_Pulse		5

#define Timer3_Channel_2_Pin			GPIO_Pin_7
#define Timer3_Channel_2_Pin_Port		GPIOA
#define Timer3_Channel_2_Pin_Rcc		RCC_APB2Periph_GPIOA
#define Timer3_Channel_2_OCPolarity		TIM_OCPolarity_High
#define Timer3_Channel_2_Init_Pulse		5

#define Timer3_Channel_3_Pin			GPIO_Pin_0
#define Timer3_Channel_3_Pin_Port		GPIOB
#define Timer3_Channel_3_Pin_Rcc		RCC_APB2Periph_GPIOB
#define Timer3_Channel_3_OCPolarity		TIM_OCPolarity_High
#define Timer3_Channel_3_Init_Pulse		5

#define Timer3_Channel_4_Pin			GPIO_Pin_1
#define Timer3_Channel_4_Pin_Port		GPIOB
#define Timer3_Channel_4_Pin_Rcc		RCC_APB2Periph_GPIOB
#define Timer3_Channel_4_OCPolarity		TIM_OCPolarity_High
#define Timer3_Channel_4_Init_Pulse		5

void timer3_File_Config(u8 Prescaler,u32 Period);
void timer3_Mode_Config(u8 Prescaler,u32 Period);
void timer3_GPIO_Config(void);
#endif   //end file...
