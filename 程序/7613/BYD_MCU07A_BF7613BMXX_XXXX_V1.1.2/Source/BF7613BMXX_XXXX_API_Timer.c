#include "Config.h"

#if Timer0_EN
uchar TH0_Reload = 0;
uchar TL0_Reload = 0;

#ifdef SNS_NUM
	#if SNS_NUM
	unsigned int 	xdata ctk_soft_reset_count = 0;
	uint xdata ctk_soft_reset_max_count = 30000;
	#endif
	void Reset_Cnt_Add(void);
#endif

#ifdef IICS_EN
	#if IICS_EN
	uint xdata sclen_soft_reset_count = 0;
	uint xdata sclen_soft_reset_max_count = 0;
	void Set_SCLEN(void);
	#endif
#endif




#endif 

#if Timer1_EN
	uchar TH1_Reload = 0;
	uchar TL1_Reload = 0;
#endif


//-----------------------------------------------------------------//
//函数名称： void Timer0_Init(uint Timer0Us)
//函数功能： 定时器0初始化
//输入参数： uint Timer0Us:定时Timer0Us us时间，Timer0Us取值范围1~10000 
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
#if Timer0_EN

	#pragma message "编译，void Timer0_Init(uint Timer0Us)函数"
	void Timer0_Init(uint Timer0Us)
	{
		EA = 0;//关总中断；
	
		T0_IP_SET;//根据实际应运设置优先级
		T0_INT_FLAG_CLR;//清除Timer0中断标志
		T0_MODE_SET(1); //Timer0定时模式选择：0：13bit定时器，1：16bit定时器，2：自动重载初值的8bit定时器，3：两个8bit定时器 tiemr0_clk=(1/12)*sys_clk
		
		TH0 = (65536 - ((uint)((Timer0Us*1.0)*((12*1.0)/12.0))))>>8;
		TL0 = (65536 - ((uint)((Timer0Us*1.0)*((12*1.0)/12.0))));
	
		
		TH0_Reload = TH0;
		TL0_Reload = TL0;
		
		#ifdef SNS_NUM
			#if SNS_NUM
				ctk_soft_reset_max_count = (500000 / Timer0Us);//计算定时500ms的次数
			#endif
		#endif
		
		#ifdef IICS_EN
			#if IICS_EN
				sclen_soft_reset_max_count = (500000 / Timer0Us);//计算定时500ms的次数
			#endif
		#endif
		
		#ifdef IDLE_MODE
			#if IDLE_MODE
				Idle_Time_Count =  (1000 / Timer0Us);//计算定时1ms的次数
			#endif
		#endif
		
		#ifdef ADC_IS_OPEN
			#if ADC_IS_OPEN
					#if ADC_MODE
					ADC_Rest_Max_Count = (100000 / Timer0Us);//计算定时100ms的次数
					#endif
			#endif
		#endif
		
		T0_IE_SET;//使能Timer0中断 
		T0_RUN;//开启Timer0
		EA = 1;//开总中断	  
	}
//-----------------------------------------------------------------//
//函数名称： void Timer0_ISR() interrupt 1
//函数功能： 定时器0中断子函数
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
	
