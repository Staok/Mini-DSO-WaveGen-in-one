
/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC 1T Series MCU Demo Programme -------------------------------*/
/* --- Tel: 86-0513-55012928,55012929 ---------------------------------*/
/* --- Web: www.STCMCUDATA.com  ---------------------------------------*/
/* --- QQ:  800003751 -------------------------------------------------*/
/* 如果要在程序中使用此代码,请在程序中注明使用了STC的资料及程序        */
/* 本例程为复杂应用程序, 已测试通过, 用户自行理解领悟, 不提供技术支持  */
/*---------------------------------------------------------------------*/

/*************	功能说明	**************

本例程基于STC32G为主控芯片进行编写测试。

使用Keil C251编译器，Memory Model推荐设置XSmall模式，默认定义变量在edata，单时钟存取访问速度快。

简单示波器程序。

工程文件:
EEPROM.c
TFT480x320-V2.c
OSCOPE-V2-8bit.c	8bit采样


	STC 32位8051全球大学计划
	屠龙刀-STC32G12K128开源示波器专案
	2组CAN，USB，32位8051，
	STC32G12K128，高精准12位ADC，
	DMA支持（TFT彩屏，ADC，4组串口，SPI，I2C）
	STC32G12K128购买途径：
	0513-55012928，55012929
	官网：www.STCMCUDATA.com

示波器参数:
工作电压: 5.0V。
MCU:      STC32G12K128，使用屠龙刀核心板配合。
主频:     35MHz。
ADC:      最高采样800KHz 12位，本示波器使用最高采样率500KHz。
模拟带宽: 探头x1大于等于250mV/DIV，探头x10大于等于2.5V/DIV：100KHz。
显示屏:   3.2寸TFT LCD 480x320，16位数据口。
          水平16格，一格25点，一共400点，存储深度4000点。
          垂直10格，每格25点，一共250点。
时基:     1-2-5步进，50us 100us 200us 500us 1ms 2ms 5ms 10ms 20ms 50ms
                     100ms 200ms 500ms 1s 2s 5s 10s 20s 50s
垂直幅度: 探头x1:   50mV  100mV  250mV  500mV   1V  2.5V   5V  10V/DIV。
          探头x10: 500mV     1V   2.5V     5V  10V   25V  50V  100V/DIV。
最高输入电压: 探头x1： +-50V，探头x10：+-500V。
触发模式: 上升沿触发，下降沿触发。
触发方式: 自动、标准、单次。

******************************************/


#include	"config.h"
#include	"TFT480x320.h"
#include	"EEPROM.h"

/*************	本地常量声明	**************/
#define		K_UP		1
#define		K_DOWNN		2
#define		K_LEFT		3
#define		K_RIGHT		4
#define		K_OK		5
#define		K_RUN_STOP 	6
#define		K_TRIGGER	7

#define		EE_ADDR		0x000000


/*************	IO口声明	**************/
sbit	P_K_UP    = P7^4;
sbit	P_K_DOWN  = P7^3;
sbit	P_K_LEFT  = P7^2;
sbit	P_K_RIGHT = P7^1;
sbit	P_K_OK    = P7^0;

sbit	P_V_A    = P0^6;	//输入增益选择
sbit	P_V_B    = P0^5;	//输入增益选择, CBA   000 001 010 011 100 101 110 111
sbit	P_V_C    = P5^3;	//输入增益选择, 倍数   2   4   10  1   20 200  40 100  
//P0.7--T4CLKO: 1000Hz方波输出
//P0.4--ADC12: 波形输入
//P1.0-_PWM1P: 垂直位移PWM
//P1.4-_PWM3P: 负电压50% PWM
//P3.3--PWM7_2: H1S_L10ms测频闸门信号, 同时也是Timer1对外计数测频门控信号.
//P3.4--CMPO, 比较器输出端
//P3.5--T1,   Timer1对外计数测频输入端, 连接P3.4--CMPO
//P3.6--CMP-: 比较器用于同步检测
//P3.7--CMP+: 

	

/*************	本地变量声明	**************/
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
u8	TimeScale;		//时基系数, 10: 10取1, 5: 5取1, 2: 2取1, 1: 1取1
u8	TimeScaleIndex;	//时基系数索引, 0-->10, 1-->5, 2-->2, 3-->1
bit	B_RUN_REQ;		//请求停止

bit	B_TrigPhase;	//默认上升沿触发
bit	B_TrigMode;
u8	TrigMode;

u8	InputIndex;		//幅度档位
u8	AutoTimeCnt;
u8	AutoTime;
u8	pwm1_voltage;

bit	B_FrequencyOk;
u32	frequency;
u8	freq_H;

bit	B_Shift;	//移位标志, 停止时切换时基或移位
u16	Shift;		//移位点数
u8	Current_TimeBase;
u8	WriteDelay;	//写入延时

u8	cnt_8ms, cnt_32ms;
bit	B_8ms, B_32ms;


/*************	本地函数声明	**************/
void	OSCOPE_inilize(void);
void	ShowOscope(void);
void	RealShowOscope(void);
void	Timer0_config(void);
void	Timer1_config(void);
u8		Timer3_Config(u8 t, u32 reload);	//t=0: reload值是主时钟周期数,  t=1: reload值是时间(单位us), 返回0正确, 返回1装载值过大错误.
void	Timer4_Config(void);
void	SetSampleTime(void);
void	ShowVoltage(void);

void	ShowTimeBase(void);	//显示时基
void	ShowPhase(void);
void	ShowRunStop(void);	//显示运行状态
void	ShowStartTime(void);

void	ADC_config(void);
void	Compare_Config(void);	//比较器初始化
void	PWMA_config(void);
void	PWMB_config(void);
void	ReadKey(void);
void	AutoCheck(void);
void 	ShowTrigMode(void);
void	ShowRunStop(void);
void	OscStop(void);


/****************  外部函数声明和外部变量声明 *****************/

/**************************************************************/

//采样索引 SampleIndex   0     1      2      3      4     5      6     7      8     9     10     11     12     13     14   15   16    17    18    19    20
//采样时间/DIV         10us  20us   50us  100us  200us  500us   1ms   2ms    5ms  10ms   20ms   50ms  100ms  200ms  500ms  1s   2s    5s   10s   20s   50s
//第一维3, 是(SampleIndex % 3)的余数, 第二维是缩放系数, 数字为每N个点取一点, 但数字三是指2.5点取一点, 折中方案是每5点取0 2两点.
u8	const 	T_TimeScale[3][4]={	{10,5,2,1},
								{10,5,3,1},
								{10,4,2,1}};



