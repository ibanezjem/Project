/*********************************************************************************
* ����дʱ�䡿�� 2011.07.07
* ����    �ߡ��� �������
* ����    ������ V1.0
* ����    վ���� http://ylelectronic.taobao.com/ 
* ��Q      Q���� 348439350
* ����    ������ �˳��������ѧϰ��ο���������ע����Ȩ��������Ϣ��
* ���������ܡ��� DA-AD����			   			            			    
* ��ʹ��˵������ ��Ƭ����STC89C52 
                 ���ڲ����ʣ�9600
				 ����һ������4���ֽ�  
				 1 ��������
				 2 ��������
				 3 ����
				 4 �ɵ�0-5V��ѹ����ɫ��λ�����ڣ�
				 
**********************************************************************************/
/********************************************************************************************/

#include<reg52.h>    //������Ƭ���Ĵ�����ͷ�ļ�
#include "./I2C.H"
#include "../../Common.h"
#include "../../system/Uart.h"

#define uchar unsigned char
#define PCF8591 0x90    //PCF8591 ��ַ

// ��������
//U8 code table[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,
//                        0xf8,0x80,0x90};

/*******************************************************************
DAC �任, ת������               
*******************************************************************/
bit DACconversion(unsigned char sla,unsigned char c,  unsigned char Val)
{
   Start_I2c();              //��������
   SendByte(sla);            //����������ַ
   if(ack==0)return(0);
   SendByte(c);              //���Ϳ����ֽ�
   if(ack==0)return(0);
   SendByte(Val);            //����DAC����ֵ  
   if(ack==0)return(0);
   Stop_I2c();               //��������
   return(1);
}

/*******************************************************************
ADC�����ֽ�[����]���ݺ���               
*******************************************************************/
bit ISendByte(unsigned char sla,unsigned char c)
{
   Start_I2c();              //��������
   SendByte(sla);            //����������ַ
   if(ack==0)return(0);
   SendByte(c);              //��������
   if(ack==0)return(0);
   Stop_I2c();               //��������
   return(1);
}

// *****************************************************************************
// ��������: ADC���ֽ����ݺ���
// ��ڲ���: void
// ���ڲ���: void
// ˵	 ��: 
// *****************************************************************************
U8 IRcvByte(U8 sla)
{  
	unsigned char c;

	Start_I2c();          //��������
	SendByte(sla+1);      //����������ַ
	if(ack==0)return(0);
	c=RcvByte();          //��ȡ����0

	Ack_I2c(1);           //���ͷǾʹ�λ
	Stop_I2c();           //��������
	return(c);
}


// *****************************************************************************
// ��������: DA-AD��������
// ��ڲ���: U8 bChannel : ѡ�������ͨ��
//			 U8 bDAC_Val : ѡ��ͨ��4������DACת����ֵ
// ���ڲ���: void
// ˵    ��: 
// *****************************************************************************
U8 ADC_Sample(U8 bChannel, U8 bDAC_Val)
{
	U8 bRecData;	// �������л�ȡ������
	
	switch(bChannel)
	{
		case 0: 
		{
			UART_SendStr("PhotoResist:");
			ISendByte(PCF8591,0x41);
			bRecData = IRcvByte(PCF8591);  //ADC0 ģ��ת��1 	 ��������
			break;
		}
		case 1: 
		{
			UART_SendStr("Thermistor:");
			ISendByte(PCF8591,0x42);
			bRecData = IRcvByte(PCF8591);  //ADC1  ģ��ת��2   ��������
			break;  
		}
		case 2: 
		{
			UART_SendStr("Nothing:");
			ISendByte(PCF8591,0x43);
			bRecData = IRcvByte(PCF8591);  //ADC2	 ģ��ת��3		����
			break;  
		}		
		case 3: 
		{
			UART_SendStr("ADC:");
			ISendByte(PCF8591,0x40);
			bRecData = IRcvByte(PCF8591);  //ADC3	ģ��ת��4		�ɵ�0-5v
			break;  
		}
		case 4: 
		{
			UART_SendStr("DAC:");
			DACconversion(PCF8591,0x40, bDAC_Val); // DAC	   ��ģת��
			break;
		}
	}

	UART_SendStr("Current:");
	UART_SendASCII(bRecData);
	return bRecData;
}
