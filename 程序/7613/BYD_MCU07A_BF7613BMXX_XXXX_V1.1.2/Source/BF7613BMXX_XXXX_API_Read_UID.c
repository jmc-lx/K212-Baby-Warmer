#include "Config.h"

#if INF_READ_EN
#pragma message "编译,CHIP_UDI_Read相关函数"
/****************************************************************/
//函数名：void CHIP_UDI_Read(void)   
//功  能：读取芯片唯一识别码
//参  数：无
//返回值：无
/****************************************************************/
uchar xdata UID_Buffer[16] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
void CHIP_UDI_Read(void)  
{
	uint rom_offset = 0;
	uchar i = 0;
	EA = 0;
	REG_ADDR = 0x24;
	rom_offset = ((uint)REG_DATA)<<8;
	REG_ADDR = 0x23;
	rom_offset |= REG_DATA;
	for(i = 0; i < 16; i++)
	{
		UID_Buffer[i] = CBYTE[0x83A8-rom_offset + i];
	}
	EA = 1;
}
#endif	