/****************  主函数 *****************/
void	main(void)
{
	u8	i;
	u16	j;

	WTST = 0;
	CKCON = 0;

	P0M1 = 0;	P0M0 = 0;	//设置为准双向口
	P1M1 = 0;	P1M0 = 0;	//设置为准双向口
	P2M1 = 0;	P2M0 = 0;	//设置为准双向口
	P3M1 = 0;	P3M0 = 0;	//设置为准双向口
	P4M1 = 0;	P4M0 = 0;	//设置为准双向口
	P5M1 = 0;	P5M0 = 0;	//设置为准双向口
	P6M1 = 0;	P6M0 = 0;	//设置为准双向口
	P7M1 = 0;	P7M0 = 0;	//设置为准双向口
	
	P_SW2 = 0x80;
/*
	XOSCCR = 0xc0;			//启动外部晶振
	while (!(XOSCCR & 1));	//等待时钟稳定
	CLKDIV = 0x00;			//时钟不分频
	CLKSEL = 0x01;			//选择外部晶振
*/	
	P0n_push_pull(0x80);	//P0.7 T4CLKO 1000Hz

	P_K_UP    = 1;
	P_K_DOWN  = 1;
	P_K_LEFT  = 1;
	P_K_RIGHT = 1;
	P_K_OK    = 1;
	P33 = 1;	P35 = 1;	//	P3.3--PWM7_2: H1S_L10ms测频闸门信号

	ADC_config();		//ADC初始化
	Compare_Config();	//模拟比较器初始化
	Timer0_config();	//Timer0初始化, 频率计
	Timer1_config();	//Timer1初始化, 采样
	Timer3_Config(0, MAIN_Fosc / 5000);	//t=0: reload值是主时钟周期数,  (中断频率, 20000次/秒)
	Timer4_Config();	//Timer4初始化, 输出1000Hz方波.
	PWMA_config();		//PWM控制垂直位移、触发电平
	PWMB_config();		//产生 H1S_L10ms闸门信号用于测频
	EA = 1;
	
	EX1 = 1;	//允许中断
	IT1 = 1;	//下降沿中断

	WriteDelay = 0;
	EEPROM_read_n(EE_ADDR, tmp, 6);
	if(tmp[4] == (tmp[0]+tmp[1]+tmp[2]+tmp[3]) ^ 0x55)	//校验
	{
		pwm1_voltage = tmp[0];
		SampleIndex = tmp[1];	InputIndex = tmp[2];	TrigMode = tmp[3];
		if(TrigMode & 0x80)	B_TrigPhase = 1;
		else				B_TrigPhase = 0;
		TrigMode &= 0x03;
		if(pwm1_voltage > 250)	pwm1_voltage = 128;	//默认中点
		if(SampleIndex > 20)	SampleIndex  = 6;	//默认1ms/div
		if(SampleIndex < 2)		SampleIndex  = 6;	//默认1ms/div
		if(InputIndex >= 8)		InputIndex   = 3;	//默认1V/div
		if(TrigMode >= 3)		TrigMode     = 0;	//默认自动触发
		WriteDelay = 0;		//写入延时
	}
	else	//校验没通过
	{
		B_TrigPhase = 0;	//默认上升沿触发
		pwm1_voltage = 128;	//默认中点
		SampleIndex  = 6;	//默认1ms/div
		InputIndex   = 3;	//默认1V/div
		TrigMode     = 0;	//默认自动触发
		WriteDelay   = 250;	//写入延时
	}
	PWMA_CCR1L = pwm1_voltage;
	
	background = BLACK;
	foreground = WHITE;

	LCD_Init();		//LCD初始化

	SetView_H();		//横屏
	LCM_Config();	//LCM初始化
	DMA_Config();	//LCM_DMA初始化, 使用DMA方式显示下面的字符串.
	DMA_printf_text16(80,  0+40,"   STC 32位8051全球大学计划");
	DMA_printf_text16(80, 20+40,"屠龙刀-STC32G12K128开源示波器专案");
	DMA_printf_text16(80, 40+60,"2组CAN, USB, 32位8051");
	DMA_printf_text16(80, 60+60,"STC32G12K128, 高精准12位ADC");
	DMA_printf_text16(80, 80+60,"DMA支持(TFT彩屏, ADC, 4组串口, SPI, I2C)");
	DMA_printf_text16(80,100+80,"STC32G12K128购买途径:");
	DMA_printf_text16(80,120+80,"0513-55012928, 55012929");
	DMA_printf_text16(80,140+80,"官网: www.STCMCUDATA.com");
	DMA_printf_text16(80,180+90,"Please press any key to continue!");
	LCMIFCR   = 0x00;	//禁止LCM接口

	KeyCode = 0;
	while(KeyCode == 0)	//等待任意键
	{
		if(B_32ms)
		{
			B_32ms = 0;
			ReadKey();
		}
	}
	KeyCode = 0;
	LCD_Fill_XY(0,0,480,320,BLACK);

	background = MAGENTA;	//洋红底白字
//	LCD_Fill_XY(430, 8, 45, 18, MAGENTA);	//运行 停止
	LCD_Fill_XY(430,28, 45, 18, MAGENTA);	//上升沿 下降沿
//	LCD_Fill_XY(430,48, 45, 18, MAGENTA);	//自动 标准 单次
//	LCD_Fill_XY(430,68, 45, 18, MAGENTA);	//垂直
//	printf_text(430+4, 8+3, " 运行");
	printf_text(430+4,28+3, "上生沿");	//0xfd问题, 升字不能出现, 通假为生
//	printf_text(430+4,48+3, " 自动");
//	printf_text(430+4,68+3, " 垂直");

	LCD_Fill_XY(130, 11, 40, 15, MAGENTA);	//时基, 洋红底白字
	LCD_Fill_XY(180, 11, 40, 15, MAGENTA);	//幅度, 洋红底白字
	LCD_Fill_XY(230, 11, 70, 15, MAGENTA);	//频率, 洋红底白字

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
			AutoCheck();	// 触发超时处理
		}

		if(B_32ms)
		{
			B_32ms = 0;
			ReadKey();
			if(WriteDelay != 0)		//延时写入
			{
				if(--WriteDelay == 0)
				{
					tmp[0] = pwm1_voltage;
					tmp[1] = SampleIndex;
					tmp[2] = InputIndex;
					tmp[3] = TrigMode;
					if(B_TrigPhase)	tmp[3] |= 0x80;
					tmp[4] = (tmp[0]+tmp[1]+tmp[2]+tmp[3]) ^ 0x55;	//校验
					EEPROM_SectorErase(EE_ADDR);
					EEPROM_write_n(EE_ADDR,tmp,6);
				}
			}
		}
				
		if(B_Run)
		{
			if(!B_ADC_Busy)		//启动一次采样序列
			{
				B_Sample_OK = 0;
				adc_wr = 0;
				adc_rd = 0;
					 if(SampleIndex <= 2)	TimeScale = 1,	TimeScaleIndex = 3;	// 50us/DIV		逐点取	停止时2点间内插9点变10倍采样
				else if(SampleIndex == 3)	TimeScale = 2,	TimeScaleIndex = 2;	// 100us/DIV	2取1	停止时2点间内插4点变5倍采样
				else if(SampleIndex == 4)	TimeScale = 4,	TimeScaleIndex = 1;	// 200us/DIV	4取1	停止时2点间内插2.5点变2.5倍采样
				else 						TimeScale = 10,	TimeScaleIndex = 0;	// >=500us/DIV	10取1
				Current_TimeBase = SampleIndex;
				B_ADC_Busy = 1;
				SetSampleTime();	//设置采样时间
				if(B_TrigPhase)	CMPCR1 = 0x86 + 0x10;	// 比较器上升沿中断触发, 反相了
				else			CMPCR1 = 0x86 + 0x20;	// 比较器下降沿中断触发, 反相了
			}
			else if(SampleIndex <= 10)	// <=20ms/DIV
			{
				if(B_Sample_OK)		//采样完成
				{
					B_Sample_OK = 0;
					B_ADC_Busy  = 0;
					ShowOscope();	//显示波形
					if(B_RUN_REQ || (TrigMode == 2))	OscStop();	//请求停止 或 单次模式 则停止运行
				}
			}

			else if(B_Sample_OK)	//50ms/DIV以上采样, 实时刷新
			{
				B_Sample_OK = 0;
				RealShowOscope();	//实时显示波形
				if(adc_rd >= 4000)	//结束
				{
					B_ADC_Busy = 0;
					if(B_RUN_REQ || (TrigMode == 2))	OscStop();	//请求停止 或 单次模式 停止运行
				}
			}
		}
		else	B_ADC_Busy = 0;

		if(B_FrequencyOk)	//频率已OK
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
				background = MAGENTA;	//洋红底白字
				for(i=0; i<10; i++)	text_ascii5x7(230+5+i*6,8+7, tmp[i]);
				background = BLACK;
			}
		}

		if(KeyCode)	//有键按下
		{
			if(KeyCode == K_RUN_STOP)		//运行/停止
			{
				if(!B_Run)			//已停止则启动
				{
					if(InputIndex >= 8)	InputIndex = 7;
					ShowVoltage();
					B_Run = 1;		//启动运行
					B_RUN_REQ = 0;
					ShowRunStop();
					printf_text(25,13, "        ");	//起点时间清除
					printf_text(350, 13, "    ");		//取消显示红色移动
					B_Shift = 0;
					Shift  = 0;
				}
				else	//运行中
				{
					if(TrigMode != 0)			OscStop();	//标准模式 单次模式, 则直接停止
					else if(SampleIndex >= 11)	OscStop();	//扫描模式, 则直接停止
					else	B_RUN_REQ = 1;	//运行中, 无停止请求, 则请求停止
				}
			}

			else if(KeyCode == K_TRIGGER)	//触发模式 垂直调整, 只在运行时可以调整
			{
				B_TrigMode = ~B_TrigMode;	//切换调整 触发模式 垂直调整
				ShowTrigMode();
			}
			
			else if(KeyCode == K_OK)	//五向键的中间OK键, 运行时切换上升沿 下降沿触发, 停止时切换时基或移动波形
			{
				if(B_Run)	//运行中, 则切换上升下降沿
				{
					B_TrigPhase = ~B_TrigPhase;
					ShowPhase();
					B_ADC_Busy = 0;		//切换触发模式重新启动采样(如果没有停止的话)
					WriteDelay = 250;	//写入延时8秒
				}
			}

			else if(KeyCode == K_LEFT)		//左键 时基+
			{
				if(B_TrigMode)	//运行中, 处于调整 触发模式 垂直调整
				{
					if(--TrigMode >= 3)		TrigMode = 2;
					ShowTrigMode();
					B_ADC_Busy = 0;		//切换触发模式重新启动采样(如果没有停止的话)
					WriteDelay = 250;	//写入延时8秒
				}
				else if(SampleIndex < 20)
				{
					if(B_Run)	//运行中改变时基, 则仅仅改变采样率
					{
						SampleIndex++;
						B_ADC_Busy = 0;
						WriteDelay = 250;	//写入延时8秒
					}
					else if(TimeScaleIndex != 0)	//停止时缩放时基并刷新波形
					{
						SampleIndex++;
						TimeScaleIndex--;	//停止时缩放
						Shift = Shift * TimeScale;
						TimeScale = T_TimeScale[Current_TimeBase%3][TimeScaleIndex];	//时基系数索引, 0-->10, 1-->5, 2-->2, 3-->1
						Shift = Shift / TimeScale;
						if(TimeScaleIndex == 0)	Shift = 0;
						ShowTimeBase();	//显示时基
						ShowStartTime();	//显示波形起始时间
						ShowOscope();		//停止则刷新波形
						WriteDelay = 250;	//写入延时8秒
					}
				}
			}

			else if(KeyCode == K_RIGHT)		//右键 时基-
			{
				if(B_TrigMode)	//运行中, 处于调整 触发模式 垂直调整
				{
					if(++TrigMode >= 3)	TrigMode = 0;
					ShowTrigMode();
					B_ADC_Busy = 0;		//切换触发模式重新启动采样(如果没有停止的话)
					WriteDelay = 250;	//写入延时8秒
				}
				else if(SampleIndex > 2)
				{
					if(B_Run)	//运行中改变时基, 则仅仅改变采样率
					{
						SampleIndex--;
						B_ADC_Busy = 0;
						WriteDelay = 250;	//写入延时8秒
					}
					else if(TimeScaleIndex < 3)	//停止时缩放时基并刷新波形
					{
						SampleIndex--;
						TimeScaleIndex++;	//停止时缩放
						Shift = Shift * TimeScale;
						TimeScale = T_TimeScale[Current_TimeBase%3][TimeScaleIndex];	//时基系数索引, 0-->10, 1-->5, 2-->2, 3-->1
						Shift = Shift / TimeScale;
						ShowTimeBase();	//显示时基
						ShowStartTime();	//显示波形起始时间
						ShowOscope();		//停止则刷新波形
						WriteDelay = 250;	//写入延时8秒
					}
				}
			}

			else if(KeyCode == K_UP)	//上键 垂直幅度 +
			{
				if(B_Run)	//运行中
				{
					if(B_TrigMode)	//运行中, 处于调整 触发模式 垂直调整
					{
						if(B_KeyRepeat)		//重键时快速移动
						{
							if(pwm1_voltage >= 5)	pwm1_voltage -= 5;
						}
						else if(pwm1_voltage != 0)	pwm1_voltage--;
						PWMA_CCR1L = pwm1_voltage;
						WriteDelay = 250;	//写入延时8秒
					}
					else if(InputIndex != 0)	//调整垂直幅度
					{
						InputIndex--;
						ShowVoltage();
						WriteDelay = 250;	//写入延时8秒
					}
				}
				else	//左右移动波形
				{
					if(!B_KeyRepeat)	Shift++;
					else				Shift += 10;
					TimeScale = T_TimeScale[Current_TimeBase%3][TimeScaleIndex];	//时基系数索引, 0-->10, 1-->5, 2-->2, 3-->1
					if(TimeScale == 3)	j = 8000/5 - 400;
					else				j = 4000/TimeScale - 400;
					if(Shift >= j)	Shift = j;
					ShowStartTime();	//显示波形起始时间
					ShowOscope();		//停止则刷新波形
				}
			}

			else if(KeyCode == K_DOWNN)	//下键 垂直幅度 -
			{
				if(B_Run)	//运行中
				{
					if(B_TrigMode)	//运行中, 处于调整 触发模式 垂直调整
					{
						if(B_KeyRepeat)		//重键时快速移动
						{
							if(pwm1_voltage <= 245)	pwm1_voltage += 5;
						}
						else if(pwm1_voltage < 250)	pwm1_voltage++;
						PWMA_CCR1L = pwm1_voltage;
						WriteDelay = 250;	//写入延时8秒
					}
					else if(InputIndex < 7)	//调整垂直幅度
					{
						InputIndex++;
						ShowVoltage();
						WriteDelay = 250;	//写入延时8秒
					}
				}
				else	//左右移动波形
				{
					if(!B_KeyRepeat)	{	if(Shift != 0)	Shift--;	}
					else if(Shift >= 10)	Shift -= 10;
					else					Shift = 0;
					TimeScale = T_TimeScale[Current_TimeBase%3][TimeScaleIndex];	//时基系数索引, 0-->10, 1-->5, 2-->2, 3-->1
					if(TimeScale == 3)	j = 8000/5 - 400;
					else				j = 4000/TimeScale - 400;
					if(Shift >= j)	Shift = j;
					ShowStartTime();	//显示波形起始时间
					ShowOscope();		//停止则刷新波形
				}
			}
			KeyCode = 0;
		}
	}
}
/**********************************************/


