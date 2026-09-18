#ifndef __BF7613BMXX_XXXX_API_TK_H__
#define __BF7613BMXX_XXXX_API_TK_H__

/////////////////////////////////////////TK//////////////////////////////////////////////
#define CTK_START 					{CSD_START &= ~0X01;CSD_START |= 0X01;}//CTK模块开启从低0到1
#define CTK_STOP 						(CSD_START &= ~0X01)//CTK模块停止
#define CTK_PULL_I_SET(x) 	{PULL_I_SELA_L = x;SNS_SCAN_CFG2 &= (~0x40);SNS_SCAN_CFG2 |= ((0x100&x)>>2);}//上拉电流源设置
#define CTK_PRS_SW_SET(x) 	{SNS_SCAN_CFG1 &= ~(0x40);SNS_SCAN_CFG1 |= (0x40&(((unsigned char)x)<<6));}//前端充放电开关,1为关，0为开
#define CTK_PRS_SET(x) 			{SNS_SCAN_CFG1 &= ~(0x3F);SNS_SCAN_CFG1 |= (0x3F&(x<<0));}//PRS(充放电频率) = 48/2/(x+4),62:正态分布(1~1.5~3)MHz,63:均匀分布(1~1.5~3)MHz,26--800KHz,20--1MHz,12--1.5MHz,8--2MHz。

#define CTK_PAR_SET(x) 				{SNS_SCAN_CFG2 &= ~(0x20);SNS_SCAN_CFG2 |= (0x20&(x<<5));}//1:为多通道并联模式；0：为单通道模式
#define CTK_ADDR_SET(x) 			{SNS_SCAN_CFG2 &= ~(0x1F);SNS_SCAN_CFG2 |= (0x1F&(x<<0));}//设置通道地址0~31
#define CTK_RESO_SET(x) 			{SNS_SCAN_CFG3 &= ~(0x70);SNS_SCAN_CFG3 |= (0x70&(x<<4));}//0~7 CTK电容扫描分辨率，计数器位数：(CFG_CTK_RESOLUTION+9)位。
#define CTK_DS_SET(x) 				{SNS_SCAN_CFG3 &= ~(0x0C);SNS_SCAN_CFG3 |= (0x0C&(x<<2));}//检测速度0:24MHz,1:12MHz,2:6MHz,3:4MHz
#define CTK_PRE_CH_SET(x) 		{SNS_SCAN_CFG3 &= ~(0x02);SNS_SCAN_CFG3 |= (0x02&(x<<1));}//预充电时间：0为20us,1为40us
#define CTK_PRE_DISCH_SET(x) 	{SNS_SCAN_CFG3 &= ~(0x01);SNS_SCAN_CFG3 |= (0x01&(x<<0));}//预放电时间：0为2us,1为10us

#define CTK_PD_SET(x) 				{PD_ANA &= ~0x02;PD_ANA |= (0x02&(x<<1));}//0为CTK开，1为CTK关
#define CTK_RB_SET(x) 				{SNS_ANA_CFG &= (~0x38);SNS_ANA_CFG |= (0x38&(x<<3));}//选择RB电阻大小0:10K,1:20K,2:30K,3:40K,4:60K,5:80K,6:150K,7:300K。
#define CTK_VTH_SET(x) 				{SNS_ANA_CFG &= (~0x07);SNS_ANA_CFG |= (0x07&(x<<0));}//参考电压(0:1.81V),(1:2.14V),(2:2.49V),(3:2.83V),(4:3.18V),(5:3.51V),(6:3.86V),(7:4.10V);


#define CTK_INT_FLAG_CLR IRCON1 &= ~0X20//清除CTK中断标志位

#define CTK_IE_SET IEN1 |= 0X20//开CTK中断使能
#define CTK_IE_CLR IEN1 &= ~0X20//关CTK中断使

#define CTK_IP_SET IPL1 |= 0X20//设置CTK中断优级为高
#define CTK_IP_CLR IPL1 &= ~0X20//设置CTK中断优级为低


#if SNS_NUM

extern unsigned char xdata sensor_open[];				//0~31	
extern unsigned char sns_next;
extern unsigned char xdata Mode;								//0为单通道模式，1为多通道并联模式
extern unsigned int  xdata pull_i_value[];//电流源级数;

#if (CS_SW == 1)
extern	uint cs_noise;
#endif

extern bit adjust_done_flag;
extern bit base_line_int_flag;
extern bit ctk_circle_done;//0为ctk扫描中，1为扫描一轮完成


extern unsigned int xdata pull_i_value_parallel;

extern bit parallel_init_flag;


extern unsigned long xdata open_sns;
extern unsigned long xdata adjust_flag;



extern unsigned int  xdata n_base_line[];
extern unsigned char xdata n_base_line_reno_count[];
extern unsigned char xdata touch_confirm_count[];
	

extern unsigned long xdata mode_flag;
extern unsigned long xdata muli_key_flag;

extern unsigned char xdata touch_left_count[];	


extern unsigned char  xdata over_p_noise_count[];
extern unsigned char  xdata under_p_noise_count[];
extern unsigned char  xdata over_n_noise_count[];
extern unsigned char  xdata under_n_noise_count[];
extern unsigned char  xdata under_nn_noise_count[];

#if (RENOVATE_MODE == 1)
extern bit water_flow_flag;	
extern unsigned int 	xdata water_flow_left_count;	
extern unsigned char  xdata water_flow_key_count;//溢水计数
extern unsigned char  xdata water_flow_key_reset_cnt;
#endif
extern unsigned char 	xdata multi_key_count;
extern unsigned char  xdata multi_key_reset_cnt;



//-----------------------------------------------------------------//
//函数名称： void Base_Line_Init()
//函数功能： 基线初始化
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
extern void Base_Line_Init();



//-----------------------------------------------------------------//
//函数名称： void CTK_TK_Left_Count(void)
//函数功能： 手指离开判断计数
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
extern void CTK_TK_Left_Count(uchar addr);


//-----------------------------------------------------------------//
//函数名称： void CTK_SNS_Renovate(unsigned char addr,unsigned int fth)
//函数功能： SNS基线更新
//输入参数： unsigned char addr：SNS通道;unsigned int fth:手指阈值
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
extern void CTK_SNS_Renovate(unsigned char addr,unsigned int fth);

/////////////////////////////////////////TK//////////////////////////////////////////////


extern void BF7613BMXX_XXXX_Set_Touch_Flag(void);
extern uchar Sns_Count;


extern void CTK_Set_Para(void);
extern unsigned int   code 	FTH[];
extern unsigned char  code 	SNS[];
extern unsigned int   code 	PUIV[]; 
extern unsigned char  xdata sensor_open[];
extern unsigned int   xdata pull_i_value[];
extern unsigned char  xdata touch_left_count[];
extern unsigned char  xdata over_p_noise_count[];
extern unsigned char  xdata under_p_noise_count[];
extern unsigned char  xdata over_n_noise_count[];
extern unsigned char  xdata under_n_noise_count[];
extern unsigned char  xdata n_base_line_reno_count[];
extern unsigned int   xdata n_base_line[];
extern unsigned char  xdata touch_confirm_count[];


#if UN_NORMAL_CHECK
extern unsigned char xdata un_normal_count;
extern unsigned char xdata un_normal_recover_count;
extern bit un_normal_flag;
extern unsigned long xdata adjust_flag;
extern void Rawdata_Un_Normal(uchar sns_num);
#endif

extern void CTK_Init(void);

#endif


#endif  