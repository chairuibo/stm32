#include "usart2.h"
#include "stm32f10x.h"
#include <stdio.h>
#include "delay.h"
#include "string.h"

/********************************************************
**Name:GY_51_USART2_File_Config
**Description: GY_51_USART2 File Config  funtion
**Input:None
**Output:None
********************************************************/
void usart2_File_Config(u32 BaudRate)
{
	usart2_GPIO_Config();
	usart2_Mode_Config(BaudRate);
}
/********************************************************
**Name:USART2_GPIO_Config
**Description: USART2 GPIO Config  funtion
**Input:None
**Output:None
********************************************************/
void usart2_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(USART2_TX_Pin_RCC | USART2_RX_Pin_RCC , ENABLE);
	//TX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = USART2_TX_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(USART2_TX_Port,&GPIO_InitStructure);
	
	//RX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = USART2_RX_Pin;
	GPIO_Init(USART2_RX_Port,&GPIO_InitStructure);
	
}
/********************************************************
**Name:USART2_Mode_Config
**Description: USART2 Mode Config  funtion
**Input:None
**Output:None
********************************************************/
void usart2_Mode_Config(u32 BaudRate)
{
	USART_InitTypeDef USART_InitStructure;
	
	RCC_APB1PeriphClockCmd(USART2_RCC , ENABLE);
		
	USART_InitStructure.USART_BaudRate = BaudRate;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
 	USART_InitStructure.USART_Mode =USART_Mode_Tx |USART_Mode_Rx;
	USART_InitStructure.USART_Parity =  USART_Parity_No;
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART2, &USART_InitStructure);
	
	USART_Cmd(USART2,ENABLE);
	
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
}
/********************************************************
**Name:USART2_SendData
**Description: USART2 Mode Config  funtion
**Input:None
**Output:None
********************************************************/
void usart2_SendData(uint8_t Data[],char number)
{
	do{
		USART_SendData(USART2, *Data);
		Data++;
		while(USART_GetFlagStatus( USART2, USART_FLAG_TC) == RESET);
	}while(number--);
}
