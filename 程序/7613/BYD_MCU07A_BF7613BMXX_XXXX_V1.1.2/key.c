#include "Config.h"


void key_menu_deal();
void key_power_deal();
void key_setTime_deal(uchar select);
void key_setTime_Longdeal(uchar select);
void key_Fan_deal();
void key_Warm_deal();
uchar xdata key_deal;
uchar xdata key_count;

uchar xdata key_buz_b;
uchar xdata Menu;
uchar xdata baowen_temp;
uchar xdata temp_max;
uchar xdata temp_min;
ulong xdata key_value;
uchar xdata Fan_b;
uint  xdata ShangDian_Time;
uchar xdata Jian_baowen_xianzhi;
//#define ZhuFei  1
//#define ChuLv   2
//#define DunZhu  3
//#define YuYue   4
//#define TiaoNai 5
//#define ReTiao  6
//#define HuaCha  7
//#define WenHuo  8

unsigned char xdata baowen_1;
unsigned char xdata baowen_2;
unsigned char xdata baowen_3;
unsigned char xdata baowen_4;
unsigned char xdata baowen_5;
unsigned char xdata baowen_6;
unsigned char xdata baowen_7;
unsigned char xdata baowen_8;
unsigned char xdata baowen_9;
unsigned char xdata baowen_xiugai_b;
unsigned int xdata dunzhu_time;
unsigned int xdata huacha_time;
unsigned int xdata wenhuo_time;
code unsigned char SetTemp_Tel[]={0,100,100,100,0,45,55,100,100};
//code unsigned char SetTime_Tel[]={0,0,0,120,0,4320,4320,20,60};
//code unsigned char SetBaoWen_Tel[]={0,45,45,65,0,0,0,65,65};
uchar xdata SetBaoWen_Tel[15];
uint xdata SetTime_Tel[15];
//code unsigned char SetBaoWen_Tel[]={0,baowen_1,baowen_1,baowen_3,0,baowen_5,baowen_6,baowen_7,baowen_8};
code unsigned int Set_Max[]={0,100,100,240,1440,55,70,60,240};
code unsigned int Set_Min[]={0,100,100,60,30,35,50,20,60};

void shuzu_fuzhi(void)
{
	SetBaoWen_Tel[1]=baowen_1;
	SetBaoWen_Tel[2]=baowen_2;
	SetBaoWen_Tel[3]=baowen_3;
	SetBaoWen_Tel[5]=baowen_5;
	SetBaoWen_Tel[6]=baowen_6;
	SetBaoWen_Tel[7]=baowen_7;
	SetBaoWen_Tel[8]=baowen_8;
	SetBaoWen_Tel[9]=baowen_9;
	
	
	SetTime_Tel[3]=dunzhu_time;
	SetTime_Tel[7]=huacha_time;
	SetTime_Tel[8]=wenhuo_time;
}

void Key_duration(void)
{
	if(key_deal)
	{
		switch(keys_flag)
		{
			case key_add:
					if(key_count>120)
					{
						key_count=80;
						key_setTime_Longdeal(1);
					}
				break;
				
				case key_cut:
					if(key_count>120)
					{
						key_count=80;
						key_setTime_Longdeal(0);
					}
				break; 
		}
	}
	if(system_state==ZiJian_state)
	{
		if(keys_flag!=0)
		{	
			key_count++;
			if(key_deal)return;
			switch(keys_flag)
			{
				case key_menu:
					if(key_count>4)
					{
						if(++ZiJian_menu>2)ZiJian_menu=3;
						if(ZiJian_menu==3)
						{
								ZiJian_menu2=0;
								Temp_gear=4;
						}
						key_deal=1;
						key_buz_b=1;
					}
				break;
				
				case key_power:
					if(key_count>4)
					{
						if(ZiJian_menu==3)
						{
							ZiJian_menu2=1;
							key_deal=1;
							key_buz_b=1;
							Temp_gear=3;
						}
					}
				break;
				
				case key_add:
					if(key_count>4)
					{
						if(ZiJian_menu==3)
						{
							ZiJian_menu2=2;
							key_deal=1;
							key_buz_b=1;
							SET_Fan;
							Fan_b=1;
						}	
					}
				break;
				
				case key_cut:
					if(key_count>=200)
					{
						system_state=GuanJi_state;
						key_deal=1;
						key_buz_b=1;
					}
				break;
			}
			key_value=keys_flag;
		}
		else
		{
			if(key_value==key_cut)
			{
				if(key_count>4)
					{
						if(ZiJian_menu==3)
						{
							ZiJian_menu2=3;
							key_deal=1;
							key_buz_b=1;
						}	
					}
			}
			key_count=0;
			key_deal=0;
		}
	}
	else
	{
		if(keys_flag!=0)
		{	
			key_count++;
			if(key_deal)return;
			switch(keys_flag)
			{
				case key_zijian:
					if(ShangDian_Time>=Time_10S)return;
					if(key_count>=250)
					{
						system_state=ZiJian_state;
						key_deal=1;
						key_buz_b=1;
					}
				break;
				case key_menu:
					key_Warm_deal();
				break;
				
				case key_power:
						key_Fan_deal();
				break;
				
				case key_add:
					if(key_count>4)
					{
						key_setTime_deal(1);
					}
				break;
				
				case key_cut:
					if(key_count>4)
					{
						key_setTime_deal(0);
					}
				break;
			}
			key_value=keys_flag;
		}
		else
		{
			switch(key_value)
			{
				case key_power:
					if(key_count>4)
					key_power_deal();
				break;
					
				case key_menu:
					if(key_count>4)
					key_menu_deal();
				break;
			}
			key_value=0;
			key_deal=0;
			key_count=0;
		}
	}
}

