#include "Config.h"


//#define ZhuFei  0x01
//#define ChuLv   0x02
//#define DunZhu  0x04
//#define YuYue   0x08
//#define TiaoNai 0x10
//#define ReTiao  0x20
//#define HuaCha  0x40
//#define WenHuo  0x80
uchar xdata r_cook_step;
uint xdata change_time;
uint xdata Warm_Cnt;
uint xdata Fun_Time;
//uint xdata ChuLv_Time;
uchar xdata start_time_b;//开始倒计时标志位
uchar xdata JiaXian_b;
uchar xdata warm_jiaxian_time;
uchar xdata ChuLv_daojishi;
uchar xdata frist_baowen_temp;
uchar xdata baowen_jieduan;
uchar xdata gaoyuan_No;
uint xdata Warm_long_time;

#define High_water 1
#define Low_water  0

void fun(void)
{
//	if(system_state!=Work_state&&system_state!=Warm_state)
//	{
//		
//	}
	if(system_state!=Work_state)gaoyuan_b=0;
	if(system_state==Work_state&&TiHu_b==0)
	{
		if(du_97==0)
		GaoYuan_deal();
		switch(Menu)
		{
			case ZhuFei:
				switch(r_cook_step)
				{
					case 0:
						if(dsp_wendu>=100)
						{
							r_cook_step=1;
							change_time=0;
						}
//						if(gaoyuan_b)
//						Temp_gear=1;	
//						else
						Temp_gear=4;
						
						if(gaoyuan_b&&dsp_wendu<=94)
						{
						   	system_state=Warm_state;
								No_operation_Time=250;
								max_wendu=dsp_wendu;
								frist_baowen_temp=0;
								Warm_Cnt=4320;
								Fun_Time=0;
								du_97=0;
								Buz_Start(60,30,1);
								BaoWen_JiaXian_100=1;
								duibi_time2=0;
						}
					break;
						
					case 1:
						if(dsp_wendu>=100)
						{
							if(++change_time>Time_30S)
							{
								system_state=Warm_state;
								No_operation_Time=250;
								max_wendu=dsp_wendu;
								frist_baowen_temp=0;
								Warm_Cnt=4320;
								Fun_Time=0;
								du_97=0;
								Buz_Start(60,30,1);
								BaoWen_JiaXian_100=1;
								duibi_time2=0;
							}
						}
						 if(gaoyuan_b&&dsp_wendu<=94)
						{
						   	system_state=Warm_state;
								No_operation_Time=250;
								max_wendu=dsp_wendu;
								frist_baowen_temp=0;
								Warm_Cnt=4320;
								Fun_Time=0;
								du_97=0;
								Buz_Start(60,30,1);
								BaoWen_JiaXian_100=1;
								duibi_time2=0;
						}
						if(dsp_wendu<95)
						{
							change_time=0;
							r_cook_step=0;
						}
//						if(gaoyuan_b)
//						Temp_gear=1;	
//						else
						Temp_gear=3;
					break;
				}
			break;
			
			case ChuLv:
				switch(r_cook_step)
				{
					case 0:
						if(dsp_wendu>=100)
						{
							if(++change_time>Time_30S)
							{
							r_cook_step=1;
							Fun_Time=0;
							ChuLv_daojishi=1;
							CL_Min=5;
							CL_Sec=0;
							}
							Temp_gear=3;
						}
						else
						Temp_gear=4;//全功率
						
						if(gaoyuan_b&&dsp_wendu<=94)
						{
							r_cook_step=1;
							Fun_Time=0;
							ChuLv_daojishi=1;
							CL_Min=5;
							CL_Sec=0;
						}
					break;
						
					case 1:
							if(!CL_Sec&&!CL_Min)
							{
								system_state=Warm_state;
								No_operation_Time=250;
								frist_baowen_temp=0;
								max_wendu=dsp_wendu;
								Warm_Cnt=4320;
								Fun_Time=0;
								du_97=0;
								Buz_Start(60,30,1);
								BaoWen_JiaXian_100=1;
								duibi_time2=0;
							}
							if(++Fun_Time>=Time_1S)
							{
								Fun_Time=0;
								if(!CL_Sec)
							{
								CL_Sec=59;
								CL_Min--;
							}
							else
								CL_Sec--;
							}
						if(dsp_wendu<96&&gaoyuan_b==0)
						{
							ChuLv_daojishi=0;
							change_time=0;
							r_cook_step=0;
						}
						Temp_gear=2;//300w
				}
			break;
			
			case DunZhu:
			case HuaCha:
			case WenHuo:
				switch(r_cook_step)
				{
					case 0:
						if(dsp_wendu>=95)
						{
							r_cook_step=1;
							change_time=0;
						}
//						if(gaoyuan_b)
//						Temp_gear=1;	
//						else
						Temp_gear=4;//全功率
						
						if(gaoyuan_b&&dsp_wendu<=94)
						{
							r_cook_step=2;
							start_time_b=1;
							Fun_Time=0;
							feiteng_b=1;
						}
					break;
						
					case 1:
						if(dsp_wendu>=100)
						{
							if(++change_time>Time_30S)
							{
							r_cook_step=2;
							start_time_b=1;
							Fun_Time=0;
							feiteng_b=1;
							}
						}
						if(gaoyuan_b&&dsp_wendu<=94)
						{
							r_cook_step=2;
							start_time_b=1;
							Fun_Time=0;
							feiteng_b=1;
						}
						if(dsp_wendu<93)
						{
							r_cook_step=0;
						}
//						if(gaoyuan_b)
//						Temp_gear=1;	
//						else
						Temp_gear=3;//400w
					break;
						
					case 2:
						gaoyuan_No=1;
						dsp_way=dsp_time;
					if(dsp_wendu<=96)
						Temp_gear=3;
					else if(dsp_wendu>=99)
						Temp_gear=1;//100w
					break;
				}
			break;
			
			case TiaoNai:
			case ReTiao:
				start_time_b=1;
			if(dsp_wendu<=set_temp)
		{
			Fan_b=0;
			CLR_Fan;
		}
				if(adc_NTC_Temp<set_temp-7)
				{
					if(shuiwei_dangwei==High_water)
						Temp_gear=4;
					else
						Temp_gear=6;
					JiaXian_b=0;
					return;
				}
				else if(adc_NTC_Temp<set_temp-2)
				{
					if(shuiwei_dangwei==High_water)
						Temp_gear=3;
					else
						Temp_gear=5;
					JiaXian_b=0;
					return;
				}
				else if(adc_NTC_Temp<set_temp)
				{
					Temp_gear=5;
					if(adc_NTC_Temp<set_temp-3)
					{
					JiaXian_b=0;
					return;
					}
				}
				else if(adc_NTC_Temp>set_temp)
				{
					Temp_gear=0;
					CLR_Heat;
					if(adc_NTC_Temp>set_temp+3)
					{
					JiaXian_b=0;
					return;
					}
				}
         if(dsp_wendu==set_temp&&adc_NTC_Temp>=set_temp)
				{
						JiaXian_b=1;
						if(frist_baowen_temp==0)
					{
						frist_baowen_temp=1;
						key_buz_b=1;
					}
						Temp_gear=0;
						CLR_Heat;
				}
//				else
//				{
//					warm_jiaxian_time=0;
//				}
			break;

		}
	}
	else if(system_state==Warm_state&&TiHu_b==0)
	{
		//ShuiWei_deal();
		dsp_way=dsp_temp;
		if(dsp_wendu<=baowen_temp)
		{
			Fan_b=0;
			CLR_Fan;
		}
		if(adc_NTC_Temp<baowen_temp-7)
		{
			Warm_long_time=0;
			if(shuiwei_dangwei==High_water)
				Temp_gear=4;
			else
				Temp_gear=6;
			JiaXian_b=0;
			return;
		}
		else if(adc_NTC_Temp<baowen_temp-2)
		{
			Warm_long_time=0;
			if(shuiwei_dangwei==High_water)
				Temp_gear=3;
			else
				Temp_gear=5;
			JiaXian_b=0;
			return;
		}
		else if(adc_NTC_Temp<baowen_temp)
		{
			if(++Warm_long_time<=Time_30S)
				Temp_gear=5;
			else
				Temp_gear=2;
			if(adc_NTC_Temp<baowen_temp-3)
			{
			JiaXian_b=0;
			return;
			}
		}
		else if(adc_NTC_Temp>baowen_temp)
		{
			Warm_long_time=0;
			Temp_gear=0;
			CLR_Heat;
			if(adc_NTC_Temp>baowen_temp+3)
			{
			JiaXian_b=0;
			return;
			}
		}
		 if(dsp_wendu==baowen_temp&&adc_NTC_Temp>=baowen_temp)
		{
//			if(++warm_jiaxian_time>=Time_2S)
//			{
				JiaXian_b=1;
			Warm_long_time=0;
					if(frist_baowen_temp==0)
				{
					frist_baowen_temp=1;
					key_buz_b=1;
				}
//			}
				Temp_gear=0;
				CLR_Heat;
		}
//		else
//		{
//			warm_jiaxian_time=0;
//		}
		
	}
	else
	{
		if(system_state!=ZiJian_state)
		{
		Temp_gear=0;
		CLR_Heat;
		}
	}
}

