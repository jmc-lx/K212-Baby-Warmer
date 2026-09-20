#ifndef __LED_H__
#define __LED_H__

//#include "main.h"


#define SEGA	0X01
#define SEGB	0x02
#define SEGC	0x04
#define SEGD	0x08
#define SEGE	0x10
#define SEGF	0x20
#define SEGG	0x40
#define SEGH	0x80


//#define    CLR_COM1       PB0=0  
//#define    CLR_COM2       PB1=0 
//#define    CLR_COM3       PB2=0    
//#define    CLR_COM4       PB3=0    
//#define    CLR_COM5       PH7=0   
//#define    CLR_COM6       PE6=0  
                          
#define    CLR_SEG1       PB0=0    
#define    CLR_SEG2       PB1=0    
#define    CLR_SEG3       PB2=0    
#define    CLR_SEG4       PB3=0    
#define    CLR_SEG5       PB4=0    
#define    CLR_SEG6       PB5=0    
#define    CLR_SEG7       PB6=0    
#define    CLR_SEG8       PB7=0  
      




//#define    SET_COM1        PB0=1    
//#define    SET_COM2        PB1=1    
//#define    SET_COM3        PB2=1    
//#define    SET_COM4        PB3=1    
//#define    SET_COM5        PH7=1  
//#define    SET_COM6        PE6=1 

#define    SET_SEG1        PB0=1    
#define    SET_SEG2        PB1=1    
#define    SET_SEG3        PB2=1    
#define    SET_SEG4        PB3=1    
#define    SET_SEG5        PB4=1    
#define    SET_SEG6        PB5=1    
#define    SET_SEG7        PB6=1 
#define    SET_SEG8        PB7=1   

#define left1_1    SEGD|SEGE|SEGF
#define left1_2    SEGA|SEGD|SEGE|SEGF
#define left1_3    SEGA|SEGD|SEGE|SEGF
#define left1_4    SEGA|SEGD|SEGE|SEGF
#define left1_5    SEGA|SEGD|SEGE|SEGF
#define left1_6    SEGA|SEGD|SEGE|SEGF
#define left1_7    SEGA|SEGD|SEGE|SEGF
#define left1_8    SEGA|SEGD|SEGE|SEGF
#define left1_9    SEGA|SEGD|SEGE|SEGF
#define left1_10   SEGA|SEGE|SEGF
#define left1_11   SEGA|SEGD|SEGF
#define left1_12   SEGA|SEGD|SEGE

#define left2_1    SEGA|SEGD
#define left2_2    SEGD
#define left2_3    SEGA|SEGD
#define left2_4    SEGA|SEGD
#define left2_5    SEGA|SEGD
#define left2_6    SEGA|SEGD
#define left2_7    SEGA|SEGD
#define left2_8    SEGA|SEGD
#define left2_9    SEGA
#define left2_10   SEGA|SEGD
#define left2_11   SEGA|SEGD
#define left2_12   SEGA|SEGD

#define left3_1    SEGA|SEGD
#define left3_2    SEGA|SEGD
#define left3_3    SEGD
#define left3_4    SEGA|SEGD
#define left3_5    SEGA|SEGD
#define left3_6    SEGA|SEGD
#define left3_7    SEGA|SEGD
#define left3_8    SEGA
#define left3_9    SEGA|SEGD
#define left3_10   SEGA|SEGD
#define left3_11   SEGA|SEGD
#define left3_12   SEGA|SEGD

#define left4_1    SEGA|SEGB|SEGC|SEGD
#define left4_2    SEGA|SEGB|SEGC|SEGD
#define left4_3    SEGA|SEGB|SEGC|SEGD
#define left4_4    SEGB|SEGC|SEGD
#define left4_5    SEGA|SEGC|SEGD
#define left4_6    SEGA|SEGB|SEGD
#define left4_7    SEGA|SEGB|SEGC
#define left4_8    SEGA|SEGB|SEGC|SEGD
#define left4_9    SEGA|SEGB|SEGC|SEGD
#define left4_10   SEGA|SEGB|SEGC|SEGD
#define left4_11   SEGA|SEGB|SEGC|SEGD
#define left4_12   SEGA|SEGB|SEGC|SEGD

