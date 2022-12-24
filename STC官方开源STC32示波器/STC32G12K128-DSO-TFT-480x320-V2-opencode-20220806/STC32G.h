
/*------------------------------------------------------------------*/
/* --- STC MCU International Limited -------------------------------*/
/* --- STC 1T Series MCU Demo --------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ---------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ---------------------*/
/* --- Web: www.stcmcudata.com -------------------------------------*/
/* --- QQ:  800003751 ----------------------------------------------*/
/* If you want to use the program or the program referenced in the  */
/* article, please specify in which data and procedures from STC    */
/*------------------------------------------------------------------*/

#ifndef	_STC32G_H
#define	_STC32G_H

#include <intrins.h>

/*  BYTE Registers  */
sfr P0    = 0x80;
sfr SP    = 0x81;
sfr DPL   = 0x82;
sfr DPH   = 0x83;
sfr DPXL  = 0x84;
sfr	SPH   = 0x85;
sfr PCON  = 0x87;

sfr TCON = 0x88;
sfr TMOD = 0x89;
sfr TL0  = 0x8A;
sfr TL1  = 0x8B;
sfr TH0  = 0x8C;
sfr TH1  = 0x8D;
sfr	AUXR = 0x8E;
sfr INTCLKO  = 0x8F;

sfr P1    = 0x90;
sfr P1M1  = 0x91;	//P1M1.n,P1M0.n 	=00--->Standard,	01--->push-pull		ʵ����1T�Ķ�һ��
sfr P1M0  = 0x92;	//					=10--->pure input,	11--->open drain
sfr P0M1  = 0x93;	//P0M1.n,P0M0.n 	=00--->Standard,	01--->push-pull
sfr P0M0  = 0x94;	//					=10--->pure input,	11--->open drain
sfr P2M1  = 0x95;	//P2M1.n,P2M0.n 	=00--->Standard,	01--->push-pull
sfr P2M0  = 0x96;	//					=10--->pure input,	11--->open drain
sfr	AUXR2 = 0x97;

sfr SCON  = 0x98;  //����1���ƼĴ���
sfr SBUF  = 0x99;  //����1���ݼĴ���
sfr S2CON = 0x9A;  //����2���ƼĴ���
sfr S2BUF = 0x9B;  //����2���ݼĴ���
sfr IRCBAND = 0x9D;	//IRCƵ��ѡ����
sfr LIRTRIM = 0x9E;	//IRCƵ��΢���Ĵ���
sfr IRTRIM  = 0x9F;	//IRCƵ�ʵ����Ĵ���

sfr P2    = 0xA0;
sfr BUS_SPEED = 0xA1;
sfr P_SW1 = 0xA2;	//����˿��л��Ĵ���1

sfr IE    = 0xA8;
sfr SADDR = 0xA9;
sfr WKTCL = 0xAA;  //���Ѷ�ʱ�����ֽ�
sfr WKTCH = 0xAB;  //���Ѷ�ʱ�����ֽ�
sfr	S3CON = 0xAC;  //����4���ƼĴ���
sfr S3BUF = 0xAD;  //����4���ݼĴ���
sfr TA    = 0xAE;  //DPTRʱ����ƼĴ���
sfr IE2   = 0xAF;  //�ж�����Ĵ���2

sfr P3    = 0xB0;
sfr P3M1  = 0xB1;	//P3M1.n,P3M0.n 	=00--->Standard,	01--->push-pull
sfr P3M0  = 0xB2;	//					=10--->pure input,	11--->open drain
sfr P4M1  = 0xB3;	//P4M1.n,P4M0.n 	=00--->Standard,	01--->push-pull
sfr P4M0  = 0xB4;	//					=10--->pure input,	11--->open drain
sfr IP2   = 0xB5;	//
sfr IP2H  = 0xB6;	//
sfr IPH   = 0xB7;

sfr IP        = 0xB8;
sfr SADEN     = 0xB9;
sfr	P_SW2     = 0xBA;	//����˿��л��Ĵ���2
sfr	P_SW3     = 0xBB;	//����˿��л��Ĵ���3
sfr ADC_CONTR = 0xBC;	//ADC���ƼĴ���
sfr ADC_RES   = 0xBD;	//ADC������ֽ�
sfr ADC_RESL  = 0xBE;	//ADC������ֽ�

sfr P4        = 0xC0;
sfr WDT_CONTR = 0xC1;
sfr IAP_DATA  = 0xC2;
sfr IAP_ADDRH = 0xC3;
sfr IAP_ADDRL = 0xC4;
sfr IAP_CMD   = 0xC5;
sfr IAP_TRIG  = 0xC6;
sfr IAP_CONTR = 0xC7;

sfr ISP_DATA  = 0xC2;
sfr ISP_ADDRH = 0xC3;
sfr ISP_ADDRL = 0xC4;
sfr ISP_CMD   = 0xC5;
sfr ISP_TRIG  = 0xC6;
sfr ISP_CONTR = 0xC7;

sfr P5     = 0xC8;	//
sfr P5M1   = 0xC9;	//	P5M1.n,P5M0.n 	=00--->Standard,	01--->push-pull
sfr P5M0   = 0xCA;	//					=10--->pure input,	11--->open drain
sfr P6M1   = 0xCB;	//	P6M1.n,P6M0.n 	=00--->Standard,	01--->push-pull
sfr P6M0   = 0xCC;	//					=10--->pure input,	11--->open drain
sfr SPSTAT = 0xCD;	//SPI״̬�Ĵ���
sfr SPCTL  = 0xCE;	//SPI���ƼĴ���
sfr SPDAT  = 0xCF;	//SPI���ݼĴ���

sfr PSW    = 0xD0;	//����״̬�Ĵ���
sfr	PSW1   = 0xD1;	//����״̬�Ĵ���1
sfr	T4H    = 0xD2;
sfr	T4L    = 0xD3;
sfr	T3H    = 0xD4;
sfr	T3L    = 0xD5;
sfr	T2H    = 0xD6;
sfr	T2L    = 0xD7;

sfr	TH4    = 0xD2;
sfr	TL4    = 0xD3;
sfr	TH3    = 0xD4;
sfr	TL3    = 0xD5;
sfr	TH2    = 0xD6;
sfr	TL2    = 0xD7;

sfr	IAP_DATA1  = 0xD9;  //IAP���ݼĴ���1
sfr	IAP_DATA2  = 0xDA;  //IAP���ݼĴ���2
sfr	IAP_DATA3  = 0xDB;  //IAP���ݼĴ���3
sfr USBCLK     = 0xDC;  //USBʱ�ӿ��ƼĴ���
sfr T4T3M      = 0xDD;
sfr	ADCCFG     = 0xDE;  //ADC���üĴ���
sfr	IP3        = 0xDF;  //�ж����ȼ����ƼĴ���3

sfr ACC    = 0xE0;
sfr	P7M1   = 0xE1;	//	P7M1.n,P7M0.n 	=00--->Standard,	01--->push-pull
sfr	P7M0   = 0xE2;	//					=10--->pure input,	11--->open drain
sfr	DPS    = 0xE3;	//DPTRָ��ѡ��Ĵ���
sfr	DPL1   = 0xE4;	//��2������ָ����ֽ�
sfr	DPH1   = 0xE5;	//��2������ָ����ֽ�
sfr	CMPCR1 = 0xE6;	//�Ƚ������ƼĴ���1
sfr	CMPCR2 = 0xE7;	//�Ƚ������ƼĴ���2

sfr	P6     = 0xE8;
sfr	WTST   = 0xE9;	//�����ȡ���ƼĴ���
sfr	CKCON  = 0xEA;  //XRAM���ƼĴ���
sfr	MXAX   = 0xEB;  //MOVX��չ��ַ�Ĵ���
sfr USBDAT = 0xEC;	//USB���ݼĴ���
sfr	DMAIR  = 0xED;  //FMU DMAָ��Ĵ���
sfr	IP3H   = 0xEE;	//���ж����ȼ����ƼĴ���3
sfr	AUXINTIF = 0xEF;	//��չ�ⲿ�жϱ�־�Ĵ��� B6-INT4IF, B5-INT3IF, B4-INT2IF, B2-T4IF, B1-T3IF, B0-T2IF

sfr B        = 0xF0;
sfr	CANICR   = 0xF1;  //CANBUS�жϿ��ƼĴ���
sfr USBCON   = 0xF4;  //USB���ƼĴ�����
sfr	IAP_TPS  = 0xF5;  //IAP�ȴ�ʱ����ƼĴ���
sfr	IAP_ADDRE  = 0xF6;  //IAP��չ�ߵ�ַ�Ĵ���
sfr	ICHE     = 0xF7;  //CACHE���ƼĴ���

sfr	P7       = 0xF8;
sfr	LINICR   = 0xF9;  //LINBUS�жϿ��ƼĴ���
sfr	LINAR    = 0xFA;  //LINBUS��ַ�Ĵ���
sfr	LINDR    = 0xFB;  //LINBUS���ݼĴ���
sfr USBADR   = 0xFC;  //USB��ַ�Ĵ���
sfr	S4CON    = 0xFD;  //����4���ƼĴ���
sfr	S4BUF    = 0xFE;  //����4���ݼĴ���
sfr	RSTCFG   = 0xFF;  //��λ���üĴ���

//=============================================================================================================
#define DMA_M2M_CFG     (*(unsigned char volatile far *)0x7efa00)	/*  M2M_DMA���üĴ��� */
#define DMA_M2M_CR      (*(unsigned char volatile far *)0x7efa01)	/*  M2M_DMA���ƼĴ��� */
#define DMA_M2M_STA     (*(unsigned char volatile far *)0x7efa02)	/*  M2M_DMA״̬�Ĵ��� */
#define DMA_M2M_AMT     (*(unsigned char volatile far *)0x7efa03)	/*  M2M_DMA�������ֽ��� */
#define DMA_M2M_DONE    (*(unsigned char volatile far *)0x7efa04)	/*  M2M_DMA��������ֽ��� */
#define DMA_M2M_TXAH    (*(unsigned char volatile far *)0x7efa05)	/*  M2M_DMA���͸ߵ�ַ */
#define DMA_M2M_TXAL    (*(unsigned char volatile far *)0x7efa06)	/*  M2M_DMA���͵͵�ַ */
#define DMA_M2M_RXAH    (*(unsigned char volatile far *)0x7efa07)	/*  M2M_DMA���ոߵ�ַ */
#define DMA_M2M_RXAL    (*(unsigned char volatile far *)0x7efa08)		/*  M2M_DMA���յص�ַ */

#define DMA_ADC_CFG     (*(unsigned char volatile far *)0x7efa10)	/*  ADC_DMA���üĴ��� */
#define DMA_ADC_CR      (*(unsigned char volatile far *)0x7efa11)	/*  ADC_DMA���ƼĴ��� */
#define DMA_ADC_STA     (*(unsigned char volatile far *)0x7efa12)	/*  ADC_DMA״̬�Ĵ��� */
#define DMA_ADC_RXAH    (*(unsigned char volatile far *)0x7efa17)	/*  ADC_DMA���ոߵ�ַ */
#define DMA_ADC_RXAL    (*(unsigned char volatile far *)0x7efa18)	/*  ADC_DMA���յص�ַ */
#define DMA_ADC_CFG2    (*(unsigned char volatile far *)0x7efa19)	/*  ADC_DMA���üĴ���2 */
#define DMA_ADC_CHSW0   (*(unsigned char volatile far *)0x7efa1a)	/*  ADC_DMAͨ��ʹ�ܼĴ���0 */
#define DMA_ADC_CHSW1   (*(unsigned char volatile far *)0x7efa1b)	/*  ADC_DMAͨ��ʹ�ܼĴ���1 */

#define DMA_SPI_CFG     (*(unsigned char volatile far *)0x7efa20)	/*  SPI_DMA���üĴ��� */
#define DMA_SPI_CR      (*(unsigned char volatile far *)0x7efa21)	/*  SPI_DMA���ƼĴ��� */
#define DMA_SPI_STA     (*(unsigned char volatile far *)0x7efa22)	/*  SPI_DMA״̬�Ĵ��� */
#define DMA_SPI_AMT     (*(unsigned char volatile far *)0x7efa23)	/*  SPI_DMA�������ֽ��� */
#define DMA_SPI_DONE    (*(unsigned char volatile far *)0x7efa24)	/*  SPI_DMA��������ֽ��� */
#define DMA_SPI_TXAH    (*(unsigned char volatile far *)0x7efa25)	/*  SPI_DMA���͸ߵ�ַ */
#define DMA_SPI_TXAL    (*(unsigned char volatile far *)0x7efa26)	/*  SPI_DMA���͵͵�ַ */
#define DMA_SPI_RXAH    (*(unsigned char volatile far *)0x7efa27)	/*  SPI_DMA���ոߵ�ַ */
#define DMA_SPI_RXAL    (*(unsigned char volatile far *)0x7efa28)	/*  SPI_DMA���յص�ַ */
#define DMA_SPI_CFG2    (*(unsigned char volatile far *)0x7efa29)	/*  SPI_DMA���üĴ���2 */

#define DMA_UR1T_CFG    (*(unsigned char volatile far *)0x7efa30)	/*  UR1T_DMA���üĴ��� */
#define DMA_UR1T_CR     (*(unsigned char volatile far *)0x7efa31)	/*  UR1T_DMA���ƼĴ��� */
#define DMA_UR1T_STA    (*(unsigned char volatile far *)0x7efa32)	/*  UR1T_DMA״̬�Ĵ��� */
#define DMA_UR1T_AMT    (*(unsigned char volatile far *)0x7efa33)	/*  UR1T_DMA�������ֽ��� */
#define DMA_UR1T_DONE   (*(unsigned char volatile far *)0x7efa34)	/*  UR1T_DMA��������ֽ��� */
#define DMA_UR1T_TXAH   (*(unsigned char volatile far *)0x7efa35)	/*  UR1T_DMA���͸ߵ�ַ */
#define DMA_UR1T_TXAL   (*(unsigned char volatile far *)0x7efa36)	/*  UR1T_DMA���͵͵�ַ */
#define DMA_UR1R_CFG    (*(unsigned char volatile far *)0x7efa38)	/*  UR1R_DMA���üĴ��� */
#define DMA_UR1R_CR     (*(unsigned char volatile far *)0x7efa39)	/*  UR1R_DMA���ƼĴ��� */
#define DMA_UR1R_STA    (*(unsigned char volatile far *)0x7efa3a)	/*  UR1R_DMA״̬�Ĵ��� */
#define DMA_UR1R_AMT    (*(unsigned char volatile far *)0x7efa3b)	/*  UR1R_DMA�������ֽ��� */
#define DMA_UR1R_DONE   (*(unsigned char volatile far *)0x7efa3c)	/*  UR1R_DMA��������ֽ��� */
#define DMA_UR1R_TXAH   (*(unsigned char volatile far *)0x7efa3d)	/*  UR1R_DMA���͸ߵ�ַ */
#define DMA_UR1R_TXAL   (*(unsigned char volatile far *)0x7efa3e)	/*  UR1R_DMA���͵͵�ַ */

#define DMA_UR2T_CFG    (*(unsigned char volatile far *)0x7efa40)	/*  UR2T_DMA���üĴ��� */
#define DMA_UR2T_CR     (*(unsigned char volatile far *)0x7efa41)	/*  UR2T_DMA���ƼĴ��� */
#define DMA_UR2T_STA    (*(unsigned char volatile far *)0x7efa42)	/*  UR2T_DMA״̬�Ĵ��� */
#define DMA_UR2T_AMT    (*(unsigned char volatile far *)0x7efa43)	/*  UR2T_DMA�������ֽ��� */
#define DMA_UR2T_DONE   (*(unsigned char volatile far *)0x7efa44)	/*  UR2T_DMA��������ֽ��� */
#define DMA_UR2T_TXAH   (*(unsigned char volatile far *)0x7efa45)	/*  UR2T_DMA���͸ߵ�ַ */
#define DMA_UR2T_TXAL   (*(unsigned char volatile far *)0x7efa46)	/*  UR2T_DMA���͵͵�ַ */
#define DMA_UR2R_CFG    (*(unsigned char volatile far *)0x7efa48)	/*  UR2R_DMA���üĴ��� */
#define DMA_UR2R_CR     (*(unsigned char volatile far *)0x7efa49)	/*  UR2R_DMA���ƼĴ��� */
#define DMA_UR2R_STA    (*(unsigned char volatile far *)0x7efa4a)	/*  UR2R_DMA״̬�Ĵ��� */
#define DMA_UR2R_AMT    (*(unsigned char volatile far *)0x7efa4b)	/*  UR2R_DMA�������ֽ��� */
#define DMA_UR2R_DONE   (*(unsigned char volatile far *)0x7efa4c)	/*  UR2R_DMA��������ֽ��� */
#define DMA_UR2R_TXAH   (*(unsigned char volatile far *)0x7efa4d)	/*  UR2R_DMA���͸ߵ�ַ */
#define DMA_UR2R_TXAL   (*(unsigned char volatile far *)0x7efa4e)	/*  UR2R_DMA���͵͵�ַ */

