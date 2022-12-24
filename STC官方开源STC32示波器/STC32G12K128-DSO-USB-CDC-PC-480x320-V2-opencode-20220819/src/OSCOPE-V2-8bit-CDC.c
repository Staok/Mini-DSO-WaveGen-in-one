
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
OSCOPE-V2-8bit-CDC.c	8bit采样


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
MCU:      STC32G12K128.
主频:     35MHz。
ADC:      最高采样800KHz 12位，本示波器使用最高采样率500KHz。
模拟带宽: 探头x1大于等于250mV/DIV，探头x10大于等于2.5V/DIV：100KHz。
显示屏:   虚拟显示, 通信方式 USB-CDC。
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


#include	"inc\stc.h"
#include	"EEPROM.h"
#include	"stc.h"
#include	"usb.h"
#include	"uart.h"


/*************	本地常量声明	**************/
#define		K_BaseTimeUp	0x01
#define		K_BaseTimeDn	0x02
#define		K_VoltageUp		0x03
#define		K_VoltageDn		0x04
#define		K_RUN_STOP 		0x05
#define		K_TrigPhase		0x06
#define		K_TrigMode		0x07
#define		K_ShiftLeft		0x08
#define		K_ShiftRight	0x09
#define		K_WaveUp		0x0A
#define		K_WaveDown		0x0B
#define		K_RtnMssage		0x0C

#define		EE_ADDR		0x000000


/*************	IO口声明	**************/

sbit	P_V_A    = P0^6;	//输入增益选择
sbit	P_V_B    = P0^5;	//输入增益选择, CBA   000 001 010 011 100 101 110 111
sbit	P_V_C    = P5^3;	//输入增益选择, 倍数   2   4   10  1   20 200  40 100  
//P0.7--T4CLKO: 1000Hz方波输出
//P0.4--ADC12: 波形输入
//P1.0--PWM1P: 垂直位移PWM
//P1.3--PWM2N: 输出SPWM, 100Hz正弦波.
//P1.4--PWM3P: 负电压50% PWM
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
bit	B_32ms_rtn;

u16 	TxCnt;


/*************	本地函数声明	**************/
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
void	AutoCheck(void);
void 	ShowTrigMode(void);
void	ShowRunStop(void);
void	OscStop(void);

void	TxData255(u8 dat);	//转义字符处理
void	TX_write2buff(u8 dat);	//写入发送缓冲，指针+1
void	TrigTx(void);	//触发发送


/****************  外部函数声明和外部变量声明 *****************/

/**************************************************************/

//采样索引 SampleIndex   0     1      2      3      4     5      6     7      8     9     10     11     12     13     14   15   16    17    18    19    20
//采样时间/DIV         10us  20us   50us  100us  200us  500us   1ms   2ms    5ms  10ms   20ms   50ms  100ms  200ms  500ms  1s   2s    5s   10s   20s   50s
//第一维3, 是(SampleIndex % 3)的余数, 第二维是缩放系数, 数字为每N个点取一点, 但数字三是指2.5点取一点, 折中方案是每5点取0 2两点.
u8	const 	T_TimeScale[3][4]={	{10,5,2,1},
								{10,5,3,1},
								{10,4,2,1}};

//========================================================================
void  delay_ms(u16 ms)
{
     u16 i;
	 do
	 {
	 	i = MAIN_Fosc / 6000;
		while(--i)	;
     }while(--ms);
}

