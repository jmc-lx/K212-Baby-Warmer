#include "Config.h"  //包含芯片寄存器、宏定义(SET_PB0_IO_OUT,SEG1等)

//各个系统状态对应的显示处理函数声明
void  dsp_ShangDian_deal();	//上电画面
void  dsp_DaiJi_deal();		//待机
void  dsp_Menu_deal();		//菜单选择
void dps_PaoMaLed_deal();	//跑马灯
void  dsp_Work_deal();		//加热工作
void Menu_LED_deal();		//功能菜单指示灯
void  dsp_YuYue_deal();	//预约模式
void  dsp_WarmPaoMa_deal();//保温跑马灯
void  dsp_Warm_deal();		//保温模式
void  dsp_error_deal();		//故障报错
void dsp_ZiJian_deal();		//自检模式
void ZiJianMenu_LED_deal();//自检指示灯
void  dsp_huxi_deal();		//呼吸灯
void DiYaLiKaiGuan_deal();	//低压力处理
void dsp_GuanJi_deal();		//关机

//xdata:8051 外部RAM，把大变量放到片外，节省内部RAM
unsigned char xdata  disp_scannum;		//点阵扫描-行号 0~7
unsigned char xdata  disp_scannum2;	//点阵扫描-列号 0~6
uchar xdata CL_Sec;						//除氯倒计时秒
uchar xdata CL_Min;						//除氯倒计时分
uint xdata GuanJi_time;					//无操作自动关机计时
uchar xdata disp_tel[DisData_Len];		//点阵原始显示缓存
uchar xdata disp_tel2[DisData_Len];	//点阵扫描专用缓存(拷贝disp_tel)
uchar xdata b_sys_5ms;					//5ms系统标志位
uchar xdata QuFan_b;					//闪烁标志位，0/1翻转，用来做LED闪烁
uint xdata YuYue_Time;					//预约剩余时间
uchar xdata YuYue_b;					//预约使能标记
uchar xdata dsp_way;					//显示模式：温度 /时间
uchar xdata set_temp;					//目标设定温度
uint xdata Work_Time;					//工作倒计时
uchar xdata dsp_wendu;					//屏幕显示温度(经过滤波、防抖后的温度，不是原始ADC)
uchar xdata duibi_time;					//温度偏差计时
uint xdata duibi_time2;
uchar xdata QuFan_Time;					//闪烁定时计数器
uchar xdata No_operation_Time;			//按键无操作计时
uchar xdata max_wendu;					//最高温度记录
uchar xdata buz_time_delay;				//蜂鸣器消抖延时
uchar xdata system_state;				//整机运行状态机：上电/待机/工作/保温/故障...
uchar xdata All_dspTime;				//上电画面保持时间
uint xdata JiaXian_time;				//温度加速爬升计时
uchar xdata du_97;						//温度>97℃标志(做沸腾延时逻辑)
uchar xdata BaoWen_JiaXian_100;			//保温温度补偿标志
uchar xdata BaoWen_Jia_time;			//保温计时
uchar xdata feiteng_b;					//水沸腾标记
//uchar xdata guoling_b;
//const unsigned int smg_tt[]={0,0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
//code unsigned int SMG_Tel_1[] = {SMG1_0,SMG1_1,SMG1_2,SMG1_3,SMG1_4,SMG1_5,SMG1_6,SMG1_7,SMG1_8,SMG1_9};

//const unsigned int SMG_Tel_2[] = {SMG2_0,SMG2_1,SMG2_2,SMG2_3,SMG2_4,SMG2_5,SMG2_6,SMG2_7,SMG2_8,SMG2_9};

//const unsigned int SMG_Tel_3[] = {SMG3_0,SMG3_1,SMG3_2,SMG3_3,SMG3_4,SMG3_5,SMG3_6,SMG3_7,SMG3_8,SMG3_9};

//const unsigned int SMG_Tel_4[] = {SMG4_0,SMG4_1,SMG4_2,SMG4_3,SMG4_4,SMG4_5,SMG4_6,SMG4_7,SMG4_8,SMG4_9};
void Disp_gpio_out_init()
{
	  
	
	SET_PB0_IO_IN;   
	SET_PB1_IO_IN;
	SET_PB2_IO_IN;
	SET_PB3_IO_IN;
	SET_PB4_IO_IN;
	SET_PB5_IO_IN;
	SET_PB6_IO_IN;
	SET_PB7_IO_IN;
	
		SET_SEG4;
		SET_SEG1;
		SET_SEG2;
		SET_SEG3;
		SET_SEG5;
		SET_SEG6;
		SET_SEG7;
		SET_SEG8;
}




void Delay_Us(uint us)//1--2.38us@12MHz;10-11.8us@12MHz;100-106us@12MHz;1000-1.045ms
{
	for (; us > 0; us--)
	{	
		WDT_CTRL = 0x07;
	}		
}





