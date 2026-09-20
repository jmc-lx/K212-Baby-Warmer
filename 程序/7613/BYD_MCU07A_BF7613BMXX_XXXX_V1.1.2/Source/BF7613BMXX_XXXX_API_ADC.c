#include "Config.h"

#ifdef ADC_IS_OPEN		
#if ADC_IS_OPEN

	#if (ADC_MODE == 1)//ADC查询模式

		bit ADC_Start_Flag = 0;
		uint  ADC_Rest_Max_Count = 0;
		uint  ADC_Start_Count = 0;
		void ADC_Unormal_Count(void);
		
		//-----------------------------------------------------------------//
		//函数名称： void ADC_Delay_us(unsigned int us)
		//函数功能： 延时函数
		//输入参数： uint us：1--2.38us@12MHz;10-11.8us@12MHz;100-106us@12MHz;1000-1.045ms
		//输出参数： 无
		//返 回 值： 无
		//-----------------------------------------------------------------//
		void ADC_Delay_us(unsigned int us)
		{
			for (; us > 0; us--)
			{	
				WDT_CTRL = 0x07;
			}		
		}
		
		//-----------------------------------------------------------------//
		//函数名称： void ADC_Reset_Count()
		//函数功能： ADC超时计数器累加函数
		//输入参数： 无
		//输出参数： 无
		//返 回 值： 无
		//-----------------------------------------------------------------//
		#ifdef Timer0_EN
			#if Timer0_EN
				#if ADC_IS_OPEN
					#if ADC_MODE
					void ADC_Reset_Count(void)
					{
						if(ADC_Start_Flag == 1)
						{
							ADC_Start_Count++;
							if(ADC_Start_Count >= ADC_Rest_Max_Count)
							{
								SOFT_RST = 0x55;	
								ADC_Start_Count = 0;
								ADC_Start_Flag = 0;
							}
						}
					}
					#endif
				#endif
			#endif
		#endif		
				
	#endif
