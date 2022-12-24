/*
    adc_stc8.h

    Sampling with ADC built in MCU
    
    Copyright (c) 2020 Creative Lau (creativelaulab@gmail.com)

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#ifndef ADC_STC8_H
#define ADC_STC8_H

#define STC8
#ifdef STC8

#include "config_stc.h"
#include "intrins.h"
#include "delay.h"
#include "chart.h"
#include <string.h>

#ifndef uint8
#define uint8 unsigned char
#endif

#ifndef uint16
#define uint16 unsigned int
#endif

#ifndef uint32
#define uint32 unsigned long int
#endif

//ADC ���⹦�ܼĴ���
sfr ADC_CONTR = 0xbc;
sfr ADC_RES = 0xbd;
sfr ADC_RESL = 0xbe;
sfr ADCCFG = 0xde;

//Bandgap��ѹ��RAM��ROM�еĴ�ŵ�ַ����λmV��RAM�е������п��ܱ�����������Ƽ�ʹ��ROM�е����ݣ�RAM�е����ݿ�����Ϊ��ѡ
//WORD idata Vbg_RAM _at_ 0xef; //����ֻ��256�ֽ�RAM��MCU��ŵ�ַΪ0EFH
//idata �� EFH ��ַ��Ÿ��ֽ�
//idata �� F0H ��ַ��ŵ��ֽ�
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
#define BGV_ADR 0xfdf7
#define ADC_POWER 0x80     //ADC��Դ����λ
#define ADC_FLAG 0x20      //ADC��ɱ�־
#define ADC_START 0x40     //ADC��ʼ����λ
#define ADC_SPEED_512 0x0F //512��ʱ��
#define ADC_SPEED_480 0x0E //480��ʱ��
#define ADC_SPEED_448 0x0D //448��ʱ��
#define ADC_SPEED_416 0x0C //416��ʱ��
#define ADC_SPEED_384 0x0B //384��ʱ��
#define ADC_SPEED_352 0x0A //352��ʱ��
#define ADC_SPEED_320 0x09 //320��ʱ��
#define ADC_SPEED_288 0x08 //288��ʱ��
#define ADC_SPEED_256 0x07 //256��ʱ��
#define ADC_SPEED_224 0x06 //224��ʱ��
#define ADC_SPEED_192 0x05 //192��ʱ��
#define ADC_SPEED_160 0x04 //160��ʱ��
#define ADC_SPEED_128 0x03 //128��ʱ��
#define ADC_SPEED_96 0x02  //96��ʱ��
#define ADC_SPEED_64 0x01  //64��ʱ��
#define ADC_SPEED_32 0x00  //32��ʱ��
#define RESFMT 0x20        //ת���������λ�������0x00���Ҷ���0x20
#define ADC_CHS_10 0x00    //��P1.0��ģ��ֵ����ADCģ��ͨ��
#define ADC_CHS_11 0x01    //��P1.1��ģ��ֵ����ADCģ��ͨ��
#define ADC_CHS_12 0x02    //��P1.2��ģ��ֵ����ADCģ��ͨ��
#define ADC_CHS_13 0x03    //��P1.3��ģ��ֵ����ADCģ��ͨ��
#define ADC_CHS_14 0x04    //��P1.4��ģ��ֵ����ADCģ��ͨ��
#define ADC_CHS_15 0x05    //��P1.5��ģ��ֵ����ADCģ��ͨ��
#define ADC_CHS_16 0x06    //��P1.6��ģ��ֵ����ADCģ��ͨ��
#define ADC_CHS_17 0x07    //��P1.7��ģ��ֵ����ADCģ��ͨ��
#define ADC_CHS_00 0x08    //��P0.0��ģ��ֵ����ADCģ��ͨ��
#define ADC_CHS_01 0x09    //��P0.1��ģ��ֵ����ADCģ��ͨ��
#define ADC_CHS_02 0x0A    //��P0.2��ģ��ֵ����ADCģ��ͨ��
#define ADC_CHS_03 0x0B    //��P0.3��ģ��ֵ����ADCģ��ͨ��
#define ADC_CHS_04 0x0C    //��P0.4��ģ��ֵ����ADCģ��ͨ��
#define ADC_CHS_05 0x0D    //��P0.5��ģ��ֵ����ADCģ��ͨ��
#define ADC_CHS_06 0x0E    //��P0.6��ģ��ֵ����ADCģ��ͨ��
#define ADC_CHS_BG 0x0F    //����16ͨ�����ڲ�BandGap�ο���ѹ����ģ��ֵ����ADCģ��ͨ��

uint16 GetADC_CHX(uint8 chx);                 //���chxͨ��ADC
uint16 GetVoltage(uint8 chx, uint16 lsb);     //���chxͨ����ѹֵ mV
uint16 *GetBGV(void);                         //����ڲ��ο���ѹBGV mV
uint16 *GetWaveADC(uint8 chx, uint8 scale_h); //��ò��β���

#endif
#endif