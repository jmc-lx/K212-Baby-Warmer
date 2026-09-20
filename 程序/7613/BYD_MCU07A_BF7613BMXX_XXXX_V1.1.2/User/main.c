#include "Config.h"
//code unsigned char SetBaoWen_Tel[]={0,45,45,65,0,0,0,65,65};
//code unsigned char SetBaoWen_Tel[]={0,baowen_1,baowen_1,baowen_3,0,baowen_5,baowen_6,baowen_7,baowen_8};

void main(void)
{
	//MCU_Init()初始化函数，调用函数有WDT_Init()、Default_Set_IO()、
	//Init_IO()、Function_Init()。
	
	MCU_Init();
	baowen_1=45;
	baowen_2=45;
	baowen_3=65;
	baowen_5=45;
	baowen_6=55;
	baowen_7=65;
	baowen_8=65;
	baowen_9=50;
	
	dunzhu_time=120;
	huacha_time=20;
	wenhuo_time=60;
	while(1)
	{
		//清看门狗。
		WDT_CTRL = 7;
		
		#if SNS_NUM	
			#if VolDet_EN
			if(low_power == 0)//进入低电压中断时标记，low_power = 1时,不处理按键，低电压检测点根据实际项目配置
			#endif
			{
				//获取按键标志位
				BF7613BMXX_XXXX_Set_Touch_Flag();	
				
			}
		#endif
			
		//建议将项目功能函数定义在Project.c中或新建c文件。
		Project();
				
	}			
}