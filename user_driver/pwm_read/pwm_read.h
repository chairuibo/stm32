#ifndef _PWM_READ_H
#define _PWM_READ_H

#define PWM_READ_1_Pin			GPIO_Pin_3
#define PWM_READ_1_Port			GPIOA
#define PWM_READ_1_Pin_Rcc		RCC_APB2Periph_GPIOA

#define PWM_READ_2_Pin			GPIO_Pin_4
#define PWM_READ_2_Port			GPIOA
#define PWM_READ_2_Pin_Rcc		RCC_APB2Periph_GPIOA

#define PWM_READ_3_Pin			GPIO_Pin_5
#define PWM_READ_3_Port			GPIOA
#define PWM_READ_3_Pin_Rcc		RCC_APB2Periph_GPIOA

#define PWM_READ_4_Pin			GPIO_Pin_6
#define PWM_READ_4_Port			GPIOA
#define PWM_READ_4_Pin_Rcc		RCC_APB2Periph_GPIOA

#define PWM_READ_5_Pin			GPIO_Pin_7
#define PWM_READ_5_Port			GPIOA
#define PWM_READ_5_Pin_Rcc		RCC_APB2Periph_GPIOA

#define PWM_READ_6_Pin			GPIO_Pin_8
#define PWM_READ_6_Port			GPIOA
#define PWM_READ_6_Pin_Rcc		RCC_APB2Periph_GPIOA

void pwm_read_file_config(void);
void pwm_gpio_config(void);
void pwm_tim_config(void);
#endif //  ...end file
