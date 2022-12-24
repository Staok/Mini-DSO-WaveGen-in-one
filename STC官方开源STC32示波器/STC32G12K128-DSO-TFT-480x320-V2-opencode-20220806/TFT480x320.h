
#ifndef		_TFT480x320_h
#define		_TFT480x320_h

#include	"config.h"

#define	D_BackGround	(210/8*2048+210/4*32+210/8)
#define	D_BackLight		64	//���ñ������ȵȼ�Ϊ60(0~127)
#define	picture_en		0	//1: �������ͼƬ��0����ֹ

#define	LCD_sleep_en	0		//1: ����LCD˯��,
#define X_DOTS			320		//480: �ῴ��320��������

#if (X_DOTS == 320)
	#define Y_DOTS			480
#elif (X_DOTS == 480)
	#define Y_DOTS			320
#endif

//������ɫ
#define WHITE       0xFFFF	//��ɫ
#define BLACK      	0x0000	//��ɫ	  
#define BLUE       	0x001F	//��ɫ  
#define BRED        0XF81F
#define GRED 		0XFFE0
#define GBLUE		0X07FF	//
#define RED         0xF800	//��ɫ
#define MAGENTA     0xF81F	//��� Ʒ�� �Ϻ�
#define GREEN       0x07E0	//��ɫ
#define CYAN        0x7FFF	//����ɫ
#define YELLOW      0xFFE0	//��ɫ
#define BROWN 		0XBC40	//��ɫ
#define BRRED 		0XFC07	//�غ�ɫ
#define GRAY  		0X8430	//��ɫ


/*************	TFT240x320_24.c��������	**********************/
void	LCD_delay(u16 ms);
void	LCD_Init(void);
void	text_ascii5x7(u16 x, u16 y, u8 index);
void	Set_Dot_Addr_LCD(u16 x,u16 y);
void	LCD_WriteDot(u16 color);
void 	LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd);

void	Rectangle(u16 x0,u16 y0,u16 x,u16 y,u16 color);
void	Line_v(u16 x, u16 y, u16 lenth,u16 color);
void	Line_h(u16 x, u16 y, u16 lenth,u16 color);
void	Line_Grid25(u16 x,u16 y,u16 color);
void	Line_Grid5(u16 x,u16 y,u16 color);
void	HZ_12x12s(		u16 x, u16 y, u16 hz);

void	LCD_Fill_XY(u16 x0,u16 y0,u16 x,u16 y,u16 color);
void	button_dn(u16 x0,u16 y0,u16 x_lenth,u16 y_lenth);
void	windows(u16 x0,u16 y0,u16 x_lenth,u16 y_lenth,u8 const *ptr);
void	button_unselect(u16 x0,u16 y0,u16 x_lenth,u16 y_lenth,u8 const *ptr);
void	button_select(u16 x0,u16 y0,u16 x_lenth,u16 y_lenth,u8 const *ptr);
void	ShowImageXY(u16 x0,u16 y0,u16 x,u16 y,u8 const *map);
void	printf_text(u16 x, u16 y, u8 *ptr);
void	PutString(u16 x,u16 y,u8 *puts);

void 	LCD_RegWriteAddr(u8 Reg_Addr);
void 	LCD_RegWriteData(u8 dat);
void	SetView_H(void);		//����
void	SetView_V(void);		//����
void	WriteSingleDot(u16 x, u16 y, u16 color);
void 	DMA_text_ascii_8x16(u16 x,u16 y,u8 index);
void 	DMA_HZ_16x16(u16 x,u16 y,u16 hz_code);
void	DMA_printf_text16(u16 x,u16 y,u8 *ptr);
void 	LCM_Config(void);
void 	DMA_Config(void);

extern	u16	foreground,background;
extern	u8	edata rd_buffer[];

/************************************************************/


#endif

