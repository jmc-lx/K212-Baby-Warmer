#include "Config.h"
#if IICS_EN
	uint data  IICS_PA_Soft_Cnt = 0;
	uint xdata SCLEN_SoftCnt = 0; 
#endif


	#if IICS_EN
		#if (TRACEMODE==0)
		
		//-----------------------------------------------------------------//
		//函数名称： void IIC_Slave_Init(uchar IICSlaveAddr,uchar iic_port)
		//函数功能： IIC从机初始化
		//输入参数： uchar IICSlaveAddr:IIC从机地址,iic_port:0:(PA1/PA0-SDA_A/SCL_A),1:(PC0/PB5-SDA_B/SCL_B),2:(PD6/PA1-SDA_C/SCL_C)
		//输出参数： 无
		//返 回 值： 无
		//-----------------------------------------------------------------//

		void IIC_Slave_Init(uchar IICSlaveAddr,uchar iic_port)
		{
			EA = 0;//关总中断;
			IIC_IP_SET; //设置IIC中断优先级为高，根据实际应运设置优先级
			IIC_INT_FLAG_CLR;//清除IIC中断标志位 
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
			
			IICADD = IICSlaveAddr;//设置IIC从机地址；
			
			IICCON |= IIC_EN;//IIC工作使能
			IICCON |= (IIC_SR);//IIC转换速率适应100K
			IICCON |= IIC_SCLEN;//SLC时钟正常工作
			IICCON &= (~IIC_W_SCL_EN);//不使能写拉低,根据IIC主机读写时序设置
			IICCON |= (IIC_R_SCL_EN);//使能读拉低，根据IIC主机读写时序设置
			IIC_FIL_SEL(1);//1:为数字滤波(开数字滤波，Sleep模式下无唤醒功能)；2为模拟滤波；3为模拟和数字滤波(开数字滤波，Sleep模式下无唤醒功能);
			IIC_IO_MAP(iic_port);//0:映射到SDA0_A/SCL0_A；1:映射到SDA0_B/SCL0_B；2:映射到SDA0_C/SCL0_C；
			IIC_IE_SET; //开IIC中断使能
			EA = 1;//开总中断；
		}
		//-----------------------------------------------------------------//
		//函数名称： void Master_Read_Data()  
		//函数功能： 将发送的数据写入IICBUF
		//输入参数： 无
		//输出参数： 无
		//返 回 值： 无
		//-----------------------------------------------------------------//
		void Master_Read_Data()    
		{   
			uchar tmp = 0;
			IICBUF = tmp;
			SCLEN_SET;
		}
		//-----------------------------------------------------------------//
		//函数名称： void Master_Write_Data()  
		//函数功能： 从IICBUF读取数据
		//输入参数： 无
		//输出参数： 无
		//返 回 值： 无
		//-----------------------------------------------------------------//
		void Master_Write_Data() 
		{   
			uchar tmp = 0;
			tmp = IICBUF;
		} 
		//-----------------------------------------------------------------//
		//函数名称： void IIC_ISR_PA() interrupt 10 
		//函数功能： PA口IIC中断子函数
		//输入参数： 无
		//输出参数： 无
		//返 回 值： 无
		//-----------------------------------------------------------------//
		void IIC_ISR_PA() interrupt 10
		{
				uchar tmp = 0;
				static uchar xdata addr_bak = 0;
				PUSH_REG_ADDR_SFR();
				IIC_INT_FLAG_CLR;//清除IIC中断标志位
				if((IICCON & 0x10) == 0)
				{
					IICCON |= (IIC_R_SCL_EN);//使能读拉低，根据IIC主机读写时序设置
				}
				
				if (IICS_WCOL)//写冲突标志位
				{ 
						IICS_WCOL_CLR;
				}
				if (IICS_RECOV)//读冲突标志位  
				{
						IICS_RECOV_CLR;
						tmp = IICBUF;
				}
				if (IICS_AD == 0)//是地址
				{	 
				
						if (IICS_RW)//主机读 
						{
				
								Master_Read_Data();
								SCLEN_SET; 
						}
						else //主机写
						{
								tmp = IICBUF;
						}   
					}
					else 
					{
						if (IICS_RW)//主机读 
						{        
								Master_Read_Data();
								SCLEN_SET;	  
						}
						else//主机写  
						{   
							if (IICS_BF) 
							{ 
								Master_Write_Data();
							}
						}
				}
				SCLEN_SET;
				POP_REG_ADDR_SFR();
		}
		
		#endif
	#endif//PA_SLAVE
