#include "stm32f10x.h"
#include "usart.h"
#include "delay.h"
#include "System_interrupt.h"
#include "stdio.h"
#include "can1.h"
#include "key.h"
#include "Bsp_RCC.h"
#include "timer3.h"

/**************************************************
**Name: RCC_config
**Description: 系统板上没有晶振的时候需要此配置
**Input:None
**Output:None
**************************************************/
void RCC_config(void)
{
	Remap_GPIO();
	HSI_SetSysClock(RCC_PLLMul_16);
}
/**************************************************
**Name: system_Init
**Description: OS Init
**Input:None
**Output:None
**************************************************/
void system_Init(void)
{
//	RCC_config();
	SysTick_Init();
	all_interrupt_config();
	USART1_Config();
	can1_config();
	Key_Config();
	timer3_File_Config(72,1000);
}
uint8_t Key[9];
uint8_t Command_1[20]={'#',0,0,0,0,0,'!'};
uint8_t Command_2[20]={'#',0,0,0,0,0,'!'};
uint8_t Command_3[20]={'#',0,0,0,0,0,'!'};
u8 CAN_senddata[8] = {0};
u8 CAN_receivedata[8] = {0};
extern u8 CAN_receive_falg;
extern u8 Receive_succeed_1;
extern u8 Receive_succeed_2;
extern u8 Receive_succeed_3;
void xiangzadi(u16 pinlv);
int main()
{
	CanRxMsg RxMessage;
	system_Init();

	TIM_SetCompare1(TIM3,500);
//	delay_ms(500);
	xiangzadi(2000);
	while(1)
	{
		LED_Green(ON);
		delay_ms(2000);
		LED_Green(OFF);
		delay_ms(2000);
	}
}
void xiangzadi(u16 pinlv)
{
	u32 axiba = 1000000 / pinlv;
	TIM_SetAutoreload(TIM3,axiba);
	TIM_SetCompare1(TIM3,axiba/2);
}
////		if(CAN_receive_falg == 1){
////			CAN_receive_falg = 0;
////			LED_Blue(ON);
////		}
//		CAN_senddata[0] = 94;
//		CAN_senddata[1] = 11;
//		CAN_senddata[2] = 2;
//		CAN_senddata[3] = 42;
//		can1_SendData(CAN_senddata);
//		LED_Green(ON);
//		delay_ms(300);
//		LED_Green(OFF);
//		delay_ms(300);