#define right_1   (SEGE)
#define right_2   (SEGE | SEGF)
#define right_3   (SEGA | SEGE | SEGF)
#define right_4   (SEGA | SEGB | SEGE| SEGF)
#define right_5   (SEGA | SEGB | SEGC| SEGF | SEGE)
#define right_6   (SEGA | SEGB | SEGC| SEGF | SEGE | SEGD)
//--------------------数字----------------------
//#define SMG1_0    (A_SMG1 | B_SMG1 | C_SMG1 | D_SMG1 | E_SMG1 | F_SMG1)





#define DISP_0    (SEGA | SEGB | SEGC | SEGD | SEGE | SEGF)
#define DISP_1    (SEGB | SEGC)
#define DISP_2    (SEGA | SEGB | SEGG | SEGE | SEGD)
#define DISP_3    (SEGA | SEGB | SEGG | SEGC | SEGD)
#define DISP_4    (SEGB | SEGG | SEGF | SEGC)
#define DISP_5    (SEGA | SEGF | SEGG | SEGC | SEGD)
#define DISP_6    (SEGA | SEGF | SEGG | SEGC | SEGD | SEGE)
#define DISP_7    (SEGA | SEGB | SEGC)
#define DISP_8    (SEGA | SEGB | SEGC | SEGD | SEGE | SEGF | SEGG)
#define DISP_9    (SEGA | SEGB | SEGC | SEGD | SEGF | SEGG)
//--------------------字母----------------------
#define DISP_A    (SEGA | SEGB | SEGC | SEGG | SEGE | SEGF)
#define DISP_B    (SEGE | SEGF | SEGG | SEGC | SEGD)
#define DISP_C    (SEGA | SEGE | SEGF | SEGD)
#define DISP_D    (SEGB | SEGC | SEGD | SEGE | SEGG)
#define DISP_E    (SEGA | SEGF | SEGG | SEGE | SEGD)
#define DISP_F    (SEGA | SEGF | SEGG | SEGE)
#define DISP_G    (SEGA | SEGB | SEGC | SEGD | SEGF | SEGG)
#define DISP_H    (SEGB | SEGC | SEGE | SEGF | SEGG)
#define DISP_I    (SEGE)
#define DISP_J    (SEGB | SEGC | SEGD)
#define DISP_K    (SEGB | SEGC | SEGE | SEGF | SEGG)
#define DISP_L    (SEGE | SEGF | SEGD)
#define DISP_M    (SEGA | SEGB | SEGC | SEGE | SEGF)
#define DISP_N    (SEGE | SEGG | SEGC)
#define DISP_O    (SEGE | SEGG | SEGC | SEGD)
#define DISP_P    (SEGA | SEGB | SEGG | SEGE | SEGF)
#define DISP_Q    (SEGA | SEGB | SEGG | SEGC | SEGF)
#define DISP_R    (SEGE | SEGF | SEGG)
#define DISP_S    (SEGA | SEGF | SEGG | SEGC | SEGD)
#define DISP_T    (SEGA | SEGF | SEGE)
#define DISP_U    (SEGB | SEGC | SEGD | SEGE | SEGF)
#define DISP_V    (SEGC | SEGD | SEGE)
#define DISP_W    (SEGC | SEGD | SEGE)
#define DISP_X    (SEGC | SEGD | SEGE)
#define DISP_Y    (SEGB | SEGC | SEGF | SEGG)
#define DISP_Z    (SEGD | SEGG)





#define DISP_Colon_Off		Dis_Tel[DISP_COM1] &= ~SEGH;Dis_Tel[DISP_COM2] &= ~SEGH  //两点灭 

#define ZiJian_1  B_SMG2;C_SMG2;
#define ZiJian_U  B_SMG3;C_SMG3;D_SMG3;E_SMG3;F_SMG3;
#define ZiJian_0  A_SMG4;B_SMG4;C_SMG4;D_SMG4;E_SMG4;F_SMG4;
#define ZiJian_5  A_SMG5; F_SMG5; G_SMG5; C_SMG5; D_SMG5;

#define error_E  A_SMG2;G_SMG2;D_SMG2;E_SMG2;F_SMG2;
#define error_1  B_SMG3;C_SMG3;
#define error_2  A_SMG3;B_SMG3;G_SMG3;E_SMG3;D_SMG3;
#define error_3  A_SMG3;B_SMG3;G_SMG3;C_SMG3;D_SMG3;
#define error_4  B_SMG3;G_SMG3;F_SMG3;C_SMG3;

#define   DISP_Colon_On	  Dis_Tel[10] |= SEGH //两点亮

