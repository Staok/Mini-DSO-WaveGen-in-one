/*
    settings.c

    Settings Control and Parameter Adjusting

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

*/

#include "settings.h"

    //��Ƭ���ٶ����ƣ����κ���ͨ�������м������ɵ�Ƭ���޷����100us�������
    //MCU speed limitation result in the Single Sweep and Normal Sweep calculations could not complete in 100us time interval.
    void
    Check_MinTimeInterval()
{
    if (TriMode)
    {
        if (ScaleH > SCALE_H_MAX - 1)
            ScaleH = SCALE_H_MAX - 1;
    }
    else
    {
        if (ScaleH > SCALE_H_MAX)
            ScaleH = SCALE_H_MAX;
    }
}

void change_ScaleH(bit i)
{
    if (i)
    {
        ScaleH++;
        Check_MinTimeInterval();
    }
    else
    {
        ScaleH--;

        if (ScaleH < SCALE_H_MIN)
            ScaleH = SCALE_H_MIN;
    }
}

void change_TriggerValue(bit i)
{
    if (i)
    {
        if (TriLevel >= 5000)
            TriLevel += 500;
        else
            TriLevel += 100;

        if (TriLevel > MAX_V)
            TriLevel = MAX_V;
    }
    else
    {
        if (TriLevel <= 5000)
            TriLevel -= 100;
        else
            TriLevel -= 500;

        if (TriLevel < MIN_V)
            TriLevel = MIN_V;
    }
}

void change_LSB(bit i)
{
    if (i)
    {
        Lsb++;

        if (Lsb > LSB_MAX)
            Lsb = LSB_MAX;
    }
    else
    {
        Lsb--;

        if (Lsb < LSB_MIN)
            Lsb = LSB_MIN;
    }
}

void change_PlotMode()
{
    PlotMode = ~PlotMode;
}

void change_TriMode(bit i)
{
    if (i)
    {
        TriMode++;

        if (TriMode > 2)
            TriMode = 0;
    }
    else
    {
        TriMode--;

        if (TriMode < 0)
            TriMode = 2;
    }
}

void change_TriPosOffset(bit i)
{
    if (i)
    {
        TriPosOffset--;
        if (TriPosOffset + TriPos < ((CHART_H_MAX - CHART_H_MIN) >> 1))
            TriPosOffset = ((CHART_H_MAX - CHART_H_MIN) >> 1) - TriPos;
    }
    else
    {
        TriPosOffset++;
        if (TriPosOffset + TriPos > SAMPLE_NUM - ((CHART_H_MAX - CHART_H_MIN) >> 1) - 1)
            TriPosOffset = SAMPLE_NUM - ((CHART_H_MAX - CHART_H_MIN) >> 1) - 1 - TriPos;
    }
}

void change_OptionInChart(bit i)
{
    if (i)
    {
        OptionInChart++;

        if (OptionInChart > 4)
            OptionInChart = 0;
    }
    else
    {
        OptionInChart--;

        if (OptionInChart < 0)
            OptionInChart = 4;
    }
}

void change_OptionInSettings(bit i)
{
    if (i)
    {
        OptionInSettings++;
        if (OptionInSettings > 2)
            OptionInSettings = 0;
    }
    else
    {
        OptionInSettings--;
        if (OptionInSettings < 0)
            OptionInSettings = 2;
    }
}

void change_RulerVMax(bit i)
{
    if (i)
    {
        if (RulerVMax <= 1000)
        {
            RulerVMax -= 100;
            //RulerVMin += 100;
        }
        else
        {
            RulerVMax -= 500;
            //RulerVMin += 500;
        }

        if (RulerVMax <= RulerVMin)
            ScaleV_Auto = 1;
    }
    else
    {
        ScaleV_Auto = 0;
        if (RulerVMax >= 1000)
        {
            RulerVMax += 500;
            //RulerVMin -= 500;
        }
        else
        {
            RulerVMax += 100;
            //RulerVMin -= 100;
        }

        if (RulerVMax > MAX_V)
            RulerVMax = MAX_V;

        // if (RulerVMin < MIN_V)
        //     RulerVMin = MIN_V;
    }
}

void change_RulerV(bit i)
{
    ScaleV_Auto = 0;
    if (i)
    {
        RulerVMax -= 100;
        RulerVMin -= 100;
        if (RulerVMin < MIN_V + 100)
        {
            RulerVMax += 100;
            RulerVMin = MIN_V;
        }
    }
    else
    {
        RulerVMax += 100;
        RulerVMin += 100;
        if (RulerVMax > MAX_V)
        {
            RulerVMax = MAX_V;
            RulerVMin -= 100;
        }
    }
}

