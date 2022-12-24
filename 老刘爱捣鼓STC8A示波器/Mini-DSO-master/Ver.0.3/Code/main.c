/*
    Mini DSO with STC MCU

    GitHub: https://github.com/CreativeLau/Mini-DSO
    
    Copyright (c) 2020 Creative Lau (creativelaulab@gmail.com)

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

     
    Version: V0.3
    MCU Type: STC8A8K64S4A12 @27MHz
    YouTube Tutorial(First Version): https://youtu.be/c6gBv6Jcz7w
    YouTube Tutorial(V0.3): https://youtu.be/-8PadlS7c4c
    Instructable(First Version): https://www.instructables.com/id/Make-Your-Own-OscilloscopeMini-DSO-With-STC-MCU-Ea/
    Instructable(V0.3): 
    Any question please contact CreativeLauLab@gmail.com
    YouTube Channel: https://www.youtube.com/c/CreativeLau

    Note:
    How to Operation:
        Main Interface - Parameter Mode:
            Single Click Encoder: Run/Stop sampling
            Double Click Encoder: Enter Wave Scroll Mode
            Long Press Encoder: Enter Settings Interface
            Rotate Encoder: Adjust parameters
            Rotate Encoder While Pressing: Switch between options
            
        Main Interface - Wave Scroll Mode: 
            Single Click Encoder: Run/Stop sampling
            Double Click Encoder: Enter Parameter Mode
            Long Press Encoder: Enter Settings Interface
            Rotate Encoder: Scroll waveform horizontally (only available when sampling stopped)
            Rotate Encoder While Pressing: Scroll waveform vertically (only available when sampling stopped)
            
        Settings Interface:
            Single Click Encoder: N/A
            Double Click Encoder: N/A
            Long Press Encoder: Return to Main Interface
            Rotate Encoder: Adjust parameters
            Rotate Encoder While Pressing: Switch between options

    Parameters in Main Interface:
        Seconds Per Division: "500ms", "200ms", "100ms", "50ms", "20ms", "10ms","5ms", "2ms", "1ms", "500us", "200us", "100us"(100us only available in Auto Trigger Mode)
        Voltage Range: Maximum voltage is 30V. Rotate Encoder clockwise continuous to enter auto range. Rotate Encoder anticlockwise to enter manual range. 
        Trigger Level: Set trigger voltage level. The trigger position will be put at the center of chart. 
                       You should set a correct Trigger Level in Single and Normal Trigger Mode in order to capture the waveform.
        Trigger Slope: Trigger on Rising or Falling Edge. 
                       You should set a correct Trigger Slop in Single and Normal Trigger Mode in order to capture the waveform.
        Trigger Mode:
            Auto:   Sweep continuous, indicator always on. Single click the encoder to stop or run sampling. 
                    If triggered, the waveform will be shown on the display and the trigger position will be put at the center of chart. 
                    Otherwise, the waveform will scroll irregular, and 'Fail' will be shown on the display.
            Normal: When complete pre-sampling, you can input signal. If triggered, waveform shown on the display and waiting for new trigger. 
                    If no new trigger, the waveform will be kept.
            Single: When complete pre-sampling, you can input signal. If triggered, waveform shown on display and stop sampling. 
                    User need to single click Encoder to start next sampling.
            For Normal Mode and Single Mode, be sure the trigger level has been adjusted correctly, otherwise no waveform will be shown on the display.

    Status in Main Interface:
        'Run': Sampling Running.
        'Stop': Sampling Stopped.
        'Fail': The Trigger Level beyond the waveform in Auto Trigger Mode.
        'Auto': Auto Voltage Range.
                    
    Parameters in Settings Interface:
        PMode(Plot Mode): Show waveform in Vector or Dots.
        LSB(Sampling Coefficient): 100 times of voltage dividing coefficient. e.g. the resistor for voltage dividing is 10k and 2k, calculate the voltage dividing coefficient (10+2)/2=6. Get the LSB=6x100=600.
        BRT(Brightness): Adjust OLED Brightness

    Saving Settings: When exit settings interface, all parameters in settings and main interface will be saved in EEPROM.

    Indicator:
    Generally, the indicator on means the sampling is running. 
    The more important use is in Single and Normal Trigger Mode, before get into the trigger stage, pre-sampling is required. 
    The indicator will not on during pre-sampling stage. We should not input signal until the indicator comes on. 
    The longer time scale selected, the longer waiting time of pre-sampling.

    2020-04-30 Update
    1. Add Single Sweep and Normal Sweep function. Set trigger value to catch the waveform mutation.
    2. According to datasheet, set ADC port to high-impedance.

    2020-05-3 Update
    1. Show frequency of waveform.
    2. Scroll waveform horizontally/vertically with EC11 Encoder.
    3. Zoom waveform vertically with EC11 Encoder.
    4. The trigger level could be customized.

    ����ʾ����
    �汾��V0.3
    ���ߣ�����������
    ��Ƭ���ͣ�STC8A8K64S4A12 @27MHz
    �κ���������ϵCreativeLauLab@gmail.com
    ���������ģ�ȫ��ͬ�����ڴ����Ĺ�ע��
    Bվ�̳̣����棩��https://www.bilibili.com/video/BV1ai4y1t79R
    Bվ�̳̣�V0.3����https://www.bilibili.com/video/BV1ai4y1t79R
    �͹�Ƶ��: https://www.youtube.com/c/CreativeLau

    ����˵����
        ������-ѡ������ģʽ��
            �������������л���ʼ/��ͣ����
            ˫�����������л�����ˮƽ����ģʽ/ѡ������ģʽ
            �������������������ý���
            ��ת���������޸ĵ�ǰ����
            ����ͬʱ��ת���������ڲ������л�
            
        ������-����ˮƽ����ģʽ��
            �������������л���ʼ/��ͣ����
            ˫�����������л�����ˮƽ����ģʽ/ѡ������ģʽ
            �������������������ý���
            ��ת��������ˮƽ�������Σ�����ͣ����״̬����Ч��
            ����ͬʱ��ת����������ֱ�������Σ�������ͣ����״̬����Ч��
            
        ���ý��棺
            ��������������Ч
            ˫������������Ч
            ����������������������
            ��ת���������޸ĵ�ǰѡ��
            ����ͬʱ��ת���������л�ѡ��

    �����������
        ����ʱ�����䣺"500ms", "200ms", "100ms", "50ms", "20ms", "10ms","5ms", "2ms", "1ms", "500us", "200us", "100us"(100us�����Զ�����ģʽ�¿���)
        �����ѹ���䣺�趨��ѹ�������ޣ����30V��˳ʱ����ת����������ѹ��������Ϊ0������Զ����̣���ʱ����ת�����ֶ�����
        ����ֵ���趨������ѹֵ������λ�ñ�������Ļ����
        �����������¼�ͷ���ֱ���������ش������½��ش���
        ������ʽ��
            Auto(�Զ�����)  ������������ָʾ��ʼ�յ�����ͨ������������������ͣ�������ɹ�ʱ��������λ����Ļ���ģ�����ʧ�������޹��ɹ�������Ļ�����ʾFail��־
            Normal(��ͨ����)���ȴ�Ԥ��������ָʾ�������ʾԤ������������ʱ���������źţ�
                              �����ɹ�����ʾ���Σ��������ȴ��´δ�����
                              ������µĴ����ɹ������Զ���ʾ�µĲ��Σ���û���µĴ����ɹ�����Ļ���α��ֲ�һֱ�ȴ��´δ�����
                              ��ע��������ȷ�Ĵ���ֵ������һֱ���ڵȴ�����״̬����Ļ������ʾ����
            Single(���δ���)���ȴ�Ԥ��������ָʾ�������ʾԤ������������ʱ���������źţ�
                              �����ɹ�����ʾ���Σ���ֹͣ���������û�������������ʼ�´β���	
                              ��ע��������ȷ�Ĵ���ֵ������һֱ���ڵȴ�����״̬����Ļ������ʾ����
            
    ������״̬��ʾ��	
        Run�����ڲ���
        Stop��ֹͣ����
        Fail���Զ�ģʽ�£�����ֵ�������η�Χ���𴥷�ʧ��
        Auto���Զ�����
            
    ���ý���ѡ�
        PMode(��ͼģʽ)��
            Vector��������ʸ����ʾ
            Dots  �������Ե�����ʾ
        LSB(����ϵ��)����ѹϵ����100����������10k��2k�ĵ�����з�ѹ����ѹϵ��Ϊ(10+2/2)=6��LSB����ȡֵΪ6x100=600������ʵ�ʵ��辫�Ƚ���΢��	
        BRT��OLED����

    �������ã������������˳����ý���ʱ�����ý��������������в��������浽EEPROM

    2020-04-30����
    1. ���ӵ��δ�������ͨ�������ܣ����Զ��崥����������׽���α仯
    2. ���չ����Ҫ��ADC�����˿�����Ϊ��������
    2020-5-3����
    1. ���Ӳ���Ƶ����ʾ
    2. ʹ�ñ�����ˮƽ/��ֱ��������
    3. ʹ�ñ�������ֱ���Ų���
    4. �û����趨������ƽ
*/

