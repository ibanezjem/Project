 /*
************************************************************
//					�������Ͷ���
************************************************************
*/

#ifndef __COMMOMM_H__
#define __COMMOMM_H__

#include<reg52.h> 

// �������Ͷ���
typedef unsigned long      U32;
typedef unsigned short     U16;
typedef unsigned char      U8;

typedef unsigned long      xdata U32_X;
typedef unsigned short     xdata U16_X;
typedef unsigned char      xdata U8_X;

// ���ú����
#define HIGH_LEVEL	(1)	
#define LOW_LEVEL	(0)	

#define TRUE		(1)
#define FALSE		(0)

// ���Ŷ���
sbit P2_0 = P2^0;
sbit P2_1 = P2^1;
sbit P2_2 = P2^2;
sbit P2_3 = P2^3;

// ============= ����ʵ�ʵĵ�·�������޸� ================ //
// ����
sbit KEY1 = P3^3;	// ���尴���˿�
sbit KEY2 = P3^4;	// ���尴���˿�
sbit KEY3 = P3^5;	// ���尴���˿�

// ������
#define BEEP_PAD   		(P2^4)  // Ĭ��ʹ��1-0����

// I2C
#define I2C_CLK			(P2^6)
#define I2C_DATA		(P2^7)

// ��ʪ�ȴ�����
#define DH21_PAD		(P3^7)

// YL40ģ��
#define YL40_CHANNEL 	(0)	// ѡ����Ե�ͨ��

// Debugģ��
#define DEBUG_PAD		(P3^6)
sbit Debug_Pad = DEBUG_PAD;	
#define DEBUG_HIGH()	{Debug_Pad = HIGH_LEVEL;}
#define DEBUG_LOW()		{Debug_Pad = LOW_LEVEL;}

// ÿ�β����ļ��(5msΪ��λ)
#define SAMPLE_TIME		(200)
#endif
