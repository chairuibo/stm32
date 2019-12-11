#include "timer5.h"
#include "stm32f10x.h"
#include "stm32f10x_tim.h"

/********************************************************
**Name:timer5_File_Config
**Description: timer5File Config  funtion
**Input:None
**Output:None
********************************************************/
void timer5_File_Config(u8 Prescaler,u32 Period)
{
	timer5_Mode_Config(Prescaler,Period);
	timer5_GPIO_Config();
}
/********************************************************
**Name:timer5_Mode_Config
**Description: timer5 Mode Config  funtion
**Input:None
**Output:None
********************************************************/
void timer5_Mode_Config(u8 Prescaler,u32 Period)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	/*TIMER Base Init*/
	TIM_TimeBaseInitStructure.TIM_Prescaler = Prescaler;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_Period = Period;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	
	/*TIMER Channel_1 OC Init*/
#ifdef Timer5_CHANNEL_1_OC_Enable	
	TIM_OCInitStructure.TIM_OCPolarity = Timer5_Channel_1_OCPolarity;	
	TIM_OCInitStructure.TIM_Pulse = Timer5_Channel_1_Init_Pulse;
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);	
	TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Enable);
#endif
	
	/*TIMER Channel_2 OC Init*/
#ifdef Timer5_CHANNEL_2_OC_Enable	
	TIM_OCInitStructure.TIM_OCPolarity = Timer5_Channel_2_OCPolarity;
	TIM_OCInitStructure.TIM_Pulse = Timer5_Channel_2_Init_Pulse;
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);	
	TIM_OC2PreloadConfig(TIM2,TIM_OCPreload_Enable);
#endif

	/*TIMER Channel_3 OC Init*/
#ifdef Timer5_CHANNEL_3_OC_Enable	
	TIM_OCInitStructure.TIM_OCPolarity = Timer5_Channel_3_OCPolarity;
	TIM_OCInitStructure.TIM_Pulse = Timer5_Channel_3_Init_Pulse;
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);	
	TIM_OC3PreloadConfig(TIM2,TIM_OCPreload_Enable);
#endif

	/*TIMER Channel_4 OC Init*/
#ifdef Timer5_CHANNEL_4_OC_Enable	
	TIM_OCInitStructure.TIM_OCPolarity = Timer5_Channel_4_OCPolarity;
	TIM_OCInitStructure.TIM_Pulse = Timer5_Channel_4_Init_Pulse;
	TIM_OC4Init(TIM2, &TIM_OCInitStructure);	
	TIM_OC4PreloadConfig(TIM2,TIM_OCPreload_Enable);
#endif

	TIM_ARRPreloadConfig(TIM2,ENABLE);
	TIM_Cmd(TIM2,ENABLE);
}
/********************************************************
**Name:timer5_GPIO_Config
**Description: timer5 GPIO Config  funtion
**Input:None
**Output:None
********************************************************/
void timer5_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(Timer5_Channel_1_Pin_Rcc |
							Timer5_Channel_2_Pin_Rcc |
							Timer5_Channel_3_Pin_Rcc |
							Timer5_Channel_4_Pin_Rcc,ENABLE);
	
	/*Timer5 Channel 1 GPIO(PA0) Init*/
#ifdef Timer5_CHANNEL_1_OC_Enable
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = Timer5_Channel_1_Pin;
	GPIO_InitStructure.GPIO_Speed =GPIO_Speed_50MHz;
	GPIO_Init(Timer5_Channel_1_Pin_Port,&GPIO_InitStructure);
#endif

	/*Timer5 Channel 2 GPIO(PA0) Init*/
#ifdef Timer5_CHANNEL_2_OC_Enable
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = Timer5_Channel_2_Pin;
	GPIO_InitStructure.GPIO_Speed =GPIO_Speed_50MHz;
	GPIO_Init(Timer5_Channel_2_Pin_Port,&GPIO_InitStructure);
#endif

	/*Timer5 Channel 3 GPIO(PA0) Init*/
#ifdef Timer5_CHANNEL_3_OC_Enable
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = Timer5_Channel_3_Pin;
	GPIO_InitStructure.GPIO_Speed =GPIO_Speed_50MHz;
	GPIO_Init(Timer5_Channel_3_Pin_Port,&GPIO_InitStructure);
#endif

	/*Timer5 Channel 4 GPIO(PA0) Init*/
#ifdef Timer5_CHANNEL_4_OC_Enable
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = Timer5_Channel_4_Pin;
	GPIO_InitStructure.GPIO_Speed =GPIO_Speed_50MHz;
	GPIO_Init(Timer5_Channel_4_Pin_Port,&GPIO_InitStructure);
#endif
}
