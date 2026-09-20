#include "Config.h"


#if (PWM0_EN == 1)
	#pragma message "编译，void PWM0_Init(void)函数"
	
	//函数名：PWM0_Init(void)
	//功  能：初始化PWM0
	//参  数：无
	//返回值：无

	void PWM0_Init(void)
	{ 
		EA = 0;
		#if (PWM0_CH_EN & 0x01)
			#if ((PWM0_MAP & 0x01) == 0)
				TRISB &= ~0x01;
				REG_ADDR = 0x2D;
				REG_DATA &= ~0x01;
			#else
				TRISB &= ~0x20;
				REG_ADDR = 0x2D;
				REG_DATA |= 0x01;
			#endif
		#endif
		
		#if (PWM0_CH_EN & 0x02)
			#if ((PWM0_MAP & 0x02) == 0)
				TRISB &= ~0x02;
				REG_ADDR = 0x2D;
				REG_DATA &= ~0x02;
			#else
				TRISC&= ~0x01;
				REG_ADDR = 0x2D;
				REG_DATA |= 0x02;
			#endif
		#endif
		
		#if (PWM0_CH_EN & 0x04)
			#if ((PWM0_MAP & 0x04) == 0)
				TRISB &= ~0x04;
				REG_ADDR = 0x2D;
				REG_DATA &= ~0x04;
			#else
				TRISC&= ~0x08;
				REG_ADDR = 0x2D;
				REG_DATA |= 0x04;
			#endif
		#endif
		
		#if (PWM0_CH_EN & 0x08)
			#if ((PWM0_MAP & 0x08) == 0)
				TRISB &= ~0x08;
				REG_ADDR = 0x2D;
				REG_DATA &= ~0x08;
			#else
				TRISC&= ~0x20;
				REG_ADDR = 0x2D;
				REG_DATA |= 0x08;
			#endif
		#endif
	
		PWM0_CH_CTRL |= PWM0_CH_EN;
		PWM0_CH_CTRL |= (PWM0_POLO_SEL<<4);
		PWM_EN |= (PWM0_DUTY_MODE<<3);
		PWM_EN |= 0x01;
		PWM0_CH0_CNT_L = 0x00;
		PWM0_CH0_CNT_H = 0x00;
		PWM0_CH1_CNT_L = 0x00;
		PWM0_CH1_CNT_H = 0x00;
		PWM0_CH2_CNT_L = 0x00;
		PWM0_CH2_CNT_H = 0x00;
		PWM0_CH3_CNT_L = 0x00;
		PWM0_CH3_CNT_H = 0x00;
		PWM0_MOD_L = 0x00;
		PWM0_MOD_H = 0x00;
		EA = 1;
	}
	
	//函数名：void PWM0A_Set(ulong pwm0a_fre, uint pwm0a_rank)
	//功  能：设置PWM0A
	//参  数：pwm0a_fre频率，周期 =（PWM0_MOD+1）
	//参  数：pwm0a_rank占空比,pwm0a_cnt =(24.0*1000000)/(pwm0a_fre*1000.0),pwm0a_rank 应<= pwm0a_cnt();
	//[pwm0a_fre,pwm0a_rank]-[4000,6000]--4KHz 100%duty,[pwm0a_fre,pwm0a_rank]-[2000,12000]--4KHz 100%duty
	//返回值：无
	#if (PWM0_CH_EN & 0x01)
	void PWM0A_Set(ulong pwm0a_fre, uint pwm0a_rank)
	{ 
			uint pwm0a_cnt = 0;
		
			pwm0a_cnt = (24.0*1000000)/(pwm0a_fre*1.0)-1;
			if(pwm0a_rank <= pwm0a_cnt)
			{
					PWM0_CH0_CNT_L = (uchar)pwm0a_rank;
					PWM0_CH0_CNT_H = (uchar)(pwm0a_rank>>8);
			}
			else
			{
					PWM0_CH0_CNT_L = 0xFF;
					PWM0_CH0_CNT_H = 0xFF;
			}
			PWM0_MOD_L = (uchar)pwm0a_cnt;
			PWM0_MOD_H = (uchar)(pwm0a_cnt>>8);
			
			
	} 
	#endif
	
	//函数名：void PWM0B_Set(ulong pwm0b_fre, uint pwm0b_rank)
	//功  能：设置PWM0B
	//参  数：pwm0b_fre频率，周期 =（PWM0_MOD+1）
	//参  数：pwm0b_rank占空比,pwm0b_cnt =(24.0*1000000)/(pwm0b_fre*1000.0),pwm0b_rank 应<= pwm0b_cnt();
	//[pwm0b_fre,pwm0b_rank]-[4000,6000]--4KHz 100%duty,[pwm0b_fre,pwm0b_rank]-[2000,12000]--4KHz 100%duty
	//返回值：无
	#if (PWM0_CH_EN & 0x02)
	void PWM0B_Set(ulong pwm0b_fre, uint pwm0b_rank)
	{ 
			uint pwm0b_cnt = 0;
		
			pwm0b_cnt = (24.0*1000000)/(pwm0b_fre*1.0)-1;
			if(pwm0b_rank <= pwm0b_cnt)
			{
					PWM0_CH1_CNT_L = (uchar)pwm0b_rank;
					PWM0_CH1_CNT_H = (uchar)(pwm0b_rank>>8);
			}
			else
			{
					PWM0_CH1_CNT_L = 0xFF;
					PWM0_CH1_CNT_H = 0xFF;
			}
			PWM0_MOD_L = (uchar)pwm0b_cnt;
			PWM0_MOD_H = (uchar)(pwm0b_cnt>>8);
			
	} 
	#endif
	
	//函数名：void PWM0C_Set(ulong pwm0c_fre, uint pwm0c_rank)
	//功  能：设置PWM0C
	//参  数：pwm0c_fre频率，周期 =（PWM0_MOD+1）
	//参  数：pwm0c_rank占空比,pwm0c_cnt =(24.0*1000000)/(pwm0c_fre*1000.0),pwm0c_rank 应<= pwm0c_cnt();
	//[pwm0c_fre,pwm0c_rank]-[4000,6000]--4KHz 100%duty,[pwm0c_fre,pwm0c_rank]-[2000,12000]--4KHz 100%duty
	//返回值：无
	#if (PWM0_CH_EN & 0x04)
	void PWM0C_Set(ulong pwm0c_fre, uint pwm0c_rank)
	{ 
			uint pwm0c_cnt = 0;

			pwm0c_cnt = (24.0*1000000)/(pwm0c_fre*1.0)-1;
			if(pwm0c_rank <= pwm0c_cnt)
			{
					PWM0_CH2_CNT_L = (uchar)pwm0c_rank;
					PWM0_CH2_CNT_H = (uchar)(pwm0c_rank>>8);
			}
			else
			{
					PWM0_CH2_CNT_L = 0xFF;
					PWM0_CH2_CNT_H = 0xFF;
			}
			PWM0_MOD_L = (uchar)pwm0c_cnt;
			PWM0_MOD_H = (uchar)(pwm0c_cnt>>8);
			
	} 
	#endif
	//函数名：void PWM0D_Set(ulong pwm0d_fre, uint pwm0d_rank)
	//功  能：设置PWM0D
	//参  数：pwm0d_fre频率，周期 =（PWM0_MOD+1）
	//参  数：pwm0d_rank占空比,pwm0d_cnt =(24.0*1000000)/(pwm0d_fre*1000.0),pwm0d_rank 应<= pwm0d_cnt();
	//[pwm0d_fre,pwm0d_rank]-[4000,6000]--4KHz 100%duty,[pwm0d_fre,pwm0d_rank]-[2000,12000]--4KHz 100%duty
	//返回值：无
	#if (PWM0_CH_EN & 0x08)
	void PWM0D_Set(ulong pwm0d_fre, uint pwm0d_rank)
	{ 
			uint pwm0d_cnt = 0;
	
			pwm0d_cnt = (24.0*1000000)/(pwm0d_fre*1.0)-1;
			if(pwm0d_rank <= pwm0d_cnt)
			{
					PWM0_CH3_CNT_L = (uchar)pwm0d_rank;
					PWM0_CH3_CNT_H = (uchar)(pwm0d_rank>>8);
			}
			else
			{
					PWM0_CH3_CNT_L = 0xFF;
					PWM0_CH3_CNT_H = 0xFF;
			}
			PWM0_MOD_L = (uchar)pwm0d_cnt;
			PWM0_MOD_H = (uchar)(pwm0d_cnt>>8);
		
	} 
	#endif
