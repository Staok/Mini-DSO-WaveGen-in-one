
/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC 1T Series MCU Demo Programme -------------------------------*/
/* --- Tel: 86-0513-55012928,55012929 ---------------------------------*/
/* --- Web: www.STCMCUDATA.com  ---------------------------------------*/
/* --- QQ:  800003751 -------------------------------------------------*/
/* ���Ҫ�ڳ�����ʹ�ô˴���,���ڳ�����ע��ʹ����STC�����ϼ�����        */
/* ������Ϊ����Ӧ�ó���, �Ѳ���ͨ��, �û������������, ���ṩ����֧��  */
/*---------------------------------------------------------------------*/

/*************	����˵��	**************

�����̻���STC32GΪ����оƬ���б�д���ԡ�

ʹ��Keil C251��������Memory Model�Ƽ�����XSmallģʽ��Ĭ�϶��������edata����ʱ�Ӵ�ȡ�����ٶȿ졣

��ʾ��������

�����ļ�:
EEPROM.c
TFT480x320-V2.c
OSCOPE-V2-8bit.c	8bit����


	STC 32λ8051ȫ���ѧ�ƻ�
	������-STC32G12K128��Դʾ����ר��
	2��CAN��USB��32λ8051��
	STC32G12K128���߾�׼12λADC��
	DMA֧�֣�TFT������ADC��4�鴮�ڣ�SPI��I2C��
	STC32G12K128����;����
	0513-55012928��55012929
	������www.STCMCUDATA.com

ʾ��������:
������ѹ: 5.0V��
MCU:      STC32G12K128��ʹ�����������İ���ϡ�
��Ƶ:     35MHz��
ADC:      ��߲���800KHz 12λ����ʾ����ʹ����߲�����500KHz��
ģ�����: ̽ͷx1���ڵ���250mV/DIV��̽ͷx10���ڵ���2.5V/DIV��100KHz��
��ʾ��:   3.2��TFT LCD 480x320��16λ���ݿڡ�
          ˮƽ16��һ��25�㣬һ��400�㣬�洢���4000�㡣
          ��ֱ10��ÿ��25�㣬һ��250�㡣
ʱ��:     1-2-5������50us 100us 200us 500us 1ms 2ms 5ms 10ms 20ms 50ms
                     100ms 200ms 500ms 1s 2s 5s 10s 20s 50s
��ֱ����: ̽ͷx1:   50mV  100mV  250mV  500mV   1V  2.5V   5V  10V/DIV��
          ̽ͷx10: 500mV     1V   2.5V     5V  10V   25V  50V  100V/DIV��
��������ѹ: ̽ͷx1�� +-50V��̽ͷx10��+-500V��
����ģʽ: �����ش������½��ش�����
������ʽ: �Զ�����׼�����Ρ�

******************************************/


#include	"config.h"
#include	"TFT480x320.h"
#include	"EEPROM.h"

/*************	���س�������	**************/
#define		K_UP		1
#define		K_DOWNN		2
#define		K_LEFT		3
#define		K_RIGHT		4
#define		K_OK		5
#define		K_RUN_STOP 	6
#define		K_TRIGGER	7

#define		EE_ADDR		0x000000


/*************	IO������	**************/
sbit	P_K_UP    = P7^4;
sbit	P_K_DOWN  = P7^3;
sbit	P_K_LEFT  = P7^2;
sbit	P_K_RIGHT = P7^1;
sbit	P_K_OK    = P7^0;

sbit	P_V_A    = P0^6;	//��������ѡ��
sbit	P_V_B    = P0^5;	//��������ѡ��, CBA   000 001 010 011 100 101 110 111
sbit	P_V_C    = P5^3;	//��������ѡ��, ����   2   4   10  1   20 200  40 100  
//P0.7--T4CLKO: 1000Hz�������
//P0.4--ADC12: ��������
//P1.0-_PWM1P: ��ֱλ��PWM
//P1.4-_PWM3P: ����ѹ50% PWM
//P3.3--PWM7_2: H1S_L10ms��Ƶբ���ź�, ͬʱҲ��Timer1���������Ƶ�ſ��ź�.
//P3.4--CMPO, �Ƚ��������
//P3.5--T1,   Timer1���������Ƶ�����, ����P3.4--CMPO
//P3.6--CMP-: �Ƚ�������ͬ�����
//P3.7--CMP+: 

	

/*************	���ر�������	**************/
u8	KeyState, KeyCode, KeyHoldCnt;
bit	B_KeyRepeat;

u8	xdata adc_sample[4008];
u8	edata	tmp[32];
u8	edata	adc_tmp[410];
u8	edata	dot[410];
bit	B_ADC_Busy, B_Sample_OK;
u16	adc_wr, adc_rd;
u8	adc;
u8	SampleIndex;
u16	sample_cnt;
bit	B_sample_ms;
u16	SampleTime;
bit	B_Run;
u16	LastDot;
u8	TimeScale;		//ʱ��ϵ��, 10: 10ȡ1, 5: 5ȡ1, 2: 2ȡ1, 1: 1ȡ1
u8	TimeScaleIndex;	//ʱ��ϵ������, 0-->10, 1-->5, 2-->2, 3-->1
bit	B_RUN_REQ;		//����ֹͣ

bit	B_TrigPhase;	//Ĭ�������ش���
bit	B_TrigMode;
u8	TrigMode;

u8	InputIndex;		//���ȵ�λ
u8	AutoTimeCnt;
u8	AutoTime;
u8	pwm1_voltage;

bit	B_FrequencyOk;
u32	frequency;
u8	freq_H;

bit	B_Shift;	//��λ��־, ֹͣʱ�л�ʱ������λ
u16	Shift;		//��λ����
u8	Current_TimeBase;
u8	WriteDelay;	//д����ʱ

u8	cnt_8ms, cnt_32ms;
bit	B_8ms, B_32ms;


/*************	���غ�������	**************/
void	OSCOPE_inilize(void);
void	ShowOscope(void);
void	RealShowOscope(void);
void	Timer0_config(void);
void	Timer1_config(void);
u8		Timer3_Config(u8 t, u32 reload);	//t=0: reloadֵ����ʱ��������,  t=1: reloadֵ��ʱ��(��λus), ����0��ȷ, ����1װ��ֵ�������.
void	Timer4_Config(void);
void	SetSampleTime(void);
void	ShowVoltage(void);

void	ShowTimeBase(void);	//��ʾʱ��
void	ShowPhase(void);
void	ShowRunStop(void);	//��ʾ����״̬
void	ShowStartTime(void);

void	ADC_config(void);
void	Compare_Config(void);	//�Ƚ�����ʼ��
void	PWMA_config(void);
void	PWMB_config(void);
void	ReadKey(void);
void	AutoCheck(void);
void 	ShowTrigMode(void);
void	ShowRunStop(void);
void	OscStop(void);


/****************  �ⲿ�����������ⲿ�������� *****************/

/**************************************************************/

//�������� SampleIndex   0     1      2      3      4     5      6     7      8     9     10     11     12     13     14   15   16    17    18    19    20
//����ʱ��/DIV         10us  20us   50us  100us  200us  500us   1ms   2ms    5ms  10ms   20ms   50ms  100ms  200ms  500ms  1s   2s    5s   10s   20s   50s
//��һά3, ��(SampleIndex % 3)������, �ڶ�ά������ϵ��, ����ΪÿN����ȡһ��, ����������ָ2.5��ȡһ��, ���з�����ÿ5��ȡ0 2����.
u8	const 	T_TimeScale[3][4]={	{10,5,2,1},
								{10,5,3,1},
								{10,4,2,1}};