#define DMA_UR3T_CFG    (*(unsigned char volatile far *)0x7efa50)	/*  UR3T_DMA���üĴ��� */
#define DMA_UR3T_CR     (*(unsigned char volatile far *)0x7efa51)	/*  UR3T_DMA���ƼĴ��� */
#define DMA_UR3T_STA    (*(unsigned char volatile far *)0x7efa52)	/*  UR3T_DMA״̬�Ĵ��� */
#define DMA_UR3T_AMT    (*(unsigned char volatile far *)0x7efa53)	/*  UR3T_DMA�������ֽ��� */
#define DMA_UR3T_DONE   (*(unsigned char volatile far *)0x7efa54)	/*  UR3T_DMA��������ֽ��� */
#define DMA_UR3T_TXAH   (*(unsigned char volatile far *)0x7efa55)	/*  UR3T_DMA���͸ߵ�ַ */
#define DMA_UR3T_TXAL   (*(unsigned char volatile far *)0x7efa56)	/*  UR3T_DMA���͵͵�ַ */
#define DMA_UR3R_CFG    (*(unsigned char volatile far *)0x7efa58)	/*  UR3R_DMA���üĴ��� */
#define DMA_UR3R_CR     (*(unsigned char volatile far *)0x7efa59)	/*  UR3R_DMA���ƼĴ��� */
#define DMA_UR3R_STA    (*(unsigned char volatile far *)0x7efa5a)	/*  UR3R_DMA״̬�Ĵ��� */
#define DMA_UR3R_AMT    (*(unsigned char volatile far *)0x7efa5b)	/*  UR3R_DMA�������ֽ��� */
#define DMA_UR3R_DONE   (*(unsigned char volatile far *)0x7efa5c)	/*  UR3R_DMA��������ֽ��� */
#define DMA_UR3R_TXAH   (*(unsigned char volatile far *)0x7efa5d)	/*  UR3R_DMA���͸ߵ�ַ */
#define DMA_UR3R_TXAL   (*(unsigned char volatile far *)0x7efa5e)	/*  UR3R_DMA���͵͵�ַ */

#define DMA_UR4T_CFG    (*(unsigned char volatile far *)0x7efa60)	/*  UR4T_DMA���üĴ��� */
#define DMA_UR4T_CR     (*(unsigned char volatile far *)0x7efa61)	/*  UR4T_DMA���ƼĴ��� */
#define DMA_UR4T_STA    (*(unsigned char volatile far *)0x7efa62)	/*  UR4T_DMA״̬�Ĵ��� */
#define DMA_UR4T_AMT    (*(unsigned char volatile far *)0x7efa63)	/*  UR4T_DMA�������ֽ��� */
#define DMA_UR4T_DONE   (*(unsigned char volatile far *)0x7efa64)	/*  UR4T_DMA��������ֽ��� */
#define DMA_UR4T_TXAH   (*(unsigned char volatile far *)0x7efa65)	/*  UR4T_DMA���͸ߵ�ַ */
#define DMA_UR4T_TXAL   (*(unsigned char volatile far *)0x7efa66)	/*  UR4T_DMA���͵͵�ַ */
#define DMA_UR4R_CFG    (*(unsigned char volatile far *)0x7efa68)	/*  UR4R_DMA���üĴ��� */
#define DMA_UR4R_CR     (*(unsigned char volatile far *)0x7efa69)	/*  UR4R_DMA���ƼĴ��� */
#define DMA_UR4R_STA    (*(unsigned char volatile far *)0x7efa6a)	/*  UR4R_DMA״̬�Ĵ��� */
#define DMA_UR4R_AMT    (*(unsigned char volatile far *)0x7efa6b)	/*  UR4R_DMA�������ֽ��� */
#define DMA_UR4R_DONE   (*(unsigned char volatile far *)0x7efa6c)	/*  UR4R_DMA��������ֽ��� */
#define DMA_UR4R_TXAH   (*(unsigned char volatile far *)0x7efa6d)	/*  UR4R_DMA���͸ߵ�ַ */
#define DMA_UR4R_TXAL   (*(unsigned char volatile far *)0x7efa6e)	/*  UR4R_DMA���͵͵�ַ */

#define DMA_LCM_CFG     (*(unsigned char volatile far *)0x7efa70)	/*  LCM_DMA���üĴ��� */
#define DMA_LCM_CR      (*(unsigned char volatile far *)0x7efa71)	/*  LCM_DMA���ƼĴ��� */
#define DMA_LCM_STA     (*(unsigned char volatile far *)0x7efa72)	/*  LCM_DMA״̬�Ĵ��� */
#define DMA_LCM_AMT     (*(unsigned char volatile far *)0x7efa73)	/*  LCM_DMA�������ֽ��� */
#define DMA_LCM_DONE    (*(unsigned char volatile far *)0x7efa74)	/*  LCM_DMA��������ֽ��� */
#define DMA_LCM_TXAH    (*(unsigned char volatile far *)0x7efa75)	/*  LCM_DMA���͸ߵ�ַ */
#define DMA_LCM_TXAL    (*(unsigned char volatile far *)0x7efa76)	/*  LCM_DMA���͵͵�ַ */
#define DMA_LCM_RXAH    (*(unsigned char volatile far *)0x7efa77)	/*  LCM_DMA���ոߵ�ַ */
#define DMA_LCM_RXAL    (*(unsigned char volatile far *)0x7efa78)	/*  LCM_DMA���յص�ַ */

#define DMA_M2M_AMTH    (*(unsigned char volatile far *)0x7efa80)	/*  M2M_DMA�������ֽ��� */
#define DMA_M2M_DONEH   (*(unsigned char volatile far *)0x7efa81)	/*  M2M_DMA��������ֽ��� */
#define DMA_SPI_AMTH    (*(unsigned char volatile far *)0x7efa84)	/*  SPI_DMA�������ֽ��� */
#define DMA_SPI_DONEH   (*(unsigned char volatile far *)0x7efa85)	/*  SPI_DMA��������ֽ��� */
#define DMA_LCM_AMTH    (*(unsigned char volatile far *)0x7efa86)	/*  LCM_DMA�������ֽ��� */
#define DMA_LCM_DONEH   (*(unsigned char volatile far *)0x7efa87)	/*  LCM_DMA��������ֽ��� */
#define DMA_UR1T_AMTH   (*(unsigned char volatile far *)0x7efa88)	/*  UR1T_DMA�������ֽ��� */
#define DMA_UR1T_DONEH  (*(unsigned char volatile far *)0x7efa89)	/*  UR1T_DMA��������ֽ��� */
#define DMA_UR1R_AMTH   (*(unsigned char volatile far *)0x7efa8a)	/*  UR1R_DMA�������ֽ��� */
#define DMA_UR1R_DONEH  (*(unsigned char volatile far *)0x7efa8b)	/*  UR1R_DMA��������ֽ��� */
#define DMA_UR2T_AMTH   (*(unsigned char volatile far *)0x7efa8c)	/*  UR2T_DMA�������ֽ��� */
#define DMA_UR2T_DONEH  (*(unsigned char volatile far *)0x7efa8d)	/*  UR2T_DMA��������ֽ��� */
#define DMA_UR2R_AMTH   (*(unsigned char volatile far *)0x7efa8e)	/*  UR2R_DMA�������ֽ��� */
#define DMA_UR2R_DONEH  (*(unsigned char volatile far *)0x7efa8f)	/*  UR2R_DMA��������ֽ��� */
#define DMA_UR3T_AMTH   (*(unsigned char volatile far *)0x7efa90)	/*  UR3T_DMA�������ֽ��� */
#define DMA_UR3T_DONEH  (*(unsigned char volatile far *)0x7efa91)	/*  UR3T_DMA��������ֽ��� */
#define DMA_UR3R_AMTH   (*(unsigned char volatile far *)0x7efa92)	/*  UR3R_DMA�������ֽ��� */
#define DMA_UR3R_DONEH  (*(unsigned char volatile far *)0x7efa93)	/*  UR3R_DMA��������ֽ��� */
#define DMA_UR4T_AMTH   (*(unsigned char volatile far *)0x7efa94)	/*  UR4T_DMA�������ֽ��� */
#define DMA_UR4T_DONEH  (*(unsigned char volatile far *)0x7efa95)	/*  UR4T_DMA��������ֽ��� */
#define DMA_UR4R_AMTH   (*(unsigned char volatile far *)0x7efa96)	/*  UR4R_DMA�������ֽ��� */
#define DMA_UR4R_DONEH  (*(unsigned char volatile far *)0x7efa97)	/*  UR4R_DMA��������ֽ��� */

#define DMA_I2CT_CFG    (*(unsigned char volatile far *)0x7efa98)	/*  I2CT_DMA���üĴ��� */
#define DMA_I2CT_CR     (*(unsigned char volatile far *)0x7efa99)	/*  I2CT_DMA���ƼĴ��� */
#define DMA_I2CT_STA    (*(unsigned char volatile far *)0x7efa9a)	/*  I2CT_DMA״̬�Ĵ��� */
#define DMA_I2CT_AMT    (*(unsigned char volatile far *)0x7efa9b)	/*  I2CT_DMA�������ֽ���   */
#define DMA_I2CT_DONE   (*(unsigned char volatile far *)0x7efa9c)	/*  I2CT_DMA��������ֽ��� */
#define DMA_I2CT_TXAH   (*(unsigned char volatile far *)0x7efa9d)	/*  I2CT_DMA���͸ߵ�ַ */
#define DMA_I2CT_TXAL   (*(unsigned char volatile far *)0x7efa9e)	/*  I2CT_DMA���͵͵�ַ */
#define DMA_I2CR_CFG    (*(unsigned char volatile far *)0x7efaa0)	/*  I2CR_DMA���üĴ��� */
#define DMA_I2CR_CR     (*(unsigned char volatile far *)0x7efaa1)	/*  I2CR_DMA���ƼĴ��� */
#define DMA_I2CR_STA    (*(unsigned char volatile far *)0x7efaa2)	/*  I2CR_DMA״̬�Ĵ��� */
#define DMA_I2CR_AMT    (*(unsigned char volatile far *)0x7efaa3)	/*  I2CR_DMA�������ֽ���   */
#define DMA_I2CR_DONE   (*(unsigned char volatile far *)0x7efaa4)	/*  I2CR_DMA��������ֽ��� */
#define DMA_I2CR_TXAH   (*(unsigned char volatile far *)0x7efaa5)	/*  I2CR_DMA���͸ߵ�ַ */
#define DMA_I2CR_TXAL   (*(unsigned char volatile far *)0x7efaa6)	/*  I2CR_DMA���͵͵�ַ */

#define DMA_I2CT_AMTH   (*(unsigned char volatile far *)0x7efaa8)	/*  I2CT_DMA�������ֽ���   */
#define DMA_I2CT_DONEH  (*(unsigned char volatile far *)0x7efaa9)	/*  I2CT_DMA��������ֽ��� */
#define DMA_I2CR_AMTH   (*(unsigned char volatile far *)0x7efaaa)	/*  I2CR_DMA�������ֽ���   */
#define DMA_I2CR_DONEH  (*(unsigned char volatile far *)0x7efaab)	/*  I2CR_DMA��������ֽ��� */
#define DMA_I2C_CR      (*(unsigned char volatile far *)0x7efaad)	/*  I2C_DMA���ƼĴ��� */
#define DMA_I2C_ST1     (*(unsigned char volatile far *)0x7efaae)	/*  I2C_DMA״̬�Ĵ��� */
#define DMA_I2C_ST2     (*(unsigned char volatile far *)0x7efaaf)	/*  I2C_DMA״̬�Ĵ��� */

#define DMA_I2ST_CFG    (*(unsigned char volatile far *)0x7efab0)	/*  I2ST_DMA���üĴ��� */
#define DMA_I2ST_CR     (*(unsigned char volatile far *)0x7efab1)	/*  I2ST_DMA���ƼĴ��� */
#define DMA_I2ST_STA    (*(unsigned char volatile far *)0x7efab2)	/*  I2ST_DMA״̬�Ĵ��� */
#define DMA_I2ST_AMT    (*(unsigned char volatile far *)0x7efab3)	/*  I2ST_DMA�������ֽ���   */
#define DMA_I2ST_DONE   (*(unsigned char volatile far *)0x7efab4)	/*  I2ST_DMA��������ֽ��� */
#define DMA_I2ST_TXAH   (*(unsigned char volatile far *)0x7efab5)	/*  I2ST_DMA���͸ߵ�ַ */
#define DMA_I2ST_TXAL   (*(unsigned char volatile far *)0x7efab6)	/*  I2ST_DMA���͵͵�ַ */
#define DMA_I2SR_CFG    (*(unsigned char volatile far *)0x7efab8)	/*  I2SR_DMA���üĴ��� */
#define DMA_I2SR_CR     (*(unsigned char volatile far *)0x7efab9)	/*  I2SR_DMA���ƼĴ��� */
#define DMA_I2SR_STA    (*(unsigned char volatile far *)0x7efaba)	/*  I2SR_DMA״̬�Ĵ��� */
#define DMA_I2SR_AMT    (*(unsigned char volatile far *)0x7efabb)	/*  I2SR_DMA�������ֽ���   */
#define DMA_I2SR_DONE   (*(unsigned char volatile far *)0x7efabc)	/*  I2SR_DMA��������ֽ��� */
#define DMA_I2SR_TXAH   (*(unsigned char volatile far *)0x7efabd)	/*  I2SR_DMA���͸ߵ�ַ */
#define DMA_I2SR_TXAL   (*(unsigned char volatile far *)0x7efabe)	/*  I2SR_DMA���͵͵�ַ */

#define DMA_I2ST_AMTH   (*(unsigned char volatile far *)0x7efac0)	/*  I2ST_DMA�������ֽ��� */
#define DMA_I2ST_DONEH  (*(unsigned char volatile far *)0x7efac1)	/*  I2ST_DMA��������ֽ��� */
#define DMA_I2SR_AMTH   (*(unsigned char volatile far *)0x7efac2)	/*  I2SR_DMA�������ֽ��� */
#define DMA_I2SR_DONEH  (*(unsigned char volatile far *)0x7efac3)	/*  I2SR_DMA��������ֽ��� */

#define DMA_ARB_CFG     (*(unsigned char volatile far *)0x7efaf8)	/*  DMA�ܲ����üĴ��� */
#define DMA_ARB_STA     (*(unsigned char volatile far *)0x7efaf9)	/*  DMA�ܲ�״̬�Ĵ��� */

#define HSPWMA_CFG  (*(unsigned char volatile far *)0x7efbf0)	/*  ����PWMA���üĴ��� */
#define HSPWMA_ADR  (*(unsigned char volatile far *)0x7efbf1)	/*  ����PWMA��ַ�Ĵ��� */
#define HSPWMA_DAT  (*(unsigned char volatile far *)0x7efbf2)	/*  ����PWMA���ݼĴ��� */
#define HSPWMB_CFG  (*(unsigned char volatile far *)0x7efbf4)	/*  ����PWMB���üĴ��� */
#define HSPWMB_ADR  (*(unsigned char volatile far *)0x7efbf5)	/*  ����PWMB��ַ�Ĵ��� */
#define HSPWMB_DAT  (*(unsigned char volatile far *)0x7efbf6)	/*  ����PWMB���ݼĴ��� */
#define HSSPI_CFG   (*(unsigned char volatile far *)0x7efbf8)	/*  ����SPI���üĴ��� */
#define HSSPI_CFG2  (*(unsigned char volatile far *)0x7efbf9)	/*  ����SPI���üĴ���2 */
#define HSSPI_STA   (*(unsigned char volatile far *)0x7efbfa)	/*  ����SPI״̬�Ĵ��� */

#define P0INTE      (*(unsigned char volatile far *)0x7efd00)	/* P0���ж�ʹ�ܼĴ��� */
#define P1INTE      (*(unsigned char volatile far *)0x7efd01)	/* P1���ж�ʹ�ܼĴ��� */
#define P2INTE      (*(unsigned char volatile far *)0x7efd02)	/* P2���ж�ʹ�ܼĴ��� */
#define P3INTE      (*(unsigned char volatile far *)0x7efd03)	/* P3���ж�ʹ�ܼĴ��� */
#define P4INTE      (*(unsigned char volatile far *)0x7efd04)	/* P4���ж�ʹ�ܼĴ��� */
#define P5INTE      (*(unsigned char volatile far *)0x7efd05)	/* P5���ж�ʹ�ܼĴ��� */
#define P6INTE      (*(unsigned char volatile far *)0x7efd06)	/* P6���ж�ʹ�ܼĴ��� */
#define P7INTE      (*(unsigned char volatile far *)0x7efd07)	/* P7���ж�ʹ�ܼĴ��� */

