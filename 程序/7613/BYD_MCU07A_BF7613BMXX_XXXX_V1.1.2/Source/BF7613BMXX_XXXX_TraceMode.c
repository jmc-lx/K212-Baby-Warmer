#include "Config.h"

#if (TRACEMODE == TRUE)
void TraceMode_Master_Read_Data(unsigned int *p_rawData,unsigned int *p_baseline,unsigned long t_keysFlagSN);   
unsigned char data ReadCnt = 0;
unsigned char data ReceData = 0;
unsigned char data DataNum = 0;
bit OddCheck = 0,NeedCheckOdd = 0;
unsigned int xdata raw = 0;
unsigned int xdata bas = 0;


//-----------------------------------------------------------------//
//函数名称： void TraceMode_Master_Write_Data(void)  
//函数功能： 从IICBUF读取数据
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
#pragma disable
void TraceMode_Master_Write_Data(void) 
{   
	ReceData = IICBUF;
}


//#pragma message "编译,TRACEMODE功能"
unsigned long xdata keys_flag_Tracemode = 0;	

//-----------------------------------------------------------------//
//函数名称： void Trace_Mode_IIC_ISR_PA() interrupt 10 
//函数功能： PA口IIC中断子函数
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
void Trace_Mode_IIC_ISR_PA() interrupt 10
{
		uchar tmp;
		static uchar xdata addr_bak = 0;
		PUSH_REG_ADDR_SFR();
		IRCON1 &= ~0x08;//IIC_INT_FLAG_CLR;//清除IIC中断标志位

		if (IICSTAT & 0x02)//IICS_WCOL)//写冲突标志位
		{ 
				IICSTAT &= ~0x02;//IICS_WCOL_CLR;
		}
		if (IICSTAT & 0x01)//IICS_RECOV)//读冲突标志位  
		{
				IICSTAT &= ~0x01;//IICS_RECOV_CLR;
				tmp = IICBUF;
		}
		if ((IICSTAT & 0x10)==0)//IICS_AD == 0)//是地址
		{	 
		
				if (IICSTAT & 0x20)//IICS_RW)//主机读 
				{
						ReadCnt = 0;
						OddCheck = 0;
						DataNum = 0;
						TraceMode_Master_Read_Data(raw_data,base_line,keys_flag_Tracemode);
						IICCON |= 0x04;//SCLEN_SET; 
				}
				else //主机写
				{
						tmp = IICBUF;
				}   
			}
			else 
			{
				if (IICSTAT & 0x20)//IICS_RW)//主机读 
				{     
						TraceMode_Master_Read_Data(raw_data,base_line,keys_flag_Tracemode);
						IICCON |= 0x04;//SCLEN_SET; 	  
				}
				else//主机写  
				{   
			
					if (IICSTAT & 0x08)//IICS_BF) 
					{ 
						TraceMode_Master_Write_Data();
					}
				}
		}
		IICCON |= 0x04;//SCLEN_SET; 
		POP_REG_ADDR_SFR();
}

//-----------------------------------------------------------------//
//函数名称： void BF7613BMXX_XXXX_Trace_Mode_Init(uchar iic_port)   
//函数功能： BF7613BMXX_XXXX_Trace_Mode_Init初始化
//输入参数： uchar iic_port,IIC端口映射选择，
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
void BF7613BMXX_XXXX_Trace_Mode_Init(uchar iic_port)
{
	
		EA = 0;//关总中断； 
		IPL1 |= 0x08; //设置IIC中断优先级为高，根据实际应运设置优先级
		IRCON1 &= ~0x08;//清除IIC中断标志位 
	
		if(iic_port == 0)
		{
			TRISA |= 0x03;//设置SDA、SCL为输入；(PA1/PA0-SDA_A/SCL_A)
		}
		else if(iic_port == 1)
		{
				TRISC |= 0x01;
				TRISB |= 0x20;//设置SDA、SCL为输入；(PC0/PB5-SDA_B/SCL_B)
		}
		else if(iic_port == 2)
		{
				TRISD |= 0x40;
				TRISA |= 0x02;//设置SDA、SCL为输入；(PD6/PA1-SDA_C/SCL_C)
					
		}
		
		IICADD = 0x54;//设置IIC从机地址；
	
		IICCON |= 0x01;//IIC工作使能
		IICCON |= (0x02);//IIC转换速率适应100K
		IICCON |= 0x04;//SLC时钟正常工作
		IICCON &= (~0x08);//不使能写拉低,根据IIC主机读写时序设置
		IICCON |= (0x10);//使能读拉低，根据IIC主机读写时序设置
	
		PERIPH_IO_SEL &= ~(0x60);
		PERIPH_IO_SEL |= (0x60&(1<<5));//bit5/6:IIC_FIL_SEL(1);//1:为数字滤波(Sleep模式下无唤醒功能)；2为模拟滤波；3为模拟和数字滤波
	  PERIPH_IO_SEL &= ~(0x18);
		PERIPH_IO_SEL |= (0x18&(iic_port<<3));//bit3/4:0:映射到SDA0_A/SCL0_A；1:映射到SDA0_B/SCL0_B；2:映射到SDA0_C/SCL0_C；
		IEN1 |= 0x08; //开IIC中断使能
		EA = 1;//开总中断；
	
}
//-----------------------------------------------------------------//
//函数名称： void TraceMode_Master_Read_Data(uint *p_rawData,uint *p_baseline,ulong t_keysFlagSN)   
//函数功能： 将发送的数据写入IICBUF
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//

