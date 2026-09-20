#include "Config.h"


//#if ((UART0_EN == 1)||(UART1_EN == 1))
///****************************************************************/
////函数名：uchar UART_Rece_Check(uchar n,uchar *nSendByte)  
////功  能：UART接送校验
////参  数：uchar n:接送校验字节数；uchar *nSendByte：发送数据指针
////返回值：uchar 返回校验值
///****************************************************************/

//uchar UART_Rece_Check(uchar n,uchar *nCheckByte1,uchar *nCheckByte2)  
//{
//	uchar i = 0;
//	for(i = 0; i < n; i++)
//	{
//		if((*(nCheckByte1 + i)) != (*(nCheckByte2 + i)))
//		{
//				return 1;
//		}
//	}	
//	return 0;
//}
//#endif

#if (UART0_EN == 1)


	
	//-----------------------------------------------------------------//
	//函数名称： void UART0_Init(void)  
	//函数功能： UART0初始化
	//输入参数： 无
	//输出参数： 无
	//返 回 值： 无
	//-----------------------------------------------------------------//
	void UART0_Init(void) 
	{ 
			EA = 0;//关总中断；
			UART0_IP_SET;//设置UART0中断优级为高，根据实际应运设置优先级
			UART0_INT_FLAG_CLR;//清除UART0中断标志
		
			UART0_MODULE_SET(1);//UAERT0模块开关,1为开，0为关
			UART0_RX_EN_SET(1);//接收器使能 ,1为使能，0为禁止
			UART0_TX_EN_SET(1);//发送器使能 ,1为使能，0为禁止
			UART0_MULTI_SET(0);//多处理器通信使能,1为使能，0为禁止
			UART0_SEND_MODE_SET(0);//发送数据模式bit[3]：0：八位模式：1：9位模式模式
			UART0_STOP_MODE_SET(0);//STOP位 ,1为2位STOP，0为1位STOP
			UART0_OD_EN_SET(0);//奇偶校验使能 ,1为使能，0为不使能
			UART0_OD_SET(0);//奇偶校验选择 ,1为奇校验，0为偶校验
			UART0_PC_SET(UART0_PORT_CHANGE);//TX/RX引脚功能互换,1为功能互换，0为功能不互换
	
			UART0_BDL = (uchar)M_HEX_OF_BR(UART0_CFG_BAUD_RATE);//设置波特率=BUSCLK/(16*(UART_BDH[0:1],UART_BDL))
			UART0_CON2 |= (((((uint)(M_HEX_OF_BR(UART0_CFG_BAUD_RATE)))>>8)&0x03));//设置UART0_BDH[0:1]高两位
			UART0_TX_IE_SET(1);//UART0发送中断使能,1为中断使能，0为中断禁止
			UART0_RX_IE_SET(1);//UART0接收中断使能,1为中断使能，0为中断禁止
			UART0_PORT_SET(UART0_PORT);//UART0 RX/TX映射选择,0:PA0/PA1;1:PB3/PB4,2,保留，3:PC0/PC1;4:PD6/PA1,5:PD7/PA0
	
		#if(UART0_PORT == UART0_MAP_A)
			#if UART0_PORT_CHANGE
				TRISA |=  0x02;//设置RX为输入
				TRISA &= ~0x01;//设置TX为输出
			#else
				TRISA &= ~0x02;//设置TX为输出
				TRISA |= 0x01; //设置RX为输入
			#endif
		#elif(UART0_PORT == UART0_MAP_B)
			#if UART0_PORT_CHANGE
				TRISB |=  0x10;//设置RX为输入
				TRISB &= ~0x08;//设置TX为输出
			#else
				TRISB &= ~0x10;//设置TX为输出
				TRISB |= 0x08;//设置RX为输入
			#endif
		#elif(UART0_PORT == UART0_MAP_D)
			#if UART0_PORT_CHANGE
				TRISC |=  0x02;//设置RX为输入
				TRISC &= ~0x01;//设置TX为输出
			#else 
				TRISC &= ~0x02;//设置TX为输出
				TRISC |= 0x01;//设置RX为输入
			#endif
		#elif(UART0_PORT == UART0_MAP_E)
			#if UART0_PORT_CHANGE
				TRISA |=  0x02;//设置RX为输入
				TRISD &= ~0x40;//设置TX为输出
			#else 
				TRISA &= ~0x02;//设置TX为输出
				TRISD |= 0x40;//设置RX为输入
			#endif
		#elif(UART0_PORT == UART0_MAP_F)
			#if UART0_PORT_CHANGE
				TRISA |=  0x01;//设置RX为输入
				TRISD &= ~0x80;//设置TX为输出
			#else
				TRISA &= ~0x01;//设置TX为输出
				TRISD |= 0x80;//设置RX为输入
			#endif
		#else

		#endif

		TI0 = 0;//清除接收中断标志位
		RI0 = 0;//清除发送中断标志位
		
		UART0_IE_SET;//开UART中断使能				
		
		EA = 1;//开总中断
	}
	
