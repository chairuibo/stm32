#include "can1.h"
#include "stm32f10x.h"
#include "stm32f10x_can.h"
#include "usart.h"
#include "key.h"
#include "delay.h"
/********************************************************
**Name:can1_config
**Description: CAN1 Config  funtion
**Input:None
**Output:None
********************************************************/
void can1_config(void)
{
	can1_gpio_config();
	can1_mode_config();
}
/********************************************************
**Name:can1_gpio_config
**Description: CAN1 gpio Config  funtion
**Input:None
**Output:None
********************************************************/
void can1_gpio_config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOB, ENABLE);	                        											 
	
	/* CAN1 Periph clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
	
	/* Configure CAN pin: RX */									               // PB8
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	             // ��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* Configure CAN pin: TX */									               // PB9
	GPIO_InitStructure.GPIO_Pin =	GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		         // �����������
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//#define GPIO_Remap_CAN    GPIO_Remap1_CAN1 ��ʵ��û���õ���ӳ��I/O
	GPIO_PinRemapConfig(GPIO_Remap1_CAN1, ENABLE);
}
/********************************************************
**Name:can1_mode_config
**Description: CAN1 mode Config  funtion
**Input:None
**Output:None
********************************************************/
void can1_mode_config(void)
{
	CAN_InitTypeDef        CAN_InitStructure;
	CAN_FilterInitTypeDef  CAN_FilterInitStructure;
	
	/* CAN register init */
	CAN_DeInit(CAN1);
	CAN_StructInit(&CAN_InitStructure);
	
	/* CAN cell init */
	CAN_InitStructure.CAN_TTCM=DISABLE;						 // ʱ�䴥��ͨ�Ž�ֹ
	CAN_InitStructure.CAN_ABOM=DISABLE;						 // �����˳������ж���λ��0���˳�
	CAN_InitStructure.CAN_AWUM=DISABLE;						 // �Զ�����ģʽ������sleep
	CAN_InitStructure.CAN_NART=DISABLE;						 // �Զ����´��ͱ��ƣ�֪�����ͳɹ�
	CAN_InitStructure.CAN_RFLM=DISABLE;						 // FIFOû���������±��ĸ��Ǿɱ���  
	CAN_InitStructure.CAN_TXFP=DISABLE;						 // ���ͱ������ȼ�ȷ������־��
	CAN_InitStructure.CAN_Mode=CAN_Mode_Normal;	 // �ػ�ģʽ
	CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;				 // 1tq��BS1��BS2��ֵ���������й�
	CAN_InitStructure.CAN_BS1=CAN_BS1_8tq;
	CAN_InitStructure.CAN_BS2=CAN_BS2_7tq;
	CAN_InitStructure.CAN_Prescaler=5;             // ��Ƶϵ��Ϊ5
	CAN_Init(CAN1, &CAN_InitStructure);            // ��ʼ��CAN1 
	
	/* CAN filter init */
	CAN_FilterInitStructure.CAN_FilterNumber=0;
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;
	CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;
	CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=0;
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;
	CAN_FilterInit(&CAN_FilterInitStructure);
	
	CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);
}
/********************************************************
**Name:can1_SendData
**Description: CAN1 send data  funtion
**Input:None
**Output:None
********************************************************/
void can1_SendData(u8 data[8])
{
	CanTxMsg TxMessage;
	uint8_t TXMessage_Staute = 0;
	u16 i=0;
	
	/* transmit */
	TxMessage.StdId=0x1;			// �趨��׼��ʶ����11λ����չ��Ϊ29λ��
	TxMessage.RTR=CAN_RTR_DATA;		// ������Ϣ��֡����Ϊ����֡������Զ��֡��
	TxMessage.IDE=CAN_ID_STD;		// ��Ϣ��־��ʵ���׼��ʶ��
	TxMessage.DLC=5;					  // ������֡��һ֡8λ
	TxMessage.Data[0]=data[0];			// ��һ֡����
	TxMessage.Data[1]=data[1];			// �ڶ�֡����
	TxMessage.Data[2]=data[2];			// ��һ֡����
	TxMessage.Data[3]=data[3];			// �ڶ�֡����
	TxMessage.Data[4]=data[4];			// ��һ֡����
//	TxMessage.Data[5]=data[5];			// �ڶ�֡����
//	TxMessage.Data[6]=data[6];			// ��һ֡����
//	TxMessage.Data[7]=data[7];			// �ڶ�֡����
	TXMessage_Staute=CAN_Transmit(CAN1, &TxMessage);
	
	while((CAN_TransmitStatus(CAN1, TXMessage_Staute) == CAN_TxStatus_Failed) && (i <=0xfff))
	{
		i++;
	}
//	if(i>=0xfff) 	printf("Tx Send Fail!!!\n");
//	else printf("Tx Send Succeed!!!\n");
	if(i>=0xfff) 	{
		LED_Red(ON);
	}
	else {
		LED_Blue(ON);
	}
	delay_ms(300);
	LED_Blue(OFF);
	LED_Red(OFF);
}
/********************************************************
**Name:USB_LP_CAN1_RX0_IRQHandler
**Description: CAN1 Intrrrupt Config  funtion
**Input:None
**Output:None
********************************************************/
u8 CAN_receive_falg = 0;
extern u8 CAN_receivedata[8];
void USB_LP_CAN1_RX0_IRQHandler(void)
{
	CanRxMsg RxMessage;
	u8 i=0;
	
	printf("Rx Enter!!!\n");
	CAN_receive_falg = 1;
	CAN_Receive(CAN1,CAN_FIFO0,&RxMessage);
	
	for(;i<8;i++)
		CAN_receivedata[i] = RxMessage.Data[i];
}