/***************** 显示触发方式函数 *****************************/
void ShowTrigMode(void)
{
	if(!B_TrigMode)	background = MAGENTA;	//洋红底白字
	else			background = BLUE;
	LCD_Fill_XY(430,48, 45, 18, background);	//自动 标准 单次
		 if(TrigMode == 1)	printf_text(430+4,48+3, " 标准");
	else if(TrigMode == 2)	printf_text(430+4,48+3, " 单次");
	else					printf_text(430+4,48+3, " 自动");
	LCD_Fill_XY(430,68, 45, 18, background);	//垂直
	printf_text(430+4,68+3, " 垂直");
	background = BLACK;
}

/***************** 显示运行状态函数 *****************************/
void	ShowRunStop(void)
{
	if(B_Run)
	{
		background = BLUE;	//蓝底白字
		LCD_Fill_XY(430, 8, 45, 18, BLUE);	//运行 停止
		printf_text(430+4, 8+3, " 运行");
	}
	else
	{
		background = RED;	//红底白字
		LCD_Fill_XY(430, 8, 45, 18, RED);	//运行 停止
		printf_text(430+4, 8+3, " 停止");
	}
	background = BLACK;
}


/***************** 停止运行函数 *****************************/
void	OscStop(void)
{
	CMPCR1 = 0x86;		// 关比较器中断
	TR0    = 0;			//关闭采样定时器1
	B_ADC_Busy = 0;
	B_Run = 0;
	B_RUN_REQ = 0;
	ShowRunStop();
	Shift = 0;			//停止后可以移位波形
	ShowStartTime();	//显示波形起始时间

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


          //采样索引 SampleIndex   0     1      2      3      4     5     6     7      8     9     10     11     12     13   14    15    16    17    18    19    20
          //采样时间单位       0.1us 0.1us     us     us     us   10us  10us  10us   0.1ms 0.1ms  0.1ms   1ms   1ms    1ms  10ms  10ms  10ms  0.1s  0.1s  0.1s   1s 
u16 const   StartTimeTable[]= {   4,    8,     2,     4,     8,    2,     4,    8,    2,    4,     8,     2,     4,     8,    2,    4,    8,    2,    4,    8,   2};
          //采样时间/DIV        10us  20us   50us  100us  200us  500us   1ms   2ms    5ms  10ms   20ms   50ms  100ms  200ms  500ms   1s   2s    5s   10s   20s   50s

/***************** 显示起始时间函数 *****************************/
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

	if(SampleIndex <= 1)	//单位为0.1us
	{
		tmp[5] = tmp[4];
		tmp[4] = '.';
		tmp[6] = 'u';
		tmp[7] = 's';
		k = 3;
	}
	else if(SampleIndex <= 4)	//单位为us
	{
		tmp[5] = 'u';
		tmp[6] = 's';
		tmp[7] = ' ';
		k = 4;
	}
	else if(SampleIndex <= 7)	//单位为10us
	{
		tmp[5] = '0';
		tmp[6] = 'u';
		tmp[7] = 's';
		k = 5;
	}
	else if(SampleIndex <= 10)	//单位为0.1ms
	{
		tmp[5] = tmp[4];
		tmp[4] = '.';
		tmp[6] = 'm';
		tmp[7] = 's';
		k = 3;
	}
	else if(SampleIndex <= 13)	//单位为1ms
	{
		tmp[5] = 'm';
		tmp[6] = 's';
		tmp[7] = ' ';
		k = 4;
	}
	else if(SampleIndex <= 16)	//单位为10ms
	{
		tmp[5] = '0';
		tmp[6] = 'm';
		tmp[7] = 's';
		k = 5;
	}
	else if(SampleIndex <= 19)	//单位为0.1s
	{
		tmp[5] = tmp[4];
		tmp[4] = '.';
		tmp[6] = 's';
		tmp[7] = ' ';
		k = 3;
	}
	else	//单位为1s
	{
		tmp[5] = 's';
		tmp[6] = ' ';
		tmp[7] = ' ';
		k = 4;
	}
	for(i=0; i<k; i++)		//消无效0
	{
		if(tmp[i] != '0')	break;
		tmp[i] = ' ';
	}
	tmp[8] = 0;

	printf_text(25,13, tmp);	//黑底白字
}



	#define	X_START		40
	#define	Y_START		25
	#define	GridColor	GREEN	//格子颜色
	#define	WaveColor	YELLOW	//波形颜色

