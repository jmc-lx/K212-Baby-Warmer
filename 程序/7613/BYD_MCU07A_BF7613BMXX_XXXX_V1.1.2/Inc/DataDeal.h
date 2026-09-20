#ifndef __DATADEAL_H__
#define __DATADEAL_H__

extern unsigned int  xdata rawData_Tem[];
extern unsigned int  xdata rawData_Count;
extern unsigned long xdata rawData_AVG;
extern unsigned char xdata rawData_AVG_Count;	

//累积扫描次数 raw_count:2~20；扫描完成一轮后的延时ms@12MHz，需要芯片型号支持,返回噪声处理值；
extern unsigned int  Data_Deal(unsigned char raw_count,unsigned char delay,unsigned char sns_num);

extern bit adjust_done_flag;
extern unsigned char sns_next;
extern unsigned int  xdata base_line[];
extern unsigned int  xdata raw_data[];
extern unsigned int  xdata n_base_line[];
extern bit ctk_circle_done;

#endif