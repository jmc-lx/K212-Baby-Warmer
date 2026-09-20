BYD_MCU07A_BF7613BMXX_XXXX_V1.1.2
更新日期：2023-01-13
1)TK.c文件中在"else if(differ >= (((int)fth)*RENOVATE_NTH_RATE/10))//>=p_noise基线更新"条件分支中加了"RENOVATE_MODE == 1"分支条件处理
2)在TK.c文件中增加了变量
unsigned char xdata noise_count[SNS_NUM] = {0};
unsigned char xdata noise_flag[SNS_NUM] = {0};
删除了变量
unsigned char xdata over_p_noise_count[SNS_NUM] = {0};
unsigned char xdata under_p_noise_count[SNS_NUM] = {0};
unsigned char xdata over_n_noise_count[SNS_NUM] =  {0};
unsigned char xdata under_n_noise_count[SNS_NUM] = {0};
unsigned char xdata under_nn_noise_count[SNS_NUM] = {0};
并修改了void CTK_SNS_Renovate(unsigned char addr,unsigned int fth)中相应代码，优化了xdata空间。
更新日期：2023-01-12
1)LED.h文件中增加了一个宏LED_SER_Dis_MODE用来选择LED串行点阵的显示计算方式，当为0时选择1.1.2版本之前的显示方式，为1时为此版本新加的显示方式，
新的LED串行点阵显示方式将相关变量存储在data区，并将原来的32位数操作改为多个八位数值的操作。新的LED显示方式
减少了CODE区代码长度，改善了亮灯函数的执行时间
2)删除Timer.h文件中的宏定义#define T1_CT_MODE(x)和宏定义#define T0_CT_MODE(x)
3)修改Timer.h文件中的宏定义T0_MODE_SET(x)和宏定义T1_MODE_SET(x) 的注释
4）删除了Timer.c文件中void Timer0_Init(uint Timer0Us)函数中的 “T0_CT_MODE(0); //TIMER0定时/计数模式选择0为定时模式，1为计数模式”并修改了T0_MODE_SET(1); 的注释
5）修改了Timer.c文件中void Timer1_Init(uint Timer1Us)函数

更新日期：2022-12-21
1)修改了Read_UID.c文件中的void CHIP_UDI_Read(void)函数
2)删除了Touch_MCU_Init.h文件中的以下语句：
#ifdef SLEEP_MODE
	#if (SLEEP_MODE == 0)
	extern void Delay_Ms(uint ms);//1-1ms
	#endif
#endif
和TK.c文件中的以下语句：		
#ifdef SLEEP_MODE
	#if (SLEEP_MODE == 1)
		Sleep();
	#endif
#endif	
更新日期：2022-12-20
1)修改了Idle.c文件中的void Idle()函数。
2）删除了Sleep.c文件和Sleep.h文件和config.h文件中的//#include "BF7613BMXX_XXXX_API_Sleep.h"。
更新日期：2022-07-11
1)修改了PWM.h中PWM1_DUTY_MODE、PWM1_POLO_SEL、PWM2_DUTY_MODE、PWM2_POLO_SEL宏的备注;
更新日期：2022-07-11
1）修改了Project.h文件中的SET_PA4_IO_IN、SET_PA5_IO_IN宏定义

BYD_MCU07A_BF7613BMXX_XXXX_V1.1.1
更新日期：2022-06-01
1)将ADC.h文件中宏定义#define ADC_ANCK备注中的分频值改为(12MHz,8MhHz,4MHz,2MHz)
2）将IIC.c中void IIC_Slave_Init()函数的IIC_IO_MAP(0);改为IIC_IO_MAP(iic_port);
3）将UART.c中void UART1_Init(void)函数中#elif(UART1_PORT == UART1_MAP_D)条件下的：
TRISD &= ~0x20;//设置TX为输出
TRISD |= 0x10;//设置RX为输入
改为
TRISA |= ~0x10;//设置TX为输出
TRISA &=  0x08;//设置RX为输入
更新日期：2022-06-02
1)更正了ADC.c文件中ADC_CTRL_SET(ADC_CTRL)的注释;

BYD_MCU07A_BF7613BMXX_XXXX_V1.1.0
更新日期：2022-05-16
1)更正了ADC_CTRL_SET(x) 宏定义和注释

BYD_MCU07A_BF7613BMXX_XXXX_V1.0.9
更新日期：2022-03-03
1)在EEP.c文件中加入了CODE区偏移地址读取函数uint Read_ROM_Offset(void)，并在EEP初始化函数中获取偏移地址。
将uchar NVR_Read_Byte(uchar nvr,uint addr)函数中的0x1000更正为CODE地址偏移。

BYD_MCU07A_BF7613BMXX_XXXX_V1.0.8
更新日期：2021-12-23
1）更正了Eeprom_Init(void)函数中总中断的设置
2）在void OP_Init(void)定义中加入了rom_offset的定义，解决了没定义报错问题
更新日期：2021-12-22
1）更新了宏定义SYS_CLK_OSC_CFG_READ(reg_data),将原来的reg_data =REG_DATA改成了reg_data =（REG_DATA&0x7F);
更新日期：2021-12-15
1）在串口中加入了引脚互换宏定义，在串口引脚输入输出配置时加入了引脚是否互换的判断和相关配置
更新日期：2021-11-29
1）加入了判断触摸按键电阻RB值是否有效的语句

BYD_MCU07A_BF7613BMXX_XXXX_V1.0.7
更新日期：2021-11-2
1）将BOR掉电复位0档定为保留，将LVDT低电压升检测点0和1定为保留
更新日期：2021-09-10
1)修复APP NVR读复位BUG。
2)增加#define ADC_IO_CGF_CLR(x)宏。
更新日期：2021-08-19
1)重新定义UART0_A~UART0_F宏，避免与位寄存器重名。
2)修复开MULTI_KEY_MAX_COUNT多按键消除判断编译不通过Bug。

BYD_MCU07A_BF7613BMXX_XXXX_V1.0.6
1)修复FTH设置>3276时计算溢出Bug。
更新日期：2021-08-13
1)更新OP_Init初始函数，修复有boot功能时复位问题”
2)XXX_API_ADC.h文件恢复ADC_VREF_VOL_SEL(x)宏定义。

BYD_MCU07A_BF7613BMXX_XXXX_V1.0.4
更新日期：2021-06-7
1)更新CFG_Check()函数,"0x83F3"地址的与值为“0x1F”

BYD_MCU07A_BF7613BMXX_XXXX_V1.0.3
更新日期：2021-05-24
1)更新ADC内部参考电压4V/VCC配置，ADC参考电压配置只保留4V/VCC。
2)更新“UARTX_PC_SET(0)”注释

BYD_MCU07A_BF7613BMXX_XXXX_V1.0.2
更新日期：2021-05-14
1)修复RESO为15/16bit时自适应溢出Bug。
2)删除ADC内部参考电压2V/4V配置，ADC参考电压配置只保留VCC。

BYD_MCU07A_BF7613BMXX_XXXX_V1.0.1
更新日期：2021-05-06
1)修复Timer0_Init默认初始化为16bit模式

BYD_MCU07A_BF7613BMXX_XXXX_V1.0.0
更新日期：2021-04-27
1)初版。
/****************************************************/
说明：
1、开发底层软件包，尽可能做到兼容性或适应性更好，实际应用项目中以实际开发测试验证为准。
2、Keil编译器不会对堆栈大小作限制，堆栈分配在DATA或IDATA区向上增涨与程序中断与函数调用有关
，所以程序一般建议预留至少50个字节，具体以实际项目应用测试验证为准。	