//	#pragma disable //发送时不允许中断
//	void UART0_Send_Word(uint willSendWord)   
//	{
//			UART0_Send_Byte(willSendWord>>8);
//			UART0_Send_Byte(willSendWord);
//	}

//	#pragma message "编译,UART0功能"
//	/****************************************************************/
//	//函数名：void UART0_Send_NByte(uchar n,uchar *nSendByte)  
//	//功  能：UART0发送N BYTES
//	//参  数：uchar n:发送字节数；uchar *nSendByte：发送数据指针
//	//返回值：无
//	/****************************************************************/

//		void UART0_Send_NByte(uchar n,uchar *nSendByte)  
//		{
//				uchar i = 0;
//				for(i = 0; i < n; i++)
//				{
//					UART0_Send_Byte(*(nSendByte + i));
//				}		
//		}	
//	#pragma disable //发送时不允许中断
//	void UART0_Send_Byte(uchar willSendByte)  
//	{
//			UART0_STATE = 0x0F;//清除发送中断标志位
//			UART0_TX_IE_SET(0);//UART0发送中断使能,1为中断使能，0为中断禁止
//			UART0_BUF = willSendByte;
//			if(UART0_CON1 & 0x40)
//			{
//				while(TI0 == 0);
//				UART0_STATE = 0x0F;//清除发送中断标志位
//			}
//	}
	
	
	/* 串口0中断服务子程序 */
	void UART0_ISR() interrupt 16
	{    
			unsigned char temp;	
			static uchar xdata addr_bak = 0;
			PUSH_REG_ADDR_SFR();
			UART0_INT_FLAG_CLR;//清除UART0中断标志	
	
			if(RI0 == 1)
			{
				UART0_STATE = 0x17;//清除接收中断标志位
				temp = UART0_BUF;
					
			} 

			if(TI0 == 1)
			{
				UART0_STATE = 0x0F;//清除发送中断标志位
			} 
			POP_REG_ADDR_SFR();
	}

#endif
	
#if (UART1_EN == 1)
		#pragma message "编译,UART1功能"
		/****************************************************************/
		//函数名：void UART1_Send_NByte(uchar n,uchar *nSendByte)  
		//功  能：UART1发送N BYTES
		//参  数：uchar n:发送字节数；uchar *nSendByte：发送数据指针
		//返回值：无
		/****************************************************************/

//	#pragma disable //发送时不允许中断
//	void UART1_Send_Word(uint willSendWord)   
//	{
//			UART1_Send_Byte(willSendWord>>8);
//			UART1_Send_Byte(willSendWord);
//	}

//		void UART1_Send_NByte(uchar n,uchar *nSendByte)  
//		{
//				uchar i = 0;
//				for(i = 0; i < n; i++)
//				{
//					UART1_Send_Byte(*(nSendByte + i));
//				}		
//		}

