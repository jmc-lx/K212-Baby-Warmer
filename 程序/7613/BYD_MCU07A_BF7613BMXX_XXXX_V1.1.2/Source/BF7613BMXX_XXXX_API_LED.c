#include "Config.h"
		
#if (LED_EN == 1)
	#pragma message "编译,LED 串行点阵功能"
	uchar code Led_ser_num[16]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};//0~9,A,b,c,d,E,F
	uchar code Led_dp1 = 	0x80;
	uchar code Led_dp2 = 	0x80;
	uchar code Led_dp3 = 	0x80;
	uchar code Led_dp4 = 	0x80;
	uchar code Led_dp5 = 	0x01;
	uchar code Led_dp6 = 	0x02;
	
	#if LED_SER_Dis_MODE==0
		ulong xdata LED_H_Tem = 0;
		ulong xdata LED_L_Tem = 0;
		
		ulong xdata LED_Light_H_Tem = 0x00FFFFFF;
		ulong xdata LED_Light_L_Tem = 0xFFFFFFFF;
	#endif
	
	#if LED_SER_Dis_MODE==1

		uchar data LED_Tem[6]={0,0,0,0,0,0};
		
		ulong data LED_Light_H_Tem = 0x00FFFFFF;
		ulong data LED_Light_L_Tem = 0xFFFFFFFF;
		
	#endif
	

#endif


#if (LED_EN == 1)

/****************************************************************/
//函数名：void LED_IO_Sel(void)
//功  能：LED0~LED8 IO重映射,扫描顺序重排，XBYTE[0x410]~XBYTE[0x418]填0~8非重复值
//参  数：无
//返回值：无
/****************************************************************/

void LED_IO_Sel(void)
{
	XBYTE[0x410] = LED0_SCAN;//PB0
	XBYTE[0x411] = LED1_SCAN;//PB1
	XBYTE[0x412] = LED2_SCAN;//PB2
	XBYTE[0x413] = LED3_SCAN;//PB3
	XBYTE[0x414] = LED4_SCAN;//PB4
	XBYTE[0x415] = LED5_SCAN;//PB5
	XBYTE[0x416] = LED6_SCAN;//PB6
	XBYTE[0x417] = LED7_SCAN;//PB7
	XBYTE[0x418] = LED8_SCAN;//PC0
}


#if LED_SER_Dis_MODE==0

/****************************************************************/
//函数名：void LED_SER_Dis_Num(uchar num,uchar dis_data)
//功  能：LED显示函数
//参  数：uchar num:数码管位，uchar dis_data数据
//返回值：无
/****************************************************************/

void LED_SER_Dis_Num(uchar num,uchar dis_data)
{
		if(num == 1)
		{

			
			LED_L_Tem &= ~0x01010101;
			LED_H_Tem &= ~0x00000303;
			LED_L_Tem |= (((ulong)dis_data)<<0) & (0x00000001);//A1
			LED_L_Tem |= (((ulong)dis_data)<<7) & (0x00000100);//B1
			LED_L_Tem |= (((ulong)dis_data)<<14)& (0x00010000);//C1
			LED_L_Tem |= (((ulong)dis_data)<<21)& (0x01000000);//D1
			LED_H_Tem |= (((ulong)dis_data)>>4) & (0x00000001);//E1
			LED_H_Tem |= (((ulong)dis_data)<<3) & (0x00000100);//F1
			LED_H_Tem |= (((ulong)dis_data)<<3) & (0x00000200);//G1
			LED_H_Tem |= (((ulong)dis_data)>>6) & (0x00000002);//H1
			
		}
		if(num == 2)
		{

			LED_L_Tem &= ~0x06060200;
			LED_H_Tem &= ~0x00000C04;
			
			LED_L_Tem |= (((ulong)dis_data)<<25) & (0x02000000);//A2
			LED_L_Tem |= (((ulong)dis_data)<<16) & (0x00020000);//B2
			LED_L_Tem |= (((ulong)dis_data)<<7)  & (0x00000200);//C2
			LED_L_Tem |= (((ulong)dis_data)<<15) & (0x00040000);//D2
			LED_L_Tem |= (((ulong)dis_data)<<22) & (0x04000000);//E2
			LED_H_Tem |= (((ulong)dis_data)>>3)  & (0x00000004);//F2
			LED_H_Tem |= (((ulong)dis_data)<<4)  & (0x00000400);//G2
			LED_H_Tem |= (((ulong)dis_data)<<4)  & (0x00000800);//H2
		}
		if(num == 3)
		{

		
			LED_L_Tem &= ~0x48000000;
			LED_H_Tem &= ~0x00007058;
			

			LED_H_Tem |= (((ulong)dis_data)<<3)  & (0x00000008);//A3
			LED_L_Tem |= (((ulong)dis_data)<<26) & (0x08000000);//B3
			LED_H_Tem |= (((ulong)dis_data)<<2)  & (0x00000010);//C3
			LED_H_Tem |= (((ulong)dis_data)<<9)  & (0x00001000);//D3
			LED_H_Tem |= (((ulong)dis_data)<<9)  & (0x00002000);//E3
			LED_H_Tem |= (((ulong)dis_data)<<9)  & (0x00004000);//F3
			LED_H_Tem |= (((ulong)dis_data)<<0)  & (0x00000040);//G3
			LED_L_Tem |= (((ulong)dis_data)<<23) & (0x40000000);//H3

		}
		if(num == 4)
		{
			
			LED_L_Tem &= ~0x20606060;
			LED_H_Tem &= ~0x00000020;

			LED_L_Tem |= (((ulong)dis_data)<<22) & (0x00400000);//A4
			LED_L_Tem |= (((ulong)dis_data)<<13) & (0x00004000);//B4
			LED_L_Tem |= (((ulong)dis_data)<<4)  & (0x00000040);//C4
			LED_H_Tem |= (((ulong)dis_data)<<2)  & (0x00000020);//D4
			LED_L_Tem |= (((ulong)dis_data)<<25) & (0x20000000);//E4
			LED_L_Tem |= (((ulong)dis_data)<<16) & (0x00200000);//F4
			LED_L_Tem |= (((ulong)dis_data)<<7)  & (0x00002000);//G4
			LED_L_Tem |= (((ulong)dis_data)>>2)  & (0x00000020);//H4
			
		}
		if(num == 5)
		{
			LED_L_Tem &= ~0x10100000;
			
			LED_L_Tem |= (((ulong)dis_data)<<28) & (0x10000000);//H5
			LED_L_Tem |= (((ulong)dis_data)<<20) & (0x00100000);//H6
			
		}
}


