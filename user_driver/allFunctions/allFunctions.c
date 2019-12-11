#include "stm32f10x.h"
#include "allFunctions.h"
#include "usart2.h"
#include "usart.h"
#include "oled.h"
#include "key.h"
#include "iic_driver.h"
#include "stdio.h"

extern uint8_t Command_1[20];
extern uint8_t Command_2[20];

/***************************************************
 *�������ƣ�input_1_Function
 *˵������ͨ����
 *���룺data ��Ҫ���������  
 *��������μ�����
****************************************************/
int32_t inputFunction(uint8_t data[4])
{
	union SendData receive_data;
	/*�յ�����*/
	receive_data.transform_data2[0] = data[0];
	receive_data.transform_data2[1] = data[1];
	receive_data.transform_data2[2] = data[2];
	receive_data.transform_data2[3] = data[3];

	return receive_data.transform_data1;
}

/***************************************************
 *�������ƣ�output_1_Function
 *˵������ͨ����
 *���룺data ��Ҫ���������  
 *��������μ�����
****************************************************/
int32_t outputFunction(int32_t data,u8 count,u8 Exit)
{
	/*������*/
	uint8_t will_send_data[7] = {'#',1,2,3,4,0,'!'};
	uint8_t *p = will_send_data;
	union SendData user_data;
	
	/*����ת��*/
	user_data.transform_data1 = data;
	will_send_data[1] = user_data.transform_data2[0];
	will_send_data[2] = user_data.transform_data2[1];
	will_send_data[3] = user_data.transform_data2[2];
	will_send_data[4] = user_data.transform_data2[3];
	will_send_data[5] =count;
	/*��������*/
	switch(Exit)
	{
		case 1:usart1_SendData(p,7);break;
		case 2:usart2_SendData(p,7);break;
		default :return 0;
	}
	return 1;
}

#ifdef _NORMALFunction
/***************************************************
 *�������ƣ�normalFunction
 *˵������ͨ����
 *���룺data ��һ�ε�����  
 *��������μ�����
****************************************************/
int32_t normalFunction(int32_t data)
{
	outputFunction(data,0,1);
	/*������*/
	/*��д*/	
	return 1;
}
#endif

#ifdef _SHOWFunction
/***************************************************
 *�������ƣ�showFunction
 *˵������ʾ����
 *���룺data ��Ҫ��ʾ������  
 *��������μ�����
****************************************************/
int32_t showFunction(int32_t data)
{
	int32_t user_data = data;
	
	OLED_Clear();
	/*��ʾ���*/
	OLED_ShowCHinese(16*2,1,29);
	OLED_ShowCHinese(16*3,1,30);
	OLED_ShowCHinese(16*4,1,3);
	OLED_ShowNum(42,3,user_data,5,16);
	return 1;
}
#endif

#ifdef _STARTFunction
/***************************************************
 *�������ƣ�startFunction
 *˵������ʼ����
 *���룺IsStart�Ƿ�ʼָ��  
 *��������μ�����
****************************************************/
int32_t startFunction(int32_t IsStart)
{
	int32_t user_IsStart =  IsStart;
	int32_t data = 666;
	if(user_IsStart){
		/*������*/
		outputFunction(data,0,1);	
		/*״ָ̬ʾ��*/
		LED_Green(ON);
		LED_Yellow(OFF);
		LED_Red(OFF);
		return 1;
	}else{
		return 0;
	}
}
#endif

#ifdef _DATAFunction
/***************************************************
 *�������ƣ�dataFunction
 *˵�������ݺ���
 *���룺data ��Ҫ���������  
 *������ɹ����
****************************************************/
int32_t dataFunction(u8 data[4])
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
	sprintf(iic_data,"S1%04d",user_data);
	/*������*/
	i = Command_1[5];
	outputFunction(user_data,i,1);
	Single_Write(I2C1_SlaveAddr,iic_data,5);
	
	/*��ʾ���*/
	OLED_ShowCHinese(16*0,6,31);
	OLED_ShowCHinese(16*1,6,32);
	OLED_ShowCHinese(16*2,6,29);
	OLED_ShowCHinese(16*3,6,30);
	OLED_ShowCHinese(16*4,6,3);
	OLED_ShowNum(16*5,6,user_data,4,16);
	
	/*״ָ̬ʾ��*/
	LED_Green(ON);
	LED_Yellow(OFF);
	LED_Red(OFF);
	
	return 1;	
}
#endif