//uchar xdata time_1ms;
uchar xdata time_5ms;
//uchar xdata time_50us;
uchar xdata frist_ad;
uchar xdata frist_buz;
void Timer0_ISR() interrupt 1
{
	static uchar xdata addr_bak = 0;
	PUSH_REG_ADDR_SFR();
	TH0 = TH0+TH0_Reload;   
	TL0 = TL0+TL0_Reload;
	T0_INT_FLAG_CLR;//清除Timer0中断标志
	
		if(++time_5ms>=5)
		{
			time_5ms=0;
			b_sys_5ms=1;
		}

	#ifdef SNS_NUM
		#if SNS_NUM
			Reset_Cnt_Add();
			if(keys_flag != 0)
			{
				long_key_clear_count++;	
			}
			else
			{
				long_key_clear_count = 0;
			}
			
			#ifdef IDLE_MODE
				#if IDLE_MODE
					if(keys_flag == 0)
					{
						
						if(Idle_Flag == 0)
						{
							Idle_Time_Count1++;
							if(Idle_Time_Count1 >= Idle_Time_Count)
							{
								Idle_Time_Count1 = 0;
								Idle_Wait_Count++;
								if(Idle_Wait_Count > (Step_In_Idle_Time-50))
								{
										parallel_mode = 1;
										
								}
								if(Idle_Wait_Count > Step_In_Idle_Time)
								{
									
									Idle_Wait_Count = 0;
									
									Idle_Flag = 1;
																													
								}
							}
						}
						else
						{
								
						}
					}
					else
					{
							Idle_Flag = 0;
							Idle_Time_Count1 = 0;
							Idle_Wait_Count = 0;
					}
				
				#endif
			#endif
		#endif
	#endif
		
	#ifdef IICS_EN
		#if IICS_EN
			Set_SCLEN();
		#endif
	#endif
	
	#ifdef ADC_IS_OPEN
		#if ADC_IS_OPEN
			#if ADC_MODE
				ADC_Reset_Count();
			#endif
		#endif
	#endif
	
	
	
	#ifdef VolDet_EN
		#if(VolDet_EN == 1)
		if(Low_Volotage_Flag == 1)
		{
			if(Low_Volotage_Flag_Count < 10000)
			{
				Low_Volotage_Flag_Count++;
				if(Low_Volotage_Flag_Count > 10)//根据实际项目调试确认次数
				{
					Low_Volotage_Flag = 0;
					Low_Volotage_Flag_Count = 0;
					Low_Volotage_Flag_Confirm = 1;//VolDet_COUNT*(timer0定时)
				}
			}	
		}
		if(Low_Volotage_Flag_Confirm == 1)
		{
			Low_Volotage_Flag_Confirm_count++;
			if(Low_Volotage_Flag_Confirm_count >= 30000)//若定时器定时为1ms，30000对应30s计数清零，Low_Volotage_Flag_Confirm清0，根据实际项目调试
			{
				Low_Volotage_Flag_Confirm_count = 0;
				Low_Volotage_Flag_Confirm = 0;
				low_power = 0;
			}
		}
		#endif
	#endif
	POP_REG_ADDR_SFR();
}
#endif

//-----------------------------------------------------------------//
//函数名称： void Timer1_Init(uint Timer1Us)
//函数功能： 定时器0初始化
//输入参数： uint Timer1Us:定时Timer1Us us时间，Timer1Us取值范围1~10000 
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
#if ((Timer1_EN == 1))
#pragma message "编译，void Timer1_Init(uint Timer1Us)函数"
void Timer1_Init(uint Timer1Us)
{
	EA = 0;//关总中断；
	T1_IP_SET;//根据实际应运设置优先级
	T1_INT_FLAG_CLR;//清除Timer1中断标志
	T1_MODE_SET(1); //设置为16位定时器，tiemr1_clk=(1/12)*sys_clk

	
//	TH1 = (65536 - ((uint)((Timer1Us*1.0)*((SYSCLK*1.0)/12.0))))>>8;//
//	TL1 = (65536 - ((uint)((Timer1Us*1.0)*((SYSCLK*1.0)/12.0))));//
	
	TH1 = (65536 - ((uint)((Timer1Us*1.0)*((12*1.0)/12.0))))>>8;//SYSCLK=12MHz
	TL1 = (65536 - ((uint)((Timer1Us*1.0)*((12*1.0)/12.0))));//SYSCLK=12MHz
	
	
	TH1_Reload = TH1;
	TL1_Reload = TL1;

	T1_IE_SET;//开Timer1中断使能 
	T1_RUN;//开启Timer1
	EA = 1;//开总中断	  
}
//-----------------------------------------------------------------//
//函数名称： void Timer1_ISR() interrupt 3
//函数功能： 定时器1中断子函数
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
void Timer1_ISR() interrupt 3
{	
	static uchar xdata addr_bak = 0;
	PUSH_REG_ADDR_SFR();
	TH1 = TH1_Reload;   
	TL1 = TL1_Reload; 
	T1_INT_FLAG_CLR;//清除Timer1中断标志
	POP_REG_ADDR_SFR();
	
	if(Buz_Begin_b)//蜂鸣器响的标志位
		 {
			 if(frist_buz==0)//首次响设输出
			 {
				 ADC_IO_SEL3 &=~0x01;
				// ADC_PD(1);ADC_SCAN_CLR;
				 frist_buz=1;
				 SET_PD0_IO_OUT;
			 }
			 buz_lead_p=~buz_lead_p;
			frist_ad=0;
		 }
		
	Disp_scan();
	Zero_deal();
} 
#endif



