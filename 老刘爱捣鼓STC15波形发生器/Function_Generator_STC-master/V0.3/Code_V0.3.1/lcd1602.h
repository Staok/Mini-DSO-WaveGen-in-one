#ifndef LCD1602_H
#define LCD1602_H

//#include "stc_header.h"
#include "delay.h"
#include "reg51.h"

#ifndef uint8
#define uint8 unsigned char
#endif

#ifndef uint16
#define uint16 unsigned int
#endif

#define LCD_INIT 0x38 				//0011 1000����ʼ������8λ�������ߣ�5x8����
#define LCD_CLEAR 0x01 				//0000 0001������
#define LCD_OFF 0x08				//0000 1000������ʾ
#define LCD_CURSOR_BLINK 0x0f		//0000 1111������ʾ���й�겢��˸
#define LCD_NOCURSOR 0x0c			//0000 1100������ʾ���޹��
#define LCD_MODE 0x06				//0000 0110������дһ���ַ��󣬹�����ƣ�ָ���1
#define LCD_HOME1 0x80				//���ص����Ͻ�
#define LCD_HOME2 (0x80+0x40)		//���ص����½�
#define BF_COUT 100 				//���æµ����

#define DataPort P1			//LCD���ݺ�����ӿ�
sbit RS=P0^5;	 			//LCD��������ѡ��
sbit RW=P0^6;	 			//LCD��дѡ��               
sbit E=P0^7;	  			//LCDʹ��

extern uint8 code page1_position[];
extern uint8 code page2_position[];

void Lcd_Init(void);
bit Lcd_Check_Busy(void);
void Lcd_Write_Command(uint8);
void Lcd_Write_Data(uint8);
void Lcd_Write_Str(uint8 *s);
void Lcd_Write_Int(long int i);

//void Lcd_Display_HEX(unsigned int num);
//void Lcd_Display_INT(unsigned int num);
#endif



