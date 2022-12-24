

/*************	����˵��	**************

480x320 3.2��TFT LCD �Ļ����������򣬿�������ILI9481BDS��

TFT480x320-V2.c  �Ľ����Ż�����.

******************************************/

#include	"TFT480x320.h"
#include	"ASCII5x7.h"
#include	"HZK12.h"
#include	"ASCII_8x16_H.h"
#include	"HZK16.h"

u16	foreground,background;


/****** ����LCD�ӿ� *********/
sbit LCD_RS  = P4^5;
sbit LCD_WR  = P4^2;
sbit LCD_CS  = P4^3;
sbit LCD_RST = P4^1;
sfr	 LCD_BUS_H = 0xE8;	//P0--0x80,P1=0x90,P2=0xA0,P3=0x0B0, P6= 0xE8
sfr	 LCD_BUS_L = 0xA0;	//P0--0x80,P1=0x90,P2=0xA0,P3=0x0B0, P6= 0xE8



/**** LCD���������궨�� ***********/

#define LCD_CS_SET()		LCD_CS = 1
#define LCD_CS_CLR()		LCD_CS = 0

#define LCD_RST_SET()		LCD_RST = 1
#define LCD_RST_CLR()		LCD_RST = 0

#define LCD_RS_SET()		LCD_RS = 1
#define LCD_RS_CLR()		LCD_RS = 0

#define LCD_WR_SET()		LCD_WR = 1
#define LCD_WR_CLR()		LCD_WR = 0

#define LCD_RD_SET()		LCD_RD = 1
#define LCD_RD_CLR()		LCD_RD = 0

#define LCD_WriteWord(n) 	LCD_BUS_H = (u8)(n>>8); LCD_BUS_L = (u8)n; NOP(1);	LCD_WR_CLR(); NOP(1);	LCD_WR_SET();	NOP(1);	

#define	LCD_WR_PULSE()		NOP(1);	LCD_WR_CLR(); NOP(1);	LCD_WR_SET()


//========================================================================
// ����: void LCD_delay(u16 ms)
// ����: ��ʱ����
// ����: ms ��ʱʱ�� 1~65535 ms
// ����: ��
// �汾:
//========================================================================
void LCD_delay(u16 ms)
{
    u16 i;
	do{
	//	i = MAIN_Fosc / 14000;	//STC12F
	//	i = MAIN_Fosc / 13000;	//STC15F
	//	i = MAIN_Fosc / 10000;	//STC8
		i = MAIN_Fosc / 6000;	//STC32G
		while(--i)	;
    }while(--ms);
}


//========================================================================
// ����: void LCD_RegWriteComd(u8 cmd)
// ����: дһ���ֽڵ�������LCD�еĿ��ƼĴ�������
// ����: cmd: �Ĵ�������
// ����: ��
// ��ע: 
// �汾:
//      2007/04/10      First version
//========================================================================
void LCD_RegWriteComd(u8 cmd)
{
	LCD_RS_CLR();			//point to ID register
	LCD_CS_CLR();
	LCD_BUS_H = 0;
	LCD_BUS_L = cmd;
	LCD_WR_PULSE();
	LCD_RS_SET();			//point to GRAM
	LCD_CS_SET();
}

//=========== дһ���ֽڵ�������LCD�еĿ��ƼĴ������� ===================
void LCD_RegWriteData(u8 dat)
{
//	LCD_RS_SET();			//point to GRAM
	LCD_CS_CLR();
	LCD_BUS_H = 0;
	LCD_BUS_L = dat;
	LCD_WR_PULSE();
	LCD_CS_SET();
}


