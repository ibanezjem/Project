 /*
************************************************************
//					数据类型定义
************************************************************
*/

#ifndef __COMMOMM_H__
#define __COMMOMM_H__

#include<reg52.h> 

// 数据类型定义
typedef unsigned long      U32;
typedef unsigned short     U16;
typedef unsigned char      U8;

typedef unsigned long      xdata U32_X;
typedef unsigned short     xdata U16_X;
typedef unsigned char      xdata U8_X;

// 常用宏设计
#define HIGH_LEVEL	(1)	
#define LOW_LEVEL	(0)	

#define TRUE		(1)
#define FALSE		(0)

// 引脚定义
sbit P2_0 = P2^0;
sbit P2_1 = P2^1;
sbit P2_2 = P2^2;
sbit P2_3 = P2^3;

// ============= 根据实际的电路来进行修改 ================ //
// 按键
sbit KEY1 = P3^3;	// 定义按键端口
sbit KEY2 = P3^4;	// 定义按键端口
sbit KEY3 = P3^5;	// 定义按键端口

// 蜂鸣器
#define BEEP_PAD   		(P2^4)  // 默认使用1-0引脚

// I2C
#define I2C_CLK			(P2^6)
#define I2C_DATA		(P2^7)

// 温湿度传感器
#define DH21_PAD		(P3^7)

// YL40模块
#define YL40_CHANNEL 	(0)	// 选择测试的通道

// Debug模块
#define DEBUG_PAD		(P3^6)
sbit Debug_Pad = DEBUG_PAD;	
#define DEBUG_HIGH()	{Debug_Pad = HIGH_LEVEL;}
#define DEBUG_LOW()		{Debug_Pad = LOW_LEVEL;}

// 每次采样的间隔(5ms为单位)
#define SAMPLE_TIME		(200)
#endif
