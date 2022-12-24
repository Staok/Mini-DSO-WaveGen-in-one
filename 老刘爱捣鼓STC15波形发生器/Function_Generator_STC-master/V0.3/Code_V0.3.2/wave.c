/*
	wave.c
	
    Generate Square and Sine waveform functions

	GitHub: https://github.com/CreativeLau/Function_Generator_STC
	
	Copyright (c) 2020 Creative Lau (CreativeLauLab@gmail.com)

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.

    Note:
    2020-05-17 Update
    1. Fix an error in PWM_Config(), may casue wrong output PWM frequency when frequency less than 50Hz.
    1. ����PWM_Config()�е�һ���㷨���󣬻�����С��50Hz�ķ����������Ƶ�ʡ�
*/

#include "wave.h"
#include "T_SineTable.h"

bit WAVE_ON = 0;                       //������α�־λ 1:ON 0:OFF
uint8 PWMCKS_PS = 0;                   //ϵͳʱ�ӷ�Ƶϵ��
uint32 PWM_Hz = 100;                   //PWMƵ��
uint32 PWM_Hz_Pre;                     //��¼��һ��PWMƵ��
uint32 PWM_Cycle;                      //PWM����(���ֵΪ32767)
int8 PWM_Duty = 50;                    //PWMռ�ձ�
uint32 PWM_Width;                      //PWM�ߵ�ƽ���
uint32 SIN_Hz = 100;                   //SINƵ��
uint8 Wave_Shape = 1;                  //���α�־ 1:���� 2:���Ҳ�
uint8 Wave_Shape_Pre;                  //�ϴβ��α�־
uint16 PWM_Index = 0;                  //SPWM�������
uint16 T_SinTable_Current[SIN_POINTS]; //����ԭʼSINֵ�����µ�SIN��
uint8 Sin_Table_Times = 1;             //SIN����
uint32 PWM1_high, PWM1_low;
uint16 n, n_high, n_low;

void Set_PWMCKS_PS(void)
{
    if (PWM_Hz <= (FOSC / 0X7fff)) //0X7fff=32767��15λPWM�����������ֵ�����FOSC / 0X7fff����ʱ�Ӳ���Ƶ�������PWM_Hz����Сֵ
    {
        PWMCKS_PS = 0x0F;
    }
    else
    {
        PWMCKS_PS = 0x00;
    }
}

void Set_PWM_Cycle(void) //PWM���ڣ�����50Hzʱʹ����ǿ��PWM���η�����ֱ�����ɣ�����STC15W4K��STC8��С��50Hzʹ�ö�ʱ������GPIO��ת
{
    if (PWM_Hz < 50)
    {
        PWM_Cycle = FOSC / CKS_50HZ / PWM_Hz; //ʹ�ö�ʱ��1ѭ�����ɵ�Ƶ����
    }
    else
    {
        PWM_Cycle = (FOSC * 10 / (PWMCKS_PS + 1) / PWM_Hz + 5) / 10 - 1; //ʹ��STC15W4K�ĸ߾���PWM���ɸ�Ƶ����
    }
}

void Set_PWM_Width(void) //PWM�ߵ�ƽ���
{
    PWM_Width = (PWM_Cycle * PWM_Duty * 10 + 5) / 10 / 100;
}

void Set_Sin_Table_Times()
{
    Sin_Table_Times = 1;
    if (SIN_Hz > 6000)
        Sin_Table_Times = 100;
    else if (SIN_Hz > 5000)
        Sin_Table_Times = 50;
    else if (SIN_Hz > 3000)
        Sin_Table_Times = 40;
    else if (SIN_Hz > 2500)
        Sin_Table_Times = 25;
    else if (SIN_Hz > 1000)
        Sin_Table_Times = 20;
    else if (SIN_Hz > 500)
        Sin_Table_Times = 8;
    else if (SIN_Hz > 250)
        Sin_Table_Times = 4;
    else if (SIN_Hz > 100)
        Sin_Table_Times = 2;

    PWM_Hz = SIN_Hz * SIN_POINTS / Sin_Table_Times;
}

void Wave_OFF(void) //�رղ������
{
    P_SW2 |= 0x80;  //����xSFR
    PWMCR &= ~0x80; //�ر�PWMģ�� ������50Hz�ķ��������Ҳ���
    PWMCR &= ~0x40; //��ֹPWM�����������ж� �����Ҳ���
    PWMIF &= ~CBIF; //����жϱ�־
    P_SW2 &= ~0x80; //�ָ�����XRAM

    TR1 = 0; //�رն�ʱ��1��С��50Hz�ķ�����
    TF1 = 0; //�����ʱ��1�жϱ�־

    //PWM IO״̬
    PWM3 = 0;      //����PWM3 P4.5�͵�ƽ ����
    PWM4 = 0;      //����PWM4 P4.4�͵�ƽ	���Ҳ�
    P4M1 |= 0x30;  //����P4.4(PWM4_2),4.5(PWM3_2)Ϊ����
    P4M0 &= ~0x30; //����P4.4(PWM4_2),4.5(PWM3_2)Ϊ����
}