//-----------------------------------------------------------------//
//函数名称： void LED_SER_Data(ulong led_data_h,ulong led_data_l,ulong led_width_h,ulong led_width_l)
//函数功能： LED串行点阵数据显示函数
//输入参数： ulong led_data_h,LED高32位数据，ulong led_data_l,LED低32位数据,
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
void LED_SER_Data(ulong led_data_h,ulong led_data_l)
{

	XBYTE[0x400] = (uchar)(led_data_l>>0);
	XBYTE[0x401] = (uchar)(led_data_l>>8);
	XBYTE[0x402] = (uchar)(led_data_l>>16);
	XBYTE[0x403] = (uchar)(led_data_l>>24);
	XBYTE[0x404] = (uchar)(led_data_h>>0);
	XBYTE[0x405] = (uchar)(led_data_h>>8);
	XBYTE[0x406] = (uchar)(led_data_h>>16);
	XBYTE[0x407] = (uchar)(led_data_h>>24);
}

#endif

#if LED_SER_Dis_MODE==1
	
	/****************************************************************/
	//函数名：void LED_SER_Dis_Num(uchar num,uchar dis_data)
	//功  能：LED显示函数
	//参  数：uchar num:数码管位，uchar dis_data数据
	//返回值：无
	/****************************************************************/

	void LED_SER_Dis_Num(uchar num,uchar dis_data)
	{
			if(num == 1)
			{
				
				LED_Tem[0]&= ~0x01;
				LED_Tem[1]&= ~0x01;
				LED_Tem[2]&= ~0x01;
				LED_Tem[3]&= ~0x01;
				LED_Tem[4]&= ~0x01;
				LED_Tem[5]&= ~0x01;
				LED_Tem[5]&= ~0x02;
				LED_Tem[4]&= ~0x02;
				
				if(dis_data & SA )
				{
						
					LED_Tem[0]|=0x01;
				}
				if(dis_data & SB )
				{
					LED_Tem[1]|=0x01;
				}
				if(dis_data & SC )
				{
					LED_Tem[2]|=0x01;
				}
				if(dis_data & SD )
				{
					LED_Tem[3]|=0x01;
				}
				if(dis_data & SE )
				{
					LED_Tem[4]|=0x01;
				}
				if(dis_data & SF )
				{
					LED_Tem[5]|=0x01;
				}
				if(dis_data & SG )
				{
					LED_Tem[5]|=0x02;
				}
				if(dis_data & SH )
				{
					LED_Tem[4]|=0x02;
				}
				
			}
			if(num == 2)
			{
			
				LED_Tem[3]&=~0x02;
				LED_Tem[3]&=~0x04;
				
				LED_Tem[2]&=~0x02;
				LED_Tem[1]&=~0x02;
				LED_Tem[2]&=~0x04;
				
				LED_Tem[4]&=~0x04;
				LED_Tem[5]&=~0x04;
				LED_Tem[5]&=~0x08;

				if(dis_data & SA )
				{
					LED_Tem[3]|=0x02;
				}
				if(dis_data & SB )
				{
					LED_Tem[2]|=0x02;
				}
				if(dis_data & SC )
				{
					LED_Tem[1]|=0x02;
				}
				if(dis_data & SD )
				{
					LED_Tem[2]|=0x04;
				}
				if(dis_data & SE )
				{
					LED_Tem[3]|=0x04;
				}
				if(dis_data & SF )
				{
					LED_Tem[4]|=0x04;
				}
				if(dis_data & SG )
				{
					LED_Tem[5]|=0x04;
				}
				if(dis_data & SH )
				{
					LED_Tem[5]|=0x08;
				}

			}
			if(num == 3)
			{
			
				LED_Tem[4]&=~0x08;
				LED_Tem[3]&=~0x08;
				LED_Tem[4]&=~0x10;
				LED_Tem[5]&=~0x10;
				LED_Tem[5]&=~0x20;
				LED_Tem[5]&=~0x40;
				LED_Tem[4]&=~0x40;
				LED_Tem[3]&=~0x40;
				

				if(dis_data & SA )
				{
					LED_Tem[4]|=0x08;
				}
				if(dis_data & SB )
				{
					LED_Tem[3]|=0x08;
				}
				if(dis_data & SC )
				{
					LED_Tem[4]|=0x10;
				}
				if(dis_data & SD )
				{
					LED_Tem[5]|=0x10;
				}
				if(dis_data & SE )
				{
					LED_Tem[5]|=0x20;
				}
				if(dis_data & SF )
				{
					LED_Tem[5]|=0x40;
				}
				if(dis_data & SG )
				{
					LED_Tem[4]|=0x40;
				}
				if(dis_data & SH )
				{
					LED_Tem[3]|=0x40;
				}
				
			}
			if(num == 4)
			{
							
				LED_Tem[2]&=~0x40;
				LED_Tem[1]&=~0x40;
				LED_Tem[0]&=~0x40;
				LED_Tem[4]&=~0x20;
				LED_Tem[3]&=~0x20;
				LED_Tem[2]&=~0x20;
				LED_Tem[1]&=~0x20;
				LED_Tem[0]&=~0x20;
				
				if(dis_data & SA )
				{
					LED_Tem[2]|=0x40;
				}
				if(dis_data & SB )
				{
					LED_Tem[1]|=0x40;
				}
				if(dis_data & SC )
				{
					LED_Tem[0]|=0x40;
				}
				if(dis_data & SD )
				{
					LED_Tem[4]|=0x20;
				}
				if(dis_data & SE )
				{
					LED_Tem[3]|=0x20;
				}
				if(dis_data & SF )
				{
					LED_Tem[2]|=0x20;
				}
				if(dis_data & SG )
				{
					LED_Tem[1]|=0x20;
				}
				if(dis_data & SH )
				{
					LED_Tem[0]|=0x20;
				}
				
			}
			if(num == 5)
			{
		
				LED_Tem[3]&=~0x10;
				LED_Tem[2]&=~0x10;
				
				if(dis_data & 0x01 )
				{
					LED_Tem[3]|=0x10;
					LED_Tem[2]|=0x10;
				}
				
			}
	}

	//-----------------------------------------------------------------//
	//函数名称： void LED_SER_Data(ulong led_data_h,ulong led_data_l,ulong led_width_h,ulong led_width_l)
	//函数功能： LED串行点阵数据显示函数
	//输入参数： ulong led_data_h,LED高24位数据，ulong led_data_l,LED低32位数据,
	//输出参数： 无
	//返 回 值： 无
	//-----------------------------------------------------------------//
	void LED_SER_Data(uchar* led_data)
	{
		XBYTE[0x400] = led_data[0];
		XBYTE[0x401] = led_data[1];
		XBYTE[0x402] = led_data[2];
		XBYTE[0x403] = led_data[3];
		XBYTE[0x404] = led_data[4];
		XBYTE[0x405] = led_data[5];
		XBYTE[0x406] = led_data[6];
	} 
	