#include <reg51.h>
#include "global.h"
#include "delay.h"
#include "adc_stc8.h"
#include "config_stc.h"
#include "settings.h"
#include "chart.h"
#include "ssd1306.h"

// #include "uart.h"
// #include "stdio.h"

#define VBAT_UPDATE_FREQ 40 //��ص�ѹ��Ϣ�ĸ���Ƶ�� VBAT_UPDATE_FREQ*25ms
#define VBAT_LSB 600        //��ص�ѹ������ѹϵ��*100
#define INT_0 0             //�ⲿ�ж�0��ţ���������ת
#define INT_1 2             //�ⲿ�ж�1��ţ�����������
#define TIMER_0 1           //��ʱ��0�ж����

void init()
{
    InSettings = 0;         //��ʼ����������
    OptionInSettings = 0;   //��ʼ�����ý����ѡ����
    OptionInChart = 0;      //��ʼ���������ѡ����
    WaveScroll = 0;         //���㲨�ι�����־
    OptionChanged = 0;      //���������޸ı�־
    ADCRunning = 1;         //��λ������־
    ADCInterrupt = 0;       //����ADC�жϱ�־
    ADCComplete = 0;        //����ADC��ɱ�־
    WaveUpdate = 0;         //���㲨�θ��±�־
    ClearWave = 0;          //����������α�־
    ClearDisplay = 1;       //��λ�����Ļ��־
    EC11PressAndRotate = 0; //�����������ת��־
    UpdateVbat = 0;         //���������ص�ѹ��־
    ADCComplete = 0;        //����ADC��ɲ�����־
    WaveFreq = 0;           //���㲨��Ƶ��
    TriPos = 50;            //��ʼ��������λ��
    TriPosOffset = 0;       //��ʼ��������ƫ����
    TriFail = 0;            //���㴥��ʧ�ܱ�־
    VMax = 0;               //���㲨�ε�ѹ���ֵ
    VMin = 0;               //���㲨�ε�ѹ��Сֵ
    WaveLengthSumNum = 0;   //���㲨�γ�����ʹ���
    WaveLengthSum = 0;      //���㲨�γ������

    /* ���ι���ģʽ�����ڲ���������ⲿ�ж�0����������ת��
       Disable external interrupt 0(Encoder rotation) in waveform scroll mode when sampling*/
    if (ADCRunning && WaveScroll)
        EX0 = 0;

    /* ��ȡ�ڲ��ο���ѹֵ
       Get internal reference voltage */
    BGV = GetBGV();
}

