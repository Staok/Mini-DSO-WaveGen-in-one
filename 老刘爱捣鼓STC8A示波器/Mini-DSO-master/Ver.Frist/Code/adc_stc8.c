#include "adc_stc8.h"

#ifdef STC8
uint16 *BGV;
bit Stop_Aquire = 0;
static uint16 ADCBuf[SAMPLE_NUM];

void ADCInit(uint8 scale_h)
{
    uint8 ADC_SPEED;
    switch (scale_h)
    {
    case 0:
        ADC_SPEED = ADC_SPEED_512;
        break;
    case 1:
        ADC_SPEED = ADC_SPEED_512;
        break;
    case 2:
        ADC_SPEED = ADC_SPEED_512;
        break;
    case 3:
        ADC_SPEED = ADC_SPEED_512;
        break;
    case 4:
        ADC_SPEED = ADC_SPEED_512;
        break;
    case 5:
        ADC_SPEED = ADC_SPEED_512;
        break;
    case 6:
        ADC_SPEED = ADC_SPEED_512;
        break;
    case 7:
        ADC_SPEED = ADC_SPEED_512;
        break;
    case 8:
        ADC_SPEED = ADC_SPEED_352;
        break;
    case 9:
        ADC_SPEED = ADC_SPEED_192;
        break;
    case 10:
        ADC_SPEED = ADC_SPEED_32;
        break;
    case 11:
        ADC_SPEED = ADC_SPEED_32;
        break;
    }
    ADCCFG = RESFMT | ADC_SPEED; //����Ҷ��룬���� ADC ʱ��Ϊϵͳʱ��/2/16/16
    ADC_CONTR = ADC_POWER;       //ʹ�� ADC ģ��
    Delay5ms();                  //ADC�ϵ粢��ʱ
}

uint16 ADCRead(uint8 chx)
{
    uint16 res;
    ADC_RES = 0;            //�������Ĵ���
    ADC_RESL = 0;           //�������Ĵ���
    ADC_CONTR &= 0xF0;      //ѡ��ADC����ͨ��
    ADC_CONTR |= chx;       //ѡ��ADC����ͨ��
    ADC_CONTR |= ADC_START; //���� AD ת��
    _nop_();
    _nop_();
    while (!(ADC_CONTR & ADC_FLAG))
        ;                            //��ѯ ADC ��ɱ�־
    ADC_CONTR &= ~ADC_FLAG;          //����ɱ�־
    res = (ADC_RES << 8) | ADC_RESL; //��ȡ ADC ���
    return res;
}

void GetBGV(void)
{
	BGV = (uint16 code *)BGV_ADR;
}

uint16 GetVoltage(uint8 chx, uint16 lsb)
{
    uint16 ADCbg;
    uint16 ADCx;
    uint16 Vx;
    uint8 i;
    
    ADCInit(0); //ADC ��ʼ��

    //ͨ��ADC�ĵ�16ͨ����ȡBandgap��ѹ��ADC����ֵ
    ADCRead(ADC_CHS_BG);
    ADCRead(ADC_CHS_BG); //ǰ�������ݶ���
    ADCbg = 0;
    for (i = 0; i < 16; i++)
    {
        ADCbg += ADCRead(ADC_CHS_BG); 
    }
    ADCbg >>= 4; //ȡƽ��ֵ

    //ͨ��ADC��chxͨ����ȡ�ⲿ�����ѹ��ADC����ֵ
    ADCRead(chx);
    ADCRead(chx); //ǰ�������ݶ���
    ADCx = 0;
    for (i = 0; i < 16; i++)
    {
        ADCx += ADCRead(chx); 
    }
    ADCx >>= 4; //ȡƽ��ֵ

    //ͨ����ʽ�����ⲿ�����ʵ�ʵ�ѹֵ
	GetBGV();
    Vx = (uint32)*BGV * ADCx * lsb / ADCbg;
    return Vx;
}

uint16 GetBGADC()
{
    uint16 ADCbg;
    uint8 i;
    //BGV = (uint16 code *)BGV_ADR;
    ADCInit(0); //ADC ��ʼ��

    //ͨ��ADC�ĵ�16ͨ����ȡBandgap��ѹ��ADC����ֵ
    ADCRead(ADC_CHS_BG);
    ADCRead(ADC_CHS_BG); //ǰ�������ݶ���
    ADCbg = 0;
    for (i = 0; i < 16; i++)
    {
        ADCbg += ADCRead(ADC_CHS_BG); //��ȡ 8 ������
    }
    ADCbg >>= 4; //ȡƽ��ֵ
    return ADCbg;
}

