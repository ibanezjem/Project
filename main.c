 /*
*********************************************************************************************************
//	主函数
*********************************************************************************************************
*/
 
#include "REG52.h"
#include "Common.h"
#include "./Hardware/YL40/DA-AD.h"
#include "./Hardware/DHT11/DHT11.h"
#include "./Hardware/OhterHW/OhterHW.h"
#include "./system/Uart.h"
#include "./system/Delay.h"


// 函数声明
static void TaskHandle(U8 bCurrent, tDHT11_INFO tDHT_info);
static U8   g_bKeyValue; // 记录最后一次按下的按键值

// *****************************************************************************
// 函数功能: 主函数
// 入口参数: 
// 出口参数: 
// 说    明: 
// *****************************************************************************
void main(void)
{
	U8  bTempKey;
	U8  bFlag;				// 记录DHT11是否采样成功
	U16 wLoop;
	U8  bCurrent;			// 检测到的电流值
	tDHT11_INFO tDHT_info;	// 温湿度传感器获取的数值
	
	// 硬件初始化函数
	UART_Initial();  // 串口初始化
	Beep_Dis();	     // 关闭蜂鸣器
	EA = 1;          // 开总中断

	UART_SendStr("Start");

	bFlag = FALSE;
	wLoop = 0;
	g_bKeyValue = 0;
	bTempKey = 0;
	
	// 死循环，循环检测
	while(1)
	{
		g_bKeyValue = Key_Detect();
		
		if ((wLoop++) >= SAMPLE_TIME)
		{
			wLoop = 0;
			
			bCurrent  = ADC_Sample(3, 0);
			tDHT_info = DHT11_Capture();

			if (TRUE == tDHT_info.m_ChkResult)	// 温湿度采样成功
			{
				bFlag = TRUE;
			}
			else
			{
				bFlag = FALSE;
			}
			
			if (TRUE == bFlag)	// 温湿度采样成功
			{
				UART_SendStr("DHT11_RHI");
				UART_SendASCII(tDHT_info.m_bRH_Int);
				UART_SendStr("DHT11_RHF");
				UART_SendASCII(tDHT_info.m_bRH_Float);
				UART_SendStr("DHT11_TEMI");
				UART_SendASCII(tDHT_info.m_bTem_Int);
				UART_SendStr("DHT11_TEMF");
				UART_SendASCII(tDHT_info.m_bTem_Float);		
				
				TaskHandle(bCurrent, tDHT_info);
			}
			else
			{
				UART_SendStr("DHT11_Error");
			}
		}

		#if 1
		if (NO_KEY_PRESS != g_bKeyValue)	// 有不同的按键按下，切换显示的内容
		{
			bTempKey = g_bKeyValue;
		}

		// 显示采样的数值	
		if (KEY1_PRESS == bTempKey)	// 显示湿度
		{
			if (TRUE == bFlag)	// 温湿度采样成功
			{
				LED_Display(tDHT_info.m_bRH_Int, tDHT_info.m_bRH_Float);
			}
			else	// 湿度采样失败
			{
				LED_Display(99, 99);
			}	
		}
		else if (KEY2_PRESS == bTempKey) // 显示电流值
		{
			LED_Display(bCurrent, 0);
		}
		else if (KEY3_PRESS == bTempKey)	// 默认显示温度值
		{
			if (TRUE == bFlag)	// 温湿度采样成功
			{
				LED_Display(tDHT_info.m_bTem_Int, tDHT_info.m_bTem_Float);
			}
			else	// 湿度采样失败
			{
				LED_Display(99, 99);
			}
		}
		#endif
		DelayMs(2);	// 100ms循环一次
	}
}

// *****************************************************************************
// 函数功能: 装置处理温湿度和电流的函数
// 入口参数: U8 bCurrent           : 检测到的电流
//			 tDHT11_INFO tDHT_info : 温湿度信息
// 出口参数: void
// 说    明: 根据需求进行修改
// *****************************************************************************
void TaskHandle(U8 bCurrent, tDHT11_INFO tDHT_info)
{
	U8 bWarnFlag;
	
	/**************
	  报警条件判断
	***************/

	if (tDHT_info.m_bRH_Int < 80)	// 空气湿度小于80%
	{	
		if (bCurrent < 30)	// 漏电流小于30mA
		{
			bWarnFlag = FALSE;
		}
		else 
		{
			bWarnFlag = TRUE;
		}
	}
	else // 空气湿度大于等于80%
	{
		if (bCurrent < 60)	// 漏电流小于60mA
		{
			bWarnFlag = FALSE;
		}
		else 
		{
			bWarnFlag = TRUE;
		}		
	}
	
	// 满足报警条件 
	if (TRUE == bWarnFlag)
	{
		UART_SendStr("Start Beep!");
		Beep_En(); 	// 蜂鸣器响起
	}
	else
	{
		Beep_Dis();
	}
}