#ifdef _CALCULATEFunction
/***************************************************
 *�������ƣ�calculate_OLEDShow_Function
 *˵��������ѡ����ʾ����
 *���룺picture ���ڵĻ���
		command ����ָ��
 *��������μ�����
****************************************************/
int32_t calculate_OLEDShow_Function(u8 picture,u8 command)
{
	u8 x = command / 4;
	u8 y = (command % 4) * 2;
	
	if(picture == 0){
		OLED_Clear();
		OLED_ShowChar(16*1,0,'+',16);
		OLED_ShowChar(16*1,2,'-',16);
		OLED_ShowChar(16*1,4,'x',16);
		OLED_ShowChar(16*1,6,'/',16);
		OLED_ShowChar(16*4,0,'>',16);
		OLED_ShowChar(16*4,2,'<',16);
		OLED_ShowString(16*4,4,">=",16);//OLED_ShowChar(16*5,8*2,'>',16);OLED_ShowChar(16*6,8*4,'=',16);
		OLED_ShowString(16*4,6,"<=",16);//OLED_ShowChar(16*5,8*3,'<',16);OLED_ShowChar(16*6,8*4,'=',16);
		OLED_ShowString(16*7,0,"==",16);//OLED_ShowChar(16*1,8*4,'=',16);OLED_ShowChar(16*2,8*4,'=',16);
		OLED_ShowString(16*7,2,"!=",16);//OLED_ShowChar(16*5,8*4,'!',16);OLED_ShowChar(16*6,8*4,'=',16);
	}

	OLED_ShowChar(16*x*3,y,'*',16);
	/*״ָ̬ʾ��*/
	LED_Green(OFF);
	LED_Yellow(ON);
	LED_Red(OFF);
//	OLED_ShowNum(16*6,6,command,1,16);
	return 1;
}
/***************************************************
 *�������ƣ�calculateFunction
 *˵�������㺯��
 *���룺data1 ��һ�ε�����
		data2 �ڶ�������
		falg  �������
 *��������μ�����
****************************************************/
int32_t calculateFunction(int32_t data1, int32_t data2,int8_t flag)
{
	int32_t user_data1 = data1;
	int32_t user_data2 = data2;
	int8_t user_flag = flag;
	int32_t user_results = 0;
	char iic_data[40],symbol = '+';
	u8 count;
	int i=2,j=0;
	
	OLED_Clear();
	/*��ʾ����*/	
	OLED_ShowNum(16*0,0,user_data1,4,16);
	OLED_ShowNum(16*0,4,user_data2,4,16);
	/*����������ʾ����*/
	switch(user_flag){
		case 0:user_results = user_data1 + user_data2; 	OLED_ShowChar(16*0,2,'+',16); symbol = '+'; break;		// +
		case 1:user_results = user_data1 - user_data2;	OLED_ShowChar(16*0,2,'-',16); symbol = '-'; break;		// -
		case 2:user_results = user_data1 * user_data2; 	OLED_ShowChar(16*0,2,'x',16); symbol = '*'; break;		// *
		case 3:user_results = user_data1 / user_data2; 	OLED_ShowChar(16*0,2,'/',16); symbol = '/'; break;		// /
		case 4:user_results = user_data1 > user_data2; 	OLED_ShowChar(16*0,2,'>',16); symbol = '>'; break;		// >
		case 5:user_results = user_data1 < user_data2; 	OLED_ShowChar(16*0,2,'<',16); symbol = '<'; break;		// <
		case 6:user_results = user_data1 >= user_data2;	OLED_ShowString(16*0,2,">=",16); symbol = '>';break;		// >=
		case 7:user_results = user_data1 <= user_data2;	OLED_ShowString(16*0,2,"<=",16); symbol = '=';break;		// <=
		case 8:user_results = user_data1 == user_data2;	OLED_ShowString(16*0,2,"==",16); symbol = '=';break;		// == 
		case 9:user_results = user_data1 != user_data2;	OLED_ShowString(16*0,2,"!=",16); symbol = '!';break;		// !=
		default:break;
	}

	/*ת������*/
	if(user_flag <= 5)
		sprintf(iic_data,"J1%d%c%d=%d",user_data1,symbol,user_data2,user_results);
	else 
		sprintf(iic_data,"J1%d%c=%d=%d",user_data1,symbol,user_data2,user_results);
	/*������*/
	count = Command_1[5];
	outputFunction(user_results,count,1);
	Single_Write(I2C1_SlaveAddr,iic_data,20);
	
	
	/*��ʾ���*/
	OLED_ShowChar(16*0,6,'=',16);
	if(user_flag < 4)		//������������ʾ
	{
		if(user_results >= 0 )	OLED_ShowNum(16*3,6,user_results,8,16);
			else {
				j = -user_results;
				while(j){
					i++;
					j = j/10;
				}
				if(i<4) i=4;
				OLED_ShowNum(16*3,6,-user_results,8,16);
				OLED_ShowChar(8*(15-i),6,'-',16);	
			}
		}else{			//�߼���������ʾ
			if(user_results == 0 ) OLED_ShowChar(16*7,6,'F',16);
				else OLED_ShowChar(16*7,6,'T',16);
		}
	/*״ָ̬ʾ��*/
	LED_Green(ON);
	LED_Yellow(OFF);
	LED_Red(OFF);
	return user_results;
}
#endif

