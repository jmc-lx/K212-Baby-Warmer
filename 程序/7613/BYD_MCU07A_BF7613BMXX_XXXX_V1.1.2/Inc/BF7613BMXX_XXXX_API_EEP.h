#ifndef __BF7613BMXX_XXXX_API_EEP_H__
#define __BF7613BMXX_XXXX_API_EEP_H__

#define EEPROM_EN										0	// 1:使能编译，0:不使能编译

#define EEPROM_ERASE_TIMER_SET(x)  		{SPROG_TIM &= (~0x1F);SPROG_TIM |= (0x1F&x);}//擦出时间选择(0~9),0~9:0.5ms~5ms(0.5)+0.065ms,9：4.56ms
#define EEPROM_WRITE_TIMER_SET(x)  		{SPROG_TIM &= (~0xE0);SPROG_TIM |= (0xE0&(x<<5));}//默认固定为2，字节写时间固定23.5us

#if EEPROM_EN
	extern uchar xdata Eeprom_Write_Buffer[];
	extern void Eeprom_Init(void);
	extern void NVR_Erase_Page(uchar nvr);
	extern bit NVR_Write_Byte(uchar nvr,uint addr,uchar write_byte);
	extern bit NVR_Write_NBytes(uchar nvr,uint addr,uchar *write_data,uint length);
	extern uchar NVR_Read_Byte(uchar nvr,uint addr);
#endif
	
#endif