uchar xdata fanzhuan_time;
uchar xdata zero_data;
uchar xdata zero_time_b;
uchar xdata zero_cnt;
uchar xdata Temp_gear;
void Zero_deal(void) //过零处理
{
	if(zero_pro_b!=zero_data)
		{
			zero_data=zero_pro_b;
			zero_time_b=1;	//检测到翻转为1
			fanzhuan_time=0;
		}
		else
		{
			if(fanzhuan_time<250)
			fanzhuan_time++;
		}
		
	if(system_state==Work_state||system_state==Warm_state||system_state==ZiJian_state)
	{
		if(zero_time_b)//为1后进来判
		{
			zero_time_b=0;
			if(++zero_cnt>12)//进来7次
			{
				zero_cnt=1;
			}
			if(Temp_gear==1)//100w
			{
				if(zero_cnt==1)
					SET_Heat;
				else CLR_Heat;
			}
			else if(Temp_gear==2)//300w
			{
					if(zero_cnt==3||zero_cnt==4||zero_cnt==5||zero_cnt==6)
						SET_Heat;
					else 
						CLR_Heat;
			}
			else if(Temp_gear==3)//400w
			{
					if(zero_cnt==2||zero_cnt==5||zero_cnt==6||zero_cnt==7)
						SET_Heat;
					else 
						CLR_Heat;
			}
			else if(Temp_gear==4)//800w全功率
			{
				SET_Heat;
			}
			else if(Temp_gear==5)//200w
			{
				if(zero_cnt==1||zero_cnt==2)
					SET_Heat;
				else CLR_Heat;
			}
			else if(Temp_gear==6)//600w
			{
				if(zero_cnt==4||zero_cnt==5||zero_cnt==6||zero_cnt==7||zero_cnt==9||zero_cnt==10)
					SET_Heat;
				else CLR_Heat;
			}
			else
			{
				CLR_Heat;
			}
		}
	}
}



