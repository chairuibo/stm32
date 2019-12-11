#ifndef DAC_H
#define DAC_H

typedef enum
{
    ClockWise = 0,
    AntiClockWise = !ClockWise
}RunDirection;

typedef enum
{
    False = 0,
    True = !False
}bool;

#include "stm32f10x.h"
#include "stm32f10x_dac.h"

#define LeftFrontWheelDirection_Pin                 GPIO_Pin_13
#define LeftBackWheelDirection_Pin                  GPIO_Pin_14
#define RightFrontWheelDirection_Pin                GPIO_Pin_12
#define RightBackWheelDirection_Pin                 GPIO_Pin_15
#define WheelDirection_Port                         GPIOE
#define WheelDirection_PortRcc                      RCC_APB2Periph_GPIOE

#define DAC_Pin                                     GPIO_Pin_5
#define DAC_Port                                    GPIOA
#define DAC_PortRcc                                 RCC_APB2Periph_GPIOA

#define setLeftFrontWheelRunDirection(a)               if(a) GPIO_SetBits(WheelDirection_Port,LeftFrontWheelDirection_Pin); \
                                                            else GPIO_ResetBits(WheelDirection_Port,LeftFrontWheelDirection_Pin);
#define setLeftBackWheelRunDirection(a)                if(a) GPIO_SetBits(WheelDirection_Port,LeftBackWheelDirection_Pin); \
                                                            else GPIO_ResetBits(WheelDirection_Port,LeftBackWheelDirection_Pin);                                                                    
#define setRightFrontWheelRunDirection(a)              if(a) GPIO_SetBits(WheelDirection_Port,RightFrontWheelDirection_Pin); \
                                                            else GPIO_ResetBits(WheelDirection_Port,RightFrontWheelDirection_Pin);                                                                
#define setRightBackWheelRunDirection(a)               if(a) GPIO_SetBits(WheelDirection_Port,RightBackWheelDirection_Pin); \
                                                            else GPIO_ResetBits(WheelDirection_Port,RightBackWheelDirection_Pin);                                                                                                                           
void configDACFile(void);
void configDACGPIO(void);
void configDirectionGPIO(void);
void configDAC(void);
void setDACValue(u16 value);

#endif

