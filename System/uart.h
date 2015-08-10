#ifndef __UART_H__
#define __UART_H__

#include<reg52.h> //包含头文件，一般情况不需要改动，头文件包含特殊功能寄存器的定义                        
#include "../Common.h"


void UART_Initial(void);
void UART_SendByte(unsigned char dat);
void UART_SendStr(unsigned char *s);
void UART_SendASCII(unsigned char bDat);
void UART_SendInfor(U8 *pInfo, U16 dDat);


#endif