void key_Warm_deal()
{
	if(error_b||error_b2)return;
	if(system_state!=DaiJi_state&&system_state!=Warm_state)return;
	if(key_count>=200)
	{
		key_count=0;
		if(system_state==DaiJi_state)
		{
		system_state=Warm_state;
			baowen_temp=baowen_9;
		Warm_Cnt=4320;
		Fun_Time=0;
		dsp_way=dsp_temp;
			if(dsp_wendu==baowen_temp)
				frist_baowen_temp=1;
			else
			frist_baowen_temp=0;
		No_operation_Time=250;
		}
		else if(system_state==Warm_state)
		system_state=DaiJi_state;	
		key_buz_b=1;
		key_deal=1;
		dsp_way=0;
		JiaXian_b=0;
	}
}

void key_Fan_deal()
{
	if(error_b||error_b2)return;
	//if(system_state!=DaiJi_state&&system_state!=Warm_state)return;
	if(system_state==DaiJi_state||system_state==Warm_state||Menu==TiaoNai||Menu==ReTiao)
	{
		if(key_count>=200)
		{
			key_count=0;
			key_deal=1;
			key_buz_b=1;
			GuanJi_time=0;
			switch(system_state)
			{
				case DaiJi_state:
				case Menu_state:
					if(Fan_b)
					{
						Fan_b=0;
						CLR_Fan;
					}
					else
					{
						Fan_b=1;
						SET_Fan;
					}
				break;
				case Work_state:
					if(dsp_wendu>set_temp)
					{
						if(Fan_b)
						{
							Fan_b=0;
							CLR_Fan;
						}
						else
						{
							Fan_b=1;
							SET_Fan;
						}
					}
				break;
				case Warm_state:
					if(dsp_wendu>baowen_temp)
					{
						if(Fan_b)
						{
							Fan_b=0;
							CLR_Fan;
						}
						else
						{
							Fan_b=1;
							SET_Fan;
						}
					}
				break;
			}
		}
	}
}

void key_menu_deal()
{
	if(system_state!=DaiJi_state&&system_state!=Menu_state&&system_state!=Work_state&&system_state!=Warm_state&&system_state!=YuYue_state)return;
	if(error_b||error_b2)return;
	if(TiHu_b)return;
	if(key_deal)return;
	if(system_state==Warm_state)
				Menu=0;
	if(++Menu>8)
	{
		Menu=1;
	}
	if(Menu==ZhuFei||Menu==ChuLv||Menu==TiaoNai||Menu==ReTiao)
				dsp_way=dsp_temp;
			else
				dsp_way=dsp_time;
			if(Menu==ReTiao||Menu==TiaoNai)
				set_temp=SetBaoWen_Tel[Menu];
			else
				set_temp=SetTemp_Tel[Menu];
	Work_Time=SetTime_Tel[Menu];
	baowen_temp=SetBaoWen_Tel[Menu];
//			if(system_state==YuYue_state)
//			{
//				YuYue_b=0;
//				YuYue_Time=0;
//			}
			
	system_state=Menu_state;
	QuFan_Time=0;
	QuFan_b=0;
	key_deal=1;
	No_operation_Time=0;
	key_buz_b=1;
	GuanJi_time=0;
	BaoWen_JiaXian_100=0;
	du_97=0;
	ChuLv_daojishi=0;
	JiaXian_b=0;
	feiteng_b=0;
	gaoyuan_b=0;
	gaoyuan_time=0;
	gaoyuan_No=0;
}