/****************  ������ *****************/
void	main(void)
{
	u8	i;
	u16	j;

	WTST = 0;
	CKCON = 0;

	P0M1 = 0;	P0M0 = 0;	//����Ϊ׼˫���
	P1M1 = 0;	P1M0 = 0;	//����Ϊ׼˫���
	P2M1 = 0;	P2M0 = 0;	//����Ϊ׼˫���
	P3M1 = 0;	P3M0 = 0;	//����Ϊ׼˫���
	P4M1 = 0;	P4M0 = 0;	//����Ϊ׼˫���
	P5M1 = 0;	P5M0 = 0;	//����Ϊ׼˫���
	P6M1 = 0;	P6M0 = 0;	//����Ϊ׼˫���
	P7M1 = 0;	P7M0 = 0;	//����Ϊ׼˫���
	
	P_SW2 = 0x80;
/*
	XOSCCR = 0xc0;			//�����ⲿ����
	while (!(XOSCCR & 1));	//�ȴ�ʱ���ȶ�
	CLKDIV = 0x00;			//ʱ�Ӳ���Ƶ
	CLKSEL = 0x01;			//ѡ���ⲿ����
*/	
	P0n_push_pull(0x80);	//P0.7 T4CLKO 1000Hz

	P_K_UP    = 1;
	P_K_DOWN  = 1;
	P_K_LEFT  = 1;
	P_K_RIGHT = 1;
	P_K_OK    = 1;
	P33 = 1;	P35 = 1;	//	P3.3--PWM7_2: H1S_L10ms��Ƶբ���ź�

	ADC_config();		//ADC��ʼ��
	Compare_Config();	//ģ��Ƚ�����ʼ��
	Timer0_config();	//Timer0��ʼ��, Ƶ�ʼ�
	Timer1_config();	//Timer1��ʼ��, ����
	Timer3_Config(0, MAIN_Fosc / 5000);	//t=0: reloadֵ����ʱ��������,  (�ж�Ƶ��, 20000��/��)
	Timer4_Config();	//Timer4��ʼ��, ���1000Hz����.
	PWMA_config();		//PWM���ƴ�ֱλ�ơ�������ƽ
	PWMB_config();		//���� H1S_L10msբ���ź����ڲ�Ƶ
	EA = 1;
	
	EX1 = 1;	//�����ж�
	IT1 = 1;	//�½����ж�

	WriteDelay = 0;
	EEPROM_read_n(EE_ADDR, tmp, 6);
	if(tmp[4] == (tmp[0]+tmp[1]+tmp[2]+tmp[3]) ^ 0x55)	//У��
	{
		pwm1_voltage = tmp[0];
		SampleIndex = tmp[1];	InputIndex = tmp[2];	TrigMode = tmp[3];
		if(TrigMode & 0x80)	B_TrigPhase = 1;
		else				B_TrigPhase = 0;
		TrigMode &= 0x03;
		if(pwm1_voltage > 250)	pwm1_voltage = 128;	//Ĭ���е�
		if(SampleIndex > 20)	SampleIndex  = 6;	//Ĭ��1ms/div
		if(SampleIndex < 2)		SampleIndex  = 6;	//Ĭ��1ms/div
		if(InputIndex >= 8)		InputIndex   = 3;	//Ĭ��1V/div
		if(TrigMode >= 3)		TrigMode     = 0;	//Ĭ���Զ�����
		WriteDelay = 0;		//д����ʱ
	}
	else	//У��ûͨ��
	{
		B_TrigPhase = 0;	//Ĭ�������ش���
		pwm1_voltage = 128;	//Ĭ���е�
		SampleIndex  = 6;	//Ĭ��1ms/div
		InputIndex   = 3;	//Ĭ��1V/div
		TrigMode     = 0;	//Ĭ���Զ�����
		WriteDelay   = 250;	//д����ʱ
	}
	PWMA_CCR1L = pwm1_voltage;
	
	background = BLACK;
	foreground = WHITE;

	LCD_Init();		//LCD��ʼ��

	SetView_H();		//����
	LCM_Config();	//LCM��ʼ��
	DMA_Config();	//LCM_DMA��ʼ��, ʹ��DMA��ʽ��ʾ������ַ���.
	DMA_printf_text16(80,  0+40,"   STC 32λ8051ȫ���ѧ�ƻ�");
	DMA_printf_text16(80, 20+40,"������-STC32G12K128��Դʾ����ר��");
	DMA_printf_text16(80, 40+60,"2��CAN, USB, 32λ8051");
	DMA_printf_text16(80, 60+60,"STC32G12K128, �߾�׼12λADC");
	DMA_printf_text16(80, 80+60,"DMA֧��(TFT����, ADC, 4�鴮��, SPI, I2C)");
	DMA_printf_text16(80,100+80,"STC32G12K128����;��:");
	DMA_printf_text16(80,120+80,"0513-55012928, 55012929");
	DMA_printf_text16(80,140+80,"����: www.STCMCUDATA.com");
	DMA_printf_text16(80,180+90,"Please press any key to continue!");
	LCMIFCR   = 0x00;	//��ֹLCM�ӿ�

	KeyCode = 0;
	while(KeyCode == 0)	//�ȴ������
	{
		if(B_32ms)
		{
			B_32ms = 0;
			ReadKey();
		}
	}
	KeyCode = 0;
	LCD_Fill_XY(0,0,480,320,BLACK);

	background = MAGENTA;	//���װ���
//	LCD_Fill_XY(430, 8, 45, 18, MAGENTA);	//���� ֹͣ
	LCD_Fill_XY(430,28, 45, 18, MAGENTA);	//������ �½���
//	LCD_Fill_XY(430,48, 45, 18, MAGENTA);	//�Զ� ��׼ ����
//	LCD_Fill_XY(430,68, 45, 18, MAGENTA);	//��ֱ
//	printf_text(430+4, 8+3, " ����");
	printf_text(430+4,28+3, "������");	//0xfd����, ���ֲ��ܳ���, ͨ��Ϊ��
//	printf_text(430+4,48+3, " �Զ�");
//	printf_text(430+4,68+3, " ��ֱ");

	LCD_Fill_XY(130, 11, 40, 15, MAGENTA);	//ʱ��, ���װ���
	LCD_Fill_XY(180, 11, 40, 15, MAGENTA);	//����, ���װ���
	LCD_Fill_XY(230, 11, 70, 15, MAGENTA);	//Ƶ��, ���װ���

	background = BLACK;
	
	ShowTrigMode();
	ShowPhase();

	B_Shift = 0;
	Shift  = 0;
	B_ADC_Busy = 0;
	SetSampleTime();
	OSCOPE_inilize();
	ShowVoltage();
	B_Run = 1;
	ShowRunStop();
	
	KeyCode = 0;

	while (1)
	{
		if(B_8ms)	//8ms
		{
			B_8ms = 0;
			AutoCheck();	// ������ʱ����
		}

		if(B_32ms)
		{
			B_32ms = 0;
			ReadKey();
			if(WriteDelay != 0)		//��ʱд��
			{
				if(--WriteDelay == 0)
				{
					tmp[0] = pwm1_voltage;
					tmp[1] = SampleIndex;
					tmp[2] = InputIndex;
					tmp[3] = TrigMode;
					if(B_TrigPhase)	tmp[3] |= 0x80;
					tmp[4] = (tmp[0]+tmp[1]+tmp[2]+tmp[3]) ^ 0x55;	//У��
					EEPROM_SectorErase(EE_ADDR);
					EEPROM_write_n(EE_ADDR,tmp,6);
				}
			}
		}
				
		if(B_Run)
		{
			if(!B_ADC_Busy)		//����һ�β�������
			{
				B_Sample_OK = 0;
				adc_wr = 0;
				adc_rd = 0;
					 if(SampleIndex <= 2)	TimeScale = 1,	TimeScaleIndex = 3;	// 50us/DIV		���ȡ	ֹͣʱ2����ڲ�9���10������
				else if(SampleIndex == 3)	TimeScale = 2,	TimeScaleIndex = 2;	// 100us/DIV	2ȡ1	ֹͣʱ2����ڲ�4���5������
				else if(SampleIndex == 4)	TimeScale = 4,	TimeScaleIndex = 1;	// 200us/DIV	4ȡ1	ֹͣʱ2����ڲ�2.5���2.5������
				else 						TimeScale = 10,	TimeScaleIndex = 0;	// >=500us/DIV	10ȡ1
				Current_TimeBase = SampleIndex;
				B_ADC_Busy = 1;
				SetSampleTime();	//���ò���ʱ��
				if(B_TrigPhase)	CMPCR1 = 0x86 + 0x10;	// �Ƚ����������жϴ���, ������
				else			CMPCR1 = 0x86 + 0x20;	// �Ƚ����½����жϴ���, ������
			}
			else if(SampleIndex <= 10)	// <=20ms/DIV
			{
				if(B_Sample_OK)		//�������
				{
					B_Sample_OK = 0;
					B_ADC_Busy  = 0;
					ShowOscope();	//��ʾ����
					if(B_RUN_REQ || (TrigMode == 2))	OscStop();	//����ֹͣ �� ����ģʽ ��ֹͣ����
				}
			}

			else if(B_Sample_OK)	//50ms/DIV���ϲ���, ʵʱˢ��
			{
				B_Sample_OK = 0;
				RealShowOscope();	//ʵʱ��ʾ����
				if(adc_rd >= 4000)	//����
				{
					B_ADC_Busy = 0;
					if(B_RUN_REQ || (TrigMode == 2))	OscStop();	//����ֹͣ �� ����ģʽ ֹͣ����
				}
			}
		}
		else	B_ADC_Busy = 0;

		if(B_FrequencyOk)	//Ƶ����OK
		{
			B_FrequencyOk = 0;

			if(B_Run)
			{
				tmp[0] = frequency / 100000UL;
				tmp[1] = (frequency % 100000UL) / 10000;
				tmp[2] = (frequency % 10000) / 1000;
				tmp[3] = '.';
				tmp[4] = (frequency % 1000) / 100;
				tmp[5] = (frequency % 100) / 10;
				tmp[6] = frequency % 10;
				tmp[7] = 'K';
				tmp[8] = 'H';
				tmp[9] = 'z';
				for(i=0; i<2; i++)
				{
					if(tmp[i] != 0)	break;
					tmp[i] = ' ';
				}
				background = MAGENTA;	//���װ���
				for(i=0; i<10; i++)	text_ascii5x7(230+5+i*6,8+7, tmp[i]);
				background = BLACK;
			}
		}

		if(KeyCode)	//�м�����
		{
			if(KeyCode == K_RUN_STOP)		//����/ֹͣ
			{
				if(!B_Run)			//��ֹͣ������
				{
					if(InputIndex >= 8)	InputIndex = 7;
					ShowVoltage();
					B_Run = 1;		//��������
					B_RUN_REQ = 0;
					ShowRunStop();
					printf_text(25,13, "        ");	//���ʱ�����
					printf_text(350, 13, "    ");		//ȡ����ʾ��ɫ�ƶ�
					B_Shift = 0;
					Shift  = 0;
				}
				else	//������
				{
					if(TrigMode != 0)			OscStop();	//��׼ģʽ ����ģʽ, ��ֱ��ֹͣ
					else if(SampleIndex >= 11)	OscStop();	//ɨ��ģʽ, ��ֱ��ֹͣ
					else	B_RUN_REQ = 1;	//������, ��ֹͣ����, ������ֹͣ
				}
			}

			else if(KeyCode == K_TRIGGER)	//����ģʽ ��ֱ����, ֻ������ʱ���Ե���
			{
				B_TrigMode = ~B_TrigMode;	//�л����� ����ģʽ ��ֱ����
				ShowTrigMode();
			}
			
			else if(KeyCode == K_OK)	//��������м�OK��, ����ʱ�л������� �½��ش���, ֹͣʱ�л�ʱ�����ƶ�����
			{
				if(B_Run)	//������, ���л������½���
				{
					B_TrigPhase = ~B_TrigPhase;
					ShowPhase();
					B_ADC_Busy = 0;		//�л�����ģʽ������������(���û��ֹͣ�Ļ�)
					WriteDelay = 250;	//д����ʱ8��
				}
			}

			else if(KeyCode == K_LEFT)		//��� ʱ��+
			{
				if(B_TrigMode)	//������, ���ڵ��� ����ģʽ ��ֱ����
				{
					if(--TrigMode >= 3)		TrigMode = 2;
					ShowTrigMode();
					B_ADC_Busy = 0;		//�л�����ģʽ������������(���û��ֹͣ�Ļ�)
					WriteDelay = 250;	//д����ʱ8��
				}
				else if(SampleIndex < 20)
				{
					if(B_Run)	//�����иı�ʱ��, ������ı������
					{
						SampleIndex++;
						B_ADC_Busy = 0;
						WriteDelay = 250;	//д����ʱ8��
					}
					else if(TimeScaleIndex != 0)	//ֹͣʱ����ʱ����ˢ�²���
					{
						SampleIndex++;
						TimeScaleIndex--;	//ֹͣʱ����
						Shift = Shift * TimeScale;
						TimeScale = T_TimeScale[Current_TimeBase%3][TimeScaleIndex];	//ʱ��ϵ������, 0-->10, 1-->5, 2-->2, 3-->1
						Shift = Shift / TimeScale;
						if(TimeScaleIndex == 0)	Shift = 0;
						ShowTimeBase();	//��ʾʱ��
						ShowStartTime();	//��ʾ������ʼʱ��
						ShowOscope();		//ֹͣ��ˢ�²���
						WriteDelay = 250;	//д����ʱ8��
					}
				}
			}

			else if(KeyCode == K_RIGHT)		//�Ҽ� ʱ��-
			{
				if(B_TrigMode)	//������, ���ڵ��� ����ģʽ ��ֱ����
				{
					if(++TrigMode >= 3)	TrigMode = 0;
					ShowTrigMode();
					B_ADC_Busy = 0;		//�л�����ģʽ������������(���û��ֹͣ�Ļ�)
					WriteDelay = 250;	//д����ʱ8��
				}
				else if(SampleIndex > 2)
				{
					if(B_Run)	//�����иı�ʱ��, ������ı������
					{
						SampleIndex--;
						B_ADC_Busy = 0;
						WriteDelay = 250;	//д����ʱ8��
					}
					else if(TimeScaleIndex < 3)	//ֹͣʱ����ʱ����ˢ�²���
					{
						SampleIndex--;
						TimeScaleIndex++;	//ֹͣʱ����
						Shift = Shift * TimeScale;
						TimeScale = T_TimeScale[Current_TimeBase%3][TimeScaleIndex];	//ʱ��ϵ������, 0-->10, 1-->5, 2-->2, 3-->1
						Shift = Shift / TimeScale;
						ShowTimeBase();	//��ʾʱ��
						ShowStartTime();	//��ʾ������ʼʱ��
						ShowOscope();		//ֹͣ��ˢ�²���
						WriteDelay = 250;	//д����ʱ8��
					}
				}
			}

			else if(KeyCode == K_UP)	//�ϼ� ��ֱ���� +
			{
				if(B_Run)	//������
				{
					if(B_TrigMode)	//������, ���ڵ��� ����ģʽ ��ֱ����
					{
						if(B_KeyRepeat)		//�ؼ�ʱ�����ƶ�
						{
							if(pwm1_voltage >= 5)	pwm1_voltage -= 5;
						}
						else if(pwm1_voltage != 0)	pwm1_voltage--;
						PWMA_CCR1L = pwm1_voltage;
						WriteDelay = 250;	//д����ʱ8��
					}
					else if(InputIndex != 0)	//������ֱ����
					{
						InputIndex--;
						ShowVoltage();
						WriteDelay = 250;	//д����ʱ8��
					}
				}
				else	//�����ƶ�����
				{
					if(!B_KeyRepeat)	Shift++;
					else				Shift += 10;
					TimeScale = T_TimeScale[Current_TimeBase%3][TimeScaleIndex];	//ʱ��ϵ������, 0-->10, 1-->5, 2-->2, 3-->1
					if(TimeScale == 3)	j = 8000/5 - 400;
					else				j = 4000/TimeScale - 400;
					if(Shift >= j)	Shift = j;
					ShowStartTime();	//��ʾ������ʼʱ��
					ShowOscope();		//ֹͣ��ˢ�²���
				}
			}

			else if(KeyCode == K_DOWNN)	//�¼� ��ֱ���� -
			{
				if(B_Run)	//������
				{
					if(B_TrigMode)	//������, ���ڵ��� ����ģʽ ��ֱ����
					{
						if(B_KeyRepeat)		//�ؼ�ʱ�����ƶ�
						{
							if(pwm1_voltage <= 245)	pwm1_voltage += 5;
						}
						else if(pwm1_voltage < 250)	pwm1_voltage++;
						PWMA_CCR1L = pwm1_voltage;
						WriteDelay = 250;	//д����ʱ8��
					}
					else if(InputIndex < 7)	//������ֱ����
					{
						InputIndex++;
						ShowVoltage();
						WriteDelay = 250;	//д����ʱ8��
					}
				}
				else	//�����ƶ�����
				{
					if(!B_KeyRepeat)	{	if(Shift != 0)	Shift--;	}
					else if(Shift >= 10)	Shift -= 10;
					else					Shift = 0;
					TimeScale = T_TimeScale[Current_TimeBase%3][TimeScaleIndex];	//ʱ��ϵ������, 0-->10, 1-->5, 2-->2, 3-->1
					if(TimeScale == 3)	j = 8000/5 - 400;
					else				j = 4000/TimeScale - 400;
					if(Shift >= j)	Shift = j;
					ShowStartTime();	//��ʾ������ʼʱ��
					ShowOscope();		//ֹͣ��ˢ�²���
				}
			}
			KeyCode = 0;
		}
	}
}
/**********************************************/