/************** 初始化示波器函数 ********************/
void	OSCOPE_inilize(void)
{
	u16	y;
	SetView_V();		//竖屏
	Rectangle(X_START-1, Y_START-1, 253, 403, WHITE);	//画长方框
	
	for(y=0; y<=400; y+=25)	Line_h(X_START-5,y+Y_START,4,WHITE);	//画底下时间刻度

	SetView_H();		//横屏
	for(y=0; y<250; y+=25)
	{
		text_ascii5x7(y+Y_START-2, 320-(X_START-9), (u8)((y/25)%10));	//底下刻度个位
	}
	for(y=250; y<=400; y+=25)
	{
		text_ascii5x7(y+Y_START-5,   320-(X_START-9), '1');				//底下刻度十位
		text_ascii5x7(y+Y_START+1,   320-(X_START-9), (u8)((y/25)%10));	//底下刻度个位
	}
}



//	P_V_C = 0;	P_V_B = 1;	P_V_A = 1;	//输入增益选择, CBA   000 001 010 011 100 101 110 111
										//				倍数   2   4   10  1   20 200  40 100
  //索引InputIndex      0   1    2    3   4    5    6    7    8   9   10
			//倍数      1   2    4   10  20   40   100  200  200 200 200
			//ADC      /20 /20  /20  /20 /20  /20  /20  /20  /10  /4  /2
u8	const T_V_GAIN[14]={ 3,  0,   1,   2,  4,   6,   7,   5,   5,  5,  5};	//电压幅度, adc/n, 幅度档位, 0->0.25V/DIV, 1->0.5V/DIV, 2->1V/DIV, 3->2.5V/DIV, 4->5V/DIV
			//幅度     1V 500m 250m 100m 50m  25m  10m  5m  2.5m  1m 0.5m
			//幅度    10V  5V  2.5V  1V  500m 250m 100m 50m  25m 10m  5m

