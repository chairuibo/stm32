#ifndef _USART_H
#define _USART_H
#include "stm32f10x.h"

/*****************宏定义*****************/
#define TX_GPIO				GPIO_Pin_9
#define TXRX_GPIO_CLK		RCC_APB2Periph_GPIOA
#define RX_GPIO				GPIO_Pin_10
#define USART1_CLK			RCC_APB2Periph_USART1
#define RX_IRQ					USART1_IRQn

/***************函数声明*****************/
void USART1_Config(void);
void USART1_EXTI_Config(void);
void USART1_GPIO_Config(void);
void SendByte(uint8_t ch);
void SendString(uint8_t *str);
void usart1_SendData(uint8_t Data[],char number);
#endif
