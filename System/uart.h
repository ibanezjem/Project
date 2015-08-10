#ifndef __UART_H__
#define __UART_H__

#include<reg52.h> //����ͷ�ļ���һ���������Ҫ�Ķ���ͷ�ļ��������⹦�ܼĴ����Ķ���                        
#include "../Common.h"


void UART_Initial(void);
void UART_SendByte(unsigned char dat);
void UART_SendStr(unsigned char *s);
void UART_SendASCII(unsigned char bDat);
void UART_SendInfor(U8 *pInfo, U16 dDat);


#endif
