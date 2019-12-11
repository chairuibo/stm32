#ifndef ADC_H
#define ADC_H
#include "stm32f10x.h"

extern int16_t ADC_value;

#define POSADC_Pin            			GPIO_Pin_1
#define POSADC_Port                    	GPIOA
#define POSADC_PortRcc                 	RCC_APB2Periph_GPIOA

#define ADC_RCC                         RCC_APB2Periph_ADC1

void configADCFile(void);
void configADCGPIO(void); 
void configADC(void);
void configADCNVIC(void);
void ADC1_2_IRQHandler(void);
void readADCValue(int32_t *value);

#endif
