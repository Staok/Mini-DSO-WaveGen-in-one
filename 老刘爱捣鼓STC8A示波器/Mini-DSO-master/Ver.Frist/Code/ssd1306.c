/*
�汾��V0.1
���ߣ�����������
ʱ�䣺2020-04-24
���������ģ�ȫ��ͬ�����ڴ����Ĺ�ע��

��ע��ΪMini DSO�����Ŀ��ʱ��д��SSD1306 128x64�������в�����
��д�ַ����ַ��������֣�16x16�����ַ�����ˮƽ�ߣ���ֱ�ߣ����������߶Σ�����ͼƬ�ȹ���
��Ҫ�ο���Arduino��Adafruit SSD1306�Ŀ⺯��
����ȫ��buf��������ռ��128x8��uint8�ڴ�ռ�
ȫ������ٿ���Ļ���ݱȽϷ��㣬ˢ���ٶȿ죬���Ե�Ƭ�����ڴ��С��Ҫ��
F6x8���������о�԰���ӵ�DEMO
*/
#include "ssd1306.h"
#include "ssd1306font.h"
#include <string.h>
#include <stdlib.h>

//OLED���Դ�
//��Ÿ�ʽ����.
//[0]0 1 2 3 ... 127
//[1]0 1 2 3 ... 127
//[2]0 1 2 3 ... 127
//[3]0 1 2 3 ... 127
//[4]0 1 2 3 ... 127
//[5]0 1 2 3 ... 127
//[6]0 1 2 3 ... 127
//[7]0 1 2 3 ... 127

#ifndef _swap_char
#define _swap_char(a, b)     \
    {                        \
        uint8 t = a; \
        a = b;               \
        b = t;               \
    }
#endif

bit _oled_reverse = 0; 	//��ͼģʽ��1:�׵׺��֣�0:�ڵװ���
bit _oled_overlap = 1; 	//��ͼģʽ��1:���ӣ�0:���ǣ�������û�и���Ҫ���õ��ӣ�����ʱ����������У���Ḳ�ǵ��������ݣ�������Ľ�
uint8 buffer[1024]; 	//128x64ȫ������,����128�����أ�����64�����ط�Ϊ8ҳ��ÿҳ8��������Ϊһ���ֽڣ���128x8���ֽ�
static char _x, _y;
static uint8 _font_width = 6; //ASCII�ַ����

void delay_ms(unsigned int ms)
{
    unsigned int a;
    while (ms)
    {
        a = 1800;
        while (a--)
            ;
        ms--;
    }
    return;
}

//д����
void OLED_Write_Command(uint8 dat)
{
    uint8 i;
    OLED_DC_Clr();
    OLED_CS_Clr();
    for (i = 0; i < 8; i++)
    {
        OLED_SCLK_Clr();
        if (dat & 0x80) //�ж��������λ��1����0
        {
            OLED_SDIN_Set();
        }
        else
            OLED_SDIN_Clr();
        OLED_SCLK_Set();
        dat <<= 1;
    }
    OLED_CS_Set();
//    OLED_DC_Set();
}

//д����
void OLED_Write_Data(uint8 dat)
{
    uint8 i;
    OLED_DC_Set();
    OLED_CS_Clr();
    for (i = 0; i < 8; i++)
    {
        OLED_SCLK_Clr();
        if (dat & 0x80) //�ж��������λ��1����0
        {
            OLED_SDIN_Set();
        }
        else
            OLED_SDIN_Clr();
        OLED_SCLK_Set();
        dat <<= 1;
    }
    OLED_CS_Set();
//    OLED_DC_Set();
}

//1���׵׺��֣�0���ڵװ���
void OLED_Reverse(bit i)
{
	_oled_reverse=i;
}

//����ģʽ��1�����ӣ�0������
void OLED_Overlap(bit i)
{
    _oled_overlap = i;
}

//����ASCII�ַ����
void OLED_SetFontWidth(uint8 w)
{
    _font_width = w;
}


//�����ڴ�λ��x:0-127,y:0-63
void OLED_Set_Pos(uint8 x, uint8 y)
{
    _x = x;
    _y = y;
    OLED_Write_Command(0xb0 + y / 8);
    OLED_Write_Command(((x & 0xf0) >> 4) | 0x10);
    OLED_Write_Command((x & 0x0f) | 0x00);
}

//�����������
void OLED_Clear(void)
{
    memset(buffer, 0x00, WIDTH * ((HEIGHT + 7) / 8));
}


