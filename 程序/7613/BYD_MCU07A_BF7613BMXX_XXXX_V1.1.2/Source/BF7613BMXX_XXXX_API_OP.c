#include "Config.h"


#if	OP_EN
//-----------------------------------------------------------------//
//函数名称： void OP_Init(void)
//函数功能： 降压升压检测初始化
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
void OP_Init(void)
{
	uint rom_offset = 0;
	EA = 0;//关总中断；
	REG_ADDR = 0x24;
	rom_offset = ((uint)REG_DATA)<<8;
	REG_ADDR = 0x23;
	rom_offset |= REG_DATA;
	TRISD |= 0x70;
	OP_OUT_MODE_SET(1);//1:打开OP外部输出;0:关闭OP外部输出,输出到ADC31
	OP_P_VIN_SET(0);//OP同相输入端电压选择，0:1/2VCC; 1:1/3VCC; 2:2/3VCC; 3:内部GND;4/others:外部输入
	OP_FB_SET(1);//OP反馈选择，0:外部反馈; 1:内部反馈
	OP_MODE_SET(OP_MODE);//OP工作模式选择，1:输入共模电压1/2VCC~VCC-1.2V；4:输入共模电压0.1V~1/2VCC；其它保留
	OP_IN_A_SET(2);//OP内部放大倍数选择，0:10倍; 1:15倍；2:20倍；3：25倍；4:30倍；5:35倍；6:40倍；7:45倍；
	OP_PD_SET(0);//OP控制寄存器，0：打开;1:关闭
	
	#if (OP_MODE == 1)
		OP_I_SET(CBYTE[0x83CF-rom_offset]);
	#elif (OP_MODE == 4)
		OP_I_SET(CBYTE[0x83D1-rom_offset]);
	#else
	
	#endif
	EA = 1;//开总中断	   
}
	 
#endif
