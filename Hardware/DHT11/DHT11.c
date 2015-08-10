//****************************************************************//
//	   DHT21使用范例 
//单片机 AT89S52 或 STC89C52RC 
//功能   串口发送温湿度数据 晶振 11.0592M 波特率 9600 
//硬件   P2.0口为通讯口连接DHT11,DHT11的电源和地连接单片机的电源和地，单片机串口加MAX232连接电脑 
//公司  雁凌电子    
//****************************************************************//
#include "../../common.h"
#include "./DHT11.h"
#include "../../System/Delay.h"
#include "../../system/Uart.h"

static U8 DHT11_RecData(void);

//--------------------------------
//-----湿度读取子程序 ------------
//--------------------------------
//----以下变量均为全局变量--------
//----温度高8位== U8T_data_H------
//----温度低8位== U8T_data_L------
//----湿度高8位== U8RH_data_H-----
//----湿度低8位== U8RH_data_L-----
//----校验 8位 == U8checkdata-----
//----调用相关子程序如下----------
//---- Delay();, Delay_10us();,COM(); 
//--------------------------------
tDHT11_INFO DHT11_Capture(void)
{
	U8 bTimeOutFlag = FALSE; // 超时标记
	U8 bFlag;
	U8 bRH_Int;		// 湿度整数数据
	U8 bRH_Float;	// 湿度小数数据
	U8 bTem_Int;	// 温度整数数据
	U8 bTem_Float;	// 温度小数数据	
	U8 bParity; 	// 校验数据
	U8 bCheckSum;	// 数据校验和
	tDHT11_INFO tDHT_info;	// 温湿度传感器获取的数值
	
	// 主机拉低18ms 
	DHT11_CTRL = LOW_LEVEL;
	DelayMs(18);
	
 	//总线由上拉电阻拉高 主机延时20us
 	DHT11_CTRL = HIGH_LEVEL;
	DelayUs2x(2);

	// 主机设为输入 判断从机响应信号 
	DHT11_CTRL = HIGH_LEVEL;
	
 	// 判断从机是否有低电平响应信号 如不响应则跳出，响应则向下运行	  
    if (!DHT11_CTRL)
	{
		bFlag = 2;
		
		// 判断从机是否发出 80us 的低电平响应信号是否结束	 
		while((!DHT11_CTRL) && (bFlag++));

		if (1 == bFlag)	// 超时
		{
			bTimeOutFlag = TRUE;
			UART_SendStr("DHT11_Timeout");
		}
		
		bFlag = 2;
		
		// 判断从机是否发出 80us 的高电平，如发出则进入数据接收状态
		while((DHT11_CTRL) && (bFlag++));

		if (1 == bFlag)	// 超时
		{
			bTimeOutFlag = TRUE;
			UART_SendStr("DHT11_Timeout");
		}
			
		// 数据接收状态		 
		bRH_Int = DHT11_RecData();
		bRH_Float = DHT11_RecData();
		bTem_Int = DHT11_RecData();
		bTem_Float = DHT11_RecData();
		bParity = DHT11_RecData();
		
		DHT11_CTRL = HIGH_LEVEL;

		//数据校验 	
		bCheckSum = (bRH_Int + bRH_Float + bTem_Int + bTem_Float);

		if ((bParity == bCheckSum) && (FALSE == bTimeOutFlag)) // 校验通过并且没有超时
		{
			tDHT_info.m_ChkResult  = TRUE;
			tDHT_info.m_bRH_Float  = bRH_Float;
			tDHT_info.m_bRH_Int    = bRH_Int;
			tDHT_info.m_bTem_Float = bTem_Float;
			tDHT_info.m_bTem_Int   = bTem_Int;
		}
		else	// 校验失败
		{
			tDHT_info.m_ChkResult  = FALSE;
			UART_SendStr("DHT11_ChksumError");
		}	
	}
	else  // 从机时序异常
	{
		tDHT_info.m_ChkResult  = FALSE;
		UART_SendStr("DHT11_NoResp");
	}
	return tDHT_info;
}

U8 DHT11_RecData(void)
{
	U8 bCnt;
	U8 bFlag;
	U8 bLevel;
	U8 bData;

	bData = 0;  
	for(bCnt = 0; bCnt < 8; bCnt++)    
	{
		bFlag = 2;	

		while((!DHT11_CTRL) && bFlag++);	// 从机拉低，准备发数据
		DelayUs2x(4);	// 延迟40us

		bLevel = 0;
		if (DHT11_CTRL)	// 判断Pin上的电平高低
		{
			bLevel = 1;
		}
		
		bFlag=2;

		while((DHT11_CTRL) && bFlag++);	// 等从机拉低
		
		if (1 == bFlag)
		{
			break; //超时则跳出for循环 	  
		}
		
		// 判断数据位是0还是1	 
		// 如果高电平高过预定0高电平值则数据位为 1 
		bData <<= 1;
		bData |= bLevel;		
	}

	//DEBUG_HIGH();
	return bData;
}

