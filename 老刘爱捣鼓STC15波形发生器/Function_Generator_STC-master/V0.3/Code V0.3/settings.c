/*
	settings.c
	
    Options and Interface

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

#include "settings.h"
//#include "uart.h"
//#include "stdio.h"

bit Options = 1;        //Ƶ�ʺ�ռ�ձ�����ѡ�� 1:HZ 0:Duty
bit Clear_LCD_Flag = 1; //����LCD��־λ
uint8 PWM_Max_Duty;     //PWM���ռ�ձȣ���Ƶ�ʱ仯
uint8 PWM_Min_Duty;     //PWM���ռ�ձȣ���Ƶ�ʱ仯

void show_Options()
{
    Lcd_Write_Command(LCD_HOME1 + 0x01);
    Lcd_Write_Str("F:");
    Lcd_Write_Command(LCD_HOME1 + 0x03);
    switch (Wave_Shape)
    {
    /* ����
        Square Waveform */
    case 1:                   
        Lcd_Write_Int(PWM_Hz);   //PWMƵ��
        Lcd_Write_Str("Hz  ");
        Lcd_Write_Command(LCD_HOME1 + 0x0A);
        Lcd_Write_Str("D:");
        Lcd_Write_Int(PWM_Duty); //PWMռ�ձ�
        Lcd_Write_Str("% ");
        Lcd_Write_Command(LCD_HOME2);
        Lcd_Write_Data(0x00);   //����ͼ��
        Lcd_Write_Data(0x00);
        break;
    /* ���Ҳ�
        Sine Waveform */
    case 2:                   
        Lcd_Write_Int(SIN_Hz);  //SINƵ��
        Lcd_Write_Str("Hz  ");
        Lcd_Write_Command(LCD_HOME2);
        Lcd_Write_Data(0x02);  //���Ҳ�ͼ��
        Lcd_Write_Data(0x03);
        break;
    }
}

void show_Info()
{
    Lcd_Write_Command(LCD_HOME2 + 0x0C);
    Lcd_Write_Str("CD");
    if (PWM_Hz < 50)
    {
        Lcd_Write_Int(CKS_50HZ);      //��ʱ��ʱ�ӷ�Ƶϵ��
    }
    else
    {
        Lcd_Write_Int(PWMCKS_PS + 1); //��ǿ��PWMʱ�ӷ�Ƶϵ��
    }
    Lcd_Write_Str(" ");
    if (Wave_Shape == 2)
    {
        Lcd_Write_Command(LCD_HOME1 + 0x0A);
        Lcd_Write_Str("P");
        Lcd_Write_Int(PWM_Hz);                          //PWMƵ��
        Lcd_Write_Str("  ");
        Lcd_Write_Command(LCD_HOME2 + 0x06);
        Lcd_Write_Str("Pt");
        Lcd_Write_Int(SIN_POINTS / Sin_Table_Times);    //ÿ�����Ҳ��ĵ���
        Lcd_Write_Str(" ");
    }
}

/* ���״̬
   Output status */
void show_ON_OFF()
{
    Lcd_Write_Command(LCD_HOME2 + 0x02);
    if (WAVE_ON)
        Lcd_Write_Str("ON  ");
    else
        Lcd_Write_Str("OFF ");
}


void show_Options_Flag()
{
    if (Options)
    {
        Lcd_Write_Command(LCD_HOME1);
        Lcd_Write_Data(0x7E);
        Lcd_Write_Command(LCD_HOME1 + 0x09);
        Lcd_Write_Data(' ');
    }
    else
    {
        Lcd_Write_Command(LCD_HOME1);
        Lcd_Write_Data(' ');
        Lcd_Write_Command(LCD_HOME1 + 0x09);
        Lcd_Write_Data(0x7E);
    }
}

void show_VCC()
{
    uint16 vol;
    vol = Get_VCC_Voltage();
    //vol = (vol + 5) / 10;
    Lcd_Write_Command(LCD_HOME1);
    Lcd_Write_Str("VDD=");
    Lcd_Write_Data(vol / 1000 + '0');
    Lcd_Write_Data('.');
    Lcd_Write_Data(vol / 100 % 10 + '0');
    Lcd_Write_Data(vol / 10 % 10 + '0');
    Lcd_Write_Data(vol % 10 + '0');
    Lcd_Write_Data('V');
}

void show_CopyRight()
{
    Lcd_Write_Command(LCD_HOME2);
    Lcd_Write_Str("By Creative Lau");
}

void Update_LCD()
{
    if (Clear_LCD_Flag)
    {
        Clear_LCD_Flag = 0;
        Lcd_Write_Command(LCD_CLEAR);
    }
    if (Wave_Shape == 0)
    {
        show_CopyRight();
        show_VCC();
    }
    else
    {
        show_Options();
        show_Info();
        show_Options_Flag();
        show_ON_OFF();
    }
}