/***************** ��ʾ������ʽ���� *****************************/
void ShowTrigMode(void)
{
	if(!B_TrigMode)	background = MAGENTA;	//���װ���
	else			background = BLUE;
	LCD_Fill_XY(430,48, 45, 18, background);	//�Զ� ��׼ ����
		 if(TrigMode == 1)	printf_text(430+4,48+3, " ��׼");
	else if(TrigMode == 2)	printf_text(430+4,48+3, " ����");
	else					printf_text(430+4,48+3, " �Զ�");
	LCD_Fill_XY(430,68, 45, 18, background);	//��ֱ
	printf_text(430+4,68+3, " ��ֱ");
	background = BLACK;
}

/***************** ��ʾ����״̬���� *****************************/
void	ShowRunStop(void)
{
	if(B_Run)
	{
		background = BLUE;	//���װ���
		LCD_Fill_XY(430, 8, 45, 18, BLUE);	//���� ֹͣ
		printf_text(430+4, 8+3, " ����");
	}
	else
	{
		background = RED;	//��װ���
		LCD_Fill_XY(430, 8, 45, 18, RED);	//���� ֹͣ
		printf_text(430+4, 8+3, " ֹͣ");
	}
	background = BLACK;
}


/***************** ֹͣ���к��� *****************************/
void	OscStop(void)
{
	CMPCR1 = 0x86;		// �رȽ����ж�
	TR0    = 0;			//�رղ�����ʱ��1
	B_ADC_Busy = 0;
	B_Run = 0;
	B_RUN_REQ = 0;
	ShowRunStop();
	Shift = 0;			//ֹͣ�������λ����
	ShowStartTime();	//��ʾ������ʼʱ��

	if(Current_TimeBase == 4)	//200us/DIV
	{
		Current_TimeBase = 5;
		TimeScaleIndex   = 1;
	}
	else if(Current_TimeBase == 3)	//100us/DIV
	{
		Current_TimeBase = 5;
		TimeScaleIndex   = 2;
	}
	else if(Current_TimeBase == 2)	//50us/DIV
	{
		Current_TimeBase = 5;
		TimeScaleIndex   = 3;
	}
}


          //�������� SampleIndex   0     1      2      3      4     5     6     7      8     9     10     11     12     13   14    15    16    17    18    19    20
          //����ʱ�䵥λ       0.1us 0.1us     us     us     us   10us  10us  10us   0.1ms 0.1ms  0.1ms   1ms   1ms    1ms  10ms  10ms  10ms  0.1s  0.1s  0.1s   1s 