/************** 显示波形函数 ( 50us< 采样 <=20ms/DIV 或停止后缩放时基) ********************/
void	ShowOscope(void)
{
	u16	x,y,j;
	u8	i;

	if(TimeScale == 3)
	{
		j = 8000/5 - 400;	//波形移位处理
		if(Shift >= j)	Shift = j;
		for(j=(Shift*5)/2,x=0; x<400; x++)
		{
			i = adc_sample[j];	//读一个采样
			if(i > 250)	i = 250;
			adc_tmp[x] = i;
			j = j + 2;
			x++;
			i = adc_sample[j];	//读一个采样
			if(i > 250)	i = 250;
			adc_tmp[x] = i;
			j = j + 3;
		}
	}
	else
	{
		j = 4000/TimeScale - 400;	//波形移位处理
		if(Shift >= j)	Shift = j;
		for(j=Shift*TimeScale,x=0; x<400; x++)
		{
			i = adc_sample[j];	//读一个采样
			if(i > 250)	i = 250;
			adc_tmp[x] = i;
			j = j + TimeScale;
		}
	}

	SetView_V();		//竖屏
	LastDot = adc_tmp[0] + X_START;
	for(y=0; y<400; y++)
	{
		if(((y%25) == 0) || (y == 199) || (y == 201))	Line_Grid5(X_START, y+Y_START, GridColor);		//每5个点一个刻度
		else if((y%5) == 0)		Line_Grid25(X_START, y+Y_START, GridColor);	//每25个点一个刻度
		else					Line_h(X_START,y+Y_START,251, BLACK);	//清除一条线
		
		x = adc_tmp[y] + X_START;
		if(x == LastDot)		WriteSingleDot(x, y+Y_START,  WaveColor);	//两个点相等
		else if(x < LastDot)	Line_h(x,y+Y_START,LastDot-x, WaveColor);
		else 					Line_h(LastDot+1,y+Y_START,x-LastDot, WaveColor);
		LastDot = x;
	}
	Line_Grid5(X_START, 400+Y_START, GridColor);	//最后一排刻度

	SetView_H();		//横屏
}


/************** 实时显示波形函数(>=50ms/DIV) ********************/
void	RealShowOscope(void)
{
	u16	x,y;
	u8	i;

	y = adc_rd/10;
	if(y >= 400)	return;	

	SetView_V();		//竖屏
	if(((y%25) == 0) || (y == 199) || (y == 201))	Line_Grid5( X_START, y+Y_START, GridColor);	//每5个点一个刻度
	else if((y%5) == 0)								Line_Grid25(X_START, y+Y_START, GridColor);	//每25个点一个刻度
	else											Line_h(X_START,y+Y_START,251, BLACK);		//清除一条线

	i = adc_sample[adc_rd];
	if(i > 250)	i = 250;	//增加判断, 中断不判断
	x = (u16)i + X_START;
	if(adc_rd == 0)			LastDot = x;	//刚开始的第一个点
	if(x == LastDot)		WriteSingleDot(x, y+Y_START,  WaveColor);	//两个点相等
	else if(x < LastDot)	Line_h(x,y+Y_START,LastDot-x, WaveColor);
	else 					Line_h(LastDot+1,y+Y_START,x-LastDot, WaveColor);	//if(x > LastDot)
	LastDot = x;
	adc_rd += 10;
	SetView_H();		//横屏
}


/***************** ADC配置函数 *****************************/
#define ADC_START	(1<<6)	/* 自动清0 */
#define ADC_FLAG	(1<<5)	/* 软件清0 */

#define	ADC_SPEED	0		/* 0~15, ADC时钟 = SYSclk/2/(n+1) */
#define	RES_FMT		(0<<5)	/* ADC结果格式 0: 左对齐, ADC_RES: D9 D8 D7 D6 D5 D4 D3 D2, ADC_RESL: D1 D0 0  0  0  0  0  0 */
							/*             1: 右对齐, ADC_RES: 0  0  0  0  0  0  D9 D8, ADC_RESL: D7 D6 D5 D4 D3 D2 D1 D0 */

#define CSSETUP		(0<<7)	/* 0~1,  ADC通道选择时间      0: 1个ADC时钟, 1: 2个ADC时钟,  默认0(默认1个ADC时钟)	*/
#define CSHOLD		(0<<5)	/* 0~3,  ADC通道选择保持时间  (n+1)个ADC时钟, 默认1(默认2个ADC时钟)					*/
#define SMPDUTY		10		/* 10~31, ADC模拟信号采样时间  (n+1)个ADC时钟, 默认10(默认11个ADC时钟)				*/
							/* ADC转换时间: 10位ADC固定为10个ADC时钟, 12位ADC固定为12个ADC时钟. 				*/

void	ADC_config(void)
{
	P0n_pure_input(0x10);	//设置要做ADC的IO做高阻输入
	ADC_CONTR = 0x80 + 12;	//ADC on + channel
	ADCCFG = RES_FMT + ADC_SPEED;
	P_SW2 |=  0x80;	//访问XSFR
	ADCTIM = CSSETUP + CSHOLD + SMPDUTY;	//28 ADC CLOCK
}
//***********************************************************************************************

//========================================================================
// 函数: void Timer4_Config(void)
// 描述: timer3初始化函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2018-12-20
//========================================================================
void Timer4_Config(void)
{
	P_SW2 |= 0x80;		//SFR enable   
	T4T3M &= 0x0f;		//停止计数, 定时模式, 12T模式, 不输出时钟

	T4T3M |=  (1<<5);	//1T mode
	T4H = (u8)((65536UL - MAIN_Fosc/2000) /256);
	T4L = (u8)((65536UL - MAIN_Fosc/2000) %256);

	T3T4PIN = 0x00;		//选择IO, 0x00: T3--P0.4, T3CLKO--P0.5, T4--P0.6, T4CLKO--P0.7;    0x01: T3--P0.0, T3CLKO--P0.1, T4--P0.2, T4CLKO--P0.3;
	T4T3M |=  (1<<4);	//允许输出时钟
	T4T3M |=  (1<<7);	//开始运行
}

/************************ 比较器配置函数 ****************************/
void	Compare_Config(void)	//比较器初始化
{
	CMPCR1 = 0;
	CMPCR2 = 10;		//比较结果变化延时周期数, 0~63
	CMPCR1 |= (1<<7);	//1: 允许比较器,     0:关闭比较器
	CMPCR1 |= (0<<5);	//1: 允许上升沿中断, 0: 禁止
	CMPCR1 |= (0<<4);	//1: 允许下降沿中断, 0: 禁止
	CMPCR1 |= (0<<3);	//输入正极性选择, 0: 选择外部P3.7做正输入,           1: 由ADC_CHS[3:0]所选择的ADC输入端做正输入.
	CMPCR1 |= (1<<2);	//输入负极性选择, 0: 选择内部BandGap电压BGv做负输入, 1: 选择外部P3.6做输入
	CMPCR1 |= (1<<1);	//1: 允许比较结果输出到IO(P3.4或P4.1),  0: 比较结果禁止输出到IO
	CMPCR2 |= (0<<7);	//1: 比较器结果输出IO取反, 0: 不取反
	CMPCR2 |= (0<<6);	//0: 允许内部0.1uF滤波,    1: 关闭

	CMPO_P34();				//结果输出到P3.4.
//	CMPO_P41();				//结果输出到P4.1.
	P3n_push_pull(Pin4);	//P3.4设置为推挽输出
	P3n_pure_input(0xc0);	//设置要做ADC的IO做高阻输入(P3.7 P3.6)
	IP2  |= (1<<5);	//比较器中断优先级最高
	IP2H |= (1<<5);

	CMPCR1 = 0x86;			// 关比较器中断
//	CMPCR1 = 0x86 + 0x20;	// 比较器上升沿中断
//	CMPCR1 = 0x86 + 0x10;	// 比较器下降沿中断
}