#endif

//-----------------------------------------------------------------//
//函数名称： void LED_SER_Light_Set(ulong led_width_h,ulong led_width_l)
//函数功能： LED串行点阵LED导通时间选择
//输入参数： ulong led_width_h,ulong led_width_l:LED导通时间选择,0为导通时间1，1为导通时间2
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
void LED_SER_Light_Set(ulong led_width_h,ulong led_width_l)
{

	XBYTE[0x408] = (uchar)(led_width_l>>0);
	XBYTE[0x409] = (uchar)(led_width_l>>8);
	XBYTE[0x40A] = (uchar)(led_width_l>>16);
	XBYTE[0x40B] = (uchar)(led_width_l>>24);
	XBYTE[0x40C] = (uchar)(led_width_h>>0);
	XBYTE[0x40D] = (uchar)(led_width_h>>8);
	XBYTE[0x40E] = (uchar)(led_width_h>>16);
	XBYTE[0x40F] = (uchar)(led_width_h>>24);

	LED_START_SET(1);
	
}

//-----------------------------------------------------------------//
//函数名称： void LED_SER_Light_Set_Int(ulong led_width_h,ulong led_width_l)
//函数功能： LED串行点阵LED导通时间选择
//输入参数： ulong led_width_h,ulong led_width_l:LED导通时间选择,0为导通时间1，1为导通时间2
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
#if (LED_MODE == 0)
void LED_SER_Light_Set_Int(ulong led_width_h,ulong led_width_l)
{

	XBYTE[0x408] = (uchar)(led_width_l>>0);
	XBYTE[0x409] = (uchar)(led_width_l>>8);
	XBYTE[0x40A] = (uchar)(led_width_l>>16);
	XBYTE[0x40B] = (uchar)(led_width_l>>24);
	XBYTE[0x40C] = (uchar)(led_width_h>>0);
	XBYTE[0x40D] = (uchar)(led_width_h>>8);
	XBYTE[0x40E] = (uchar)(led_width_h>>16);
	XBYTE[0x40F] = (uchar)(led_width_h>>24);
	
}
#endif