void runWhenInSettrings()
{
    P_Ready = 0;
    ClearDisplay = 1;
    while (InSettings)
    {
        /* ���µ�ص�ѹ��Ϣ
           Update voltage infor of battery */
        if (UpdateVbat)
        {
            UpdateVbat = 0;
            VBat = GetVoltage(ADC_BAT, VBAT_LSB);
        }

        /* ������Ļ����
           Update OLED Brightness */
        if (OLED_BrightnessChanged)
        {
            OLED_BrightnessChanged = 0;
            OLED_Write_Command(0x81);
            OLED_Write_Command(OLED_Brightness * 10);
        }

        /* ���²���
           Update parameters */
        if (DisplayUpdate)
        {
            DisplayUpdate = 0;
            PlotSettings();
            OLED_Display();
        }
    }

    /* ��������
       Save Settings */
    EA = 0;
    if (OptionChanged)
    {
        OptionChanged = 0;
        ClearDisplay = 0;
        /* �������ò���ʾ����״̬
           Save settings and display saving status*/
        PlotSaveStatus(Save_Options());
        OLED_Display();
        Delay1000ms();
    }

    /* �˳�settings��ˢ����Ļ
       Redraw display after exit settings */
    ClearDisplay = 1;
    PlotChart();
    OLED_Display();
    IE0 = 0;
    IE1 = 0;
    EA = 1;
}