uchar xdata shuiwei_dangwei;
uchar xdata shuiwei_duibi;
uint xdata shuiwei_time;
void ShuiWei_deal()       //水位检测
{
	if(system_state==Warm_state)
	{
		if(dsp_wendu>shuiwei_duibi+1)
		{
			shuiwei_duibi=dsp_wendu;
				if(shuiwei_time<410)   //相当于8S
				{
					shuiwei_dangwei=Low_water;
				}
				else
				{
					shuiwei_dangwei=High_water;
				}
			shuiwei_time=0;
		}
		else if(dsp_wendu<shuiwei_duibi)
		{
			shuiwei_duibi=dsp_wendu;
			shuiwei_time=0;
			shuiwei_dangwei=High_water;
		}
		else
		{
			if(shuiwei_time<60000)
			shuiwei_time++;
		}
	}
	else if(system_state==Work_state&&(Menu==TiaoNai||Menu==ReTiao))
	{
		if(dsp_wendu>shuiwei_duibi+1)
		{
			shuiwei_duibi=dsp_wendu;
				if(shuiwei_time<410)   //相当于8S
				{
					shuiwei_dangwei=Low_water;
				}
				else
				{
					shuiwei_dangwei=High_water;
				}
			shuiwei_time=0;
		}
		else if(dsp_wendu<shuiwei_duibi)
		{
			shuiwei_duibi=dsp_wendu;
			shuiwei_time=0;
			shuiwei_dangwei=High_water;
		}
		else
		{
			if(shuiwei_time<60000)
			shuiwei_time++;
		}
	}
	else
	{
		shuiwei_time=0;
		shuiwei_dangwei=0;
		shuiwei_duibi=0;
	}
}


uchar xdata gaoyuan_b;
uint xdata gaoyuan_time;
uchar xdata gaoyuan_temp;
void GaoYuan_deal()//高原处理
{
	if(Menu==TiaoNai||Menu==ReTiao)
	{
		gaoyuan_b=0;
		return;
	}
	if(dsp_way==dsp_time)return;
	if(adc_NTC_Temp>=80&&adc_NTC_Temp<100&&gaoyuan_b==0)
	{
		if(gaoyuan_temp!=dsp_wendu)
		{
			gaoyuan_temp=dsp_wendu;
			gaoyuan_time=0;
		}
		else
		{
			if(++gaoyuan_time>=Time_1Min)
			{
				gaoyuan_time=0;
				gaoyuan_b=1;
			}
		}
	}
	else if(adc_NTC_Temp<80)
	{
		gaoyuan_b=0;
		gaoyuan_time=0;
	}
	if(adc_NTC_Temp>gaoyuan_temp)
	{
		gaoyuan_b=0;
		gaoyuan_time=0;
	}
	if(gaoyuan_temp>adc_NTC_Temp+1)
	{
		gaoyuan_b=0;
		gaoyuan_time=0; 
	}
}




