#include "delay.h"
static __IO u32 TimingDelay;

void SysTick_Init(void)
{
	if (SysTick_Config(SystemCoreClock / 100000))	// ST3.5.0��汾
	{ 
		/* Capture error */ 
		while (1);
	}
		// �رյδ�ʱ��  
	SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
}

void delay_10us(__IO u32 nTime)
{ 
	TimingDelay = nTime;	

	// ʹ�ܵδ�ʱ��  
	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;
    
	while(TimingDelay != 0);
    
    SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
}

void TimingDelay_Decrement(void)
{
	if (TimingDelay != 0x00)
	{ 
		TimingDelay--;
	}
}
/*********************************************END OF FILE**********************/