//========================================================================
// ����: void LCD_Init(void)
// ����: LCD��ʼ����������������LCD��ʼ����Ҫ���õ����Ĵ������������
//		 �û����˽⣬����鿴DataSheet���и����Ĵ���������
// ����: �� 
// ����: ��
// �汾: V1.0
//========================================================================
void LCD_Init(void)
{
	P6n_standard(0xff);
	P2n_standard(0xff);
	P4n_standard(0x2e);

	background = 0x00;
	foreground = 0xffff;

	LCD_RS_SET();
	LCD_CS_SET();
	LCD_BUS_H = 0xFF;
	LCD_BUS_L = 0xFF;
	LCD_WR_SET();

	LCD_RST_SET();
	LCD_delay(150);
	LCD_RST_CLR();
	LCD_delay(150);
	LCD_RST_SET();
	LCD_delay(150);

	//************* ILI9481��ʼ��**********//
	LCD_RegWriteComd(0x11);
	LCD_delay(20);
	LCD_RegWriteComd(0xD0);
	LCD_RegWriteData(0x07);
	LCD_RegWriteData(0x42);
	LCD_RegWriteData(0x18);
	
	LCD_RegWriteComd(0xD1);
	LCD_RegWriteData(0x00);
	LCD_RegWriteData(0x07);//07
	LCD_RegWriteData(0x10);
	
	LCD_RegWriteComd(0xD2);
	LCD_RegWriteData(0x01);
	LCD_RegWriteData(0x02);
	
	LCD_RegWriteComd(0xC0);
	LCD_RegWriteData(0x10);
	LCD_RegWriteData(0x3B);
	LCD_RegWriteData(0x00);
	LCD_RegWriteData(0x02);
	LCD_RegWriteData(0x11);
	
	LCD_RegWriteComd(0xC5);
	LCD_RegWriteData(0x03);
	
	LCD_RegWriteComd(0xC8);
	LCD_RegWriteData(0x00);
	LCD_RegWriteData(0x32);
	LCD_RegWriteData(0x36);
	LCD_RegWriteData(0x45);
	LCD_RegWriteData(0x06);
	LCD_RegWriteData(0x16);
	LCD_RegWriteData(0x37);
	LCD_RegWriteData(0x75);
	LCD_RegWriteData(0x77);
	LCD_RegWriteData(0x54);
	LCD_RegWriteData(0x0C);
	LCD_RegWriteData(0x00);
	
	LCD_RegWriteComd(0x36);
	#if (X_DOTS == 320)
		LCD_RegWriteData(0x0A);
	#endif
	#if (X_DOTS == 480)
		LCD_RegWriteData(0x28);
	#endif
	
	LCD_RegWriteComd(0x3A);
	LCD_RegWriteData(0x55);
	
	LCD_RegWriteComd(0x2A);
	LCD_RegWriteData(0x00);
	LCD_RegWriteData(0x00);
//	LCD_RegWriteData(0x01);
//	LCD_RegWriteData(0x3F);
	LCD_RegWriteData(((X_DOTS-1)>>8));
	LCD_RegWriteData(((X_DOTS-1)&0xff));
	
	LCD_RegWriteComd(0x2B);
	LCD_RegWriteData(0x00);
	LCD_RegWriteData(0x00);
//	LCD_RegWriteData(0x01);
//	LCD_RegWriteData(0xE0);
	LCD_RegWriteData(((Y_DOTS-1)>>8));
	LCD_RegWriteData(((Y_DOTS-1)&0xff));

	LCD_delay(120);
//	LCD_RegWriteComd(0x21);	//ȡ����ʾ, �е���Ҫȡ������������ʾ
	LCD_RegWriteComd(0x29);
	LCD_RegWriteComd(0x2c);

	//����LCD���Բ���
	SetView_V();		//����
	LCD_delay(1);
	LCD_Fill_XY(0,0,X_DOTS,Y_DOTS,0x0000);

}


/*************************************************
����: void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd)
����: ����lcd��ʾ���ڣ��ڴ�����д�������Զ�����. ÿ�д� xStar��ʼ ��yStar����, ���xStar==yStar��ֻдһ��㻻��, �������ڻ�����.
���: xy�����յ�
����: ��
*************************************************/
void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd)
{
	LCD_RegWriteComd(0x2a);	
	LCD_RegWriteData((u8)(xStar>>8));
	LCD_RegWriteData((u8)(xStar &0xff));		
	LCD_RegWriteData((u8)(xEnd>>8));
	LCD_RegWriteData((u8)(xEnd &0xff));

	LCD_RegWriteComd(0x2b);	
	LCD_RegWriteData((u8)(yStar>>8));
	LCD_RegWriteData((u8)(yStar &0xff));		
	LCD_RegWriteData((u8)(yEnd>>8));
	LCD_RegWriteData((u8)(yEnd &0xff)); 

	LCD_RegWriteComd(0x2c);	//��ʼд��GRAM
}   

