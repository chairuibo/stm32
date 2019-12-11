#ifndef _KEY_H
#define _KEY_H

#include "stm32f10x.h"

#define ON 	0
#define OFF 1

#define LED_Red_GPIO  			GPIO_Pin_4
#define LED_Green_GPIO  		GPIO_Pin_5
#define LED_Blue_GPIO  			GPIO_Pin_6
#define LED_GPIO_Port  			GPIOA

#define Up_Key_GPIO				GPIO_Pin_4
#define Up_Key_GPIO_port		GPIOB
#define Down_Key_GPIO			GPIO_Pin_15
#define Down_Key_GPIO_port		GPIOA
#define Left_Key_GPIO			GPIO_Pin_14
#define Left_Key_GPIO_port 		GPIOC
#define Right_Key_GPIO			GPIO_Pin_15
#define Right_Key_GPIO_port		GPIOC
#define OK_Key_GPIO				GPIO_Pin_13
#define OK_Key_GPIO_port		GPIOC
#define Power_GPIO				GPIO_Pin_8
#define Power_GPIO_Port			GPIOA

//////////////////////////////////////////////////////////////////////////////////////
#define MCU_Power(a)		if(a) GPIO_SetBits(Power_GPIO_Port,Power_GPIO);	\
								else GPIO_ResetBits(Power_GPIO_Port,Power_GPIO);
								
#define LED_Blue(a)			if(a) GPIO_SetBits(LED_GPIO_Port,LED_Blue_GPIO);	\
								else GPIO_ResetBits(LED_GPIO_Port,LED_Blue_GPIO);
#define LED_Green(a)		if(a) GPIO_SetBits(LED_GPIO_Port,LED_Green_GPIO);	\
								else GPIO_ResetBits(LED_GPIO_Port,LED_Green_GPIO);
#define LED_Red(a)			if(a) GPIO_SetBits(LED_GPIO_Port,LED_Red_GPIO);	\
								else GPIO_ResetBits(LED_GPIO_Port,LED_Red_GPIO);
								
#define getUpKeyStatue		GPIO_ReadInputDataBit(Up_Key_GPIO_port,Up_Key_GPIO)		
#define getDownKeyStatue	GPIO_ReadInputDataBit(Down_Key_GPIO_port,Down_Key_GPIO)		
#define getLeftKeyStatue	GPIO_ReadInputDataBit(Left_Key_GPIO_port,Left_Key_GPIO)		
#define getRightKeyStatue	GPIO_ReadInputDataBit(Right_Key_GPIO_port,Right_Key_GPIO)		
#define getOKKeyStatue		GPIO_ReadInputDataBit(OK_Key_GPIO_port,OK_Key_GPIO)										

/////////////////////////////////////////////////////////////////////////////////////////
void Key_Config(void);
void Key_GPIO_Config(void);
void Key_EXTI_Config(void);
//void And_minu(uint8_t* Exti_flag,u8* value,u8 x);
void And_minu(u8* value,u8 x);
void EXTI9_5_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);
void EXTI3_IRQHandler(void);
void EXTI4_IRQHandler(void);

#endif
