
#ifndef __DEFINE_H__
#define __DEFINE_H__


#define	T3T4PIN		(*(unsigned char volatile far *)0x7efeac)	/* T3/T4选择寄存器  */

//                       7      6     5    4    3    2     1      0        Reset Value
//sfr CMPCR1 = 0xE6;   CMPEN  CMPIF  PIE  NIE  PIS  NIS  CMPOE  CMPRES      00000000B
#define	CMPEN	0x80	//1: 允许比较器, 0: 禁止,关闭比较器电源
#define	CMPIF	0x40	//比较器中断标志, 包括上升沿或下降沿中断, 软件清0
#define	PIE		0x20	//1: 比较结果由0变1, 产生上升沿中断
#define	NIE		0x10	//1: 比较结果由1变0, 产生下降沿中断
#define	PIS		0x08	//输入正极性选择, 0: 选择内部P3.7做正输入,           1: 由ADC_CHS[3:0]所选择的ADC输入端做正输入.
#define	NIS		0x04	//输入负极性选择, 0: 选择内部BandGap电压BGv做负输入, 1: 选择外部P3.6做输入.
#define	CMPOE	0x02	//1: 允许比较结果输出, 0: 禁止.
#define	CMPRES	0x01	//比较结果, 1: CMP+电平高于CMP-,  0: CMP+电平低于CMP-,  只读

#define	CMP_P_P37	0x00	//输入正极性选择, 0: 选择内部P3.7做正输入
#define	CMP_P_ADC	0x08	//输入正极性选择, 1: 由ADC_CHS[3:0]所选择的ADC输入端做正输入.
#define	CMP_N_GAP	0x00	//输入负极性选择, 0: 选择内部BandGap电压BGv做负输入.
#define	CMP_N_P36	0x04	//输入负极性选择, 1: 选择外部P3.6做输入.

#define	CMPO_P34()	P_SW2 &= ~0x08	//结果输出到P3.4.

//                       7        6       5  4  3  2  1  0    Reset Value
//sfr CMPCR2 = 0xE7;   INVCMPO  DISFLT       LCDTY[5:0]       00001001B
#define	INVCMPO	0x80	//1: 比较器输出IO取反,  0: 不取反
#define	DISFLT	0x40	//1: 关闭0.1uF滤波,   	0: 允许
#define	LCDTY	0x00	//0~63, 比较结果变化延时周期数

/**********************************************************/
//						   7     6       5      4     3      2      1      0    Reset Value
//sfr AUXR  = 0x8E;		T0x12 T1x12 UART_M0x6  T2R  T2_C/T T2x12 EXTRAM  S1ST2  0000,0000	//Auxiliary Register

#define 	InternalXdata_Disable()		AUXR |=  2		/* 禁止使用内部xdata, 所有访问xdata都是访问外部xdata  */
#define 	InternalXdata_Enable()		AUXR &= ~2		/* 允许使用内部xdata, 当访问的地址在内部xdata范围时, 访问内部的xadta, 当地址超过内部xdata时, 访问外部xdata  */
#define		S1_M0x6()					AUXR |=  (1<<5)	/* UART Mode0 Speed is 6x Standard       */
#define		S1_M0x1()					AUXR &= ~(1<<5)	/* default,	UART Mode0 Speed is Standard */

