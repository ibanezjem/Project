#ifndef __BEEP_H__
#define __BEEP_H__

sbit BEEP_CTRL = BEEP_PAD; 

// ���ݷ�������·��ȷ�������ƽ��ʹ�ܵĹ�ϵ
#define BEEP_EN     (0)
#define BEEP_DIS    (1)

// �ⲿʹ��
#define Beep_En()    {BEEP_CTRL = BEEP_EN;}
#define Beep_Dis()   {BEEP_CTRL = BEEP_DIS;}

#define NO_KEY_PRESS (0)
#define KEY1_PRESS	 (1)
#define KEY2_PRESS	 (2)
#define KEY3_PRESS	 (3)

U8 Key_Detect(void);
void LED_Display(U16 bInt, U16 bFloat);

#endif