//-----------------------------------------------------------------//
//函数名称： void LED_SER_Init(void)
//函数功能： LED串行点阵驱动初始化
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------
//|    名称		   		|			    公式													|		     说明 				|
//-------------------------------------------------------------------------------------------------------
//|  T_LED(ms)			|    T_LED(ms) 	= TX_LED(ms)<=17ms		  |		LED总亮灯时间			|
//|	导通时间1<导通时间2, TX_LED(ms) = T_LED2(ms)					
//|	导通时间1>导通时间2, TX_LED(ms) = T_LED1(ms)					
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//LED串行点阵矩阵选择(X*Y) 0-无矩阵，1-4*4，2-4*5，3-5*6,4-6*7，5-7*7，6-7*8，7-8*8
//-------------------------------------------------------------------------------------------------------

void LED_SER_Init(void)
{
	EA = 0;//关总中断；
	LED_IP_SET; 		 //设置LED中断优先级为高，根据实际应运设置优先级
	LED_INT_FLAG_CLR;	// 清除LED中断标志位
	LED_SER_COM_SET(0);//COM大电流选择，0为不开启，1为开启(开启后LED硬件扫描时序无效)
	LED_SER_MATRIX_SET(4);//LED串行点阵矩阵选择(X*Y) 0-无矩阵，1-4*4，2-4*5，3-5*6,4-6*7，5-7*7，6-7*8，7-8*8
	LED_SER_CURRENT_SET(5);//LED驱动能力配置(0~15)，参照规格书LED驱动电流表
	LED_SER_LED1_WIDTH_SET(0);//单个灯导通时间1配置，(x+1)*16us
	LED_SER_LED2_WIDTH_SET(5);//单个灯导通时间2配置，(x+1)*16us
	LED_SER_SCAN_SET(LED_MODE);//LED扫描模式选择，0为中断模式，1为循环模式 
	
	LED_IO_Sel();//LED0~LED8 IO重映射,扫描顺序重排
	
	#if LED_SER_Dis_MODE==0
		LED_SER_Data(LED_H_Tem,LED_L_Tem);////输入参数： ulong led_data_h,LED高24位数据，ulong led_data_l,LED低32位数据,根据应用进行显示数据初始化，电路上无连接LED对应点设置为0；	
	#endif
	#if LED_SER_Dis_MODE==1
		LED_SER_Data(LED_Tem);
	#endif
	LED_SER_Light_Set(0xFFFFFFFF,0xFFFFFFFF);//输入参数： ulong led_width_h,ulong led_width_l:LED导通时间选择,0为导通时间1，1为导通时间2
	
	#if (LED_MODE == 0)
		LED_IE_SET;			  //开LED中断使
	#else
		LED_IE_CLR;			  //关LED中断使
	#endif
	
	LED_START_SET(1);//LED扫描开始停止控制，0为停止扫描，1为开始扫描

	EA = 1;//开总中断

}



//-----------------------------------------------------------------//
//函数名称： void LED_ISR() interrupt 13 
//函数功能： LED中断服务函数
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
#if (LED_MODE == 0)
void LED_ISR() interrupt 13
{
	static uchar xdata addr_bak = 0;
	PUSH_REG_ADDR_SFR();
	LED_INT_FLAG_CLR;	  // 清除LED中断标志位

	LED_SER_Light_Set_Int(LED_Light_H_Tem,LED_Light_L_Tem);

	
	LED_START_SET(1);	 //LED扫描开始停止控制，0为停止扫描，1为开始扫描
	POP_REG_ADDR_SFR();
}
#endif

#endif
