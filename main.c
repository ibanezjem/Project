 /*
*********************************************************************************************************
//	������
*********************************************************************************************************
*/
 
#include "REG52.h"
#include "Common.h"
#include "./Hardware/YL40/DA-AD.h"
#include "./Hardware/DHT11/DHT11.h"
#include "./Hardware/OhterHW/OhterHW.h"
#include "./system/Uart.h"
#include "./system/Delay.h"


// ��������
static void TaskHandle(U8 bCurrent, tDHT11_INFO tDHT_info);
static U8   g_bKeyValue; // ��¼���һ�ΰ��µİ���ֵ

// *****************************************************************************
// ��������: ������
// ��ڲ���: 
// ���ڲ���: 
// ˵    ��: 
// *****************************************************************************
void main(void)
{
	U8  bTempKey;
	U8  bFlag;				// ��¼DHT11�Ƿ�����ɹ�
	U16 wLoop;
	U8  bCurrent;			// ��⵽�ĵ���ֵ
	tDHT11_INFO tDHT_info;	// ��ʪ�ȴ�������ȡ����ֵ
	
	// Ӳ����ʼ������
	UART_Initial();  // ���ڳ�ʼ��
	Beep_Dis();	     // �رշ�����
	EA = 1;          // �����ж�

	UART_SendStr("Start");

	bFlag = FALSE;
	wLoop = 0;
	g_bKeyValue = 0;
	bTempKey = 0;
	
	// ��ѭ����ѭ�����
	while(1)
	{
		g_bKeyValue = Key_Detect();
		
		if ((wLoop++) >= SAMPLE_TIME)
		{
			wLoop = 0;
			
			bCurrent  = ADC_Sample(3, 0);
			tDHT_info = DHT11_Capture();

			if (TRUE == tDHT_info.m_ChkResult)	// ��ʪ�Ȳ����ɹ�
			{
				bFlag = TRUE;
			}
			else
			{
				bFlag = FALSE;
			}
			
			if (TRUE == bFlag)	// ��ʪ�Ȳ����ɹ�
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
		if (NO_KEY_PRESS != g_bKeyValue)	// �в�ͬ�İ������£��л���ʾ������
		{
			bTempKey = g_bKeyValue;
		}

		// ��ʾ��������ֵ	
		if (KEY1_PRESS == bTempKey)	// ��ʾʪ��
		{
			if (TRUE == bFlag)	// ��ʪ�Ȳ����ɹ�
			{
				LED_Display(tDHT_info.m_bRH_Int, tDHT_info.m_bRH_Float);
			}
			else	// ʪ�Ȳ���ʧ��
			{
				LED_Display(99, 99);
			}	
		}
		else if (KEY2_PRESS == bTempKey) // ��ʾ����ֵ
		{
			LED_Display(bCurrent, 0);
		}
		else if (KEY3_PRESS == bTempKey)	// Ĭ����ʾ�¶�ֵ
		{
			if (TRUE == bFlag)	// ��ʪ�Ȳ����ɹ�
			{
				LED_Display(tDHT_info.m_bTem_Int, tDHT_info.m_bTem_Float);
			}
			else	// ʪ�Ȳ���ʧ��
			{
				LED_Display(99, 99);
			}
		}
		#endif
		DelayMs(2);	// 100msѭ��һ��
	}
}

// *****************************************************************************
// ��������: װ�ô�����ʪ�Ⱥ͵����ĺ���
// ��ڲ���: U8 bCurrent           : ��⵽�ĵ���
//			 tDHT11_INFO tDHT_info : ��ʪ����Ϣ
// ���ڲ���: void
// ˵    ��: ������������޸�
// *****************************************************************************
void TaskHandle(U8 bCurrent, tDHT11_INFO tDHT_info)
{
	U8 bWarnFlag;
	
	/**************
	  ���������ж�
	***************/

	if (tDHT_info.m_bRH_Int < 80)	// ����ʪ��С��80%
	{	
		if (bCurrent < 30)	// ©����С��30mA
		{
			bWarnFlag = FALSE;
		}
		else 
		{
			bWarnFlag = TRUE;
		}
	}
	else // ����ʪ�ȴ��ڵ���80%
	{
		if (bCurrent < 60)	// ©����С��60mA
		{
			bWarnFlag = FALSE;
		}
		else 
		{
			bWarnFlag = TRUE;
		}		
	}
	
	// ���㱨������ 
	if (TRUE == bWarnFlag)
	{
		UART_SendStr("Start Beep!");
		Beep_En(); 	// ����������
	}
	else
	{
		Beep_Dis();
	}
}


