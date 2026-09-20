#ifndef __BF7613BMXX_XXXX_API_READ_UID_H__
#define __BF7613BMXX_XXXX_API_READ_UID_H__

#define INF_READ_EN							0	// 1:使能编译，0:不使能编译

#if (INF_READ_EN == 1)
extern void CHIP_UDI_Read(void);
extern uchar xdata UID_Buffer[];
#endif

#endif