//	#pragma disable //发送时不允许中断
//	void UART1_Send_Byte(uchar willSendByte)  
//	{
//			UART1_STATE = 0x0F;//清除发送中断标志位
//			UART1_TX_IE_SET(0);//UART0发送中断使能,1为中断使能，0为中断禁止
//			UART1_BUF = willSendByte;
//			if(UART1_CON1 & 0x40)
//			{
//				while(TI1 == 0);
//				UART1_STATE = 0x0F;//清除发送中断标志位
//			}
//	}

	//-----------------------------------------------------------------//
	//函数名称： void UART1_Init(void)  
	//函数功能： UART1初始化
	//输入参数： 无
	//输出参数： 无
	//返 回 值： 无
	//-----------------------------------------------------------------//
	void UART1_Init(void) 
	{ 
			EA = 0;//关总中断；
			UART1_IP_SET;//设置UART1中断优级为高，根据实际应运设置优先级
			UART1_INT_FLAG_CLR;//清除UART1中断标志
		
			UART1_MODULE_SET(1);//UAERT1模块开关,1为开，0为关
			UART1_RX_EN_SET(1);//接收器使能 ,1为使能，0为禁止
			UART1_TX_EN_SET(1);//发送器使能 ,1为使能，0为禁止
			UART1_MULTI_SET(0);//多处理器通信使能,1为使能，0为禁止
			UART1_SEND_MODE_SET(0);//发送数据模式bit[3]：0：八位模式：1：9位模式模式
			UART1_STOP_MODE_SET(0);//STOP位 ,1为2位STOP，0为1位STOP
			UART1_OD_EN_SET(0);//奇偶校验使能 ,1为使能，0为不使能
			UART1_OD_SET(0);//奇偶校验选择 ,1为奇校验，0为偶校验
			UART1_PC_SET(UART1_PORT_CHANGE);//TX/RX引脚功能互换,1为功能互换，0为功能不互换
	
			UART1_BDL = (uchar)M_HEX_OF_BR(UART1_CFG_BAUD_RATE);//设置波特率=BUSCLK/(16*(UART_BDH[0:1],UART_BDL))
			UART1_CON2 |= (((((uint)(M_HEX_OF_BR(UART1_CFG_BAUD_RATE)))>>8)&0x03));//设置UART1_BDH[0:1]高两位
			UART1_TX_IE_SET(1);//UART1发送中断使能,1为中断使能，0为中断禁止
			UART1_RX_IE_SET(1);//UART1接收中断使能,1为中断使能，0为中断禁止
			UART1_PORT_SET(UART1_PORT);//UART1 RX/TX映射选择,0:PB1/PB2;1:PB6/PB7,2,PA3/PA4，3:PD4/PD5;
		
		#if(UART1_PORT == UART1_MAP_A)
			#if UART1_PORT_CHANGE
				TRISB |=  0x04;//设置RX为输入
				TRISB &= ~0x02;//设置TX为输出
			#else
				TRISB &= ~0x04;//设置TX为输出
				TRISB |= 0x02;//设置RX为输入
			#endif
		#elif(UART1_PORT == UART1_MAP_B)
			#if UART1_PORT_CHANGE
				TRISB |=  0x80;//设置RX为输入
				TRISB &= ~0x40;//设置TX为输出
			#else
				TRISB &= ~0x80;//设置TX为输出
				TRISB |= 0x40;//设置RX为输入
			#endif
		#elif(UART1_PORT == UART1_MAP_C)
			#if UART1_PORT_CHANGE
				TRISD |=  0x20;//设置RX为输入
				TRISD &= ~0x10;//设置TX为输出
			#else
				TRISD &= ~0x20;//设置TX为输出
				TRISD |= 0x10;//设置RX为输入
			#endif
		#elif(UART1_PORT == UART1_MAP_D)
			#if UART1_PORT_CHANGE
				TRISA |=  0x10;//设置RX为输入
				TRISA &= ~0x08;//设置TX为输出
			#else
				TRISA |= ~0x10;//设置TX为输出
				TRISA &=  0x08;//设置RX为输入
			#endif
		#else

		#endif
		
		TI1 = 0;//清除接收中断标志位
		RI1 = 0;//清除发送中断标志位
		
		UART1_IE_SET;//开UART中断使能				
		
		EA = 1;//开总中断
	}
	
	/* 串口1中断服务子程序 */
	void UART1_ISR() interrupt 17
	{    
			unsigned char temp;	
			static uchar xdata addr_bak = 0;
			PUSH_REG_ADDR_SFR();
			UART1_INT_FLAG_CLR;//清除UART1中断标志		
			if(RI1 == 1)
			{
					UART1_STATE = 0x17;//清除接收中断标志位
					temp = UART1_BUF;
					
			} 

			if(TI1 == 1)
			{
					UART1_STATE = 0x0F;//清除发送中断标志位
					
			}  
			POP_REG_ADDR_SFR();
	}

#endif