u16 const   StartTimeTable[]= {   4,    8,     2,     4,     8,    2,     4,    8,    2,    4,     8,     2,     4,     8,    2,    4,    8,    2,    4,    8,   2};
          //����ʱ��/DIV        10us  20us   50us  100us  200us  500us   1ms   2ms    5ms  10ms   20ms   50ms  100ms  200ms  500ms   1s   2s    5s   10s   20s   50s

/***************** ��ʾ��ʼʱ�亯�� *****************************/
void ShowStartTime(void)
{
	u16	j;
	u8	i,k;
	
	j = StartTimeTable[SampleIndex] * Shift;
	tmp[0] = j / 10000 +'0';
	tmp[1] = (j % 10000)/ 1000 +'0';
	tmp[2] = (j % 1000)/100 +'0';
	tmp[3] = (j % 100)/10 +'0';
	tmp[4] = (j % 10) +'0';

	if(SampleIndex <= 1)	//��λΪ0.1us
	{
		tmp[5] = tmp[4];
		tmp[4] = '.';
		tmp[6] = 'u';
		tmp[7] = 's';
		k = 3;
	}
	else if(SampleIndex <= 4)	//��λΪus
	{
		tmp[5] = 'u';
		tmp[6] = 's';
		tmp[7] = ' ';
		k = 4;
	}
	else if(SampleIndex <= 7)	//��λΪ10us
	{
		tmp[5] = '0';
		tmp[6] = 'u';
		tmp[7] = 's';
		k = 5;
	}
	else if(SampleIndex <= 10)	//��λΪ0.1ms
	{
		tmp[5] = tmp[4];
		tmp[4] = '.';
		tmp[6] = 'm';
		tmp[7] = 's';
		k = 3;
	}
	else if(SampleIndex <= 13)	//��λΪ1ms
	{
		tmp[5] = 'm';
		tmp[6] = 's';
		tmp[7] = ' ';
		k = 4;
	}
	else if(SampleIndex <= 16)	//��λΪ10ms
	{
		tmp[5] = '0';
		tmp[6] = 'm';
		tmp[7] = 's';
		k = 5;
	}
	else if(SampleIndex <= 19)	//��λΪ0.1s
	{
		tmp[5] = tmp[4];
		tmp[4] = '.';
		tmp[6] = 's';
		tmp[7] = ' ';
		k = 3;
	}
	else	//��λΪ1s
	{
		tmp[5] = 's';
		tmp[6] = ' ';
		tmp[7] = ' ';
		k = 4;
	}
	for(i=0; i<k; i++)		//����Ч0
	{
		if(tmp[i] != '0')	break;
		tmp[i] = ' ';
	}
	tmp[8] = 0;

	printf_text(25,13, tmp);	//�ڵװ���
}



	#define	X_START		40
	#define	Y_START		25
	#define	GridColor	GREEN	//������ɫ
	#define	WaveColor	YELLOW	//������ɫ

/************** ��ʼ��ʾ�������� ********************/
void	OSCOPE_inilize(void)
{
	u16	y;
	SetView_V();		//����
	Rectangle(X_START-1, Y_START-1, 253, 403, WHITE);	//��������
	
	for(y=0; y<=400; y+=25)	Line_h(X_START-5,y+Y_START,4,WHITE);	//������ʱ��̶�

	SetView_H();		//����
	for(y=0; y<250; y+=25)
	{
		text_ascii5x7(y+Y_START-2, 320-(X_START-9), (u8)((y/25)%10));	//���¿̶ȸ�λ
	}
	for(y=250; y<=400; y+=25)
	{
		text_ascii5x7(y+Y_START-5,   320-(X_START-9), '1');				//���¿̶�ʮλ
		text_ascii5x7(y+Y_START+1,   320-(X_START-9), (u8)((y/25)%10));	//���¿̶ȸ�λ
	}
}



//	P_V_C = 0;	P_V_B = 1;	P_V_A = 1;	//��������ѡ��, CBA   000 001 010 011 100 101 110 111
										//				����   2   4   10  1   20 200  40 100
  //����InputIndex      0   1    2    3   4    5    6    7    8   9   10
			//����      1   2    4   10  20   40   100  200  200 200 200
			//ADC      /20 /20  /20  /20 /20  /20  /20  /20  /10  /4  /2
u8	const T_V_GAIN[14]={ 3,  0,   1,   2,  4,   6,   7,   5,   5,  5,  5};	//��ѹ����, adc/n, ���ȵ�λ, 0->0.25V/DIV, 1->0.5V/DIV, 2->1V/DIV, 3->2.5V/DIV, 4->5V/DIV
			//����     1V 500m 250m 100m 50m  25m  10m  5m  2.5m  1m 0.5m
			//����    10V  5V  2.5V  1V  500m 250m 100m 50m  25m 10m  5m