#define LED_ReTiao 		disp_tel[1]|=0x01
#define LED_DunZhu 		disp_tel[1]|=0x80
#define LED_TiaoNai		disp_tel[2]|=0x01
#define LED_ZhuFei    disp_tel[3]|=0x01
#define LED_YuYue     disp_tel[3]|=0x80
#define LED_ChuLv     disp_tel[4]|=0x01
#define LED_WenHuo    disp_tel[4]|=0x80
#define LED_Power     disp_tel[5]|=0x80
#define LED_HuaCha    disp_tel[7]|=0x80

//extern uchar xdata  DSP_SMG1;
#define A_SMG1  disp_tel[1]|=0x10
#define B_SMG1 	disp_tel[2]|=0x10
#define C_SMG1  disp_tel[5]|=0x10
#define D_SMG1  disp_tel[5]|=0x01
#define E_SMG1  disp_tel[7]|=0x01
#define F_SMG1  disp_tel[6]|=0x01
#define G_SMG1  disp_tel[3]|=0x10

//extern uchar xdata  DSP_SMG2;
#define A_SMG2  disp_tel[7]|=0x10
#define B_SMG2  disp_tel[7]|=0x20
#define C_SMG2  disp_tel[3]|=0x20
#define D_SMG2  disp_tel[4]|=0x20
#define E_SMG2  disp_tel[4]|=0x10
#define F_SMG2  disp_tel[6]|=0x10
#define G_SMG2  disp_tel[2]|=0x20

//extern uchar xdata  DSP_SMG3;
#define A_SMG3  disp_tel[6]|=0x20
#define B_SMG3  disp_tel[4]|=0x08
#define C_SMG3  disp_tel[1]|=0x08
#define D_SMG3  disp_tel[3]|=0x08
#define E_SMG3  disp_tel[1]|=0x20
#define F_SMG3  disp_tel[5]|=0x20
#define G_SMG3 	disp_tel[2]|=0x08

//extern uchar xdata  DSP_SMG4;
#define A_SMG4  disp_tel[6]|=0x08
#define B_SMG4  disp_tel[4]|=0x04
#define C_SMG4  disp_tel[1]|=0x04
#define D_SMG4 	disp_tel[2]|=0x04
#define E_SMG4  disp_tel[3]|=0x04
#define F_SMG4  disp_tel[5]|=0x08
#define G_SMG4  disp_tel[5]|=0x04

//extern uchar xdata  DSP_SMG5;
#define A_SMG5  disp_tel[6]|=0x04
#define B_SMG5  disp_tel[6]|=0x02
#define C_SMG5 	disp_tel[3]|=0x02
#define D_SMG5  disp_tel[2]|=0x02
#define E_SMG5  disp_tel[1]|=0x02
#define F_SMG5  disp_tel[7]|=0x04
#define G_SMG5  disp_tel[7]|=0x02

//extern uchar xdata  DSP_SMG6;
#define A_SMG6  disp_tel[5]|=0x40
#define B_SMG6  disp_tel[7]|=0x40
#define C_SMG6  disp_tel[3]|=0x40
#define D_SMG6  disp_tel[1]|=0x40
#define E_SMG6  disp_tel[4]|=0x40
#define F_SMG6  disp_tel[4]|=0x02
#define G_SMG6  disp_tel[2]|=0X40


#define ShangDian_state  0    //上电
#define GuanJi_state     1    //关机
#define DaiJi_state    	 2    //待机
#define Menu_state       3	  //菜单
#define Work_state       4    //工作
#define Warm_state       5	  //保温
#define ZiJian_state     6    //自检
#define BaoJing_state    7    //保护
#define YuYue_state      8    //预约

#define ZhuFei  1
#define ChuLv   2
#define DunZhu  3
#define YuYue   4
#define TiaoNai 5
#define ReTiao  6
#define HuaCha  7
#define WenHuo  8


extern unsigned int xdata dunzhu_time;
extern unsigned int xdata huacha_time;
extern unsigned int xdata wenhuo_time;
extern unsigned char xdata baowen_1;
extern unsigned char xdata baowen_2;
extern unsigned char xdata baowen_3;
extern unsigned char xdata baowen_4;
extern unsigned char xdata baowen_5;
extern unsigned char xdata baowen_6;
extern unsigned char xdata baowen_7;
extern unsigned char xdata baowen_8;
extern unsigned char xdata baowen_9;

extern uchar xdata dsp_way;//显示方式如下2种
#define dsp_temp  1   //温度
#define dsp_time  2   //时间


#define DisData_Len 16					       //显存字节长度

