#ifndef _ENCODER_H
#define _ENCODER_H

#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#define encoder_A_pin       GPIO_Pin_8
#define encoder_B_pin       GPIO_Pin_9
#define encoder_pin_port    GPIOB
#define encoder_pin_rcc     RCC_APB2Periph_GPIOB

void encoder_file_configure(void);
void encoder_TIM_configure(void);
void encoder_GPIO_configure(void);
void encoder_TIM4_configure(void);
void TIM4_IRQHandler(void);
#endif
