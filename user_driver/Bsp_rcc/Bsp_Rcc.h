#ifndef __BSP_RCC_H
#define	__BSP_RCC_H
#include "stm32f10x.h"
void Remap_GPIO(void);
void HSE_SetSysClock(uint32_t pllmul);
void HSI_SetSysClock(uint32_t pllmul);
#endif