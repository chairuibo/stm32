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
 *函数名称：input_1_Function
 *说明：普通函数
 *输入：data 需要输出的数据  
 *输出：本次计算结果
****************************************************/
int32_t inputFunction(uint8_t data[4])
{
	union SendData receive_data;
	/*收到数据*/
	receive_data.transform_data2[0] = data[0];
	receive_data.transform_data2[1] = data[1];
	receive_data.transform_data2[2] = data[2];
	receive_data.transform_data2[3] = data[3];

	return receive_data.transform_data1;
}

/***************************************************
 *函数名称：output_1_Function
 *说明：普通函数
 *输入：data 需要输出的数据  
 *输出：本次计算结果
****************************************************/
int32_t outputFunction(int32_t data,u8 count,u8 Exit)
{
	/*输出结果*/
	uint8_t will_send_data[7] = {'#',1,2,3,4,0,'!'};
	uint8_t *p = will_send_data;
	union SendData user_data;
	
	/*数据转换*/
	user_data.transform_data1 = data;
	will_send_data[1] = user_data.transform_data2[0];
	will_send_data[2] = user_data.transform_data2[1];
	will_send_data[3] = user_data.transform_data2[2];
	will_send_data[4] = user_data.transform_data2[3];
	will_send_data[5] =count;
	/*发送数据*/
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
 *函数名称：normalFunction
 *说明：普通函数
 *输入：data 上一次的数据  
 *输出：本次计算结果
****************************************************/
int32_t normalFunction(int32_t data)
{
	outputFunction(data,0,1);
	/*输出结果*/
	/*待写*/	
	return 1;
}
#endif

#ifdef _SHOWFunction
/***************************************************
 *函数名称：showFunction
 *说明：显示函数
 *输入：data 需要显示的数据  
 *输出：本次计算结果
****************************************************/
int32_t showFunction(int32_t data)
{
	int32_t user_data = data;
	
	OLED_Clear();
	/*显示结果*/
	OLED_ShowCHinese(16*2,1,29);
	OLED_ShowCHinese(16*3,1,30);
	OLED_ShowCHinese(16*4,1,3);
	OLED_ShowNum(42,3,user_data,5,16);
	return 1;
}
#endif

#ifdef _STARTFunction
/***************************************************
 *函数名称：startFunction
 *说明：开始函数
 *输入：IsStart是否开始指令  
 *输出：本次计算结果
****************************************************/
int32_t startFunction(int32_t IsStart)
{
	int32_t user_IsStart =  IsStart;
	int32_t data = 666;
	if(user_IsStart){
		/*输出结果*/
		outputFunction(data,0,1);	
		/*状态指示灯*/
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
 *函数名称：dataFunction
 *说明：数据函数
 *输入：data 需要输出的数据  
 *输出：成功与否
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
	
	/*转换数据*/
	sprintf(iic_data,"S1%04d",user_data);
	/*输出结果*/
	i = Command_1[5];
	outputFunction(user_data,i,1);
	Single_Write(I2C1_SlaveAddr,iic_data,5);
	
	/*显示结果*/
	OLED_ShowCHinese(16*0,6,31);
	OLED_ShowCHinese(16*1,6,32);
	OLED_ShowCHinese(16*2,6,29);
	OLED_ShowCHinese(16*3,6,30);
	OLED_ShowCHinese(16*4,6,3);
	OLED_ShowNum(16*5,6,user_data,4,16);
	
	/*状态指示灯*/
	LED_Green(ON);
	LED_Yellow(OFF);
	LED_Red(OFF);
	
	return 1;	
}
#endif

#ifdef _CALCULATEFunction
/***************************************************
 *函数名称：calculate_OLEDShow_Function
 *说明：运算选择显示函数
 *输入：picture 所在的画面
		command 增减指令
 *输出：本次计算结果
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
	/*状态指示灯*/
	LED_Green(OFF);
	LED_Yellow(ON);
	LED_Red(OFF);
//	OLED_ShowNum(16*6,6,command,1,16);
	return 1;
}
/***************************************************
 *函数名称：calculateFunction
 *说明：运算函数
 *输入：data1 上一次的数据
		data2 第二个数据
		falg  运算符号
 *输出：本次计算结果
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
	/*显示数字*/	
	OLED_ShowNum(16*0,0,user_data1,4,16);
	OLED_ShowNum(16*0,4,user_data2,4,16);
	/*计算结果并显示符号*/
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

	/*转换数据*/
	if(user_flag <= 5)
		sprintf(iic_data,"J1%d%c%d=%d",user_data1,symbol,user_data2,user_results);
	else 
		sprintf(iic_data,"J1%d%c=%d=%d",user_data1,symbol,user_data2,user_results);
	/*输出结果*/
	count = Command_1[5];
	outputFunction(user_results,count,1);
	Single_Write(I2C1_SlaveAddr,iic_data,20);
	
	
	/*显示结果*/
	OLED_ShowChar(16*0,6,'=',16);
	if(user_flag < 4)		//四则运算结果显示
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
		}else{			//逻辑运算结果显示
			if(user_results == 0 ) OLED_ShowChar(16*7,6,'F',16);
				else OLED_ShowChar(16*7,6,'T',16);
		}
	/*状态指示灯*/
	LED_Green(ON);
	LED_Yellow(OFF);
	LED_Red(OFF);
	return user_results;
}
#endif

