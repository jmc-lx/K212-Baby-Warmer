#include "Config.h"


//-----------------------------------------------------------------//
//函数名称： void ExtInt0_Init(uchar TriggerMode)
//函数功能： 外部中断0初始化
//输入参数：
//外部中断0触发方式选择，uchar TriggerMode
//			 TriggerMode = 0，触发方式为下降沿触发
//			 TriggerMode = 1，触发方式为上升沿触发
//			 TriggerMode = 2，触发方式为双边沿触发 
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------// 
#if ExtInt0_EN
#pragma message "编译，void ExtInt0_Init(uchar TriggerMode)函数"
void ExtInt0_Init(uchar TriggerMode)
{

	EA = 0;//关总中断；

	INT0_FUN_SET(1)//0选择为IO口功能，1选择为INT中断功能
	INT0_IP_SET;//设置IN0中断优级为高
	INT0_INT_FLAG_CLR;//清除INT0中断标志，根据实际应运设置优先级
	
	switch(TriggerMode)
	{
		case 0:	
								
			EXT_INT_CON |= 0X01;	//设置为下降沿触发 
			
		break;

		case 1:						
			EXT_INT_CON &= ~0X01;	
			EXT_INT_CON |= 0X02;  	//设置为上升沿触发
		break;
							 
		case 2:						
			EXT_INT_CON |= 0X03;	//设置为双边沿触发
		
		break;
							

		default:
			EXT_INT_CON |= 0X01;	//设置为下降沿触发
		break;	
	}
	INT0_IE_SET;//使能外部INT0中断 
	EA = 1;//开总中断	
}
//-----------------------------------------------------------------//
//函数名称： void Ext0_ISR() interrupt 0
//函数功能： 外部中断0中断子函数
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------// 
void Ext0_ISR() interrupt 0 
{
	static uchar xdata addr_bak = 0;
	PUSH_REG_ADDR_SFR();
	INT0_INT_FLAG_CLR;//清除INT0中断标志
	POP_REG_ADDR_SFR();
} 
#endif

//-----------------------------------------------------------------//
//函数名称： void ExtInt1_Init(uchar TriggerMode)
//函数功能： 外部中断1初始化
//输入参数： 
//外部中断1触发方式选择，uchar TriggerMode
//			 TriggerMode = 0，触发方式为下降沿触发
//			 TriggerMode = 1，触发方式为上升沿触发
//			 TriggerMode = 2，触发方式为双边沿触发 
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------// 
#if ExtInt1_EN
#pragma message "编译，void ExtInt1_Init(uchar TriggerMode)函数"
void ExtInt1_Init(uchar TriggerMode)
{
	EA = 0;//关总中断；
	INT1_FUN_SET(1)//0选择为IO口功能，1选择为INT中断功能
	INT1_INT_FLAG_CLR;//清除INT1中断标志
	INT1_IP_SET;//设置INT1中断优级为高，根据实际应运设置优先级
	switch(TriggerMode)
	{
		case 0:	
								
			EXT_INT_CON |= 0X04;	//设置为下降沿触发 
			
		break;

		case 1:						
			EXT_INT_CON &= ~0X04;	
			EXT_INT_CON |= 0X08;  	//设置为上升沿触发
		break;
							 
		case 2:						
			EXT_INT_CON |= 0X0C;	//设置为双边沿触发
		
		break;
							

		default:
			EXT_INT_CON |= 0X04;	//设置为下降沿触发
		break;	
	}
	INT1_IE_SET;//使能外部INT1中断 
	EA = 1;//开总中断	
}
//-----------------------------------------------------------------//
//函数名称： void Ext1_ISR() interrupt 2
//函数功能： 外部中断1中断子函数
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------// 
void Ext1_ISR() interrupt 2 
{
	static uchar xdata addr_bak = 0;
	PUSH_REG_ADDR_SFR();
	INT1_INT_FLAG_CLR;//清除INT1中断标志
	POP_REG_ADDR_SFR();
	
}
#endif


