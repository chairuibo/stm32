#include "hardware_i2c_1.h"
#define I2C1_OWN_ADDRESS7  0XA0
#define I2C_SPEED    100000
void I2C_1_Config(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure; 
	I2C_InitTypeDef   I2C_InitStructure; 
	
	I2C_DeInit(I2C1);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,ENABLE);  
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;	  
	GPIO_Init(GPIOB, &GPIO_InitStructure);    
	
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_OwnAddress1 =I2C1_OWN_ADDRESS7; 
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_ClockSpeed =I2C_SPEED;
	I2C_Init(I2C1, &I2C_InitStructure); 
	I2C_Cmd(I2C1,ENABLE);
}
void I2C_Master_SingleWrite(uint8_t SlaveAddress,uint8_t Reg_Address, uint8_t Data)
{
	I2C_GenerateSTART(I2C1, ENABLE);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
	
	I2C_Send7bitAddress(I2C1, SlaveAddress, I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	
	I2C_SendData(I2C1,Reg_Address);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	I2C_SendData(I2C1,Data);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	I2C_GenerateSTOP(I2C1, ENABLE);
}
void I2C_Master_BufferRead(uint8_t SlaveAddress,uint8_t* pBuffer, uint8_t Reg_Address, uint16_t NumByteToRead)
{
  while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
  I2C_GenerateSTART(I2C1, ENABLE);
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
  I2C_Send7bitAddress(I2C1, SlaveAddress, I2C_Direction_Transmitter);
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
  I2C_Cmd(I2C1, ENABLE);
  I2C_SendData(I2C1,Reg_Address);  
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));  
  I2C_GenerateSTART(I2C1, ENABLE);
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
  I2C_Send7bitAddress(I2C1, SlaveAddress, I2C_Direction_Receiver);
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
  while(NumByteToRead)  
  {
    if(NumByteToRead == 1)
    {
      I2C_AcknowledgeConfig(I2C1, DISABLE);
      I2C_GenerateSTOP(I2C1, ENABLE);
    }
    if(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED))  
    {      
      *pBuffer = I2C_ReceiveData(I2C1);
      pBuffer++; 
      NumByteToRead--;        
    }   
  }
  I2C_AcknowledgeConfig(I2C1, ENABLE);
}
