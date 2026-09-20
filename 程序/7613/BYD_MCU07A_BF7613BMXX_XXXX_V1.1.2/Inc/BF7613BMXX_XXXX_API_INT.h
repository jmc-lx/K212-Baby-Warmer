#ifndef __BF7613BMXX_XXXX_API_INT_H__
#define __BF7613BMXX_XXXX_API_INT_H__


#define	ExtInt0_EN			0	//外部中断0使能配置		 			1:使能编译，0:不使能编译
#define	ExtInt1_EN			0	//外部中断1使能配置		 			1:使能编译，0:不使能编译
#define	ExtInt2_EN			0	//外部中断2使能配置		 			1:使能编译，0:不使能编译
#define	ExtInt3_EN			0	//外部中断3使能配置		 			1:使能编译，0:不使能编译
#define ExtInt3_SEL			0x00000000//INT3_X对应的bit0~bit26位为1选择为中断功能，INT3_X共用一个中断向量，同一时刻只有一个中断输入信号有效，使用后需要释放。

#define INT0_FUN_SET(x) {TRISD |= 0x01;PERIPH_IO_SEL &= ~(0x01);PERIPH_IO_SEL |= (0x01&(x<<0));}//0选择为IO口功能，1选择为INT中断功能 
#define INT0_IE_SET 	IEN0 |= 0x01//开INT0中断使能 
#define INT0_IE_CLR 	IEN0 &= ~0x01//关INT0中断使能
#define INT0_IP_SET 	IPL0  |= 0x01//设置INT0中断优级为高
#define INT0_IP_CLR 	IPL0 &= ~0X01//设置INT0中断优级为低
#define INT0_INT_FLAG_CLR TCON  &= ~0X02//清除INT0中断标志


#define INT1_FUN_SET(x) {TRISD |= 0x40;PERIPH_IO_SEL &= ~(0x02);PERIPH_IO_SEL |= (0x02&(x<<1));}//0选择为IO口功能，1选择为INT中断功能 
#define INT1_IE_SET 	IEN0 |= 0x04//开INT1中断使能 
#define INT1_IE_CLR 	IEN0 &= ~0x04//关INT1中断使能
#define INT1_IP_SET 	IPL0  |= 0x04//设置INT1中断优级为高
#define INT1_IP_CLR 	IPL0 &= ~0X04//设置INT1中断优级为低
#define INT1_INT_FLAG_CLR TCON  &= ~0X08//清除INT1中断标志

#define INT2_FUN_SET(x) {TRISD |= 0x80;PERIPH_IO_SEL &= ~(0x04);PERIPH_IO_SEL |= (0x04&(x<<2));}//0选择为IO口功能，1选择为INT中断功能 
#define INT2_IE_SET 	IEN1 |= 0x04//开INT2中断使能 
#define INT2_IE_CLR 	IEN1 &= ~0x04//关INT2中断使能
#define INT2_IP_SET 	IPL1  |= 0x04//设置INT2中断优级为高
#define INT2_IP_CLR 	IPL1 &= ~0X04//设置INT2中断优级为低
#define INT2_INT_FLAG_CLR IRCON1  &= ~0X04//清除INT2中断标志



#define INT3_IE_SET 	IEN2 |= 0x08//开INT3中断使能 
#define INT3_IE_CLR 	IEN2 &= ~0x08//关INT3中断使能
#define INT3_IP_SET 	IPL2  |= 0x08//设置INT3中断优级为高
#define INT3_IP_CLR 	IPL2 &= ~0X08//设置INT3中断优级为低
#define INT3_INT_FLAG_CLR IRCON2  &= ~0X08//清除INT3中断标志

#if ExtInt0_EN
extern void ExtInt0_Init(uchar TriggerMode);
#endif

#if ExtInt1_EN
extern void ExtInt1_Init(uchar TriggerMode);
#endif

#if ExtInt2_EN
extern void ExtInt2_Init(uchar TriggerMode);
#endif

#if ExtInt3_EN
extern void ExtInt3_Init(uchar TriggerMode,ulong Int3_X_Sel);
#endif

#endif