/*
    ADCRuning=1
    |	WaveUpdate=1
    |	|	ClearWave=1
    |	|	ClearWave=0
    |	WaveUpdate=0
    ADCRuning=0
        DisplayUpdate=1
            WaveUpdate=1
            |	ClearWave=1
            |	ClearWave=0
            WaveUpdate=0
*/
void runWhenADCInterrupt()
{
    ADCInterrupt = 0;
    P_Ready = 0;

    /* ADC��������
       ADC Sampling Running */
    if (ADCRunning)
    {
        EX0 = 0;

        if (WaveUpdate)
        {
            WaveUpdate = 0;
            ClearDisplay = 1;

            /* ��ղ��λ���
               Clear waveform in buffer*/
            if (ClearWave)
            {
                ClearWave = 0;
                memset(ADCbuf, 0x00, SAMPLE_NUM * 2);
                WaveFreq = 0;
                TriFail = 0;
                VMax = 0;
                VMin = 0;
                PlotChart();
            }
            /* ��ʾ�����еĲ���
               Display waveform in buffer*/
            else
            {
                AnalyseData();
                PlotChart();
                PlotWave();
            }
        }
        else
        {
            ClearDisplay = 0;
            PlotChart();
        }
        OLED_Display();

        /* ADCRuning��WaveScrollͬʱ��λʱ���������ⲿ�ж�0����������ת��
           Not to enable external interrupt 0(Encoder Rotation) when both of ADCRunning and WaveScroll set. */
        if (!WaveScroll)
        {
            IE0 = 0;
            EX0 = 1;
        }
    }

    /* ADC����ֹͣ
       ADC Sampling Stopped */
    else
    {
        while (!ADCRunning && !InSettings)
        {
            if (DisplayUpdate)
            {
                EX0 = 0;
                DisplayUpdate = 0;
                if (WaveUpdate)
                {
                    WaveUpdate = 0;
                    /* ������������ɲ����Ĳ�������
                       Analyse completed sampling data in buffer */
                    AnalyseData();
                    ClearDisplay = 1;

                    /* �����Ļ�����Ʋ���
                       Clear display and draw waveform */
                    if (ScaleH == ScaleH_tmp)
                    {
                        /* �����������ޣ���֧�ֺ������Ų��Σ�ֻ��ʱ����������ɲ�����ʱ��������ͬ�Ż��Ʋ���
                           Since the sampling points limitation, scaling waveform along horizontal is not support.
                           Show waveform only when time scale is same as that when sampling completed */
                        PlotChart();
                        PlotWave();
                    }

                    /* �����Ļ�������Ʋ���
                       Clear display and no waveform */
                    else
                    {
                        WaveFreq = 0; //����WaveFreq�����ƽ���ʱ��Ƶ��λ�û���ʾ****Hz
                        PlotChart();
                    }
                }
                /* ֻ������Ļ�ϵĲ��������β���
                   Update parameters on display only, keep waveform */
                else
                {
                    ClearDisplay = 0;
                    PlotChart();
                }

                OLED_Display();
                IE0 = 0;
                EX0 = 1;
            }
        }
    }
}

