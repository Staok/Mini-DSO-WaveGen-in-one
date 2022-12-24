#ifndef ADC_STC15_H
#define ADC_STC15_H

#define STC15
#ifdef STC15

//#include "stc_header.h"
#include "delay.h"

#ifndef uint8
#define uint8 unsigned char
#endif

#ifndef uint16
#define uint16 unsigned int
#endif	

#ifndef uint32
#define uint32 unsigned long int
#endif

//Bandgap��ѹ��RAM��ROM�еĴ�ŵ�ַ����λmV��RAM�е������п��ܱ�����������Ƽ�ʹ��ROM�е����ݣ�RAM�е����ݿ�����Ϊ��ѡ
//WORD idata Vbg_RAM _at_ 0xef; //����ֻ��256�ֽ�RAM��MCU��ŵ�ַΪ0EFH
//WORD idata Vbg_RAM _at_ 0x6f; //����ֻ��128�ֽ�RAM��MCU��ŵ�ַΪ06FH
//ע��:��Ҫ�����ش���ʱѡ��"��ID��ǰ��?��Ҫ���Բ���"ѡ��,�ſ��ڳ���ROM�л�ȡ�˲���
//WORD code Vbg_ROM _at_ 0x03f7; //1K����ռ��MCU
//WORD code Vbg_ROM _at_ 0x07f7; //2K����ռ��MCU
//WORD code Vbg_ROM _at_ 0x0bf7; //3K����ռ��MCU
//WORD code Vbg_ROM _at_ 0x0ff7; //4K����ռ��MCU
//WORD code Vbg_ROM _at_ 0x13f7; //5K����ռ��MCU
//WORD code Vbg_ROM _at_ 0x1ff7; //8K����ռ��MCU
//WORD code Vbg_ROM _at_ 0x27f7; //10K����ռ��MCU
//WORD code Vbg_ROM _at_ 0x2ff7; //12K����ռ��MCU
//WORD code Vbg_ROM _at_ 0x3ff7; //16K����ռ��MCU
//WORD code Vbg_ROM _at_ 0x4ff7; //20K����ռ��MCU
//WORD code Vbg_ROM _at_ 0x5ff7; //24K����ռ��MCU
//WORD code Vbg_ROM _at_ 0x6ff7; //28K����ռ��MCU
//WORD code Vbg_ROM _at_ 0x7ff7; //32K����ռ��MCU
//WORD code Vbg_ROM _at_ 0x9ff7; //40K����ռ��MCU
//WORD code Vbg_ROM _at_ 0xbff7; //48K����ռ��MCU
//WORD code Vbg_ROM _at_ 0xcff7; //52K����ռ��MCU
//WORD code Vbg_ROM _at_ 0xdff7; //56K����ռ��MCU
//WORD code Vbg_ROM _at_ 0xeff7; //60K����ռ��MCU
//WORD code Vbg_ROM _at_ 0xfdf7; //64K����ռ��MCU
#define BGV_ADR 0x7ff7
//-----------------------------------------
sfr ADC_CONTR = 0xBC; //ADC���ƼĴ���
sfr ADC_RES = 0xBD; //ADC��8λ���
sfr ADC_RESL = 0xBE; //ADC��2λ���
sfr P1ASF = 0x9D; //P1�ڵ�2���ܿ��ƼĴ���
sfr CLK_DIV =   0x97;   //0000,0000 ʱ�ӷ�Ƶ���ƼĴ���

#define ADC_POWER 0x80   	//ADC��Դ����λ
#define ADC_FLAG 0x10		//ADC��ɱ�־
#define ADC_START 0x08   	//ADC��ʼ����λ
#define ADC_SPEEDLL 0x00 	//540��ʱ��
#define ADC_SPEEDL 0x20  	//360��ʱ��
#define ADC_SPEEDH 0x40  	//180��ʱ��
#define ADC_SPEEDHH 0x60 	//90��ʱ��		
#define ADRJ 0x20 			//��ADRJ=1ʱ�� 10λA/Dת������ĸ�2λ�����ADC_RES�ĵ�2λ�У���8λ�����ADC_RESL��
							//��ADRJ=0ʱ�� 10λA/Dת������ĸ�8λ�����ADC_RES�У���2λ�����ADC_RESL�ĵ�2λ��
#define ADC_CHS_10 0x00 	//��P1.0��ģ��ֵ����ADCģ��ͨ��
#define ADC_CHS_11 0x01 	//��P1.1��ģ��ֵ����ADCģ��ͨ��
#define ADC_CHS_12 0x02 	//��P1.2��ģ��ֵ����ADCģ��ͨ��
#define ADC_CHS_13 0x03 	//��P1.3��ģ��ֵ����ADCģ��ͨ��
#define ADC_CHS_14 0x04 	//��P1.4��ģ��ֵ����ADCģ��ͨ��
#define ADC_CHS_15 0x05 	//��P1.5��ģ��ֵ����ADCģ��ͨ��
#define ADC_CHS_16 0x06 	//��P1.6��ģ��ֵ����ADCģ��ͨ��
#define ADC_CHS_17 0x07 	//��P1.7��ģ��ֵ����ADCģ��ͨ��
#define ADC_CHS_BG 0x09 	//���ڲ�BandGap����Ϊ�ھ�ͨ��
#define P1ASF_0 0x01		//��P1.0����ΪADģ������ģʽ
#define P1ASF_1 0x02		//��P1.1����ΪADģ������ģʽ
#define P1ASF_2 0x04		//��P1.2����ΪADģ������ģʽ
#define P1ASF_3 0x08		//��P1.3����ΪADģ������ģʽ
#define P1ASF_4 0x10		//��P1.4����ΪADģ������ģʽ
#define P1ASF_5 0x20		//��P1.5����ΪADģ������ģʽ
#define P1ASF_6 0x40		//��P1.6����ΪADģ������ģʽ
#define P1ASF_7 0x80		//��P1.7����ΪADģ������ģʽ
#define P1ASF_BG 0x00		//���ڲ�BandGapʱ���ر�����ADCͨ��

uint16 Get_VCC_Voltage();

#endif
#endif