#pragma disable
void TraceMode_Master_Read_Data(unsigned int *p_rawData,unsigned int *p_baseline,unsigned long t_keysFlagSN)    
{   
	unsigned char data tmp = 0;

	if(ReceData == 0xb2)
	{
		if(ReadCnt == 0)
			tmp = 0xae;
		else if(ReadCnt == 1)
			tmp = CH_MAX;		
	}
	else if(ReceData == 0xb3)
	{
		if(ReadCnt < 1)			//发送头码0XAE
		{
			tmp = 0xae;			
		}
		else if(ReadCnt < ((CH_MAX<<1) + 1))	//发送RAWDATA
		{
			NeedCheckOdd = 1;
			if(ReadCnt % 2)	
			{
				raw = *(p_rawData + DataNum);
				tmp = (raw >> 8);
			}
			else
			{
				tmp = raw;
				DataNum ++;	
			}
		}
		else if(ReadCnt == ((CH_MAX << 1) + 1))  //发送BASELINE[0]高8位
		{
			NeedCheckOdd = 1;
			DataNum = 0;
			bas = *(p_baseline + DataNum);
			tmp = (bas >> 8);
		}
		else if(ReadCnt < ((CH_MAX << 2) + 1))		//发送BASELINE
		{
			
			NeedCheckOdd = 1;
			if(ReadCnt % 2)	
			{
				bas = *(p_baseline + DataNum);
				tmp = (bas >> 8);
			}
			else
			{
				tmp = bas;  
				DataNum++;	
			}
			
		} 
		else if(ReadCnt == ((CH_MAX << 2) + 1))		//发送奇偶校验位
		{
			tmp = OddCheck;
			
		}
		else if(ReadCnt == ((CH_MAX << 2) + 2))		//发送有效数据长度
		{						
			tmp = (CH_MAX << 2);
		}				
		else if(ReadCnt == ((CH_MAX << 2) + 2))		//发送有效数据长度
		{						
			tmp = (CH_MAX << 2);
		}				
		else if(ReadCnt == ((CH_MAX << 2) + 3))		//触摸标志位bit31:17
		{ 						
			tmp = (unsigned char )(t_keysFlagSN >> 24);
		}
		else if(ReadCnt == ((CH_MAX << 2) + 4))		//触摸标志位bit23:16
		{ 						
			tmp = (unsigned char )(t_keysFlagSN >> 16);
		}
		else if(ReadCnt == ((CH_MAX << 2) + 5))		//触摸标志位bit15:8
		{						 
			tmp = (unsigned char )(t_keysFlagSN >> 8);
			
		}
		else if(ReadCnt == ((CH_MAX << 2) + 6))		//触摸标志位bit7:0
		{						
			tmp = (unsigned char )t_keysFlagSN;						
		}									
		else																		//发送结束码0xff、0xff
		{						
			tmp = 0xff;	
		}
	}

	IICBUF = tmp;
	
	if(NeedCheckOdd)		//当前数据是否需要进行奇偶校验
	{
		NeedCheckOdd = 0;
		
		ACC = tmp;
		if((PSW & 0x01))
			OddCheck = !OddCheck;
	}
	ReadCnt ++;
}

#endif