#define P0INTF      (*(unsigned char volatile far *)0x7efd10)	/* P0���жϱ�־�Ĵ��� */
#define P1INTF      (*(unsigned char volatile far *)0x7efd11)	/* P1���жϱ�־�Ĵ��� */
#define P2INTF      (*(unsigned char volatile far *)0x7efd12)	/* P2���жϱ�־�Ĵ��� */
#define P3INTF      (*(unsigned char volatile far *)0x7efd13)	/* P3���жϱ�־�Ĵ��� */
#define P4INTF      (*(unsigned char volatile far *)0x7efd14)	/* P4���жϱ�־�Ĵ��� */
#define P5INTF      (*(unsigned char volatile far *)0x7efd15)	/* P5���жϱ�־�Ĵ��� */
#define P6INTF      (*(unsigned char volatile far *)0x7efd16)	/* P6���жϱ�־�Ĵ��� */
#define P7INTF      (*(unsigned char volatile far *)0x7efd17)	/* P7���жϱ�־�Ĵ��� */

#define P0IM0       (*(unsigned char volatile far *)0x7efd20)	/* P0���ж�ģʽ�Ĵ���0 */
#define P1IM0       (*(unsigned char volatile far *)0x7efd21)	/* P1���ж�ģʽ�Ĵ���0 */
#define P2IM0       (*(unsigned char volatile far *)0x7efd22)	/* P2���ж�ģʽ�Ĵ���0 */
#define P3IM0       (*(unsigned char volatile far *)0x7efd23)	/* P3���ж�ģʽ�Ĵ���0 */
#define P4IM0       (*(unsigned char volatile far *)0x7efd24)	/* P4���ж�ģʽ�Ĵ���0 */
#define P5IM0       (*(unsigned char volatile far *)0x7efd25)	/* P5���ж�ģʽ�Ĵ���0 */
#define P6IM0       (*(unsigned char volatile far *)0x7efd26)	/* P6���ж�ģʽ�Ĵ���0 */
#define P7IM0       (*(unsigned char volatile far *)0x7efd27)	/* P7���ж�ģʽ�Ĵ���0 */

#define P0IM1       (*(unsigned char volatile far *)0x7efd30)	/* P0���ж�ģʽ�Ĵ���1 */
#define P1IM1       (*(unsigned char volatile far *)0x7efd31)	/* P1���ж�ģʽ�Ĵ���1 */
#define P2IM1       (*(unsigned char volatile far *)0x7efd32)	/* P2���ж�ģʽ�Ĵ���1 */
#define P3IM1       (*(unsigned char volatile far *)0x7efd33)	/* P3���ж�ģʽ�Ĵ���1 */
#define P4IM1       (*(unsigned char volatile far *)0x7efd34)	/* P4���ж�ģʽ�Ĵ���1 */
#define P5IM1       (*(unsigned char volatile far *)0x7efd35)	/* P5���ж�ģʽ�Ĵ���1 */
#define P6IM1       (*(unsigned char volatile far *)0x7efd36)	/* P6���ж�ģʽ�Ĵ���1 */
#define P7IM1       (*(unsigned char volatile far *)0x7efd37)	/* P7���ж�ģʽ�Ĵ���1 */

#define INTE_0       0x01	/* ʹ��Px.0���жϹ��� */
#define INTE_1       0x02	/* ʹ��Px.1���жϹ��� */
#define INTE_2       0x04	/* ʹ��Px.2���жϹ��� */
#define INTE_3       0x08	/* ʹ��Px.3���жϹ��� */
#define INTE_4       0x10	/* ʹ��Px.4���жϹ��� */
#define INTE_5       0x20	/* ʹ��Px.5���жϹ��� */
#define INTE_6       0x40	/* ʹ��Px.6���жϹ��� */
#define INTE_7       0x80	/* ʹ��Px.7���жϹ��� */

#define INTF_0       0x01	/* ʹ��Px.0���жϱ�־ */
#define INTF_1       0x02	/* ʹ��Px.1���жϱ�־ */
#define INTF_2       0x04	/* ʹ��Px.2���жϱ�־ */
#define INTF_3       0x08	/* ʹ��Px.3���жϱ�־ */
#define INTF_4       0x10	/* ʹ��Px.4���жϱ�־ */
#define INTF_5       0x20	/* ʹ��Px.5���жϱ�־ */
#define INTF_6       0x40	/* ʹ��Px.6���жϱ�־ */
#define INTF_7       0x80	/* ʹ��Px.7���жϱ�־ */

#define	INT_FALL	0		/* �½����ж�   */
#define	INT_RISE	1		/* �������ж�   */
#define	INT_LOW		2		/* �͵�ƽ�ж�   */
#define	INT_HIGH	3		/* �ߵ�ƽ�ж�   */

#define P0WKUE      (*(unsigned char volatile far *)0x7efd40)	/* P0���жϻ���ʹ�ܼĴ��� */
#define P1WKUE      (*(unsigned char volatile far *)0x7efd41)	/* P1���жϻ���ʹ�ܼĴ��� */
#define P2WKUE      (*(unsigned char volatile far *)0x7efd42)	/* P2���жϻ���ʹ�ܼĴ��� */
#define P3WKUE      (*(unsigned char volatile far *)0x7efd43)	/* P3���жϻ���ʹ�ܼĴ��� */
#define P4WKUE      (*(unsigned char volatile far *)0x7efd44)	/* P4���жϻ���ʹ�ܼĴ��� */
#define P5WKUE      (*(unsigned char volatile far *)0x7efd45)	/* P5���жϻ���ʹ�ܼĴ��� */
#define P6WKUE      (*(unsigned char volatile far *)0x7efd46)	/* P6���жϻ���ʹ�ܼĴ��� */
#define P7WKUE      (*(unsigned char volatile far *)0x7efd47)	/* P7���жϻ���ʹ�ܼĴ��� */

#define PINIPL      (*(unsigned char volatile far *)0x7efd60)	/* IO���ж����ȼ��ͼĴ��� */
#define PINIPH      (*(unsigned char volatile far *)0x7efd61)	/* IO���ж����ȼ��߼Ĵ��� */

#define FSHWUPPRD   (*(unsigned char volatile far *)0x7efd68)	/* FLASH���ѵȴ�ʱ��Ĵ��� */

#define UR1TOCR     (*(unsigned char volatile far *)0x7efd70)	/* ����1��ʱ���ƼĴ��� */
#define UR1TOSR     (*(unsigned char volatile far *)0x7efd71)	/* ����1��ʱ״̬�Ĵ��� */
#define UR1TOTH     (*(unsigned char volatile far *)0x7efd72)	/* ����1��ʱ���ȿ��ƼĴ��� */
#define UR1TOTL     (*(unsigned char volatile far *)0x7efd73)	/* ����1��ʱ���ȿ��ƼĴ��� */
#define UR2TOCR     (*(unsigned char volatile far *)0x7efd74)	/* ����2��ʱ���ƼĴ��� */
#define UR2TOSR     (*(unsigned char volatile far *)0x7efd75)	/* ����2��ʱ״̬�Ĵ��� */
#define UR2TOTH     (*(unsigned char volatile far *)0x7efd76)	/* ����2��ʱ���ȿ��ƼĴ��� */
#define UR2TOTL     (*(unsigned char volatile far *)0x7efd77)	/* ����2��ʱ���ȿ��ƼĴ��� */
#define UR3TOCR     (*(unsigned char volatile far *)0x7efd78)	/* ����3��ʱ���ƼĴ��� */
#define UR3TOSR     (*(unsigned char volatile far *)0x7efd79)	/* ����3��ʱ״̬�Ĵ��� */
#define UR3TOTH     (*(unsigned char volatile far *)0x7efd7a)	/* ����3��ʱ���ȿ��ƼĴ��� */
#define UR3TOTL     (*(unsigned char volatile far *)0x7efd7b)	/* ����3��ʱ���ȿ��ƼĴ��� */
#define UR4TOCR     (*(unsigned char volatile far *)0x7efd7c)	/* ����4��ʱ���ƼĴ��� */
#define UR4TOSR     (*(unsigned char volatile far *)0x7efd7d)	/* ����4��ʱ״̬�Ĵ��� */
#define UR4TOTH     (*(unsigned char volatile far *)0x7efd7e)	/* ����4��ʱ���ȿ��ƼĴ��� */
#define UR4TOTL     (*(unsigned char volatile far *)0x7efd7f)	/* ����4��ʱ���ȿ��ƼĴ��� */

#define SPITOCR     (*(unsigned char volatile far *)0x7efd80)	/* SPI��ʱ���ƼĴ��� */
#define SPITOSR     (*(unsigned char volatile far *)0x7efd81)	/* SPI��ʱ״̬�Ĵ��� */
#define SPITOTH     (*(unsigned char volatile far *)0x7efd82)	/* SPI��ʱ���ȿ��ƼĴ��� */
#define SPITOTL     (*(unsigned char volatile far *)0x7efd83)	/* SPI��ʱ���ȿ��ƼĴ��� */
#define I2CTOCR     (*(unsigned char volatile far *)0x7efd84)	/* I2C��ʱ���ƼĴ��� */
#define I2CTOSR     (*(unsigned char volatile far *)0x7efd85)	/* I2C��ʱ״̬�Ĵ��� */
#define I2CTOTH     (*(unsigned char volatile far *)0x7efd86)	/* I2C��ʱ���ȿ��ƼĴ��� */
#define I2CTOTL     (*(unsigned char volatile far *)0x7efd87)	/* I2C��ʱ���ȿ��ƼĴ��� */

#define I2SCR       (*(unsigned char volatile far *)0x7efd98)	/* I2S���ƼĴ��� */
#define I2SSR       (*(unsigned char volatile far *)0x7efd99)	/* I2S״̬�Ĵ��� */
#define I2SDRH      (*(unsigned char volatile far *)0x7efd9a)	/* I2S���ݼĴ������ֽ� */
#define I2SDRL      (*(unsigned char volatile far *)0x7efd9b)	/* I2S���ݼĴ������ֽ� */
#define I2SPRH      (*(unsigned char volatile far *)0x7efd9c)	/* I2S��Ƶ�Ĵ������ֽ� */
#define I2SPRL      (*(unsigned char volatile far *)0x7efd9d)	/* I2S��Ƶ�Ĵ������ֽ� */
#define I2SCFGH     (*(unsigned char volatile far *)0x7efd9e)	/* I2S���üĴ������ֽ� */
#define I2SCFGL     (*(unsigned char volatile far *)0x7efd9f)	/* I2S���üĴ������ֽ� */
#define I2SMD       (*(unsigned char volatile far *)0x7efda0)	/* I2S��ģʽ���ƼĴ��� */

#define CRECR       (*(unsigned char volatile far *)0x7efda8)	/* CRE���ƼĴ��� */
#define CRECNTH     (*(unsigned char volatile far *)0x7efda9)	/* CREУ׼Ŀ��Ĵ��� */
#define CRECNTL     (*(unsigned char volatile far *)0x7efdaa)	/* CREУ׼Ŀ��Ĵ��� */
#define CRERES      (*(unsigned char volatile far *)0x7efdab)	/* CRE�ֱ��ʿ��ƼĴ��� */

#define S2CFG       (*(unsigned char volatile far *)0x7efdb4)	/* ����2���üĴ��� */
#define S2ADDR      (*(unsigned char volatile far *)0x7efdb5)	/* ����2�ӻ���ַ�Ĵ��� */
#define S2ADEN      (*(unsigned char volatile far *)0x7efdb6)	/* ����2�ӻ���ַ���μĴ��� */

#define USARTCR1    (*(unsigned char volatile far *)0x7efdc0)	/* ����1���ƼĴ���1 */
#define USARTCR2    (*(unsigned char volatile far *)0x7efdc1)	/* ����1���ƼĴ���2 */
#define USARTCR3    (*(unsigned char volatile far *)0x7efdc2)	/* ����1���ƼĴ���3 */
#define USARTCR4    (*(unsigned char volatile far *)0x7efdc3)	/* ����1���ƼĴ���4 */
#define USARTCR5    (*(unsigned char volatile far *)0x7efdc4)	/* ����1���ƼĴ���5 */
#define USARTGTR    (*(unsigned char volatile far *)0x7efdc5)	/* ����1����ʱ��Ĵ��� */
#define USARTBRH    (*(unsigned char volatile far *)0x7efdc6)	/* ����1�����ʼĴ������ֽ� */
#define USARTBRL    (*(unsigned char volatile far *)0x7efdc7)	/* ����1�����ʼĴ������ֽ� */

#define USART2CR1   (*(unsigned char volatile far *)0x7efdc8)	/* ����2���ƼĴ���1 */
#define USART2CR2   (*(unsigned char volatile far *)0x7efdc9)	/* ����2���ƼĴ���2 */
#define USART2CR3   (*(unsigned char volatile far *)0x7efdca)	/* ����2���ƼĴ���3 */
#define USART2CR4   (*(unsigned char volatile far *)0x7efdcb)	/* ����2���ƼĴ���4 */
#define USART2CR5   (*(unsigned char volatile far *)0x7efdcc)	/* ����2���ƼĴ���5 */
#define USART2GTR   (*(unsigned char volatile far *)0x7efdcd)	/* ����2����ʱ��Ĵ��� */
#define USART2BRH   (*(unsigned char volatile far *)0x7efdce)	/* ����2�����ʼĴ������ֽ� */
#define USART2BRL   (*(unsigned char volatile far *)0x7efdcf)	/* ����2�����ʼĴ������ֽ� */

#define CHIPID0     (*(unsigned char volatile far *)0x7efde0) /* Ӳ��ID0 */
#define CHIPID1     (*(unsigned char volatile far *)0x7efde1) /* Ӳ��ID1 */
#define CHIPID2     (*(unsigned char volatile far *)0x7efde2) /* Ӳ��ID2 */
#define CHIPID3     (*(unsigned char volatile far *)0x7efde3) /* Ӳ��ID3 */
#define CHIPID4     (*(unsigned char volatile far *)0x7efde4) /* Ӳ��ID4 */
#define CHIPID5     (*(unsigned char volatile far *)0x7efde5) /* Ӳ��ID5 */
#define CHIPID6     (*(unsigned char volatile far *)0x7efde6) /* Ӳ��ID6 */
#define CHIPID7     (*(unsigned char volatile far *)0x7efde7) /* Ӳ��ID7 */
#define CHIPID8     (*(unsigned char volatile far *)0x7efde8) /* Ӳ��ID8 */
#define CHIPID9     (*(unsigned char volatile far *)0x7efde9) /* Ӳ��ID9 */
#define CHIPID10    (*(unsigned char volatile far *)0x7efdea) /* Ӳ��ID10 */
#define CHIPID11    (*(unsigned char volatile far *)0x7efdeb) /* Ӳ��ID11 */
#define CHIPID12    (*(unsigned char volatile far *)0x7efdec) /* Ӳ��ID12 */
#define CHIPID13    (*(unsigned char volatile far *)0x7efded) /* Ӳ��ID13 */
#define CHIPID14    (*(unsigned char volatile far *)0x7efdee) /* Ӳ��ID14 */
#define CHIPID15    (*(unsigned char volatile far *)0x7efdef) /* Ӳ��ID15 */
#define CHIPID16    (*(unsigned char volatile far *)0x7efdf0) /* Ӳ��ID16 */
#define CHIPID17    (*(unsigned char volatile far *)0x7efdf1) /* Ӳ��ID17 */
#define CHIPID18    (*(unsigned char volatile far *)0x7efdf2) /* Ӳ��ID18 */
#define CHIPID19    (*(unsigned char volatile far *)0x7efdf3) /* Ӳ��ID19 */
#define CHIPID20    (*(unsigned char volatile far *)0x7efdf4) /* Ӳ��ID20 */
#define CHIPID21    (*(unsigned char volatile far *)0x7efdf5) /* Ӳ��ID21 */
#define CHIPID22    (*(unsigned char volatile far *)0x7efdf6) /* Ӳ��ID22 */
#define CHIPID23    (*(unsigned char volatile far *)0x7efdf7) /* Ӳ��ID23 */
#define CHIPID24    (*(unsigned char volatile far *)0x7efdf8) /* Ӳ��ID24 */
#define CHIPID25    (*(unsigned char volatile far *)0x7efdf9) /* Ӳ��ID25 */
#define CHIPID26    (*(unsigned char volatile far *)0x7efdfa) /* Ӳ��ID26 */
#define CHIPID27    (*(unsigned char volatile far *)0x7efdfb) /* Ӳ��ID27 */
#define CHIPID28    (*(unsigned char volatile far *)0x7efdfc) /* Ӳ��ID28 */
#define CHIPID29    (*(unsigned char volatile far *)0x7efdfd) /* Ӳ��ID29 */
#define CHIPID30    (*(unsigned char volatile far *)0x7efdfe) /* Ӳ��ID30 */
#define CHIPID31    (*(unsigned char volatile far *)0x7efdff) /* Ӳ��ID31 */