//====================================
#define		Timer0_16bitAutoReload()	TMOD &= ~0x03					/* 16位自动重装	*/
#define		Timer0_16bit()				TMOD  = (TMOD & ~0x03) | 0x01	/* 16位         */
#define		Timer0_8bitAutoReload()		TMOD  = (TMOD & ~0x03) | 0x02	/* 8位自动重装	*/
#define		Timer0_16bitAutoRL_NoMask()	TMOD |=  0x03		/* 16位自动重装不可屏蔽中断	*/
#define 	Timer0_Run()	 			TR0 = 1				/* 允许定时器0计数			*/
#define 	Timer0_Stop()	 			TR0 = 0				/* 禁止定时器0计数			*/
#define		Timer0_Gate_INT0_P32()		TMOD |=  (1<<3)		/* 时器0由外部INT0高电平允许定时计数 */
#define		Timer0_AsTimer()			TMOD &= ~(1<<2)		/* 时器0用做定时器	*/
#define		Timer0_AsCounter()			TMOD |=  (1<<2)		/* 时器0用做计数器	*/
#define		Timer0_AsCounterP34()		TMOD |=  (1<<2)		/* 时器0用做计数器	*/
#define 	Timer0_1T()					AUXR |=  (1<<7)		/* Timer0 clodk = fo	*/
#define 	Timer0_12T()				AUXR &= ~(1<<7)		/* Timer0 clodk = fo/12	12分频,	default	*/
#define		Timer0_CLKO_Enable()		INT_CLKO |=  1			/* 允许 T0 溢出脉冲在T0(P3.5)脚输出，Fck0 = 1/2 T0 溢出率，T0可以1T或12T。	*/
#define		Timer0_CLKO_Disable()		INT_CLKO &= ~1
#define		Timer0_CLKO_Enable_P35()	INT_CLKO |=  1			/* 允许 T0 溢出脉冲在T0(P3.5)脚输出，Fck0 = 1/2 T0 溢出率，T0可以1T或12T。	*/
#define		Timer0_CLKO_Disable_P35()	INT_CLKO &= ~1
#define 	Timer0_InterruptEnable()	ET0 = 1				/* 允许Timer1中断.*/
#define 	Timer0_InterruptDisable()	ET0 = 0				/* 禁止Timer1中断.*/

#define		T0_Load(n)					TH0 = (n) / 256,	TL0 = (n) % 256
#define		T0_Load_us_1T(n)			Timer0_AsTimer(),Timer0_1T(), Timer0_16bitAutoReload(),TH0=(65536-((MAIN_Fosc/1000)*(n)+500)/1000)/256, TL0=(65536-((MAIN_Fosc/1000)*(n)+500)/1000)%256
#define		T0_Load_us_12T(n)			Timer0_AsTimer(),Timer0_12T(),Timer0_16bitAutoReload(),TH0=(65536-((MAIN_Fosc/12000)*(n)+500)/1000)/256,TL0=(65536-((MAIN_Fosc/12000)*(n)+500)/1000)%256
#define		T0_Frequency_1T_P35(n)		ET0=0,Timer0_AsTimer(),Timer0_1T(),Timer0_16bitAutoReload(),TH0=(65536-(n/2+MAIN_Fosc/2)/(n))/256,TL0=(65536-(n/2+MAIN_Fosc/2)/(n))%256,INT_CLKO |= 1,TR0=1		/* fx=fosc/(2*M)/n,  M=1 or M=12 */
#define		T0_Frequency_12T_P35(n)		ET0=0,Timer0_AsTimer(),Timer0_12T(),Timer0_16bitAutoReload(),TH0=(65536-(n/2+MAIN_Fosc/24)/(n))/256,TL0=(65536-(n/2+MAIN_Fosc/24)/(n))%256,INT_CLKO |= 1,TR0=1	/* fx=fosc/(2*M)/n,  M=1 or M=12 */