#endif
	
#if (PWM1_EN == 1)
	#pragma message "编译，void PWM1_Init(void)函数"
	
	//函数名：PWM1_Init(void)
	//功  能：初始化PWM1
	//参  数：无
	//返回值：无

	void PWM1_Init(void)
	{ 

		EA = 0;
		#if (PWM1_CH_EN & 0x01)
			TRISD &= ~0x01;
		#endif
		
		#if (PWM1_CH_EN & 0x02)
			TRISC &= ~0x40;
		#endif
	
	
		PWMX_CH_CTRL |= PWM1_CH_EN;
		PWMX_CH_CTRL |= (PWM1_POLO_SEL<<2);
		PWM_EN |= (PWM1_DUTY_MODE<<6);
		PWM_EN |= 0x02;
		PWM1_CH0_CNT_L = 0x00;
		PWM1_CH0_CNT_H = 0x00;
		PWM1_CH1_CNT_L = 0x00;
		PWM1_CH1_CNT_H = 0x00;
		PWM1_MOD_L = 0x00;
		PWM1_MOD_H = 0x00;
		EA = 1;
		
		
	}
	//函数名：void PWM1A_Set(ulong pwm1a_fre, uint pwm1a_rank)
	//功  能：设置PWM1A
	//参  数：pwm1a_fre频率，周期 =（PWM1_MOD+1）
	//参  数：pwm1a_rank占空比,pwm1a_cnt =(24.0*1000000)/(pwm1a_fre*1000.0),pwm1a_rank 应<= pwm1a_cnt();
	//[pwm1a_fre,pwm1a_rank]-[4000,6000]--4KHz 100%duty,[pwm1a_fre,pwm1a_rank]-[2000,12000]--4KHz 100%duty
	//返回值：无
	#if (PWM1_CH_EN & 0x01)
	void PWM1A_Set(ulong pwm1a_fre, uint pwm1a_rank)
	{ 
			uint pwm1a_cnt = 0;
		
			pwm1a_cnt = (24.0*1000000)/(pwm1a_fre*1.0)-1;
			if(pwm1a_rank <= pwm1a_cnt)
			{
					PWM1_CH0_CNT_L = (uchar)pwm1a_rank;
					PWM1_CH0_CNT_H = (uchar)(pwm1a_rank>>8);
			}
			else
			{
					PWM1_CH0_CNT_L = 0xFF;
					PWM1_CH0_CNT_H = 0xFF;
			}
			PWM1_MOD_L = (uchar)pwm1a_cnt;
			PWM1_MOD_H = (uchar)(pwm1a_cnt>>8);
					
	} 
	#endif
	
	//函数名：void PWM1B_Set(ulong pwm1b_fre, uint pwm1b_rank)
	//功  能：设置PWM1B
	//参  数：pwm1b_fre频率，周期 =（PWM1_MOD+1）
	//参  数：pwm1b_rank占空比,pwm1b_cnt =(24.0*1000000)/(pwm1b_fre*1000.0),pwm1b_rank 应<= pwm1b_cnt();
	//[pwm1b_fre,pwm1b_rank]-[4000,6000]--4KHz 100%duty,[pwm1b_fre,pwm1b_rank]-[2000,12000]--4KHz 100%duty
	//返回值：无
	#if (PWM1_CH_EN & 0x02)
	void PWM1B_Set(ulong pwm1b_fre, uint pwm1b_rank)
	{ 
			uint pwm1b_cnt = 0;
		
			pwm1b_cnt = (24.0*1000000)/(pwm1b_fre*1.0)-1;
			if(pwm1b_rank <= pwm1b_cnt)
			{
					PWM1_CH1_CNT_L = (uchar)pwm1b_rank;
					PWM1_CH1_CNT_H = (uchar)(pwm1b_rank>>8);
			}
			else
			{
					PWM1_CH1_CNT_L = 0xFF;
					PWM1_CH1_CNT_H = 0xFF;
			}
			PWM1_MOD_L = (uchar)pwm1b_cnt;
			PWM1_MOD_H = (uchar)(pwm1b_cnt>>8);
			
	} 
	#endif
	
	#endif
	
	#if (PWM2_EN == 1)
	#pragma message "编译，void PWM2_Init(void)函数"
	
	//函数名：PWM2_Init(void)
	//功  能：初始化PWM2
	//参  数：无
	//返回值：无

	void PWM2_Init(void)
	{ 
		EA = 0;
		#if (PWM2_CH_EN & 0x01)
			TRISD &= ~0x02;
		#endif
		
		#if (PWM2_CH_EN & 0x02)
			TRISC &= ~0x80;
		#endif
	
	
		PWMX_CH_CTRL |= (PWM2_CH_EN<<4);
		PWMX_CH_CTRL |= (PWM2_POLO_SEL<<6);
		PWM_EN |= (PWM2_DUTY_MODE<<7);
		PWM_EN |= 0x04;
		PWM2_CH0_CNT_L = 0x00;
		PWM2_CH0_CNT_H = 0x00;
		PWM2_CH1_CNT_L = 0x00;
		PWM2_CH1_CNT_H = 0x00;
		PWM2_MOD_L = 0x00;
		PWM2_MOD_H = 0x00;
		EA = 1;
	}
	
	
	//函数名：void PWM2A_Set(ulong pwm2a_fre, uint pwm2a_rank)
	//功  能：设置PWM2A
	//参  数：pwm2a_fre频率，周期 =（PWM2_MOD+1）
	//参  数：pwm2a_rank占空比,pwm2a_cnt =(24.0*1000000)/(pwm2a_fre*1000.0),pwm2a_rank 应<= pwm2a_cnt();
	//[pwm2a_fre,pwm2a_rank]-[4000,6000]--4KHz 100%duty,[pwm2a_fre,pwm2a_rank]-[2000,12000]--4KHz 100%duty
	//返回值：无
	#if (PWM2_CH_EN & 0x01)
	void PWM2A_Set(ulong pwm2a_fre, uint pwm2a_rank)
	{ 
			uint pwm2a_cnt = 0;
		
			pwm2a_cnt = (24.0*1000000)/(pwm2a_fre*1.0)-1;
			if(pwm2a_rank <= pwm2a_cnt)
			{
					PWM2_CH0_CNT_L = (uchar)pwm2a_rank;
					PWM2_CH0_CNT_H = (uchar)(pwm2a_rank>>8);
			}
			else
			{
					PWM2_CH0_CNT_L = 0xFF;
					PWM2_CH0_CNT_H = 0xFF;
			}
			PWM2_MOD_L = (uchar)pwm2a_cnt;
			PWM2_MOD_H = (uchar)(pwm2a_cnt>>8);		
	} 
	#endif
	
	//函数名：void PWM2B_Set(ulong pwm2b_fre, uint pwm2b_rank)
	//功  能：设置PWM2B
	//参  数：pwm2b_fre频率，周期 =（PWM2_MOD+1）
	//参  数：pwm2b_rank占空比,pwm2b_cnt =(24.0*1000000)/(pwm2b_fre*1000.0),pwm2b_rank 应<= pwm2b_cnt();
	//[pwm2b_fre,pwm2b_rank]-[4000,6000]--4KHz 100%duty,[pwm2b_fre,pwm2b_rank]-[2000,12000]--4KHz 100%duty
	//返回值：无
	#if (PWM2_CH_EN & 0x02)
	void PWM2B_Set(ulong pwm2b_fre, uint pwm2b_rank)
	{ 
			uint pwm2b_cnt = 0;
		
			pwm2b_cnt = (24.0*1000000)/(pwm2b_fre*1.0)-1;
			if(pwm2b_rank <= pwm2b_cnt)
			{
					PWM2_CH1_CNT_L = (uchar)pwm2b_rank;
					PWM2_CH1_CNT_H = (uchar)(pwm2b_rank>>8);
			}
			else
			{
					PWM2_CH1_CNT_L = 0xFF;
					PWM2_CH1_CNT_H = 0xFF;
			}
			PWM2_MOD_L = (uchar)pwm2b_cnt;
			PWM2_MOD_H = (uchar)(pwm2b_cnt>>8);
			
	} 
	#endif  
	#endif
	