#define CLKSEL      (*(unsigned char volatile far *)0x7efe00)	/* ��ʱ��Դѡ��Ĵ���    */
#define	CLKDIV		(*(unsigned char volatile far *)0x7efe01)	/* ��ʱ�ӷ�Ƶ�Ĵ���      */
#define	HIRCCR		(*(unsigned char volatile far *)0x7efe02)	/* �ڲ������������ƼĴ��� */
#define	XOSCCR		(*(unsigned char volatile far *)0x7efe03)	/* �ⲿ���پ����������ƼĴ���    */
#define	IRC32KCR	(*(unsigned char volatile far *)0x7efe04)	/* �ڲ�32K����IRCʱ�ӿ��ƼĴ���   */
#define	MCLKOCR		(*(unsigned char volatile far *)0x7efe05)	/* ��ʱ��������ƼĴ���  */
#define	IRCDB		(*(unsigned char volatile far *)0x7efe06)	/* �ڲ���������ȥ�����ƼĴ���   */
#define	IRC48MCR	(*(unsigned char volatile far *)0x7efe07)	/* �ڲ�48M�������ƼĴ���  */
#define	X32KCR		(*(unsigned char volatile far *)0x7efe08)	/* �ⲿ32K�����������ƼĴ���   */
#define	HSCLKDIV	(*(unsigned char volatile far *)0x7efe0b)	/* ����ʱ�ӷ�Ƶ�Ĵ���  */
#define	HPLLCR		(*(unsigned char volatile far *)0x7efe0c)	/* ����PLL���ƼĴ���  */
#define	HPLLPSCR	(*(unsigned char volatile far *)0x7efe0d)	/* ����PLLԤ��Ƶ�Ĵ���  */

#define	P0PU		(*(unsigned char volatile far *)0x7efe10)	/* P0������������ƼĴ���, 0: ��ֹ(Ĭ��), 1: ����  */
#define	P1PU		(*(unsigned char volatile far *)0x7efe11)	/* P1������������ƼĴ���  */
#define	P2PU		(*(unsigned char volatile far *)0x7efe12)	/* P2������������ƼĴ���  */
#define	P3PU		(*(unsigned char volatile far *)0x7efe13)	/* P3������������ƼĴ���  */
#define	P4PU		(*(unsigned char volatile far *)0x7efe14)	/* P4������������ƼĴ���  */
#define	P5PU		(*(unsigned char volatile far *)0x7efe15)	/* P5������������ƼĴ���  */
#define	P6PU		(*(unsigned char volatile far *)0x7efe16)	/* P6������������ƼĴ���  */
#define	P7PU		(*(unsigned char volatile far *)0x7efe17)	/* P7������������ƼĴ���  */

#define	P0NCS		(*(unsigned char volatile far *)0x7efe18)	/* P0 Non Schmit Trigger  0: ʹ�ܶ˿�ʩ���ش�������(Ĭ��), 1: ��ֹ  */
#define	P1NCS		(*(unsigned char volatile far *)0x7efe19)	/* P1 Non Schmit Trigger  */
#define	P2NCS		(*(unsigned char volatile far *)0x7efe1a)	/* P2 Non Schmit Trigger  */
#define	P3NCS		(*(unsigned char volatile far *)0x7efe1b)	/* P3 Non Schmit Trigger  */
#define	P4NCS		(*(unsigned char volatile far *)0x7efe1c)	/* P4 Non Schmit Trigger  */
#define	P5NCS		(*(unsigned char volatile far *)0x7efe1d)	/* P5 Non Schmit Trigger  */
#define	P6NCS		(*(unsigned char volatile far *)0x7efe1e)	/* P6 Non Schmit Trigger  */
#define	P7NCS		(*(unsigned char volatile far *)0x7efe1f)	/* P7 Non Schmit Trigger  */

#define	P0SR		(*(unsigned char volatile far *)0x7efe20)	/* P0�ڵ�ƽת�����ʼĴ��� Ĭ��1: ��ͨģʽ, 0:����ģʽ */
#define	P1SR		(*(unsigned char volatile far *)0x7efe21)	/* P1�ڵ�ƽת�����ʼĴ���  */
#define	P2SR		(*(unsigned char volatile far *)0x7efe22)	/* P2�ڵ�ƽת�����ʼĴ���  */
#define	P3SR		(*(unsigned char volatile far *)0x7efe23)	/* P3�ڵ�ƽת�����ʼĴ���  */
#define	P4SR		(*(unsigned char volatile far *)0x7efe24)	/* P4�ڵ�ƽת�����ʼĴ���  */
#define	P5SR		(*(unsigned char volatile far *)0x7efe25)	/* P5�ڵ�ƽת�����ʼĴ���  */
#define	P6SR		(*(unsigned char volatile far *)0x7efe26)	/* P6�ڵ�ƽת�����ʼĴ���  */
#define	P7SR		(*(unsigned char volatile far *)0x7efe27)	/* P7�ڵ�ƽת�����ʼĴ���  */

#define	P0DR		(*(unsigned char volatile far *)0x7efe28)	/* P0�������������ƼĴ��� Ĭ��1: ��ͨģʽ, 0:�����ģʽ*/
#define	P1DR		(*(unsigned char volatile far *)0x7efe29)	/* P1�������������ƼĴ��� */
#define	P2DR		(*(unsigned char volatile far *)0x7efe2a)	/* P2�������������ƼĴ��� */
#define	P3DR		(*(unsigned char volatile far *)0x7efe2b)	/* P3�������������ƼĴ��� */
#define	P4DR		(*(unsigned char volatile far *)0x7efe2c)	/* P4�������������ƼĴ��� */
#define	P5DR		(*(unsigned char volatile far *)0x7efe2d)	/* P5�������������ƼĴ��� */
#define	P6DR		(*(unsigned char volatile far *)0x7efe2e)	/* P6�������������ƼĴ��� */
#define	P7DR		(*(unsigned char volatile far *)0x7efe2f)	/* P7�������������ƼĴ��� */

#define	P0IE		(*(unsigned char volatile far *)0x7efe30)	/* P0������ʹ�ܿ��ƼĴ���, 1����(Ĭ��), 0��ֹ */
#define	P1IE		(*(unsigned char volatile far *)0x7efe31)	/* P1������ʹ�ܿ��ƼĴ��� */
#define	P2IE		(*(unsigned char volatile far *)0x7efe32)	/* P2������ʹ�ܿ��ƼĴ��� */
#define	P3IE		(*(unsigned char volatile far *)0x7efe33)	/* P3������ʹ�ܿ��ƼĴ��� */
#define	P4IE		(*(unsigned char volatile far *)0x7efe34)	/* P4������ʹ�ܿ��ƼĴ��� */
#define	P5IE		(*(unsigned char volatile far *)0x7efe35)	/* P5������ʹ�ܿ��ƼĴ��� */
#define	P6IE		(*(unsigned char volatile far *)0x7efe36)	/* P6������ʹ�ܿ��ƼĴ��� */
#define	P7IE		(*(unsigned char volatile far *)0x7efe37)	/* P7������ʹ�ܿ��ƼĴ��� */

#define	P0PD		(*(unsigned char volatile far *)0x7efe40)	/* P0������������ƼĴ���, 0: ��ֹ(Ĭ��), 1: ����  */
#define	P1PD		(*(unsigned char volatile far *)0x7efe41)	/* P1������������ƼĴ���  */
#define	P2PD		(*(unsigned char volatile far *)0x7efe42)	/* P2������������ƼĴ���  */
#define	P3PD		(*(unsigned char volatile far *)0x7efe43)	/* P3������������ƼĴ���  */
#define	P4PD		(*(unsigned char volatile far *)0x7efe44)	/* P4������������ƼĴ���  */
#define	P5PD		(*(unsigned char volatile far *)0x7efe45)	/* P5������������ƼĴ���  */
#define	P6PD		(*(unsigned char volatile far *)0x7efe46)	/* P6������������ƼĴ���  */
#define	P7PD		(*(unsigned char volatile far *)0x7efe47)	/* P7������������ƼĴ���  */

#define	LCMIFCFG	(*(unsigned char volatile far *)0x7efe50)	/* LCM�ӿ����üĴ��� */
#define	LCMIFCFG2	(*(unsigned char volatile far *)0x7efe51)	/* LCM�ӿ����üĴ���2 */
#define	LCMIFCR		(*(unsigned char volatile far *)0x7efe52)	/* LCM�ӿڿ��ƼĴ��� */
#define	LCMIFSTA	(*(unsigned char volatile far *)0x7efe53)	/* LCM�ӿ�״̬�Ĵ��� */
#define	LCMIDDATL	(*(unsigned char volatile far *)0x7efe54)	/* LCM�ӿڵ��ֽ����� */
#define	LCMIDDATH	(*(unsigned char volatile far *)0x7efe55)	/* LCM�ӿڸ��ֽ����� */

#define	RTCCR		(*(unsigned char volatile far *)0x7efe60)	/* RTC���ƼĴ��� */
#define	RTCCFG		(*(unsigned char volatile far *)0x7efe61)	/* RTC���üĴ��� */
#define	RTCIEN		(*(unsigned char volatile far *)0x7efe62)	/* RTC�ж�ʹ�ܼĴ��� */
#define	RTCIF		(*(unsigned char volatile far *)0x7efe63)	/* RTC�ж�����Ĵ��� */
#define	ALAHOUR		(*(unsigned char volatile far *)0x7efe64)	/* RTC���ӵ�Сʱֵ */
#define	ALAMIN		(*(unsigned char volatile far *)0x7efe65)	/* RTC���ӵķ���ֵ */
#define	ALASEC		(*(unsigned char volatile far *)0x7efe66)	/* RTC���ӵ���ֵ */
#define	ALASSEC		(*(unsigned char volatile far *)0x7efe67)	/* RTC���ӵ�1/128��ֵ */
#define	INIYEAR		(*(unsigned char volatile far *)0x7efe68)	/* RTC���ʼ�� */
#define	INIMONTH	(*(unsigned char volatile far *)0x7efe69)	/* RTC�³�ʼ�� */
#define	INIDAY		(*(unsigned char volatile far *)0x7efe6a)	/* RTC�ճ�ʼ�� */
#define	INIHOUR		(*(unsigned char volatile far *)0x7efe6b)	/* RTCʱ��ʼ�� */
#define	INIMIN		(*(unsigned char volatile far *)0x7efe6c)	/* RTC�ֳ�ʼ�� */
#define	INISEC		(*(unsigned char volatile far *)0x7efe6d)	/* RTC���ʼ�� */
#define	INISSEC		(*(unsigned char volatile far *)0x7efe6e)	/* RTC1/128���ʼ�� */
#define	RTC_YEAR	(*(unsigned char volatile far *)0x7efe70)	/* RTC�������ֵ */
#define	RTC_MONTH	(*(unsigned char volatile far *)0x7efe71)	/* RTC���¼���ֵ */
#define	RTC_DAY		(*(unsigned char volatile far *)0x7efe72)	/* RTC���ռ���ֵ */
#define	RTC_HOUR	(*(unsigned char volatile far *)0x7efe73)	/* RTC��ʱ����ֵ */
#define	RTC_MIN		(*(unsigned char volatile far *)0x7efe74)	/* RTC�ķּ���ֵ */
#define	RTC_SEC		(*(unsigned char volatile far *)0x7efe75)	/* RTC�������ֵ */
#define	RTC_SSEC	(*(unsigned char volatile far *)0x7efe76)	/* RTC��1/128�����ֵ */

#define	I2CCFG		(*(unsigned char volatile far *)0x7efe80)	/* I2C���üĴ���  */
#define	I2CMSCR		(*(unsigned char volatile far *)0x7efe81)	/* I2C�������ƼĴ���  */
#define	I2CMSST		(*(unsigned char volatile far *)0x7efe82)	/* I2C����״̬�Ĵ���  */
#define	I2CSLCR		(*(unsigned char volatile far *)0x7efe83)	/* I2C�ӻ����ƼĴ���  */
#define	I2CSLST		(*(unsigned char volatile far *)0x7efe84)	/* I2C�ӻ�״̬�Ĵ���  */
#define	I2CSLADR	(*(unsigned char volatile far *)0x7efe85)	/* I2C�ӻ���ַ�Ĵ���  */
#define	I2CTXD		(*(unsigned char volatile far *)0x7efe86)	/* I2C���ݷ��ͼĴ���  */
#define	I2CRXD		(*(unsigned char volatile far *)0x7efe87)	/* I2C���ݽ��ռĴ���  */
#define	I2CMSAUX	(*(unsigned char volatile far *)0x7efe88)	/* I2C�����������ƼĴ���  */

#define	SPFUNC		(*(unsigned char volatile far *)0x7efe98)	/* �������ƼĴ���  */
#define	RSTFLAG		(*(unsigned char volatile far *)0x7efe99)	/* ��λ��־�Ĵ���  */
#define	RSTCR0		(*(unsigned char volatile far *)0x7efe9a)	/* ��λ���ƼĴ���0  */
#define	RSTCR1		(*(unsigned char volatile far *)0x7efe9b)	/* ��λ���ƼĴ���1  */
#define	RSTCR2		(*(unsigned char volatile far *)0x7efe9c)	/* ��λ���ƼĴ���2  */
#define	RSTCR3		(*(unsigned char volatile far *)0x7efe9d)	/* ��λ���ƼĴ���3  */
#define	RSTCR4		(*(unsigned char volatile far *)0x7efe9e)	/* ��λ���ƼĴ���4  */
#define	RSTCR5		(*(unsigned char volatile far *)0x7efe9f)	/* ��λ���ƼĴ���5  */

#define	TM0PS		(*(unsigned char volatile far *)0x7efea0)	/* ��ʱ��0ʱ��Ԥ��Ƶ�Ĵ���  */
#define	TM1PS		(*(unsigned char volatile far *)0x7efea1)	/* ��ʱ��1ʱ��Ԥ��Ƶ�Ĵ���  */
#define	TM2PS		(*(unsigned char volatile far *)0x7efea2)	/* ��ʱ��2ʱ��Ԥ��Ƶ�Ĵ���  */
#define	TM3PS		(*(unsigned char volatile far *)0x7efea3)	/* ��ʱ��3ʱ��Ԥ��Ƶ�Ĵ���  */
#define	TM4PS		(*(unsigned char volatile far *)0x7efea4)	/* ��ʱ��4ʱ��Ԥ��Ƶ�Ĵ���  */
#define	ADCTIM		(*(unsigned char volatile far *)0x7efea8)	/* ADCʱ����ƼĴ���  */
#define	T3T4PIN		(*(unsigned char volatile far *)0x7efeac)	/* T3/T4ѡ��Ĵ���  */
#define	ADCEXCFG	(*(unsigned char volatile far *)0x7efead)	/* ADC��չ���üĴ���  */
#define	CMPEXCFG	(*(unsigned char volatile far *)0x7efeae)	/* �Ƚ�����չ���üĴ���  */

#define	PWMA_ETRPS	(*(unsigned char volatile far *)0x7efeb0)	/* PWMA��ETRѡ��Ĵ���  */
#define	PWMA_ENO	(*(unsigned char volatile far *)0x7efeb1)	/* PWMA���ʹ�ܼĴ���   */
#define	PWMA_PS		(*(unsigned char volatile far *)0x7efeb2)	/* PWMA�����ѡ��Ĵ��� */
#define	PWMA_IOAUX	(*(unsigned char volatile far *)0x7efeb3)	/* PWMA�����Ĵ���       */
#define	PWMB_ETRPS	(*(unsigned char volatile far *)0x7efeb4)	/* PWMB��ETRѡ��Ĵ���  */
#define	PWMB_ENO	(*(unsigned char volatile far *)0x7efeb5)	/* PWMB���ʹ�ܼĴ���   */
#define	PWMB_PS		(*(unsigned char volatile far *)0x7efeb6)	/* PWMB�����ѡ��Ĵ��� */
#define	PWMB_IOAUX	(*(unsigned char volatile far *)0x7efeb7)	/* PWMB�����Ĵ���       */

#define	CANAR		(*(unsigned char volatile far *)0x7efebb)	/* CANBUS��ַ�Ĵ��� */
#define	CANDR		(*(unsigned char volatile far *)0x7efebc)	/* CANBUS���ݼĴ���       */

#define	PWMA_CR1	(*(unsigned char volatile far *)0x7efec0)	/* PWMA���ƼĴ���1  */
#define	PWMA_CR2	(*(unsigned char volatile far *)0x7efec1)	/* PWMA���ƼĴ���2  */
#define	PWMA_SMCR	(*(unsigned char volatile far *)0x7efec2)	/* PWMA��ģʽ���ƼĴ���  */
#define	PWMA_ETR	(*(unsigned char volatile far *)0x7efec3)	/* PWMA�ⲿ�����Ĵ���  */
#define	PWMA_IER	(*(unsigned char volatile far *)0x7efec4)	/* PWMA�ж�ʹ�ܼĴ���  */
#define	PWMA_SR1	(*(unsigned char volatile far *)0x7efec5)	/* PWMA״̬�Ĵ���1  */
#define	PWMA_SR2	(*(unsigned char volatile far *)0x7efec6)	/* PWMA״̬�Ĵ���2  */
#define	PWMA_EGR	(*(unsigned char volatile far *)0x7efec7)	/* PWMA�¼������Ĵ���  */

