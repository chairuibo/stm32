#include "timer4.h"
#include "stm32f10x.h"
#include "stm32f10x_tim.h"

/********************************************************
**Name:timer4_File_Config
**Description: timer4File Config  funtion
**Input:None
**Output:None
********************************************************/
void timer4_File_Config(u8 Prescaler,u32 Period)
{
	timer4_Mode_Config(Prescaler,Period);
	timer4_GPIO_Config();
}
/********************************************************
**Name:timer4_Mode_Config
**Description: timer4 Mode Config  funtion
**Input:None
**Output:None
********************************************************/
void timer4_Mode_Config(u8 Prescaler,u32 Period)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	/*TIMER Base Init*/
	TIM_TimeBaseInitStructure.TIM_Prescaler = Prescaler;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_Period = Period;
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		
	TIM_OCInitStructure.TIM_OCPolarity = Timer4_Channel_2_OCPolarity;
	TIM_OCInitStructure.TIM_Pulse = Timer4_Channel_2_Init_Pulse;
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);	
	TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(TIM4,ENABLE);
	TIM_Cmd(TIM4,ENABLE);
}
/********************************************************
**Name:Timer4_GPIO_Config
**Description: timer4 GPIO Config  funtion
**Input:None
**Output:None
********************************************************/
void timer4_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(	Timer4_Channel_2_Pin_Rcc ,ENABLE);


	/*Timer4 Channel 2 GPIO(PB7) Init*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = Timer4_Channel_2_Pin;
	GPIO_InitStructure.GPIO_Speed =GPIO_Speed_50MHz;
	GPIO_Init(Timer4_Channel_2_Pin_Port,&GPIO_InitStructure);

}
