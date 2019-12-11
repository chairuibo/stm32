/********************************************************************
**��������������Ϊ�ƶ��Ĳ���
**2019-04-12   �޸�iic�����ַ���
**���ߣ�����
********************************************************************/
#include "MiGong.h"

extern uint8_t Command_1[20];
extern u8 Receive_succeed_1;
/***************************************************
 *�������ƣ�MiGong_App
 *˵�����Թ�������Ҫ�Ļ����н�ģ��
 *���룺��
 *�������
****************************************************/
void MiGong_App(void)
{
	static u8 key_value[4] = {'0','0','0','5'},key_value_last[4] = {'0','0','0','5'};
	static int8_t i = 3;
	static u8 ok_key = 0;
	u8 j=0;
	
	if(getUpKeyStatue == SET) And_minu(&key_value[i],1);  	//��
	if(getDownKeyStatue == SET) And_minu(&key_value[i],0);	//��
	if(getLeftKeyStatue == SET) 
	{
		if(++i > 3) i=3;	//��
			/*״ָ̬ʾ��*/
		LED_Green(OFF);
		LED_Yellow(ON);
		LED_Red(OFF);
	}
	if(getRightKeyStatue == SET) 
	{
		if(--i < 0) i=0;	//��
		/*״ָ̬ʾ��*/
		LED_Green(OFF);
		LED_Yellow(ON);
		LED_Red(OFF);
	}
	if(getOKKeyStatue == SET) ok_key = 1;//ok��
	
	OLED_ShowCHinese(16*0,1,31);
	OLED_ShowCHinese(16*1,1,33);
	OLED_ShowCHinese(16*2,1,34);
	OLED_ShowCHinese(16*3,1,35);
	OLED_ShowCHinese(16*4,1,3);
	OLED_ShowChar(16*5,4,key_value[3],16);	//��λ
	OLED_ShowChar(16*4,4,key_value[2],16);	//ʮλ
	OLED_ShowChar(16*3,4,key_value[1],16);	//��λ
	OLED_ShowChar(16*2,4,key_value[0],16);	//ǧλ
	OLED_ShowChar(16*(i+2),6,'*',16);	//���

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
 *�������ƣ�DataFunction
 *˵�������ݺ���
 *���룺data ��Ҫ���������  
 *������ɹ����
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
	
	/*��ʾ���*/
	OLED_ShowCHinese(16*0,6,31);
	OLED_ShowCHinese(16*1,6,32);
	OLED_ShowCHinese(16*2,6,29);
	OLED_ShowCHinese(16*3,6,30);
	OLED_ShowCHinese(16*4,6,3);
	OLED_ShowNum(16*5,6,user_data,4,16);

	
	/*������*/
	i = xunhuan_count;
	outputFunction(user_data,i,1);
	Single_Write(I2C1_SlaveAddr,iic_data,15);

	/*״ָ̬ʾ��*/
	LED_Green(ON);
	LED_Yellow(OFF);
	LED_Red(OFF);
	
	return 1;	
}
/***************************************************
 *�������ƣ�and_minu
 *˵�����жϰ����Ƿ���
 *���룺Exti_flag  �����Ƿ���
		value ��Ӧ�仯��λ
		flag �Ӽ�����
 *�����
****************************************************/
void And_minu(u8* value,u8 x)
{
	switch(x)
	{
		case 0: (*value)--; if(*value < '0') *value = '0'; break;
		case 1: (*value)++; if(*value > '9') *value = '9'; break;
		default : *value = '5';
	}
	/*״ָ̬ʾ��*/
	LED_Green(OFF);
	LED_Yellow(ON);
	LED_Red(OFF);
}
