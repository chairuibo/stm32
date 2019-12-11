#include "ADC.h"
#include "Usart.h"
#include "misc.h"
#include "delay.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_dma.h"

__IO uint16_t ADC_ConvertedValue;
int16_t ADC_value = 0;

/*****************************************
**函数名：configADCFile
**功能：ADC配置函数
**输出：无
**输入：无
******************************************/
void configADCFile(void)
{
//    configADCNVIC();
    configADCGPIO();
    configADC();
}
/*****************************************
**函数名：configADCGPIO
**功能：ADC相关引脚配置
**输出：无
**输入：无
******************************************/
void configADCGPIO(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(POSADC_PortRcc , ENABLE );
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6); 
	
	GPIO_InitStructure.GPIO_Pin = POSADC_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入
	GPIO_Init(POSADC_Port, &GPIO_InitStructure);	
		
}
/*****************************************
**函数名：configADCGPIO
**功能：ADC模式配置
**输出：无
**输入：无
******************************************/
void configADC(void)
{
    ADC_InitTypeDef ADC_InitStructure; 
    DMA_InitTypeDef dma;
    
    RCC_APB2PeriphClockCmd(ADC_RCC , ENABLE );	
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    DMA_DeInit(DMA1_Channel1);
    dma.DMA_PeripheralBaseAddr  = ((u32)0x40012400 + 0x4c);     //DMA????????
    dma.DMA_MemoryBaseAddr      = (u32)(&ADC_value);       //???????
    dma.DMA_DIR                 = DMA_DIR_PeripheralSRC;//DMA??????SRC??,????????
    dma.DMA_M2M                 = DMA_M2M_Disable;      //M2M????
    dma.DMA_PeripheralDataSize  = DMA_PeripheralDataSize_HalfWord;//?????????16?
    dma.DMA_MemoryDataSize      = DMA_MemoryDataSize_HalfWord;  //DMA??????,HalfWord???16?    
    dma.DMA_BufferSize          = 1;                       //DMA????CH_NUM?
    dma.DMA_MemoryInc           = DMA_MemoryInc_Disable;         //???????,????????
    dma.DMA_PeripheralInc       = DMA_PeripheralInc_Disable;    //???????,????????
    dma.DMA_Mode                = DMA_Mode_Circular;            //????,???????
    dma.DMA_Priority            = DMA_Priority_High;            //DMA????
    DMA_Init(DMA1_Channel1,&dma);
    DMA_Cmd(DMA1_Channel1,ENABLE);
    
    ADC_DeInit(ADC1);
    
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = 1;
	ADC_Init(ADC1, &ADC_InitStructure);
    
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_7Cycles5 ); 	

//	ADC_ITConfig(ADC1, ADC_IT_EOC,ENABLE);
	ADC_Cmd(ADC1, ENABLE);
    ADC_DMACmd(ADC1 , ENABLE);			//ADC转换完成之后自动用DMA传输到ADC——value
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);

	//校准
	ADC_ResetCalibration(ADC1);  
	while(ADC_GetResetCalibrationStatus(ADC1));
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1));
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}
/*****************************************
**函数名：configADCNVIC
**功能：ADC中断配置
**输出：无
**输入：无
******************************************/
void configADCNVIC(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    
    NVIC_InitStructure.NVIC_IRQChannel = ADC1_2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_Init(&NVIC_InitStructure);
}
/*****************************************
**函数名：ADC1_2_IRQHandler
**功能：ADC中断函数
**输出：无
**输入：无
******************************************/
void ADC1_2_IRQHandler(void)
{
    if(ADC_GetITStatus(ADC1,ADC_IT_EOC) == SET)
    {
        printf("ADC Vakue: %d",ADC_value);
    }
}