//-----------------------------------------------------------------//
//函数名称： void ExtInt2_Init(uchar TriggerMode)
//函数功能： 外部中断2初始化
//输入参数： 
//外部中断1触发方式选择，uchar TriggerMode
//			 TriggerMode = 0，触发方式为下降沿触发
//			 TriggerMode = 1，触发方式为上升沿触发
//			 TriggerMode = 2，触发方式为双边沿触发
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------// 
#if ExtInt2_EN
#pragma message "编译，void ExtInt2_Init(uchar TriggerMode)函数"
void ExtInt2_Init(uchar TriggerMode)
{
	EA = 0;//关总中断；
	INT2_FUN_SET(1)//0选择为IO口功能，1选择为INT中断功能
	INT2_INT_FLAG_CLR;//清除INT2中断标志
	INT2_IP_SET;//设置INT2中断优级为高，根据实际应运设置优先级
	switch(TriggerMode)
	{
		case 0:	
								
			EXT_INT_CON |= 0X10;	//设置为下降沿触发 
			
		break;

		case 1:						
			EXT_INT_CON &= ~0X10;	
			EXT_INT_CON |= 0X20;  	//设置为上升沿触发
		break;
							 
		case 2:						
			EXT_INT_CON |= 0X30;	//设置为双边沿触发
		
		break;
							

		default:
			EXT_INT_CON |= 0X10;	//设置为下降沿触发
		break;	
	}
	INT2_IE_SET;//使能外部INT2中断 
	EA = 1;//开总中断	
}
//-----------------------------------------------------------------//
//函数名称： void Ext2_ISR() interrupt 9
//函数功能： 外部中断2中断子函数
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------// 
void Ext2_ISR() interrupt 9 
{
	static uchar xdata addr_bak = 0;
	PUSH_REG_ADDR_SFR();
	INT2_INT_FLAG_CLR;//清除INT2中断标志	
	POP_REG_ADDR_SFR();
}
#endif

//-----------------------------------------------------------------//
//函数名称： void ExtInt3_Init(uchar TriggerMode,ulong Int3_X_Sel)
//函数功能： 外部中断3初始化
//输入参数： 
//外部中断1触发方式选择，uchar TriggerMode
//			 TriggerMode = 0，触发方式为下降沿触发
//			 TriggerMode = 1，触发方式为上升沿触发
//输出参数： 无
//返 回 值： 无
//注：开启多个INT3_X中断时，同一时刻只能响应一个中断，需要释放后才响应下一个INT3_X
//-----------------------------------------------------------------// 
#if ExtInt3_EN
#pragma message "编译，void ExtInt3_Init(uchar TriggerMode,ulong Int3_X_Sel)函数"
void ExtInt3_Init(uchar TriggerMode,ulong Int3_X_Sel)
{
	EA = 0;//关总中断；
	REG_ADDR = 0x27;
	REG_DATA = (uchar)(Int3_X_Sel>>24);
	TRISA |= ((uchar)(Int3_X_Sel>>24))&(0x38);
	REG_ADDR = 0x28;
	REG_DATA = (uchar)(Int3_X_Sel>>16);
	TRISD |= ((uchar)(Int3_X_Sel>>15))&(0x3E);
	TRISA |= ((uchar)(Int3_X_Sel>>21))&(0x07);
	REG_ADDR = 0x29;
	REG_DATA = (uchar)(Int3_X_Sel>>8);
	TRISC |= (uchar)(Int3_X_Sel>>8);
	REG_ADDR = 0x2A;
	REG_DATA = (uchar)(Int3_X_Sel);
	TRISB |= (uchar)(Int3_X_Sel);
	INT3_INT_FLAG_CLR;//清除INT2中断标志
	INT3_IP_SET;//设置INT2中断优级为高，根据实际应运设置优先级
	switch(TriggerMode)
	{
		case 0:									
			EXT_INT_CON &= ~0X40;	//设置为下降沿触发 			
		break;

		case 1:						
			EXT_INT_CON |= 0X40;  	//设置为上升沿触发
		break;
							 
		default:
			EXT_INT_CON &= ~0X40;	//设置为下降沿触发 
		break;	
	}
	INT3_IE_SET;//使能外部INT2中断 
	EA = 1;//开总中断	
}
//-----------------------------------------------------------------//
//函数名称： void Ext3_ISR() interrupt 18
//函数功能： 外部中断3中断子函数，同一时刻只能响应一个外部中断输入信号，INT3_X开启多个引脚检测时，电平状态需要释放才后才能响应。
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------// 
void Ext3_ISR() interrupt 18 
{
	static uchar xdata addr_bak = 0;
	PUSH_REG_ADDR_SFR();
	INT3_INT_FLAG_CLR;//清除INT2中断标志
	if((DATAB&0x01))//PB0上升沿后，读IO电平状态
	{
			
	}
	else//下降沿后，读IO电平状态
	{
			
	}
	if((DATAB&0x02))//PB1上升后，读IO电平状态
	{
		
	}
	else//下降沿后，读IO电平状态
	{
			
	}
	POP_REG_ADDR_SFR();
}
#endif