#ifdef _IFFunction
/***************************************************
 *�������ƣ�ifFunction
 *˵����ѭ������
 *���룺data ��һ�ε�����  
 *  	TorF �ж�ִ����ȷ�����Ľ��
 *��������μ�����
****************************************************/
int32_t ifFunction(int32_t data,uint8_t flag)
{
	uint8_t user_flag = flag;
	int32_t user_data = data;
	u8 count = Command_1[5];
	if(user_flag){
	/*��ȷ��������*/
		outputFunction(user_data,count,1);
	}else {
		/*�����������*/
		outputFunction(user_data,count,2);
	}
	/*״ָ̬ʾ��*/
	LED_Green(ON);
	LED_Yellow(OFF);
	LED_Red(OFF);
	delay_ms(500);
	return 0;
}
#endif

#ifdef _SWITCHFunction
/***************************************************
 *�������ƣ�switchFunction
 *˵����switch��֧ѡ����
 *���룺data ��һ�εĽ��  
 *��������μ�����
****************************************************/
int32_t switchFunction(int32_t data)
{
	int32_t user_data = data;
	u8 count = Command_1[5];
	
	/*������*/
	outputFunction(data,count,1);
	/*״ָ̬ʾ��*/
	LED_Green(ON);
	LED_Yellow(OFF);
	LED_Red(OFF);
	delay_ms(500);
	/*�������� ��Ҫ��ʾģ��
	OLED_ShowCHinese(16*0,2,22);//"ѡ",22
	OLED_ShowCHinese(16*1,2,23);//"��",23
	OLED_ShowCHinese(16*2,2,29);//"��",29
	OLED_ShowCHinese(16*3,2,30);//"��",30
	OLED_ShowCHinese(16*4,2,3);
	OLED_ShowNum(16*5,4,user_data,4,16);*/
	return user_data;
}
#endif

#ifdef _CASEFunction
/***************************************************
 *�������ƣ�caseFunction
 *˵����ѭ������
 *���룺index ��Ҫִ�еķ�֧���� 
 *��������μ�����
****************************************************/
int32_t caseFunction(int32_t index,int32_t own_index)
{
	uint16_t request_index = index;
	uint16_t my_index = own_index;
	int32_t user_data = (request_index == my_index);
	u8 count = Command_1[5];
	
	if(user_data){	
		/*���д˷�֧�ĳ���*/
		outputFunction(request_index,count,2);
		/*״ָ̬ʾ��*/
		LED_Green(ON);
		LED_Yellow(OFF);
		LED_Red(OFF);
		/*��������ʹ��  ��Ҫ��ʾģ��
		OLED_ShowString(16*0,0,"(^-^) req_num",16);
		OLED_ShowNum(16*5,2,request_index,4,16);
		OLED_ShowString(16*0,4,"(^-^) own_num",16);
		OLED_ShowNum(16*5,6,own_index,4,16);*/
		
		return 1;
	}else {
		/*�����к����͸���һ��caseģ��*/
		outputFunction(my_index,count,1);
		/*״ָ̬ʾ��*/
		LED_Green(OFF);
		LED_Yellow(ON);
		LED_Red(OFF);
		/*��������ʹ��  ��Ҫ��ʾģ��
		OLED_ShowString(16*0,0,"X request_num",16);
		OLED_ShowNum(16*5,2,request_index,4,16);
		OLED_ShowString(16*0,4,"X own_num",16);
		OLED_ShowNum(16*5,6,own_index,4,16);*/
		return 0;
	}
	delay_ms(500);
}
#endif
