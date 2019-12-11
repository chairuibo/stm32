#include "timer6.h"
#include "stm32f10x.h"
#include "stm32f10x_tim.h"

/********************************************************
**Name:timer6_File_Config
**Description: Timer6File Config  funtion
**Input:None
**Output:None
********************************************************/
void timer6_File_Config(u8 Prescaler,u32 Period)
{
	timer6_Mode_Config(Prescaler,Period);
}
/********************************************************
**Name:timer6_Mode_Config
**Description: Timer6 Mode Config  funtion
**Input:None
**Output:None
********************************************************/
void timer6_Mode_Config(u8 Prescaler,u32 Period)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
	
	/*TIMER Base Init*/
	TIM_TimeBaseInitStructure.TIM_Prescaler = Prescaler;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_Period = Period;
	TIM_TimeBaseInit(TIM6,&TIM_TimeBaseInitStructure);

	TIM_ARRPreloadConfig(TIM6,ENABLE);
	TIM_Cmd(TIM6,ENABLE);
}