void PWM_Config(void)
{
    if (WAVE_ON)
    {
        //PWM IO״̬
        PWM3 = 0;      //����PWM3 P4.5�͵�ƽ
        P4M1 &= ~0x20; //����P4.5Ϊ�������
        P4M0 |= 0x20;  //����P4.5Ϊ�������
                       /* ռ�ձ�Ϊ0ʱ��ʼ������͵�ƽ
           Output low when duty cycle is 0*/
        if (PWM_Width == 0)
        {
            TR1 = 0;        //�رն�ʱ��1��С��50Hz�ķ�����
            TF1 = 0;        //�����ʱ��1�жϱ�־
            PWMCR &= ~0x02; //PWMͨ��3�Ķ˿�ΪGPIO
            PWM3 = 0;       //PWMͨ��3ʼ������͵�ƽ
        }
        /* ռ�ձ�Ϊ100%ʱ��ʼ������ߵ�ƽ
           Output high when duty cycle is 100%*/
        else if (PWM_Width == PWM_Cycle)
        {
            TR1 = 0;        //�رն�ʱ��1��С��50Hz�ķ�����
            TF1 = 0;        //�����ʱ��1�жϱ�־
            PWMCR &= ~0x02; //PWMͨ��3�Ķ˿�ΪGPIO
            PWM3 = 1;       //PWMͨ��3ʼ������ߵ�ƽ
        }
        /* PWMƵ�ʴ��ڵ���50ʱ��ʹ��������ǿ��PWM���
           Use enhanced PWM waveform generator when PWM frequency higher than or equal to 50*/
        else if (PWM_Hz >= 50)
        {
            P_SW2 |= 0x80;       //����xSFR
            PWMCKS = 0x00;       //PWMʱ��ѡ��
            PWMCKS |= PWMCKS_PS; //ϵͳʱ�ӷ�Ƶ��ΪPWMʱ��
            PWMC = PWM_Cycle;    //����PWM����
            PWMCFG &= ~0x02;     //����PWM�������ʼ��ƽ
            PWM3T1 = 0;          //��һ�η�ת������
            PWM3T2 = PWM_Width;  //�ڶ��η�ת������
            PWM3CR = 0x08;       //PWM3�����P4.5
            PWMCR = 0x02;        //ʹ��PWM3���
            PWMCR &= ~0x40;      //��ֹPWM�����������ж�
            PWMCR |= 0x80;       //ʹ��PWMģ��
            P_SW2 &= ~0x80;      //�ָ�����XRAM
        }
        /* PWMƵ��С��50ʱ��ʹ�ö�ʱ�����
           Use timer when PWM frequency lower than 50*/
        else
        {
            PWMCR &= ~0x02;                                                      //PWMͨ��3�Ķ˿�ΪGPIO
            PWM3 = 0;                                                            //PWMͨ��3����͵�ƽ
            PWM1_high = PWM_Width;                                               //�ߵ�ƽ������ʱ��
            PWM1_low = PWM_Cycle - PWM_Width;                                    //�͵�ƽ������ʱ��
            n_high = PWM1_high / 65536;                                          //�ߵ�ƽ������ʱ������Ĵ���
            n_low = PWM1_low / 65536;                                            //�͵�ƽ������ʱ������Ĵ���
            PWM1_high = 65535 - PWM1_high % 65536 + FOSC * 2 / 10000 / CKS_50HZ; //��ʱ����ֵ��������Ϊ�ж�PWM��ƽ�仯��ʱ��200us
            PWM1_low = 65535 - PWM1_low % 65536 + FOSC * 2 / 10000 / CKS_50HZ;   //��ʱ����ֵ��������Ϊ�ж�PWM��ƽ�仯��ʱ��200us
            //������㷨֮ǰд���ˣ����������Ƶ�ʴ���������
            if (PWM1_high > 65535) //������Ķ�ʱ����ֵ����65535���ٴ�����
            {
                n_high--;
                PWM1_high -= 65535;
            }
            if (PWM1_low > 65535) //������Ķ�ʱ����ֵ����65535���ٴ�����
            {
                n_low--;
                PWM1_low -= 65535;
            }
            n = n_low;
            TH1 = (uint8)(PWM1_low >> 8); //���������͵�ƽ����װ�ص͵�ƽʱ�䡣
            TL1 = (uint8)PWM1_low;
            TR1 = 1; //��ʱ��1��ʼ����
        }
    }
    else
    {
        Wave_OFF();
    }
}