//�����ֽ�������
void OLED_Draw_Byte(uint8 *pBuf, uint8 mask)
{
	if (_oled_overlap)
	{
		if (_oled_reverse)
			*pBuf |= ~mask;
		else
			*pBuf |= mask;
	}
	else
	{
		if (_oled_reverse)
		{
			*pBuf &= ~mask;
			*pBuf |= ~mask;
		}
		else
		{
			*pBuf &= mask;
			*pBuf |= mask;
		}
	}
}
	
//�����ַ�������
void OLED_DrawChar(uint8 x, uint8 y, uint8 chr)
{
    uint8 c = 0, i = 0;
    uint8 mask;
	uint8 *pBuf;
    c = chr - ' '; //�õ�ƫ�ƺ��ֵ
    if (x > WIDTH - _font_width)
    {
        x = 0;
        y += 8;
    }
    pBuf = &buffer[(y / 8) * WIDTH + x];

    for (i = 0; i <_font_width; i++)
    {
        mask = F6x8[c][i] << (y & 7);
		OLED_Draw_Byte(pBuf++, mask);
    }
    if (y % 8 && y<HEIGHT-8)
    {
        pBuf = &buffer[(y / 8 + 1) * WIDTH + x];
        for (i = 0; i < _font_width; i++)
        {
            mask = F6x8[c][i] >> (8 - (y & 7));
            OLED_Draw_Byte(pBuf++, mask);
        }
    }
}

//�����ַ���������
void OLED_DrawString(uint8 *chr)
{
    while (*chr)
    {
        OLED_DrawChar(_x, _y, *chr++);
        _x += _font_width;

        if (_x > WIDTH - _font_width)
        {
            _x = 0;
            _y += 8;
        }
    }
}

//m^n����
uint32 oled_pow(uint8 m, uint8 n)
{
    uint32 result = 1;
    while (n--)
        result *= m;
    return result;
}

//��������������
//numlen :���ֵ�λ��
//num:��ֵ(0~4294967295);
void OLED_DrawNum(uint32 num, uint8 numlen)
{
    uint8 t, temp;
    uint8 enshow = 0;
    for (t = 0; t < numlen; t++)
    {
        temp = (num / oled_pow(10, numlen - t - 1)) % 10;
        if (enshow == 0 && t < (numlen - 1))
        {
            if (temp == 0)
            {
                OLED_DrawChar(_x + (_font_width)*t, _y, ' ');
                continue;
            }
            else
                enshow = 1;
        }
        OLED_DrawChar(_x + (_font_width)*t, _y, temp + '0');
    }
}

//����ͼƬ������
void OLED_DrawBMP(uint8 x0, uint8 y0, uint8 x1, uint8 y1, uint8 *BMP, uint16 len)
{
    uint16 j = 0;
    uint8 x, y;
    uint8 mask;
	uint8 *pBuf;
    if (x0 > x1)
    {
        _swap_char(x0, x1);
    }
    if (y0 > y1)
    {
        _swap_char(y0, y1);
    }

    if (x1 > 127)
        x1 = 127;
    if (y1 > 63)
        y1 = 63;

    for (y = y0; y <= y1; y += 8)
    {
        for (x = x0; x <= x1; x++)
        {
            if (j > len - 1)
                break;
            pBuf = &buffer[(y / 8) * WIDTH + x];
            mask = *(BMP + j++) << (y & 7);
            OLED_Draw_Byte(pBuf++, mask);

            if (y % 8 && y < HEIGHT - 8)
            {
                j--;
                pBuf = &buffer[(y / 8 + 1) * WIDTH + x];
                mask = *(BMP + j++) >> (8 - (y & 7));
                OLED_Draw_Byte(pBuf++, mask);
            }
        }
    }
}

//���ƺ���������
void OLED_DrwCHS_16x16(uint8 chs_no)
{
    if (_x > WIDTH - 16)
    {
        _x = 0;
        _y += 16;
    }
    OLED_DrawBMP(_x, _y, _x + 15, _y + 15, CHS_16x16[chs_no], sizeof(CHS_16x16[chs_no]) / sizeof(CHS_16x16[chs_no][0]));
    _x += 16;
}

//����һ������������
void OLED_DrawPixel(uint8 x, uint8 y)
{
    uint8 mask;
	uint8 *pBuf;
    pBuf = &buffer[(y / 8) * WIDTH + x];
    mask = 1 << (y & 7);
    *pBuf++ |= mask;
}

