#ifndef __BF7613BMXX_XXXX_API_UART_H__
#define __BF7613BMXX_XXXX_API_UART_H__



#define UART0_EN							0	// 1:使能编译，0:不使能编译
#define UART0_PORT 						UART0_MAP_A//选择UART0映射
#define UART0_CFG_BAUD_RATE   9600 //UART0波特率选择:2400/4800/9600/19200/38400/57600/115200
#define UART0_PORT_CHANGE     0 //RX/TX引脚功能互换,1为功能互换，0为功能不互换


#define UART1_EN							1	// 1:使能编译，0:不使能编译
#define UART1_PORT 						UART1_MAP_C//选择UART1映射
#define UART1_CFG_BAUD_RATE  	9600 // UART1波特率选择2400/4800/9600/19200/38400/57600/115200
#define UART1_PORT_CHANGE     0 //RX/TX引脚功能互换,1为功能互换，0为功能不互换


#define UART_CFG_BUSCLK  		24   // BUSCLK固定频率
#define _CFG_BUSCLK 				(UART_CFG_BUSCLK * 1e6)
#define M_HEX_OF_BR(br)     (_CFG_BUSCLK/(16.0*br))


#define UART0_MAP_A 			0
#define UART0_MAP_B 			1
#define UART0_MAP_D 			3
#define UART0_MAP_E 			4
#define UART0_MAP_F 			5

#define UART0_PORT_SET(x) 		 {UART_IO_SEL &= ~(0x07);UART_IO_SEL |= (0x07&(x<<0));}//UART0 RX/TX映射选择,0:PA0/PA1;1:PB3/PB4,2,保留，3:PC0/PC1;4:PD6/PA1,5:PD7/PA0

#define UART0_MODULE_SET(x) 	 {UART0_CON1 &= ~(0x80);UART0_CON1 |= (0x80&(x<<7));}//UAERT0模块开关,1为开，0为关
#define UART0_TX_EN_SET(x) 		 {UART0_CON1 &= ~(0x40);UART0_CON1 |= (0x40&(x<<6));}//发送使能 ,1为使能，0为禁止
#define UART0_RX_EN_SET(x) 		 {UART0_CON1 &= ~(0x20);UART0_CON1 |= (0x20&(x<<5));}//接收使能 ,1为使能，0为禁止
#define UART0_MULTI_SET(x) 		 {UART0_CON1 &= ~(0x10);UART0_CON1 |= (0x10&(x<<4));}//多处理器通信使能,1为使能，0为禁止
#define UART0_STOP_MODE_SET(x) {UART0_CON1 &= ~(0x08);UART0_CON1 |= (0x08&(x<<3));}//STOP位 ,1为2位STOP，0为1位STOP
#define UART0_SEND_MODE_SET(x) {UART0_CON1 &= ~(0x04);UART0_CON1 |= (0x04&(x<<2));}//发送数据模式选择 ,1为9位模式模式，0为八位模式
#define UART0_OD_EN_SET(x) 		 {UART0_CON1 &= ~(0x02);UART0_CON1 |= (0x02&(x<<1));}//奇偶校验使能 ,1为使能，0为不使能
#define UART0_OD_SET(x) 		 	 {UART0_CON1 &= ~(0x01);UART0_CON1 |= (0x01&(x<<0));}//奇偶校验选择 ,1为奇校验，0为偶校验

#define UART0_PC_SET(x) 	 {UART0_CON2 &= ~(0x10);UART0_CON2 |= (0x10&(x<<4));}//RX/TX引脚功能互换,1为功能互换，0为功能不互换
#define UART0_TX_IE_SET(x) {UART0_CON2 &= ~(0x08);UART0_CON2 |= (0x08&(x<<3));}//UART0发送中断使能,1为中断使能，0为中断禁止
#define UART0_RX_IE_SET(x) {UART0_CON2 &= ~(0x04);UART0_CON2 |= (0x04&(x<<2));}//UART0接收中断使能,1为中断使能，0为中断禁止