void runWhenADCComplete()
{
    /*  ADC������� - ���δ���
        ADC Sampling Complete - Single Trigger Mode */
    if (TriMode == 2)
    {
        EX0 = 0;
        ADCInterrupt = 1;
        DisplayUpdate = 0;
        WaveUpdate = 0;
        ADCRunning = 0; //����ADC���б�־��ֹͣ����
        AnalyseData();
        ClearDisplay = 1;
        PlotChart();
        PlotWave();
        OLED_Display();
        IE0 = 0;
        EX0 = 1;
    }

    /*  ADC������� - �Զ���������ͨ����
        ADC Sampling Complete - Auto or Normal Trigger Mode */
    else
    {
        //EX0 = 0;
        ClearDisplay = 1; //��λ�����Ļ��־
        AnalyseData();    //������������
        PlotChart();      //����������
        PlotWave();       //���Ʋ���
        OLED_Display();
        //IE0 = 0;
        //EX0 = 1;
    }
}

/* �������
   Program Entry */
void main()
{
    /* ��ADC�˿�P0.4��P0.6����Ϊ����
       Set ADC port P0.4, P0.6 as high-impedance */
    P0M1 |= 0x50;
    P0M0 &= ~0x50;

    /* ����ָʾ�ƶ˿�P1.1Ϊ�������
       Set indicator port P1.1 as push-pull output */
    P0M1 &= ~0x02;
    P0M0 |= 0x02;

    /* ���ñ������˿�P3.2��P3.3��P3.4Ϊ׼˫��
       Set Encoder port P3.2, P3.3, P3.4 as quasi bidirectional */
    P3M1 &= ~0x1C;
    P3M0 &= ~0x1C;

    /* ����OLED�˿�P2.3��P2.4��P2.5��P2.6��P2.7Ϊ׼˫��
       Set OLED port P2.3, P2.4, P2.5, P2.6 as quasi bidirectional */
    P2M1 &= ~0xF8;
    P2M0 &= ~0xF8;

    /* ��������ת�ⲿ�ж� 
       Interrupt for rotating of Encoder */
    IT0 = 0; //�ⲿ�ж�0������ʽ�������غ��½���
    PX0 = 1; //�ⲿ�ж�0�����ȼ����ɴ�ϰ����жϣ������жϰ���ͬʱ��ת
    EX0 = 1; //�����ⲿ�ж�0

    /* �����������ⲿ�ж� 
       Interrupt for clicking of Encoder */
    IT1 = 1; //�ⲿ�ж�1������ʽ���½���
    PX1 = 0; //�ⲿ�ж�1�����ȼ�
    EX1 = 1; //�����ⲿ�ж�1

    /* ��ʱ��0��Ϊ���µ�ص�ѹ��Ϣ��ʱ
       Timer 0, for updating voltage of battery */
    AUXR &= 0x7F; //��ʱ��ʱ��12Tģʽ
    TMOD &= 0xF0; //���ö�ʱ��ģʽ
    TL0 = 0x46;   //���ö�ʱ��ֵ //27MHz��25ms
    TH0 = 0x24;   //���ö�ʱ��ֵ
    TF0 = 0;      //���TF0��־
    ET0 = 1;      //����ʱ��0�ж�

    /* �����ж�
       Enable global interrupt */
    EA = 1;

    //UartInit();

    Read_Options();
    init();
    OLED_Init();
    OLED_SetFontWidth(6);
    PlotChart();
    OLED_Display();

    while (1)
    {
        P_Ready = 0;

        /* ��������
           Sampling*/
        GetWaveData();

        /* �������ý���
           Enter Settings Interface */
        if (InSettings)
        {
            runWhenInSettrings();
        }

        /* ADC�����ж�
           ADC Sampling Interrupt */
        else if (ADCInterrupt)
        {
            runWhenADCInterrupt();
        }

        /* ADC�������
           ADC Sampling Complete */
        else
        {
            runWhenADCComplete();
        }
    }
}

/* ������������ת
   Analyse Rotation of Encoder */