//====================================
#define		Timer1_16bitAutoReload()	TMOD &= ~0x30					/* 16位自动重装	*/
#define		Timer1_16bit()				TMOD  = (TMOD & ~0x30) | 0x10	/* 16位			*/
#define		Timer1_8bitAutoReload()		TMOD  = (TMOD & ~0x30) | 0x20	/* 8位自动重装	*/
#define 	Timer1_Run()	 			TR1 = 1				/* 允许定时器1计数			*/
#define 	Timer1_Stop()	 			TR1 = 0				/* 禁止定时器1计数			*/
#define		Timer1_Gate_INT1_P33()		TMOD |=  (1<<7)		/* 时器1由外部INT1高电平允许定时计数	*/
#define		Timer1_AsTimer()			TMOD &= ~(1<<6)		/* 时器1用做定时器			*/
#define		Timer1_AsCounter()			TMOD |=  (1<<6)		/* 时器1用做计数器			*/
#define		Timer1_AsCounterP35()		TMOD |=  (1<<6)		/* 时器1用做计数器			*/
#define 	Timer1_1T()					AUXR |=  (1<<6)		/* Timer1 clodk = fo		*/
#define 	Timer1_12T()				AUXR &= ~(1<<6)		/* Timer1 clodk = fo/12	12分频,	default	*/
#define		Timer1_CLKO_Enable()		INT_CLKO |=  2			/* 允许 T1 溢出脉冲在T1(P3.4)脚输出，Fck1 = 1/2 T1 溢出率，T1可以1T或12T。	*/
#define		Timer1_CLKO_Disable()		INT_CLKO &= ~2
#define		Timer1_CLKO_Enable_P34()	INT_CLKO |=  2			/* 允许 T1 溢出脉冲在T1(P3.4)脚输出，Fck1 = 1/2 T1 溢出率，T1可以1T或12T。	*/
#define		Timer1_CLKO_Disable_P34()	INT_CLKO &= ~2
#define 	Timer1_InterruptEnable()	ET1 = 1				/* 允许Timer1中断.	*/
#define 	Timer1_InterruptDisable()	ET1 = 0				/* 禁止Timer1中断.	*/

#define		T1_Load(n)					TH1 = (n) / 256,	TL1 = (n) % 256
#define		T1_Load_us_1T(n)			Timer1_AsTimer(),Timer1_1T(), Timer1_16bitAutoReload(),TH1=(65536-((MAIN_Fosc/1000)*(n)+500)/1000)/256, TL1=(65536-((MAIN_Fosc/1000)*(n)+500)/1000)%256
#define		T1_Load_us_12T(n)			Timer1_AsTimer(),Timer1_12T(),Timer1_16bitAutoReload(),TH1=(65536-((MAIN_Fosc/12000)*(n)+500)/1000)/256,TL1=(65536-((MAIN_Fosc/12000)*(n)+500)/1000)%256
#define		T1_Frequency_1T_P34(n)		ET1=0,Timer1_AsTimer(),Timer1_1T(),Timer1_16bitAutoReload(),TH1=(65536-(n/2+MAIN_Fosc/2)/(n))/256,TL1=(65536-(n/2+MAIN_Fosc/2)/(n))%256,INT_CLKO |= 2,TR1=1		/* fx=fosc/(2*M)/n,  M=1 or M=12 */
#define		T1_Frequency_12T_P34(n)		ET1=0,Timer1_AsTimer(),Timer1_12T(),Timer1_16bitAutoReload(),TH1=(65536-(n/2+MAIN_Fosc/24)/(n))/256,TL1=(65536-(n/2+MAIN_Fosc/24)/(n))%256,INT_CLKO |= 2,TR1=1	/* fx=fosc/(2*M)/n,  M=1 or M=12 */

//====================================
#define 	Timer2_Run()	 			AUXR |=  (1<<4)	/* 允许定时器2计数	*/
#define 	Timer2_Stop()	 			AUXR &= ~(1<<4)	/* 禁止定时器2计数	*/
#define		Timer2_AsTimer()			AUXR &= ~(1<<3)	/* 时器2用做定时器	*/
#define		Timer2_AsCounter()			AUXR |=  (1<<3)	/* 时器2用做计数器	*/
#define		Timer2_AsCounterP31()		AUXR |=  (1<<3)	/* 时器2用做计数器	*/
#define 	Timer2_1T()					AUXR |=  (1<<2)	/* Timer0 clock = fo	*/
#define 	Timer2_12T()				AUXR &= ~(1<<2)	/* Timer0 clock = fo/12	12分频,	default	*/
#define		Timer2_CLKO_Enable()		INT_CLKO |=  4		/* 允许 T2 溢出脉冲在P1.3脚输出，Fck2 = 1/2 T2 溢出率，T2可以1T或12T。	*/
#define		Timer2_CLKO_Disable()		INT_CLKO &= ~4
#define		Timer2_CLKO_Enable_P13()	INT_CLKO |=  4		/* 允许 T2 溢出脉冲在P1.3脚输出，Fck2 = 1/2 T2 溢出率，T2可以1T或12T。	*/
#define		Timer2_CLKO_Disable_P13()	INT_CLKO &= ~4
#define 	Timer2_InterruptEnable()	IE2  |=  (1<<2)	/* 允许Timer2中断.	*/
#define 	Timer2_InterruptDisable()	IE2  &= ~(1<<2)	/* 禁止Timer2中断.	*/