void key_power_deal()
{
	if(key_deal)return;
		switch(system_state)
	{
		case GuanJi_state:
		case BaoJing_state:
			system_state=DaiJi_state;
			fanDaiJi_Time=0;
			error_b2=error_b;
			error_b=0;
		  Menu=0;
//		  if(adc_NTC_Temp>=97)
//			dsp_wendu=adc_NTC_Temp;
		  Buz_Start(16,0,1);
		if(system_state==GuanJi_state)
		{
			error_b2=0;
			error_b=0;
		}
		break;
		
		case DaiJi_state:
		case Menu_state:
		case Work_state:
		case Warm_state:
		case YuYue_state:
			if(system_state!=DaiJi_state)
			{
			system_state=DaiJi_state;
			Buz_Start(16,0,1);
			}
			else
			{
			system_state=GuanJi_state;
			Fan_b=0;
			CLR_Fan;
			Buz_Start(60,0,1);
			}
			error_b=0;
	    fanDaiJi_Time=0;
			error_b2=0;
		break;
	}
			Work_Time=0;
		  YuYue_Time=0;
		  set_temp=0;
//		  set_time=0;
		  YuYue_b=0;
			key_deal=1;
			feiteng_b=0;
			//key_buz_b=1;
		  Menu=0;
			dsp_way=0;
			JiaXian_b=0;
	    gaoyuan_b=0;
			gaoyuan_time=0;
			GuanJi_time=0;
			ChiXu_TiHu_time=0;
			JiaXian_time=0;
			baowen_temp=0;
			BaoWen_JiaXian_100=0;
			du_97=0;
			ChuLv_daojishi=0;
    	gaoyuan_No=0;
}

void key_setTime_Longdeal(uchar select)
{
	if(error_b||error_b2)return;
	if(TiHu_b)return;
	
	if(system_state==Warm_state)
	{
//		key_deal=1;
		QuFan_Time=0;
		QuFan_b=0;
		BaoWen_Jia_time=0;
		warm_jiaxian_time=0;
		No_operation_Time=0;
		baowen_buz=1;
//		frist_baowen_temp=0;
//		if(JiaXian_b)
//		{
//		duibi_time=0;
//		dsp_wendu=baowen_temp;
//		}
		JiaXian_b=0;
		if(select)
		{
			if(baowen_temp>=95)
				baowen_temp=35;
			else
			{
				Jian_baowen_xianzhi=0;
				baowen_temp+=1;
			}
		}
		else
		{
			if(baowen_temp<=35)
				baowen_temp=95;
			else
			{
				baowen_temp-=1;
				Jian_baowen_xianzhi=1;
			}
		}
	}
	

	if((Menu==YuYue&&dsp_way==dsp_time)||system_state==YuYue_state)
	{
		if(select)
		{
			if(YuYue_Time>=1440)
				YuYue_Time=30;
			else
			{
				if(YuYue_Time%60<30&&YuYue_Time%60!=0)
					YuYue_Time+=(30-YuYue_Time%60);
				else if(YuYue_Time%60>30)
					YuYue_Time+=(60-YuYue_Time%60);
				else
				YuYue_Time+=30;
			}
		}
		else
		{
			if(YuYue_Time<=30)
				YuYue_Time=1440;
			else
			{
				if(YuYue_Time%60<30&&YuYue_Time%60!=0)
					YuYue_Time-=(YuYue_Time%60);
				else if(YuYue_Time%60>30)
					YuYue_Time-=(YuYue_Time%60);
				else
				YuYue_Time-=30;
			}
		}
//		YuYue_b=1;
//		key_deal=1;
		QuFan_Time=0;
		QuFan_b=0;
		return;
	}
	if(Menu==ZhuFei||Menu==ChuLv)return;
	if(system_state!=Menu_state&&Menu!=ReTiao&&Menu!=TiaoNai)return;
	 if(dsp_way==dsp_time&&Menu!=YuYue)
	{
		if(select)
		{
			if(Work_Time>=Set_Max[Menu])
			{
				Work_Time=Set_Min[Menu];
			}
			else
			{
				if(Menu==HuaCha)
				Work_Time+=5;	
				else
				Work_Time+=30;
			}
		}
		else
		{
			if(Work_Time<=Set_Min[Menu])
			{
				Work_Time=Set_Max[Menu];
			}
			else
			{
				if(Menu==HuaCha)
				Work_Time-=5;	
				else
				Work_Time-=30;
			}
		}
	}
	else if(dsp_way==dsp_temp)
	{
			if(select)
			{
				if(set_temp>=Set_Max[Menu])
				{
					set_temp=Set_Min[Menu];
				}
				else
				{
					set_temp+=1;
				}
			}
			else
			{
				if(set_temp<=Set_Min[Menu])
				{
					set_temp=Set_Max[Menu];
				}
				else
				{
					set_temp-=1;
				}
			}
	}
	No_operation_Time=0;
//	key_deal=1;
	GuanJi_time=0;
	QuFan_Time=0;
	QuFan_b=0;
}