#ifdef _IFFunction
/***************************************************
 *函数名称：ifFunction
 *说明：循环函数
 *输入：data 上一次的数据  
 *  	TorF 判断执行正确或错误的结果
 *输出：本次计算结果
****************************************************/
int32_t ifFunction(int32_t data,uint8_t flag)
{
	uint8_t user_flag = flag;
	int32_t user_data = data;
	u8 count = Command_1[5];
	if(user_flag){
	/*正确的输出结果*/
		outputFunction(user_data,count,1);
	}else {
		/*错误的输出结果*/
		outputFunction(user_data,count,2);
	}
	/*状态指示灯*/
	LED_Green(ON);
	LED_Yellow(OFF);
	LED_Red(OFF);
	delay_ms(500);
	return 0;
}
#endif

#ifdef _SWITCHFunction
/***************************************************
 *函数名称：switchFunction
 *说明：switch分支选择函数
 *输入：data 上一次的结果  
 *输出：本次计算结果
****************************************************/
int32_t switchFunction(int32_t data)
{
	int32_t user_data = data;
	u8 count = Command_1[5];
	
	/*输出结果*/
	outputFunction(data,count,1);
	/*状态指示灯*/
	LED_Green(ON);
	LED_Yellow(OFF);
	LED_Red(OFF);
	delay_ms(500);
	/*单独测试 需要显示模块
	OLED_ShowCHinese(16*0,2,22);//"选",22
	OLED_ShowCHinese(16*1,2,23);//"择",23
	OLED_ShowCHinese(16*2,2,29);//"结",29
	OLED_ShowCHinese(16*3,2,30);//"果",30
	OLED_ShowCHinese(16*4,2,3);
	OLED_ShowNum(16*5,4,user_data,4,16);*/
	return user_data;
}
#endif

#ifdef _CASEFunction
/***************************************************
 *函数名称：caseFunction
 *说明：循环函数
 *输入：index 需要执行的分支程序 
 *输出：本次计算结果
****************************************************/
int32_t caseFunction(int32_t index,int32_t own_index)
{
	uint16_t request_index = index;
	uint16_t my_index = own_index;
	int32_t user_data = (request_index == my_index);
	u8 count = Command_1[5];
	
	if(user_data){	
		/*运行此分支的程序*/
		outputFunction(request_index,count,2);
		/*状态指示灯*/
		LED_Green(ON);
		LED_Yellow(OFF);
		LED_Red(OFF);
		/*单独测试使用  需要显示模块
		OLED_ShowString(16*0,0,"(^-^) req_num",16);
		OLED_ShowNum(16*5,2,request_index,4,16);
		OLED_ShowString(16*0,4,"(^-^) own_num",16);
		OLED_ShowNum(16*5,6,own_index,4,16);*/
		
		return 1;
	}else {
		/*将序列号输送给下一个case模块*/
		outputFunction(my_index,count,1);
		/*状态指示灯*/
		LED_Green(OFF);
		LED_Yellow(ON);
		LED_Red(OFF);
		/*单独测试使用  需要显示模块
		OLED_ShowString(16*0,0,"X request_num",16);
		OLED_ShowNum(16*5,2,request_index,4,16);
		OLED_ShowString(16*0,4,"X own_num",16);
		OLED_ShowNum(16*5,6,own_index,4,16);*/
		return 0;
	}
	delay_ms(500);
}
#endif