/***************** 比较器中断函数 *****************************/
void CMP_ISR(void) interrupt CMP_VECTOR		//比较器中断函数, 检测到反电动势过0事件
{
	ADC_RES = 0;
//	ADC_RESL = 0;
	ADC_CONTR = 0x80 + ADC_START + 12;	//ADC on + channel
	TR0 = 1;		//开始运行Timer1.

	AutoTimeCnt = 0;	//有同步信号, 则取消超时触发
	adc_wr  = 0;
	adc_rd  = 0;

	CMPCR1 = 0x86;		// 关比较器中断 并且清除中断标志位
}

/***************** 定时器1初始化函数 *****************************/
void	Timer1_config(void)
{
	TR1 = 0;	//停止计数
	Timer1_1T();
	Timer1_16bit();
	Timer1_AsCounter();
	TH1 = 0;	TL1 = 0;
	Timer1_Gate_INT1_P33();
	Timer1_InterruptEnable();
	TR1 = 1;
}

//========================================================================
// 函数: void timer1_ISR (void) interrupt TMR1_VECTOR
// 描述:  timer1中断函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2018-12-20
//========================================================================
void timer1_ISR (void) interrupt TMR1_VECTOR
{
	freq_H++;
}

/********************* INT0中断函数 *************************/
void INT1_ISR(void) interrupt INT1_VECTOR
{
	frequency = ((u32)freq_H << 16) + ((u32)TH1 << 8) + (u32)TL1;
	freq_H = 0;	TH1 = 0;	TL1 = 0;
	B_FrequencyOk = 1;
}


//========================================================================
// 函数: void PWMA_config(void)
// 描述: PWMA初始化函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2022-6-25
//========================================================================
void PWMA_config(void)
{
	u8	ccer1;
	u8	ccer2;
	u8	ps;
	u8	eno;
	u8	PWMA_ISR_En;

	P_SW2 |= 0x80;		//SFR enable   
	PWMA_ENO    = 0;	// IO输出禁止
	PWMA_IER    = 0;	// 禁止中断
	PWMA_SR1    = 0;	// 清除状态
	PWMA_SR2    = 0;	// 清除状态
	ccer1 = 0;
	ccer2 = 0;
	ps    = 0;
	eno   = 0;
	PWMA_ISR_En = 0;

	PWMA_PSCRH = 0x00;		// 预分频寄存器, 分频 Fck_cnt = Fck_psc/(PSCR[15:0}+1), 边沿对齐PWM频率 = SYSclk/((PSCR+1)*(AAR+1)), 中央对齐PWM频率 = SYSclk/((PSCR+1)*(AAR+1)*2).
	PWMA_PSCRL = 0x00;
	PWMA_DTR  = 24;			// 死区时间配置, n=0~127: DTR= n T,   0x80 ~(0x80+n), n=0~63: DTR=(64+n)*2T,  
							//				0xc0 ~(0xc0+n), n=0~31: DTR=(32+n)*8T,   0xE0 ~(0xE0+n), n=0~31: DTR=(32+n)*16T,
	PWMA_ARRH   = 256/256;	// 自动重装载寄存器,  控制PWM周期
	PWMA_ARRL   = 256%256;

	PWMA_CCMR1  = 0x68;		// 通道模式配置, PWM模式1, 预装载允许
	PWMA_CCR1H  = 128/256;	// 比较值, 控制占空比(高电平时钟数)
	PWMA_CCR1L  = 128%256;
	ccer1 |= 0x05;			// 开启比较输出, 高电平有效
	ps    |= 0;				// 选择IO, 0:选择P1.0 P1.1, 1:选择P2.0 P2.1, 2:选择P6.0 P6.1, 
	eno   |= 0x01;			// IO输出允许,  bit7: ENO4N, bit6: ENO4P, bit5: ENO3N, bit4: ENO3P,  bit3: ENO2N,  bit2: ENO2P,  bit1: ENO1N,  bit0: ENO1P
//	PWMA_ISR_En|= 0x02;		// 使能中断

	PWMA_CCMR2  = 0x68;		// 通道模式配置, PWM模式1, 预装载允许
	PWMA_CCR2H  = 128/256;	// 比较值, 控制占空比(高电平时钟数)
	PWMA_CCR2L  = 128%256;
	ccer1 |= 0x50;			// 开启比较输出, 高电平有效
	ps    |= (0<<2);		// 选择IO, 0:选择P1.2 P1.3, 1:选择P2.2 P2.3, 2:选择P6.2 P6.3, 
	eno   |= 0x08;			// IO输出允许,  bit7: ENO4N, bit6: ENO4P, bit5: ENO3N, bit4: ENO3P,  bit3: ENO2N,  bit2: ENO2P,  bit1: ENO1N,  bit0: ENO1P
//	PWMA_ISR_En|= 0x04;		// 使能中断

	PWMA_CCMR3  = 0x68;		// 通道模式配置, PWM模式1, 预装载允许
	PWMA_CCR3H  = 128/256;	// 比较值, 控制占空比(高电平时钟数)
	PWMA_CCR3L  = 128%256;
	ccer2 |= 0x05;			// 开启比较输出, 高电平有效
	ps    |= (0<<4);		// 选择IO, 0:选择P1.4 P1.5, 1:选择P2.4 P2.5, 2:选择P6.4 P6.5, 
	eno   |= 0x10;			// IO输出允许,  bit7: ENO4N, bit6: ENO4P, bit5: ENO3N, bit4: ENO3P,  bit3: ENO2N,  bit2: ENO2P,  bit1: ENO1N,  bit0: ENO1P
//	PWMA_ISR_En|= 0x08;		// 使能中断

	PWMA_CCER1  = ccer1;	// 捕获/比较使能寄存器1
	PWMA_CCER2  = ccer2;	// 捕获/比较使能寄存器2
	PWMA_PS     = ps;		// 选择IO
	PWMA_IER    = PWMA_ISR_En;	//设置允许通道1~4中断处理

	PWMA_BKR    = 0x80;		// 主输出使能 相当于总开关
	PWMA_CR1    = 0x81;		// 使能计数器, 允许自动重装载寄存器缓冲, 边沿对齐模式, 向上计数,  bit7=1:写自动重装载寄存器缓冲(本周期不会被打扰), =0:直接写自动重装载寄存器本(周期可能会乱掉)
	PWMA_EGR    = 0x01;		//产生一次更新事件, 清除计数器和预分频计数器, 装载预分频寄存器的值
	PWMA_ENO    = eno;		// 允许IO输出

	P1n_push_pull(0x19);	//P1.0 P1.3 P1.4 设置为推挽输出
}
//	PWMA_PS   = (0<<6)+(0<<4)+(0<<2)+0;	//选择IO, 4项从高到低(从左到右)对应PWM1 PWM2 PWM3 PWM4, 0:选择P1.x, 1:选择P2.x, 2:选择P6.x, 
//  PWMA_PS    PWM4N PWM4P    PWM3N PWM3P    PWM2N PWM2P    PWM1N PWM1P
//    00       P1.7  P1.6     P1.5  P1.4     P1.3  P5.4     P1.1  P1.0
//    01       P2.7  P2.6     P2.5  P2.4     P2.3  P2.2     P2.1  P2.0
//    02       P6.7  P6.6     P6.5  P6.4     P6.3  P6.2     P6.1  P6.0
//    03       P3.3  P3.4      --    --       --    --       --    --

