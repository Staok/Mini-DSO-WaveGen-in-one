/*Register of MCU and Pins defined here*/

#ifndef CONFIG_STC_H
#define CONFIG_STC_H

#include <reg51.h>
//#include <STC8.H>
//#define DEBUG

/* ADC����ͨ������
   ADC Channel Setup */
#define ADC_DSO ADC_CHS_06
#define ADC_BAT ADC_CHS_04

/* ���⹦�ܼĴ���
    Special Function Register */
sfr AUXR = 0x8e;
sfr P0M0 = 0x94;
sfr P0M1 = 0x93;
sfr P1M0 = 0x92;
sfr P1M1 = 0x91;
sfr P2M0 = 0x96;
sfr P2M1 = 0x95;
sfr P3M0 = 0xb2;
sfr P3M1 = 0xb1;

/* EC11�������ܽ�����
   Setup EC11 Encoder Pin */
sbit EC11_KEY = P3 ^ 3; //���������������ⲿ�ж�1 connect to External Interrupt 1
sbit EC11_A = P3 ^ 2;   //������A���������ⲿ�ж�0 connect to External Interrupt 0
sbit EC11_B = P3 ^ 4;   //������B����������ͨIO�� connect to GPIO

/* ��������ָʾ��
   Indicator for sampling running */
sbit P_Ready = P1 ^ 1;

/*  OLED Pin */
sbit OLED_SCLK = P2 ^ 7; //ʱ�ӣ�D0/SCLK��
sbit OLED_SDIN = P2 ^ 6; //���ݣ�D1/MOSI��
sbit OLED_RST = P2 ^ 5;  //��λ��RES��
sbit OLED_DC = P2 ^ 4;   //����/������ƣ�DC��
sbit OLED_CS = P2 ^ 3;   //Ƭѡ��CS��

#ifdef DEBUG
sbit P15 = P1 ^ 5;
#endif

#endif