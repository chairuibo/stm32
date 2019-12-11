/********************************************************************
**接收上一个模块的数据作为移动的步数
**2019-04-12   创建文档
**作者：柴锐波
********************************************************************/
#include "MiGong_02.h"

extern uint8_t Command_1[20];
extern u8 Receive_succeed_1;
/***************************************************
 *函数名称：MiGong_App
 *说明：迷宫任务需要的基本行进模块
 *输入：无
 *输出：无
****************************************************/
void MiGong_02_App(void)
{
	int32_t data = 0;
	if(Receive_succeed_1 == 1)
		{
			data = inputFunction(&Command_1[1]);
			SwitchFunction(data);
			Receive_succeed_1 = 0;
		}else {
			/*状态指示灯*/
			LED_Green(OFF);
			LED_Yellow(ON);
			LED_Red(OFF);
		}
		delay_ms(100);
}
/***************************************************
 *函数名称：switchFunction
 *说明：switch分支选择函数
 *输入：data 上一次的结果  
 *输出：本次计算结果
****************************************************/
static void SwitchFunction(int32_t data)
{
	int32_t user_data = data;
	char iic_data[40];
	int i=3;
	u8 xunhuan_count = Command_1[5];

	/*转换数据*/
#ifdef LEFT_MODEL
	sprintf(iic_data,"S1TurnLeft%04d",user_data);
#endif
#ifdef RIGHT_MODEL
	sprintf(iic_data,"S1TurnRight%04d",user_data);
#endif
#ifdef FRONT_MODEL
	sprintf(iic_data,"S1TurnFront%04d",user_data);
#endif
#ifdef BACK_MODEL
	sprintf(iic_data,"S1TurnBack%04d",user_data);
#endif
	
	/*输出结果*/
	outputFunction(user_data,xunhuan_count,1);
	Single_Write(I2C1_SlaveAddr,iic_data,15);
	
	/*状态指示灯*/
	LED_Green(ON);
	LED_Yellow(OFF);
	LED_Red(OFF);
	delay_ms(500);
}
