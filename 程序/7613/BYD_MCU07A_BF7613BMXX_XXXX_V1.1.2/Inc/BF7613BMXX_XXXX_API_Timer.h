#ifndef __BF7613BMXX_XXXX_API_TIMER_H__
#define __BF7613BMXX_XXXX_API_TIMER_H__


#define	Timer0_EN				1	//Timer0使能配置，		 			1:使能编译，0:不使能编译
#define	Timer1_EN				1	//Timer1使能配置，		 			1:使能编译，0:不使能编译
#define	Timer2_EN				0	//Timer2使能配置，		 			1:使能编译，0:不使能编译

#define	TIMER2_CLK_SEL	0	//Timer2选择时钟源选择配置，		0为内部LIRC32K,1为外部晶振32768Hz

#define T0_IE_SET  IEN0 |= 0x02//开Timer0中断使能 
#define T0_IE_CLR  IEN0 &= ~0x02//关Timer0中断使能
#define T0_IP_SET  IPL0 |= 0x02//设置Timer0中断优级为高
#define T0_IP_CLR  IPL0 &= ~0X02//设置Timer0中断优级为低
#define T0_MODE_SET(x) {TMOD &= ~(0x03);TMOD |= (0x03&(x<<0));}//TIMER0定时模式选择：0：13bit定时器，1：16bit定时器，2：自动重载初值的8bit定时器，3：两个8bit定时器，tiemr0_clk=(1/12)*sys_clk
#define T0_INT_FLAG_CLR TCON  &= ~0X20//清除Timer0中断标志
#define T0_RUN TCON |= 0X10// 1为开启Timer0
#define T0_STOP TCON &= ~0X10//0为停止Timer0

#define T1_IE_SET  IEN0 |= 0x08//开Timer1中断使能 
#define T1_IE_CLR IEN0 &= ~0x08//关Timer1中断使能
#define T1_IP_SET  IPL0  |= 0x08//设置Timer1中断优级为高
#define T1_IP_CLR  IPL0 &= ~0X08//设置Timer1中断优级为低
#define T1_MODE_SET(x) {TMOD &= ~(0x30);TMOD |= (0x30&(x<<4));}//TIMER1定时模式选择：0：13bit定时器，1：16bit定时器，2：自动重载初值的8bit定时器，3：两个8bit定时器， tiemr1_clk=(1/12)*sys_clk
#define T1_INT_FLAG_CLR TCON  &= ~0X80//清除Timer1中断标志
#define T1_RUN TCON |= 0X40//1为开启 Timer1
#define T1_STOP TCON &= ~0X40//0为停止Timer1

#define T2_MODE 0x02
#define T2_SART 0x02
#define T2_CLK  0x04 

#define T2_XTAL_SET(x) {PD_ANA &= ~(0x04);PD_ANA |= (0x04&(x<<2));}//Timer2 外部晶振开关,1为关，0为开
#define T2_CLK_SET(x) {TIMER2_CFG &= ~(0x04);TIMER2_CFG |= (0x04&(x<<2));}//Timer2定时时钟选择：0：内部LIRC32K，1：外部晶振
#define T2_IE_SET IEN1 |= 0x80//开Timer2中断使能 
#define T2_IE_CLR IEN1 &= ~0x80//关Timer2中断使能
#define T2_IP_SET IPL1  |= 0x80//设置Timer2中断优级为高
#define T2_IP_CLR IPL1 &= ~0X80//设置Timer2中断优级为低
#define T2_MODE_SET(x) {TIMER2_CFG &= ~(0x02);TIMER2_CFG |= (0x02&(x<<1));}//Timer2定时模式选择：0：手动重载模式，1：1自动重载模式
#define T2_CNT_MODE_SET(x) {TIMER2_CFG &= ~(0x08);TIMER2_CFG |= (0x08&(x<<3));}//Timer2计数步进模式选择：0：1个时钟计数步进，1：65536个时钟计数步进
#define T2_INT_FLAG_CLR INT_PE_STAT &= ~0x01;IRCON1 &= ~0x80 // 清除Timer2中断标志位
#define T2_RUN  TIMER2_CFG |= 0X01//1为开启Timer2
#define T2_STOP TIMER2_CFG &= ~0X01//0为停止Timer2

#if Timer0_EN
extern void Timer0_Init(uint Timer0Us);
extern uint xdata ctk_soft_reset_max_count;
extern uint xdata sclen_soft_reset_count;
extern uint xdata sclen_soft_reset_max_count;
#endif

#if Timer1_EN
extern void Timer1_Init(uint Timer1Us);
#endif

#if Timer2_EN
#define TIMER2_CLK_RC32K 0 //Timer2时钟选择内部LIRC32K
#define TIMER2_CLK_XTAL 1 //Timer2时钟选择外部晶振
extern void Timer2_Init(unsigned int Timer2Ms);
#endif

#endif