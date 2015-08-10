 /*
*********************************************************************************************************
//	蜂鸣器函数
*********************************************************************************************************
*/
#include "Common.h"
#include "../../System/Delay.h"
#include "./Hardware/OhterHW/OhterHW.h"

U8 NumTable[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,
                        0xf8,0x80,0x90};

U8 NumTable_Dot[]={0x40,0x79,0x24,0x30,0x19,0x12,0x02,
                        0x78,0x00,0x10};	// 带小数点的共阴数码管段值

// *****************************************************************************
// 函数功能: 按键检测
// 入口参数: void
// 出口参数: U8 : 被按下的按键值
// 说    明: 
// *****************************************************************************
U8 Key_Detect(void)
{
	if (LOW_LEVEL == KEY1)
	{
		DelayMs(10); // 延时10MS 用于按键消抖

		if (LOW_LEVEL == KEY1)
		{
			return KEY1_PRESS;
		}
	}
	else if (LOW_LEVEL == KEY2)
	{
		DelayMs(10);//延时10MS 用于按键消抖
		
		if (LOW_LEVEL == KEY2)
		{
			return KEY2_PRESS;	//关闭蜂鸣器
		}
	}
	else if (LOW_LEVEL == KEY3)
	{
		DelayMs(10);//延时10MS 用于按键消抖
		
		if (LOW_LEVEL == KEY3)
		{
			return KEY3_PRESS;	//关闭蜂鸣器
		}
	}		
	else
	{
		return NO_KEY_PRESS;
	}
}

// *****************************************************************************
// 函数功能: 显示数值
// 入口参数: void
// 出口参数: U8 : 被按下的按键值
// 说    明: 
// *****************************************************************************
void LED_Display(U16 bInt, U16 bFloat)
{
	U8 bDecade;	 // 整数十位
	U8 bUnit;	 // 整数个位
	U8 bDecimal_1; // 小数1位
	U8 bDecimal_2; // 小数2为
	
	bDecade    = bInt / 10;
	bUnit      = bInt % 10;
	bDecimal_1 = bFloat / 10;
	bDecimal_2 = bFloat % 10;

	P0 = NumTable[bDecade];
	P2_0 = 0;
	DelayMs(1);
	P2_0 = 1;
	
	P0 = NumTable_Dot[bUnit];
	P2_1 = 0;
	DelayMs(1);
	P2_1 = 1;
	
	P0 = NumTable[bDecimal_1];
	P2_2 = 0;
	DelayMs(1);
	P2_2 = 1;
	
	P0 = NumTable[bDecimal_2];
	P2_3 = 0;
	DelayMs(1);
	P2_3 = 1;
}