void Scan_EC11(void)
{
    /* ��ʱȥ����
       Delay to remove jitter */
    Delay500us();

    /* ��ת
       Clockwise */
    if (EC11_A != EC11_B)
    {
        Change_Val(1);
    }

    /* ��ת
       Anticlockwise */
    else if (EC11_A == EC11_B)
    {
        Change_Val(0);
    }
}

/* ��������ת�ж�
   Interrput for Encoder Rotated */
void INT0_interrupt(void) interrupt INT_0
{
    Delay500us();

    /* �������Ƿ񱻰���
       Whether the Encoder is pressed */
    if (!EC11_KEY)
        EC11PressAndRotate = 1;
    else
        EC11PressAndRotate = 0;

    Scan_EC11();
    ADCInterrupt = 1;
    DisplayUpdate = 1;
    IE1 = 0; //�����ⲿ�ж�1��־λ
    IE0 = 0; //�����ⲿ�ж�0��־λ
}

/* ����������ж�
   Interrput for Encoder Pressed */
void INT1_interrupt(void) interrupt INT_1
{
    Delay50ms();
    if (!EC11_KEY)
    {
        EC11PressAndRotate = 0;

        /*  �������������� - �л�����������ý���
            Long presse Encoder - Switch main interface and settings interface */
        if (Delay800ms_Long_Press())
        {
            InSettings = ~InSettings;

            /*  �������ý���
                Enter Settings  */
            if (InSettings)
            {
                DisplayUpdate = 1;
                UpdateVbat = 1;
                TF0 = 0; //���㶨ʱ��0�����־
                TR0 = 1; //��ʱ��0��ʼ��ʱ����ʼ��ص�ѹ��Ϣ���¼�ʱ
                IE0 = 0; //�����ⲿ�ж�0�жϱ�־
                EX0 = 1; //�����ⲿ�ж�0����������ת��
            }

            /*  �ص�������
                Retrurn to main interface   */
            else
            {
                TR0 = 0; //���㶨ʱ��0�����־
                TF0 = 0; //��ʱ��0ֹͣ��ʱ��ֹͣ��ص�ѹ��Ϣ���¼�ʱ
                WaveFreq = 0;
                TriFail = 0;
                VMax = 0;
                VMin = 0;
                DisplayUpdate = 1;
                WaveUpdate = 1;
                ClearWave = 0;
            }
            ADCInterrupt = 1;
        }

        /*  ��ס������ͬʱ��ת
            Rotate Encoder while pressing  */
        else if (EC11PressAndRotate)
        {
            /* �ɱ�������ת�ж�ִ�в���
               Operations Performed by Interrupt of Encoder Rotation */
        }

        /* ˫������������ - �������棬�������κ�ѡ��ģʽ֮���л�
           Double click Encoder - Switch between Waveform Scroll Mode and Parameter Mode in Main Interface */
        else if (Delay300ms_Double_Click())
        {
            /* ������
               Main Interface*/
            if (!InSettings)
            {
                WaveScroll = ~WaveScroll;
                OptionChanged = 1;
                ADCInterrupt = 1;
                DisplayUpdate = 1;
                ClearWave = 0;
            }
        }

        /*  �������������� - �������棬�л�Stop/Run״̬
            Single click Encoder - Switch Run/Stop in main interface    */
        else if (!InSettings)
        {
            EX0 = 0;
            ADCRunning = ~ADCRunning;
            if (ADCRunning)
            {
                WaveUpdate = 1;
                ClearWave = 1;
            }
            else
            {
                DisplayUpdate = 1;
                WaveUpdate = 1;
            }
            ADCInterrupt = 1;
            IE0 = 0;
            IE1 = 0;
        }
    }
    IE1 = 0;
}

/* Ϊ����Vbat��ʱ
   Timer for updating Vbat */
void TIMER0_interrupt(void) interrupt TIMER_0
{
    static uint8 n;

    if (++n >= VBAT_UPDATE_FREQ)
    {
        n = 0;
        UpdateVbat = 1;
        DisplayUpdate = 1;
    }
}