#define	PWMA_CCMR1	(*(unsigned char volatile far *)0x7efec8)	/* PWMA����/�Ƚ�ģʽ�Ĵ���1  */
#define	PWMA_CCMR2	(*(unsigned char volatile far *)0x7efec9)	/* PWMA����/�Ƚ�ģʽ�Ĵ���2  */
#define	PWMA_CCMR3	(*(unsigned char volatile far *)0x7efeca)	/* PWMA����/�Ƚ�ģʽ�Ĵ���3  */
#define	PWMA_CCMR4	(*(unsigned char volatile far *)0x7efecb)	/* PWMA����/�Ƚ�ģʽ�Ĵ���4  */
#define	PWMA_CCER1	(*(unsigned char volatile far *)0x7efecc)	/* PWMA����Ƚ�ʹ�ܼĴ���1  */
#define	PWMA_CCER2	(*(unsigned char volatile far *)0x7efecd)	/* PWMA����Ƚ�ʹ�ܼĴ���2  */
#define	PWMA_CNTRH	(*(unsigned char volatile far *)0x7efece)	/* PWMA���������ֽ�   */
#define	PWMA_CNTRL	(*(unsigned char volatile far *)0x7efecf)	/* PWMA���������ֽ�   */

#define PWMA_PSCRH  (*(unsigned char volatile far *)0x7efed0)	/* PWMAԤ��Ƶ�����ֽ� */
#define PWMA_PSCRL  (*(unsigned char volatile far *)0x7efed1)	/* PWMAԤ��Ƶ�����ֽ� */
#define PWMA_ARRH   (*(unsigned char volatile far *)0x7efed2)	/* PWMA�Զ���װ�Ĵ������ֽ� */
#define PWMA_ARRL   (*(unsigned char volatile far *)0x7efed3)	/* PWMA�Զ���װ�Ĵ������ֽ� */
#define PWMA_RCR    (*(unsigned char volatile far *)0x7efed4)	/* PWMA�ظ������Ĵ��� */
#define PWMA_CCR1H  (*(unsigned char volatile far *)0x7efed5)	/* PWMA�Ƚϲ���Ĵ���1���ֽ� */
#define PWMA_CCR1L  (*(unsigned char volatile far *)0x7efed6)	/* PWMA�Ƚϲ���Ĵ���1���ֽ� */
#define PWMA_CCR2H  (*(unsigned char volatile far *)0x7efed7)	/* PWMA�Ƚϲ���Ĵ���2���ֽ� */
#define PWMA_CCR2L  (*(unsigned char volatile far *)0x7efed8)	/* PWMA�Ƚϲ���Ĵ���2���ֽ� */
#define PWMA_CCR3H  (*(unsigned char volatile far *)0x7efed9)	/* PWMA�Ƚϲ���Ĵ���3���ֽ� */
#define PWMA_CCR3L  (*(unsigned char volatile far *)0x7efeda)	/* PWMA�Ƚϲ���Ĵ���3���ֽ� */
#define PWMA_CCR4H  (*(unsigned char volatile far *)0x7efedb)	/* PWMA�Ƚϲ���Ĵ���4���ֽ� */
#define PWMA_CCR4L  (*(unsigned char volatile far *)0x7efedc)	/* PWMA�Ƚϲ���Ĵ���4���ֽ� */
#define PWMA_BKR    (*(unsigned char volatile far *)0x7efedd)	/* PWMAɲ���Ĵ��� */
#define PWMA_DTR    (*(unsigned char volatile far *)0x7efede)	/* PWMA�������ƼĴ��� */
#define PWMA_OISR   (*(unsigned char volatile far *)0x7efedf)	/* PWMA�������״̬�Ĵ��� */

#define	PWMB_CR1	(*(unsigned char volatile far *)0x7efee0)	/* PWMB���ƼĴ���1  */
#define	PWMB_CR2	(*(unsigned char volatile far *)0x7efee1)	/* PWMB���ƼĴ���2  */
#define	PWMB_SMCR	(*(unsigned char volatile far *)0x7efee2)	/* PWMB��ģʽ���ƼĴ���  */
#define	PWMB_ETR	(*(unsigned char volatile far *)0x7efee3)	/* PWMB�ⲿ�����Ĵ���  */
#define	PWMB_IER	(*(unsigned char volatile far *)0x7efee4)	/* PWMB�ж�ʹ�ܼĴ���  */
#define	PWMB_SR1	(*(unsigned char volatile far *)0x7efee5)	/* PWMB״̬�Ĵ���1  */
#define	PWMB_SR2	(*(unsigned char volatile far *)0x7efee6)	/* PWMB״̬�Ĵ���2  */
#define	PWMB_EGR	(*(unsigned char volatile far *)0x7efee7)	/* PWMB�¼������Ĵ���  */

#define	PWMB_CCMR1	(*(unsigned char volatile far *)0x7efee8)	/* PWMB����/�Ƚ�ģʽ�Ĵ���1  */
#define	PWMB_CCMR2	(*(unsigned char volatile far *)0x7efee9)	/* PWMB����/�Ƚ�ģʽ�Ĵ���2  */
#define	PWMB_CCMR3	(*(unsigned char volatile far *)0x7efeea)	/* PWMB����/�Ƚ�ģʽ�Ĵ���3  */
#define	PWMB_CCMR4	(*(unsigned char volatile far *)0x7efeeb)	/* PWMB����/�Ƚ�ģʽ�Ĵ���4  */
#define	PWMB_CCER1	(*(unsigned char volatile far *)0x7efeec)	/* PWMB����Ƚ�ʹ�ܼĴ���1  */
#define	PWMB_CCER2	(*(unsigned char volatile far *)0x7efeed)	/* PWMB����Ƚ�ʹ�ܼĴ���2  */
#define	PWMB_CNTRH	(*(unsigned char volatile far *)0x7efeee)	/* PWMB���������ֽ�   */
#define	PWMB_CNTRL	(*(unsigned char volatile far *)0x7efeef)	/* PWMB���������ֽ�   */

#define PWMB_PSCRH  (*(unsigned char volatile far *)0x7efef0)	/* PWMBԤ��Ƶ�����ֽ� */
#define PWMB_PSCRL  (*(unsigned char volatile far *)0x7efef1)	/* PWMBԤ��Ƶ�����ֽ� */
#define PWMB_ARRH   (*(unsigned char volatile far *)0x7efef2)	/* PWMB�Զ���װ�Ĵ������ֽ� */
#define PWMB_ARRL   (*(unsigned char volatile far *)0x7efef3)	/* PWMB�Զ���װ�Ĵ������ֽ� */
#define PWMB_RCR    (*(unsigned char volatile far *)0x7efef4)	/* PWMB�ظ������Ĵ��� */
#define PWMB_CCR1H  (*(unsigned char volatile far *)0x7efef5)	/* PWMB�Ƚϲ���Ĵ���1���ֽ� */
#define PWMB_CCR1L  (*(unsigned char volatile far *)0x7efef6)	/* PWMB�Ƚϲ���Ĵ���1���ֽ� */
#define PWMB_CCR2H  (*(unsigned char volatile far *)0x7efef7)	/* PWMB�Ƚϲ���Ĵ���2���ֽ� */
#define PWMB_CCR2L  (*(unsigned char volatile far *)0x7efef8)	/* PWMB�Ƚϲ���Ĵ���2���ֽ� */
#define PWMB_CCR3H  (*(unsigned char volatile far *)0x7efef9)	/* PWMB�Ƚϲ���Ĵ���3���ֽ� */
#define PWMB_CCR3L  (*(unsigned char volatile far *)0x7efefa)	/* PWMB�Ƚϲ���Ĵ���3���ֽ� */
#define PWMB_CCR4H  (*(unsigned char volatile far *)0x7efefb)	/* PWMB�Ƚϲ���Ĵ���4���ֽ� */
#define PWMB_CCR4L  (*(unsigned char volatile far *)0x7efefc)	/* PWMB�Ƚϲ���Ĵ���4���ֽ� */
#define PWMB_BKR    (*(unsigned char volatile far *)0x7efefd)	/* PWMBɲ���Ĵ��� */
#define PWMB_DTR    (*(unsigned char volatile far *)0x7efefe)	/* PWMB�������ƼĴ��� */
#define PWMB_OISR   (*(unsigned char volatile far *)0x7efeff)	/* PWMB�������״̬�Ĵ��� */

/*
#define PWMA_CNTR   (*(unsigned int  volatile far *)0x7efece)	//* PWMA������16λ���� *
#define PWMA_PSCR   (*(unsigned int  volatile far *)0x7efed0)	//* PWMAԤ��Ƶ��16λ���� *
#define PWMA_ARR    (*(unsigned int  volatile far *)0x7efed2)	//* PWMA�Զ���װ�Ĵ���16λ���� *
#define PWMA_CCR1   (*(unsigned int  volatile far *)0x7efed5)	//* PWMA�Ƚϲ���Ĵ���1 16λ���� *
#define PWMA_CCR2   (*(unsigned int  volatile far *)0x7efed7)	//* PWMA�Ƚϲ���Ĵ���2 16λ���� *
#define PWMA_CCR3   (*(unsigned int  volatile far *)0x7efed9)	//* PWMA�Ƚϲ���Ĵ���3 16λ���� *
#define PWMA_CCR4   (*(unsigned int  volatile far *)0x7efedB)	//* PWMA�Ƚϲ���Ĵ���4 16λ���� *

#define PWMB_CNTR   (*(unsigned int  volatile far *)0x7efeee)	//* PWMA������16λ���� *
#define PWMB_PSCR   (*(unsigned int  volatile far *)0x7efef0)	//* PWMAԤ��Ƶ��16λ���� *
#define PWMB_ARR    (*(unsigned int  volatile far *)0x7efef2)	//* PWMA�Զ���װ�Ĵ���16λ���� *
#define PWMB_CCR1   (*(unsigned int  volatile far *)0x7efef5)	//* PWMA�Ƚϲ���Ĵ���1 16λ���� *
#define PWMB_CCR2   (*(unsigned int  volatile far *)0x7efef7)	//* PWMA�Ƚϲ���Ĵ���2 16λ���� *
#define PWMB_CCR3   (*(unsigned int  volatile far *)0x7efef9)	//* PWMA�Ƚϲ���Ĵ���3 16λ���� *
#define PWMB_CCR4   (*(unsigned int  volatile far *)0x7efefB)	//* PWMA�Ƚϲ���Ĵ���4 16λ���� *
*/
//=============================================================================================================

#define	EAXSFR()		P_SW2 |=  0x80		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չSFR(XSFR) */
#define	EAXRAM()		P_SW2 &= ~0x80		/* MOVX A,@DPTR/MOVX @DPTR,Aָ��Ĳ�������Ϊ��չRAM(XRAM) */

#define	I2C_USE_P15P14()	P_SW2 &= ~0x30						/* ��I2C�л���P1.5(SCL) P1.4(SDA)(�ϵ�Ĭ��).*/
#define	I2C_USE_P25P24()	P_SW2  = (P_SW2 & ~0x30) | 0x10		/* ��I2C�л���P2.5(SCL) P2.4(SDA).*/
#define	I2C_USE_P32P33()	P_SW2 |= 0x30						/* ��I2C�л���P3.2(SCL) P3.3(SDA).*/

#define	MainFosc_IRC24M()	CKSEL = (CKSEL & ~0x03)			/* ѡ���ڲ�24MHZʱ�� */
#define	MainFosc_XTAL()		CKSEL = (CKSEL & ~0x03) | 0x01	/* ѡ���ⲿ�����ʱ�� */
#define	EXT_CLOCK()			XOSCCR = 0x80					/* ѡ���ⲿʱ�� */
#define	EXT_CRYSTAL()		XOSCCR = 0xC0					/* ѡ���ⲿ���� */
#define	MainFosc_IRC32K()	CKSEL =  CKSEL | 0x03			/* ѡ���ڲ�32Kʱ�� */
#define	MCLKO_None()		MCLKOCR = 0						/* ��ʱ�Ӳ���� 	    */
#define	MCLKO54_DIV(n)		MCLKOCR = n						/* ��ʱ�Ӵ�P5.4��Ƶ��� */
#define	MCLKO16_DIV(n)		MCLKOCR = n | 0x80				/* ��ʱ�Ӵ�P1.6��Ƶ��� */


/*  BIT Registers  */
/*  PSW   */
sbit CY   = PSW^7;
sbit AC   = PSW^6;
sbit F0   = PSW^5;
sbit RS1  = PSW^4;
sbit RS0  = PSW^3;
sbit OV   = PSW^2;
sbit F1   = PSW^1;
sbit P    = PSW^0;

/*  TCON  */
sbit TF1  = TCON^7;	//��ʱ��1����жϱ�־λ
sbit TR1  = TCON^6;	//��ʱ��1���п���λ
sbit TF0  = TCON^5;	//��ʱ��0����жϱ�־λ
sbit TR0  = TCON^4;	//��ʱ��0���п���λ
sbit IE1  = TCON^3;	//���ж�1��־λ
sbit IT1  = TCON^2;	//���ж�1�źŷ�ʽ����λ��1���½����жϣ�0�������½����жϡ�
sbit IE0  = TCON^1;	//���ж�0��־λ
sbit IT0  = TCON^0;	//���ж�0�źŷ�ʽ����λ��1���½����жϣ�0�������½����жϡ�

/*  P0  */
sbit  P00 = P0^0;
sbit  P01 = P0^1;
sbit  P02 = P0^2;
sbit  P03 = P0^3;
sbit  P04 = P0^4;
sbit  P05 = P0^5;
sbit  P06 = P0^6;
sbit  P07 = P0^7;

/*  P1  */
sbit  P10 = P1^0;
sbit  P11 = P1^1;
sbit  P12 = P1^2;
sbit  P13 = P1^3;
sbit  P14 = P1^4;
sbit  P15 = P1^5;
sbit  P16 = P1^6;
sbit  P17 = P1^7;

/*  P2  */
sbit  P20 = P2^0;
sbit  P21 = P2^1;
sbit  P22 = P2^2;
sbit  P23 = P2^3;
sbit  P24 = P2^4;
sbit  P25 = P2^5;
sbit  P26 = P2^6;
sbit  P27 = P2^7;

/*  P3  */
sbit  P30 = P3^0;
sbit  P31 = P3^1;
sbit  P32 = P3^2;
sbit  P33 = P3^3;
sbit  P34 = P3^4;
sbit  P35 = P3^5;
sbit  P36 = P3^6;
sbit  P37 = P3^7;

/*  P4  */
sbit  P40 = P4^0;
sbit  P41 = P4^1;
sbit  P42 = P4^2;
sbit  P43 = P4^3;
sbit  P44 = P4^4;
sbit  P45 = P4^5;
sbit  P46 = P4^6;
sbit  P47 = P4^7;

/*  P5  */
sbit  P50 = P5^0;
sbit  P51 = P5^1;
sbit  P52 = P5^2;
sbit  P53 = P5^3;
sbit  P54 = P5^4;
sbit  P55 = P5^5;
sbit  P56 = P5^6;
sbit  P57 = P5^7;

/*  P6  */
sbit  P60 = P6^0;
sbit  P61 = P6^1;
sbit  P62 = P6^2;
sbit  P63 = P6^3;
sbit  P64 = P6^4;
sbit  P65 = P6^5;
sbit  P66 = P6^6;
sbit  P67 = P6^7;

/*  P7  */
sbit  P70 = P7^0;
sbit  P71 = P7^1;
sbit  P72 = P7^2;
sbit  P73 = P7^3;
sbit  P74 = P7^4;
sbit  P75 = P7^5;
sbit  P76 = P7^6;
sbit  P77 = P7^7;

sbit  RXD2      = P1^0;
sbit  TXD2      = P1^1;
sbit  ECI       = P1^2;
sbit  CCP0      = P1^1;
sbit  CCP1      = P1^0;
sbit  CCP2      = P3^7;
sbit  ECI_2     = P3^4;
sbit  CCP0_2    = P3^5;
sbit  CCP1_2    = P3^6;
sbit  CCP2_2    = P3^7;

sbit  SPI_SS    = P1^2;
sbit  SPI_MOSI  = P1^3;
sbit  SPI_MISO  = P1^4;
sbit  SPI_SCLK  = P1^5;

sbit  SPI_SS_2    = P2^2;
sbit  SPI_MOSI_2  = P2^3;
sbit  SPI_MISO_2  = P2^4;
sbit  SPI_SCLK_2  = P2^5;

sbit  SPI_SS_4    = P3^5;
sbit  SPI_MOSI_4  = P3^4;
sbit  SPI_MISO_4  = P3^3;
sbit  SPI_SCLK_4  = P3^2;

sbit RXD  = P3^0;
sbit TXD  = P3^1;
sbit INT0 = P3^2;
sbit INT1 = P3^3;
sbit T0   = P3^4;
sbit T1   = P3^5;

