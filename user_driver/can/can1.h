#ifndef _CAN_1_H
#define _CAN_1_H

#include "stm32f10x.h"

void can1_config(void);
void can1_gpio_config(void);
void can1_mode_config(void);
void USB_LP_CAN1_RX0_IRQHandler(void);
void can1_SendData(u8 data[8]);
#endif