//========================================================================
// 函数: void PWMB_config(void)
// 描述: PWMA初始化函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2022-6-25
//========================================================================
void PWMB_config(void)
{
	u8	ccer1;
	u8	ccer2;
	u8	ps;
	u8	eno;
	u8	PWMB_ISR_En;

	P_SW2 |= 0x80;		//SFR enable   
	PWMB_ENO    = 0;	// IO输出禁止
	PWMB_IER    = 0;	// 禁止中断
	PWMB_SR1    = 0;	// 清除状态
	PWMB_SR2    = 0;	// 清除状态
	ccer1 = 0;
	ccer2 = 0;
	ps    = 0;
	eno   = 0;
	PWMB_ISR_En = 0;

	PWMB_PSCRH = (u8)((35000-1)/256);		// 预分频寄存器, 分频 Fck_cnt = Fck_psc/(PSCR[15:0}+1), 边沿对齐PWM频率 = SYSclk/((PSCR+1)*(AAR+1)), 中央对齐PWM频率 = SYSclk/((PSCR+1)*(AAR+1)*2).
	PWMB_PSCRL = (u8)((35000-1)%256);
	PWMB_ARRH  = (u8)(1010/256);	// 自动重装载寄存器,  控制PWM周期
	PWMB_ARRL  = (u8)(1010%256);

	PWMB_CCMR3  = 0x68;		// 通道模式配置, PWM模式1, 预装载允许
	PWMB_CCR3H  = (u8)(1000/256);	// 比较值, 控制占空比(高电平时钟数)
	PWMB_CCR3L  = (u8)(1000%256);
	ccer2 |= 0x05;			// 开启比较输出, 高电平有效
	ps    |= (1<<4);		// 选择IO, 0:选择P2.2, 1:选择P3.3, 2:选择P0.2, 3:选择P7.6, 
	eno   |= 0x10;			// IO输出允许,  bit6: ENO8P, bit4: ENO7P,  bit2: ENO6P,  bit0: ENO5P
//	PWMB_ISR_En|= 0x08;		// 使能中断

	PWMB_CCER1  = ccer1;	// 捕获/比较使能寄存器1
	PWMB_CCER2  = ccer2;	// 捕获/比较使能寄存器2
	PWMB_PS     = ps;		// 选择IO
	PWMB_IER    = PWMB_ISR_En;	//设置允许通道1~4中断处理

	PWMB_BKR    = 0x80;		// 主输出使能 相当于总开关
	PWMB_CR1    = 0x81;		// 使能计数器, 允许自动重装载寄存器缓冲, 边沿对齐模式, 向上计数,  bit7=1:写自动重装载寄存器缓冲(本周期不会被打扰), =0:直接写自动重装载寄存器本(周期可能会乱掉)
	PWMB_EGR    = 0x01;		//产生一次更新事件, 清除计数器和预分频计数器, 装载预分频寄存器的值
	PWMB_ENO    = eno;		// 允许IO输出
	P3n_push_pull(1<<3);	//P3.3设置为推挽输出
}
//	PWMB_PS   = (0<<6)+(0<<4)+(0<<2)+0;	//选择IO, 4项从高到低(从左到右)对应PWM8 PWM7 PWM6 PWM5
//  PWMB_PS    PWM8    PWM7    PWM6    PWM5
//    00       P2.3    P2.2    P2.1    P2.0
//    01       P3.4    P3.3    P5.4    P1.7
//    02       P0.3    P0.2    P0.1    P0.0
//    03       P7.7    P7.6    P7.5    P7.4


//========================================================================
// 函数:void	Timer0_config(void)
// 描述: timer0初始化函数.
// 参数: noe.
// 返回: none.
// 版本: V1.0, 2018-12-20
//========================================================================
void	Timer0_config(void)
{
	TR0 = 0;	//停止计数
	ET0 = 1;	//允许中断
	PT0 = 1;	//高优先级中断
	TMOD &= ~0x03;
//	TMOD |= 0;	//工作模式, 0: 16位自动重装, 1: 16位定时/计数, 2: 8位自动重装
	Timer0_1T();	//1T mode
//	TR0 = 1;	//开始运行
}

//========================================================================
void timer0_ISR (void) interrupt TMR0_VECTOR
{
	adc = ~ADC_RES;
	ADC_RES = 0;
//	ADC_RESL = 0;
	ADC_CONTR = 0x80 + ADC_START + 12;	//ADC on + channel

	if(!B_sample_ms)	//  <=20ms/DIV, 采样完一块再显示
	{
		adc_sample[adc_wr] = adc;
		if(++adc_wr >= 4000)	B_Sample_OK = 1, TR0 = 0;
	}

	else if(--sample_cnt == 0)	// >=50ms/DIV 实时扫描显示波形
	{
		sample_cnt = SampleTime;
		adc_sample[adc_wr] = adc;
		if((adc_wr%10) == 0)	B_Sample_OK = 1;
		if(++adc_wr >= 4000)	B_Sample_OK = 1, TR0 = 0;
	}
}

//================= 触发超时处理 ========================
void	AutoCheck(void)
{
	if(AutoTimeCnt != 0)		//8ms call
	{
		if(--AutoTimeCnt == 0)	//同步触发超时, 则强制启动
		{
			ADC_RES = 0;
			ADC_RESL = 0;
			ADC_CONTR = 0x80 + ADC_START + 12;	//ADC on + channel
			TR0 = 1;		//开始运行Timer1.

			CMPCR1 = 0x86;		// 关比较器中断
			adc_wr  = 0;
			adc_rd  = 0;
		}
	}
}




#define	D_MAIN_CLOCK	35

          //采样索引 SampleIndex   0     1      2      3      4     5      6     7      8     9     10     11     12     13     14   15   16    17    18    19    20
          //采样时间单位          us    us     us     us     us    us     us    us     us    us     us     ms     ms     ms     ms   ms   ms    ms    ms    ms    ms 
u16	const   SampleTimeTable[]={   2,    2,     2,     2,     2,     2,    4,    8,    20,   40,    80,   200,   400,   800,     2,   4,    8,   20,   40,   80,  200};
          //采样时间/DIV        10us  20us   50us  100us  200us  500us   1ms   2ms    5ms  10ms   20ms   50ms  100ms  200ms  500ms   1s   2s    5s   10s   20s   50s
u16	const   T_Time_div[]=     {  10,   20,    50,   100,   200,   500,    1,    2,     5,   10,    20,    50,   100,   200,   500,   1,    2,    5,   10,   20,   50};

