#ifndef WAVE_H
#define WAVE_H

#include <reg51.h>
#include <intrins.h>
#include "config_stc.h"
#include "delay.h"

#ifndef uint8
#define uint8 unsigned char
#endif

#ifndef int8
#define int8 char
#endif

#ifndef uint16
#define uint16 unsigned int
#endif

#ifndef uint32
#define uint32 unsigned long int
#endif

#define FOSC 24000000UL                           //��ʱ��
#define SPWM_VECTOR 22                             //PWM�ж����
#define TIMER_1 3                                 //��ʱ��1�ж����
#define CBIF 0x40                                 //PWM�����������жϱ�־
#define SIN_TABLE_PWM_HZ 150000                   //T_SinTable����ʹ�õ�PWMƵ�ʣ���FOSC/SIN_TABLE_PWM_HZ���PWM�����
#define SIN_POINTS 1000                           //T_SinTable����
#define SIN_OFFSET 1                              //SINֵƫ����������������һ�η�ת�͵ڶ��η�ת��Ϊ0���������Ӧ�÷�ת���Σ�����ֻ��ת��һ�Σ���ɵ�ƽ����
#define WAVE_NUM 2                                //����ѡ�����������ʱֻ���˷��������Ҳ�������Ϊ2����Wave_Shape=0ʱ����ת����ʾVCC��ѹ
#define PWM_MAX_DUTY 99                           //PWM���ռ�ձ�
#define PWM_MIN_DUTY 1                            //PWM��Сռ�ձ�
#define PWM_MIN_WIDTH 200                         //PWM��С��ȳ���ʱ�� ns
#define PWM_MAX_HZ 2000000                        //PWM���Ƶ��2MHz
#define PWM_MIN_HZ 1                              //PWM��СƵ��1Hz
#define SIN_MAX_HZ 10000                          //SIN���Ƶ��10kHz
#define SIN_MIN_HZ 1                              //SIN��СƵ��1Hz
#define CKS_50HZ 12                               //С��50Hz��ʱ�ӷ�Ƶ
#define PWMC (*(uint16 volatile xdata *)0xfff0)   //PWM������
#define PWMCKS (*(uint8 volatile xdata *)0xfff2)  //PWMʱ��ѡ��λ
#define PWM3T1 (*(uint16 volatile xdata *)0xff10) //PWM3T1������
#define PWM3T2 (*(uint16 volatile xdata *)0xff12) //PWM3T2������
#define PWM3CR (*(uint8 volatile xdata *)0xff14)  //PWM3����λ
#define PWM4T1 (*(uint16 volatile xdata *)0xFF20) //PWM4T1������
#define PWM4T2 (*(uint16 volatile xdata *)0xFF22) //PWM4T2������
#define PWM4CR (*(uint8 volatile xdata *)0xFF24)  //PWM4����λ

extern uint8 PWMCKS_PS;       //ϵͳʱ�ӷ�Ƶϵ��
extern uint32 PWM_Hz;         //PWMƵ��
extern uint32 PWM_Hz_Pre;     //��¼��һ��PWMƵ��
extern int8 PWM_Duty;         //PWMռ�ձ�
extern uint32 SIN_Hz;         //SINƵ��
extern uint8 Wave_Shape;      //���α�־ 1:���� 2:���Ҳ�
extern uint8 Wave_Shape_Pre;  //�ϴβ��α�־
extern uint8 Sin_Table_Times; //SIN����
extern bit WAVE_ON;           //������α�־λ 1:ON 2:OFF

void Set_Wave_Shape();
void Wave_OFF();
#endif