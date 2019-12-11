#include "motor.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "misc.h"
/********************************************************
**Name:motor_file_config
**Description: motor file configuration funtion
**Input:None
**Output:None
********************************************************/
void motor_file_config(void)
{
	motor_gpio_config();
	motor_tim_config();
}
/********************************************************
**Name:motor_gpio_config
**Description: motor gpio configuration funtion (A6 A7 B0 B1)
**Input: None
**Output:None
********************************************************/
void motor_gpio_config(void)
{
	GPIO_InitTypeDef GPIO_InitStruction;
	
	RCC_APB2PeriphClockCmd(	LEFT_Crawler_0_Pin_Rcc | \
							LEFT_Crawler_1_Pin_Rcc | \
							RIGHT_Crawler_0_Pin_Rcc | \
							RIGHT_Crawler_1_Pin_Rcc ,ENABLE);
	
	//PA6  
	GPIO_InitStruction.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruction.GPIO_Pin = LEFT_Crawler_0_Pin;
	GPIO_InitStruction.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LEFT_Crawler_0_Port,&GPIO_InitStruction);
	
	//PA7 
	GPIO_InitStruction.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruction.GPIO_Pin = LEFT_Crawler_1__Pin;
	GPIO_InitStruction.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LEFT_Crawler_1_Port,&GPIO_InitStruction);
	
	//PB0 
	GPIO_InitStruction.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruction.GPIO_Pin = RIGHT_Crawler_0_Pin;
	GPIO_InitStruction.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(RIGHT_Crawler_0_Port,&GPIO_InitStruction);
	
	//PB1  
	GPIO_InitStruction.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruction.GPIO_Pin = RIGHT_Crawler_1_Pin;
	GPIO_InitStruction.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(RIGHT_Crawler_1_Port,&GPIO_InitStruction);
}
/********************************************************
**Name:motor_tim_config
**Description:motor tim configuration funtion(Timer3)
**Input:None
**Output:None
********************************************************/
void motor_tim_config(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	//Base set
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 1000;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 71;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
	//OC1 set
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC1Init(TIM3,&TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);
	
	//OC2 set
	TIM_OC2Init(TIM3,&TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);
	
	//OC3 set
	TIM_OC3Init(TIM3,&TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);
	
	//OC4 set
	TIM_OC4Init(TIM3,&TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM3,TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM3,ENABLE);
	TIM_Cmd(TIM3,DISABLE);
}
/********************************************************
**Name:setLEFT_Crawler_Speed
**Description: set LEFT_Crawler motor speed funtion (A6 A7)
**Input:Speed   >0   前进   A6输出PWM
				=0   停止   A6 A7 不输出
				<0   后退	A7输出pwm
**Output:None
********************************************************/
void setLEFT_Crawler_Speed(int16_t Speed)
{
	if(Speed >0){
		TIM_SetCompare1(TIM3,Speed);
		TIM_SetCompare2(TIM3,0);
	}else if(Speed == 0){
		TIM_SetCompare1(TIM3,0);
		TIM_SetCompare2(TIM3,0);
	}else if(Speed <0){
		TIM_SetCompare1(TIM3,0);
		TIM_SetCompare2(TIM3,-Speed);
	}
}
/********************************************************
**Name:setRIGHT_Crawler_Speed
**Description: set RIGHT_Crawler motor speed funtion (B0 B1)
**Input:Speed   >0   前进   B0输出PWM
				=0   停止   B0 B1 不输出
				<0   后退	B1 输出pwm
**Output:None
********************************************************/
void setRIGHT_Crawler_Speed(int16_t Speed)
{
	if(Speed >0){
		TIM_SetCompare3(TIM3,Speed);
		TIM_SetCompare4(TIM3,0);
	}else if(Speed == 0){
		TIM_SetCompare3(TIM3,0);
		TIM_SetCompare4(TIM3,0);
	}else if(Speed <0){
		TIM_SetCompare3(TIM3,0);
		TIM_SetCompare4(TIM3,-Speed);
	}
}
//end file...