//========================================================================
// ����: void LCD_Fill_XY(u8 x0,u16 y0,u8 x,u16 y,u16 color)
// ����: ������俪ʼ����Ϊx0,y0,��x,��y,��color��������������
// ����: x0,y0 ��ʼ����,  x ��,	y ��, color: Ҫ������ɫ����
// ����: ��
// �汾: V1.0
//========================================================================
void LCD_Fill_XY(u16 x0,u16 y0,u16 x,u16 y,u16 color)
{
	u8 i;

	LCD_SetWindows(x0,y0,x0+x-1,y0+y-1);	//������ʾ����
	LCD_RS = 1;	LCD_CS_CLR();
	LCD_BUS_H = (u8)(color>>8);
	LCD_BUS_L = (u8)color;

	i = (u8)(((u32)x *(u32)y) & 7);	//��д����8��������
	while(i != 0)
	{
		LCD_WR_PULSE();
		i--;
	}
	x = (u16)(((u32)x *(u32)y) /8);	//д8����
	while(x != 0)	//ƽ��ÿ��ѭ����������8T
	{
		LCD_WR_PULSE();	//��һ��д����, ��д��һ����(2�ֽ�).
		LCD_WR_PULSE();
		LCD_WR_PULSE();
		LCD_WR_PULSE();
		LCD_WR_PULSE();
		LCD_WR_PULSE();
		LCD_WR_PULSE();
		LCD_WR_PULSE();
		x--;
	}
	LCD_CS_SET();

}


/**********************************************/
/*	x,yΪ��ʼ����,indexΪASCII�ַ�	*/
void text_ascii5x7(u16 x,u16 y,u8 index)
{
	u8 const *p;
 	u8 i,s,b;

	if(x > 474)	return;	//���
	if(y > 314)	return;	//���

	LCD_SetWindows(x,y,x+5-1,y+8-1);
	LCD_RS = 1;	LCD_CS = 0;

	p = (u16)index * 8 + ASCII5x7;
	for(i=0; i<8; i++)
	{    
		b = *p;	p++;
		for(s=0; s<5; s++)
		{
			if(b & 0x10)	{LCD_WriteWord(foreground);}
			else			{LCD_WriteWord(background);}
			b <<= 1;
		}
	}
	LCD_CS = 1;
}

//========================================================================
// ����: void HZ_12x12s(u16 x,u16 y,u16 hz_code)
// ����: ��x,yΪ��ʼ����,hzΪ�����׵�ַ����ʾ11*11�ĺ��֡�
//		 �ڱ���ɫbackground����ǰ��ɫforeground��ʾ���֡�
// ����: x  y������     hz �����׵�ַ
// ����: ��
// ��ע: ʹ��ǰ��ɫ
//========================================================================
void HZ_12x12s(u16 x,u16 y,u16 hz_code)
{
	u8 const *p;
	u8 i,s,b;

	if(x > 468)	return;	//���
	if(y > 308)	return;	//���

 	LCD_SetWindows(x,y,x+12-1,y+12-1);
	LCD_RS = 1;	LCD_CS = 0;

	p = hz_code * 18 + HZK12;
	for(i=0; i<18; i++)
	{    
		b = *p;	p++;
 		for(s=0; s<8; s++)
		{
			if(b & 0x80)	{LCD_WriteWord(foreground);}
			else			{LCD_WriteWord(background);}
			b <<= 1;
		}
	}
	LCD_CS = 0;
}