void Time(void)
{
	if(TiHu_b)return;
	if(system_state==YuYue_state)
	{
		if(++Fun_Time>=Time_1Min)
		{
			Fun_Time=0;
			YuYue_Time--;
		}
		
		if(!YuYue_Time)
		{
			system_state=Work_state;
			Fun_Time=0;
			Buz_Start(30,0,1);
			dsp_way=dsp_temp;
			YuYue_b=0;
		}
	}
	else if(system_state==Work_state&&Menu!=ZhuFei&&Menu!=ChuLv&&Menu!=TiaoNai&&Menu!=ReTiao&&start_time_b&&No_operation_Time>200)
	{
		if(++Fun_Time>=Time_1Min)
		{
			Fun_Time=0;
			Work_Time--;
		}
		
		if(!Work_Time)
		{
			Warm_Cnt=4320;
			Fun_Time=0;
			system_state=Warm_state;
			frist_baowen_temp=0;
			No_operation_Time=250;
			Buz_Start(30,0,1);
			du_97=0;
			BaoWen_JiaXian_100=1;
			duibi_time2=0;
		}
	}
	else if(system_state==Warm_state)
	{
		if(++Fun_Time>=Time_1Min)
		{
			Fun_Time=0;
			Warm_Cnt--;
		}
		if(!Warm_Cnt)
		{
			system_state=DaiJi_state;
			dsp_way=0;
			Buz_Start(30,30,3);
		}
	}
}

uchar xdata error_b;
uchar xdata error_b2;
uchar xdata TiHu_time;
uchar xdata TiHu_b;
uchar xdata TiHu_frist_buz;
uchar xdata FangHu_time;
uint xdata ChiXu_TiHu_time;
uint xdata fanDaiJi_Time;
uchar xdata E4_Time;
void error_deal()
{
	if(system_state==GuanJi_state)return;
	if(fanzhuan_time>=100)return;
	if(ad_NTC_value>=1010)//提壶判断
	{
		if(++TiHu_time>=30)//连续20次
		{
			TiHu_time=0;
			if(TiHu_b==0)
			{
				if(TiHu_frist_buz)
				Buz_Start(15,0,1);
			}
			change_time=0;
			TiHu_b=1;
			gaoyuan_time=0;
			gaoyuan_b=0;
		}
		FangHu_time=0;
	}
	else
	{
		if(++FangHu_time>=30)
		{
			FangHu_time=0;
			if(TiHu_b)
			{
			Buz_Start(15,0,1);
				GuanJi_time=0;
				if(adc_NTC_Temp>=100)
				dsp_wendu=100;
			else
			dsp_wendu=adc_NTC_Temp;
			}
			TiHu_b=0;
			TiHu_frist_buz=1;
		}
		TiHu_time=0;
	}
	
	if(TiHu_b&&(system_state==Work_state||system_state==YuYue_state||system_state==Warm_state))
	{
		if(++ChiXu_TiHu_time>=Time_2Min)
		{
			ChiXu_TiHu_time=0;
			system_state=GuanJi_state;
			Menu=0;
			dsp_way=0;
		}
	}
	else if(TiHu_b&&(system_state==DaiJi_state||system_state==Menu_state))
	{
		if(++ChiXu_TiHu_time>=Time_30S)
		{
			ChiXu_TiHu_time=0;
			system_state=GuanJi_state;
			Menu=0;
			dsp_way=0;
		}
	}
	else
	{
		ChiXu_TiHu_time=0;
	}
	
	
	
	if(ad_NTC_value<=30&&error_b==0&&error_b2==0) //NTC短路
	{
			error_b=2;
			Buz_Start(25,18,15);
	}
	else if(ad_NTC_value<=200&&error_b==0&&error_b2==0)//干烧
	{
			error_b=3;
			Buz_Start(25,18,15);
	}
	else if(Fan_state==0&&error_b==0&&error_b2==0&&Fan_b==0) //风扇开路
	{
		if(++E4_Time>=Time_1S)
		{
			error_b=4;
			Buz_Start(25,18,15);
		}
	}
	else
	{
		E4_Time=0;
	}

	if(error_b)
	{
		if(system_state==DaiJi_state||system_state==Menu_state)
		{
			error_b2=error_b;
			error_b=0;
			GuanJi_time=0;
		}
		else
				system_state=BaoJing_state;
	}
	if(system_state==BaoJing_state)
	{
		if(++fanDaiJi_Time>=Time_30S)
		{
			system_state=DaiJi_state;
			error_b2=error_b;
			error_b=0;
			Menu=0;
		}
	}
}











