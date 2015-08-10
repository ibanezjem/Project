#ifndef __DHT11_H__
#define __DHT11_H__

// ��ʪ�ȴ������������ݵĸ�ʽ����
typedef struct __tDHT11_INFO
{
	U8 m_ChkResult;		// У��ͨ�����
	U8 m_bRH_Int;		// ʪ����������
	U8 m_bRH_Float;		// ʪ��С������
	U8 m_bTem_Int;		// �¶���������
	U8 m_bTem_Float;	// �¶�С������		
	U8 m_bRes[3];		// �����ֽ�
}tDHT11_INFO;

sbit DHT11_CTRL = DH21_PAD; 


// ��ʪ�ȴ��������⺯��
tDHT11_INFO DHT11_Capture(void);
#endif
