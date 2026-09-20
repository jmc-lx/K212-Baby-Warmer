#ifndef __BF7613BMXX_XXXX_API_OP_H__
#define __BF7613BMXX_XXXX_API_OP_H__

#define	OP_EN				0	//OP功能使能配置	 				1:使能编译，0:不使能编译
#define	OP_MODE			1	//OP工作模式选择，1:模式1输入共模电压1/2VCC~VCC-1.2V；4:模式2输入共模电压0.1V~1/2VCC；其它保留
#define OP_OUT_MODE_SET(x) 	{OP_CFG1 &= ~(0x80);OP_CFG1 |= (0x80&(x<<7));}//1:打开OP外部输出;0:关闭OP外部输出,输出到ADC31					 
#define OP_P_VIN_SET(x) 		{OP_CFG1 &= ~(0x70);OP_CFG1 |= (0x70&(x<<4));}//OP同相输入端电压选择，0:1/2VCC; 1:1/3VCC; 2:2/3VCC; 3:内部GND;4/others:外部输入
#define OP_FB_SET(x) 				{OP_CFG1 &= ~(0x08);OP_CFG1 |= (0x08&(x<<3));}//OP反馈选择，0:外部反馈; 1:内部反馈
#define OP_MODE_SET(x) 			{OP_CFG1 &= ~(0x07);OP_CFG1 |= (0x07&(x<<0));}//OP工作模式选择，1:模式1输入共模电压1/2VCC~VCC-1.2V；4:模式2输入共模电压0.1V~1/2VCC；其它保留
#define OP_IN_A_SET(x) 			{OP_CFG2 &= ~(0xE0);OP_CFG2 |= (0xE0&(x<<5));}//OP内部放大倍数选择，0:10倍; 1:15倍；2:20倍；3：25倍；4:30倍；5:35倍；6:40倍；7:45倍；
#define OP_I_SET(x) 				{OP_CFG2 &= ~(0x1F);OP_CFG2 |= (0x1F&(x<<0));}//OP注入电流选择,使用时从0x83CF(模式1)/0x83D1(模式2)读加校准值写入该寄存器
#define OP_PD_SET(x) 				{PD_ANA  &= ~(0x08);PD_ANA  |= (0x08&(x<<3));}//OP控制寄存器，0：打开;1:关闭

extern void OP_Init(void);

#endif