void change_OLED_Brightness(bit i)
{
    if (i)
    {
        OLED_Brightness++;
        if (OLED_Brightness > BRIGHTNESS_MAX)
            OLED_Brightness = BRIGHTNESS_MAX;
    }
    else
    {
        OLED_Brightness--;
        if (OLED_Brightness < BRIGHTNESS_MIN)
            OLED_Brightness = BRIGHTNESS_MIN;
    }
    OLED_BrightnessChanged = 1;
}

void Change_Val(bit i)
{
    /* ����ͬʱ��ת������
       Rotating Encoder while pressing */
    if (EC11PressAndRotate)
    {
        //���ý���
        //In settings
        if (InSettings)
        {
            change_OptionInSettings(i);
        }

        //���ι���ģʽ
        //In waveform scroll mode
        else if (WaveScroll)
        {
            change_RulerV(i);
            WaveUpdate = 1; //��λ���θ��±�־
        }

        //�ǲ��ι���ģʽ
        //Not in waveform scroll mode
        else
        {
            change_OptionInChart(i);
            //�л�ѡ��ʱ������ղ���
            //Not to clear waveform when switch options
            ClearWave = 0;
        }
    }

    /* �����ý�����ת������
       Rotating Encoder in settings */
    else if (InSettings)
    {
        /* ���ڻ�ͼģʽ
           Ajust Plot Mode */
        if (OptionInSettings == 0)
            change_PlotMode();

        /* ����LSB
           Adjust LSB */
        else if (OptionInSettings == 1)
            change_LSB(i);

        /* ����OLED_Brightness
           Adjust OLED_Brightness */
        else if (OptionInSettings == 2)
            change_OLED_Brightness(i);

        /* ��λ���ñ����־
           Options need to be saved */
        OptionChanged = 1;
    }

    /* ��������ģʽ����ת������
       Rotate Encoder in waveform horizontal scroll mode */
    else if (WaveScroll)
    {
        change_TriPosOffset(i);
        WaveUpdate = 1; 
    }

    /* ����������ת������
       Rotate Encoder in Main interface */
    else
    {
        /* ����ʱ������
           Adjust time scale */
        if (OptionInChart == 0)
        {
            change_ScaleH(i);
            WaveUpdate = 1;
            ClearWave = 1;
            WaveLengthSumNum = 0; 
            WaveLengthSum = 0;   
        }

        /* ��������
           Adjust measuring range */
        else if (OptionInChart == 1)
        {
            change_RulerVMax(i);
            WaveUpdate = 1;
            ClearWave = 0;
        }

        /* ���ڴ���ֵ
           Adjust Trigger level */
        else if (OptionInChart == 2)
        {
            change_TriggerValue(i);
            WaveUpdate = 0;
            ClearWave = 0;
        }

        /* ���ڴ�������
           Adjust Trigger Slope */
        else if (OptionInChart == 3)
        {
            TriSlope = ~TriSlope;
            WaveUpdate = 0;
            ClearWave = 0;
        }

        /* ���Ĵ�����ʽ
           Switch Trigger Mode */
        if (OptionInChart == 4)
        {
            change_TriMode(i);
            Check_MinTimeInterval(); //���ʱ������ĺϷ���
            WaveUpdate = 1;
            ClearWave = 1;
            WaveLengthSumNum = 0; 
            WaveLengthSum = 0;   
        }

        /* ��λ���ñ����־
           Options need to be saved */
        OptionChanged = 1;
    }
}

void check_Options()
{
    if (Lsb > LSB_MAX || Lsb < LSB_MIN)
        Lsb = 600;

    if (ScaleH > SCALE_H_MAX || ScaleH < SCALE_H_MIN)
        ScaleH = 0;

    if (RulerVMax > MAX_V || RulerVMax < MIN_V)
        RulerVMax = 0;

    if (RulerVMin > MAX_V || RulerVMin < MIN_V)
        RulerVMin = 0;

    if (RulerVMax <= RulerVMin)
    {
        RulerVMax = RulerVMin;
        ScaleV_Auto = 1;
    }

    if (TriLevel > MAX_V || TriLevel < MIN_V)
        TriLevel = 2000;

    if (TriMode > 2 || TriMode < 0)
        TriMode = 0;

    if (OLED_Brightness > BRIGHTNESS_MAX || OLED_Brightness < BRIGHTNESS_MIN)
        OLED_Brightness = 10;

    Check_MinTimeInterval();
}

