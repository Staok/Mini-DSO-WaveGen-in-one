#ifndef CONFIG_STC_H
#define CONFIG_STC_H

#include <reg51.h>
//#include <STC8.H>

#define ADC_DSO ADC_CHS_06
#define ADC_BAT ADC_CHS_04

sfr AUXR        =   0x8e;

sbit EC11_KEY = P3 ^ 3; //���������������ⲿ�ж�1
sbit EC11_A = P3 ^ 2;   //������A���������ⲿ�ж�0
sbit EC11_B = P3 ^ 4;   //������B����������ͨIO��

#endif