void Disp_scan(void)
{
		  								
	Disp_gpio_out_init();

	switch(disp_scannum)
	{
		case 0:
			SET_PB0_IO_OUT;
		SET_SEG1;
		switch(disp_scannum2)
		{
			case 0:
			if(disp_tel2[1]&0x01){
						 SET_PB1_IO_OUT;CLR_SEG2;
			}		
			disp_scannum2++;
			break;
			
			case 1:
			if(disp_tel2[2]&0x01){
						 SET_PB2_IO_OUT;CLR_SEG3;
			}
			disp_scannum2++;
			break;
			
			case 2:
			if(disp_tel2[3]&0x01){
						 SET_PB3_IO_OUT;CLR_SEG4;
			}
			disp_scannum2++;
			break;
			
			case 3:
			if(disp_tel2[4]&0x01){
						 SET_PB4_IO_OUT;CLR_SEG5;
			}
			disp_scannum2++;
			break;
			
			case 4:
			if(disp_tel2[5]&0x01){
						 SET_PB5_IO_OUT;CLR_SEG6;
			}
			disp_scannum2++;
			break;
			
			case 5:
			if(disp_tel2[6]&0x01){
						 SET_PB6_IO_OUT;CLR_SEG7;
			}
			disp_scannum2++;
			break;
			
			case 6:
			if(disp_tel2[7]&0x01){
						 SET_PB7_IO_OUT;CLR_SEG8;
			}	
			disp_scannum++;
			disp_scannum2=0;
			break;
		}
		break;
		
		case 1:
			SET_PB1_IO_OUT;
		SET_SEG2;
		switch(disp_scannum2)
		{
			case 0:
			if(disp_tel2[1]&0x02){
						 SET_PB0_IO_OUT;CLR_SEG1;
			}		
			disp_scannum2++;
			break;
			
			case 1:
			if(disp_tel2[2]&0x02){
						 SET_PB2_IO_OUT;CLR_SEG3;
			}
			disp_scannum2++;
			break;
			
			case 2:
			if(disp_tel2[3]&0x02){
						 SET_PB3_IO_OUT;CLR_SEG4;
			}
			disp_scannum2++;
			break;
			
			case 3:
			if(disp_tel2[4]&0x02){
						 SET_PB4_IO_OUT;CLR_SEG5;
			}
			disp_scannum2++;
			break;
			
			case 4:
			if(disp_tel2[5]&0x02){
						 SET_PB5_IO_OUT;CLR_SEG6;
			}
			disp_scannum2++;
			break;
			
			case 5:
			if(disp_tel2[6]&0x02){
						 SET_PB6_IO_OUT;CLR_SEG7;
			}
			disp_scannum2++;
			break;
			
			case 6:
			if(disp_tel2[7]&0x02){
						 SET_PB7_IO_OUT;CLR_SEG8;
			}	
			disp_scannum++;
			disp_scannum2=0;
			break;
		}
		break;
		
		case 2:
			SET_PB2_IO_OUT;
		SET_SEG3;
		switch(disp_scannum2)
		{
			case 0:
			if(disp_tel2[1]&0x04){
						 SET_PB0_IO_OUT;CLR_SEG1;
			}		
			disp_scannum2++;
			break;
			
			case 1:
			if(disp_tel2[2]&0x04){
						 SET_PB1_IO_OUT;CLR_SEG2;
			}
			disp_scannum2++;
			break;
			
			case 2:
			if(disp_tel2[3]&0x04){
						 SET_PB3_IO_OUT;CLR_SEG4;
			}
			disp_scannum2++;
			break;
			
			case 3:
			if(disp_tel2[4]&0x04){
						 SET_PB4_IO_OUT;CLR_SEG5;
			}
			disp_scannum2++;
			break;
			
			case 4:
			if(disp_tel2[5]&0x04){
						 SET_PB5_IO_OUT;CLR_SEG6;
			}
			disp_scannum2++;
			break;
			
			case 5:
			if(disp_tel2[6]&0x04){
						 SET_PB6_IO_OUT;CLR_SEG7;
			}
			disp_scannum2++;
			break;
			
			case 6:
			if(disp_tel2[7]&0x04){
						 SET_PB7_IO_OUT;CLR_SEG8;
			}	
			disp_scannum++;
			disp_scannum2=0;
			break;
		}
		break;
		
		case 3:
			SET_PB3_IO_OUT;
		SET_SEG4;
		switch(disp_scannum2)
		{
			case 0:
			if(disp_tel2[1]&0x08){
						 SET_PB0_IO_OUT;CLR_SEG1;
			}		
			disp_scannum2++;
			break;
			
			case 1:
			if(disp_tel2[2]&0x08){
						 SET_PB1_IO_OUT;CLR_SEG2;
			}
			disp_scannum2++;
			break;
			
			case 2:
			if(disp_tel2[3]&0x08){
						 SET_PB2_IO_OUT;CLR_SEG3;
			}
			disp_scannum2++;
			break;
			
			case 3:
			if(disp_tel2[4]&0x08){
						 SET_PB4_IO_OUT;CLR_SEG5;
			}
			disp_scannum2++;
			break;
			
			case 4:
			if(disp_tel2[5]&0x08){
						 SET_PB5_IO_OUT;CLR_SEG6;
			}
			disp_scannum2++;
			break;
			
			case 5:
			if(disp_tel2[6]&0x08){
						 SET_PB6_IO_OUT;CLR_SEG7;
			}
			disp_scannum2++;
			break;
			
			case 6:
			if(disp_tel2[7]&0x08){
						 SET_PB7_IO_OUT;CLR_SEG8;
			}	
			disp_scannum++;
			disp_scannum2=0;
			break;
		}
		break;
		
		case 4:
			SET_PB4_IO_OUT;
		SET_SEG5;
		switch(disp_scannum2)
		{
			case 0:
			if(disp_tel2[1]&0x10){
						 SET_PB0_IO_OUT;CLR_SEG1;
			}		
			disp_scannum2++;
			break;
			
			case 1:
			if(disp_tel2[2]&0x10){
						 SET_PB1_IO_OUT;CLR_SEG2;
			}
			disp_scannum2++;
			break;
			
			case 2:
			if(disp_tel2[3]&0x10){
						 SET_PB2_IO_OUT;CLR_SEG3;
			}
			disp_scannum2++;
			break;
			
			case 3:
			if(disp_tel2[4]&0x10){
						 SET_PB3_IO_OUT;CLR_SEG4;
			}
			disp_scannum2++;
			break;
			
			case 4:
			if(disp_tel2[5]&0x10){
						 SET_PB5_IO_OUT;CLR_SEG6;
			}
			disp_scannum2++;
			break;
			
			case 5:
			if(disp_tel2[6]&0x10){
						 SET_PB6_IO_OUT;CLR_SEG7;
			}
			disp_scannum2++;
			break;
			
			case 6:
			if(disp_tel2[7]&0x10){
						 SET_PB7_IO_OUT;CLR_SEG8;
			}	
			disp_scannum++;
			disp_scannum2=0;
			break;
		}
		break;
		
		case 5:
			SET_PB5_IO_OUT;
		SET_SEG6;
		switch(disp_scannum2)
		{
			case 0:
			if(disp_tel2[1]&0x20){
						 SET_PB0_IO_OUT;CLR_SEG1;
			}		
			disp_scannum2++;
			break;
			
			case 1:
			if(disp_tel2[2]&0x20){
						 SET_PB1_IO_OUT;CLR_SEG2;
			}
			disp_scannum2++;
			break;
			
			case 2:
			if(disp_tel2[3]&0x20){
						 SET_PB2_IO_OUT;CLR_SEG3;
			}
			disp_scannum2++;
			break;
			
			case 3:
			if(disp_tel2[4]&0x20){
						 SET_PB3_IO_OUT;CLR_SEG4;
			}
			disp_scannum2++;
			break;
			
			case 4:
			if(disp_tel2[5]&0x20){
						 SET_PB4_IO_OUT;CLR_SEG5;
			}
			disp_scannum2++;
			break;
			
			case 5:
			if(disp_tel2[6]&0x20){
						 SET_PB6_IO_OUT;CLR_SEG7;
			}
			disp_scannum2++;
			break;
			
			case 6:
			if(disp_tel2[7]&0x20){
						 SET_PB7_IO_OUT;CLR_SEG8;
			}	
			disp_scannum++;
			disp_scannum2=0;
			break;
		}
		break;
		
		case 6:
			SET_PB6_IO_OUT;
		SET_SEG7;
		switch(disp_scannum2)
		{
			case 0:
			if(disp_tel2[1]&0x40){
						 SET_PB0_IO_OUT;CLR_SEG1;
			}		
			disp_scannum2++;
			break;
			
			case 1:
			if(disp_tel2[2]&0x40){
						 SET_PB1_IO_OUT;CLR_SEG2;
			}
			disp_scannum2++;
			break;
			
			case 2:
			if(disp_tel2[3]&0x40){
						 SET_PB2_IO_OUT;CLR_SEG3;
			}
			disp_scannum2++;
			break;
			
			case 3:
			if(disp_tel2[4]&0x40){
						 SET_PB3_IO_OUT;CLR_SEG4;
			}
			disp_scannum2++;
			break;
			
			case 4:
			if(disp_tel2[5]&0x40){
						 SET_PB4_IO_OUT;CLR_SEG5;
			}
			disp_scannum2++;
			break;
			
			case 5:
			if(disp_tel2[6]&0x40){
						 SET_PB5_IO_OUT;CLR_SEG6;
			}
			disp_scannum2++;
			break;
			
			case 6:
			if(disp_tel2[7]&0x40){
						 SET_PB7_IO_OUT;CLR_SEG8;
			}	
			disp_scannum++;
			disp_scannum2=0;
			break;
		}
		break;
		
		case 7:
			SET_PB7_IO_OUT;
		SET_SEG8;
		switch(disp_scannum2)
		{
			case 0:
			if(disp_tel2[1]&0x80){
						 SET_PB0_IO_OUT;CLR_SEG1;
			}		
			disp_scannum2++;
			break;
			
			case 1:
			if(disp_tel2[2]&0x80){
						 SET_PB1_IO_OUT;CLR_SEG2;
			}
			disp_scannum2++;
			break;
			
			case 2:
			if(disp_tel2[3]&0x80){
						 SET_PB2_IO_OUT;CLR_SEG3;
			}
			disp_scannum2++;
			break;
			
			case 3:
			if(disp_tel2[4]&0x80){
						 SET_PB3_IO_OUT;CLR_SEG4;
			}
			disp_scannum2++;
			break;
			
			case 4:
			if(disp_tel2[5]&0x80){
						 SET_PB4_IO_OUT;CLR_SEG5;
			}
			disp_scannum2++;
			break;
			
			case 5:
			if(disp_tel2[6]&0x80){
						 SET_PB5_IO_OUT;CLR_SEG6;
			}
			disp_scannum2++;
			break;
			
			case 6:
			if(disp_tel2[7]&0x80){
						 SET_PB6_IO_OUT;CLR_SEG7;
			}	
			disp_scannum=0;
			disp_scannum2=0;
			break;
		}	
		break;
	}

	  	
	}