void get_PWM_Duty_Limit()
{
    /* ����PWM_Hz�趨zռ�ձȵ�������
       Set min and max duty accordding to PWM_Hz*/
    PWM_Min_Duty = PWM_Hz * PWM_MIN_WIDTH / 10000000.0 + 0.5;
    PWM_Min_Duty < PWM_MIN_DUTY ? PWM_Min_Duty = PWM_MIN_DUTY : PWM_Min_Duty;
    PWM_Max_Duty = 100 - PWM_Min_Duty;
}

void change_PWM_Hz(bit i)
{
    if (i)
    {
        if (PWM_Hz >= 1000000)
        {
            PWM_Hz += 100000;
        }
        else if (PWM_Hz >= 100000)
        {
            PWM_Hz += 50000;
        }
        else if (PWM_Hz >= 10000)
        {
            PWM_Hz += 5000;
        }
        else if (PWM_Hz >= 1000)
        {
            PWM_Hz += 1000;
        }
        else if (PWM_Hz >= 100)
        {
            PWM_Hz += 50;
        }
        else if (PWM_Hz >= 10)
        {
            PWM_Hz += 2;
        }
        else if (PWM_Hz >= 0)
        {
            PWM_Hz += 1;
        }
        if (PWM_Hz > PWM_MAX_HZ)
            PWM_Hz = PWM_MAX_HZ;
    }
    else
    {
        if (PWM_Hz <= 10)
        {
            PWM_Hz -= 1;
        }
        else if (PWM_Hz <= 100)
        {
            PWM_Hz -= 2;
        }
        else if (PWM_Hz <= 1000)
        {
            PWM_Hz -= 50;
        }
        else if (PWM_Hz <= 10000)
        {
            PWM_Hz -= 1000;
        }
        else if (PWM_Hz <= 100000)
        {
            PWM_Hz -= 5000;
        }
        else if (PWM_Hz <= 1000000)
        {
            PWM_Hz -= 50000;
        }
        else if (PWM_Hz <= 10000000)
        {
            PWM_Hz -= 100000;
        }
        if (PWM_Hz < PWM_MIN_HZ)
            PWM_Hz = PWM_MIN_HZ;
    }
    get_PWM_Duty_Limit();
    if (PWM_Duty > PWM_Max_Duty)
        PWM_Duty = PWM_Max_Duty;
    else if (PWM_Duty < PWM_Min_Duty)
        PWM_Duty = PWM_Min_Duty;
}

void change_SIN_Hz(bit i)
{
    if (i)
    {
        if (SIN_Hz >= 2000)
        {
            SIN_Hz += 500;
        }
        else if (SIN_Hz >= 1000)
        {
            SIN_Hz += 100;
        }
        else if (SIN_Hz >= 200)
        {
            SIN_Hz += 50;
        }
        else if (SIN_Hz >= 100)
        {
            SIN_Hz += 10;
        }
        else if (SIN_Hz >= 20)
        {
            SIN_Hz += 5;
        }
        else if (SIN_Hz >= 0)
        {
            SIN_Hz += 1;
        }
        if (SIN_Hz > SIN_MAX_HZ)
            SIN_Hz = SIN_MAX_HZ;
    }
    else
    {
        if (SIN_Hz <= 20)
        {
            SIN_Hz -= 1;
        }
        else if (SIN_Hz <= 100)
        {
            SIN_Hz -= 5;
        }
        else if (SIN_Hz <= 200)
        {
            SIN_Hz -= 10;
        }
        else if (SIN_Hz <= 1000)
        {
            SIN_Hz -= 50;
        }
        else if (SIN_Hz <= 2000)
        {
            SIN_Hz -= 100;
        }
        else if (SIN_Hz <= 10000)
        {
            SIN_Hz -= 500;
        }
        if (SIN_Hz < SIN_MIN_HZ)
            SIN_Hz = SIN_MIN_HZ;
    }
}

void change_Duty(bit i)
{
    if (i)
    {
        PWM_Duty++;
        if (PWM_Duty > PWM_Max_Duty)
            PWM_Duty = PWM_Max_Duty;
    }
    else
    {
        PWM_Duty--;
        if (PWM_Duty < PWM_Min_Duty)
            PWM_Duty = PWM_Min_Duty;
    }
}

void Change_Val(bit i)
{
    switch (Wave_Shape)
    {
    case 1:
        if (Options)
        {
            change_PWM_Hz(i);
        }
        else
        {
            change_Duty(i);
        }
        break;
    case 2:
        change_SIN_Hz(i);
        break;
    }
}
