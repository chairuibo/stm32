#ifndef _SPI1_H
#define _SPI1_H

#include "stm32f10x.h"

#define SPI1_MOSI_Pin			GPIO_Pin_7
#define SPI1_MOSI_Port			GPIOA
#define SPI1_MOSI_Pin_Rcc		RCC_APB2Periph_GPIOA

#define SPI1_CLK_Pin			GPIO_Pin_5
#define SPI1_CLK_Port			GPIOB
#define SPI1_CLK_Pin_Rcc		RCC_APB2Periph_GPIOB

#define USART3_RCC				RCC_APB1Periph_USART3

void usart3_File_Config(u32 BaudBate);
void usart3_GPIO_Config(void);
void usart3_Mode_Config(u32 BaudBate);
void usart3_SendData(uint8_t Data[],char number);
#endif  //end file...

