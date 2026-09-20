#ifndef __BF7613BMXX_XXXX_API_IIC_H__
#define __BF7613BMXX_XXXX_API_IIC_H__

#define IICS_EN							0	//IIC PA口从机使能配置， 			1:使能编译，0:不使能编译

#define IIC_FIL_SEL(x)			{PERIPH_IO_SEL &= ~(0x60);PERIPH_IO_SEL |= (0x60&(x<<5));}//1:为数字滤波(开数字滤波，Sleep模式下无唤醒功能)；2为模拟滤波；3为模拟和数字滤波(开数字滤波，Sleep模式下无唤醒功能);
#define IIC_IO_MAP(x)			  {PERIPH_IO_SEL &= ~(0x18);PERIPH_IO_SEL |= (0x18&(x<<3));}//0:映射到SDA0_A/SCL0_A；1:映射到SDA0_B/SCL0_B；2:映射到SDA0_C/SCL0_C；


#define IICS_WCOL (IICSTAT & 0x02)//写冲突标志位
#define IICS_WCOL_CLR (IICSTAT &= ~0x02)//清除写冲突标志位

#define IICS_RECOV (IICSTAT & 0x01)//读冲突标志位
#define IICS_RECOV_CLR (IICSTAT &= ~0x01)//清除读冲突标志位

#define IICS_AD (IICSTAT & 0x10)//地址或数据标志位
#define IICS_RW (IICSTAT & 0x20)//读写标志位

#define SCLEN 		(IICCON & 0x04)//读时钟使能拉低状态
#define SCLEN_CLR (IICCON &= ~0x04)//使能时钟拉低状态
#define SCLEN_SET (IICCON |= 0x04)//使能时钟正常工作
#define IICS_RW   (IICSTAT & 0x20)//读写标志位
#define IICS_BF   (IICSTAT & 0x08)//读IIC_BUF满标志位
#define PSW_P 	  (PSW & 0x01)//PSW寄偶标志位


#define IIC_EN 				0x01       
#define IIC_SR 				0x02      
#define IIC_SCLEN 		0x04    	
#define IIC_W_SCL_EN 	0x08 			
#define IIC_R_SCL_EN 	0x10 			
#define IIC_RST 			0x20

#define IIC_IE_SET IEN1 |= 0x08												//开IIC中断使能
#define IIC_IE_CLR IEN1 &= ~0x08											//关IIC中断使能
#define IIC_IP_SET IPL1 |= 0x08												//设置IIC中断优先级为高
#define IIC_IP_CLR IPL1 &= ~0x08											//设置IIC中断优先级为低
#define IIC_INT_FLAG_CLR IRCON1 &= ~0x08							// 清除IIC中断标志位


#if IICS_EN
extern uint data iics_PA_soft_cnt;
extern uint xdata SCLEN_SoftCnt;
extern void IIC_Slave_Init(uchar IICSlaveAddr,uchar iic_port);
#endif


#endif