/************ �ַ�����ʾ *************************/
void	printf_text(u16 x,u16 y,u8 *ptr)
{
    u8 c1,c2,i;
	
	for (;;)
	{
        c1 = *ptr;
		ptr++;
		if(c1 == 0)		return;	//����ֹͣ��0����
		if(c1 < 0xa0)			//ASCII��
		{
			text_ascii5x7(x,y+2,c1);
			x += 6;
		}
		else					//����
		{
			c2 = *ptr;
			ptr++;
			if(c2 == 0)		return;	//����ֹͣ��0����

			for(i=0; i < sizeof(HZK)/2; i++)    // ���Ҷ�λ
			{				
				if((c1 == HZK[i*2]) && (c2 == HZK[i*2+1]))
				{
					HZ_12x12s(x,y,(u16)i);
					x += 12;
				}
			}
		}
	}
} 

//========================================================================
// ����: void Line_h(u8 x,u16 y,u8 lenth,u16 color)
// ����: ��x��yΪ��ʼ���꣬lenthΪ���ȣ�colorΪ��ɫ����һ������
// ����: x  X������     y  Y������
// ����: ��
// ��ע: ʹ��ǰ��ɫ
// �汾: V1.0
//========================================================================
void	Line_h(u16 x,u16 y,u16 lenth,u16 color)
{  
	u8	i;
	
	LCD_SetWindows(x,y,x+lenth-1, y);
	LCD_CS_CLR();
	LCD_BUS_H = (u8)(color>>8);
	LCD_BUS_L = (u8)color;

	i = (u8)lenth & 7;
	while(i != 0)
	{
		LCD_WR_PULSE();
		i--;
	}
	i = (u8)(lenth >> 3);
	while(i != 0)
	{
		LCD_WR_PULSE();	//��һ��д����, ��д��һ����(2�ֽ�).
		LCD_WR_PULSE();
		LCD_WR_PULSE();
		LCD_WR_PULSE();
		LCD_WR_PULSE();
		LCD_WR_PULSE();
		LCD_WR_PULSE();
		LCD_WR_PULSE();
		i--;
	}
	LCD_CS_SET();
}

//========================================================================
// ����: void Line_v(u8 x,u16 y,u16 lenth,u16 color)
// ����: ��x��yΪ��ʼ���꣬lenthΪ���ȣ�colorΪ��ɫ����һ������
// ����: x  X������     y  Y������
// ����: ��
// ��ע: ʹ��ǰ��ɫ
// �汾: V1.0
//========================================================================
void	Line_v(u16 x,u16 y,u16 lenth,u16 color)
{  
	u8	i;

	LCD_SetWindows(x,y,x,y+lenth-1);
	LCD_CS_CLR();
	LCD_BUS_H = (u8)(color>>8);
	LCD_BUS_L = (u8)color;

	i = (u8)lenth & 7;
	while(i != 0)
	{
		LCD_WR_PULSE();
		i--;
	}
	i = (u8)(lenth >> 3);
	while(i != 0)
	{
		LCD_WR_PULSE();	//��һ��д����, ��д��һ����(2�ֽ�).
		LCD_WR_PULSE();
		LCD_WR_PULSE();
		LCD_WR_PULSE();
		LCD_WR_PULSE();
		LCD_WR_PULSE();
		LCD_WR_PULSE();
		LCD_WR_PULSE();
		i--;
	}
	LCD_CS_SET();
}


//========================================================================
// ����: void Rectangle(u8 x0,u16 y0,u8 x,u16 y,u16 color)
// ����: ������
// ����: x0,y0��ʼ����,	x ��,	y ��, colcr ��ɫ
// ����: ��
// �汾:
//========================================================================
void Rectangle(u16 x0,u16 y0,u16 x,u16 y,u16 color)
{
	Line_h(x0,y0,x,color);
	Line_h(x0,y0+y-1,x,color);
	Line_v(x0,y0,y,color);
	Line_v(x0+x-1,y0,y,color);
}

