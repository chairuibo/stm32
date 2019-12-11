#include "iic_driver.h"
#include "usart.h"
#include <stdio.h>
void i2c_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}
void I2C_delay(void)
{
		
   u8 i=30; 
   while(i) 
   { 
     i--; 
   }  
}
bool I2C_Start(void)
{
	SDA_H;
	SCL_H;
	I2C_delay();
	if(!SDA_read)return false;	
	SDA_L;
	I2C_delay();
	if(SDA_read) return false;	
	SDA_L;
	I2C_delay();
	return true;
}

void I2C_Stop(void)
{
	SCL_L;
	I2C_delay();
	SDA_L;
	I2C_delay();
	SCL_H;
	I2C_delay();
	SDA_H;
	I2C_delay();
} 

void I2C_Ack(void)
{	
	SCL_L;
	I2C_delay();
	SDA_L;
	I2C_delay();
	SCL_H;
	I2C_delay();
	SCL_L;
	I2C_delay();
}   

void I2C_NoAck(void)
{	
	SCL_L;
	I2C_delay();
	SDA_H;
	I2C_delay();
	SCL_H;
	I2C_delay();
	SCL_L;
	I2C_delay();
} 

bool I2C_WaitAck(void) 	 
{
	SCL_L;
	I2C_delay();
	SDA_H;			
	I2C_delay();
	SCL_H;
	I2C_delay();
	if(SDA_read)
	{
      SCL_L;
	 // I2C_delay();
      return false;
	}
	SCL_L;
	//I2C_delay();
	return true;
}

void I2C_SendByte(u8 SendByte) 
{
    u8 i=8;
    while(i--)
    {
        SCL_L;
        I2C_delay();
      if(SendByte&0x80)
        SDA_H;  
      else 
        SDA_L;   
        SendByte<<=1;
        I2C_delay();
		SCL_H;
        I2C_delay();
    }
    SCL_L;
}  

uint8_t I2C_ReadByte(void)  
{ 
    u8 i=8;
    u8 ReceiveByte=0;

    SDA_H;				
    while(i--)
    {
      ReceiveByte<<=1;      
      SCL_L;
      I2C_delay();
	  SCL_H;
      I2C_delay();	
      if(SDA_read)
      {
        ReceiveByte|=0x01;
      }
    }
    SCL_L;
    return ReceiveByte;
}   

void Single_Write(unsigned char SlaveAddress,unsigned char* REG_Address,unsigned char REG_data)	
{
  	I2C_Start();
    I2C_SendByte(SlaveAddress);   
    I2C_WaitAck();
	while(REG_data--){
		I2C_SendByte(*REG_Address);     
		I2C_WaitAck();	
	}
    I2C_WaitAck();   
    I2C_Stop(); 
}

unsigned char Single_Read(unsigned char SlaveAddress,unsigned char REG_Address)
{   unsigned char REG_data;     	
    I2C_Start();
    I2C_SendByte(SlaveAddress);
    I2C_WaitAck();
    I2C_SendByte((u8) REG_Address);      
    I2C_WaitAck();
    I2C_Start();
    I2C_SendByte(SlaveAddress+1);
    I2C_WaitAck();
    delay_10us(50);
	  REG_data= I2C_ReadByte();
    I2C_Stop();
	return REG_data;
}
