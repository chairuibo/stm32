#include <stdio.h>
#include "usart.h"
#include "stm32f10x_conf.h"
/***************************************************
 *函数名称：void USART1_Config(void)
 *说明：USART1。C文件需要配置的函数
 *输入：无
 *输出：无
****************************************************/
void USART1_Config(void)
{
	USART1_GPIO_Config();
	USART1_EXTI_Config();
}
/***************************************************
 *函数名称：void USART1_GPIO_Config(void)
 *说明：USART1的GPIO口配置函数
 *输入：无
 *输出：无
****************************************************/
void USART1_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1 , ENABLE);
	
	/*RX_GPIO config*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = RX_GPIO;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/*TX_GPIO cnfig*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = TX_GPIO;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	/*USART1 config*/
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
 	USART_InitStructure.USART_Mode =USART_Mode_Tx |USART_Mode_Rx;
	USART_InitStructure.USART_Parity =  USART_Parity_No;
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &USART_InitStructure);
	
	/*使能USART1*/
	USART_Cmd(USART1, ENABLE);
	
	/*使能接收中断*/
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
}
void USART1_EXTI_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn ;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
}
/***************************************************
 *函数名称：int fput(int ch,FILEv*f);
 *说明：重定向fput和fget函数
 *输入：
 *输出：无
****************************************************/
int fputc(int ch, FILE *f)
{
		/* 发送一个字节数据到USART1 */
		USART_SendData(USART1 , (uint8_t) ch);
		
		/* 等待发送完毕 */
		while (USART_GetFlagStatus(USART1 , USART_FLAG_TXE) == RESET);		
	
		return (ch);
}
/***************************************************
 *函数名称：void SendByte(uint8_t ch)
 *说明：发送一个字节的数据
 *输入：8位数据
 *输出：无
****************************************************/
void SendByte(uint8_t ch)
{
	/*发送一个字节数据*/
	USART_SendData(USART1, ch);
	
	/*等待发送完成*/
	while(USART_GetFlagStatus( USART1, USART_FLAG_TC) == RESET);
}
/***************************************************
 *函数名称：SendString
 *说明：发送一串数据
 *输入：字符串
 *输出：无
****************************************************/
void SendString(uint8_t *str)
{
	uint8_t *s=str;
	
	do
	{
		SendByte(*s);
		s++;
	}while(*s != '\0');
}
/********************************************************
**Name:USART2_SendData
**Description: USART2 Mode Config  funtion
**Input:None
**Output:None
********************************************************/
void usart1_SendData(uint8_t Data[],char number)
{
	do
	{
		USART_SendData(USART1, *Data);
		Data++;
		while(USART_GetFlagStatus( USART1, USART_FLAG_TC) == RESET);
	}while(number--);
}