void Disp_handle(void)
{
		disp_tel2[0] =disp_tel[0];
		disp_tel2[1] =disp_tel[1];
		disp_tel2[2] =disp_tel[2];
		disp_tel2[3] =disp_tel[3];
		disp_tel2[4] =disp_tel[4];
		disp_tel2[5] =disp_tel[5];
		disp_tel2[6] =disp_tel[6];
		disp_tel2[7] =disp_tel[7];
		disp_tel2[8] =disp_tel[8];
}

void Disp_All_Close(void)
{
	disp_tel[0] = 0;
	disp_tel[1] = 0;
	disp_tel[2] = 0;
	disp_tel[3] = 0;
	disp_tel[4] = 0;
	disp_tel[5] = 0;	
	disp_tel[6] = 0;
	disp_tel[7] = 0;
	disp_tel[8] = 0;
	disp_tel[9] = 0;
	disp_tel[11] = 0;
	disp_tel[12] = 0;
	disp_tel[13] = 0;
	disp_tel[14] = 0;	
	disp_tel[15] = 0;	
}

void Disp_All_Open(void)
{
	disp_tel[0] = 0xff;
	disp_tel[1] = 0xff;
	disp_tel[2] = 0xff;
	disp_tel[3] = 0xff;
	disp_tel[4] = 0xff;
	disp_tel[5] = 0xff;	
	disp_tel[6] = 0xff;
	disp_tel[7] = 0xff;
	disp_tel[8] = 0xff;
	disp_tel[9] = 0xff;
	disp_tel[11] = 0xff;
	disp_tel[12] = 0xff;
	disp_tel[13] = 0xff;
	disp_tel[14] = 0xff;	
	disp_tel[15] = 0xff;	
}