#define		T2_Load(n)					TH2 = (n) / 256,	TL2 = (n) % 256
#define		T2_Load_us_1T(n)			Timer2_AsTimer(),Timer2_1T(), TH2=(65536-((MAIN_Fosc/1000)*(n)+500)/1000)/256, TL2=(65536-((MAIN_Fosc/1000)*(n)+500)/1000)%256
#define		T2_Load_us_12T(n)			Timer2_AsTimer(),Timer2_12T(),TH2=(65536-((MAIN_Fosc/12000)*(n)+500)/1000)/256,TL2=(65536-((MAIN_Fosc/12000)*(n)+500)/1000)%256
#define		T2_Frequency_1T_P13(n)		Timer2_InterruptDisable(),Timer2_AsTimer(),Timer2_1T(), TH2=(65536-(n/2+MAIN_Fosc/2)/(n))/256, TL2=(65536-(n/2+MAIN_Fosc/2)/(n))%256, Timer2_CLKO_Enable_P13(),Timer2_Run()	/* fx=fosc/(2*M)/n,  M=1 or M=12 */
#define		T2_Frequency_12T_P13(n)		Timer2_InterruptDisable(),Timer2_AsTimer(),Timer2_12T(),TH2=(65536-(n/2+MAIN_Fosc/24)/(n))/256,TL2=(65536-(n/2+MAIN_Fosc/24)/(n))%256,Timer2_CLKO_Enable_P13(),Timer2_Run()	/* fx=fosc/(2*M)/n,  M=1 or M=12 */

//====================================
#define 	Timer3_Run()	 			T4T3M |=  (1<<3)	/* 允许定时器3计数	*/
#define 	Timer3_Stop()	 			T4T3M &= ~(1<<3)	/* 禁止定时器3计数	*/
#define		Timer3_AsTimer()			T4T3M &= ~(1<<2)	/* 时器3用做定时器	*/
#define		Timer3_AsCounter()			T4T3M |=  (1<<2)	/* 时器3用做计数器, P0.5为外部脉冲	*/
#define		Timer3_AsCounterP05()		T4T3M |=  (1<<2)	/* 时器3用做计数器, P0.5为外部脉冲	*/
#define 	Timer3_1T()					T4T3M |=  (1<<1)	/* 1T模式	*/
#define 	Timer3_12T()				T4T3M &= ~(1<<1)	/* 12T模式,	default	*/
#define		Timer3_CLKO_Enable()		T4T3M |=  1			/* 允许T3溢出脉冲在T3(P0.4)脚输出，Fck = 1/2 T2 溢出率，T2可以1T或12T。	*/
#define		Timer3_CLKO_Disable()		T4T3M &= ~1			/* 禁止T3溢出脉冲在T3(P0.4)脚输出	*/
#define		Timer3_CLKO_Enable_P04()	T4T3M |=  1			/* 允许T3溢出脉冲在T3(P0.4)脚输出，Fck = 1/2 T2 溢出率，T2可以1T或12T。	*/
#define		Timer3_CLKO_Disable_P04()	T4T3M &= ~1			/* 禁止T3溢出脉冲在T3(P0.4)脚输出	*/
#define 	Timer3_InterruptEnable()	IE2  |=  (1<<5)		/* 允许Timer3中断.	*/
#define 	Timer3_InterruptDisable()	IE2  &= ~(1<<5)		/* 禁止Timer3中断.	*/

