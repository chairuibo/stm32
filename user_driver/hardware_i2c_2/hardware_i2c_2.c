#include "hardware_i2c_2.h"
#include "oled.h"
#define I2C2_OWN_ADDRESS7  0xA0
#define I2C_SPEED    10000

void I2C_2_Config(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure; 
  I2C_InitTypeDef   I2C_InitStructure; 
	
  I2C_DeInit(I2C2);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2,ENABLE);  
	
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_10 | GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;	  
  GPIO_Init(GPIOB, &GPIO_InitStructure);    
	
  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
  I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
  I2C_InitStructure.I2C_OwnAddress1 =I2C2_OWN_ADDRESS7; 
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_InitStructure.I2C_ClockSpeed =I2C_SPEED;
   
  I2C_Cmd(I2C2,ENABLE);
  I2C_Init(I2C2, &I2C_InitStructure);
 // I2C_ITConfig(I2C2, I2C_IT_BUF | I2C_IT_EVT, ENABLE);
  I2C_GeneralCallCmd(I2C2,ENABLE);
  I2C_AcknowledgeConfig(I2C2,ENABLE);
}

void Single_Write(uint8_t SlaveAddress,uint8_t* pBuffer, uint32_t NumByteToWrite)
{
	vu16 SR1_Tmp = 0;
	u32 Event;
	
	while(I2C_GetFlagStatus(I2C2,I2C_FLAG_BUSY));
	OLED_ShowNum(16*1,6,1,1,16);
	I2C_GenerateSTART(I2C2, ENABLE);
	OLED_ShowNum(16*2,6,2,1,16);
	Event = I2C_GetLastEvent(I2C2);
	OLED_ShowNum(16*1,0,Event,8,16);
	while(I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT))
	{
		Event = I2C_GetLastEvent(I2C2);
		OLED_ShowNum(16*1,1,Event,8,16);
//		I2C_Send7bitAddress(I2C2, SlaveAddress, I2C_Direction_Transmitter);
//		SR1_Tmp = I2C_ReadRegister(I2C2, I2C_Register_SR1);
	}
	OLED_ShowNum(16*3,3,3,1,16);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	
	while(NumByteToWrite--){
		I2C_SendData(I2C2,*pBuffer);
		pBuffer++;
		while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	}
	I2C_GenerateSTOP(I2C2, ENABLE);
}