/****************  主函数 *****************/
void	main(void)
{
	u16	j;

	WTST  = 0;
	CKCON = 0;
    EAXFR = 1;	//允许访问扩展寄存器

	P0M1 = 0;	P0M0 = 0;	//设置为准双向口
	P1M1 = 0;	P1M0 = 0;	//设置为准双向口
	P2M1 = 0;	P2M0 = 0;	//设置为准双向口
	P3M1 = 0;	P3M0 = 0;	//设置为准双向口
	P4M1 = 0;	P4M0 = 0;	//设置为准双向口
	P5M1 = 0;	P5M0 = 0;	//设置为准双向口
	P6M1 = 0;	P6M0 = 0;	//设置为准双向口
	P7M1 = 0;	P7M0 = 0;	//设置为准双向口
	
	P0n_push_pull(0x80);	//P0.7 T4CLKO 1000Hz

	P33 = 1;	P35 = 1;	//	P3.3--PWM7_2: H1S_L10ms测频闸门信号


    P3M0 &= ~0x03;	//设置为高阻
    P3M1 |= 0x03;
    
    IRC48MCR = 0x80;
    while (!(IRC48MCR & 0x01));

	uart_init();
	usb_init();
	EA = 1;

	delay_ms(500);
	while(DeviceState != DEVSTATE_CONFIGURED)	{	NOP(3);	}
	
	ADC_config();		//ADC初始化
	Compare_Config();	//模拟比较器初始化
	Timer0_config();	//Timer0初始化, 采样
	Timer1_config();	//Timer1初始化, 频率计
	Timer3_Config(0, MAIN_Fosc / 5000);	//t=0: reload值是主时钟周期数,  (中断频率, 20000次/秒)
	Timer4_Config();	//Timer4初始化, 输出1000Hz方波.
	PWMA_config();		//PWM控制垂直位移、触发电平
	PWMB_config();		//产生 H1S_L10ms闸门信号用于测频
	
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
	

	B_Shift = 0;
	Shift  = 0;
	B_ADC_Busy = 0;
	B_Run = 1;

	ShowTimeBase();		//显示水平时基
	ShowVoltage();		//显示垂直电压
	ShowRunStop();		//显示停止/运行
	ShowPhase();		//显示触发模式(触发边沿)
	ShowTrigMode();		//显示触发方式
	
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
					while(!B_32ms_rtn)	{	NOP(5);	}	//USB上传速度太快，则限制其上传速度
					B_32ms_rtn = 0;
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

			if(B_FrequencyOk)	//频率已OK
			{
				B_FrequencyOk = 0;
				TxCnt = 0;
				TX_write2buff(0xfe);	//命令头
				TX_write2buff(0x07);	//上传的是频率
				TxData255((u8)(frequency >> 24));
				TxData255((u8)(frequency >> 16));
				TxData255((u8)(frequency >> 8));
				TxData255((u8)frequency);
				TX_write2buff(0xff);	//命令结束
				TrigTx();	//触发发送
			}
		}
		else	B_ADC_Busy = 0;

		if (RxFlag)                         //当RxFlag为1时,表示已接收到CDC串口数据
											//接收的数据大小保存在RxCount里面,每个包最多接收64字节
											//数据保存在RxBuffer缓冲区
		{
			if((RxCount == 4) && (RxBuffer[0]==0xfe) &&(RxBuffer[1] == 0x01) && (RxBuffer[3] == 0xff))
			KeyCode = RxBuffer[2];			//PC下传键代码：FE 01 DAT0 FF
			uart_recv_done();               //对接收的数据处理完成后,一定要调用一次这个函数,以便CDC接收下一笔串口数据
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

			else if(KeyCode == K_TrigPhase)	//切换上升沿 下降沿触发
			{
				B_TrigPhase = ~B_TrigPhase;
				ShowPhase();
				B_ADC_Busy = 0;		//切换触发模式重新启动采样(如果没有停止的话)
				WriteDelay = 250;	//写入延时8秒
			}

			else if(KeyCode == K_TrigMode)	//切换触发方式
			{
				if(++TrigMode >= 3)	TrigMode = 0;	//0: 自动, 1:普通(标准), 2:单次
				ShowTrigMode();
				B_ADC_Busy = 0;		//切换触发模式重新启动采样(如果没有停止的话)
				WriteDelay = 250;	//写入延时8秒
			}

			else if(KeyCode == K_BaseTimeUp)	// 时基+
			{
				if(SampleIndex < 20)
				{
					if(B_Run)	//运行中改变时基, 则仅仅改变采样率
					{
						SampleIndex++;
						B_ADC_Busy = 0;
						ShowTimeBase();	//显示时基
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

			else if(KeyCode == K_BaseTimeDn)		// 时基-
			{
				if(SampleIndex > 2)
				{
					if(B_Run)	//运行中改变时基, 则仅仅改变采样率
					{
						SampleIndex--;
						B_ADC_Busy = 0;
						ShowTimeBase();	//显示时基
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

			else if(KeyCode == K_VoltageUp)	//垂直幅度 +
			{
				if(B_Run)	//运行中
				{
					if(InputIndex != 0)	//调整垂直幅度
					{
						InputIndex--;
						ShowVoltage();
						WriteDelay = 250;	//写入延时8秒
					}
				}
			}
			else if(KeyCode == K_VoltageDn)	// 垂直幅度 -
			{
				if(B_Run)	//运行中
				{
					if(InputIndex < 7)	//调整垂直幅度
					{
						InputIndex++;
						ShowVoltage();
						WriteDelay = 250;	//写入延时8秒
					}
				}
			}

			else if(KeyCode == K_WaveUp)	//波形上移
			{
				if(B_Run)	//运行中
				{
					if(pwm1_voltage != 0)	pwm1_voltage--;
					PWMA_CCR1L = pwm1_voltage;
					WriteDelay = 250;	//写入延时8秒
				}
			}
			else if(KeyCode == K_WaveDown)	//波形下移
			{
				if(B_Run)	//运行中
				{
					if(pwm1_voltage < 250)	pwm1_voltage++;
					PWMA_CCR1L = pwm1_voltage;
					WriteDelay = 250;	//写入延时8秒
				}
			}

			else if(KeyCode == K_ShiftLeft)	//波形左移
			{
				if(!B_Run)	//停止时, 左右移动波形
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
			else if(KeyCode == K_ShiftRight)	//波形右移
			{
				if(!B_Run)	//停止时, 左右移动波形
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
			
			else if(KeyCode == K_RtnMssage)	//返回参数
			{
				ShowTimeBase();		//显示水平时基
				ShowVoltage();		//显示垂直电压
				ShowRunStop();		//显示停止/运行
				ShowPhase();		//显示触发模式(触发边沿)
				ShowTrigMode();		//显示触发方式
			}	

			KeyCode = 0;
		}
	}
}
/**********************************************/



/*************** 转义字符处理 *******************************/
void	TxData255(u8 dat)
{
	if(dat >= 0xfb)
	{
		TX_write2buff(0xfd);	//转义字符
		TX_write2buff(dat & 0x7f);
	}
	else	TX_write2buff(dat);
}


/*************** 装载串口发送缓冲 *******************************/
void TX_write2buff(u8 dat)	//写入发送缓冲，指针+1
{
	TxBuffer[TxCnt++] = dat;
}

/*************** 触发发送 *******************************/
void	TrigTx(void)	//触发发送
{
	uart_send(TxCnt);	//将要发送的数据保存在TxBuffer缓冲区中, 然后调用uart_send(n)函数触发数据发送,参数为发送的字节数. 一次最多可发送64K,函数内部会自动进行USB分包.
}

/***************** 显示触发方式函数 *****************************/
void ShowTrigMode(void)
{
	TxCnt = 0;
	TX_write2buff(0xfe);		//命令开始
	TX_write2buff(0x06);		//上传触发方式：FE 06 DATA0 FF
	TX_write2buff(TrigMode);	//触发方式。0--自动，1--普通（标准），2--单次。
	TX_write2buff(0xff);		//命令结束
	TrigTx();	//触发发送
}

/***************** 显示运行状态函数 *****************************/
void	ShowRunStop(void)
{
	TxCnt = 0;
	TX_write2buff(0xfe);		//命令开始
	TX_write2buff(0x04);		//上传运行模式：FE 04 DATA0 FF
	TX_write2buff((u8)B_Run);	//运行模式。0--停止，1--运行。
	TX_write2buff(0xff);		//命令结束
	TrigTx();	//触发发送
}


/***************** 停止运行函数 *****************************/
void	OscStop(void)
{
	CMPCR1 = 0x86;		// 关比较器中断
	TR0    = 0;			//关闭采样定时器1
	B_ADC_Busy = 0;
	B_Run = 0;
	B_RUN_REQ = 0;
	AutoTimeCnt = 0;
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
u8	const	StartTimeDanWei[]={   2,    2,     3,     3,     3,    4,     4,    4,    5,    5,     5,     6,     6,     6,    7,    7,    7,    8,    8,    8,   9};
//    DAT2：时间单位。0--1ns，1--10ns, 2--100ns, 3--1us，4--10us, 5--100us, 6--1ms，7--10ms, 8--100ms, 9--1s。

/***************** 显示起始时间函数 *****************************/
void ShowStartTime(void)
{
	u16	j;

	TxCnt = 0;
	j = StartTimeTable[SampleIndex] * Shift;
	TX_write2buff(0xfe);	//命令开始
	TX_write2buff(0x08);	//上传波形左移时间：FE 08 DATA0 DATA1 DATA2 FF
	TxData255((u8)(j >> 8));
	TxData255((u8)j);
	TX_write2buff(StartTimeDanWei[SampleIndex]);	//时间单位: 时间单位。0--1ns，1--10ns, 2--100ns, 3--1us，4--10us, 5--100us, 6--1ms，7--10ms, 8--100ms, 9--1s。
	TX_write2buff(0xff);	//命令结束
	TrigTx();	//触发发送
}



	#define	X_START		40
	#define	Y_START		25
	#define	GridColor	GREEN	//格子颜色
	#define	WaveColor	YELLOW	//波形颜色


//	P_V_C = 0;	P_V_B = 1;	P_V_A = 1;	//输入增益选择, CBA   000 001 010 011 100 101 110 111
										//				倍数   2   4   10  1   20 200  40 100
  //索引InputIndex      0   1    2    3   4    5    6    7    8   9   10
			//倍数      1   2    4   10  20   40   100  200  200 200 200
u8	const T_V_GAIN[14]={ 3,  0,   1,   2,  4,   6,   7,   5,   5,  5,  5};	//电压幅度
			//幅度     1V 500m 250m 100m 50m  25m  10m  5m  2.5m  1m 0.5m
			//幅度    10V  5V  2.5V  1V  500m 250m 100m 50m  25m 10m  5m

/************** 显示波形函数 ( 50us< 采样 <=20ms/DIV 或停止后缩放时基) ********************/
void	ShowOscope(void)
{
	u16	x,j;
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
	
	TxCnt = 0;
	TX_write2buff(0xfb);	//上传一帧数据：FB DAT0 DAT1 ..... DAT399 FF
	for(x=0; x<400; x++)	TX_write2buff(adc_tmp[x]);
	TX_write2buff(0xff);	//命令结束
	TrigTx();	//触发发送
}


/************** 实时显示波形函数(>=50ms/DIV) ********************/
void	RealShowOscope(void)
{
	u16	x;
	u8	i;

	x = adc_rd/10;
	if(x >= 400)	return;	

	i = adc_sample[adc_rd];
	if(i > 250)	i = 250;	//增加判断, 中断不判断
	TxCnt = 0;
	TX_write2buff(0xfc);	//上传一个点数据：FC DAT0 DAT1 DAT2 FF
	TxData255((u8)(x>>8));	//X轴位置高字节
	TxData255((u8)x);		//X轴位置低字节
	TX_write2buff(i);			//Y轴数值(0~250)
	TX_write2buff(0xff);	//命令结束
	TrigTx();	//触发发送
	adc_rd += 10;
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
u8	const   T_Time_DanWei[]=  {   1,    1,     1,     1,     1,     1,    2,    2,     2,    2,     2,     2,     2,     2,     2,   3,    3,    3,    3,    3,    3};

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
}

/***************** 显示时基函数 *****************************/
void	ShowTimeBase(void)
{
	TxCnt = 0;
	TX_write2buff(0xfe);	//命令开始
	TX_write2buff(0x02);	//上传时基参数: FE 02 DATA0 DATA1 DATA2 FF
	TX_write2buff((u8)(T_Time_div[SampleIndex] >> 8));
	TxData255((u8)T_Time_div[SampleIndex]);
	TX_write2buff(T_Time_DanWei[SampleIndex]);	//时间单位: 0--ns, 1--us, 2--ms, 3--s
	TX_write2buff(0xff);	//命令结束
	TrigTx();	//触发发送
}


	//InputIndex     0   1    2    3     4    5      6    7
	//InputIndex+3                 3     4    5      6    7      8    9  10   11   12   13
	// V/DIV        10V  5V  2.5V  1V  500mV 250mV 100mV 50mV
u16 const T_VOLTAGE[]={ 10000, 5000, 2500, 1000, 500, 250, 100, 50};

/***************** 显示垂直电压档位 V/DIV 函数 *****************************/
void	ShowVoltage(void)
{
	u8	i;
	TxCnt = 0;
	TX_write2buff(0xfe);	//命令开始
	TX_write2buff(0x03);	//上传垂直幅度参数: FE 03 DATA0 DATA1 DATA2 FF
	TX_write2buff((u8)(T_VOLTAGE[InputIndex] >> 8));
	TxData255((u8)T_VOLTAGE[InputIndex]);
	TX_write2buff(0x01);	//电压单位: mV
	TX_write2buff(0xff);	//命令结束
	TrigTx();	//触发发送

	i = T_V_GAIN[InputIndex];
	if(i & 0x04)	P_V_C = 1;	else P_V_C = 0;
	if(i & 0x02)	P_V_B = 1;	else P_V_B = 0;
	if(i & 0x01)	P_V_A = 1;	else P_V_A = 0;
}

/***************** 显示触发模式函数 *****************************/
void	ShowPhase(void)
{
	TxCnt = 0;
	TX_write2buff(0xfe);	//命令开始
	TX_write2buff(0x05);	//上传触发方式: FE 05 DATA0 FF
	if(B_TrigPhase)	TX_write2buff(0x00);	//  B_TrigPhase=1:上升沿, 0:下降沿.
	else			TX_write2buff(0x01);	//  DAT0：触发模式。0--上升沿，1--下降沿。
	TX_write2buff(0xff);	//命令结束
	TrigTx();	//触发发送
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
		B_32ms_rtn = 1;
	}
}