#define		T3_Load(n)					TH3 = (n) / 256,	TL3 = (n) % 256
#define		T3_Load_us_1T(n)			Timer3_AsTimer(),Timer3_1T(), TH3=(65536-((MAIN_Fosc/1000)*(n)+500)/1000)/256, TL3=(65536-((MAIN_Fosc/1000)*(n)+500)/1000)%256
#define		T3_Load_us_12T(n)			Timer3_AsTimer(),Timer3_12T(),TH3=(65536-((MAIN_Fosc/12000)*(n)+500)/1000)/256,TL3=(65536-((MAIN_Fosc/12000)*(n)+500)/1000)%256
#define		T3_Frequency_1T_P04(n)		Timer3_InterruptDisable(),Timer3_AsTimer(),Timer3_1T(), TH3=(65536-(n/2+MAIN_Fosc/2)/(n))/256, TL3=(65536-(n/2+MAIN_Fosc/2)/(n))%256, Timer3_CLKO_P04_Enable,Timer3_Run()	/* fx=fosc/(2*M)/n,  M=1 or M=12 */
#define		T3_Frequency_12T_P04(n)		Timer3_InterruptDisable(),Timer3_AsTimer(),Timer3_12T(),TH3=(65536-(n/2+MAIN_Fosc/24)/(n))/256,TL3=(65536-(n/2+MAIN_Fosc/24)/(n))%256,Timer3_CLKO_P04_Enable,Timer3_Run()	/* fx=fosc/(2*M)/n,  M=1 or M=12 */

//====================================
#define 	Timer4_Run()	 			T4T3M |=  (1<<7)	/* 允许定时器4计数	*/
#define 	Timer4_Stop()	 			T4T3M &= ~(1<<7)	/* 禁止定时器4计数	*/
#define		Timer4_AsTimer()			T4T3M &= ~(1<<6)	/* 时器4用做定时器  */
#define		Timer4_AsCounter()			T4T3M |=  (1<<6)	/* 时器4用做计数器, P0.7为外部脉冲	*/
#define		Timer4_AsCounterP07()		T4T3M |=  (1<<6)	/* 时器4用做计数器, P0.7为外部脉冲	*/
#define 	Timer4_1T()					T4T3M |=  (1<<5)	/* 1T模式	*/
#define 	Timer4_12T()				T4T3M &= ~(1<<5)	/* 12T模式,	default	*/
#define		Timer4_CLKO_Enable()		T4T3M |=  (1<<4)	/* 允许T4溢出脉冲在T4(P0.6)脚输出，Fck = 1/2 T2 溢出率，T2可以1T或12T。	*/
#define		Timer4_CLKO_Disable()		T4T3M &= ~(1<<4)	/* 禁止T4溢出脉冲在T4(P0.6)脚输出	*/
#define		Timer4_CLKO_Enable_P06()	T4T3M |=  (1<<4)	/* 允许T4溢出脉冲在T4(P0.6)脚输出，Fck = 1/2 T2 溢出率，T2可以1T或12T。	*/
#define		Timer4_CLKO_Disable_P06()	T4T3M &= ~(1<<4)	/* 禁止T4溢出脉冲在T4(P0.6)脚输出	*/
#define 	Timer4_InterruptEnable()	IE2  |=  (1<<6)		/* 允许Timer4中断.	*/
#define 	Timer4_InterruptDisable()	IE2  &= ~(1<<6)		/* 禁止Timer4中断.	*/

#define		T4_Load(n)					TH4 = (n) / 256,	TL4 = (n) % 256
#define		T4_Load_us_1T(n)			Timer4_AsTimer(),Timer4_1T(), TH4=(65536-((MAIN_Fosc/1000)*(n)+500)/1000)/256, TL4=(65536-((MAIN_Fosc/1000)*(n)+500)/1000)%256
#define		T4_Load_us_12T(n)			Timer4_AsTimer(),Timer4_12T(),TH4=(65536-((MAIN_Fosc/12000)*(n)+500)/1000)/256,TL4=(65536-((MAIN_Fosc/12000)*(n)+500)/1000)%256
#define		T4_Frequency_1T_P06(n)		Timer4_InterruptDisable(),Timer4_AsTimer(),Timer4_1T(), TH4=(65536-(n/2+MAIN_Fosc/2)/(n))/256, TL4=(65536-(n/2+MAIN_Fosc/2)/(n))%256, Timer4_CLKO_P06_Enable(),Timer4_Run()	/* fx=fosc/(2*M)/n,  M=1 or M=12 */
#define		T4_Frequency_12T_P06(n)		Timer4_InterruptDisable(),Timer4_AsTimer(),Timer4_12T(),TH4=(65536-(n/2+MAIN_Fosc/24)/(n))/256,TL4=(65536-(n/2+MAIN_Fosc/24)/(n))%256,Timer4_CLKO_P06_Enable(),Timer4_Run()	/* fx=fosc/(2*M)/n,  M=1 or M=12 */
//====================================================================================================================