sbit INT2 = P3^6;
sbit INT3 = P3^7;
sbit INT4 = P3^0;

sbit CLKOUT0   = P3^5;
sbit CLKOUT1   = P3^4;


/*  SCON  */
sbit SM0  = SCON^7;	//SM0/FE		SM0 SM1 = 00 ~ 11: ��ʽ0~3
sbit SM1  = SCON^6;	//
sbit SM2  = SCON^5;	//���ͨѶ
sbit REN  = SCON^4;	//��������
sbit TB8  = SCON^3;	//�������ݵ�8λ
sbit RB8  = SCON^2;	//�������ݵ�8λ
sbit TI   = SCON^1;	//�����жϱ�־λ
sbit RI   = SCON^0;	//�����жϱ�־λ

/*  IE   */
sbit EA   = IE^7;	//�ж������ܿ���λ
sbit ELVD = IE^6;	//��ѹ����ж�����λ
sbit EADC = IE^5;	//ADC �ж� ����λ
sbit ES   = IE^4;	//�����ж� �������λ
sbit ET1  = IE^3;	//��ʱ�ж�1�������λ
sbit EX1  = IE^2;	//�ⲿ�ж�1�������λ
sbit ET0  = IE^1;	//��ʱ�ж�0�������λ
sbit EX0  = IE^0;	//�ⲿ�ж�0�������λ

sbit ACC0 = ACC^0;
sbit ACC1 = ACC^1;
sbit ACC2 = ACC^2;
sbit ACC3 = ACC^3;
sbit ACC4 = ACC^4;
sbit ACC5 = ACC^5;
sbit ACC6 = ACC^6;
sbit ACC7 = ACC^7;

sbit B0 = B^0;
sbit B1 = B^1;
sbit B2 = B^2;
sbit B3 = B^3;
sbit B4 = B^4;
sbit B5 = B^5;
sbit B6 = B^6;
sbit B7 = B^7;

//                                     7    6    5    4    3     2       1       0      Reset Value
//INT_CLKO:  �ж���ʱ��������ƼĴ���  -   EX4  EX3  EX2   -   T2CLKO  T1CLKO  T0CLKO    0000,0000
#define	INT4_Enable()	INT_CLKO |= (1 << 6)
#define	INT3_Enable()	INT_CLKO |= (1 << 5)
#define	INT2_Enable()	INT_CLKO |= (1 << 4)
#define	INT1_Enable()	EX1 = 1
#define	INT0_Enable()	EX0 = 1

#define	INT4_Disable()	INT_CLKO &= ~(1 << 6)
#define	INT3_Disable()	INT_CLKO &= ~(1 << 5)
#define	INT2_Disable()	INT_CLKO &= ~(1 << 4)
#define	INT1_Disable()	EX1 = 0
#define	INT0_Disable()	EX0 = 0

//                               7    6       5       4      3    2     1     0      Reset Value
//AUXINTIF:  �����жϱ�־�Ĵ���  -  INT4IF  INT3IF  INT2IF   -   T4IF  T3IF  T2IF    0000,0000
#define	INT4IF	0x40
#define	INT3IF	0x20
#define	INT2IF	0x10
#define	T4IF	0x04
#define	T3IF	0x02
#define	T2IF	0x01

#define	INT4_Clear()	AUXINTIF &= ~INT4IF		/* ������ж�4��־λ */
#define	INT3_Clear()	AUXINTIF &= ~INT3IF		/* ������ж�3��־λ */
#define	INT2_Clear()	AUXINTIF &= ~INT2IF		/* ������ж�2��־λ */
#define	INT1_Clear()	IE1 = 0					/* ������ж�1��־λ */
#define	INT0_Clear()	IE0 = 0					/* ������ж�0��־λ */

#define	INT0_Fall()		IT0 = 1		/* INT0 �½����ж�           */
#define	INT0_RiseFall()	IT0 = 0		/* INT0 �½��������ؾ��ж�   */
#define	INT1_Fall()		IT1 = 1		/* INT1 �½����ж�           */
#define	INT1_RiseFall()	IT0 = 0		/* INT1 �½��������ؾ��ж�   */


//							7     6     5    4    3    2    1     0    Reset Value
//sfr IE2       = 0xAF;		-     -     -    -    -    -   ESPI  ES2   0000,0000B	//Auxiliary Interrupt
#define		SPI_INT_ENABLE()		IE2 |=  2	/* ����SPI�ж�		*/
#define		SPI_INT_DISABLE()		IE2 &= ~2	/* ����SPI�ж�		*/
#define		UART2_INT_ENABLE()		IE2 |=  1	/* ������2�ж�	*/
#define		UART2_INT_DISABLE()		IE2 &= ~1	/* ������2�ж�	*/

//                                          7     6     5    4    3    2    1    0    Reset Value
//sfr IP      = 0xB8; //�ж����ȼ���λ      PPCA  PLVD  PADC  PS   PT1  PX1  PT0  PX0   0000,0000
//--------
sbit PPCA	= IP^7;	//PCA ģ���ж����ȼ�
sbit PLVD	= IP^6;	//��ѹ����ж����ȼ�
sbit PADC	= IP^5;	//ADC �ж����ȼ�
sbit PS   	= IP^4;	//�����ж�0���ȼ��趨λ
sbit PT1	= IP^3;	//��ʱ�ж�1���ȼ��趨λ
sbit PX1	= IP^2;	//�ⲿ�ж�1���ȼ��趨λ
sbit PT0	= IP^1;	//��ʱ�ж�0���ȼ��趨λ
sbit PX0	= IP^0;	//�ⲿ�ж�0���ȼ��趨λ

//                                           7      6      5     4     3     2    1     0        Reset Value
//sfr IPH   = 0xB7; //�ж����ȼ���λ       PPCAH  PLVDH  PADCH  PSH  PT1H  PX1H  PT0H  PX0H   0000,0000
//sfr IP2   = 0xB5; //                       -      -      -     -     -     -   PSPI   PS2   xxxx,xx00
//sfr IP2H  = 0xB6; //                       -      -      -     -     -     -   PSPIH  PS2H  xxxx,xx00
#define		PPCAH	0x80
#define		PLVDH	0x40
#define		PADCH	0x20
#define		PSH		0x10
#define		PT1H	0x08
#define		PX1H	0x04
#define		PT0H	0x02
#define		PX0H	0x01

#define		PCA_InterruptFirst()	PPCA = 1
#define		LVD_InterruptFirst()	PLVD = 1
#define		ADC_InterruptFirst()	PADC = 1
#define		UART1_InterruptFirst()	PS   = 1
#define		Timer1_InterruptFirst()	PT1  = 1
#define		INT1_InterruptFirst()	PX1  = 1
#define		Timer0_InterruptFirst()	PT0  = 1
#define		INT0_InterruptFirst()	PX0  = 1


/*************************************************************************************************/


//                       7      6     5    4    3    2     1      0        Reset Value
//sfr CMPCR1 = 0xE6;   CMPEN  CMPIF  PIE  NIE  PIS  NIS  CMPOE  CMPRES      00000000B
#define	CMPEN	0x80	//1: ����Ƚ���, 0: ��ֹ,�رձȽ�����Դ
#define	CMPIF	0x40	//�Ƚ����жϱ�־, ���������ػ��½����ж�, �����0
#define	PIE		0x20	//1: �ȽϽ����0��1, �����������ж�
#define	NIE		0x10	//1: �ȽϽ����1��0, �����½����ж�
#define	PIS		0x08	//����������ѡ��, 0: ѡ���ڲ�P3.7��������,           1: ��ADC_CHS[3:0]��ѡ���ADC�������������.
#define	NIS		0x04	//���븺����ѡ��, 0: ѡ���ڲ�BandGap��ѹBGv��������, 1: ѡ���ⲿP3.6������.
#define	CMPOE	0x02	//1: ����ȽϽ�����, 0: ��ֹ.
#define	CMPRES	0x01	//�ȽϽ��, 1: CMP+��ƽ����CMP-,  0: CMP+��ƽ����CMP-,  ֻ��

#define	CMP_P_P37	0x00	//����������ѡ��, 0: ѡ���ڲ�P3.7��������
#define	CMP_P_ADC	0x08	//����������ѡ��, 1: ��ADC_CHS[3:0]��ѡ���ADC�������������.
#define	CMP_N_GAP	0x00	//���븺����ѡ��, 0: ѡ���ڲ�BandGap��ѹBGv��������.
#define	CMP_N_P36	0x04	//���븺����ѡ��, 1: ѡ���ⲿP3.6������.

#define	CMPO_P34()	P_SW2 &= ~0x08	//��������P3.4.

//                       7        6       5  4  3  2  1  0    Reset Value
//sfr CMPCR2 = 0xE7;   INVCMPO  DISFLT       LCDTY[5:0]       00001001B
#define	INVCMPO	0x80	//1: �Ƚ������IOȡ��,  0: ��ȡ��
#define	DISFLT	0x40	//1: �ر�0.1uF�˲�,   	0: ����
#define	LCDTY	0x00	//0~63, �ȽϽ���仯��ʱ������



/*************************************************************************************************/
//                     7     6     5    4    3    2   1   0       Reset Value
//sfr SCON  = 0x98;   SM0   SM1   SM2  REN  TB8  RB8  TI  RI      00000000B		 //S1 Control

#define		S1_DoubleRate()		PCON  |=  0x80
#define		S1_SHIFT()			SCON  &=  0x3f

#define		S1_8bit()			SCON   =  (SCON & 0x3f) | 0x40
#define		S1_9bit()			SCON   =  (SCON & 0x3f) | 0xc0
#define		S1_RX_Enable()		SCON  |=  0x10
#define		S1_RX_Disable()		SCON  &= ~0x10
#define		TI1					TI					/* �ж�TI1�Ƿ������								 */
#define		RI1					RI					/* �ж�RI1�Ƿ�������								 */
#define		SET_TI1()			TI = 1				/* ����TI1(�����ж�)								 */
#define		CLR_TI1()			TI = 0				/* ���TI1											 */
#define		CLR_RI1()			RI = 0				/* ���RI1											 */
#define		S1TB8_SET()			TB8 = 1				/* ����TB8											 */
#define		S1TB8_CLR()			TB8 = 0				/* ���TB8											 */
#define		S1_Int_Enable()		ES     =  1			/* ����1�����ж�									 */
#define		S1_Int_Disable()	ES     =  0			/* ����1��ֹ�ж�									 */
#define 	S1_BRT_UseTimer1()	AUXR  &= ~1
#define 	S1_BRT_UseTimer2()	AUXR  |=  1
#define		S1_USE_P30P31()		P_SW1 &= ~0xc0						//UART1 ʹ��P30 P31��	Ĭ��
#define		S1_USE_P36P37()		P_SW1  =  (P_SW1 & ~0xc0) | 0x40	//UART1 ʹ��P36 P37��
#define		S1_USE_P16P17()		P_SW1  =  (P_SW1 & ~0xc0) | 0x80	//UART1 ʹ��P16 P17��
#define		S1_USE_P43P44()		P_SW1  =  (P_SW1 & ~0xc0) | 0xc0	//UART1 ʹ��P4.3 P4.4��

//						  7      6      5      4      3      2     1     0        Reset Value
//sfr S2CON = 0x9A;		S2SM0    -    S2SM2  S2REN  S2TB8  S2RB8  S2TI  S2RI      00000000B		 //S2 Control

#define		S2_MODE0()			S2CON &= ~(1<<7)	/* ����2ģʽ0��8λUART�������� = ��ʱ��2������� / 4 */
#define		S2_MODE1()			S2CON |=  (1<<7)	/* ����2ģʽ1��9λUART�������� = ��ʱ��2������� / 4 */
#define		S2_8bit()			S2CON &= ~(1<<7)	/* ����2ģʽ0��8λUART�������� = ��ʱ��2������� / 4 */
#define		S2_9bit()			S2CON |=  (1<<7)	/* ����2ģʽ1��9λUART�������� = ��ʱ��2������� / 4 */
#define		S2_RX_Enable()		S2CON |=  (1<<4)	/* ����2����										 */
#define		S2_RX_Disable()		S2CON &= ~(1<<4)	/* ��ֹ��2����										 */
#define		TI2					(S2CON & 2) 		/* �ж�TI2�Ƿ������								 */
#define		RI2					(S2CON & 1) 		/* �ж�RI2�Ƿ�������								 */
#define		SET_TI2()			S2CON |=  (1<<1)	/* ����TI2(�����ж�)								 */
#define		CLR_TI2()			S2CON &= ~(1<<1)	/* ���TI2											 */
#define		CLR_RI2()			S2CON &= ~1			/* ���RI2											 */
#define		S2TB8_SET()			S2CON |=  (1<<3)	/* ����TB8											 */
#define		S2TB8_CLR()			S2CON &= ~(1<<3)	/* ���TB8											 */
#define		S2_Int_Enable()		IE2   |=  1			/* ����2�����ж�									 */
#define		S2_Int_Disable()	IE2   &= ~1			/* ����2��ֹ�ж�									 */
#define		S2_USE_P10P11()		P_SW2 &= ~1			/* UART2 ʹ��P1��	Ĭ��							 */
#define		S2_USE_P46P47()		P_SW2 |=  1			/* UART2 ʹ��P4.6 P4.7��							 */

//						  7      6      5      4      3      2     1     0        Reset Value
//sfr S3CON = 0xAC;		S3SM0  S3ST3  S3SM2  S3REN  S3TB8  S3RB8  S3TI  S3RI      00000000B		 //S3 Control

#define		S3_MODE0()			S3CON &= ~(1<<7)	/* ����3ģʽ0��8λUART�������� = ��ʱ��������� / 4  */
#define		S3_MODE1()			S3CON |=  (1<<7)	/* ����3ģʽ1��9λUART�������� = ��ʱ��������� / 4  */
#define		S3_8bit()			S3CON &= ~(1<<7)	/* ����3ģʽ0��8λUART�������� = ��ʱ��������� / 4  */
#define		S3_9bit()			S3CON |=  (1<<7)	/* ����3ģʽ1��9λUART�������� = ��ʱ��������� / 4  */
#define		S3_RX_Enable()		S3CON |=  (1<<4)	/* ����3����									     */
#define		S3_RX_Disable()		S3CON &= ~(1<<4)	/* ��ֹ��3����									     */
#define		TI3					(S3CON & 2) != 0	/* �ж�TI3�Ƿ������								 */
#define		RI3					(S3CON & 1) != 0	/* �ж�RI3�Ƿ�������								 */
#define		SET_TI3()			S3CON |=  (1<<1)	/* ����TI3(�����ж�)								 */
#define		CLR_TI3()			S3CON &= ~(1<<1)	/* ���TI3											 */
#define		CLR_RI3()			S3CON &= ~1			/* ���RI3											 */
#define		S3TB8_SET()			S3CON |=  (1<<3)	/* ����TB8											 */
#define		S3TB8_CLR()			S3CON &= ~(1<<3)	/* ���TB8											 */
#define		S3_Int_Enable()		IE2   |=  (1<<3)	/* ����3�����ж�								     */
#define		S3_Int_Disable()	IE2   &= ~(1<<3)	/* ����3��ֹ�ж�								     */
#define 	S3_BRT_UseTimer3()	S3CON |=  (1<<6)	/* BRT select Timer3								 */
#define 	S3_BRT_UseTimer2()	S3CON &= ~(1<<6)	/* BRT select Timer2								 */
#define		S3_USE_P00P01()		P_SW2 &= ~2			/* UART3 ʹ��P0.0 P0.1��	Ĭ��				     */
#define		S3_USE_P50P51()		P_SW2 |=  2			/* UART3 ʹ��P5.0 P5.1��						     */

//						  7      6      5      4      3      2     1     0        Reset Value
//sfr S4CON = 0x84;		S4SM0  S4ST4  S4SM2  S4REN  S4TB8  S4RB8  S4TI  S4RI      00000000B		 //S4 Control

