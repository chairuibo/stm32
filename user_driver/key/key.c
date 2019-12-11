#include "key.h"
#include "delay.h"
#include "allFunctions.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_exti.h"

extern uint8_t Key[9];

/***************************************************
 *�������ƣ�Key_Config
 *˵�����������ú���
 *���룺��
 *�������
****************************************************/
void Key_Config(void)
{
	Key_GPIO_Config();
//	Key_EXTI_Config();
}
void Key_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB |\
							RCC_APB2Periph_GPIOA |\
							RCC_APB2Periph_GPIOC |\
							RCC_APB2Periph_GPIOD |\
							RCC_APB2Periph_AFIO,ENABLE);

	//up Key
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Pin = Up_Key_GPIO ;
	GPIO_Init(Up_Key_GPIO_port,&GPIO_InitStructure);
	//down Key
	GPIO_InitStructure.GPIO_Pin = Down_Key_GPIO ;
	GPIO_Init(Down_Key_GPIO_port,&GPIO_InitStructure);
	//left Key
	GPIO_InitStructure.GPIO_Pin = Left_Key_GPIO ;
	GPIO_Init(Left_Key_GPIO_port,&GPIO_InitStructure);
	//right Key
	GPIO_InitStructure.GPIO_Pin = Right_Key_GPIO ;
	GPIO_Init(Right_Key_GPIO_port,&GPIO_InitStructure);
	//ok Key
	GPIO_InitStructure.GPIO_Pin = OK_Key_GPIO ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(OK_Key_GPIO_port,&GPIO_InitStructure);
	
	//LED 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = LED_Red_GPIO\
									|LED_Green_GPIO \
									|LED_Blue_GPIO ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED_GPIO_Port,&GPIO_InitStructure);
	
	LED_Green(OFF);
	LED_Blue(OFF);
	LED_Red(OFF);
	
	//Power
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = Power_GPIO;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Power_GPIO_Port,&GPIO_InitStructure);
//	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource13);
//											|GPIO_PinSource2 \
//											|GPIO_PinSource3 \
//											|GPIO_PinSource4 \
//											|GPIO_PinSource5 \
//											|GPIO_PinSource6 \
//											|GPIO_PinSource7 \
//											|GPIO_PinSource8 );		
////											
}
void Key_EXTI_Config(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line13;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_Init(&EXTI_InitStructure);
}

#ifdef _DATAFunction
/***************************************************
 *�������ƣ�and_minu
 *˵�����жϰ����Ƿ���
 *���룺Exti_flag  �����Ƿ���
		value ��Ӧ�仯��λ
		flag �Ӽ�����
 *�����
****************************************************/
//void And_minu(uint8_t* Exti_flag, u8* value,u8 x)
void And_minu(u8* value,u8 x)
{
	switch(x)
	{
		case 0: (*value)--; if(*value < '0') *value = '0'; break;
		case 1: (*value)++; if(*value > '9') *value = '9'; break;
		default : *value = '5';
	}
	/*״ָ̬ʾ��*/
	LED_Green(OFF);
	LED_Blue(ON);
	LED_Red(OFF);
}
#endif
/***************************************************
 *�������ƣ�EXTI9_5_IRQHandler
 *˵���������жϷ�����
 *���룺��
 *�������
****************************************************/
void EXTI9_5_IRQHandler(void)
{
//#ifdef _DATAFunction
	if(EXTI_GetITStatus(EXTI_Line8) != RESET)
	{
		delay_ms(20);
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8) == SET)	Key[7] = 1;
		EXTI_ClearITPendingBit(EXTI_Line8);
	}
	if(EXTI_GetITStatus(EXTI_Line7) != RESET)
	{
		delay_ms(20);
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7) == SET)	Key[6] = 1;
		EXTI_ClearITPendingBit(EXTI_Line7);
	}
	if(EXTI_GetITStatus(EXTI_Line6) != RESET)
	{
		delay_ms(20);
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6) == SET)	Key[5] = 1;
		EXTI_ClearITPendingBit(EXTI_Line6);
	}
	if(EXTI_GetITStatus(EXTI_Line5) != RESET)
	{
		delay_ms(20);
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5) == SET)	Key[4] = 1;
		EXTI_ClearITPendingBit(EXTI_Line5);
	}
//#endif
	
}
/***************************************************
 *�������ƣ�EXTI9_5_IRQHandler
 *˵���������жϷ�����
 *���룺��
 *�������
****************************************************/
void EXTI1_IRQHandler(void)
{
	
	if(EXTI_GetITStatus(EXTI_Line1) != RESET)
	{
		delay_ms(20);
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == SET)	Key[0] = 1;
		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}
/***************************************************
 *�������ƣ�EXTI9_5_IRQHandler
 *˵���������жϷ�����
 *���룺��
 *�������
****************************************************/
void EXTI2_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line2) != RESET)
	{
		delay_ms(20);
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2) == SET)	Key[1] = 1;
		EXTI_ClearITPendingBit(EXTI_Line2);
	}
}
/***************************************************
 *�������ƣ�EXTI9_5_IRQHandler
 *˵���������жϷ�����
 *���룺��
 *�������
****************************************************/
void EXTI3_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line3) != RESET)
	{
		delay_ms(20);
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3) == SET)	Key[2] = 1;
		EXTI_ClearITPendingBit(EXTI_Line3);
	}
}
/***************************************************
 *�������ƣ�EXTI9_5_IRQHandler
 *˵���������жϷ�����
 *���룺��
 *�������
****************************************************/
void EXTI4_IRQHandler(void)
{	
	if(EXTI_GetITStatus(EXTI_Line4) != RESET)
	{
		delay_ms(20);
//		Key[8]++;
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4) == SET)	Key[3] = 1;
		EXTI_ClearITPendingBit(EXTI_Line4);
	}
}