/**********************************************************/
#define NOP1()  _nop_()
#define NOP2()  NOP1(),NOP1()
#define NOP3()  NOP2(),NOP1()
#define NOP4()  NOP3(),NOP1()
#define NOP5()  NOP4(),NOP1()
#define NOP6()  NOP5(),NOP1()
#define NOP7()  NOP6(),NOP1()
#define NOP8()  NOP7(),NOP1()
#define NOP9()  NOP8(),NOP1()
#define NOP10() NOP9(),NOP1()
#define NOP11() NOP10(),NOP1()
#define NOP12() NOP11(),NOP1()
#define NOP13() NOP12(),NOP1()
#define NOP14() NOP13(),NOP1()
#define NOP15() NOP14(),NOP1()
#define NOP16() NOP15(),NOP1()
#define NOP17() NOP16(),NOP1()
#define NOP18() NOP17(),NOP1()
#define NOP19() NOP18(),NOP1()
#define NOP20() NOP19(),NOP1()
#define NOP21() NOP20(),NOP1()
#define NOP22() NOP21(),NOP1()
#define NOP23() NOP22(),NOP1()
#define NOP24() NOP23(),NOP1()
#define NOP25() NOP24(),NOP1()
#define NOP26() NOP25(),NOP1()
#define NOP27() NOP26(),NOP1()
#define NOP28() NOP27(),NOP1()
#define NOP29() NOP28(),NOP1()
#define NOP30() NOP29(),NOP1()
#define NOP31() NOP30(),NOP1()
#define NOP32() NOP31(),NOP1()
#define NOP33() NOP32(),NOP1()
#define NOP34() NOP33(),NOP1()
#define NOP35() NOP34(),NOP1()
#define NOP36() NOP35(),NOP1()
#define NOP37() NOP36(),NOP1()
#define NOP38() NOP37(),NOP1()
#define NOP39() NOP38(),NOP1()
#define NOP40() NOP39(),NOP1()
#define NOP(N)  NOP##N()


/**********************************************/
#define	Pin0		0x01	//IO引脚 Px.0
#define	Pin1		0x02	//IO引脚 Px.1
#define	Pin2		0x04	//IO引脚 Px.2
#define	Pin3		0x08	//IO引脚 Px.3
#define	Pin4		0x10	//IO引脚 Px.4
#define	Pin5		0x20	//IO引脚 Px.5
#define	Pin6		0x40	//IO引脚 Px.6
#define	Pin7		0x80	//IO引脚 Px.7
#define	PinAll		0xFF	//IO所有引脚

#define	GPIO_Pin_0		0x01	//IO引脚 Px.0
#define	GPIO_Pin_1		0x02	//IO引脚 Px.1
#define	GPIO_Pin_2		0x04	//IO引脚 Px.2
#define	GPIO_Pin_3		0x08	//IO引脚 Px.3
#define	GPIO_Pin_4		0x10	//IO引脚 Px.4
#define	GPIO_Pin_5		0x20	//IO引脚 Px.5
#define	GPIO_Pin_6		0x40	//IO引脚 Px.6
#define	GPIO_Pin_7		0x80	//IO引脚 Px.7
#define	GPIO_Pin_All	0xFF	//IO所有引脚

#define	GPIO_PullUp		0	//上拉准双向口
#define	GPIO_HighZ		1	//浮空输入
#define	GPIO_OUT_OD		2	//开漏输出
#define	GPIO_OUT_PP		3	//推挽输出

