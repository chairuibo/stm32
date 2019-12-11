/********************************************************************
**自身输入数据作为移动的步数
**2019-04-12   修改iic发送字符数
**作者：柴锐波
********************************************************************/
#include "MiGong.h"

extern uint8_t Command_1[20];
extern u8 Receive_succeed_1;
/***************************************************
 *函数名称：MiGong_App
 *说明：迷宫任务需要的基本行进模块
 *输入：无
 *输出：无
****************************************************/
void MiGong_App(void)
{
	static u8 key_value[4] = {'0','0','0','5'},key_value_last[4] = {'0','0','0','5'};
	static int8_t i = 3;
	static u8 ok_key = 0;
	u8 j=0;
	
	if(getUpKeyStatue == SET) And_minu(&key_value[i],1);  	//上
	if(getDownKeyStatue == SET) And_minu(&key_value[i],0);	//下
	if(getLeftKeyStatue == SET) 
	{
		if(++i > 3) i=3;	//左
			/*状态指示灯*/
		LED_Green(OFF);
		LED_Yellow(ON);
		LED_Red(OFF);
	}
	if(getRightKeyStatue == SET) 
	{
		if(--i < 0) i=0;	//右
		/*状态指示灯*/
		LED_Green(OFF);
		LED_Yellow(ON);
		LED_Red(OFF);
	}
	if(getOKKeyStatue == SET) ok_key = 1;//ok键
	
	OLED_ShowCHinese(16*0,1,31);
	OLED_ShowCHinese(16*1,1,33);
	OLED_ShowCHinese(16*2,1,34);
	OLED_ShowCHinese(16*3,1,35);
	OLED_ShowCHinese(16*4,1,3);
	OLED_ShowChar(16*5,4,key_value[3],16);	//个位
	OLED_ShowChar(16*4,4,key_value[2],16);	//十位
	OLED_ShowChar(16*3,4,key_value[1],16);	//百位
	OLED_ShowChar(16*2,4,key_value[0],16);	//千位
	OLED_ShowChar(16*(i+2),6,'*',16);	//标记

	if(Receive_succeed_1 && ok_key){
		DataFunction(key_value,Command_1[5]);
		delay_ms(100);
		Receive_succeed_1 = 0;
	}
		
	for(j=0;j<4;j++)
	{
		if(key_value_last[j] != key_value[j]) 
		{
			key_value_last[j] = key_value[j];
			ok_key = 0;
		}
	}
		delay_ms(200);
		OLED_Clear();
}
/***************************************************
 *函数名称：DataFunction
 *说明：数据函数
 *输入：data 需要输出的数据  
 *输出：成功与否
****************************************************/
static int32_t DataFunction(u8 data[4],u8 xunhuan_count)
{
	int32_t user_data = 0;
	char iic_data[40];
	int i=0;
	
	for(;i<4;i++)
	{
		user_data *= 10; 
		user_data += (data[i] - '0');
	}

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
	
	/*显示结果*/
	OLED_ShowCHinese(16*0,6,31);
	OLED_ShowCHinese(16*1,6,32);
	OLED_ShowCHinese(16*2,6,29);
	OLED_ShowCHinese(16*3,6,30);
	OLED_ShowCHinese(16*4,6,3);
	OLED_ShowNum(16*5,6,user_data,4,16);

	
	/*输出结果*/
	i = xunhuan_count;
	outputFunction(user_data,i,1);
	Single_Write(I2C1_SlaveAddr,iic_data,15);

	/*状态指示灯*/
	LED_Green(ON);
	LED_Yellow(OFF);
	LED_Red(OFF);
	
	return 1;	
}
/***************************************************
 *函数名称：and_minu
 *说明：判断按键是否按下
 *输入：Exti_flag  按键是否按下
		value 对应变化的位
		flag 加减符号
 *输出：
****************************************************/
void And_minu(u8* value,u8 x)
{
	switch(x)
	{
		case 0: (*value)--; if(*value < '0') *value = '0'; break;
		case 1: (*value)++; if(*value > '9') *value = '9'; break;
		default : *value = '5';
	}
	/*状态指示灯*/
	LED_Green(OFF);
	LED_Yellow(ON);
	LED_Red(OFF);
}