/************** ��ʾ���κ��� ( 50us< ���� <=20ms/DIV ��ֹͣ������ʱ��) ********************/
void	ShowOscope(void)
{
	u16	x,y,j;
	u8	i;

	if(TimeScale == 3)
	{
		j = 8000/5 - 400;	//������λ����
		if(Shift >= j)	Shift = j;
		for(j=(Shift*5)/2,x=0; x<400; x++)
		{
			i = adc_sample[j];	//��һ������
			if(i > 250)	i = 250;
			adc_tmp[x] = i;
			j = j + 2;
			x++;
			i = adc_sample[j];	//��һ������
			if(i > 250)	i = 250;
			adc_tmp[x] = i;
			j = j + 3;
		}
	}
	else
	{
		j = 4000/TimeScale - 400;	//������λ����
		if(Shift >= j)	Shift = j;
		for(j=Shift*TimeScale,x=0; x<400; x++)
		{
			i = adc_sample[j];	//��һ������
			if(i > 250)	i = 250;
			adc_tmp[x] = i;
			j = j + TimeScale;
		}
	}

	SetView_V();		//����
	LastDot = adc_tmp[0] + X_START;
	for(y=0; y<400; y++)
	{
		if(((y%25) == 0) || (y == 199) || (y == 201))	Line_Grid5(X_START, y+Y_START, GridColor);		//ÿ5����һ���̶�
		else if((y%5) == 0)		Line_Grid25(X_START, y+Y_START, GridColor);	//ÿ25����һ���̶�
		else					Line_h(X_START,y+Y_START,251, BLACK);	//���һ����
		
		x = adc_tmp[y] + X_START;
		if(x == LastDot)		WriteSingleDot(x, y+Y_START,  WaveColor);	//���������
		else if(x < LastDot)	Line_h(x,y+Y_START,LastDot-x, WaveColor);
		else 					Line_h(LastDot+1,y+Y_START,x-LastDot, WaveColor);
		LastDot = x;
	}
	Line_Grid5(X_START, 400+Y_START, GridColor);	//���һ�ſ̶�

	SetView_H();		//����
}


/************** ʵʱ��ʾ���κ���(>=50ms/DIV) ********************/
void	RealShowOscope(void)
{
	u16	x,y;
	u8	i;

	y = adc_rd/10;
	if(y >= 400)	return;	

	SetView_V();		//����
	if(((y%25) == 0) || (y == 199) || (y == 201))	Line_Grid5( X_START, y+Y_START, GridColor);	//ÿ5����һ���̶�
	else if((y%5) == 0)								Line_Grid25(X_START, y+Y_START, GridColor);	//ÿ25����һ���̶�
	else											Line_h(X_START,y+Y_START,251, BLACK);		//���һ����

	i = adc_sample[adc_rd];
	if(i > 250)	i = 250;	//�����ж�, �жϲ��ж�
	x = (u16)i + X_START;
	if(adc_rd == 0)			LastDot = x;	//�տ�ʼ�ĵ�һ����
	if(x == LastDot)		WriteSingleDot(x, y+Y_START,  WaveColor);	//���������
	else if(x < LastDot)	Line_h(x,y+Y_START,LastDot-x, WaveColor);
	else 					Line_h(LastDot+1,y+Y_START,x-LastDot, WaveColor);	//if(x > LastDot)
	LastDot = x;
	adc_rd += 10;
	SetView_H();		//����
}


/***************** ADC���ú��� *****************************/
#define ADC_START	(1<<6)	/* �Զ���0 */
#define ADC_FLAG	(1<<5)	/* �����0 */

#define	ADC_SPEED	0		/* 0~15, ADCʱ�� = SYSclk/2/(n+1) */
#define	RES_FMT		(0<<5)	/* ADC�����ʽ 0: �����, ADC_RES: D9 D8 D7 D6 D5 D4 D3 D2, ADC_RESL: D1 D0 0  0  0  0  0  0 */
							/*             1: �Ҷ���, ADC_RES: 0  0  0  0  0  0  D9 D8, ADC_RESL: D7 D6 D5 D4 D3 D2 D1 D0 */

#define CSSETUP		(0<<7)	/* 0~1,  ADCͨ��ѡ��ʱ��      0: 1��ADCʱ��, 1: 2��ADCʱ��,  Ĭ��0(Ĭ��1��ADCʱ��)	*/
#define CSHOLD		(0<<5)	/* 0~3,  ADCͨ��ѡ�񱣳�ʱ��  (n+1)��ADCʱ��, Ĭ��1(Ĭ��2��ADCʱ��)					*/
#define SMPDUTY		10		/* 10~31, ADCģ���źŲ���ʱ��  (n+1)��ADCʱ��, Ĭ��10(Ĭ��11��ADCʱ��)				*/
							/* ADCת��ʱ��: 10λADC�̶�Ϊ10��ADCʱ��, 12λADC�̶�Ϊ12��ADCʱ��. 				*/

void	ADC_config(void)
{
	P0n_pure_input(0x10);	//����Ҫ��ADC��IO����������
	ADC_CONTR = 0x80 + 12;	//ADC on + channel
	ADCCFG = RES_FMT + ADC_SPEED;
	P_SW2 |=  0x80;	//����XSFR
	ADCTIM = CSSETUP + CSHOLD + SMPDUTY;	//28 ADC CLOCK
}
//***********************************************************************************************

//========================================================================
// ����: void Timer4_Config(void)
// ����: timer3��ʼ������.
// ����: none.
// ����: none.
// �汾: V1.0, 2018-12-20
//========================================================================
void Timer4_Config(void)
{
	P_SW2 |= 0x80;		//SFR enable   
	T4T3M &= 0x0f;		//ֹͣ����, ��ʱģʽ, 12Tģʽ, �����ʱ��

	T4T3M |=  (1<<5);	//1T mode
	T4H = (u8)((65536UL - MAIN_Fosc/2000) /256);
	T4L = (u8)((65536UL - MAIN_Fosc/2000) %256);

	T3T4PIN = 0x00;		//ѡ��IO, 0x00: T3--P0.4, T3CLKO--P0.5, T4--P0.6, T4CLKO--P0.7;    0x01: T3--P0.0, T3CLKO--P0.1, T4--P0.2, T4CLKO--P0.3;
	T4T3M |=  (1<<4);	//�������ʱ��
	T4T3M |=  (1<<7);	//��ʼ����
}

/************************ �Ƚ������ú��� ****************************/
void	Compare_Config(void)	//�Ƚ�����ʼ��
{
	CMPCR1 = 0;
	CMPCR2 = 10;		//�ȽϽ���仯��ʱ������, 0~63
	CMPCR1 |= (1<<7);	//1: ����Ƚ���,     0:�رձȽ���
	CMPCR1 |= (0<<5);	//1: �����������ж�, 0: ��ֹ
	CMPCR1 |= (0<<4);	//1: �����½����ж�, 0: ��ֹ
	CMPCR1 |= (0<<3);	//����������ѡ��, 0: ѡ���ⲿP3.7��������,           1: ��ADC_CHS[3:0]��ѡ���ADC�������������.
	CMPCR1 |= (1<<2);	//���븺����ѡ��, 0: ѡ���ڲ�BandGap��ѹBGv��������, 1: ѡ���ⲿP3.6������
	CMPCR1 |= (1<<1);	//1: ����ȽϽ�������IO(P3.4��P4.1),  0: �ȽϽ����ֹ�����IO
	CMPCR2 |= (0<<7);	//1: �Ƚ���������IOȡ��, 0: ��ȡ��
	CMPCR2 |= (0<<6);	//0: �����ڲ�0.1uF�˲�,    1: �ر�

	CMPO_P34();				//��������P3.4.
//	CMPO_P41();				//��������P4.1.
	P3n_push_pull(Pin4);	//P3.4����Ϊ�������
	P3n_pure_input(0xc0);	//����Ҫ��ADC��IO����������(P3.7 P3.6)
	IP2  |= (1<<5);	//�Ƚ����ж����ȼ����
	IP2H |= (1<<5);

	CMPCR1 = 0x86;			// �رȽ����ж�
//	CMPCR1 = 0x86 + 0x20;	// �Ƚ����������ж�
//	CMPCR1 = 0x86 + 0x10;	// �Ƚ����½����ж�
}

/***************** �Ƚ����жϺ��� *****************************/
void CMP_ISR(void) interrupt CMP_VECTOR		//�Ƚ����жϺ���, ��⵽���綯�ƹ�0�¼�
{
	ADC_RES = 0;
//	ADC_RESL = 0;
	ADC_CONTR = 0x80 + ADC_START + 12;	//ADC on + channel
	TR0 = 1;		//��ʼ����Timer1.

	AutoTimeCnt = 0;	//��ͬ���ź�, ��ȡ����ʱ����
	adc_wr  = 0;
	adc_rd  = 0;

	CMPCR1 = 0x86;		// �رȽ����ж� ��������жϱ�־λ
}

