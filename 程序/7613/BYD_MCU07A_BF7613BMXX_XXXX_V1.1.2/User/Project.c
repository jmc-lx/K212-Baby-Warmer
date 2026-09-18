#include "Config.h"

bit IsTouch = 0;

/****************************************************************/
//函数名：void Project(void)
//功  能：项目项目功能函数
//参  数：无
//返回值：无
/****************************************************************/
uchar xdata time_share;



void Project(void)//范例
{
	if(b_sys_5ms)
	{
		b_sys_5ms=0;
		//Key_scan();
		 if(!Buz_Begin_b)
			{
				frist_buz=0;
			 if(frist_ad==0)
			 {
				 frist_ad=1;
				 ADC_IO_SEL3|=0x01;
				 SET_PD0_IO_IN;
			 }
			//Get_ADC(16);
			adc_samp();
			}
		Key_duration();
		Buz_Stop();
		 switch(time_share)
		 {
			case 1:          //第一个五毫秒			     
		  Key_handle();
			Disp_handle();	
			QuFan();
				break;
			
			case 2:          //第二个五毫秒			
			    Disp();
				break;
			
			case 3:          //第三个五毫秒	
				fun();
			 ShuiWei_deal();
				break;
			
			case 4:          //第四个五毫秒
				shuzu_fuzhi();
				Time();
			if(ShangDian_Time>=Time_3S)
				error_deal();
				break;										 
		 }
	     if(++time_share>4) time_share=1;
	}
}


