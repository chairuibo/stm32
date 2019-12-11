#include "timer7.h"
#include "stm32f10x.h"
#include "stm32f10x_tim.h"

/********************************************************
**Name:timer7_File_Config
**Description: Timer7 File Config  funtion
**Input:None
**Output:None
********************************************************/
void timer7_File_Config(u8 Prescaler,u32 Period)
{
	timer7_Mode_Config(Prescaler,Period);
}
/********************************************************
**Name:timer2_Mode_Config
**Description: Timer2 Mode Config  funtion
**Input:None
**Output:None
********************************************************/
void timer7_Mode_Config(u8 Prescaler,u32 Period)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
	
	/*TIMER Base Init*/
	TIM_TimeBaseInitStructure.TIM_Prescaler = Prescaler;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_Period = Period;
	TIM_TimeBaseInit(TIM7,&TIM_TimeBaseInitStructure);

	TIM_ARRPreloadConfig(TIM7,ENABLE);
	TIM_Cmd(TIM7,ENABLE);
}