void Sin_Wave_Config(void)
{
    int i;
    float Sin_Cycle_times; //SPWM_interrupt�жϺ���������Ҫʱ�䣬SPWMƵ��120K��STC15W4K32S4�����ޣ��ٸ߾�������ͨ��SPWM_interrupt����ռ�ձ���

    //T_SinTable����ֵ�Ǹ���SIN_TABLE_PWM_HZ����õ�������ڣ�����ΪFOSC/SIN_TABLE_PWM_HZ��24MHz��ʱ��150kHz��Ӧ����160
    //���ݵ�ǰ��PWM_Hz���¼������ұ�ʹ�����Ҳ���������
    Sin_Cycle_times = SIN_TABLE_PWM_HZ * 1.0 / PWM_Hz; //��ǰPWM_Hz���SIN_TABLE_PWM_HZ�ı���
    for (i = 0; i < SIN_POINTS; i += Sin_Table_Times)  //���¼������ұ�������ƫ����SIN_OFFSET
    {
        T_SinTable_Current[i] = T_SinTable[i] * Sin_Cycle_times + SIN_OFFSET;
    }

    if (WAVE_ON)
    {
        //PWM IO״̬
        PWM4 = 0;      //����PWM4 P4.4�͵�ƽ
        P4M1 &= ~0x10; //����P4.4Ϊ�������
        P4M0 |= 0x10;  //����P4.4Ϊ�������

        P_SW2 |= 0x80;       //����xSFR
        PWMCR &= ~0x80;      //�ر�PWMģ��
        PWMCR &= ~0x40;      //��ֹPWM�����������ж�
        PWMIF &= ~CBIF;      //����жϱ�־
        PWMCKS = 0x00;       //PWMʱ��ѡ��
        PWMCKS |= PWMCKS_PS; //ϵͳʱ�ӷ�Ƶ��ΪPWMʱ��
        PWMC = PWM_Cycle;    //����PWM����
        PWM_Index = 0;
        PWM4T1 = 0;                             //��һ�η�ת������
        PWM4T2 = T_SinTable_Current[PWM_Index]; //�ڶ��η�ת������
        PWM_Index += Sin_Table_Times;
        PWMCFG &= ~0x04; //����PWM4�������ʼ��ƽ
        PWM4CR = 0x08;   //PWM4�����P4.4�����ж�
        PWMCR |= 0x04;   //ʹ��PWM4���
        PWMCR |= 0x40;   //����PWM�����������ж�
        PWMCR |= 0x80;   //ʹ��PWMģ��
        P_SW2 &= ~0x80;  //�ָ�����XRAM
    }
    else
    {
        Wave_OFF();
    }
}

/* 
   */
void Set_Wave_Shape(void)
{
    if(Wave_Shape==1) //����
        PWM_Config();
    else if (Wave_Shape == 2) //���Ҳ�
        Sin_Wave_Config();
}

/* �����������Ҳ���SPWM�ж�
   SPWM Interrupt for generating the sine waveform*/
void SPWM_interrupt(void) interrupt SPWM_VECTOR
{
    PWMIF &= ~CBIF; //����жϱ�־
    _push_(P_SW2);  //����SW2����
    P_SW2 |= 0x80;  //����XFR
    PWM4T2 = T_SinTable_Current[PWM_Index];
    if ((PWM_Index += Sin_Table_Times) >= SIN_POINTS)
        PWM_Index = 0;
    _pop_(P_SW2); //�ָ�SW2����
}

/* 50Hz����PWMʹ��Timer1�жϲ���
   Generate PWM below 50Hz by Timer1 Interrupt*/
void TIMER1_interrupt(void) interrupt TIMER_1
{
    TR1 = 0;
    if (n-- == 0)
    {
        PWM3 = !PWM3;
        Delay200us(); //��ʱ�ȴ�PWM3��ƽ�仯��200us 24MHz��Ӧ4800���ڣ��ڼ�ʱ����ֵ�۳�
        if (PWM3)
        {
            n = n_high;
            TH1 = (uint8)(PWM1_high >> 8); //���������ߵ�ƽ����װ�ظߵ�ƽʱ�䡣
            TL1 = (uint8)PWM1_high;
        }
        else
        {
            n = n_low;
            TH1 = (uint8)(PWM1_low >> 8); //���������͵�ƽ����װ�ص͵�ƽʱ�䡣
            TL1 = (uint8)PWM1_low;
        }
    }
    else
    {
        TH1 = 0x00;
        TL1 = 0x00;
    }
    TF1 = 0;
    TR1 = 1;
}
