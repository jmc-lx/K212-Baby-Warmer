#include "Config.h"

//-----------------------------------------------------------------//
//函数名称： void CFG_Check(void)
//函数功能： 配置字对比判断(对应MCU04芯片)
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
uchar CFG_Rb_Rate = 100;		 
void CFG_Check(void)
{   
	unsigned char i = 0;
	unsigned int	code add_cfg[20] =    
		{0x81FF,0x83FF,0x83FD,0x83FB,0x83F9,0x83F7,0x83F5,0x83F3,0x83F1,0x83EF,0x83ED,0x83EB,0x83E9,0x83E7,0x83E5,0x83E3,0x83E1,0x83DF,0x83DD,0x83DB};
	unsigned char code add_cfg_Bit[20] = 
		{0x3E,	 0xFF,	0x1F,	 0x3F,	0x3F,	 0xFF,	0x3F,	 0x1F,  0xEF,  0x07,  0x3F,  0xFF,  0x37,  0xFF,  0xFF,  0xFF,  0x3F,  0xFF,  0xFF,  0xFF,};
	uint rom_offset = 0;
	
	EA = 0;//关总中断
	REG_ADDR = 0x24;
	rom_offset = ((uint)REG_DATA)<<8;
	REG_ADDR = 0x23;
	rom_offset |= REG_DATA;
	for(i = 0; i < 20;i++)
	{
		REG_ADDR = i;

		if((CBYTE[add_cfg[i]-rom_offset]&add_cfg_Bit[i]) != (REG_DATA&add_cfg_Bit[i]))
		{
			SOFT_RST = 0x55;
		}	
	}
	if((CBYTE[0x83CD-rom_offset] >= 64)&&(CBYTE[0x83CD-rom_offset] <= 96))
	{
		CFG_Rb_Rate = ((ulong)(CBYTE[0x83CD-rom_offset]*100)/80);
	}
	P2_XH = 0;//使用MOVX 操作PDATA区时，P2_XH清0
	EA = 1;//开总中断	
	
}
//-----------------------------------------------------------------//
//函数名称： void Delay_Us(uint us)
//函数功能： 延时为几us
//输入参数： us
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//


//void Delay_Us(uint us)//1--2.38us@12MHz;10-11.8us@12MHz;100-106us@12MHz;1000-1.045ms
//{
//	for (; us > 0; us--)
//	{	
//		WDT_CTRL = 0x07;
//	}		
//}
 

//-----------------------------------------------------------------//
//函数名称： void Bor_Init(void)
//函数功能： 掉电复位初始化
//输入参数： 无 
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
void Bor_Init(void) 
{
	EA = 0;
	BOR_DELAY(1);//0:延时1，1：延时2,延时时间见规格书表格
	V_BOR_SET(1);//BOR掉电复位:(0-保留)-(1-2.8V)-(2-3.3V)-(3-3.7V)-(4/others-4.2V)
	BOR_ON;//开启掉电复位
	EA = 1;
}

//-----------------------------------------------------------------//
//函数名称： void Set_Sys_Clk(void)
//函数功能： 系统时钟设置
//输入参数： 无 
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
void Set_Sys_Clk(void) 
{
	SYS_CLK_SET(SYSCLK_SEL);//系统时钟选择0-12MHz,1-6MHZ,2-4MHz,3-1MHz
}
 

//-----------------------------------------------------------------//
//函数名称： void Pow_Delay(uint t)
//函数功能： 上电延时函数，根据实际应用情况选择调用。
//输入参数： t
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//



//void Pow_Up_Delay(uint ms)//参考1--1ms@12MHz;10-10.05ms@12MHz;100-100ms@12MHz;1000-1000ms
//{  
//	uint a = 954,b = ms;

//	for (b = ms; b > 0; b--)
//	{
//		for (a = 954; a > 0; a--)
//		{
//			WDT_CTRL = 0x07;
//		} 
//	}	

//}


//-----------------------------------------------------------------//
//函数名称： void Delay_Ms(uint t)
//函数功能： ms延时函数
//输入参数： t
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//


//	void Delay_Ms(uint ms)//1--1ms@12MHz;10-10.05ms@12MHz;100-100ms@12MHz;1000-1000ms
//	{  
//		uint a = 954,b = ms;
//		for (b = ms; b > 0; b--)
//		{
//			for (a = 954; a > 0; a--)
//			{
//				WDT_CTRL = 0x07;
//			} 
//		}	
//	}
	

	