/***************** ��ʱ��1��ʼ������ *****************************/
void	Timer1_config(void)
{
	TR1 = 0;	//ֹͣ����
	Timer1_1T();
	Timer1_16bit();
	Timer1_AsCounter();
	TH1 = 0;	TL1 = 0;
	Timer1_Gate_INT1_P33();
	Timer1_InterruptEnable();
	TR1 = 1;
}

//========================================================================
// ����: void timer1_ISR (void) interrupt TMR1_VECTOR
// ����:  timer1�жϺ���.
// ����: none.
// ����: none.
// �汾: V1.0, 2018-12-20
//========================================================================
void timer1_ISR (void) interrupt TMR1_VECTOR
{
	freq_H++;
}

/********************* INT0�жϺ��� *************************/
void INT1_ISR(void) interrupt INT1_VECTOR
{
	frequency = ((u32)freq_H << 16) + ((u32)TH1 << 8) + (u32)TL1;
	freq_H = 0;	TH1 = 0;	TL1 = 0;
	B_FrequencyOk = 1;
}


//========================================================================
// ����: void PWMA_config(void)
// ����: PWMA��ʼ������.
// ����: none.
// ����: none.
// �汾: V1.0, 2022-6-25
//========================================================================
void PWMA_config(void)
{
	u8	ccer1;
	u8	ccer2;
	u8	ps;
	u8	eno;
	u8	PWMA_ISR_En;

	P_SW2 |= 0x80;		//SFR enable   
	PWMA_ENO    = 0;	// IO�����ֹ
	PWMA_IER    = 0;	// ��ֹ�ж�
	PWMA_SR1    = 0;	// ���״̬
	PWMA_SR2    = 0;	// ���״̬
	ccer1 = 0;
	ccer2 = 0;
	ps    = 0;
	eno   = 0;
	PWMA_ISR_En = 0;

	PWMA_PSCRH = 0x00;		// Ԥ��Ƶ�Ĵ���, ��Ƶ Fck_cnt = Fck_psc/(PSCR[15:0}+1), ���ض���PWMƵ�� = SYSclk/((PSCR+1)*(AAR+1)), �������PWMƵ�� = SYSclk/((PSCR+1)*(AAR+1)*2).
	PWMA_PSCRL = 0x00;
	PWMA_DTR  = 24;			// ����ʱ������, n=0~127: DTR= n T,   0x80 ~(0x80+n), n=0~63: DTR=(64+n)*2T,  
							//				0xc0 ~(0xc0+n), n=0~31: DTR=(32+n)*8T,   0xE0 ~(0xE0+n), n=0~31: DTR=(32+n)*16T,
	PWMA_ARRH   = 256/256;	// �Զ���װ�ؼĴ���,  ����PWM����
	PWMA_ARRL   = 256%256;

	PWMA_CCMR1  = 0x68;		// ͨ��ģʽ����, PWMģʽ1, Ԥװ������
	PWMA_CCR1H  = 128/256;	// �Ƚ�ֵ, ����ռ�ձ�(�ߵ�ƽʱ����)
	PWMA_CCR1L  = 128%256;
	ccer1 |= 0x05;			// �����Ƚ����, �ߵ�ƽ��Ч
	ps    |= 0;				// ѡ��IO, 0:ѡ��P1.0 P1.1, 1:ѡ��P2.0 P2.1, 2:ѡ��P6.0 P6.1, 
	eno   |= 0x01;			// IO�������,  bit7: ENO4N, bit6: ENO4P, bit5: ENO3N, bit4: ENO3P,  bit3: ENO2N,  bit2: ENO2P,  bit1: ENO1N,  bit0: ENO1P
//	PWMA_ISR_En|= 0x02;		// ʹ���ж�

	PWMA_CCMR2  = 0x68;		// ͨ��ģʽ����, PWMģʽ1, Ԥװ������
	PWMA_CCR2H  = 128/256;	// �Ƚ�ֵ, ����ռ�ձ�(�ߵ�ƽʱ����)
	PWMA_CCR2L  = 128%256;
	ccer1 |= 0x50;			// �����Ƚ����, �ߵ�ƽ��Ч
	ps    |= (0<<2);		// ѡ��IO, 0:ѡ��P1.2 P1.3, 1:ѡ��P2.2 P2.3, 2:ѡ��P6.2 P6.3, 
	eno   |= 0x08;			// IO�������,  bit7: ENO4N, bit6: ENO4P, bit5: ENO3N, bit4: ENO3P,  bit3: ENO2N,  bit2: ENO2P,  bit1: ENO1N,  bit0: ENO1P
//	PWMA_ISR_En|= 0x04;		// ʹ���ж�

	PWMA_CCMR3  = 0x68;		// ͨ��ģʽ����, PWMģʽ1, Ԥװ������
	PWMA_CCR3H  = 128/256;	// �Ƚ�ֵ, ����ռ�ձ�(�ߵ�ƽʱ����)
	PWMA_CCR3L  = 128%256;
	ccer2 |= 0x05;			// �����Ƚ����, �ߵ�ƽ��Ч
	ps    |= (0<<4);		// ѡ��IO, 0:ѡ��P1.4 P1.5, 1:ѡ��P2.4 P2.5, 2:ѡ��P6.4 P6.5, 
	eno   |= 0x10;			// IO�������,  bit7: ENO4N, bit6: ENO4P, bit5: ENO3N, bit4: ENO3P,  bit3: ENO2N,  bit2: ENO2P,  bit1: ENO1N,  bit0: ENO1P
//	PWMA_ISR_En|= 0x08;		// ʹ���ж�

	PWMA_CCER1  = ccer1;	// ����/�Ƚ�ʹ�ܼĴ���1
	PWMA_CCER2  = ccer2;	// ����/�Ƚ�ʹ�ܼĴ���2
	PWMA_PS     = ps;		// ѡ��IO
	PWMA_IER    = PWMA_ISR_En;	//��������ͨ��1~4�жϴ���

	PWMA_BKR    = 0x80;		// �����ʹ�� �൱���ܿ���
	PWMA_CR1    = 0x81;		// ʹ�ܼ�����, �����Զ���װ�ؼĴ�������, ���ض���ģʽ, ���ϼ���,  bit7=1:д�Զ���װ�ؼĴ�������(�����ڲ��ᱻ����), =0:ֱ��д�Զ���װ�ؼĴ�����(���ڿ��ܻ��ҵ�)
	PWMA_EGR    = 0x01;		//����һ�θ����¼�, �����������Ԥ��Ƶ������, װ��Ԥ��Ƶ�Ĵ�����ֵ
	PWMA_ENO    = eno;		// ����IO���

	P1n_push_pull(0x19);	//P1.0 P1.3 P1.4 ����Ϊ�������
}
//	PWMA_PS   = (0<<6)+(0<<4)+(0<<2)+0;	//ѡ��IO, 4��Ӹߵ���(������)��ӦPWM1 PWM2 PWM3 PWM4, 0:ѡ��P1.x, 1:ѡ��P2.x, 2:ѡ��P6.x, 
//  PWMA_PS    PWM4N PWM4P    PWM3N PWM3P    PWM2N PWM2P    PWM1N PWM1P
//    00       P1.7  P1.6     P1.5  P1.4     P1.3  P5.4     P1.1  P1.0
//    01       P2.7  P2.6     P2.5  P2.4     P2.3  P2.2     P2.1  P2.0
//    02       P6.7  P6.6     P6.5  P6.4     P6.3  P6.2     P6.1  P6.0
//    03       P3.3  P3.4      --    --       --    --       --    --