#define UART0_IE_SET IEN2 |= 0x02												//开UART0中断使能
#define UART0_IE_CLR IEN2 &= ~0x02											//关UART0中断使能
#define UART0_IP_SET IPL2  |= 0x02											//设置UART0中断优先级为高
#define UART0_IP_CLR IPL2 &= ~0x02											//设置UART0中断优先级为低
#define UART0_INT_FLAG_CLR IRCON2 &= ~0x02							// 清除UART0中断标志位


#define UART1_MAP_A 			0
#define UART1_MAP_B 			1
#define UART1_MAP_C 			3
#define UART1_MAP_D 			2

#define UART1_PORT_SET(x) 		 {UART_IO_SEL &= ~(0x18);UART_IO_SEL |= (0x18&(x<<3));}//UART1 RX/TX映射选择,0:PB1/PB2;1:PB6/PB7,2,PA3/PA4，3:PD4/PD5;

#define UART1_MODULE_SET(x) 	 {UART1_CON1 &= ~(0x80);UART1_CON1 |= (0x80&(x<<7));}//UAERT1模块开关,1为开，0为关
#define UART1_TX_EN_SET(x) 		 {UART1_CON1 &= ~(0x40);UART1_CON1 |= (0x40&(x<<6));}//发送使能 ,1为使能，0为禁止
#define UART1_RX_EN_SET(x) 		 {UART1_CON1 &= ~(0x20);UART1_CON1 |= (0x20&(x<<5));}//接收使能 ,1为使能，0为禁止
#define UART1_MULTI_SET(x) 		 {UART1_CON1 &= ~(0x10);UART1_CON1 |= (0x10&(x<<4));}//多处理器通信使能,1为使能，0为禁止
#define UART1_STOP_MODE_SET(x) {UART1_CON1 &= ~(0x08);UART1_CON1 |= (0x08&(x<<3));}//STOP位 ,1为2位STOP，0为1位STOP
#define UART1_SEND_MODE_SET(x) {UART1_CON1 &= ~(0x04);UART1_CON1 |= (0x04&(x<<2));}//发送数据模式选择 ,1为9位模式模式，0为八位模式
#define UART1_OD_EN_SET(x) 		 {UART1_CON1 &= ~(0x02);UART1_CON1 |= (0x02&(x<<1));}//奇偶校验使能 ,1为使能，0为不使能
#define UART1_OD_SET(x) 		 	 {UART1_CON1 &= ~(0x01);UART1_CON1 |= (0x01&(x<<0));}//奇偶校验选择 ,1为奇校验，0为偶校验

#define UART1_PC_SET(x) 	 {UART1_CON2 &= ~(0x10);UART1_CON2 |= (0x10&(x<<4));}//RX/TX引脚功能互换,1为功能互换，0为功能不互换
#define UART1_TX_IE_SET(x) {UART1_CON2 &= ~(0x08);UART1_CON2 |= (0x08&(x<<3));}//UART1发送中断使能,1为中断使能，0为中断禁止
#define UART1_RX_IE_SET(x) {UART1_CON2 &= ~(0x04);UART1_CON2 |= (0x04&(x<<2));}//UART1接收中断使能,1为中断使能，0为中断禁止

#define UART1_IE_SET IEN2 |= 0x04												//开UART1中断使能
#define UART1_IE_CLR IEN2 &= ~0x04											//关UART1中断使能
#define UART1_IP_SET IPL2  |= 0x04											//设置UART1中断优先级为高
#define UART1_IP_CLR IPL2 &= ~0x04											//设置UART1中断优先级为低
#define UART1_INT_FLAG_CLR IRCON2 &= ~0x04							// 清除UART1中断标志位



#if(UART0_EN == 1)
extern void UART0_Init(void);
//extern void UART0_Send_Word (unsigned int willSendWord);
//extern void UART0_Send_Byte (unsigned char willSendByte);
//extern void UART0_Send_NByte(uchar n,uchar *nSendByte);  
#endif

#if(UART1_EN == 1)
extern void UART1_Init(void);
//extern void UART1_Send_Word (unsigned int willSendWord);
//extern void UART1_Send_Byte (unsigned char willSendByte);
//extern void UART1_Send_NByte(uchar n,uchar *nSendByte);  
#endif

#if ((UART0_EN == 1)||(UART1_EN == 1))
//extern uchar UART_Rece_Check(uchar n,uchar *nCheckByte1,uchar *nCheckByte2); 
#endif

#endif