#define		S4_MODE0()			S4CON &= ~(1<<7)	/* ����4ģʽ0��8λUART�������� = ��ʱ��������� / 4  */
#define		S4_MODE1()			S4CON |=  (1<<7)	/* ����4ģʽ1��9λUART�������� = ��ʱ��������� / 4  */
#define		S4_8bit()			S4CON &= ~(1<<7)	/* ����4ģʽ0��8λUART�������� = ��ʱ��������� / 4  */
#define		S4_9bit()			S4CON |=  (1<<7)	/* ����4ģʽ1��9λUART�������� = ��ʱ��������� / 4  */
#define		S4_RX_Enable()		S4CON |=  (1<<4)	/* ����4����									     */
#define		S4_RX_Disable()		S4CON &= ~(1<<4)	/* ��ֹ��4����									     */
#define		TI4					(S4CON & 2) != 0	/* �ж�TI3�Ƿ������							     */
#define		RI4					(S4CON & 1) != 0	/* �ж�RI3�Ƿ�������							     */
#define		SET_TI4()			S4CON |=  2			/* ����TI3(�����ж�)							     */
#define		CLR_TI4()			S4CON &= ~2			/* ���TI3										     */
#define		CLR_RI4()			S4CON &= ~1			/* ���RI3										     */
#define		S4TB8_SET()			S4CON |=  8			/* ����TB8										     */
#define		S4TB8_CLR()			S4CON &= ~8			/* ���TB8										     */
#define		S4_Int_Enable()		IE2   |=  (1<<4)	/* ����4�����ж�								     */
#define		S4_Int_Disable()	IE2   &= ~(1<<4)	/* ����4��ֹ�ж�								     */
#define 	S4_BRT_UseTimer4()	S4CON |=  (1<<6)	/* BRT select Timer4								 */
#define 	S4_BRT_UseTimer2()	S4CON &= ~(1<<6)	/* BRT select Timer2								 */
#define		S4_USE_P02P03()		P_SW2 &= ~4			/* UART4 ʹ��P0.2 P0.3��	Ĭ��				     */
#define		S4_USE_P52P53()		P_SW2 |=  4			/* UART4 ʹ��P5.2 P5.3��						     */


/**********************************************************/
//						   7     6       5      4     3      2      1      0    Reset Value
//sfr AUXR  = 0x8E;		T0x12 T1x12 UART_M0x6  T2R  T2_C/T T2x12 EXTRAM  S1ST2  0000,0000	//Auxiliary Register

#define 	InternalXdata_Disable()		AUXR |=  2		/* ��ֹʹ���ڲ�xdata, ���з���xdata���Ƿ����ⲿxdata  */
#define 	InternalXdata_Enable()		AUXR &= ~2		/* ����ʹ���ڲ�xdata, �����ʵĵ�ַ���ڲ�xdata��Χʱ, �����ڲ���xadta, ����ַ�����ڲ�xdataʱ, �����ⲿxdata  */
#define		S1_M0x6()					AUXR |=  (1<<5)	/* UART Mode0 Speed is 6x Standard       */
#define		S1_M0x1()					AUXR &= ~(1<<5)	/* default,	UART Mode0 Speed is Standard */

//====================================
#define		Timer0_16bitAutoReload()	TMOD &= ~0x03					/* 16λ�Զ���װ	*/
#define		Timer0_16bit()				TMOD  = (TMOD & ~0x03) | 0x01	/* 16λ         */
#define		Timer0_8bitAutoReload()		TMOD  = (TMOD & ~0x03) | 0x02	/* 8λ�Զ���װ	*/
#define		Timer0_16bitAutoRL_NoMask()	TMOD |=  0x03		/* 16λ�Զ���װ���������ж�	*/
#define 	Timer0_Run()	 			TR0 = 1				/* ����ʱ��0����			*/
#define 	Timer0_Stop()	 			TR0 = 0				/* ��ֹ��ʱ��0����			*/
#define		Timer0_Gate_INT0_P32()		TMOD |=  (1<<3)		/* ʱ��0���ⲿINT0�ߵ�ƽ����ʱ���� */
#define		Timer0_AsTimer()			TMOD &= ~(1<<2)		/* ʱ��0������ʱ��	*/
#define		Timer0_AsCounter()			TMOD |=  (1<<2)		/* ʱ��0����������	*/
#define		Timer0_AsCounterP34()		TMOD |=  (1<<2)		/* ʱ��0����������	*/
#define 	Timer0_1T()					AUXR |=  (1<<7)		/* Timer0 clodk = fo	*/
#define 	Timer0_12T()				AUXR &= ~(1<<7)		/* Timer0 clodk = fo/12	12��Ƶ,	default	*/
#define		Timer0_CLKO_Enable()		INT_CLKO |=  1			/* ���� T0 ���������T0(P3.5)�������Fck0 = 1/2 T0 ����ʣ�T0����1T��12T��	*/
#define		Timer0_CLKO_Disable()		INT_CLKO &= ~1
#define		Timer0_CLKO_Enable_P35()	INT_CLKO |=  1			/* ���� T0 ���������T0(P3.5)�������Fck0 = 1/2 T0 ����ʣ�T0����1T��12T��	*/
#define		Timer0_CLKO_Disable_P35()	INT_CLKO &= ~1
#define 	Timer0_InterruptEnable()	ET0 = 1				/* ����Timer1�ж�.*/
#define 	Timer0_InterruptDisable()	ET0 = 0				/* ��ֹTimer1�ж�.*/

#define		T0_Load(n)					TH0 = (n) / 256,	TL0 = (n) % 256
#define		T0_Load_us_1T(n)			Timer0_AsTimer(),Timer0_1T(), Timer0_16bitAutoReload(),TH0=(65536-((MAIN_Fosc/1000)*(n)+500)/1000)/256, TL0=(65536-((MAIN_Fosc/1000)*(n)+500)/1000)%256
#define		T0_Load_us_12T(n)			Timer0_AsTimer(),Timer0_12T(),Timer0_16bitAutoReload(),TH0=(65536-((MAIN_Fosc/12000)*(n)+500)/1000)/256,TL0=(65536-((MAIN_Fosc/12000)*(n)+500)/1000)%256
#define		T0_Frequency_1T_P35(n)		ET0=0,Timer0_AsTimer(),Timer0_1T(),Timer0_16bitAutoReload(),TH0=(65536-(n/2+MAIN_Fosc/2)/(n))/256,TL0=(65536-(n/2+MAIN_Fosc/2)/(n))%256,INT_CLKO |= 1,TR0=1		/* fx=fosc/(2*M)/n,  M=1 or M=12 */
#define		T0_Frequency_12T_P35(n)		ET0=0,Timer0_AsTimer(),Timer0_12T(),Timer0_16bitAutoReload(),TH0=(65536-(n/2+MAIN_Fosc/24)/(n))/256,TL0=(65536-(n/2+MAIN_Fosc/24)/(n))%256,INT_CLKO |= 1,TR0=1	/* fx=fosc/(2*M)/n,  M=1 or M=12 */

//====================================
#define		Timer1_16bitAutoReload()	TMOD &= ~0x30					/* 16λ�Զ���װ	*/
#define		Timer1_16bit()				TMOD  = (TMOD & ~0x30) | 0x10	/* 16λ			*/
#define		Timer1_8bitAutoReload()		TMOD  = (TMOD & ~0x30) | 0x20	/* 8λ�Զ���װ	*/
#define 	Timer1_Run()	 			TR1 = 1				/* ����ʱ��1����			*/
#define 	Timer1_Stop()	 			TR1 = 0				/* ��ֹ��ʱ��1����			*/
#define		Timer1_Gate_INT1_P33()		TMOD |=  (1<<7)		/* ʱ��1���ⲿINT1�ߵ�ƽ����ʱ����	*/
#define		Timer1_AsTimer()			TMOD &= ~(1<<6)		/* ʱ��1������ʱ��			*/
#define		Timer1_AsCounter()			TMOD |=  (1<<6)		/* ʱ��1����������			*/
#define		Timer1_AsCounterP35()		TMOD |=  (1<<6)		/* ʱ��1����������			*/
#define 	Timer1_1T()					AUXR |=  (1<<6)		/* Timer1 clodk = fo		*/
#define 	Timer1_12T()				AUXR &= ~(1<<6)		/* Timer1 clodk = fo/12	12��Ƶ,	default	*/
#define		Timer1_CLKO_Enable()		INT_CLKO |=  2			/* ���� T1 ���������T1(P3.4)�������Fck1 = 1/2 T1 ����ʣ�T1����1T��12T��	*/
#define		Timer1_CLKO_Disable()		INT_CLKO &= ~2
#define		Timer1_CLKO_Enable_P34()	INT_CLKO |=  2			/* ���� T1 ���������T1(P3.4)�������Fck1 = 1/2 T1 ����ʣ�T1����1T��12T��	*/
#define		Timer1_CLKO_Disable_P34()	INT_CLKO &= ~2
#define 	Timer1_InterruptEnable()	ET1 = 1				/* ����Timer1�ж�.	*/
#define 	Timer1_InterruptDisable()	ET1 = 0				/* ��ֹTimer1�ж�.	*/

#define		T1_Load(n)					TH1 = (n) / 256,	TL1 = (n) % 256
#define		T1_Load_us_1T(n)			Timer1_AsTimer(),Timer1_1T(), Timer1_16bitAutoReload(),TH1=(65536-((MAIN_Fosc/1000)*(n)+500)/1000)/256, TL1=(65536-((MAIN_Fosc/1000)*(n)+500)/1000)%256
#define		T1_Load_us_12T(n)			Timer1_AsTimer(),Timer1_12T(),Timer1_16bitAutoReload(),TH1=(65536-((MAIN_Fosc/12000)*(n)+500)/1000)/256,TL1=(65536-((MAIN_Fosc/12000)*(n)+500)/1000)%256
#define		T1_Frequency_1T_P34(n)		ET1=0,Timer1_AsTimer(),Timer1_1T(),Timer1_16bitAutoReload(),TH1=(65536-(n/2+MAIN_Fosc/2)/(n))/256,TL1=(65536-(n/2+MAIN_Fosc/2)/(n))%256,INT_CLKO |= 2,TR1=1		/* fx=fosc/(2*M)/n,  M=1 or M=12 */
#define		T1_Frequency_12T_P34(n)		ET1=0,Timer1_AsTimer(),Timer1_12T(),Timer1_16bitAutoReload(),TH1=(65536-(n/2+MAIN_Fosc/24)/(n))/256,TL1=(65536-(n/2+MAIN_Fosc/24)/(n))%256,INT_CLKO |= 2,TR1=1	/* fx=fosc/(2*M)/n,  M=1 or M=12 */

//====================================
#define 	Timer2_Run()	 			AUXR |=  (1<<4)	/* ����ʱ��2����	*/
#define 	Timer2_Stop()	 			AUXR &= ~(1<<4)	/* ��ֹ��ʱ��2����	*/
#define		Timer2_AsTimer()			AUXR &= ~(1<<3)	/* ʱ��2������ʱ��	*/
#define		Timer2_AsCounter()			AUXR |=  (1<<3)	/* ʱ��2����������	*/
#define		Timer2_AsCounterP31()		AUXR |=  (1<<3)	/* ʱ��2����������	*/
#define 	Timer2_1T()					AUXR |=  (1<<2)	/* Timer0 clock = fo	*/
#define 	Timer2_12T()				AUXR &= ~(1<<2)	/* Timer0 clock = fo/12	12��Ƶ,	default	*/
#define		Timer2_CLKO_Enable()		INT_CLKO |=  4		/* ���� T2 ���������P1.3�������Fck2 = 1/2 T2 ����ʣ�T2����1T��12T��	*/
#define		Timer2_CLKO_Disable()		INT_CLKO &= ~4
#define		Timer2_CLKO_Enable_P13()	INT_CLKO |=  4		/* ���� T2 ���������P1.3�������Fck2 = 1/2 T2 ����ʣ�T2����1T��12T��	*/
#define		Timer2_CLKO_Disable_P13()	INT_CLKO &= ~4
#define 	Timer2_InterruptEnable()	IE2  |=  (1<<2)	/* ����Timer2�ж�.	*/
#define 	Timer2_InterruptDisable()	IE2  &= ~(1<<2)	/* ��ֹTimer2�ж�.	*/

#define		T2_Load(n)					TH2 = (n) / 256,	TL2 = (n) % 256
#define		T2_Load_us_1T(n)			Timer2_AsTimer(),Timer2_1T(), TH2=(65536-((MAIN_Fosc/1000)*(n)+500)/1000)/256, TL2=(65536-((MAIN_Fosc/1000)*(n)+500)/1000)%256
#define		T2_Load_us_12T(n)			Timer2_AsTimer(),Timer2_12T(),TH2=(65536-((MAIN_Fosc/12000)*(n)+500)/1000)/256,TL2=(65536-((MAIN_Fosc/12000)*(n)+500)/1000)%256
#define		T2_Frequency_1T_P13(n)		Timer2_InterruptDisable(),Timer2_AsTimer(),Timer2_1T(), TH2=(65536-(n/2+MAIN_Fosc/2)/(n))/256, TL2=(65536-(n/2+MAIN_Fosc/2)/(n))%256, Timer2_CLKO_Enable_P13(),Timer2_Run()	/* fx=fosc/(2*M)/n,  M=1 or M=12 */
#define		T2_Frequency_12T_P13(n)		Timer2_InterruptDisable(),Timer2_AsTimer(),Timer2_12T(),TH2=(65536-(n/2+MAIN_Fosc/24)/(n))/256,TL2=(65536-(n/2+MAIN_Fosc/24)/(n))%256,Timer2_CLKO_Enable_P13(),Timer2_Run()	/* fx=fosc/(2*M)/n,  M=1 or M=12 */

//====================================
#define 	Timer3_Run()	 			T4T3M |=  (1<<3)	/* ����ʱ��3����	*/
#define 	Timer3_Stop()	 			T4T3M &= ~(1<<3)	/* ��ֹ��ʱ��3����	*/
#define		Timer3_AsTimer()			T4T3M &= ~(1<<2)	/* ʱ��3������ʱ��	*/
#define		Timer3_AsCounter()			T4T3M |=  (1<<2)	/* ʱ��3����������, P0.5Ϊ�ⲿ����	*/
#define		Timer3_AsCounterP05()		T4T3M |=  (1<<2)	/* ʱ��3����������, P0.5Ϊ�ⲿ����	*/
#define 	Timer3_1T()					T4T3M |=  (1<<1)	/* 1Tģʽ	*/
#define 	Timer3_12T()				T4T3M &= ~(1<<1)	/* 12Tģʽ,	default	*/
#define		Timer3_CLKO_Enable()		T4T3M |=  1			/* ����T3���������T3(P0.4)�������Fck = 1/2 T2 ����ʣ�T2����1T��12T��	*/
#define		Timer3_CLKO_Disable()		T4T3M &= ~1			/* ��ֹT3���������T3(P0.4)�����	*/
#define		Timer3_CLKO_Enable_P04()	T4T3M |=  1			/* ����T3���������T3(P0.4)�������Fck = 1/2 T2 ����ʣ�T2����1T��12T��	*/
#define		Timer3_CLKO_Disable_P04()	T4T3M &= ~1			/* ��ֹT3���������T3(P0.4)�����	*/
#define 	Timer3_InterruptEnable()	IE2  |=  (1<<5)		/* ����Timer3�ж�.	*/
#define 	Timer3_InterruptDisable()	IE2  &= ~(1<<5)		/* ��ֹTimer3�ж�.	*/

#define		T3_Load(n)					TH3 = (n) / 256,	TL3 = (n) % 256
#define		T3_Load_us_1T(n)			Timer3_AsTimer(),Timer3_1T(), TH3=(65536-((MAIN_Fosc/1000)*(n)+500)/1000)/256, TL3=(65536-((MAIN_Fosc/1000)*(n)+500)/1000)%256
#define		T3_Load_us_12T(n)			Timer3_AsTimer(),Timer3_12T(),TH3=(65536-((MAIN_Fosc/12000)*(n)+500)/1000)/256,TL3=(65536-((MAIN_Fosc/12000)*(n)+500)/1000)%256
#define		T3_Frequency_1T_P04(n)		Timer3_InterruptDisable(),Timer3_AsTimer(),Timer3_1T(), TH3=(65536-(n/2+MAIN_Fosc/2)/(n))/256, TL3=(65536-(n/2+MAIN_Fosc/2)/(n))%256, Timer3_CLKO_P04_Enable,Timer3_Run()	/* fx=fosc/(2*M)/n,  M=1 or M=12 */
#define		T3_Frequency_12T_P04(n)		Timer3_InterruptDisable(),Timer3_AsTimer(),Timer3_12T(),TH3=(65536-(n/2+MAIN_Fosc/24)/(n))/256,TL3=(65536-(n/2+MAIN_Fosc/24)/(n))%256,Timer3_CLKO_P04_Enable,Timer3_Run()	/* fx=fosc/(2*M)/n,  M=1 or M=12 */

//====================================
#define 	Timer4_Run()	 			T4T3M |=  (1<<7)	/* ����ʱ��4����	*/
#define 	Timer4_Stop()	 			T4T3M &= ~(1<<7)	/* ��ֹ��ʱ��4����	*/
#define		Timer4_AsTimer()			T4T3M &= ~(1<<6)	/* ʱ��4������ʱ��  */
#define		Timer4_AsCounter()			T4T3M |=  (1<<6)	/* ʱ��4����������, P0.7Ϊ�ⲿ����	*/
#define		Timer4_AsCounterP07()		T4T3M |=  (1<<6)	/* ʱ��4����������, P0.7Ϊ�ⲿ����	*/
#define 	Timer4_1T()					T4T3M |=  (1<<5)	/* 1Tģʽ	*/
#define 	Timer4_12T()				T4T3M &= ~(1<<5)	/* 12Tģʽ,	default	*/
#define		Timer4_CLKO_Enable()		T4T3M |=  (1<<4)	/* ����T4���������T4(P0.6)�������Fck = 1/2 T2 ����ʣ�T2����1T��12T��	*/
#define		Timer4_CLKO_Disable()		T4T3M &= ~(1<<4)	/* ��ֹT4���������T4(P0.6)�����	*/
#define		Timer4_CLKO_Enable_P06()	T4T3M |=  (1<<4)	/* ����T4���������T4(P0.6)�������Fck = 1/2 T2 ����ʣ�T2����1T��12T��	*/
#define		Timer4_CLKO_Disable_P06()	T4T3M &= ~(1<<4)	/* ��ֹT4���������T4(P0.6)�����	*/
#define 	Timer4_InterruptEnable()	IE2  |=  (1<<6)		/* ����Timer4�ж�.	*/
#define 	Timer4_InterruptDisable()	IE2  &= ~(1<<6)		/* ��ֹTimer4�ж�.	*/