//========================================================================
// ����: void PWMB_config(void)
// ����: PWMA��ʼ������.
// ����: none.
// ����: none.
// �汾: V1.0, 2022-6-25
//========================================================================
void PWMB_config(void)
{
	u8	ccer1;
	u8	ccer2;
	u8	ps;
	u8	eno;
	u8	PWMB_ISR_En;

	P_SW2 |= 0x80;		//SFR enable   
	PWMB_ENO    = 0;	// IO�����ֹ
	PWMB_IER    = 0;	// ��ֹ�ж�
	PWMB_SR1    = 0;	// ���״̬
	PWMB_SR2    = 0;	// ���״̬
	ccer1 = 0;
	ccer2 = 0;
	ps    = 0;
	eno   = 0;
	PWMB_ISR_En = 0;

	PWMB_PSCRH = (u8)((35000-1)/256);		// Ԥ��Ƶ�Ĵ���, ��Ƶ Fck_cnt = Fck_psc/(PSCR[15:0}+1), ���ض���PWMƵ�� = SYSclk/((PSCR+1)*(AAR+1)), �������PWMƵ�� = SYSclk/((PSCR+1)*(AAR+1)*2).
	PWMB_PSCRL = (u8)((35000-1)%256);
	PWMB_ARRH  = (u8)(1010/256);	// �Զ���װ�ؼĴ���,  ����PWM����
	PWMB_ARRL  = (u8)(1010%256);

	PWMB_CCMR3  = 0x68;		// ͨ��ģʽ����, PWMģʽ1, Ԥװ������
	PWMB_CCR3H  = (u8)(1000/256);	// �Ƚ�ֵ, ����ռ�ձ�(�ߵ�ƽʱ����)
	PWMB_CCR3L  = (u8)(1000%256);
	ccer2 |= 0x05;			// �����Ƚ����, �ߵ�ƽ��Ч
	ps    |= (1<<4);		// ѡ��IO, 0:ѡ��P2.2, 1:ѡ��P3.3, 2:ѡ��P0.2, 3:ѡ��P7.6, 
	eno   |= 0x10;			// IO�������,  bit6: ENO8P, bit4: ENO7P,  bit2: ENO6P,  bit0: ENO5P
//	PWMB_ISR_En|= 0x08;		// ʹ���ж�

	PWMB_CCER1  = ccer1;	// ����/�Ƚ�ʹ�ܼĴ���1
	PWMB_CCER2  = ccer2;	// ����/�Ƚ�ʹ�ܼĴ���2
	PWMB_PS     = ps;		// ѡ��IO
	PWMB_IER    = PWMB_ISR_En;	//��������ͨ��1~4�жϴ���

	PWMB_BKR    = 0x80;		// �����ʹ�� �൱���ܿ���
	PWMB_CR1    = 0x81;		// ʹ�ܼ�����, �����Զ���װ�ؼĴ�������, ���ض���ģʽ, ���ϼ���,  bit7=1:д�Զ���װ�ؼĴ�������(�����ڲ��ᱻ����), =0:ֱ��д�Զ���װ�ؼĴ�����(���ڿ��ܻ��ҵ�)
	PWMB_EGR    = 0x01;		//����һ�θ����¼�, �����������Ԥ��Ƶ������, װ��Ԥ��Ƶ�Ĵ�����ֵ
	PWMB_ENO    = eno;		// ����IO���
	P3n_push_pull(1<<3);	//P3.3����Ϊ�������
}
//	PWMB_PS   = (0<<6)+(0<<4)+(0<<2)+0;	//ѡ��IO, 4��Ӹߵ���(������)��ӦPWM8 PWM7 PWM6 PWM5
//  PWMB_PS    PWM8    PWM7    PWM6    PWM5
//    00       P2.3    P2.2    P2.1    P2.0
//    01       P3.4    P3.3    P5.4    P1.7
//    02       P0.3    P0.2    P0.1    P0.0
//    03       P7.7    P7.6    P7.5    P7.4


//========================================================================
// ����:void	Timer0_config(void)
// ����: timer0��ʼ������.
// ����: noe.
// ����: none.
// �汾: V1.0, 2018-12-20
//========================================================================
void	Timer0_config(void)
{
	TR0 = 0;	//ֹͣ����
	ET0 = 1;	//�����ж�
	PT0 = 1;	//�����ȼ��ж�
	TMOD &= ~0x03;
//	TMOD |= 0;	//����ģʽ, 0: 16λ�Զ���װ, 1: 16λ��ʱ/����, 2: 8λ�Զ���װ
	Timer0_1T();	//1T mode
//	TR0 = 1;	//��ʼ����
}

//========================================================================
void timer0_ISR (void) interrupt TMR0_VECTOR
{
	adc = ~ADC_RES;
	ADC_RES = 0;
//	ADC_RESL = 0;
	ADC_CONTR = 0x80 + ADC_START + 12;	//ADC on + channel

	if(!B_sample_ms)	//  <=20ms/DIV, ������һ������ʾ
	{
		adc_sample[adc_wr] = adc;
		if(++adc_wr >= 4000)	B_Sample_OK = 1, TR0 = 0;
	}

	else if(--sample_cnt == 0)	// >=50ms/DIV ʵʱɨ����ʾ����
	{
		sample_cnt = SampleTime;
		adc_sample[adc_wr] = adc;
		if((adc_wr%10) == 0)	B_Sample_OK = 1;
		if(++adc_wr >= 4000)	B_Sample_OK = 1, TR0 = 0;
	}
}

//================= ������ʱ���� ========================
void	AutoCheck(void)
{
	if(AutoTimeCnt != 0)		//8ms call
	{
		if(--AutoTimeCnt == 0)	//ͬ��������ʱ, ��ǿ������
		{
			ADC_RES = 0;
			ADC_RESL = 0;
			ADC_CONTR = 0x80 + ADC_START + 12;	//ADC on + channel
			TR0 = 1;		//��ʼ����Timer1.

			CMPCR1 = 0x86;		// �رȽ����ж�
			adc_wr  = 0;
			adc_rd  = 0;
		}
	}
}




#define	D_MAIN_CLOCK	35

          //�������� SampleIndex   0     1      2      3      4     5      6     7      8     9     10     11     12     13     14   15   16    17    18    19    20
          //����ʱ�䵥λ          us    us     us     us     us    us     us    us     us    us     us     ms     ms     ms     ms   ms   ms    ms    ms    ms    ms 
u16	const   SampleTimeTable[]={   2,    2,     2,     2,     2,     2,    4,    8,    20,   40,    80,   200,   400,   800,     2,   4,    8,   20,   40,   80,  200};
          //����ʱ��/DIV        10us  20us   50us  100us  200us  500us   1ms   2ms    5ms  10ms   20ms   50ms  100ms  200ms  500ms   1s   2s    5s   10s   20s   50s
u16	const   T_Time_div[]=     {  10,   20,    50,   100,   200,   500,    1,    2,     5,   10,    20,    50,   100,   200,   500,   1,    2,    5,   10,   20,   50};

/***************** ���ò���ʱ�亯�� *****************************/
void	SetSampleTime(void)
{
	u16	j;

		 if(SampleIndex <= 5)	ADCCFG = RES_FMT + 0;	// ADC CLOCK = 20MHz @2us/sample,  ADC CLOCK = SYSclk/2/(n+1), ת����Ҫ 28 ADC CLOCK
	else if(SampleIndex == 6)	ADCCFG = RES_FMT + 1;	// ADC CLOCK = 10MHz @4us/sample,  ADC CLOCK = SYSclk/2/(n+1)
	else if(SampleIndex == 7)	ADCCFG = RES_FMT + 3;	// ADC CLOCK =  5MHz @8us/sample,  ADC CLOCK = SYSclk/2/(n+1)
	else 						ADCCFG = RES_FMT + 9;	// ADC CLOCK =  2MHz >=20us/sample, ADC CLOCK = SYSclk/2/(n+1)

		 if(SampleIndex <= 8)	AutoTime = 100/8;	//ͬ����ʱ100ms	   <=5ms/div		<=60ms/frme
	else if(SampleIndex == 9)	AutoTime = 200/8;	//ͬ����ʱ200ms	   10ms/div			==120ms/frme
	else if(SampleIndex == 10)	AutoTime = 400/8;	//ͬ����ʱ500ms	   20ms/div			==240ms/frme
	else if(SampleIndex == 11)	AutoTime = 800/8;	//ͬ����ʱ800ms	   50ms/div			==600ms/frme
	else if(SampleIndex == 12)	AutoTime = 1600/8;	//ͬ����ʱ800ms	   100ms/div		==600ms/frme
	else 						AutoTime = 2000/8;	//ͬ����ʱ1200ms   >=200ms/div		>=1200ms/frme

	if(TrigMode == 0)	AutoTimeCnt = AutoTime;	//�Զ�ģʽ

	if(SampleIndex <= 10)	//50us 100us 200us/DIV����2us����, 500us~20ms/DIVʹ��10������
	{
		j = SampleTimeTable[SampleIndex];
		TR0 = 0;	//ֹͣ����
		B_sample_ms = 0;
		TH0 = (u8)((65536UL - j*D_MAIN_CLOCK) / 256);
		TL0 = (u8)((65536UL - j*D_MAIN_CLOCK) % 256);
	}
	
	else if(SampleIndex <= 13)	// 50ms 100ms 200ms/DIVʹ��10������
	{
		j = SampleTimeTable[SampleIndex];
		TR0 = 0;	//ֹͣ����
		SampleTime  = 1;	//������һ���жϲ���һ��
		sample_cnt  = 1;
		B_sample_ms = 1;	//ʵʱɨ����ʾ
		TH0 = (u8)((65536UL - j*D_MAIN_CLOCK) / 256);
		TL0 = (u8)((65536UL - j*D_MAIN_CLOCK) % 256);
	}

	else 		// >=500ms/DIV, ʵʱɨ��, ��ʱ���жϹ̶�Ϊ1ms
	{
		j = SampleTimeTable[SampleIndex];
		TR0 = 0;	//ֹͣ����
		SampleTime  = j;	//һ���������Ӧ���жϴ���
		sample_cnt  = j;
		B_sample_ms = 1;	//ʵʱɨ����ʾ
		TH0 = (u8)((65536UL - 1000*D_MAIN_CLOCK) / 256);	//1ms�ж�
		TL0 = (u8)((65536UL - 1000*D_MAIN_CLOCK) % 256);
	}
	ShowTimeBase();	//��ʾʱ��
}

