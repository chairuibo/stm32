#ifndef _ALLFUNCTIONS_H
#define _ALLFUNCTIONS_H

//#define _SHOWFunction 		
//#define _NORMALFunction			
//#define _STARTFunction			
//#define _DATAFunction			
//#define _CALCULATEFunction		
//#define _IFFunction				
//#define _SWITCHFunction			
//#define _CASEFunction			

#include "stm32f10x.h"


union SendData{
	int32_t transform_data1;
	uint8_t transform_data2[4];
};

int32_t inputFunction(uint8_t data[4]);
int32_t outputFunction(int32_t data,u8 count,u8 Exit);
int32_t normalFunction(int32_t data);
int32_t showFunction(int32_t data);
int32_t startFunction(int32_t IsStart);
int32_t dataFunction(u8 data[4]);
int32_t calculate_OLEDShow_Function(u8 picture,u8 command);
int32_t calculateFunction(int32_t data1, int32_t data2,int8_t flag);
int32_t ifFunction(int32_t data,uint8_t flag);
int32_t switchFunction(int32_t data);
int32_t caseFunction(int32_t index,int32_t own_index);

#endif
