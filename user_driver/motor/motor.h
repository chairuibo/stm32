#ifndef _MCCRAM_MOTOR_H
#define _MCCRAM_MOTOR_H

#include "stm32f10x.h"

#define LEFT_Crawler_0_Pin				GPIO_Pin_6
#define LEFT_Crawler_0_Port				GPIOA
#define LEFT_Crawler_0_Pin_Rcc			RCC_APB2Periph_GPIOA

#define LEFT_Crawler_1__Pin				GPIO_Pin_7
#define LEFT_Crawler_1_Port				GPIOA
#define LEFT_Crawler_1_Pin_Rcc			RCC_APB2Periph_GPIOA

#define RIGHT_Crawler_1_Pin				GPIO_Pin_1
#define RIGHT_Crawler_1_Port			GPIOB
#define RIGHT_Crawler_1_Pin_Rcc			RCC_APB2Periph_GPIOB

#define RIGHT_Crawler_0_Pin				GPIO_Pin_0
#define RIGHT_Crawler_0_Port			GPIOB
#define RIGHT_Crawler_0_Pin_Rcc			RCC_APB2Periph_GPIOB



									
void motor_file_config(void);
void motor_gpio_config(void);
void motor_tim_config(void);
void setLEFT_Crawler_Speed(int16_t Speed);
void setRIGHT_Crawler_Speed(int16_t Speed);
#endif //  ...end file