//-----------------------------------------------------------------//
//函数名称： void WDT_Init(void)
//函数功能： 看门狗初始化
//输入参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
void WDT_Init(void)
{

		EA = 0;//关总中断；
		WDT_IP_CLR;//设置WDT中断优级为低，根据实际应运设置优先级
		WDT_INT_FLAG_CLR;//清除看门狗中断标志
		WDT_ON_OFF(0);//仅等于0x55时关闭看门狗
		WDT_CTRL = 7;//设置WDT溢出时间(0~7--18ms~2.304S)7--2.304S
		WDT_IE_SET;	//开WDT中断使能
		EA = 1;//开总中断	
}


//-----------------------------------------------------------------//
//函数名称： void Init_IO(void)
//函数功能： IO口初始化,将没有用到的或悬空的IO口，设置为IO输出为低
//输入参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
void Init_IO(void)
{
	#if (TRACEMODE == FALSE) 
		//IO口初化
		//例:SET_PB0_IO_OUT;
		//例:SET_PB0_H;
	Disp_gpio_out_init();
		SET_PA1_IO_OUT;
		SET_PA1_L;
		SET_PC1_IO_IN;
	  SET_PD3_IO_IN;

	#endif

	#if (TRACEMODE == TRUE) 
//		SET_PB3_IO_OUT;
//		SET_PB3_H;
	#endif
}

//-----------------------------------------------------------------//
//函数名称： void Default_Set_IO(void)
//函数功能： 默认IO口设置
//输入参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
void Default_Set_IO(void)
{   

		SNS_IO_SEL1 = 0x00;//bit0~bit7-0：设置为IO口；1：设置为SNS；
		SNS_IO_SEL2 = 0x00;//bit0~bit7-0：设置为IO口；1：设置为SNS；
		SNS_IO_SEL3 = 0x00;//bit0~bit7-0：设置为IO口；1：设置为SNS；
		SNS_IO_SEL4 = 0x00;//bit0~bit1-0：设置为IO口；1：设置为SNS；
	
	
		PU_PA = 0x00;		//0：设置为上拉不使能；1：设置为上拉使能；
		PU_PB = 0x00;		//0：设置为上拉不使能；1：设置为上拉使能；
		PU_PC = 0x00;		//0：设置为上拉不使能；1：设置为上拉使能；
		PU_PD = 0x00;		//0：设置为上拉不使能；1：设置为上拉使能；
	
		PD_PB = 0x00;		//0：设置为下拉不使能；1：设置为下拉使能；
	
		DATAA = 0x00;
		DATAB = 0x00;
		DATAC = 0x00;
		DATAD = 0x00;	  //0：设置为输出低；1：设置为输出高；
	
		TRISA = 0x00;
		TRISB = 0x00;
		TRISC = 0x00;
		TRISD = 0x00;	   //0：设置为输出；1：设置为输入；

}


