#ifndef __BF7613BMXX_XXXX_API_LED_H__
#define __BF7613BMXX_XXXX_API_LED_H__


#define	LED_EN							0//LED_EN使能配置	 	  1:使能编译，0:不使能编译
#define	LED_MODE						1//LED扫描模式选择		1:循环模式；0:中断模式

#define	LED_SER_Dis_MODE   0//LED串行点阵显示设置模式，0：旧模式，1：新模式

#define LED0_SCAN 0
#define LED1_SCAN 1
#define LED2_SCAN 2
#define LED3_SCAN 3
#define LED4_SCAN 4
#define LED5_SCAN 5
#define LED6_SCAN 6
#define LED7_SCAN 7
#define LED8_SCAN 8


#define LED_SER_COM_SET(x)   	{DP_CON &= ~(0x01);DP_CON |= (0x01&(x<<0));}//COM大电流选择，0为不开启，1为开启(开启后LED硬件扫描时序无效)
#define LED_COM_EN(x)   			{REG_ADDR = 0x2B;REG_DATA = x;}//COM大电流选择，对应位为0不开启COM口模式，对应位为1开启COM口模式，此时需要软件控制输出LED驱动时序
#define LED_SER_SCAN_SET(x)   {DP_CON &= ~(0x02);DP_CON |= (0x02&(x<<1));}//LED扫描模式选择，0为中断模式，1为循环模式 
#define LED_SER_MATRIX_SET(x) {DP_CON &= ~(0x1C);DP_CON |= (0x1C&(x<<2));}//LED串行点阵矩阵选择(X*Y) 0-无矩阵，1-4*4，2-5*5，3-6*6,4-6*7，5-7*7，6-7*8，7-8*8


#define LED_SER_CURRENT_SET(x) 		 (LED_DRIVE = x)									//LED驱动能力配置(0~15)，参照规格书表格
#define LED_SER_LED1_WIDTH_SET(x)  (SCAN_WIDTH = x)   							//单个灯导通时间1配置，(x+1)*16us
#define LED_SER_LED2_WIDTH_SET(x)  (LED2_WIDTH = x)									//单个灯导通时间2配置，(x+1)*16us

#define LED_START_SET(x)  		{SCAN_START &= ~(0x01);SCAN_START |= (0x01&(x<<0));}//LED扫描开始停止控制，0为停止扫描，1为开始扫描



#define LED_IE_SET IEN1 |= 0X40							//开LED中断使能
#define LED_IE_CLR IEN1 &= ~0X40						//关LED中断使能
#define LED_IP_SET IPL1 |= 0X40							//设置LED中断优先级为高
#define LED_IP_CLR IPL1 &= ~0X40						//设置LED中断优先级为低
#define LED_INT_FLAG_CLR IRCON1 &= ~0x40		// 清除LED中断标志位


#if(LED_EN == 1)

	extern void LED_SER_Init(void);
	extern void LED_IO_Sel(void);
	extern void LED_SER_Light_Set(ulong led_width_h,ulong led_width_l);
	#if (LED_MODE == 0)
		extern void LED_SER_Light_Set_Int(ulong led_width_h,ulong led_width_l);
	#endif
	extern void LED_SER_Dis_Num(uchar num,uchar dis_data);

	extern uchar code Led_ser_num[];
	extern uchar code Led_dp1;
	extern uchar code Led_dp2;
	extern uchar code Led_dp3;
	extern uchar code Led_dp4;
	extern uchar code Led_dp5;
	extern uchar code Led_dp6;

	#if (LED_SER_Dis_MODE==0)
		extern void LED_SER_Data(ulong led_data_h,ulong led_data_l);
		extern ulong xdata LED_H_Tem;
		extern ulong xdata LED_L_Tem;
		extern ulong xdata LED_Light_H_Tem;
		extern ulong xdata LED_Light_L_Tem;
	#endif

	#if LED_SER_Dis_MODE==1
		extern void LED_SER_Data(uchar* led_data);
		extern ulong data LED_Light_H_Tem;
		extern ulong data LED_Light_L_Tem;
		extern uchar data LED_Tem[];
		#define  SA  0x01
		#define  SB  0x02
		#define  SC  0x04
		#define  SD  0x08
		#define  SE  0x10
		#define  SF  0x20
		#define  SG  0x40
		#define  SH  0x80
	#endif


#endif

#endif