void	SetView_H(void)		//����
{
	LCD_RegWriteComd(0x36);
//	LCD_RegWriteData(0x28);		//����
	LCD_RegWriteData(0x2B);		//���� ��ת180��

	LCD_RegWriteComd(0x2A);
	LCD_RegWriteData(0x00);
	LCD_RegWriteData(0x00);
	LCD_RegWriteData(((480-1)>>8));
	LCD_RegWriteData(((480-1)&0xff));

	LCD_RegWriteComd(0x2B);
	LCD_RegWriteData(0x00);
	LCD_RegWriteData(0x00);
	LCD_RegWriteData(((320-1)>>8));
	LCD_RegWriteData(((320-1)&0xff));
}
void	SetView_V(void)		//����
{
	LCD_RegWriteComd(0x36);
//	LCD_RegWriteData(0x0A);		//����
	LCD_RegWriteData(0x09);		//���� ��ת180��

	LCD_RegWriteComd(0x2A);
	LCD_RegWriteData(0x00);
	LCD_RegWriteData(0x00);
	LCD_RegWriteData(((320-1)>>8));
	LCD_RegWriteData(((320-1)&0xff));

	LCD_RegWriteComd(0x2B);
	LCD_RegWriteData(0x00);
	LCD_RegWriteData(0x00);
	LCD_RegWriteData(((480-1)>>8));
	LCD_RegWriteData(((480-1)&0xff));
}

//=============== �������㺯�� =============================
void	WriteSingleDot(u16 x, u16 y, u16 color)
{
	LCD_SetWindows(x,y, x,y);
	LCD_CS_CLR();
	LCD_WriteWord(color);
	LCD_CS_SET();
}

//ר�����ʾ����д���Ӻ���, Ϊ�˾�����, �ռ任ʱ��, ���ٴ���.
//д��8����
void  Write_8dots(void)
{
	LCD_WR_PULSE();	//��һ��д����, ��д��һ����(2�ֽ�).
	LCD_WR_PULSE();
	LCD_WR_PULSE();
	LCD_WR_PULSE();
	LCD_WR_PULSE();
	LCD_WR_PULSE();
	LCD_WR_PULSE();
	LCD_WR_PULSE();
}
//д��7����
void  Write_7dots(void)
{
	LCD_WR_PULSE();	//��һ��д����, ��д��һ����(2�ֽ�).
	LCD_WR_PULSE();
	LCD_WR_PULSE();
	LCD_WR_PULSE();
	LCD_WR_PULSE();
	LCD_WR_PULSE();
	LCD_WR_PULSE();
}

//ÿ��25�㻭һ����ǵ�
void	Line_Grid25(u16 x,u16 y,u16 color)
{  
	u8	i;
	
	LCD_SetWindows(x,y,x+251-1, y);
	LCD_CS_CLR();
	for(i=0; i<4; i++)
	{
		LCD_BUS_H = (u8)(BLACK>>8);
		LCD_BUS_L = (u8)BLACK;
		Write_8dots();	//д24�����ɫ
		Write_8dots();
		Write_8dots();
		LCD_WriteWord(color);	//дһ����
	}
		LCD_BUS_H = (u8)(BLACK>>8);
		LCD_BUS_L = (u8)BLACK;
		Write_8dots();	//д23�����ɫ
		Write_8dots();
		Write_7dots();
		LCD_BUS_H = (u8)(color>>8);
		LCD_BUS_L = (u8)color;
		LCD_WR_PULSE();	//дһ����
		LCD_WR_PULSE();	//дһ����
		LCD_WR_PULSE();	//дһ����

		LCD_BUS_H = (u8)(BLACK>>8);
		LCD_BUS_L = (u8)BLACK;
		Write_8dots();	//д23�����ɫ
		Write_8dots();
		Write_7dots();
		LCD_WriteWord(color);	//дһ����

	for(i=0; i<3; i++)
	{
		LCD_BUS_H = (u8)(BLACK>>8);
		LCD_BUS_L = (u8)BLACK;
		Write_8dots();	//д24�����ɫ
		Write_8dots();
		Write_8dots();
		LCD_WriteWord(color);	//дһ����
	}

		LCD_BUS_H = (u8)(BLACK>>8);
		LCD_BUS_L = (u8)BLACK;
		Write_8dots();	//д26�����ɫ
		Write_8dots();
		Write_8dots();
		LCD_WR_PULSE();	//дһ����
		LCD_WR_PULSE();	//дһ����
	LCD_CS_SET();
}

