/********************************************************************
**������һ��ģ���������Ϊ�ƶ��Ĳ���
**2019-04-12   �����ĵ�
**���ߣ�����
********************************************************************/
#include "MiGong_02.h"

extern uint8_t Command_1[20];
extern u8 Receive_succeed_1;
/***************************************************
 *�������ƣ�MiGong_App
 *˵�����Թ�������Ҫ�Ļ����н�ģ��
 *���룺��
 *�������
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
			/*״ָ̬ʾ��*/
			LED_Green(OFF);
			LED_Yellow(ON);
			LED_Red(OFF);
		}
		delay_ms(100);
}
/***************************************************
 *�������ƣ�switchFunction
 *˵����switch��֧ѡ����
 *���룺data ��һ�εĽ��  
 *��������μ�����
****************************************************/
static void SwitchFunction(int32_t data)
{
	int32_t user_data = data;
	char iic_data[40];
	int i=3;
	u8 xunhuan_count = Command_1[5];

	/*ת������*/
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
	
	/*������*/
	outputFunction(user_data,xunhuan_count,1);
	Single_Write(I2C1_SlaveAddr,iic_data,15);
	
	/*״ָ̬ʾ��*/
	LED_Green(ON);
	LED_Yellow(OFF);
	LED_Red(OFF);
	delay_ms(500);
}