#define		T4_Load(n)					TH4 = (n) / 256,	TL4 = (n) % 256
#define		T4_Load_us_1T(n)			Timer4_AsTimer(),Timer4_1T(), TH4=(65536-((MAIN_Fosc/1000)*(n)+500)/1000)/256, TL4=(65536-((MAIN_Fosc/1000)*(n)+500)/1000)%256
#define		T4_Load_us_12T(n)			Timer4_AsTimer(),Timer4_12T(),TH4=(65536-((MAIN_Fosc/12000)*(n)+500)/1000)/256,TL4=(65536-((MAIN_Fosc/12000)*(n)+500)/1000)%256
#define		T4_Frequency_1T_P06(n)		Timer4_InterruptDisable(),Timer4_AsTimer(),Timer4_1T(), TH4=(65536-(n/2+MAIN_Fosc/2)/(n))/256, TL4=(65536-(n/2+MAIN_Fosc/2)/(n))%256, Timer4_CLKO_P06_Enable(),Timer4_Run()	/* fx=fosc/(2*M)/n,  M=1 or M=12 */
#define		T4_Frequency_12T_P06(n)		Timer4_InterruptDisable(),Timer4_AsTimer(),Timer4_12T(),TH4=(65536-(n/2+MAIN_Fosc/24)/(n))/256,TL4=(65536-(n/2+MAIN_Fosc/24)/(n))%256,Timer4_CLKO_P06_Enable(),Timer4_Run()	/* fx=fosc/(2*M)/n,  M=1 or M=12 */
//====================================================================================================================

//sfr WDT_CONTR = 0xC1; //Watch-Dog-Timer Control register
//                                      7     6     5      4       3      2   1   0     Reset Value
//                                  WDT_FLAG  -  EN_WDT CLR_WDT IDLE_WDT PS2 PS1 PS0    xx00,0000
#define D_WDT_FLAG			(1<<7)
#define D_EN_WDT			(1<<5)
#define D_CLR_WDT			(1<<4)	/* auto clear	*/
#define D_IDLE_WDT			(1<<3)	/* WDT counter when Idle	*/
#define D_WDT_SCALE_2		0
#define D_WDT_SCALE_4		1
#define D_WDT_SCALE_8		2		/* T=393216*N/fo	*/
#define D_WDT_SCALE_16		3
#define D_WDT_SCALE_32		4
#define D_WDT_SCALE_64		5
#define D_WDT_SCALE_128		6
#define D_WDT_SCALE_256		7

#define	WDT_reset(n)	WDT_CONTR = D_EN_WDT + D_CLR_WDT + D_IDLE_WDT + (n)		/* ��ʼ��WDT��ι�� */


//						  7     6      5    4     3      2    1     0     Reset Value
//sfr PCON   = 0x87;	SMOD  SMOD0  LVDF  POF   GF1    GF0   PD   IDL    0001,0000	 //Power Control
//SMOD		//����˫����
//SMOD0
#define		LVDF		(1<<5)	/* P4.6��ѹ����־ */
//POF
//GF1
//GF0
//#define 	D_PD		2		/* set 1, power down mode */
//#define 	D_IDLE		1		/* set 1, idle mode */
#define		MCU_IDLE()			PCON |= 1	/* MCU ���� IDLE ģʽ */
#define		MCU_POWER_DOWN()	PCON |= 2	/* MCU ���� ˯�� ģʽ */


//sfr ISP_CMD   = 0xC5;
#define		ISP_STANDBY()	ISP_CMD = 0		/* ISP���������ֹ��*/
#define		ISP_READ()		ISP_CMD = 1		/* ISP��������		*/
#define		ISP_WRITE()		ISP_CMD = 2		/* ISPд������		*/
#define		ISP_ERASE()		ISP_CMD = 3		/* ISP��������		*/

//sfr ISP_TRIG  = 0xC6;
#define 	ISP_TRIG()	ISP_TRIG = 0x5A,	ISP_TRIG = 0xA5		/* ISP�������� */

//							  7    6    5      4    3    2    1     0    Reset Value
//sfr IAP_CONTR = 0xC7;		IAPEN SWBS SWRST CFAIL  -    -    -     -    0000,x000	//IAP Control Register
#define ISP_EN			(1<<7)
#define ISP_SWBS		(1<<6)
#define ISP_SWRST		(1<<5)
#define ISP_CMD_FAIL	(1<<4)


/* ADC Register */
//								7       6      5       4         3      2    1    0   Reset Value
//sfr ADC_CONTR = 0xBC;		ADC_POWER SPEED1 SPEED0 ADC_FLAG ADC_START CHS2 CHS1 CHS0 0000,0000	/* AD ת�����ƼĴ��� */
//sfr ADC_RES  = 0xBD;		ADCV.9 ADCV.8 ADCV.7 ADCV.6 ADCV.5 ADCV.4 ADCV.3 ADCV.2	  0000,0000	/* A/D ת�������8λ */
//sfr ADC_RESL = 0xBE;												  ADCV.1 ADCV.0	  0000,0000	/* A/D ת�������2λ */
//sfr ADC_CONTR  = 0xBC;	//ֱ����MOV��������Ҫ�����


//sfr SPCTL  = 0xCE;	SPI���ƼĴ���
//   7       6       5       4       3       2       1       0    	Reset Value
//	SSIG	SPEN	DORD	MSTR	CPOL	CPHA	SPR1	SPR0		0x00

#define	SPI_SSIG_None()		SPCTL |=  (1<<7)		/* 1: ����SS��	*/
#define	SPI_SSIG_Enable()	SPCTL &= ~(1<<7)		/* 0: SS�����ھ������ӻ�	*/
#define	SPI_Enable()		SPCTL |=  (1<<6)		/* 1: ����SPI	*/
#define	SPI_Disable()		SPCTL &= ~(1<<6)		/* 0: ��ֹSPI	*/
#define	SPI_LSB_First()		SPCTL |=  (1<<5)		/* 1: LSB�ȷ�	*/
#define	SPI_MSB_First()		SPCTL &= ~(1<<5)		/* 0: MSB�ȷ�	*/
#define	SPI_Master()		SPCTL |=  (1<<4)		/* 1: ��Ϊ����	*/
#define	SPI_Slave()			SPCTL &= ~(1<<4)		/* 0: ��Ϊ�ӻ�	*/
#define	SPI_SCLK_NormalH()	SPCTL |=  (1<<3)		/* 1: ����ʱSCLKΪ�ߵ�ƽ	*/
#define	SPI_SCLK_NormalL()	SPCTL &= ~(1<<3)		/* 0: ����ʱSCLKΪ�͵�ƽ	*/
#define	SPI_PhaseH()		SPCTL |=  (1<<2)		/* 1: 	*/
#define	SPI_PhaseL()		SPCTL &= ~(1<<2)		/* 0: 	*/
#define	SPI_Speed(n)		SPCTL = (SPCTL & ~3) | (n)	/*�����ٶ�, 0 -- fosc/4, 1 -- fosc/8, 2 -- fosc/16, 3 -- fosc/32	*/

//sfr SPDAT  = 0xCF; //SPI Data Register                                                     0000,0000
//sfr SPSTAT  = 0xCD;	//SPI״̬�Ĵ���
//   7       6      5   4   3   2   1   0    	Reset Value
//	SPIF	WCOL	-	-	-	-	-	-
#define	SPIF	0x80		/* SPI������ɱ�־��д��1��0��*/
#define	WCOL	0x40		/* SPIд��ͻ��־��д��1��0��  */

#define		SPI_USE_P12P13P14P15()	P_SW1 &= ~0x0c					/* ��SPI�л���P12(SS) P13(MOSI) P14(MISO) P15(SCLK)(�ϵ�Ĭ��)��*/
#define		SPI_USE_P22P23P24P25()	P_SW1 = (P_SW1 & ~0x0c) | 0x04	/* ��SPI�л���P22(SS) P23(MOSI) P24(MISO) P25(SCLK)��*/
#define		SPI_USE_P35P34P33P32()	P_SW1 =  P_SW1 | 0x0C			/* ��SPI�л���P35(SS) P34(MOSI) P33(MISO) P32(SCLK)��*/


/*
;PCA_PWMn:    7       6     5   4   3   2     1       0
;			EBSn_1	EBSn_0	-	-	-	-	EPCnH	EPCnL
;B5-B2:		����
;B1(EPCnH):	��PWMģʽ�£���CCAPnH���9λ����
;B0(EPCnL):	��PWMģʽ�£���CCAPnL���9λ����
*/
#define		PWM0_NORMAL()	PCA_PWM0 &= ~3					/* PWM0�������(Ĭ��)	*/
#define		PWM0_OUT_0()	PCA_PWM0 |=  3, CCAP0H = 0xff	/* PWM0һֱ���0		*/
#define		PWM0_OUT_1()	PCA_PWM0 &= 0xc0, CCAP0H = 0	/* PWM0һֱ���1		*/

#define		PWMA_NORMAL()	PCA_PWMA &= ~3					/* PWMA�������(Ĭ��)	*/
#define		PWMA_OUT_0()	PCA_PWMA |=  3, CCAP1H = 0xff	/* PWMAһֱ���0		*/
#define		PWMA_OUT_1()	PCA_PWMA &= 0xc0, CCAP1H = 0	/* PWMAһֱ���1		*/

#define		PWMB_NORMAL()	PCA_PWMB &= ~3					/* PWMB�������(Ĭ��)	*/
#define		PWMB_OUT_0()	PCA_PWMB |=  3, CCAP2H = 0xff	/* PWMBһֱ���0		*/
#define		PWMB_OUT_1()	PCA_PWMB &= 0xc0, CCAP2H = 0	/* PWMBһֱ���1		*/


/**********************************************************/
typedef 	unsigned char	u8;
typedef 	unsigned int	u16;
typedef 	unsigned long	u32;

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
#define	Pin0		0x01	//IO���� Px.0
#define	Pin1		0x02	//IO���� Px.1
#define	Pin2		0x04	//IO���� Px.2
#define	Pin3		0x08	//IO���� Px.3
#define	Pin4		0x10	//IO���� Px.4
#define	Pin5		0x20	//IO���� Px.5
#define	Pin6		0x40	//IO���� Px.6
#define	Pin7		0x80	//IO���� Px.7
#define	PinAll		0xFF	//IO��������

#define	GPIO_Pin_0		0x01	//IO���� Px.0
#define	GPIO_Pin_1		0x02	//IO���� Px.1
#define	GPIO_Pin_2		0x04	//IO���� Px.2
#define	GPIO_Pin_3		0x08	//IO���� Px.3
#define	GPIO_Pin_4		0x10	//IO���� Px.4
#define	GPIO_Pin_5		0x20	//IO���� Px.5
#define	GPIO_Pin_6		0x40	//IO���� Px.6
#define	GPIO_Pin_7		0x80	//IO���� Px.7
#define	GPIO_Pin_All	0xFF	//IO��������

#define	GPIO_PullUp		0	//����׼˫���
#define	GPIO_HighZ		1	//��������
#define	GPIO_OUT_OD		2	//��©���
#define	GPIO_OUT_PP		3	//�������

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


//sfr INT_CLKO = 0x8F;	//���ӵ� SFR WAKE_CLKO (��ַ��0x8F)
/*
    7   6    5    4   3     2        1       0         Reset Value
    -  EX4  EX3  EX2  -   T2CLKO   T1CLKO  T0CLKO      0000,0000B
b6 -  EX4      : ���ж�INT4����
b5 -  EX3      : ���ж�INT3����
b4 -  EX2      : ���ж�INT2����
b2 - T1CLKO    : ���� T2 ���������P3.0�������Fck1 = 1/2 T1 �����
b1 - T1CLKO    : ���� T1 ���������P3.4�������Fck1 = 1/2 T1 �����
b0 - T0CLKO    : ���� T0 ���������P3.5�������Fck0 = 1/2 T0 �����
*/

#define		LVD_InterruptEnable()		ELVD = 1
#define		LVD_InterruptDisable()		ELVD = 0


//sfr WKTCL = 0xAA;	//STC11F\10��STC15ϵ�� ���Ѷ�ʱ�����ֽ�
//sfr WKTCH = 0xAB;	//STC11F\10��STC15ϵ�� ���Ѷ�ʱ�����ֽ�
//	B7		B6	B5	B4	B3	B2	B1	B0		B7	B6	B5	B4	B3	B2	B1	B0
//	WKTEN				S11	S10	S9	S8		S7	S6	S5	S4	S3	S2	S1	S0	n * 560us
#define		WakeTimerDisable()		WKTCH &= 0x7f	/* WKTEN = 0		��ֹ˯�߻��Ѷ�ʱ�� */
#define		WakeTimerSet(scale)		WKTCL = (scale) % 256,WKTCH = (scale) / 256 | 0x80	/* WKTEN = 1	����˯�߻��Ѷ�ʱ�� */



/////////////////////////////////////////////////
//Interrupt Vector
/////////////////////////////////////////////////
#define INT0_VECTOR         0       //FF0003H
#define TMR0_VECTOR         1       //FF000BH
#define INT1_VECTOR         2       //FF0013H
#define TMR1_VECTOR         3       //FF001BH
#define UART1_VECTOR        4       //FF0023H
#define ADC_VECTOR          5       //FF002BH
#define LVD_VECTOR          6       //FF0033H
#define UART2_VECTOR        8       //FF0043H
#define SPI_VECTOR          9       //FF004BH
#define INT2_VECTOR         10      //FF0053H
#define INT3_VECTOR         11      //FF005BH
#define TMR2_VECTOR         12      //FF0063H
#define USER_VECTOR         13      //FF006BH
#define INT4_VECTOR         16      //FF0083H
#define UART3_VECTOR        17      //FF008BH
#define UART4_VECTOR        18      //FF0093H
#define TMR3_VECTOR         19      //FF009BH
#define TMR4_VECTOR         20      //FF00A3H
#define CMP_VECTOR          21      //FF00ABH
#define I2C_VECTOR          24      //FF00C3H
#define USB_VECTOR          25      //FF00CBH
#define PWMA_VECTOR         26      //FF00D3H
#define PWMB_VECTOR         27      //FF00DBH
#define CANBUS_VECTOR       28      //FF00E3H
#define CAN2BUS_VECTOR      29      //FF00EBH
#define LINBUS_VECTOR       30      //FF00F3H

#define RTC_VECTOR          36      //FF0123H
#define P0_VECTOR           37      //FF012BH
#define P1_VECTOR           38      //FF0133H
#define P2_VECTOR           39      //FF013BH
#define P3_VECTOR           40      //FF0143H
#define P4_VECTOR           41      //FF014BH
#define P5_VECTOR           42      //FF0153H
#define P6_VECTOR           43      //FF015BH
#define P7_VECTOR           44      //FF0163H
#define DMA_M2M_VECTOR      47      //FF017BH
#define DMA_ADC_VECTOR      48      //FF0183H
#define DMA_SPI_VECTOR      49      //FF018BH
#define DMA_UR1T_VECTOR     50      //FF0193H
#define DMA_UR1R_VECTOR     51      //FF019BH
#define DMA_UR2T_VECTOR     52      //FF01A3H
#define DMA_UR2R_VECTOR     53      //FF01ABH
#define DMA_UR3T_VECTOR     54      //FF01B3H
#define DMA_UR3R_VECTOR     55      //FF01BBH
#define DMA_UR4T_VECTOR     56      //FF01C3H
#define DMA_UR4R_VECTOR     57      //FF01CBH
#define DMA_LCM_VECTOR      58      //FF01D3H
#define LCM_VECTOR          59      //FF01DBH
#define DMA_I2CT_VECTOR     60      //FF01E3H
#define DMA_I2CR_VECTOR     61      //FF01EBH
#define I2S_VECTOR          62      //FF01F3H
#define DMA_I2ST_VECTOR     63      //FF01FBH
#define DMA_I2SR_VECTOR     64      //FF0203H

//=============================================================

#define	TRUE	1
#define	FALSE	0

#define	PolityLow			0	//�����ȼ��ж�
#define	PolityHigh			1	//�����ȼ��ж�

#define		ENABLE		1
#define		DISABLE		0

#endif