void SMG_deal(uchar number,uchar weizhi)
{
	switch(number)
	{
		case 0:
		switch(weizhi)
		{
			case 1:
			A_SMG1; B_SMG1; C_SMG1; D_SMG1; E_SMG1; F_SMG1;
			break;
			case 2:
			A_SMG2; B_SMG2; C_SMG2; D_SMG2; E_SMG2; F_SMG2;
			break;
			case 3:
			A_SMG3; B_SMG3; C_SMG3; D_SMG3; E_SMG3; F_SMG3;
			break;
			case 4:
			A_SMG4; B_SMG4; C_SMG4; D_SMG4; E_SMG4; F_SMG4;
			break;
			case 5:
			A_SMG5; B_SMG5; C_SMG5; D_SMG5; E_SMG5; F_SMG5;
			break;
			case 6:
			A_SMG6; B_SMG6; C_SMG6; D_SMG6; E_SMG6; F_SMG6;
			break;
		}
		break;
		
		case 1:
		switch(weizhi)
		{
			case 1:
			B_SMG1;C_SMG1;
			break;
			case 2:
			B_SMG2;C_SMG2;
			break;
			case 3:
			B_SMG3;C_SMG3;
			break;
			case 4:
			B_SMG4;C_SMG4;
			break;
			case 5:
			B_SMG5;C_SMG5;
			break;
			case 6:
			B_SMG6;C_SMG6;
			break;
		}
		break;
		
		case 2:
		switch(weizhi)
		{
			case 1:
			A_SMG1; B_SMG1; G_SMG1; E_SMG1; D_SMG1;
			break;
			case 2:
			A_SMG2; B_SMG2; G_SMG2; E_SMG2; D_SMG2;
			break;
			case 3:
			A_SMG3; B_SMG3; G_SMG3; E_SMG3; D_SMG3;
			break;
			case 4:
			A_SMG4; B_SMG4; G_SMG4; E_SMG4; D_SMG4;
			break;
			case 5:
			A_SMG5; B_SMG5; G_SMG5; E_SMG5; D_SMG5;
			break;
			case 6:
			A_SMG6; B_SMG6; G_SMG6; E_SMG6; D_SMG6;
			break;
		}
		break;
		
		case 3:
			switch(weizhi)
		{
			case 1:
			A_SMG1; B_SMG1; G_SMG1; C_SMG1; D_SMG1;
			break;
			case 2:
			A_SMG2; B_SMG2; G_SMG2; C_SMG2; D_SMG2;
			break;
			case 3:
			A_SMG3; B_SMG3; G_SMG3; C_SMG3; D_SMG3;
			break;
			case 4:
			A_SMG4; B_SMG4; G_SMG4; C_SMG4; D_SMG4;
			break;
			case 5:
			A_SMG5; B_SMG5; G_SMG5; C_SMG5; D_SMG5;
			break;
			case 6:
			A_SMG6; B_SMG6; G_SMG6; C_SMG6; D_SMG6;
			break;
		}		
		break;
			
		case 4:
			switch(weizhi)
		{
			case 1:
			B_SMG1; G_SMG1; F_SMG1; C_SMG1;
			break;
			case 2:
			B_SMG2; G_SMG2; F_SMG2; C_SMG2;
			break;
			case 3:
			B_SMG3; G_SMG3; F_SMG3; C_SMG3;
			break;
			case 4:
			B_SMG4; G_SMG4; F_SMG4; C_SMG4;
			break;
			case 5:
			B_SMG5; G_SMG5; F_SMG5; C_SMG5;
			break;
			case 6:
			B_SMG6; G_SMG6; F_SMG6; C_SMG6;
			break;
		}	
		break;
		
		case 5:
			switch(weizhi)
		{
			case 1:
			A_SMG1; F_SMG1; G_SMG1; C_SMG1; D_SMG1;
			break;
			case 2:
			A_SMG2; F_SMG2; G_SMG2; C_SMG2; D_SMG2;
			break;
			case 3:
			A_SMG3; F_SMG3; G_SMG3; C_SMG3; D_SMG3;
			break;
			case 4:
			A_SMG4; F_SMG4; G_SMG4; C_SMG4; D_SMG4;
			break;
			case 5:
			A_SMG5; F_SMG5; G_SMG5; C_SMG5; D_SMG5;
			break;
			case 6:
			A_SMG6; F_SMG6; G_SMG6; C_SMG6; D_SMG6;
			break;
		}	
		break;
		
		case 6:
			switch(weizhi)
		{
			case 1:
			A_SMG1; F_SMG1; G_SMG1; C_SMG1; D_SMG1; E_SMG1;
			break;
			case 2:
			A_SMG2; F_SMG2; G_SMG2; C_SMG2; D_SMG2; E_SMG2;
			break;
			case 3:
			A_SMG3; F_SMG3; G_SMG3; C_SMG3; D_SMG3; E_SMG3;
			break;
			case 4:
			A_SMG4; F_SMG4; G_SMG4; C_SMG4; D_SMG4; E_SMG4;
			break;
			case 5:
			A_SMG5; F_SMG5; G_SMG5; C_SMG5; D_SMG5; E_SMG5;
			break;
			case 6:
			A_SMG6; F_SMG6; G_SMG6; C_SMG6; D_SMG6; E_SMG6;
			break;
		}	
		break;
		
		case 7:
			switch(weizhi)
		{
			case 1:
			A_SMG1; B_SMG1; C_SMG1;
			break;
			case 2:
			A_SMG2; B_SMG2; C_SMG2;
			break;
			case 3:
			A_SMG3; B_SMG3; C_SMG3;
			break;
			case 4:
			A_SMG4; B_SMG4; C_SMG4;
			break;
			case 5:
			A_SMG5; B_SMG5; C_SMG5;
			break;
			case 6:
			A_SMG6; B_SMG6; C_SMG6;
			break;
		}
		break;
		
		case 8:
			switch(weizhi)
		{
			case 1:
			A_SMG1; B_SMG1; C_SMG1; D_SMG1; E_SMG1; F_SMG1; G_SMG1;
			break;
			case 2:
			A_SMG2; B_SMG2; C_SMG2; D_SMG2; E_SMG2; F_SMG2; G_SMG2;
			break;
			case 3:
			A_SMG3; B_SMG3; C_SMG3; D_SMG3; E_SMG3; F_SMG3; G_SMG3;
			break;
			case 4:
			A_SMG4; B_SMG4; C_SMG4; D_SMG4; E_SMG4; F_SMG4; G_SMG4;
			break;
			case 5:
			A_SMG5; B_SMG5; C_SMG5; D_SMG5; E_SMG5; F_SMG5; G_SMG5;
			break;
			case 6:
			A_SMG6; B_SMG6; C_SMG6; D_SMG6; E_SMG6; F_SMG6; G_SMG6;
			break;
		}				
		break;	
		
		case 9:
			switch(weizhi)
		{
			case 1:
			A_SMG1; B_SMG1; C_SMG1; D_SMG1; F_SMG1; G_SMG1;
			break;
			case 2:
			A_SMG2; B_SMG2; C_SMG2; D_SMG2; F_SMG2; G_SMG2;
			break;
			case 3:
			A_SMG3; B_SMG3; C_SMG3; D_SMG3; F_SMG3; G_SMG3;
			break;
			case 4:
			A_SMG4; B_SMG4; C_SMG4; D_SMG4; F_SMG4; G_SMG4;
			break;
			case 5:
			A_SMG5; B_SMG5; C_SMG5; D_SMG5; F_SMG5; G_SMG5;
			break;
			case 6:
			A_SMG6; B_SMG6; C_SMG6; D_SMG6; F_SMG6; G_SMG6;
			break;
		}		
		break;	
	}
}


