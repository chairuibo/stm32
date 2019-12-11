/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTI
  
  AL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "stm32f10x_gpio.h"
#include "usart.h"
#include "delay.h"
#include "oled.h"
/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */

void SysTick_Handler(void)
{
	TimingDelay_Decrement();
}


/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/
/********************************************************************************
*************************串口中断服务函数****************************************
********************************************************************************/
extern uint8_t Command_1[20];
extern uint8_t Command_2[20];
extern uint8_t Command_3[20];
u8 Receive_start_1 = 0;
u8 Receive_succeed_1 = 0;
u8 Receive_start_2 = 0;
u8 Receive_succeed_2 = 0;
u8 Receive_start_3 = 0;
u8 Receive_succeed_3 = 0;
void USART1_IRQHandler(void)
{
	static u8 i=0;
	if(USART_GetITStatus(USART1,USART_IT_RXNE) == SET)
	{
		
		Command_1[i] = USART_ReceiveData(USART1);
		if(Receive_start_1 == 1){
			i++;
		}
		if(Command_1[i] == '#'){	
			Receive_start_1 = 1;
			i++;
		}else if(i == 7){
			Receive_start_1 = 0;
			Receive_succeed_1 = 1;
			i=0;
		}
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	}
}
//void USART2_IRQHandler(void)
//{
//	static u8 j=0;
//	if(USART_GetITStatus(USART2,USART_IT_RXNE) == SET)
//	{
//		
//		Command_2[j] = USART_ReceiveData(USART2);
//		if(Receive_start_2 == 1){
//			j++;
//		}
//		if(Command_2[j] == '#'){	
//			Receive_start_2 = 1;
//			j++;
//		}else if(j == 7){
//			Receive_start_2 = 0;
//			Receive_succeed_2 = 1;
//			j=0;
//		}
//		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
//	}
//}
//void USART3_IRQHandler(void)
//{
//	static u8 x = 0;
//	if(USART_GetITStatus(USART3,USART_IT_RXNE) == SET)
//	{
//		Command_3[x] = USART_ReceiveData(USART3);
//		if(Receive_start_3 == 1){
//			x++;
//		}
//		if(Command_3[x] == '#'){	
//			Receive_start_3 = 1;
//			x++;
//		}else if(x == 7){
//			Receive_start_3 = 0;
//			Receive_succeed_3 = 1;
//			x=0;
//		}
//		USART_ClearITPendingBit(USART3,USART_IT_RXNE);
//	}
//}
/********************************************************************************
*************************定时器3中断服务函数*************************************
********************************************************************************/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
