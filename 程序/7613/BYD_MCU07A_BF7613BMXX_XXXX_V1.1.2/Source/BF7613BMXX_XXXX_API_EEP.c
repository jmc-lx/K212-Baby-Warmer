#include "Config.h"

		
	#if (EEPROM_EN == 1)
		#pragma message "编译,EEPROM功能"
		uchar xdata Eeprom_Write_Buffer[10] = {0};
		uint rom_offset=0;
		
		//----------------------------------------------------------------	//
		//函数名称： uint Read_ROM_Offset(void)
		//函数功能： 读取CODE偏移地址
		//输入参数： 无
		//输出参数： 
		//返 回 值：uint：	CFG_BOOT_SEL = 0时,返回0x00;CFG_BOOT_SEL = 1时,返回0x1000
		//-----------------------------------------------------------------//
		uint Read_ROM_Offset(void)
		{
			uint rom_offset_tem = 0;
			EA = 0;
			REG_ADDR = 0x24;
			rom_offset_tem = (((uint)REG_DATA) << 8);
			REG_ADDR = 0x23;
			rom_offset_tem |= REG_DATA;
			EA = 1;
			return rom_offset_tem;
		}
		
		//-----------------------------------------------------------------//
		//函数名称： void Eeprom_Init(void)
		//函数功能： Eeprom_Init擦写时间初始化
		//输入参数： 无
		//输出参数： 无
		//返 回 值： 无
		//-----------------------------------------------------------------//
		void Eeprom_Init(void)
		{
			EA = 0;
			EEPROM_ERASE_TIMER_SET(9);//擦出时间选择(0~9),0~9:0.5ms~5ms(0.5)+0.065ms,9：4.56ms
			rom_offset=Read_ROM_Offset();
			EA = 1;
		}

		//-----------------------------------------------------------------//
		//函数名称： void NVR_Erase_Page(uchar nvr)
		//函数功能： NVR_Erase_Page擦除,uchar nvr:3/4选择要擦除的NVR:3/4对应NVR3/4
		//输入参数： 无
		//输出参数： 无
		//返 回 值： 无
		//-----------------------------------------------------------------//
		void NVR_Erase_Page(uchar nvr)
		{
			#ifdef IICS_EN
				#if ((IICS_EN == 1)) 
					IICCON &= ~0x01;//IIC工作使能关闭
				#endif
			#endif
			#ifdef TRACEMODE
				#if ((TRACEMODE == 1)) 
					IICCON &= ~0x01;//IIC工作使能关闭
				#endif
			#endif
			EA = 0;//关总中断；

			SPROG_ADDR_L = 0x00;
			if(nvr == 3)
			{
				SPROG_ADDR_H = 0x00;//NVR3
			}
			if(nvr == 4)
			{
				SPROG_ADDR_H = 0x04;//NVR4
			}
			
			SPROG_CMD = 0x96;
			_nop_();
			_nop_();
			_nop_();
			_nop_();
			SPROG_ADDR_L = 0x00;
			SPROG_ADDR_H = 0x00;

			#ifdef IICS_EN
				#if ((IICS_EN == 1)) 
					IICCON |= 0x01;//IIC工作使能
				#endif
			#endif
			#ifdef TRACEMODE
				#if ((TRACEMODE == 1)) 
					IICCON |= 0x01;//IIC工作使能
				#endif
			#endif
			EA = 1;//开总中断
		}
	
	
		
		//-----------------------------------------------------------------//
	//函数名称： bit NVR_Write_Byte(uchar nvr,uint addr,uchar write_byte)
	//函数功能： NVR写数据
	//输入参数： uchar nvr：选择将要写入的页3/4对应NVR3/4；uint addr:当前页对应的地址(0~511)；uchar write_byte：将要写入的数据;uchar write_time:写操作时间选择：建议固定为7；(0-7)-(26,28,30,32,34,36,38,40)us
	//输出参数： 无
	//返 回 值： 0:写成功；1：写失败；
	//-----------------------------------------------------------------//
	
		
		bit NVR_Write_Byte(uchar nvr,uint addr,uchar write_byte)
		{	
			
			bit Write_OK = 0;
			#ifdef IICS_EN
				#if ((IICS_EN == 1)) 
					IICCON &= ~IIC_EN;//IIC工作使能关闭
				#endif
			#endif
			#ifdef TRACEMODE
				#if ((TRACEMODE == 1)) 
					IICCON &= ~0x01;//IIC工作使能关闭
				#endif
			#endif
			EA = 0;//关总中断；

			SPROG_ADDR_L = 0x00;
			SPROG_ADDR_H = 0x00;
			if(nvr == 3)
			{
					SPROG_ADDR_H &= (~0x04);//选择要写的页
			}
			if(nvr == 4)
			{
				
					SPROG_ADDR_H |= (0x04);//选择要写的页
			}
			SPROG_ADDR_L = addr;
			SPROG_ADDR_H |= (addr>>8)&0x01;//选择要入地址
			SPROG_DATA = write_byte;//准备写入的数据
			SPROG_CMD = 0x69;
			_nop_();
			_nop_();
			_nop_();
			_nop_();
			SPROG_ADDR_L = 0x00;
			SPROG_ADDR_H = 0x00;
			
			#ifdef IICS_EN
				#if ((IICS_EN == 1)) 
					IICCON |= IIC_EN;//IIC工作使能
				#endif
			#endif
			#ifdef TRACEMODE
				#if ((TRACEMODE == 1)) 
					IICCON |= 0x01;//IIC工作使能
				#endif
			#endif
			if(NVR_Read_Byte(nvr,addr)== write_byte)
			{
					Write_OK = 0;
			}
			else
			{
					Write_OK = 1;
			}
	
			EA = 1;//开总中断
			return Write_OK;
				
		}
		
		//-----------------------------------------------------------------//
		//函数名称： bit NVR_Write_NBytes(uchar nvr,uint addr,uchar *write_data,uint length)
		//函数功能： NVR写length Bytes数据
		//输入参数： uchar nvr：选择将要写入的页(3/4对应NVR3/4)；uint addr:当前页对应的地址(0~511)；uchar *write_data：
		//将要写入的数据;uint length(1~512):从当前页第addr字节开始写入length个字节(length<= (512-addr))；
		//uchar write_time:写操作时间选择：//默认固定为2，字节写时间固定23.5us
		//输出参数： 无
		//返 回 值： 0:写成功；1：写失败；
		//-----------------------------------------------------------------//
	
		bit NVR_Write_NBytes(uchar nvr,uint addr,uchar *write_data,uint length)
		{	
			uint i = 0;
			bit Write_OK = 0;
			for(i = 0;i < length;i++)
			{
					if(NVR_Write_Byte(nvr,addr+i,*(write_data+i))!= 0)
					{
							Write_OK = 1;
					}
			}
			return Write_OK;
				
		}
	
		
		//-----------------------------------------------------------------//
		//函数名称： uchar NVR_Read_Byte(uchar nvr,uint addr)
		//函数功能： 读NVR数据
		//输入参数： uchar nvr：3/4对应NVR3/4；uint addr:0~511：读取NVR页的第addr字节;
		//输出参数： 无
		//返 回 值： 返回读NVR页的第addr字节的内容；
		//-----------------------------------------------------------------//
		uchar NVR_Read_Byte(uchar nvr,uint addr)
		{	
			return CBYTE[0x8400+(nvr-3)*512+addr-rom_offset];
		}
		

#endif