void Dsp_left_deal(uint three)
{
//	left_bai=three/100;
//	left_shi=three%100/10;
//	left_ge =three%10;
	if(three>=100)
	SMG_deal(three/100,1);
	SMG_deal(three%100/10,2);
	SMG_deal(three%10,3);
}


void Dsp_right_deal(uint three)
{
//	right_bai=three/100;
//	right_shi=three%100/10;
//	right_ge =three%10;
	if(three>=100)
	SMG_deal(three/100,4);
	SMG_deal(three%100/10,5);
	SMG_deal(three%10,6);
}

void Dsp_Time(uint three)
{
	SMG_deal(three/60/10,2);
	SMG_deal(three/60%10,3);
	SMG_deal(three%60/10,5);
	SMG_deal(three%60%10,6);
}

void dsp_ad(uint four)
{
	SMG_deal(four/1000,3);
	SMG_deal(four%1000/100,4);
	SMG_deal(four%100/10,5);
	SMG_deal(four%10,6);
}

//void  Disp(void)
//{
//	//disp_tel[1] |=0xff;
//	Disp_All_Close();
////	disp_tel[1]|=0x18;
//	Dsp_left_deal(788);
//	Dsp_right_deal(hjdhjd);
////	disp_tel[1]=smg_tt[key_cnt];
////	Disp_All_Open();
//	//disp_tel2[2]=DISP_E;
//	//disp_tel2[3]=DISP_C;
//	//DisFourU16(key_num);
//}

