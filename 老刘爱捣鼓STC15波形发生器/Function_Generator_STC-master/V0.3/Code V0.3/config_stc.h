#ifndef CONFIG_STC_H
#define CONFIG_STC_H

sfr AUXR = 0x8E; //0000,0000 �����Ĵ���
sfr T2H = 0xD6;  //0000,0000 T2���ֽ�
sfr T2L = 0xD7;  //0000,0000 T2���ֽ�

sfr P0M1 = 0x93;
sfr P0M0 = 0x94;
sfr P1M1 = 0x91;
sfr P1M0 = 0x92;
sfr P2M1 = 0x95;
sfr P2M0 = 0x96;
sfr P4M1 = 0xb3;
sfr P4M0 = 0xb4;
sfr P_SW2 = 0xba;
sfr PWMCFG = 0xf1; //PWM���üĴ���
sfr PWMCR = 0xf5;  //PWM���ƼĴ���
sfr PWMIF = 0xf6;  //PWM�жϱ�־�Ĵ���
sfr P4 = 0xC0;

sbit PWM3 = P4 ^ 5;
sbit PWM4 = P4 ^ 4;
sbit EC11_KEY = P3 ^ 2; //���������������ⲿ�ж�2
sbit EC11_A = P3 ^ 3;   //������A���������ⲿ�ж�1
sbit EC11_B = P3 ^ 4;   //������B����������ͨIO��

sbit P26 = P2 ^ 6;
#endif