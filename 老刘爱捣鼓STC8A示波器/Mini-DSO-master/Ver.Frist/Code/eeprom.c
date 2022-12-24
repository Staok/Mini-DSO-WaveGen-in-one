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

//s ����ָ��
//para_num ��������
bit EEPROM_Save(uint8 *s, uint8 para_num)
{
    int i;
    IapEraseSector(IAP_ADDRESS); //��������
    for (i = 0; i < 512; i++)    //����Ƿ�����ɹ�(ȫFF���)
    {
        if (IapReadByte(IAP_ADDRESS + i) != 0xff)
            return 0; //�������,���˳�
    }
    //Delay50ms();
    for (i = 0; i < para_num; i++) //���EEPROM
    {
        IapProgramByte(IAP_ADDRESS + i, *(s + i));
        //UartSendData(*(s+i));
    }
    //Delay50ms();
    for (i = 0; i < para_num; i++) //У��EEPROM
    {
        //		if (UartSendData(IapReadByte(IAP_ADDRESS + i)) != *(s+i))
        if (IapReadByte(IAP_ADDRESS + i) != *(s + i))
            return 0; //���У�����,���˳�
    }
    return 1;
    //	Error:
    //	//P0 &= 0x7f; //0xxx,xxxx IAP����ʧ��
    //	return 0;
}

void EEPROM_Read(uint8 *s, uint8 para_num)
{
    uint8 i;
    for (i = 0; i < para_num; i++) //��ȡEEPROM
    {
        //s[i]=UartSendData(IapReadByte(IAP_ADDRESS + i));
        *s++ = IapReadByte(IAP_ADDRESS + i);
    }
}