/***************** 设置采样时间函数 *****************************/
void	SetSampleTime(void)
{
	u16	j;

		 if(SampleIndex <= 5)	ADCCFG = RES_FMT + 0;	// ADC CLOCK = 20MHz @2us/sample,  ADC CLOCK = SYSclk/2/(n+1), 转换需要 28 ADC CLOCK
	else if(SampleIndex == 6)	ADCCFG = RES_FMT + 1;	// ADC CLOCK = 10MHz @4us/sample,  ADC CLOCK = SYSclk/2/(n+1)
	else if(SampleIndex == 7)	ADCCFG = RES_FMT + 3;	// ADC CLOCK =  5MHz @8us/sample,  ADC CLOCK = SYSclk/2/(n+1)
	else 						ADCCFG = RES_FMT + 9;	// ADC CLOCK =  2MHz >=20us/sample, ADC CLOCK = SYSclk/2/(n+1)

		 if(SampleIndex <= 8)	AutoTime = 100/8;	//同步超时100ms	   <=5ms/div		<=60ms/frme
	else if(SampleIndex == 9)	AutoTime = 200/8;	//同步超时200ms	   10ms/div			==120ms/frme
	else if(SampleIndex == 10)	AutoTime = 400/8;	//同步超时500ms	   20ms/div			==240ms/frme
	else if(SampleIndex == 11)	AutoTime = 800/8;	//同步超时800ms	   50ms/div			==600ms/frme
	else if(SampleIndex == 12)	AutoTime = 1600/8;	//同步超时800ms	   100ms/div		==600ms/frme
	else 						AutoTime = 2000/8;	//同步超时1200ms   >=200ms/div		>=1200ms/frme

	if(TrigMode == 0)	AutoTimeCnt = AutoTime;	//自动模式

	if(SampleIndex <= 10)	//50us 100us 200us/DIV均用2us采样, 500us~20ms/DIV使用10倍采样
	{
		j = SampleTimeTable[SampleIndex];
		TR0 = 0;	//停止计数
		B_sample_ms = 0;
		TH0 = (u8)((65536UL - j*D_MAIN_CLOCK) / 256);
		TL0 = (u8)((65536UL - j*D_MAIN_CLOCK) % 256);
	}
	
	else if(SampleIndex <= 13)	// 50ms 100ms 200ms/DIV使用10倍采样
	{
		j = SampleTimeTable[SampleIndex];
		TR0 = 0;	//停止计数
		SampleTime  = 1;	//依旧是一次中断采样一次
		sample_cnt  = 1;
		B_sample_ms = 1;	//实时扫描显示
		TH0 = (u8)((65536UL - j*D_MAIN_CLOCK) / 256);
		TL0 = (u8)((65536UL - j*D_MAIN_CLOCK) % 256);
	}

	else 		// >=500ms/DIV, 实时扫描, 定时器中断固定为1ms
	{
		j = SampleTimeTable[SampleIndex];
		TR0 = 0;	//停止计数
		SampleTime  = j;	//一个采样点对应的中断次数
		sample_cnt  = j;
		B_sample_ms = 1;	//实时扫描显示
		TH0 = (u8)((65536UL - 1000*D_MAIN_CLOCK) / 256);	//1ms中断
		TL0 = (u8)((65536UL - 1000*D_MAIN_CLOCK) % 256);
	}
	ShowTimeBase();	//显示时基
}

/***************** 显示时基函数 *****************************/
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
	else if(SampleIndex <= 14)	tmp[3] = 'm';	//500ms以下
	else						tmp[3] = ' ';	//1s以上
	
	background = MAGENTA;	//洋红底白字
	for(k=0; k<5; k++)	text_ascii5x7(130+5+k*6,8+7, tmp[k]);
	background = BLACK;
}


	//InputIndex     0   1    2    3     4    5      6    7
	//InputIndex+3                 3     4    5      6    7      8    9  10   11   12   13
	// V/DIV        10V  5V  2.5V  1V  500mV 250mV 100mV 50mV
u8 const *T_VOLTAGE10[]={
" 10V ", "  5V ", "2.5V ", "  1V ", "500mV", "250mV", "100mV", " 50mV"};

/***************** 显示垂直电压档位 V/DIV 函数 *****************************/
void	ShowVoltage(void)
{
	u8	i;
	background = MAGENTA;	//洋红底白字
	printf_text(185, 13, T_VOLTAGE10[InputIndex]);		//
	background = BLACK;

	i = T_V_GAIN[InputIndex];
	if(i & 0x04)	P_V_C = 1;	else P_V_C = 0;
	if(i & 0x02)	P_V_B = 1;	else P_V_B = 0;
	if(i & 0x01)	P_V_A = 1;	else P_V_A = 0;
}

/***************** 显示触发模式函数 *****************************/
void	ShowPhase(void)
{
	background = MAGENTA;	//洋红底白字
	if(B_TrigPhase)	printf_text(430+4,28+3, "上生沿");	//0xfd问题, 升字不能出现, 通假为生
	else			printf_text(430+4,28+3, "下降沿");
	background = BLACK;
}


/***************** 读键函数 *****************************/
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

	if(KeyState == 0)		//无键按下
	{
		P_K_DOWN = 0;
		for(j=0; j<5; j++)	{	NOP(2);	}	//延时一下, 循环体一定要有代码, 否则优化掉
		if(!P_K_UP)		KeyState |= 0x40;	//垂直位置
		if(!P_K_RIGHT)	KeyState |= 0x80;	//触发电平
		P_K_DOWN = 1;
	}
	
	j = (i ^ KeyState) & KeyState;	//按下检测

	if((KeyState & 0x0f) != 0)		//重键检测, 上下左右键支持重键
	{
		if(++KeyHoldCnt >= 36)
		{
			KeyHoldCnt = 33;	//4*32=128ms, 1秒8键
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
// 函数: u8	Timer3_Config(u8 t, u32 reload)
// 描述: timer3初始化函数.
// 参数:      t: 重装值类型, 0表示重装的是系统时钟数, 其余值表示重装的是时间(us).
//       reload: 重装值.
// 返回: 0: 初始化正确,  1: 重装值过大, 初始化错误.
// 版本: V1.0, 2018-12-20
//========================================================================
u8	Timer3_Config(u8 t, u32 reload)	//t=0: reload值是主时钟周期数,  t=1: reload值是时间(单位us)
{
	P_SW2 |= 0x80;		//SFR enable   
	T4T3M &= 0xf0;		//停止计数, 定时模式, 12T模式, 不输出时钟

	if(t != 0)	reload = (u32)(((float)MAIN_Fosc * (float)reload)/1000000UL);	//重装的是时间(us), 计算所需要的系统时钟数.
	if(reload >= (65536UL * 12))	return 1;	//值过大, 返回错误
	if(reload < 65536UL)	T4T3M |=  (1<<1);	//1T mode
	else	reload = reload / 12;	//12T mode
	reload = 65536UL - reload;
	T3H = (u8)(reload >> 8);
	T3L = (u8)(reload);

//	T3T4PIN = 0x01;		//选择IO, 0x00: T3--P0.4, T3CLKO--P0.5, T4--P0.6, T4CLKO--P0.7;    0x01: T3--P0.0, T3CLKO--P0.1, T4--P0.2, T4CLKO--P0.3;
	IE2   |=  (1<<5);	//允许中断
	T4T3M |=  (1<<3);	//开始运行
	return 0;
}

#include	"SineTable.h"
u8	SineIndex;
//========================================================================
// 函数: void Timer3_ISR(void) interrupt TMR3_VECTOR
// 描述:  timer3中断函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2018-12-20
//========================================================================
void Timer3_ISR(void) interrupt TMR3_VECTOR
{
	PWMA_CCR2L = T_SIN[SineIndex];		//P1.3输出100Hz正弦波
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


