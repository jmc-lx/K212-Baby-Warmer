#include "Config.h"







 uchar xdata   Buz_Start_Time;
 uchar xdata    Buz_Stop_Time;
 uchar xdata   Buz_Ring_Count;
 uchar xdata    Buz_Run_Time;
 uchar xdata    Buz_Begin_b;					//蜂鸣器开始响标志
// uchar xdata   buz_lead_p;



/****************************************************************/
//函数名：void Buz_Start( unsigned int Start_Time, unsigned int Stop_Time, unsigned char Ring_Count)
//功  能：蜂鸣器启动函数
//参  数：空
//返回值：无
/****************************************************************/
void Buz_Start(uchar  Start_Time, uchar Stop_Time, uchar Ring_Count)
{
	
	
	Buz_Start_Time = Start_Time;
	Buz_Stop_Time = Stop_Time;
	Buz_Ring_Count = Ring_Count;
	Buz_Run_Time = 0;
	if(Buz_Ring_Count){
		Buz_Begin_b = 1;
	}

}

/****************************************************************/
//函数名：Buz_Stop(void)
//功  能：蜂鸣器停止函数
//参  数：空
//返回值：无
/****************************************************************/
void Buz_Stop(void)
{
	
	//如果还没响完
	if(Buz_Ring_Count){
		Buz_Run_Time++;
		if(Buz_Begin_b==1){
			if(Buz_Run_Time >= Buz_Start_Time){
				Buz_Begin_b=0;
				Buz_Run_Time=0;
				Buz_Ring_Count--;
			}
		}

		else{
			if(Buz_Run_Time >= Buz_Stop_Time){
				Buz_Begin_b = 1;
				Buz_Run_Time = 0;
			}
		}	
	}
	else{
				
		Buz_Begin_b=0;
		buz_lead_p=1;
		
	}
}