void QuFan(void)
{
	if(++QuFan_Time>=Time_500mS)
	{
		QuFan_Time=0;
		QuFan_b=~QuFan_b;
	}
}

void Menu_Led_deal()
{
	if(Menu==ZhuFei)	LED_ZhuFei;
	
	else if(Menu==ChuLv)  LED_ChuLv;
	
	else if(Menu==DunZhu)  LED_DunZhu;
	
	else if(Menu==YuYue)  LED_YuYue;
	
	else if(Menu==TiaoNai)  LED_TiaoNai;
	
	else if(Menu==ReTiao)  LED_ReTiao;
	
	else if(Menu==HuaCha)  LED_HuaCha;
	
	else if(Menu==WenHuo)  LED_WenHuo;
//	switch(Menu)
//		{
//		case ZhuFei:
//			LED_ZhuFei;
//		break;
//		
//		case ChuLv:
//			LED_ChuLv;
//		break;
//		
//		case DunZhu:
//			LED_DunZhu;
//		break;
//		
//		case YuYue:
//			LED_YuYue;
//		break;
//		
//		case TiaoNai:
//			LED_TiaoNai;
//		break;
//		
//		case ReTiao:
//			LED_ReTiao;
//		break;
//		
//		case HuaCha:
//			LED_HuaCha;
//		break;
//		
//		case WenHuo:
//			LED_WenHuo;
//		break;
//		}
}	

void  Disp(void)
{
	if(No_operation_Time<250)No_operation_Time++;
	if(No_operation_Time>=199)
	{
		if(Menu==DunZhu||Menu==HuaCha||Menu==WenHuo)
		{
			if(feiteng_b)
				dsp_way=dsp_time;
			else
				dsp_way=dsp_temp;
		}
	}
	if(++BaoWen_Jia_time>=200)BaoWen_Jia_time=220;
	if(++ShangDian_Time>=Time_10S)ShangDian_Time=Time_12S;
	if(Buz_Begin_b)buz_time_delay=0;
	if(buz_time_delay<250)buz_time_delay++;
if(!Buz_Begin_b&&buz_time_delay>=7&&system_state!=GuanJi_state)
{
	if(gaoyuan_b&&dsp_wendu>94)  //高原假显逻辑处理
	{
		if(++JiaXian_time>=Time_3S)
		{
			JiaXian_time=0;
			if(dsp_wendu<100)
				dsp_wendu++;
		}
	}
	else           //正常显示逻辑处理
	{
		if(dsp_wendu>=97&&adc_NTC_Temp>=95&&system_state==Work_state&&Menu!=TiaoNai&&Menu!=ReTiao)
		{
			du_97=1;
		}
		else if(adc_NTC_Temp<95&&du_97)
		{
			du_97=0;
			//dsp_wendu=adc_NTC_Temp;
			gaoyuan_time=0;
		}
		if(system_state!=Work_state)du_97=0;
		if(du_97)  //97度后开始假显
		{
			if(adc_NTC_Temp>dsp_wendu&&adc_NTC_Temp<=100)
			{
				dsp_wendu=adc_NTC_Temp;
				JiaXian_time=0;
			}
				if(++JiaXian_time>Time_11S)
			{
				JiaXian_time=0;
				if(dsp_wendu<100)
					dsp_wendu++;
			}
		}
		else
		{
			if(BaoWen_JiaXian_100)
			{
					if(dsp_wendu>adc_NTC_Temp+3)
				{
					if(++duibi_time>=Time_3S)
					{
						duibi_time=0;
						BaoWen_JiaXian_100=0;
					}
				}
				else if(dsp_wendu<=adc_NTC_Temp)
				{
					if(++duibi_time>=Time_3S)
					{
						duibi_time=0;
						BaoWen_JiaXian_100=0;
					}
				}
				else
				{
					duibi_time=0;
				}
				if(dsp_wendu!=adc_NTC_Temp)
				{
						 if(dsp_wendu>adc_NTC_Temp)
						{
							if(++duibi_time2>=Time_15S)
								{
									duibi_time2=0;
									dsp_wendu--;
								}
						}
				}
			}
			else
			{
				if(dsp_wendu!=adc_NTC_Temp&&JiaXian_b==0)
				{
					if((dsp_wendu>adc_NTC_Temp+3||dsp_wendu<adc_NTC_Temp-3)&&adc_NTC_Temp<98)
					{
						Jian_baowen_xianzhi=0;
					}
					if((dsp_wendu>adc_NTC_Temp+7||dsp_wendu<adc_NTC_Temp-7))
					{
						if(++duibi_time>=10)
						{
								duibi_time=0;
						    Jian_baowen_xianzhi=0;
								if(adc_NTC_Temp>=100)
								dsp_wendu=100;
								else
								dsp_wendu=adc_NTC_Temp;
								return;
						}
					}
					 if(dsp_wendu>adc_NTC_Temp&&BaoWen_Jia_time>=210)
					{
						if(++duibi_time>=Time_3S)
							{
								duibi_time=0;
								dsp_wendu--;
								Jian_baowen_xianzhi=0;
							}
					}
					else if(dsp_wendu<adc_NTC_Temp&&BaoWen_Jia_time>=210&&Jian_baowen_xianzhi==0)
					{
						if(++duibi_time>=Time_3S)
						{
							duibi_time=0;
							if(dsp_wendu<100)
							dsp_wendu++;
							max_wendu=dsp_wendu;
						}
					}
				}
				else
				{
					duibi_time=0;
				}
			}
		}
	}
}
		

	Disp_All_Close();
if(system_state!=Warm_state&&Menu!=TiaoNai&&Menu!=ReTiao)
{
	baowen_buz=0;
}
	 switch(system_state)
   {
	   case ShangDian_state:      //上电显示
	   dsp_ShangDian_deal();
	   break;
		 
		 case GuanJi_state:         //关机显示
		 dsp_GuanJi_deal();
		 break;
	   
	   case DaiJi_state:          //待机显示
	   dsp_DaiJi_deal();
	   break;
	   
	   case Menu_state:           //菜单状态显示
	   dsp_Menu_deal();
	   break;
	   
	   case Work_state:           //工作状态显示
	   dsp_Work_deal();
	   break;
	   
	   case Warm_state:           //保温状态显示
	   dsp_Warm_deal();
	   break;
	   
	   case ZiJian_state:          //自检状态显示
	   dsp_ZiJian_deal();
	   break;
	   
	   case BaoJing_state:         //报警状态显示
	   dsp_error_deal();
	   break;
	   
	   case YuYue_state:           //预约状态显示
	   dsp_YuYue_deal();
	   break;
   }
}

