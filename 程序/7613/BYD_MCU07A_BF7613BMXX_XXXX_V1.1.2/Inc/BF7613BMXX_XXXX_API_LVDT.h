#ifndef __BF7613BMXX_XXXX_API_LVDT_H__
#define __BF7613BMXX_XXXX_API_LVDT_H__


#define	VolDet_EN				1	//降压检测使能配置	 				1:使能编译，0:不使能编译

#define LVDT_IE_SET IEN2 |= 0x01												//开LVDT中断使能
#define LVDT_IE_CLR IEN2 &= ~0x01												//关LVDT中断使能
#define LVDT_IP_SET IPL2  |= 0x01												//设置LVDT中断优先级为高
#define LVDT_IP_CLR IPL2 &= ~0x01												//设置LVDT中断优先级为低
#define LVDT_INT_FLAG_CLR 			IRCON2 &= ~0x01					//清除低电压检测中断标志位
#define LVDT_INT_DOWN_FLAG_CLR 	INT_POBO_STAT &= ~0x01	//清除LVDT下降中断标志位
#define LVDT_INT_UP_FLAG_CLR 		INT_POBO_STAT &= ~0x02	//清除LVDT上升中断标志位
#define LVDT_ON {REG_ADDR = 0x2F;REG_DATA &= ~0x20;}				   							//开启低电压检测模块
#define LVDT_OFF {REG_ADDR = 0x2F;REG_DATA |= 0x20;}			   							  //关闭低电压检测模块
#define LVDT_DELAY(x) {REG_ADDR = 0x2F;REG_DATA &= ~(0x0C);REG_DATA |= (0x0C&(x<<3));}//0:延时1;1:延时2;2:延时3,3:延时4，延时时间见规格书表格
#define V_LVDT_SET(x) {REG_ADDR = 0x2F;REG_DATA &= ~(0x07);REG_DATA |= (0x07&(x<<0));}//设置低电压升检测点:(0/1-保留)-(2-3.0V)-(3-3.3V)-(4-3.6V)-(4-3.9V)-(6/others-4.2V)

extern bit Low_Volotage_Flag;
extern bit low_power;
extern bit Low_Volotage_Flag_Confirm;
extern bit Low_Volotage_Flag_First;
extern uint xdata Low_Volotage_Flag_Count;
extern uint xdata Low_Volotage_Flag_Confirm_count;
extern void LVDT_Init(void);

#endif