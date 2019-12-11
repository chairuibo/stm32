#include "DAC.h"

void configDACFile(void)
{			
	configDACGPIO();
    configDirectionGPIO();
    configDAC();
}

void configDACGPIO(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(DAC_PortRcc, ENABLE );

	GPIO_InitStructure.GPIO_Pin = DAC_Pin;	
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
 	GPIO_Init(DAC_Port, &GPIO_InitStructure);
    
}

void configDirectionGPIO(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(WheelDirection_PortRcc, ENABLE );

	GPIO_InitStructure.GPIO_Pin = LeftFrontWheelDirection_Pin | LeftBackWheelDirection_Pin | RightFrontWheelDirection_Pin | RightBackWheelDirection_Pin;	
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(WheelDirection_Port, &GPIO_InitStructure);
}

void configDAC(void)
{
    DAC_InitTypeDef DAC_InitType;
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE );  
    
    DAC_InitType.DAC_Trigger=DAC_Trigger_Software;	                    //Do not use the trigger function
	DAC_InitType.DAC_WaveGeneration=DAC_WaveGeneration_None;            //Do not use the waveform
	DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;  //Shielding amplitude Settings
	DAC_InitType.DAC_OutputBuffer=DAC_OutputBuffer_Disable ;	        //Output caching closed
  
	DAC_Init(DAC_Channel_2,&DAC_InitType);	                            //Initialize the DAC channel 2
	
    DAC_Cmd(DAC_Channel_2, ENABLE);                                     //Enable DAC2
	
	DAC_DualSoftwareTriggerCmd(ENABLE);
	
    DAC_SetChannel2Data(DAC_Align_12b_R, 0);                            //12 right aligned data format setting DAC value

}

void setDACValue(u16 value)
{

	DAC_SetChannel2Data(DAC_Align_12b_R,value);
	DAC_SoftwareTriggerCmd(DAC_Channel_2,ENABLE);
}