/***************** ��ʾʱ������ *****************************/
void	ShowTimeBase(void)
{
	u16	j;
	u8	k;
	j = T_Time_div[SampleIndex];
	tmp[0] = j / 100 +'0';	j = j % 100;
	tmp[1] = j / 10 +'0';
	tmp[2] = j % 10 +'0';
	tmp[4] = 's';
	if(tmp[0] == '0')
	{
		tmp[0] = ' ';
		if(tmp[1] == '0')	tmp[1] = ' ';
	}
		 if(SampleIndex <= 5)	tmp[3] = 'u';	//us
	else if(SampleIndex <= 14)	tmp[3] = 'm';	//500ms����
	else						tmp[3] = ' ';	//1s����
	
	background = MAGENTA;	//���װ���
	for(k=0; k<5; k++)	text_ascii5x7(130+5+k*6,8+7, tmp[k]);
	background = BLACK;
}


	//InputIndex     0   1    2    3     4    5      6    7
	//InputIndex+3                 3     4    5      6    7      8    9  10   11   12   13
	// V/DIV        10V  5V  2.5V  1V  500mV 250mV 100mV 50mV
u8 const *T_VOLTAGE10[]={
" 10V ", "  5V ", "2.5V ", "  1V ", "500mV", "250mV", "100mV", " 50mV"};

/***************** ��ʾ��ֱ��ѹ��λ V/DIV ���� *****************************/
void	ShowVoltage(void)
{
	u8	i;
	background = MAGENTA;	//���װ���
	printf_text(185, 13, T_VOLTAGE10[InputIndex]);		//
	background = BLACK;

	i = T_V_GAIN[InputIndex];
	if(i & 0x04)	P_V_C = 1;	else P_V_C = 0;
	if(i & 0x02)	P_V_B = 1;	else P_V_B = 0;
	if(i & 0x01)	P_V_A = 1;	else P_V_A = 0;
}

/***************** ��ʾ����ģʽ���� *****************************/
void	ShowPhase(void)
{
	background = MAGENTA;	//���װ���
	if(B_TrigPhase)	printf_text(430+4,28+3, "������");	//0xfd����, ���ֲ��ܳ���, ͨ��Ϊ��
	else			printf_text(430+4,28+3, "�½���");
	background = BLACK;
}


/***************** �������� *****************************/
void	ReadKey(void)
{
	u8	i,j;
	P_K_OK = 1;
	i = KeyState;
	KeyState = 0;
	if(!P_K_UP)		KeyState |= 0x01;
	if(!P_K_DOWN)	KeyState |= 0x02;
	if(!P_K_LEFT)	KeyState |= 0x04;
	if(!P_K_RIGHT)	KeyState |= 0x08;
	if(!P_K_OK)		KeyState |= 0x10;

	if(KeyState == 0)		//�޼�����
	{
		P_K_DOWN = 0;
		for(j=0; j<5; j++)	{	NOP(2);	}	//��ʱһ��, ѭ����һ��Ҫ�д���, �����Ż���
		if(!P_K_UP)		KeyState |= 0x40;	//��ֱλ��
		if(!P_K_RIGHT)	KeyState |= 0x80;	//������ƽ
		P_K_DOWN = 1;
	}
	
	j = (i ^ KeyState) & KeyState;	//���¼��

	if((KeyState & 0x0f) != 0)		//�ؼ����, �������Ҽ�֧���ؼ�
	{
		if(++KeyHoldCnt >= 36)
		{
			KeyHoldCnt = 33;	//4*32=128ms, 1��8��
			j = KeyState;
			B_KeyRepeat = 1;
		}
	}

	if(j != 0)
	{
		if(j & 0x01)	KeyCode = K_UP;
		if(j & 0x02)	KeyCode = K_DOWNN;
		if(j & 0x04)	KeyCode = K_LEFT;
		if(j & 0x08)	KeyCode = K_RIGHT;
		if(j & 0x10)	KeyCode = K_OK;
		if(j & 0x40)	KeyCode = K_RUN_STOP;
		if(j & 0x80)	KeyCode = K_TRIGGER;
	}
	
	if(KeyState == 0)	KeyHoldCnt = 0,	B_KeyRepeat = 0;
}



//========================================================================
// ����: u8	Timer3_Config(u8 t, u32 reload)
// ����: timer3��ʼ������.
// ����:      t: ��װֵ����, 0��ʾ��װ����ϵͳʱ����, ����ֵ��ʾ��װ����ʱ��(us).
//       reload: ��װֵ.
// ����: 0: ��ʼ����ȷ,  1: ��װֵ����, ��ʼ������.
// �汾: V1.0, 2018-12-20
//========================================================================
u8	Timer3_Config(u8 t, u32 reload)	//t=0: reloadֵ����ʱ��������,  t=1: reloadֵ��ʱ��(��λus)
{
	P_SW2 |= 0x80;		//SFR enable   
	T4T3M &= 0xf0;		//ֹͣ����, ��ʱģʽ, 12Tģʽ, �����ʱ��

	if(t != 0)	reload = (u32)(((float)MAIN_Fosc * (float)reload)/1000000UL);	//��װ����ʱ��(us), ��������Ҫ��ϵͳʱ����.
	if(reload >= (65536UL * 12))	return 1;	//ֵ����, ���ش���
	if(reload < 65536UL)	T4T3M |=  (1<<1);	//1T mode
	else	reload = reload / 12;	//12T mode
	reload = 65536UL - reload;
	T3H = (u8)(reload >> 8);
	T3L = (u8)(reload);

//	T3T4PIN = 0x01;		//ѡ��IO, 0x00: T3--P0.4, T3CLKO--P0.5, T4--P0.6, T4CLKO--P0.7;    0x01: T3--P0.0, T3CLKO--P0.1, T4--P0.2, T4CLKO--P0.3;
	IE2   |=  (1<<5);	//�����ж�
	T4T3M |=  (1<<3);	//��ʼ����
	return 0;
}

#include	"SineTable.h"
u8	SineIndex;
//========================================================================
// ����: void Timer3_ISR(void) interrupt TMR3_VECTOR
// ����:  timer3�жϺ���.
// ����: none.
// ����: none.
// �汾: V1.0, 2018-12-20
//========================================================================
void Timer3_ISR(void) interrupt TMR3_VECTOR
{
	PWMA_CCR2L = T_SIN[SineIndex];		//P1.3���100Hz���Ҳ�
	if(++SineIndex == 50)	SineIndex = 0;

	if(++cnt_8ms == (8*5))
	{
		cnt_8ms = 0;
		B_8ms = 1;
	}
	if(++cnt_32ms == (32*5))
	{
		cnt_32ms = 0;
		B_32ms = 1;
	}
}