#endif
	

	#if ADC_IS_OPEN


	bit ADC_Done = 0;
	uchar ADC_Index = 0;
	uchar ADC_Index_Start = 0;

	bit adc_scan_done = 0;
	uchar xdata ADC_Access_Index[ADC_NUM] = {0};
	uint xdata adc_data[ADC_NUM] = {0};
	
	//-----------------------------------------------------------------//
	//函数名称： void ADC_Find_Next(void)
	//函数功能： ADC通道查找
	//输入参数： 无
	//输出参数： 无
	//返 回 值： 无
	//-----------------------------------------------------------------//
	#if (ADC_MODE == 0)	
	void  ADC_Find_Next(void)
	{
		while(1)
		{
			ADC_Index++;	
			
			if(ADC_Index >= ADC_NUM)
			{
					ADC_Index = ADC_Index_Start;
					adc_scan_done = 1;
			}
			if((ADC_Access_Index[ADC_Index]&0x80))//如果下一个是ADC通道，开启中ADC
			{
				ADC_ADDR_SET((ADC_Access_Index[ADC_Index]&0x7F));
				ADC_SCAN_EN;//开启ADC扫描
				break;
			}
			else
			{
			
			}
		}				
	}
	#endif
	
	
	//-----------------------------------------------------------------//
	//函数名称： uint Get_ADC(uchar adc_ch)
	//函数功能： 查询模式下获取ADC adc_ch的数据；
	//输入参数： uchar adc_ch:ADC通道
	//输出参数： uint：返回ADC数据
	//返 回 值： 无
	//-----------------------------------------------------------------// 
	#if (ADC_MODE == 1)		
	uint Get_ADC(uchar adc_ch)
	{
		ADC_IE_CLR;//关闭ADC中断使能
	
		if(OPENADC & (((ulong)(0x01))<< (adc_ch)))
		{
			ADC_ADDR_SET(adc_ch);
		}
		else
		{
			return 0;
		}
		
		ADC_PD(0);//开启ADC模块
		ADC_Delay_us(20);
		ADC_SCAN_EN;//开启ADC扫描
		
		ADC_Start_Flag = 1;
		while(!(IRCON1&0x10));
		ADC_Start_Count = 0;
		ADC_Start_Flag = 0;
		
		ADC_INT_FLAG_CLR;
		ADC_PD(1);//关闭ADC模块
		
		return ((uint)(ADC_RDATAH&0x0F) << 8) | (uint)ADC_RDATAL;
	}
	#endif	
	//-----------------------------------------------------------------//
	//函数名称： void ADC_Init(void)
	//函数功能： ADC初始化,在SetAccessIndexes()之后初始化;
	//输入参数： 无
	//输出参数： 无
	//返 回 值： 无
	//-----------------------------------------------------------------//        
	void ADC_Init(void)
	{
		#if (ADC_MODE == 0)
		uchar i = 0;
		uchar j = 0;
		#endif
		
		EA = 0;//关总中断；
		ADC_IP_SET;//设置ADC中断优级为高，根据实际应运设置优先级
		ADC_INT_FLAG_CLR;//清除ADC中断标志位
		ADC_IO_CGF(OPENADC);//ADC与IO功能选择，对应的位为1为ADC功能，0为IO功能
	
		ADC_SAMP_SET(ADC_SAMPT);//ADC采样时间设置bit[7:0],(0~255)采样时间为(ADC_SPT+1)*4*T_adc_clk
		ADC_WNUM_SET(ADC_WNUM);//转换完毕距离转换时间选择2~31，bit[7:3],(X+3)*T_adc_clk,需要(X+3)*T_adc_clk > 4*T_ADC_ANCK 
		ADC_SAMPBG_SET(ADC_SAMBG);//采样时序与比较时序间隔选择，0为间隔0，1为间隔1(ADC_CLK)
		ADC_SAMPDEL_SET(ADC_SAMDEL);//采样延时选择，0为间隔0(ADC_CLK)，1为2(ADC_CLK)，2为4(ADC_CLK)，3为8(ADC_CLK)
		ADC_FILTER_SET(ADC_FILTER);//输入信号滤波选择，0为不加RC滤波，1为加RC滤波
		ADC30_VIN_SET(ADC30_VIN);//ADC30内部输入电压选择，0:为1.326V,1为2.253V，2为3.111V,3为4.082V
		ADC_I_SET(ADC_OFFSETI);//ADC偏置电流大小选择，ADC_OFFSETI[1:0]；ADC_OFFSETI[0]比较器偏置电流大小:0为4uA，1为5uA；ADC_OFFSETI[1]运放偏置电流大小:0为4uA，1为5uA；
		ADC_CTRL_SET(ADC_CTRL);//ADC比较器失调消除选择，0/1为先失调消除后采样，2/3为失调消除和采样同时进行，2为第一级比较器的开关最后断开，3所有开关同时断开，默认为2
		
		ADC_ANCK_SET(ADC_ANCK);//模拟输入信号时钟分频选择，bit[3:2],(0~3)-(12MHz,8MhHz,4MHz,2MHz)
		ADC_DCLK_SET(ADC_DCLK);//ADC分频选择，bit[1:0],(0~3)-(8MHz,6MhHz,4MHz,3MHz)
		ADC_VREF_VOL_SEL(ADC_VREF_VOL);//ADC参考电压选择，1为4V，0为保留，使用时读取芯片校准值，当ADC参考电压选择为4V时，建议ADC_DCLK选择为3MHz
		
		ADC_VREF_SEL(ADC_VREF);//ADC参考电压选择，1为4V，0为VCC

		
		#if (ADC_MODE == 0)
		ADC_PD(0);//开启ADC模块
		for(j = 0; j < ADC_NUM; j++)
		{
			for (i = ADC_Index_Start; i < 32; i++) 
			{
				if(OPENADC & (((ulong)(0x01))<< (i)))
				{
					ADC_Index_Start = i+1;
					ADC_Access_Index[j] = (i)|0x80;
					break;
				}
			}
		}
			
		for(ADC_Index_Start = 0;ADC_Index_Start < ADC_NUM;ADC_Index_Start++)//查找第一个ADC通道
		{
			if(ADC_Access_Index[ADC_Index_Start] & 0x80)
			{
				ADC_Index = ADC_Index_Start;
				break;
			}
		}
		
		ADC_ADDR_SET((ADC_Access_Index[ADC_Index]&0x7F));
		
		ADC_SCAN_EN;//开启ADC扫描
		
		ADC_IE_SET;//开启ADC中断使能
		#endif
		
		#if (ADC_MODE == 1)
			ADC_SCAN_CLR;//关闭ADC扫描
			ADC_IE_CLR;//关闭ADC中断使能
		#endif
		
		EA = 1;//开总中断
			
		 
	}
	
	//-----------------------------------------------------------------//
	//函数名称： void  ADC_ISR interrupt 11
	//函数功能： ADC中断子函数
	//输入参数： 无
	//输出参数： 无
	//返 回 值： 无
	//-----------------------------------------------------------------//

	void  ADC_ISR() interrupt 11
	{
		static uchar xdata addr_bak = 0;
		PUSH_REG_ADDR_SFR();
		ADC_INT_FLAG_CLR;//清除ADC中断标志位
		ADC_SCAN_CLR;//关闭ADC扫描
		
		#if (ADC_MODE == 0)
	
			EA = 0;
			adc_data[ADC_Index] = ((uint)(ADC_RDATAH&0x0F) << 8) | (uint)ADC_RDATAL;//获取ADC数据	
			EA = 1;
		
			ADC_Find_Next();//查找下一个开启的ADC
	
		#else
			ADC_IE_CLR;//关闭ADC中断使能
			ADC_SCAN_CLR;//关闭ADC扫描	
		#endif
		POP_REG_ADDR_SFR();
		
	}
#endif
#endif

