#ifndef _BUJIN_H
#define _BUJIN_H

#include "stm32f10x.h"
#include "stm32f10x_tim.h"

#define PWM_pin             GPIO_Pin_6
#define Dir_pin             GPIO_Pin_7
#define Pin_port            GPIOA          


void bujindriver_file_config(void);
void bujin_tim_config(void);
void bujin_gpio_config(void);
#endif
