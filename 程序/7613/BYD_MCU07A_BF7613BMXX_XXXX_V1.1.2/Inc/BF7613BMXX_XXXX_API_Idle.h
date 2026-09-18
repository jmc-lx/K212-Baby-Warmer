#ifndef __BF7613BMXX_XXXX_API_IDLE_H__
#define __BF7613BMXX_XXXX_API_IDLE_H__

#define IDLE_MODE				0//设置Idle模式功能：0关闭；1开启。
#if IDLE_MODE	

	extern uint Idle_Cnt;
	extern bit Idle_Flag;
	extern uint Idle_Wait_Count;
	extern uint xdata Step_In_Idle_Time;
	extern uint xdata Idle_Wake_UpTime;
	extern uint xdata Idle_Time_Count;
	extern uint xdata Idle_Time_Count1;
	extern void Idle(void);
	extern void Idle_Wake_Up_Init(uint _StepInIdleTime,uint _IdleWakeUpTime);
	extern void Idle_Delay_Us(uint us);
	extern unsigned int  xdata raw_data_parallel[];
	extern unsigned int  xdata base_line_parallel[];
	extern unsigned char xdata Cnt_Par[];
#endif

#endif