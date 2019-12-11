#include "usart3.h"
#include "stm32f10x.h"
#include <stdio.h>
#include "delay.h"
#include "string.h"

/********************************************************
**Name:GY_51_usart3_File_Config
**Description: GY_51_usart3 File Config  funtion
**Input:None
**Output:None
********************************************************/
void usart3_File_Config(u32 BaudRate)
{
	usart3_GPIO_Config();
	usart3_Mode_Config(BaudRate);
}
/********************************************************
**Name:usart3_GPIO_Config
**Description: usart3 GPIO Config  funtion
**Input:None
**Output:None
********************************************************/
void usart3_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(USART3_TX_Pin_RCC | USART3_RX_Pin_RCC , ENABLE);
	//TX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = USART3_TX_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(USART3_TX_Port,&GPIO_InitStructure);
	
	//RX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = USART3_RX_Pin;
	GPIO_Init(USART3_RX_Port,&GPIO_InitStructure);
	
}
/********************************************************
**Name:usart3_Mode_Config
**Description: usart3 Mode Config  funtion
**Input:None
**Output:None
********************************************************/
void usart3_Mode_Config(u32 BaudRate)
{
	USART_InitTypeDef USART_InitStructure;
	
	RCC_APB1PeriphClockCmd(USART3_RCC , ENABLE);
		
	USART_InitStructure.USART_BaudRate = BaudRate;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
 	USART_InitStructure.USART_Mode =USART_Mode_Tx |USART_Mode_Rx;
	USART_InitStructure.USART_Parity =  USART_Parity_No;
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART3, &USART_InitStructure);
	
	USART_Cmd(USART3,ENABLE);
	
	USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);
}
/********************************************************
**Name:usart3_SendData
**Description: usart3 Mode Config  funtion
**Input:None
**Output:None
********************************************************/
void usart3_SendData(uint8_t Data[],char number)
{
	do{
		USART_SendData(USART3, *Data);
		Data++;
		while(USART_GetFlagStatus( USART3, USART_FLAG_TC) == RESET);
	}while(number--);
}
