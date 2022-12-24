/* EEPROM Functions. 
   Reference STC8 Series Datasheet */
#include "eeprom.h"

/*----------------------------
�ر�IAP
----------------------------*/
void IapIdle()
{
    IAP_CONTR = 0;     //�ر�IAP����
    IAP_CMD = IAP_IDL; //�������Ĵ���
    IAP_TRIG = 0;      //��������Ĵ���
    IAP_ADDRH = 0x80;  //����ַ���õ���IAP����
    IAP_ADDRL = 0;
}
/*----------------------------
��ISP/IAP/EEPROM�����ȡһ�ֽ�
----------------------------*/
uint8 IapReadByte(uint16 addr)
{
    uint8 dat;                  //���ݻ�����
    IAP_CONTR = IAPEN | IAP_WT; //ʹ��IAP
    IAP_CMD = IAP_READ;         //����IAP����
    IAP_ADDRL = addr;           //����IAP�͵�ַ
    IAP_ADDRH = addr >> 8;      //����IAP�ߵ�ַ
    IAP_TRIG = 0x5a;            //д��������(0x5a)
    IAP_TRIG = 0xa5;            //д��������(0xa5)
    _nop_();                    //�ȴ�ISP/IAP/EEPROM�������
    dat = IAP_DATA;             //��ISP/IAP/EEPROM����
    IapIdle();                  //�ر�IAP����
    return dat;                 //����
}

/*----------------------------
дһ�ֽ����ݵ�ISP/IAP/EEPROM����
----------------------------*/
void IapProgramByte(uint16 addr, uint8 dat)
{
    IAP_CONTR = IAPEN | IAP_WT; //ʹ��IAP
    IAP_CMD = IAP_WRITE;        //����IAP����
    IAP_ADDRL = addr;           //����IAP�͵�ַ
    IAP_ADDRH = addr >> 8;      //����IAP�ߵ�ַ
    IAP_DATA = dat;             //дISP/IAP/EEPROM����
    IAP_TRIG = 0x5a;            //д��������(0x5a)
    IAP_TRIG = 0xa5;            //д��������(0xa5)
    _nop_();                    //�ȴ�ISP/IAP/EEPROM�������
    IapIdle();
}
/*----------------------------
��������
----------------------------*/
void IapEraseSector(uint16 addr)
{
    IAP_CONTR = IAPEN | IAP_WT; //ʹ��IAP
    IAP_CMD = IAP_ERASE;        //����IAP����
    IAP_ADDRL = addr;           //����IAP�͵�ַ
    IAP_ADDRH = addr >> 8;      //����IAP�ߵ�ַ
    IAP_TRIG = 0x5a;            //д��������(0x5a)
    IAP_TRIG = 0xa5;            //д��������(0xa5)
    _nop_();                    //�ȴ�ISP/IAP/EEPROM�������
    IapIdle();
}

/* Write EEPROM
   s: Pointer to parameters
   para_num: Length of parameters */
bit EEPROM_Save(uint8 *s, uint8 para_num)
{
    int i; //��Ҫ�ĳ�uint8������˺ü��Σ���
	//��������
    IapEraseSector(IAP_ADDRESS); 
	//����Ƿ�����ɹ�(ȫFF���)
    for (i = 0; i < 512; i++)    
    {
        if (IapReadByte(IAP_ADDRESS + i) != 0xff)
            return 0; 
    }
	//���EEPROM
    for (i = 0; i < para_num; i++) 
    {
        IapProgramByte(IAP_ADDRESS + i, *(s + i));
    }
	//У��EEPROM
    for (i = 0; i < para_num; i++) 
    {
        if (IapReadByte(IAP_ADDRESS + i) != *(s + i))
            return 0; 
    }

    return 1;
}

/* Read EEPROM
   s: Pointer to parameters
   para_num: Length of parameters */
void EEPROM_Read(uint8 *s, uint8 para_num)
{
    uint8 i;

    for (i = 0; i < para_num; i++) 
    {
        *s++ = IapReadByte(IAP_ADDRESS + i);
    }
}