//-----------------------------------------------------------------//
//函数名称： void Function_Init(void)
//函数功能： 片上外设功能模块初始化
//输入参数： 无
//返 回 值： 无
//调用位置：MCU_Init()，IO初始化完成之后执行
//注意事项：全局总中断EA不在此函数打开，main初始化完成后再开EA
//-----------------------------------------------------------------//
void Function_Init(void)
{
	//==========【调试模式初始化】==========
	//如果开启调试宏，初始化调试追踪功能
	#if (TRACEMODE == TRUE)
			BF7613BMXX_XXXX_Trace_Mode_Init(0);//调试模式初始化
	#endif
	
	//==========【定时器0初始化】==========
	#ifdef Timer0_EN
		#if Timer0_EN
			Timer0_Init(1000);//定时器0初始化，传入定时参数1000
		#endif
	#endif
	
	//==========【定时器1初始化】==========
	#ifdef Timer1_EN
		#if Timer1_EN
			Timer1_Init(124);//定时器1初始化，传入定时参数124
		#endif
	#endif
	
	//==========【定时器2初始化】==========
	#ifdef Timer2_EN
		#if Timer2_EN
			Timer2_Init(1);//定时器2初始化，传入定时参数1
		#endif
	#endif
	
	//==========【空闲休眠唤醒初始化】==========
	#ifdef IDLE_MODE
		#if IDLE_MODE
			Idle_Wake_Up_Init(5000,3);//空闲模式初始化，唤醒参数5000、3
		#endif 
	#endif
	
	//==========【串口UART0初始化】==========
	#ifdef UART0_EN
		#if(UART0_EN == 1)
			UART0_Init();//UART0_初始化
		#endif
	#endif
	
	//==========【串口UART1初始化】==========
	#ifdef UART1_EN
		#if(UART1_EN == 1)
			UART1_Init();//UART1_初始化
		#endif
	#endif
	
	//==========【PWM0模块初始化】==========
	#ifdef PWM0_EN
		#if (PWM0_EN == 1)
			PWM0_Init();  //PWM0模块基础初始化
			
			//开启PWM0A通道，设置周期、占空比参数
			#if (PWM0_CH_EN & 0x01)
				PWM0A_Set(4000,3000);
			#endif
			//开启PWM0B通道
			#if (PWM0_CH_EN & 0x02)
				PWM0B_Set(4000,3000);
			#endif
			//开启PWM0C通道
			#if (PWM0_CH_EN & 0x04)
				PWM0C_Set(4000,3000);
			#endif
			//开启PWM0D通道
			#if (PWM0_CH_EN & 0x08)
				PWM0D_Set(4000,3000);
			#endif
		#endif
	#endif
	
	//==========【PWM1模块初始化】==========
	#ifdef PWM1_EN
		#if (PWM1_EN == 1)
			PWM1_Init();//PWM1模块基础初始化
			//PWM1A通道
			#if (PWM1_CH_EN & 0x01)
				PWM1A_Set(4000,3000);
			#endif
			//PWM1B通道
			#if (PWM1_CH_EN & 0x02)
				PWM1B_Set(4000,3000);
			#endif
		#endif
	#endif
	
	//==========【PWM2模块初始化】==========
	#ifdef PWM2_EN
		#if (PWM2_EN == 1)
			PWM2_Init();//PWM2模块基础初始化
			//PWM2A通道
			#if (PWM2_CH_EN & 0x01)
				PWM2A_Set(4000,3000);
			#endif
			//PWM2B通道
			#if (PWM2_CH_EN & 0x02)
				PWM2B_Set(4000,3000);
			#endif
		#endif
	#endif
	
	//==========【LED数码管/LED驱动初始化】==========
	#ifdef LED_EN
		#if (LED_EN == 1)
			LED_SER_Init();//串行LED驱动初始化
		#endif
	#endif
	
	//==========【外部中断0初始化】==========
	#ifdef ExtInt0_EN
		#if ExtInt0_EN
			ExtInt0_Init(0);//外部中断0，参数0为触发方式
		#endif
	#endif
	
	//==========【外部中断1初始化】==========
	#ifdef ExtInt1_EN
		#if ExtInt1_EN
			ExtInt1_Init(0);//外部中断1，参数0为触发方式
		#endif
	#endif
	
	//==========【外部中断2初始化】==========
	#ifdef ExtInt2_EN
		#if ExtInt2_EN
			ExtInt2_Init(0);//外部中断2，参数0为触发方式
		#endif
	#endif
	
	//==========【外部中断3初始化】==========
	#ifdef ExtInt3_EN
		#if ExtInt3_EN
			ExtInt3_Init(0,ExtInt3_SEL);//外部中断3，触发方式、引脚选择
		#endif
	#endif
	
	//==========【LVD电源电压检测初始化】==========
	#ifdef VolDet_EN
		#if ((VolDet_EN == 1))
			LVDT_Init();//低压检测模块初始化，监控供电电压
		#endif
	#endif
	
	//==========【ADC模数转换初始化】==========
	#ifdef ADC_IS_OPEN
		#if ADC_IS_OPEN
			ADC_Init();//ADC模块初始化
		#endif
	#endif
		
	//==========【IIC从机初始化，调试模式下关闭I2C】==========
	//调试模式时IIC引脚会被调试口占用，所以TRACEMODE开启时跳过IIC从机初始化
	#if (TRACEMODE == FALSE)
		#ifdef IICS_EN
			#if IICS_EN
				IIC_Slave_Init(0xC0,0);//IIC从机初始化，从机地址0xC0
			#endif
		#endif
	#endif
	
	//==========【片上运放OP初始化】==========
	#ifdef OP_EN
		#if OP_EN	
			OP_Init();//内置运算放大器初始化
		#endif
	#endif
	
	//==========【片上EEPROM初始化】==========
	#ifdef EEPROM_EN
		#if EEPROM_EN	
			Eeprom_Init();//内部EEPROM初始化，用于保存参数
		#endif
	#endif
	
	//==========【CTK电容触摸按键初始化】==========
	#ifdef SNS_NUM
		#if SNS_NUM
			CTK_Init();	//电容触摸按键初始化
		#endif
	#endif
}

//-----------------------------------------------------------------//
//函数名称： void MCU_Init(void)
//函数功能:		MUC初始化
//输入参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
void MCU_Init(void)
{	 
	//掉电复位初始化
	Bor_Init();
	
	//看门狗初始化
	WDT_Init();

	//配置核工作时钟
	Set_Sys_Clk();

	//配置字对比判断
	CFG_Check();

	//IO口默认设置
	Default_Set_IO();
	
	//IO口初始化
	Init_IO();

	//功能函数初始化
	Function_Init(); 
	
}