#define key_menu  0x100000
#define key_power 0x800000
#define key_add   0x200000
#define key_cut   0x400000
#define key_zijian   0x600000
extern uchar xdata No_operation_Time;
extern uchar xdata baowen_temp;
extern uchar xdata QuFan_b;
extern uchar xdata QuFan_Time;
extern uchar xdata key_buz_b;
//extern uchar xdata buz_lead_p;
extern uchar xdata dsp_wendu;
extern uchar xdata  Buz_Start_Time;
extern uchar xdata  Buz_Stop_Time;
extern uchar xdata  Buz_Ring_Count;
extern uchar xdata  Buz_Run_Time;
extern uchar xdata  Buz_Begin_b;	
#define buz_lead_p	PD0
extern uchar xdata set_temp;
//extern uint xdata set_time;
extern uint xdata Work_Time;
extern uchar xdata YuYue_b;
extern uchar xdata frist_ad;
extern uchar xdata frist_buz;
void Buz_Start( uchar Start_Time, uchar Stop_Time, uchar Ring_Count);
void Buz_Stop(void);
extern uchar xdata Menu;
extern uint xdata YuYue_Time;
extern uchar xdata system_state;
extern uchar xdata key_cnt;
extern uchar xdata b_sys_5ms;
extern uchar xdata time_5ms;
extern unsigned char xdata disp_scannum;	
extern uchar xdata disp_tel[DisData_Len];
extern uchar xdata disp_tel2[DisData_Len];
extern uchar  xdata dis_key_data;
extern uchar	xdata	r_NoUartSend_ms;
extern uchar xdata r_cook_step;
extern uchar xdata fanzhuan_time;
extern uchar xdata zero_data;
extern uchar xdata zero_time_b;
extern uchar xdata zero_cnt;
extern uchar xdata Temp_gear;
extern uchar xdata JiaXian_b;
extern uchar xdata gaoyuan_b;
extern uint xdata gaoyuan_time;
extern uchar xdata gaoyuan_temp;
extern uchar xdata error_b;
extern uint xdata JiaXian_time;
extern uchar xdata TiHu_b;
extern uchar xdata Fan_b;
extern uchar xdata water_bit;
extern uchar xdata water_duibi;
extern uchar xdata max_wendu;
extern uchar xdata bianhua_temp;
extern uchar xdata start_time_b;
extern uchar xdata ZiJian_menu;
extern uchar xdata ZiJian_menu2;
extern uint xdata ShangDian_Time;
extern uint xdata GuanJi_time;
extern uint xdata fanDaiJi_Time;
extern uchar xdata error_b2;
extern uchar xdata ganshao_time;
extern uchar xdata duanlu_time;
extern uchar xdata fan_kailu_time;
extern uint xdata ChiXu_TiHu_time;
extern uint xdata Warm_Cnt;
extern uint xdata Fun_Time;
extern uchar xdata du_97;
extern uchar xdata BaoWen_JiaXian_100;
extern uchar xdata duibi_time;
extern uint xdata duibi_time2;
extern uchar xdata BaoWen_Jia_time;
extern uchar xdata Jian_baowen_xianzhi;
extern uchar xdata warm_jiaxian_time;
extern uchar xdata buz_time_delay;
extern uchar xdata ChuLv_daojishi;
extern uchar xdata CL_Sec;
extern uchar xdata CL_Min;
extern uint xdata change_time;
extern uchar xdata frist_baowen_temp;
extern uchar xdata feiteng_b;
extern uchar xdata shuiwei_dangwei;
extern uchar xdata shuiwei_duibi;
extern uint xdata shuiwei_time;
extern uchar xdata baowen_jieduan;
extern uchar xdata baowen_buz;
extern uchar xdata gaoyuan_No;
extern uchar xdata SetBaoWen_Tel[15];
//
#define SET_Heat SET_PA1_H
#define CLR_Heat SET_PA1_L
#define SET_Fan  SET_PD2_H
#define CLR_Fan  SET_PD2_L
#define zero_pro_b PC1
#define Fan_state  PD3

extern void  Disp(void);
extern void Disp_handle(void);
extern void Key_duration(void);
extern void Key_handle(void);
extern void SMG_deal(uchar number,uchar weizhi);
extern void Disp_gpio_out_init(void);
extern void Disp_scan(void);
extern void Time(void);
extern void fun(void);
extern void Zero_deal(void);
extern void GaoYuan_deal();
extern void ShuiWei_deal();
extern void shuzu_fuzhi(void);
//extern void ShuiWei_deal();
#endif



