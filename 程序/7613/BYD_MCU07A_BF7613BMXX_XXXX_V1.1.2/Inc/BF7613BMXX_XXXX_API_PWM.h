#ifndef __BF7613BMXX_XXXX_API_PWM_H__
#define __BF7613BMXX_XXXX_API_PWM_H__

#define PWM0_EN					0	//PWM0使能配置,1:使能编译，0:不使能编译,PWM 周期 = ({PWM0_MOD_H,PWM0_MOD_L+1}/24)us,PWM高电平级数{1~((24000000/(PWM0_Fre)-1)}，频率范围：推荐370Hz~369KHz
#define PWM0_CH_EN 			0x01//bit[3:0]-PWM0D_CH3/PWM0C_CH2/PWM0B_CH1/PWM0A_CH0，对应的位为1时选择该通道，为0时不选择该通道
#define PWM0_DUTY_MODE 	0x00//bit[2:0]-PWM0D_CH3/PWM0C_CH2/PWM0B_CH1，对应的位为1时选择CH0占空比，为0时选择自身通道占空比
#define PWM0_POLO_SEL 	0x00//bit[3:0]-PWM0D_CH3/PWM0C_CH2/PWM0B_CH1/PWM0A_CH0，对应的位为1时计数器溢出使能输出低，为0时计数器溢出使能输出高
#define PWM0_MAP				0x00//bit[3:0]
														//bit3:为0PWM0_CH3对应PB3,为1PWM0_CH3对应PC5;
														//bit2:为0PWM0_CH2对应PB2,为1PWM0_CH2对应PC3;	
														//bit1:为0PWM0_CH1对应PB1,为1PWM0_CH1对应PC0;
														//bit0:为0PWM0_CH0对应PB0,为1PWM0_CH1对应PB5;

#define PWM1_EN					0	//PWM1使能配置，		 	 				1:使能编译，0:不使能编译
#define PWM1_CH_EN 			0x01//bit[1:0]-PWM1B_CH1/PWM1A_CH0,对应的位为1时选择该通道，为0时不选择该通道
#define PWM1_DUTY_MODE 	0x00//bit[0]-PWM1B_CH1,为1时选择CH0占空比，为0时选择自身通道占空比
#define PWM1_POLO_SEL 	0x00//bit[1:0]-PWM1B_CH1/PWM1A_CH0,对应的位为1时计数器溢出使能输出低，为0时计数器溢出使能输出高


#define PWM2_EN					0	//PWM2使能配置，		 	 				1:使能编译，0:不使能编译
#define PWM2_CH_EN 			0x01//bit[1:0]-PWM2B_CH1/PWM2A_CH0,对应的位为1时选择该通道，为0时不选择该通道
#define PWM2_DUTY_MODE 	0x00//bit[0]-PWM2B_CH1,为1时选择CH0占空比，为0时选择自身通道占空比
#define PWM2_POLO_SEL 	0x00//bit[1:0]-PWM2B_CH1/PWM2A_CH0,对应的位为1时计数器溢出使能输出低，为0时计数器溢出使能输出高

#if (PWM0_EN == 1)
	extern 	void PWM0_Init(void);

	#if (PWM0_CH_EN & 0x01)
	extern void PWM0A_Set(ulong pwm0a_fre, uint pwm0a_rank);
	#endif

	#if (PWM0_CH_EN & 0x02)
	extern void PWM0B_Set(ulong pwm0b_fre, uint pwm0b_rank);
	#endif

	#if (PWM0_CH_EN & 0x04)
	extern void PWM0C_Set(ulong pwm0c_fre, uint pwm0c_rank);
	#endif

	#if (PWM0_CH_EN & 0x08)
	extern void PWM0D_Set(ulong pwm0d_fre, uint pwm0d_rank);
	#endif
#endif



#if (PWM1_EN == 1)
	extern void PWM1_Init(void);

	#if (PWM1_CH_EN & 0x01)
		extern void PWM1A_Set(ulong pwm1a_fre, uint pwm1a_rank);
	#endif

	#if (PWM1_CH_EN & 0x02)
		extern void PWM1B_Set(ulong pwm1b_fre, uint pwm1b_rank);
	#endif

#endif

#if (PWM2_EN == 1)
	extern void PWM2_Init(void);
	#if (PWM2_CH_EN & 0x01)
		extern void PWM2A_Set(ulong pwm2a_fre, uint pwm2a_rank);
	#endif

	#if (PWM2_CH_EN & 0x02)
		extern void PWM2B_Set(ulong pwm2b_fre, uint pwm2b_rank);
	#endif
#endif

#endif