//���������߶�������
void OLED_DrawLine(uint8 x0, uint8 y0, uint8 x1, uint8 y1)
{
    char dx, dy, ystep;
    int err;
    bit swapxy = 0;

    if (x0 > 127)
        x0 = 127;
    if (y0 > 63)
        y0 = 63;
    if (x1 > 127)
        x1 = 127;
    if (y1 > 63)
        y1 = 63;

    dx = abs(x1 - x0);
    dy = abs(y1 - y0);

    if (dy > dx)
    {
        swapxy = 1;
        _swap_char(dx, dy);
        _swap_char(x0, y0);
        _swap_char(x1, y1);
    }

    if (x0 > x1)
    {
        _swap_char(x0, x1);
        _swap_char(y0, y1);
    }
    err = dx >> 1;

    if (y0 < y1)
    {
        ystep = 1;
    }
    else
    {
        ystep = -1;
    }

    for (; x0 <= x1; x0++)
    {
        if (swapxy == 0)
            OLED_DrawPixel(x0, y0);
        else
            OLED_DrawPixel(y0, x0);
        err -= dy;
        if (err < 0)
        {
            y0 += ystep;
            err += dx;
        }
    }
}

//���ƴ�ֱ��������
void OLED_DrawVLine(uint8 x, uint8 y, uint8 w)
{
    uint8 mask;
	uint8 *pBuf;
    while (w--)
    {
        pBuf = &buffer[(y / 8) * WIDTH + x];
        mask = 1 << (y & 7);
        *pBuf++ |= mask;
        y++;
    }
}

//����ˮƽ��������
void OLED_DrawHLine(uint8 x, uint8 y, uint8 w)
{
	uint8 *pBuf;
    uint8 mask;
    pBuf = &buffer[(y / 8) * WIDTH + x];
    mask = 1 << (y & 7);
    while (w--)
    {
        *pBuf++ |= mask;
    }
}

//������������ʾ����Ļ��
void OLED_Display(void)
{
    uint8 i, j;
	uint8 *pBuf;
    OLED_Write_Command(0xB0); //����ҳ��ַ��0~7��
    OLED_Write_Command(0x00); //������ʾλ�á��е͵�ַ
    OLED_Write_Command(0x10); //������ʾλ�á��иߵ�ַ
    pBuf = buffer;
    for (j = 0; j < HEIGHT; j += 8)
    {
        OLED_Set_Pos(0, j);
        for (i = 0; i < WIDTH; i++)
        {
            OLED_Write_Data(*pBuf++);
        }
    }
}

//��ʼ��SSD1306
void OLED_Init(void)
{
    OLED_RST_Set();
    delay_ms(100);
    OLED_RST_Clr();
    delay_ms(100);
    OLED_RST_Set();

    OLED_Write_Command(0xAE); //--turn off oled panel
    OLED_Write_Command(0x00); //---set low column address
    OLED_Write_Command(0x10); //---set high column address
    OLED_Write_Command(0x40); //--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
    OLED_Write_Command(0xB0); //
    OLED_Write_Command(0x81); //--set contrast control register
    OLED_Write_Command(0xFE); // Set SEG Output Current Brightness0x66
    OLED_Write_Command(0xA1); //--Set SEG/Column Mapping     0xa0���ҷ��� 0xa1����
    OLED_Write_Command(0xA6); // Disable Inverse Display On (0xa6/a7)
    OLED_Write_Command(0xC8); //Set COM/Row Scan Direction   0xc0���·��� 0xc8����
    OLED_Write_Command(0xA6); //--set normal display
    OLED_Write_Command(0xA8); //--set multiplex ratio(1 to 64)
    OLED_Write_Command(0x3f); //--1/64 duty
    OLED_Write_Command(0xD3); //-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
    OLED_Write_Command(0x00); //-not offset
    OLED_Write_Command(0xd5); //--set display clock divide ratio/oscillator frequency
    OLED_Write_Command(0x80); //--set divide ratio, Set Clock as 100 Frames/Sec
    OLED_Write_Command(0xD9); //--set pre-charge period
    OLED_Write_Command(0xF1); //Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
    OLED_Write_Command(0xDA); //--set com pins hardware configuration
    OLED_Write_Command(0x12);
    OLED_Write_Command(0xDB); //--set vcomh
    OLED_Write_Command(0x30); //Set VCOM Deselect Level
    OLED_Write_Command(0x20); //-Set Page Addressing Mode (0x00/0x01/0x02)
    OLED_Write_Command(0x00); //
    OLED_Write_Command(0x8D); //--set Charge Pump enable/disable
    OLED_Write_Command(0x14); //--set(0x10) disable
    OLED_Write_Command(0xA4); // Disable Entire Display On (0xa4/0xa5)
    OLED_Write_Command(0xAF); //--turn on oled panel
}