#define	GPIO_P0			0		//
#define	GPIO_P1			1
#define	GPIO_P2			2
#define	GPIO_P3			3
#define	GPIO_P4			4
#define	GPIO_P5			5
#define	GPIO_P6			6
#define	GPIO_P7			7

#define P0n_standard(bitn)			P0M1 &= ~(bitn),	P0M0 &= ~(bitn)	/* 00  */
#define P0n_push_pull(bitn)			P0M1 &= ~(bitn),	P0M0 |=  (bitn)	/* 01  */
#define P0n_pure_input(bitn)		P0M1 |=  (bitn),	P0M0 &= ~(bitn)	/* 10  */
#define P0n_open_drain(bitn)		P0M1 |=  (bitn),	P0M0 |=  (bitn)	/* 11  */

#define P1n_standard(bitn)			P1M1 &= ~(bitn),	P1M0 &= ~(bitn)
#define P1n_push_pull(bitn)			P1M1 &= ~(bitn),	P1M0 |=  (bitn)
#define P1n_pure_input(bitn)		P1M1 |=  (bitn),	P1M0 &= ~(bitn)
#define P1n_open_drain(bitn)		P1M1 |=  (bitn),	P1M0 |=  (bitn)

#define P2n_standard(bitn)			P2M1 &= ~(bitn),	P2M0 &= ~(bitn)
#define P2n_push_pull(bitn)			P2M1 &= ~(bitn),	P2M0 |=  (bitn)
#define P2n_pure_input(bitn)		P2M1 |=  (bitn),	P2M0 &= ~(bitn)
#define P2n_open_drain(bitn)		P2M1 |=  (bitn),	P2M0 |=  (bitn)

#define P3n_standard(bitn)			P3M1 &= ~(bitn),	P3M0 &= ~(bitn)
#define P3n_push_pull(bitn)			P3M1 &= ~(bitn),	P3M0 |=  (bitn)
#define P3n_pure_input(bitn)		P3M1 |=  (bitn),	P3M0 &= ~(bitn)
#define P3n_open_drain(bitn)		P3M1 |=  (bitn),	P3M0 |=  (bitn)

#define P4n_standard(bitn)			P4M1 &= ~(bitn),	P4M0 &= ~(bitn)
#define P4n_push_pull(bitn)			P4M1 &= ~(bitn),	P4M0 |=  (bitn)
#define P4n_pure_input(bitn)		P4M1 |=  (bitn),	P4M0 &= ~(bitn)
#define P4n_open_drain(bitn)		P4M1 |=  (bitn),	P4M0 |=  (bitn)

#define P5n_standard(bitn)			P5M1 &= ~(bitn),	P5M0 &= ~(bitn)
#define P5n_push_pull(bitn)			P5M1 &= ~(bitn),	P5M0 |=  (bitn)
#define P5n_pure_input(bitn)		P5M1 |=  (bitn),	P5M0 &= ~(bitn)
#define P5n_open_drain(bitn)		P5M1 |=  (bitn),	P5M0 |=  (bitn)

#define P6n_standard(bitn)			P6M1 &= ~(bitn),	P6M0 &= ~(bitn)
#define P6n_push_pull(bitn)			P6M1 &= ~(bitn),	P6M0 |=  (bitn)
#define P6n_pure_input(bitn)		P6M1 |=  (bitn),	P6M0 &= ~(bitn)
#define P6n_open_drain(bitn)		P6M1 |=  (bitn),	P6M0 |=  (bitn)

#define P7n_standard(bitn)			P7M1 &= ~(bitn),	P7M0 &= ~(bitn)
#define P7n_push_pull(bitn)			P7M1 &= ~(bitn),	P7M0 |=  (bitn)
#define P7n_pure_input(bitn)		P7M1 |=  (bitn),	P7M0 &= ~(bitn)
#define P7n_open_drain(bitn)		P7M1 |=  (bitn),	P7M0 |=  (bitn)


/****************************************************************/

#endif