//	ADCRead(chx) Timing:500ms, 200ms, 100ms, 50ms, 20ms, 10ms, 5ms, 2ms, 1ms, 500us, 200us, 100us
//	��Ļ�ĺ���4��ÿ�����һ��ʱ�䷶Χ��ÿ��25��������
//	ADC_SPEED_512 28us
//	ADC_SPEED_480 26.2us
//	ADC_SPEED_448 25us
//	ADC_SPEED_416 23.8us
//	ADC_SPEED_384 22us
//	ADC_SPEED_352 20us
//	ADC_SPEED_320 18us
//	ADC_SPEED_288 17us
//	ADC_SPEED_256 15us
//	ADC_SPEED_224 14us
//	ADC_SPEED_192 12us
//	ADC_SPEED_160 10.4us
//	ADC_SPEED_128 9us
//	ADC_SPEED_96 7us
//	ADC_SPEED_64 5.6us
//	ADC_SPEED_32 4us
uint16 *GetADC(uint8 chx, uint8 scale_h)
{
    uint8 i;
	
    //���δ��ڲ�A/Dת��ģ���Դ�����ʵ���ʱ�����ڲ�ģ���Դ�ȶ���������A/Dת��
    ADCInit(scale_h);
	
    //ͨ��ADC�ĵ�xͨ����ȡ�ⲿ�����ѹ��ADC����ֵ
    ADCRead(chx);
    ADCRead(chx); //ǰ�������ݶ���

    switch (scale_h)
    {
    case 0: //500ms ADC_SPEED_512
        for (i = 0; i < SAMPLE_NUM; i++)
        {
            ADCBuf[i] = ADCRead(chx);
            Delay19972us();
            if (Stop_Aquire)
                break;
            //P15 = ~P15;
        }
        break;
    case 1: //200ms ADC_SPEED_512
        for (i = 0; i < SAMPLE_NUM; i++)
        {
            ADCBuf[i] = ADCRead(chx);
            Delay7972us();
            if (Stop_Aquire)
                break;
            //P15 = ~P15;
        }
        break;
    case 2: //100ms	ADC_SPEED_512
        for (i = 0; i < SAMPLE_NUM; i++)
        {
            ADCBuf[i] = ADCRead(chx);
            Delay3972us();
            if (Stop_Aquire)
                break;
            //P15 = ~P15;
        }
        break;
    case 3: //50ms ADC_SPEED_512
        for (i = 0; i < SAMPLE_NUM; i++)
        {
            ADCBuf[i] = ADCRead(chx);
            Delay1972us();
            if (Stop_Aquire)
                break;
            //P15 = ~P15;
        }
        break;
    case 4: //20ms ADC_SPEED_512
        for (i = 0; i < SAMPLE_NUM; i++)
        {
            ADCBuf[i] = ADCRead(chx);
            Delay772us();
            if (Stop_Aquire)
                break;
            //P15 = ~P15;
        }
        break;
    case 5: //10ms ADC_SPEED_512
        for (i = 0; i < SAMPLE_NUM; i++)
        {
            ADCBuf[i] = ADCRead(chx);
            Delay372us();
            //P15 = ~P15;
        }
        break;
    case 6: //5ms ADC_SPEED_512
        for (i = 0; i < SAMPLE_NUM; i++)
        {
            ADCBuf[i] = ADCRead(chx);
            Delay172us();
            //P15 = ~P15;
        }
        break;
    case 7: //2ms ADC_SPEED_512
        for (i = 0; i < SAMPLE_NUM; i++)
        {
            ADCBuf[i] = ADCRead(chx);
            Delay52us();
            //P15 = ~P15;
        }
        break;
    case 8: //1ms ADC_SPEED_352
        for (i = 0; i < SAMPLE_NUM; i++)
        {
            ADCBuf[i] = ADCRead(chx);
            Delay20us();
            //P15 = ~P15;
        }
        break;
    case 9: //500us	ADC_SPEED_192
        for (i = 0; i < SAMPLE_NUM; i++)
        {
            ADCBuf[i] = ADCRead(chx);
            Delay8us();
            //P15 = ~P15;
        }
        break;
    case 10: //200us ADC_SPEED_32
        for (i = 0; i < SAMPLE_NUM; i++)
        {
            ADCBuf[i] = ADCRead(chx);
            Delay4us();
            //P15 = ~P15;
        }
        break;
    case 11: //100us ADC_SPEED_32
        for (i = 0; i < SAMPLE_NUM; i++)
        {
            ADCBuf[i] = ADCRead(chx);
            //P15 = ~P15;
        }
        break;
    }
    return ADCBuf;
}

#endif