uchar shangdian_buz;
void  dsp_ShangDian_deal()
{
	if(shangdian_buz==0)
	{
		shangdian_buz=1;
		Buz_Start(70,10,1);
	}
	if(++All_dspTime>=70)
	{
		system_state=GuanJi_state;	
	}
	Disp_All_Open();
}	


void dsp_GuanJi_deal()
{
//	Dsp_left_deal(Fan_state);
//	if(zero_pro_b==0)
//		LED1;
//	CLR_Heat;
//	LED_WenHuo;
		if(QuFan_b==0)LED_Power;
//	dsp_ad(ad_NTC_value);
}	



void  dsp_DaiJi_deal()
{
	
  G_SMG5;G_SMG6;
	if(Fan_b)
	{
		if(QuFan_b==0)
			LED_Power;
	}
	else
		LED_Power;
	
	if(Fan_b==0)
	{
		if(++GuanJi_time>=Time_30S)
		{
			GuanJi_time=0;
			error_b2=0;
			system_state=GuanJi_state;
			Buz_Start(20,0,1);
		}
	}
	if(error_b2)
	{
			switch(error_b2)
		{
			case 1:
				error_E;
				error_1;
			break;
			
			case 2:
				error_E;
				error_2;
			break;
			
			case 3:
				error_E;
				error_3;
			break;
			
			case 4:
				error_E;
				error_4;
			break;
		}
		return;
	}
	if(TiHu_b&&error_b2==0)
	{
		error_E;
		error_1;
		return;
	}
	Dsp_left_deal(dsp_wendu);
}

void  dsp_Menu_deal()
{
	LED_Power;
	if(TiHu_b)
	{
		error_E;
		error_1;
		G_SMG5;G_SMG6;
		return;
	}
	if(Menu==YuYue)
	{
		if(++GuanJi_time>=Time_1Min)
		{
			GuanJi_time=0;
			system_state=DaiJi_state;
			Menu=0;
			dsp_way=0;
			No_operation_Time=0;
			YuYue_b=0;
			YuYue_Time=0;
			//Buz_Start(20,0,1);
		}
	}
	
	if(Menu!=YuYue)
	{
		if(No_operation_Time>Time_4S)
		{
			//No_operation_Time=0;
			if(YuYue_b)	
				system_state=YuYue_state;
			else
				system_state=Work_state;
			Buz_Start(16,20,2);
//			if(adc_NTC_Temp>=100)
//				dsp_wendu=100;
//			else
//			dsp_wendu=adc_NTC_Temp;
//			Work_Time=set_time;
			dsp_way=dsp_temp;
			Fan_b=0;
			CLR_Fan;
			r_cook_step=0;
			BaoWen_JiaXian_100=0;
			gaoyuan_time=0;
			change_time=0;
			JiaXian_time=0;
			start_time_b=0;
			feiteng_b=0;
			frist_baowen_temp=0;
			warm_jiaxian_time=0;
			gaoyuan_No=0;
			Fun_Time=0;
			if(Menu==DunZhu)
				dunzhu_time=Work_Time;
			else if(Menu==HuaCha)
				huacha_time=Work_Time;
			else if(Menu==WenHuo)
				wenhuo_time=Work_Time;
		}
	}
	if(dsp_way==dsp_temp)
	{
		Dsp_left_deal(dsp_wendu);
		if(Menu==TiaoNai||Menu==ReTiao)
		{
			if(QuFan_b==0)
			Dsp_right_deal(set_temp);
		}
		else
		Dsp_right_deal(set_temp);	
	}
	else if(dsp_way==dsp_time&&QuFan_b==0)
	{
		if(Menu==YuYue)
		Dsp_Time(YuYue_Time);
		else
		Dsp_Time(Work_Time);
	}
	if(QuFan_b==0)
	Menu_Led_deal();
	if(YuYue_b&&Menu!=YuYue)LED_YuYue;
}