bit Save_Options()
{
    uint8 ops[15];
    uint8 *p;
    check_Options();
    p = ops;
    *p++ = Lsb >> 8;       //д��Lsb��8λ uint16
    *p++ = Lsb;            //д��Lsb��8λ
    *p++ = PlotMode;       //д���ͼģʽ bit
    *p++ = ScaleH;         //д��ʱ������ char
    *p++ = ScaleV_Auto;    //��ȡ�Զ����̱�־ bit
    *p++ = RulerVMax >> 8; //д�������ѹ��8λ int16
    *p++ = RulerVMax;      //д�������ѹ��8λ
    *p++ = RulerVMin >> 8; //д�������ѹ��8λ int16
    *p++ = RulerVMin;      //д�������ѹ��8λ
    *p++ = TriLevel >> 8;  //д�봥��ֵ��8λ int16
    *p++ = TriLevel;       //д�봥��ֵ��8λ
    *p++ = TriMode;        //д�봥����ʽ int8
    *p++ = TriSlope;       //д�봥������ bit
    *p++ = WaveScroll;     //д�벨�ι�����־ bit
    *p = OLED_Brightness;  //д��OLED���� uint8

    //	printf("Lsb=%hu\r\n",Lsb);
    //	printf("DrawMode=%X\r\n",PlotMode);
    //	printf("ScaleH=%bd\r\n",ScaleH);
    //	printf("ScaleV_Auto=%X\r\n",ScaleV_Auto);
    //	printf("RulerVMax=%hd\r\n",RulerVMax);
    //	printf("RulerVMin=%hd\r\n",RulerVMin);
    //	printf("TriLevel=%hd\r\n",TriLevel);
    //	printf("TriMode=%bd\r\n",TriMode);
    //	printf("TriSlope=%X\r\n",TriSlope);
    //	printf("WaveScroll=%X\r\n",WaveScroll);
    //	printf("OLED_Brightness=%bu\r\n",OLED_Brightness);
    //	printf("\r\n");
    return EEPROM_Save(ops, sizeof(ops) / sizeof(ops[0]));
}

void Read_Options()
{
    uint8 ops[15];
    uint8 *p;
    p = ops;
    EEPROM_Read(ops, sizeof(ops) / sizeof(ops[0]));
    Lsb = *p++;           //��ȡLsb��8λ uint16
    Lsb <<= 8;            //����8λ�Ƶ��߰�λ
    Lsb |= *p++;          //��ȡLsb��8λ
    PlotMode = *p++;      //��ȡ��ͼģʽ bit
    ScaleH = *p++;        //��ȡʱ������ char
    ScaleV_Auto = *p++;   //��ȡ�Զ����̱�־ bit
    RulerVMax = *p++;     //��ȡ�����ѹ���ֵ��8λ int16
    RulerVMax <<= 8;      //����8λ�Ƶ��߰�λ
    RulerVMax |= *p++;    //��ȡ�����ѹ���ֵ��8λ
    RulerVMin = *p++;     //��ȡ�����ѹ��С��8λ int16
    RulerVMin <<= 8;      //����8λ�Ƶ��߰�λ
    RulerVMin |= *p++;    //��ȡ�����ѹ��С��8λ
    TriLevel = *p++;      //��ȡ����ֵ��8λ int16
    TriLevel <<= 8;       //����8λ�Ƶ��߰�λ
    TriLevel |= *p++;     //��ȡ����ֵ��8λ
    TriMode = *p++;       //��ȡ������ʽ int8
    TriSlope = *p++;      //��ȡ�������� bit
    WaveScroll = *p++;    //��ȡ���ι�����־ bit
    OLED_Brightness = *p; //��ȡOLED���� uint8

    check_Options(); //���ѡ��Ϸ���
    //	printf("Lsb=%hu\r\n",Lsb);
    //	printf("DrawMode=%X\r\n",PlotMode);
    //	printf("ScaleH=%bd\r\n",ScaleH);
    //	printf("ScaleV_Auto=%X\r\n",ScaleV_Auto);
    //	printf("RulerVMax=%hd\r\n",RulerVMax);
    //	printf("RulerVMin=%hd\r\n",RulerVMin);
    //	printf("TriLevel=%hd\r\n",TriLevel);
    //	printf("TriMode=%bd\r\n",TriMode);
    //	printf("TriSlope=%X\r\n",TriSlope);
    //	printf("WaveScroll=%X\r\n",WaveScroll);
    //	printf("OLED_Brightness=%bu\r\n",OLED_Brightness);
    //	printf("\r\n");
}