//-----------------------------------------------------------------//
//函数名称： void Timer2_Init(unsigned int Timer2Ms)
//函数功能： 定时器2初始化
//输入参数： unsigned int Timer2Ms:定时ims时间，i取值范围1~1999
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
#if Timer2_EN

	#pragma message "编译，void Timer2_Init(uint Timer2Ms)函数"
	void Timer2_Init(unsigned int Timer2Ms)
	{
		unsigned int data dat;
				
		EA = 0;//关总中断；
		
		T2_IP_SET;//根据实际应运设置优先级
		T2_INT_FLAG_CLR;//清除Timer2中断标志
		T2_STOP;//bit0为0时停止计时，bit0为1时开启计时
		dat = (Timer2Ms * 32.768)-1;//内部LIRC32K
		
		
		TIMER2_SET_H = dat/256;
		TIMER2_SET_L = dat%256;
		
		T2_MODE_SET(1);//bit1为0时手动重载模式，bit[1] 1为时自动重载模式  	
		T2_CNT_MODE_SET(0);//Timer2计数步进模式选择：0：1个时钟计数步进，1：65536个时钟计数步进
		
		#if (TIMER2_CLK_SEL == 0)//0为内部LIRC32K

			T2_XTAL_SET(1);//Timer2 外部晶振开关,1为关，0为开
			T2_CLK_SET(0);//Timer2定时时钟选择：0：内部LIRC32K，1：外部晶振
		
		#elif (TIMER2_CLK_SEL == 1)//1为外部晶振32768Hz
			TRISD |= 0x0C;
			T2_XTAL_SET(0);//Timer2 外部晶振开关,1为关，0为开
			T2_CLK_SET(1);//Timer2定时时钟选择：0：内部LIRC32K，1：外部晶振	
		#else
		
		#endif
		
		T2_IE_SET;//开启Timer2中断使能
		T2_RUN;//开启Timer2
		EA = 1;//开总中断	
	
	}
#endif
//-----------------------------------------------------------------//
//函数名称： void Timer2_WDT_ISR() interrupt 14
//函数功能： Timer2_WDT_ISR中断子函数
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
void Timer2_WDT_ISR() interrupt 14
{
	static uchar xdata addr_bak = 0;
	PUSH_REG_ADDR_SFR();
	if(INT_PE_STAT & 0x02)
	{
			INT_PE_STAT &= ~0x02;IRCON1 &= ~0x80;//清除看门狗中断标志	
			
	}
	if(INT_PE_STAT & 0x01)
	{

			T2_INT_FLAG_CLR;//清除Timer2中断标志位
			
	}
	POP_REG_ADDR_SFR();
}


//-----------------------------------------------------------------//
//函数名称： void Reset_Cnt_Add()
//函数功能： CTK/IIC/外部中断出错计数器累加函数
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
	#if Timer0_EN
	#ifdef SNS_NUM
		#if SNS_NUM
		void Reset_Cnt_Add()
		{
				ctk_soft_reset_count++;
		
				if(ctk_soft_reset_count >= ctk_soft_reset_max_count)
				{
					ctk_soft_reset_count = 0;
					SOFT_RST = 0x55;
				}
		}
		#endif
	#endif
	#endif

//-----------------------------------------------------------------//
//函数名称： void Set_SCLEN(void)
//函数功能： 计数判断恢复SCLEN，定时器0开启有效，建议定时时间设置为1Ms
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
#if Timer0_EN
#ifdef IICS_EN
	#if IICS_EN
	void Set_SCLEN(void)
	{

			if(SCLEN == 0)
			{
				sclen_soft_reset_count++;//SCLEN未释放计数
				if(sclen_soft_reset_count >= sclen_soft_reset_max_count)
				{
					SCLEN_SET;
					sclen_soft_reset_count = 0;							
				}					
			}
			else
			{
				sclen_soft_reset_count = 0;	
			}
			
	}
	#endif
#endif
#endif

