//****************************************************************//
//	   DHT21ʹ�÷��� 
//��Ƭ�� AT89S52 �� STC89C52RC 
//����   ���ڷ�����ʪ������ ���� 11.0592M ������ 9600 
//Ӳ��   P2.0��ΪͨѶ������DHT11,DHT11�ĵ�Դ�͵����ӵ�Ƭ���ĵ�Դ�͵أ���Ƭ�����ڼ�MAX232���ӵ��� 
//��˾  �������    
//****************************************************************//
#include "../../common.h"
#include "./DHT11.h"
#include "../../System/Delay.h"
#include "../../system/Uart.h"

static U8 DHT11_RecData(void);

//--------------------------------
//-----ʪ�ȶ�ȡ�ӳ��� ------------
//--------------------------------
//----���±�����Ϊȫ�ֱ���--------
//----�¶ȸ�8λ== U8T_data_H------
//----�¶ȵ�8λ== U8T_data_L------
//----ʪ�ȸ�8λ== U8RH_data_H-----
//----ʪ�ȵ�8λ== U8RH_data_L-----
//----У�� 8λ == U8checkdata-----
//----��������ӳ�������----------
//---- Delay();, Delay_10us();,COM(); 
//--------------------------------
tDHT11_INFO DHT11_Capture(void)
{
	U8 bTimeOutFlag = FALSE; // ��ʱ���
	U8 bFlag;
	U8 bRH_Int;		// ʪ����������
	U8 bRH_Float;	// ʪ��С������
	U8 bTem_Int;	// �¶���������
	U8 bTem_Float;	// �¶�С������	
	U8 bParity; 	// У������
	U8 bCheckSum;	// ����У���
	tDHT11_INFO tDHT_info;	// ��ʪ�ȴ�������ȡ����ֵ
	
	// ��������18ms 
	DHT11_CTRL = LOW_LEVEL;
	DelayMs(18);
	
 	//������������������ ������ʱ20us
 	DHT11_CTRL = HIGH_LEVEL;
	DelayUs2x(2);

	// ������Ϊ���� �жϴӻ���Ӧ�ź� 
	DHT11_CTRL = HIGH_LEVEL;
	
 	// �жϴӻ��Ƿ��е͵�ƽ��Ӧ�ź� �粻��Ӧ����������Ӧ����������	  
    if (!DHT11_CTRL)
	{
		bFlag = 2;
		
		// �жϴӻ��Ƿ񷢳� 80us �ĵ͵�ƽ��Ӧ�ź��Ƿ����	 
		while((!DHT11_CTRL) && (bFlag++));

		if (1 == bFlag)	// ��ʱ
		{
			bTimeOutFlag = TRUE;
			UART_SendStr("DHT11_Timeout");
		}
		
		bFlag = 2;
		
		// �жϴӻ��Ƿ񷢳� 80us �ĸߵ�ƽ���緢����������ݽ���״̬
		while((DHT11_CTRL) && (bFlag++));

		if (1 == bFlag)	// ��ʱ
		{
			bTimeOutFlag = TRUE;
			UART_SendStr("DHT11_Timeout");
		}
			
		// ���ݽ���״̬		 
		bRH_Int = DHT11_RecData();
		bRH_Float = DHT11_RecData();
		bTem_Int = DHT11_RecData();
		bTem_Float = DHT11_RecData();
		bParity = DHT11_RecData();
		
		DHT11_CTRL = HIGH_LEVEL;

		//����У�� 	
		bCheckSum = (bRH_Int + bRH_Float + bTem_Int + bTem_Float);

		if ((bParity == bCheckSum) && (FALSE == bTimeOutFlag)) // У��ͨ������û�г�ʱ
		{
			tDHT_info.m_ChkResult  = TRUE;
			tDHT_info.m_bRH_Float  = bRH_Float;
			tDHT_info.m_bRH_Int    = bRH_Int;
			tDHT_info.m_bTem_Float = bTem_Float;
			tDHT_info.m_bTem_Int   = bTem_Int;
		}
		else	// У��ʧ��
		{
			tDHT_info.m_ChkResult  = FALSE;
			UART_SendStr("DHT11_ChksumError");
		}	
	}
	else  // �ӻ�ʱ���쳣
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

		while((!DHT11_CTRL) && bFlag++);	// �ӻ����ͣ�׼��������
		DelayUs2x(4);	// �ӳ�40us

		bLevel = 0;
		if (DHT11_CTRL)	// �ж�Pin�ϵĵ�ƽ�ߵ�
		{
			bLevel = 1;
		}
		
		bFlag=2;

		while((DHT11_CTRL) && bFlag++);	// �ȴӻ�����
		
		if (1 == bFlag)
		{
			break; //��ʱ������forѭ�� 	  
		}
		
		// �ж�����λ��0����1	 
		// ����ߵ�ƽ�߹�Ԥ��0�ߵ�ƽֵ������λΪ 1 
		bData <<= 1;
		bData |= bLevel;		
	}

	//DEBUG_HIGH();
	return bData;
}

