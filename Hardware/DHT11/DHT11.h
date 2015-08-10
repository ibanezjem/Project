#ifndef __DHT11_H__
#define __DHT11_H__

// 温湿度传感器采样数据的格式定义
typedef struct __tDHT11_INFO
{
	U8 m_ChkResult;		// 校验通过标记
	U8 m_bRH_Int;		// 湿度整数数据
	U8 m_bRH_Float;		// 湿度小数数据
	U8 m_bTem_Int;		// 温度整数数据
	U8 m_bTem_Float;	// 温度小数数据		
	U8 m_bRes[3];		// 保留字节
}tDHT11_INFO;

sbit DHT11_CTRL = DH21_PAD; 


// 温湿度传感器对外函数
tDHT11_INFO DHT11_Capture(void);
#endif
