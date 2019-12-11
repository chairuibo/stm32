#include <stdio.h>
#include "usart.h"
#include "stm32f10x_conf.h"
/***************************************************
 *�������ƣ�void USART1_Config(void)
 *˵����USART1��C�ļ���Ҫ���õĺ���
 *���룺��
 *�������
****************************************************/
void USART1_Config(void)
{
	USART1_GPIO_Config();
	USART1_EXTI_Config();
}
/***************************************************
 *�������ƣ�void USART1_GPIO_Config(void)
 *˵����USART1��GPIO�����ú���
 *���룺��
 *�������
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
	
	/*ʹ��USART1*/
	USART_Cmd(USART1, ENABLE);
	
	/*ʹ�ܽ����ж�*/
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
 *�������ƣ�int fput(int ch,FILEv*f);
 *˵�����ض���fput��fget����
 *���룺
 *�������
****************************************************/
int fputc(int ch, FILE *f)
{
		/* ����һ���ֽ����ݵ�USART1 */
		USART_SendData(USART1 , (uint8_t) ch);
		
		/* �ȴ�������� */
		while (USART_GetFlagStatus(USART1 , USART_FLAG_TXE) == RESET);		
	
		return (ch);
}
/***************************************************
 *�������ƣ�void SendByte(uint8_t ch)
 *˵��������һ���ֽڵ�����
 *���룺8λ����
 *�������
****************************************************/
void SendByte(uint8_t ch)
{
	/*����һ���ֽ�����*/
	USART_SendData(USART1, ch);
	
	/*�ȴ��������*/
	while(USART_GetFlagStatus( USART1, USART_FLAG_TC) == RESET);
}
/***************************************************
 *�������ƣ�SendString
 *˵��������һ������
 *���룺�ַ���
 *�������
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
