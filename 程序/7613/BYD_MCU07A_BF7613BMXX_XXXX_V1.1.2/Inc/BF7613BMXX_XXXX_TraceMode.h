#ifndef __BF7613BMXX_XXXX_TRACEMODE_H__ 
#define __BF7613BMXX_XXXX_TRACEMODE_H__ 

#if TRACEMODE
extern unsigned char data ReadCnt;
extern unsigned char data ReceData;
extern unsigned char data DataNum;
extern bit OddCheck;
extern bit NeedCheckOdd;
extern unsigned int xdata raw;
extern unsigned int xdata bas;


#endif
//-----------------------------------------------------------------//
//函数名称： void BF7613BMXX_XXXX_Trace_Mode_Init(void)   
//函数功能： BF7613BMXX_XXXX_Trace_ModeI_nit初始化
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
extern void BF7613BMXX_XXXX_Trace_Mode_Init(uchar iic_port);
//-----------------------------------------------------------------//
//函数名称： void TraceMode_Master_Read_Data(uint *p_rawData,uint *p_baseline,ulong t_keysFlagSN)   
//函数功能： 将发送的数据写入IICBUF
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
extern void TraceMode_Master_Read_Data(unsigned int *p_rawData,unsigned int *p_baseline,unsigned long t_keysFlagSN);   
//-----------------------------------------------------------------//
//函数名称： void TraceMode_Master_Write_Data(void)  
//函数功能： 从IICBUF读取数据
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
extern void TraceMode_Master_Write_Data(void);

#endif
