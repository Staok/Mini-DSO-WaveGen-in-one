/*
	adc_stc15.c
	
    Get voltage infor of VCC

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

*/

#include "adc_stc15.h"

#ifdef STC15

//����������ڽ�ADCģ�������IO����Ϊ����״̬PnM1.x=1,PnM0.x=0
//˵��:
// ADC�ĵ�9ͨ��(STC15ϵ�е�9ͨ����STC8ϵ�е�16ͨ��)�����������ڲ�BandGap�ο���ѹ��,�����ڲ�BandGap�ο���
//ѹ���ȶ�,������оƬ�Ĺ�����ѹ�ĸı���仯,���Կ���ͨ�����β�����һ�μ���
//��ɵõ��ⲿ�ľ�ȷ��ѹ.��ʽ����:
//
//STC15ϵ��10λADC
//ADCbg / Vbg = 1023 / VCC
//ADCx / Vx = 1023 / VCC
//
//STC8ϵ��12λADC
//ADCbg / Vbg = 4095 / VCC
//ADCx / Vx = 4095 / VCC
//
//�������β�����ʱ������?,VCC�ĵ�ѹ�ڴ��ڼ�Ĳ����ɺ��Բ���
//�Ӷ����Ƴ� ADCbg / Vbg = ADCx / Vx
//��һ���ó� Vx = Vbg * ADCx / ADCbg
//����:ADCbgΪBandgap��ѹ��ADC����ֵ
// VbgΪʵ��Bandgap�ĵ�ѹֵ,�ڵ�Ƭ������CP����ʱ��¼�Ĳ���,��λΪ����(mV)
// ADCxΪ�ⲿ�����ѹ��ADC����ֵ
// Vx�ⲿ�����ѹ��ʵ�ʵ�ѹֵ,��λΪ����(mV)
//
//����Ĳ��Է���:���Ƚ�P1ASF��ʼ��Ϊ0,���ر�����P1�ڵ�ģ�⹦��
//Ȼ��ͨ��������ADCת���ķ�����ȡ��0ͨ����ֵ,����ͨ��ADC�ĵ�9ͨ����ȡ��ǰ
//�ڲ�BandGap�ο���ѹֵADCbg,Ȼ��������ⲿ��ѹ�����ADCͨ��,������
//�ⲿ�����ѹ��ADC����ֵADCx,��������RAM������ROM����ȡʵ��Bandgap�ĵ�ѹֵVbg,
//���ͨ����ʽVx = Vbg * ADCx / ADCbg,���ɼ�����ⲿ�����ѹ��ʵ�ʵ�ѹֵVx
//-----------------------------------------

//BGV�ڲ��ο���ѹ
int *BGV;
//int *Vbg_RAM;

void ADCInit()
{
    CLK_DIV &= ~ADRJ;                    //��ADRJ=0ʱ�� 10λA/Dת������ĸ�8λ�����ADC_RES�У���2λ�����ADC_RESL�ĵ�2λ��
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL; //ADC�ϵ磬�趨ת���ٶ�
                                         //	ADC_CONTR|=ADC_POWER;			�ٷ�����������ͻ�ķ�ʽ��ADC_CONTR��ֵ
                                         //	ADC_CONTR|=ADC_SPEEDLL;
    Delay5ms();                          //ADC�ϵ粢��ʱ
}

int ADCRead(uint8 chx)
{
    int res;
    ADC_RES = 0; //�������Ĵ���
    ADC_RESL = 0;
    switch (chx)
    {
    case ADC_CHS_BG:
        P1ASF = P1ASF_BG;
        chx = P1ASF_BG;
        break;
    case ADC_CHS_10:
        P1ASF = P1ASF_0;
        break;
    case ADC_CHS_11:
        P1ASF = P1ASF_1;
        break;
    case ADC_CHS_12:
        P1ASF = P1ASF_2;
        break;
    case ADC_CHS_13:
        P1ASF = P1ASF_3;
        break;
    case ADC_CHS_14:
        P1ASF = P1ASF_4;
        break;
    case ADC_CHS_15:
        P1ASF = P1ASF_5;
        break;
    case ADC_CHS_16:
        P1ASF = P1ASF_6;
        break;
    case ADC_CHS_17:
        P1ASF = P1ASF_7;
        break;
    }
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL | ADC_START | chx;
    //ADC_CONTR|=ADC_START;		//�ٷ�����������ͻ�ķ�ʽ��ADC_CONTR��ֵ
    //ADC_CONTR&=~0x07;
    _nop_(); //�ȴ�4��NOP
    _nop_();
    _nop_();
    _nop_();
    while (!(ADC_CONTR & ADC_FLAG))
        ;                            //�ȴ�ADCת�����
    ADC_CONTR &= ~ADC_FLAG;          //���ADC��־
    res = (ADC_RES << 2) | ADC_RESL; //��ȡ ADC ���
    return res;
}

uint16 Get_VCC_Voltage()
{
    uint32 ADCbg;
    uint16 VCC;
    int i;
    BGV = (int code *)BGV_ADR; //��ROM��ȡ��BandGap��ѹֵ����λmV����STC-ISP���س���ʱ��ѡ�С��ڳ�������������Ҫ������
    //Vbg_RAM = (int idata *)0xef; 	//��RAM��ȡ��BandGap��ѹֵ����λmV
    ADCInit(); //���δ��ڲ�A/Dת��ģ���Դ�����ʵ���ʱ�����ڲ�ģ���Դ�ȶ���������A/Dת��

    //��һ��:ͨ��ADC�ĵ�9ͨ����ȡBandgap��ѹ��ADC����ֵ
    ADCRead(ADC_CHS_BG);
    ADCRead(ADC_CHS_BG); //ǰ�������ݶ���
    ADCbg = 0;
    for (i = 0; i < 512; i++)
    {
        ADCbg += ADCRead(ADC_CHS_BG); //��ȡ 8 ������
    }
    ADCbg >>= 9; //ȡƽ��ֵ
    VCC = *BGV * 1023UL / ADCbg;
    return VCC;
}

#endif