//ÿ��5�㻭һ����ǵ�
void	Line_Grid5(u16 x,u16 y,u16 color)
{  
	u8	i;
	
	LCD_SetWindows(x,y,x+251-1, y);
	LCD_CS_CLR();
	for(i=0; i<120; i +=5)
	{
		LCD_BUS_H = (u8)(BLACK>>8);
		LCD_BUS_L = (u8)BLACK;
		LCD_WR_PULSE();	//д4����
		LCD_WR_PULSE();
		LCD_WR_PULSE();
		LCD_WR_PULSE();
		LCD_WriteWord(color);	//дһ����
	}
		LCD_BUS_H = (u8)(BLACK>>8);
		LCD_BUS_L = (u8)BLACK;
		LCD_WR_PULSE();	//д3����
		LCD_WR_PULSE();
		LCD_WR_PULSE();
		LCD_BUS_H = (u8)(color>>8);
		LCD_BUS_L = (u8)color;
		LCD_WR_PULSE();	//дһ����
		LCD_WR_PULSE();	//дһ����
		LCD_WR_PULSE();	//дһ����

		LCD_BUS_H = (u8)(BLACK>>8);
		LCD_BUS_L = (u8)BLACK;
		LCD_WR_PULSE();	//д3����
		LCD_WR_PULSE();
		LCD_WR_PULSE();
		LCD_WriteWord(color);	//дһ����

	for(i=130; i<245; i +=5)
	{
		LCD_BUS_H = (u8)(BLACK>>8);
		LCD_BUS_L = (u8)BLACK;
		LCD_WR_PULSE();	//д4����
		LCD_WR_PULSE();
		LCD_WR_PULSE();
		LCD_WR_PULSE();
		LCD_WriteWord(color);	//дһ����
	}
		LCD_BUS_H = (u8)(BLACK>>8);
		LCD_BUS_L = (u8)BLACK;
		LCD_WR_PULSE();	//д6����
		LCD_WR_PULSE();
		LCD_WR_PULSE();
		LCD_WR_PULSE();
		LCD_WR_PULSE();
		LCD_WR_PULSE();
	LCD_CS_SET();
}


u16 xdata DMA_tmp[256];

/**********************************************/
/*	x,yΪ��ʼ����,indexΪASCII�ַ�	*/
void DMA_text_ascii_8x16(u16 x,u16 y,u8 index)
{
	u8 const *p;
 	u8 i,s,b;
	u16	j;

	if(x > 472)	return;	//���
	if(y > 312)	return;	//���
	if(index < 0x20)	return;	//���

	p = (u16)(index-0x20) * 16 + ASCII_8x16_H;
	for(j=0, i=0; i<16; i++)
	{    
		b = *p;	p++;
		for(s=0; s<8; s++)
		{
			if(b & 0x80)	DMA_tmp[j] = foreground;
			else			DMA_tmp[j] = background;
			b <<= 1;
			j++;
		}
	}
	LCD_SetWindows(x,y,x+8-1,y+16-1);
	LCD_RS = 1;	LCD_CS = 0;
	DMA_LCM_AMT  = (u8)(128-1);			//���ô������ֽ���(��8λ)��n+1
	DMA_LCM_AMTH = (u8)((128-1)>>8);	//���ô������ֽ���(��8λ)��n+1
	DMA_LCM_STA  = 0x00;
	DMA_LCM_CR   = 0xa0;	//����DMA�������ݹ���
	while((DMA_LCM_STA & 0x01) == 0)	{	NOP(1);	}	//�ȴ�DMA�������
	DMA_LCM_STA  = 0x00;
	DMA_LCM_CR   = 0x00;	//��ֹDMA
	LCD_CS = 1;
}
	

