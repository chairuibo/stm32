#ifndef _USART3_H
#define _USART3_H

#include "stm32f10x.h"

#define USART3_TX_Pin			GPIO_Pin_10
#define USART3_TX_Port			GPIOB
#define USART3_TX_Pin_RCC		RCC_APB2Periph_GPIOB

#define USART3_RX_Pin			GPIO_Pin_11
#define USART3_RX_Port			GPIOB
#define USART3_RX_Pin_RCC		RCC_APB2Periph_GPIOB

#define USART3_RCC				RCC_APB1Periph_USART3

void usart3_File_Config(u32 BaudBate);
void usart3_GPIO_Config(void);
void usart3_Mode_Config(u32 BaudBate);
void usart3_SendData(uint8_t Data[],char number);
#endif  //end file...

