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
sfr IAP_TPS   = 0xF5;
sfr ISP_DATA = 0xc2;
sfr ISP_ADDRH = 0xc3;
sfr ISP_ADDRL = 0xc4;
sfr ISP_CMD = 0xc5;
sfr ISP_TRIG = 0xc6;
sfr ISP_CONTR = 0xc7;

#define IAP_STANDBY()   IAP_CMD = 0     //IAP���������ֹ��
#define IAP_READ()      IAP_CMD = 1     //IAP��������
#define IAP_WRITE()     IAP_CMD = 2     //IAPд������
#define IAP_ERASE()     IAP_CMD = 3     //IAP��������

#define IAP_ENABLE()    IAP_CONTR = IAP_EN
#define IAP_DISABLE()   IAP_CONTR = 0; IAP_CMD = 0; IAP_TRIG = 0; IAP_ADDRH = 0xff; IAP_ADDRL = 0xff

#define IAP_EN          (1<<7)
#define IAP_SWBS        (1<<6)
#define IAP_SWRST       (1<<5)
#define IAP_CMD_FAIL    (1<<4)

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

/*�����׵�ַ
Start Address of Sector
Each Sector contains 512 bytes*/
#define IAP_ADDRESS 0x0000

bit EEPROM_Save(uint8 *s, char para_num);
//void EEPROM_Read(uint8 *s, char para_num);
void EEPROM_read_n(uint16 EE_address,uint8 *DataAddress,uint8 length);

#endif