//========================================================================
// ����: void HZ_12x12s(u16 x,u16 y,u16 hz_code)
// ����: ��x,yΪ��ʼ����,hzΪ�����׵�ַ����ʾ11*11�ĺ��֡�
//		 �ڱ���ɫbackground����ǰ��ɫforeground��ʾ���֡�
// ����: x  y������     hz �����׵�ַ
// ����: ��
// ��ע: ʹ��ǰ��ɫ
//========================================================================
void DMA_HZ_16x16(u16 x,u16 y,u16 hz_code)
{
	u8	const *p;
	u8	i,s,b;
	u16	j;

	if(x > 464)	return;	//���
	if(y > 304)	return;	//���
	
	p = hz_code * 32 + HZK_16;
	for(j=0, i=0; i<32; i++)
	{    
		b = *p;	p++;
 		for(s=0; s<8; s++)
		{
			if(b & 0x80)	DMA_tmp[j] = foreground;
			else			DMA_tmp[j] = background;
			b <<= 1;
			j++;
		}
	}
 	LCD_SetWindows(x,y,x+16-1,y+16-1);
	LCD_RS = 1;	LCD_CS = 0;
	DMA_LCM_AMT  = (u8)(256-1);			//���ô������ֽ���(��8λ)��n+1
	DMA_LCM_AMTH = (u8)((256-1)>>8);	//���ô������ֽ���(��8λ)��n+1
	DMA_LCM_STA  = 0x00;
	DMA_LCM_CR   = 0xa0;	//����DMA�������ݹ���
	while((DMA_LCM_STA & 0x01) == 0)	{	NOP(1);	}	//�ȴ�DMA�������
	DMA_LCM_STA  = 0x00;
	DMA_LCM_CR   = 0x00;	//��ֹDMA
	LCD_CS = 1;
}
/************ DMA�ַ�����ʾ *************************/
//������ʾ����ʱʹ��DMA.
void	DMA_printf_text16(u16 x,u16 y,u8 *ptr)
{
    u8 c1,c2,i;
	
	for (;;)
	{
        c1 = *ptr;
		ptr++;
		if(c1 == 0)		return;	//����ֹͣ��0����
		if(c1 < 0xa0)			//ASCII��
		{
			DMA_text_ascii_8x16(x,y+2,c1);
			x += 8;
		}
		else					//����
		{
			c2 = *ptr;
			ptr++;
			if(c2 == 0)		return;	//����ֹͣ��0����

			for(i=0; i < sizeof(HZK16)/2; i++)    // ���Ҷ�λ
			{				
				if((c1 == HZK16[i*2]) && (c2 == HZK16[i*2+1]))
				{
					DMA_HZ_16x16(x,y,(u16)i);
					x += 16;
				}
			}
		}
	}
}


/*****************************************************************************
 * @name       :void LCM_Config(void)
 * @date       :2018-11-13 
 * @function   :Config LCM
 * @parameters :None
 * @retvalue   :None
******************************************************************************/	
void LCM_Config(void)
{
	P_SW2 |= 0x80;
	LCMIFCFG  = 0x06;	//P6���ֽ�, P2���ֽ�, 16Ϊ����, 8080�ӿ�.
	LCMIFCFG2 = 0x09;	//RS:P45,RD:P44,WR:P42; Setup Time=2,HOLD Time=1
	LCMIFSTA  = 0x00;
	LCMIFCR   = 0x80;		//Enable interface, write command out
}

/*****************************************************************************
 * @name       :void DMA_Config(void)
 * @date       :2020-12-09 
 * @function   :Config DMA
 * @parameters :None
 * @retvalue   :None
******************************************************************************/	
void DMA_Config(void)
{
	P_SW2 |= 0x80;
	DMA_LCM_AMT  = (u8)(512-1);			//���ô������ֽ���(��8λ)��n+1
	DMA_LCM_AMTH = (u8)((512-1)>>8);	//���ô������ֽ���(��8λ)��n+1
	DMA_LCM_TXAH = (u8)((u16)&DMA_tmp >> 8);	//���͵�ַ�Ĵ������ֽ�
	DMA_LCM_TXAL = (u8)((u16)&DMA_tmp);			//���͵�ַ�Ĵ������ֽ�
	DMA_LCM_STA  = 0x00;
	DMA_LCM_CFG  = 0x00;		//�����ж�
	DMA_LCM_CR   = 0x00;
}