void  dsp_Work_deal()
{
//	if(No_operation_Time<250)No_operation_Time++;
	
	if(TiHu_b)//工作中的提壶显示
	{
		error_E;
		error_1;
		G_SMG5;G_SMG6;
	}
	else //没提壶的正常显示
	{
		if(dsp_way==dsp_temp)
		{
				if(JiaXian_b)
			{
			Dsp_left_deal(set_temp);
			Dsp_right_deal(set_temp);
				dsp_wendu=set_temp;
				duibi_time=0;
			}
			else
			{
				if(ChuLv_daojishi)
				{
					Dsp_left_deal(CL_Min);
					Dsp_right_deal(CL_Sec);
				}
				else
				{
					if(No_operation_Time<200)
					{
						Dsp_left_deal(dsp_wendu);
						if(QuFan_b==0)
						Dsp_right_deal(set_temp);	
					}
					else
					{
						if(Menu==TiaoNai)
						baowen_5=set_temp;
						else if(Menu==ReTiao)
						baowen_6=set_temp;
						Dsp_left_deal(dsp_wendu);
						Dsp_right_deal(set_temp);
							if(baowen_buz)
						{
							baowen_buz=0;
							Buz_Start(16,20,2);
						}
					}
				}
			}
		}
		else if(dsp_way==dsp_time)
		{
			if(No_operation_Time<200)
			{
				if(QuFan_b==0)
			  Dsp_Time(Work_Time);
				if(Menu==DunZhu)
				dunzhu_time=Work_Time;
			else if(Menu==HuaCha)
				huacha_time=Work_Time;
			else if(Menu==WenHuo)
				wenhuo_time=Work_Time;
			}
			else
			{
				Dsp_Time(Work_Time);	
			}
		}
	}
	Menu_Led_deal();
	LED_Power;
}

void dsp_YuYue_deal()
{
	LED_Power;
	Dsp_Time(YuYue_Time);
	Menu_Led_deal();
	LED_YuYue;
}

uchar xdata baowen_buz;
void dsp_Warm_deal()
{
	//Menu=0;
	if(TiHu_b)//工作中的提壶显示
	{
		error_E;
		error_1;
		G_SMG5;G_SMG6;
		return;
	}
	if(Fan_b)
	{
		if(QuFan_b==0)
			LED_Power;
	}
	else
		LED_Power;
//  if(No_operation_Time<250)No_operation_Time++;
	if(No_operation_Time<200)
	{
		Dsp_left_deal(dsp_wendu);
		if(QuFan_b==0)
		{
			Dsp_right_deal(baowen_temp);
		}
	}
	else
	{
		if(Menu==ZhuFei)
			baowen_1=baowen_temp;
		else if(Menu==ChuLv)
			baowen_2=baowen_temp;
		else if(Menu==DunZhu)
			baowen_3=baowen_temp;
		else if(Menu==HuaCha)
			baowen_7=baowen_temp;
		else if(Menu==WenHuo)
			baowen_8=baowen_temp;
		else 
			baowen_9=baowen_temp;
		if(baowen_buz)
		{
			baowen_buz=0;
			Buz_Start(16,20,2);
		}
		if(JiaXian_b)
		{
		Dsp_left_deal(baowen_temp);
		Dsp_right_deal(baowen_temp);
			dsp_wendu=baowen_temp;
				duibi_time=0;
		}
		else 
		{
		Dsp_left_deal(dsp_wendu);
		Dsp_right_deal(baowen_temp);
		}
	}
	
}

void dsp_error_deal()
{
	LED_Power;
	switch(error_b)
	{
		case 1:
			error_E;
			error_1;
		break;
		
		case 2:
			error_E;
			error_2;
		break;
		
		case 3:
			error_E;
			error_3;
		break;
		
		case 4:
			error_E;
			error_4;
		break;
	}
	Menu_Led_deal();
	G_SMG5;G_SMG6;
}
uchar xdata ZiJian_menu;
uchar xdata ZiJian_menu2;
void dsp_ZiJian_deal()
{
	if(TiHu_b)//工作中的提壶显示
	{
		error_E;
		error_1;
		G_SMG5;G_SMG6;
		return;
	}
	if(ZiJian_menu2!=2)
	{
		CLR_Fan;
		Fan_b=0;
	}
	if(ZiJian_menu2!=0&&ZiJian_menu2!=1)
	{
		Temp_gear=0;
	}
	LED_Power;
	switch(ZiJian_menu)
	{
		case 0:
		ZiJian_1;	
		ZiJian_U;
		ZiJian_0;
		ZiJian_5;
		break;
		
		case 1:
		Dsp_right_deal(dsp_wendu);
		break;
		
		case 2:
		Disp_All_Open();
		break;
		
		case 3:
			switch(ZiJian_menu2)
			{
				case 0:
				Dsp_left_deal(111);	
				Dsp_right_deal(111);	
				break;
				
				case 1:
				Dsp_left_deal(222);	
				Dsp_right_deal(222);	
				break;
				
				case 2:
				Dsp_left_deal(333);	
				Dsp_right_deal(333);	
				break;
				
				case 3:
				Dsp_left_deal(444);	
				Dsp_right_deal(444);	
				break;
			}
		break;
	}
}
