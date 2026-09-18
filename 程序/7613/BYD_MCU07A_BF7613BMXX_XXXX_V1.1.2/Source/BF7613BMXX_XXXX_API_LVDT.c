#include "Config.h"

#if	VolDet_EN
bit Low_Volotage_Flag = 0;
bit low_power = 0;
bit Low_Volotage_Flag_Confirm = 0;
bit Low_Volotage_Flag_First = 0;
uint xdata Low_Volotage_Flag_Count = 0;
uint xdata Low_Volotage_Flag_Confirm_count;
#endif

#if ((VolDet_EN == 1))

//-----------------------------------------------------------------//
//函数名称： void LVDT_Init(void)
//函数功能： 降压升压检测初始化
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
#if ((VolDet_EN == 1))
void LVDT_Init(void)
{
	EA = 0;//关总中断；
	LVDT_IP_SET;//设置降压升压检中断优级为高，根据实际应运设置优先级
	LVDT_INT_FLAG_CLR;//清除低电压检测中断标志位
	LVDT_INT_DOWN_FLAG_CLR;//清除电压下降中断标志位	
	LVDT_INT_UP_FLAG_CLR;//清除电压上升中断标志位LVDT_ON;//开启低电压检测模块
	
	LVDT_ON;//开启降压升压检模块
	LVDT_DELAY(3);//0:延时1;1:延时2;2:延时3;3:延时4，延时时间见规格书表格
	V_LVDT_SET(6);//设置低电压升检测点:(0/1-保留)-(2-3.0V)-(3-3.3V)-(4-3.6V)-(5-3.9V)-(6/others-4.2V)
	
	LVDT_IE_SET;//使能降压升压检中断
	EA = 1;//开总中断	   
}
#endif
//-----------------------------------------------------------------//
//函数名称： void LVDT_ISR() interrupt 15
//函数功能： 降压升压检测中断
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//	
void LVDT_ISR() interrupt 15
{	
	static uchar xdata addr_bak = 0;
	PUSH_REG_ADDR_SFR();
	LVDT_INT_FLAG_CLR;//清除降压升压中断标志位
	if(INT_POBO_STAT&0x01)
	{
		Low_Volotage_Flag = 1;
		low_power = 1;
		LVDT_INT_DOWN_FLAG_CLR;//清除电压下降中断标志位	
		
	}
	if(INT_POBO_STAT&0x02)
	{
		LVDT_INT_UP_FLAG_CLR;//清除电压上升中断标志位	
		Low_Volotage_Flag = 0;
		low_power = 0; 
		Low_Volotage_Flag_Confirm = 0;
		Low_Volotage_Flag_Count = 0;
		
	}
	POP_REG_ADDR_SFR();	
}
	 
#endif
