#include "pwm_read.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_dma.h"
#include "misc.h"
/********************************************************
**Name:pwm_read_file_config
**Description: pwm_read file configuration funtion
**Input:None
**Output:None
********************************************************/
void pwm_read_file_config(void)
{
	pwm_gpio_config();
	pwm_tim_config();
}
/********************************************************
**Name:pwm_read_file_config
**Description: pwm gpio configuration funtion
**Input:None
**Output:None
********************************************************/
void pwm_gpio_config(void)
{
	GPIO_InitTypeDef GPIO_InitStruction;
	
	RCC_APB2PeriphClockCmd(	PWM_READ_1_Pin_Rcc | \
							PWM_READ_2_Pin_Rcc | \
							PWM_READ_3_Pin_Rcc | \
							PWM_READ_4_Pin_Rcc | \
							PWM_READ_5_Pin_Rcc | \
							PWM_READ_6_Pin_Rcc ,ENABLE);
	
	//PA3  
	GPIO_InitStruction.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStruction.GPIO_Pin = PWM_READ_1_Pin;
	GPIO_Init(PWM_READ_1_Port,&GPIO_InitStruction);
	
	//PA4  
	GPIO_InitStruction.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStruction.GPIO_Pin = PWM_READ_2_Pin;
	GPIO_Init(PWM_READ_2_Port,&GPIO_InitStruction);
	
	//PA5  
	GPIO_InitStruction.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStruction.GPIO_Pin = PWM_READ_3_Pin;
	GPIO_Init(PWM_READ_3_Port,&GPIO_InitStruction);
	
	//PA6  
	GPIO_InitStruction.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStruction.GPIO_Pin = PWM_READ_4_Pin;
	GPIO_Init(PWM_READ_4_Port,&GPIO_InitStruction);
	
	//PA7  
	GPIO_InitStruction.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStruction.GPIO_Pin = PWM_READ_5_Pin;
	GPIO_Init(PWM_READ_5_Port,&GPIO_InitStruction);
	
	//PA8 
	GPIO_InitStruction.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStruction.GPIO_Pin = PWM_READ_6_Pin;
	GPIO_Init(PWM_READ_6_Port,&GPIO_InitStruction);
}
/********************************************************
**Name:pwm_read_file_config
**Description: pwm tim configuration funtion
**Input:None
**Output:None
********************************************************/
void pwm_tim_config(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 100;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 71;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
//	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
//	TIM_ICInitStructure.TIM_ICFilter = 0x0;
//	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;
//	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
//	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
//	TIM_ICInit(TIM3,&TIM_ICInitStructure);
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM3,ENABLE);
}
