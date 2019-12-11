#ifndef _SLAVER_SPI_H
#define _SLAVER_SPI_H

#include "stm32f10x.h"

extern uint16_t SPI_ReceiveData;

#define NSS_Pin                 GPIO_Pin_12
#define MISO_Pin                GPIO_Pin_14
#define MOSI_Pin                GPIO_Pin_15
#define CLK_Pin                 GPIO_Pin_13
#define SPI_Pin_port            GPIOB
#define SPI_Pin_Rcc             RCC_APB2Periph_GPIOB

void slaver_spi_file_Configure(void);
void spi_mode_Configure(void);
void spi_gpio_Configure(void);
void spi_NVIC_Configure(void);
void SPI2_IRQHandler(void);
#endif
