#ifndef _USART2_H
#define _USART2_H

#include "stm32f10x.h"

#define USART2_TX_Pin			GPIO_Pin_2
#define USART2_TX_Port			GPIOA
#define USART2_TX_Pin_RCC		RCC_APB2Periph_GPIOA

#define USART2_RX_Pin			GPIO_Pin_3
#define USART2_RX_Port			GPIOA
#define USART2_RX_Pin_RCC		RCC_APB2Periph_GPIOA

#define USART2_RCC				RCC_APB1Periph_USART2

void usart2_File_Config(u32 BaudBate);
void usart2_GPIO_Config(void);
void usart2_Mode_Config(u32 BaudBate);
void usart2_SendData(uint8_t Data[],char number);
#endif  //end file...

