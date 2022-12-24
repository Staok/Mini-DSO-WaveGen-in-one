#ifndef EEPROM_H
#define EEPROM_H

#include "intrins.h"

#ifndef uint8
#define uint8 unsigned char
#endif

#ifndef uint16
#define uint16 unsigned int
#endif

#ifndef uint32
#define uint32 unsigned long int
#endif

/*IAP/ISP ���⹦�ܼĴ���
IAP/ISP Special Function Register*/
sfr IAP_DATA = 0xc2;
sfr IAP_ADDRH = 0xc3;
sfr IAP_ADDRL = 0xc4;
sfr IAP_CMD = 0xc5;
sfr IAP_TRIG = 0xc6;
sfr IAP_CONTR = 0xc7;
sfr ISP_DATA = 0xc2;
sfr ISP_ADDRH = 0xc3;
sfr ISP_ADDRL = 0xc4;
sfr ISP_CMD = 0xc5;
sfr ISP_TRIG = 0xc6;
sfr ISP_CONTR = 0xc7;

#define IAP_IDL 0x00   //�ղ��� / No operation
#define IAP_READ 0x01  //��EEPROM / Read EEPROM
#define IAP_WRITE 0x02 //дEEPROM / Write EEPROM
#define IAP_ERASE 0x03 //����EEPROM / Erase EEPROM
#define IAPEN 0x80     //ʹ��IAP / Enable IAP
#define SWBS 0x40      /*�����λѡ�����λ 0�������λ����û����뿪ʼִ�г��� 1�������λ���ϵͳ ISP ��ش�������ʼִ�г��� \
                        Software boot selection control bit, which should be used with SWRST                                                                                 \
                        0 : Execute the program from the user code area after the software reset                                                                             \
                        1 : Execute the program from the ISP memory area after the software reset*/
#define SWRST 0x20     /*�����λ����λ 0���޶��� 1�����������λ \
                       Software reset trigger control                               \
                       0 : No operation                                             \
                       1: Generate software reset.*/
#define CMD_FAIL 0x10  /*EEPROM����ʧ��״̬λ����Ҫ������� 0�� EEPROM ������ȷ 1�� EEPROM ����ʧ�� \
                       Command fail status bit for EEPROM operation which should be cleared by software                     \
                       0 : EEPROM operation is right                                                                        \
                       0: EEPROM operation is right*/
/*EEPROM�����ĵȴ�ʱ��
EEPROM operation waiting time*/
#define IAP_WT 0x00 //if SYSCLK<30MHz
//#define IAP_WT 0x01 //if SYSCLK<24MHz
//#define IAP_WT 0x02 //if SYSCLK<20MHz
//#define IAP_WT 0x03 //if SYSCLK<12MHz
//#define IAP_WT 0x04 //if SYSCLK<6MHz
//#define IAP_WT 0x05 //if SYSCLK<3MHz
//#define IAP_WT 0x06 //if SYSCLK<2MHz
//#define IAP_WT 0x07 //if SYSCLK<1MHz

/*�����׵�ַ
Start Address of Sector
Each Sector contains 512 bytes*/
#define IAP_ADDRESS 0x0000

bit EEPROM_Save(uint8 *s, char para_num);
void EEPROM_Read(uint8 *s, char para_num);

#endif