void key_setTime_deal(uchar select)
{
	if(error_b||error_b2)return;
	if(TiHu_b)return;
	
	//if(system_state!=GuanJi_state&&system_state!=BaoJing_state)
	
	if(system_state==Warm_state)
	{
		key_deal=1;
		QuFan_Time=0;
		QuFan_b=0;
		BaoWen_Jia_time=0;
		warm_jiaxian_time=0;
		No_operation_Time=0;
		frist_baowen_temp=0;
		baowen_buz=1;
//		if(JiaXian_b)
//		{
//		duibi_time=0;
//		dsp_wendu=baowen_temp;
//		}
		JiaXian_b=0;
		if(select)
		{
			if(baowen_temp>=95)
				baowen_temp=35;
			else
			{
				Jian_baowen_xianzhi=0;
				baowen_temp+=1;
			}
		}
		else
		{
			if(baowen_temp<=35)
				baowen_temp=95;
			else
			{
				baowen_temp-=1;
				Jian_baowen_xianzhi=1;
			}
		}
		key_buz_b=1;
	}
	
	if((Menu==YuYue&&dsp_way==dsp_time)||system_state==YuYue_state)
	{
		if(select)
		{
			if(YuYue_Time>=1440)
				YuYue_Time=30;
			else
			{
				if(YuYue_Time%60<30&&YuYue_Time%60!=0)
					YuYue_Time+=(30-YuYue_Time%60);
				else if(YuYue_Time%60>30)
					YuYue_Time+=(60-YuYue_Time%60);
				else
				YuYue_Time+=30;
			}
		}
		else
		{
			if(YuYue_Time<=30)
				YuYue_Time=1440;
			else
			{
				if(YuYue_Time%60<30&&YuYue_Time%60!=0)
					YuYue_Time-=(YuYue_Time%60);
				else if(YuYue_Time%60>30)
					YuYue_Time-=(YuYue_Time%30);
				else
				YuYue_Time-=30;
			}
		}
		YuYue_b=1;
		key_buz_b=1;
		key_deal=1;
		QuFan_Time=0;
		QuFan_b=0;
		return;
	}
	if(Menu==ZhuFei||Menu==ChuLv)return;
	if(system_state!=Menu_state&&Menu!=ReTiao&&Menu!=TiaoNai)return;
	if(Menu==ZhuFei||Menu==ChuLv||Menu==TiaoNai||Menu==ReTiao)
				dsp_way=dsp_temp;
			else
				dsp_way=dsp_time;
	 if(dsp_way==dsp_time&&Menu!=YuYue)
	{
		if(select)
		{
			if(Work_Time>=Set_Max[Menu])
			{
				Work_Time=Set_Min[Menu];
			}
			else
			{
				if(Menu==HuaCha)
				Work_Time+=5;	
				else
				Work_Time+=30;
			}
		}
		else
		{
			if(Work_Time<=Set_Min[Menu])
			{
				Work_Time=Set_Max[Menu];
			}
			else
			{
				if(Menu==HuaCha)
				Work_Time-=5;	
				else
				Work_Time-=30;
			}
		}
	}
	else if(dsp_way==dsp_temp)
	{
		JiaXian_b=0;
			if(select)
			{
				if(set_temp>=Set_Max[Menu])
				{
					set_temp=Set_Min[Menu];
				}
				else
				{
					set_temp+=1;
				}
			}
			else
			{
				if(set_temp<=Set_Min[Menu])
				{
					set_temp=Set_Max[Menu];
				}
				else
				{
					set_temp-=1;
				}
			}
	}
//	system_state=Menu_state;
	key_buz_b=1;
	No_operation_Time=0;
	key_deal=1;
	GuanJi_time=0;
	QuFan_Time=0;
	QuFan_b=0;
	frist_baowen_temp=0;
	warm_jiaxian_time=0;
	baowen_buz=1;
}


void Key_handle(void)
{
	 if(key_buz_b)
	{
		key_buz_b=0;
		Buz_Start(12,0,1);
	}
}





