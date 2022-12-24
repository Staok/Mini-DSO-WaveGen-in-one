#include "settings.h"

bit In_Settings = 0;
uint16 Lsb = 605;
char Scale_H = 2;
char Scale_V = 10;  
bit Draw_Mode = 0; 				//��ͼģʽ 0:Vect 1:Dots
char Option_In_Settings = 0;   	//���ý����ѡ�����, 0:LSB, 1:DrawMode
char Option_In_Chart = 1;   	//ͼ������ѡ�����, 0:Scale_V, 1:Scale_H

uint8 code *DrawModeTxt[] = {"Vect", "Dots"}; //ͼ�����ʾ��ʽ
//uint8 code *ScaleVTxt[] = {"Auto", "200mV", "500mV", "1V", "2V", "5V", "10V", "15V", "20V", "25V", "30V"}; //ͼ��ֱ�����Ϣ
uint8 code *ScaleHTxt[] = {"500ms", "200ms", "100ms", "50ms", "20ms", "10ms", "5ms", "2ms", "1ms", "500us", "200us", "100us"}; //ͼ��ˮƽ�����Ϣ

void change_Scale_H(bit i)
{
    if (i)
    {
        Scale_H++;
        if (Scale_H > SCALE_H_MAX)
            Scale_H = SCALE_H_MAX;
    }
    else
    {
        Scale_H--;
        if (Scale_H < 0)
            Scale_H = 0;
    }
}

void change_Scale_V(bit i)
{
    if (i)
    {
        Scale_V++;
        if (Scale_V > SCALE_V_MAX)
            Scale_V = SCALE_V_MAX;
    }
    else
    {
        Scale_V--;
        if (Scale_V < 0)
            Scale_V = 0;
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

void change_Draw_Mode()
{
    Draw_Mode = ~Draw_Mode;
}

void Change_Val(bit i)
{
    if (In_Settings)
    {
        if (Option_In_Settings == 0)
            change_LSB(i);
        else if (Option_In_Settings == 1)
            change_Draw_Mode();
    }
	else if(HoldDisplay)
	{
		Option_In_Chart++;
		if(Option_In_Chart>1)
			Option_In_Chart=0;
	}
    else 
    {
		if(Option_In_Chart==1)
			change_Scale_H(i);
		else if (Option_In_Chart == 0)
			change_Scale_V(i);
    }
}

void check_Options()
{
    if (Lsb > LSB_MAX || Lsb < LSB_MIN)
        Lsb = 600;
    if (Scale_H > SCALE_H_MAX || Scale_H < SCALE_H_MIN)
        Scale_H = 0;
    if (Scale_V > SCALE_V_MAX || Scale_V < SCALE_V_MIN)
        Scale_V = 0;
}

bit Save_Options()
{
    uint8 ops[5]; //��LSB��λ�����ֳ������ֽ�
    uint8 *p;
    p = ops;
    *p++ = Lsb >> 8;  //��ȡLsb��8λ
    *p++ = Lsb;       //��ȡLsb��8λ
    *p++ = Draw_Mode; //��ȡDraw_Mode
    *p++ = Scale_H;   //��ȡDraw_Mode
    *p = Scale_V;     //��ȡDraw_Mode
    return EEPROM_Save(ops, sizeof(ops) / sizeof(ops[0]));
}

void Read_Options()
{
    uint8 ops[5];
    uint8 *p;
    p = ops;
    EEPROM_Read(ops, sizeof(ops) / sizeof(ops[0]));
    Lsb = *p++;
    Lsb <<= 8;        //��ֵLsb��8λ
    Lsb |= *p++;      //��ֵLsb��8λ
    Draw_Mode = *p++; //��ֵDraw_Mode
    Scale_H = *p++;   //��ֵScale_H
    Scale_V = *p;     //��ֵScale_V

	//��EPPROM�е�������Ч��������Ĭ��ֵ
	check_Options();
}

