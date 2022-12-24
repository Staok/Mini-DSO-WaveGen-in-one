/*
����ʾ����
���ڣ�2020-04-22
���ߣ�����������
�ο���STC8ϵ�й����
˵��������������ҵ��;�����ڱ�������ɵ��κ���ʧ�������޹ء�
�κ���������ϵCreativeLauLab@gmail.com
���������ģ�ȫ��ͬ�����ڴ����Ĺ�ע��
Bվ��Ƶ�̳̣�https://www.bilibili.com/video/BV1ai4y1t79R
ͷ����Ƶ�̳̣�https://www.ixigua.com/i6818625118101570060

Mini DSO
Date: 2020-04-22
Author: Creative Lau
Reference: STC8 Series Datasheet
Description: Do not put this code in commercial use. Author is not responsible for any loss caused by this code.
Any question please contact CreativeLauLab@gmail.com
Youtube Channel: https://www.youtube.com/channel/UCdmdxlUnprbFKZszKpb48Vg
*/
#include <reg51.h>
#include "adc_stc8.h"
#include "config_stc.h"
#include "settings.h"
#include "chart.h"
#define VBAT_UPDATE_FREQ 40 //��ص�ѹ��Ϣ�ĸ���Ƶ�� VBAT_UPDATE_FREQ*25ms
#define VBAT_LSB 6			//��ص�ѹ������ѹϵ��
#define INT_0 0 //�ⲿ�ж�0��ţ���������ת
#define INT_1 2 //�ⲿ�ж�1��ţ�����������
#define TIMER_0 1 //��ʱ��0�ж����

bit _saveSettings = 0;
uint8 n; //Ϊ��ʱ��0�жϼ���
void main()
{
    //******��������ת�ⲿ�ж�*******//
    IT0 = 0; //�ⲿ�ж�0������ʽ�������غ��½���
    PX0 = 1; //�ⲿ�ж�0�����ȼ�
    EX0 = 1; //�����ⲿ�ж�0

    //******�����������ⲿ�ж�*******//
    IT1 = 1; //�ⲿ�ж�1������ʽ���½���
    PX1 = 1; //�ⲿ�ж�1�����ȼ�
    EX1 = 1; //�����ⲿ�ж�1

	//******��ʱ��0��Ϊ���µ�ص�ѹ��Ϣ��ʱ*******//
	AUXR &= 0x7F;	//��ʱ��ʱ��12Tģʽ
	TMOD &= 0xF0;	//���ö�ʱ��ģʽ
	TL0 = 0xB0;		//���ö�ʱ��ֵ //24MHz��25ms
	TH0 = 0x3C;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	ET0=1;			//����ʱ��0�ж�
	
    EA = 1; //�����ж�

    OLED_Init();          //��ʼ��OLED
    OLED_SetFontWidth(6); //����ASCII������
                          //OLED_Clear();
    Read_Options();       //��EEPROM��ȡ���ò���

    ClearDisplay = 1; //�����Ļ
    PlotChart();
    OLED_Display();
    while (1)
    {
        ClearDisplay = 1;   //�����Ļ
        while (In_Settings) //��settings����
        {
            if (UpdateVbat)
            {
                VBat = GetVoltage(ADC_BAT,VBAT_LSB);
                UpdateVbat = 0;
            }
            if (DisplayUpdate)
            {
                PlotSettings(); //�������ý���
                OLED_Display();
                DisplayUpdate = 0;
            }
        }

        if (_saveSettings) //��������
        {
			if(OptionChanged)
			{
				_saveSettings = 0;
				OptionChanged = 0;
				PlotSaveStatus(Save_Options());
				OLED_Display();
				Delay1000ms();

				In_Settings = 0; //��ֹ�ڱ������ú���ʱ1s�����а��������ص����ý�����ߴ���Hold״̬
				HoldDisplay = 0;
			}
			_saveSettings=0; 
        }

        GetWaveData();   //����ADC
		AnalyseData();		//������������
        WaitADC = 0;     //��������������WaitADC��־
        if (Stop_Aquire) //�жϲ���
        {
            Stop_Aquire = 0;
            while (HoldDisplay)
            {
                //����Hold״̬
                ClearDisplay = 0; 	//�������Ļ
                PlotChart();		//��ʾHoldͼ��
                OLED_Display();
            }
			WaitADC = 1; 		//��ʾWait��־
			TriggerFail=0;      //����TriggerFail��־
            ClearDisplay = 1;	//�����Ļ
            PlotChart();		//����������
            OLED_Display();
        }
        else
        {
            PlotChart();   	//����������
            PlotWave();		//���Ʋ���
            OLED_Display(); 
            Delay50ms();
        }
    }
}

void Scan_EC11(void) //��������ת��Ӧ����
{
    //    EX0 = 0;                                                    //�ر��ⲿ�ж�0
    Delay500us();                                                     //��ʱȥ�źŶ���
    if ((EC11_A == 0 && EC11_B == 1) || (EC11_A == 1 && EC11_B == 0)) //��ת������ֵ
    {
        Change_Val(1);
    }
    else if ((EC11_A == 0 && EC11_B == 0) || (EC11_A == 1 && EC11_B == 1)) //��ת��С��ֵ
    {
        Change_Val(0);
    }
    IE0 = 0; //��������źŶ����������ⲿ�ж�1��־
    //    EX0 = 1; //���¿����ⲿ�ж�0
}

/*
��ת��������ת�жϣ�
�������棨��Hold״̬������ʱ�����͵�ѹ������ֵ
�������棨Hold״̬����ʱ�����͵�ѹ����֮���л�
�����ý��棬����LSB��DrawModeѡ��
*/
void INT0_interrupt(void) interrupt INT_0 
{
    Scan_EC11();       //����EC11ת������
    Stop_Aquire = 1;   //֪ͨADCֹͣ����
    DisplayUpdate = 1; //������Ļ��Ϣ
    TriggerFail = 0;
    if (!HoldDisplay) //����Hold״̬�£���λ�����޸ı�־λ
    {
        OptionChanged = 1;
    }
}

//��ת����������ж�
void INT1_interrupt(void) interrupt INT_1 
{
    bit k = 0;
    Delay50ms();
    if (!EC11_KEY)
    {
		//��������������
		//�л�����������ý���
        if (Delay500ms_long_click()) 
        {
            In_Settings = ~In_Settings; //�л�����������ý���
            if (HoldDisplay)	   //��Holdģʽ��
                HoldDisplay = 0;   //�˳�Hold״̬
            if (In_Settings)       //�������ý���
			{
				TF0 = 0;			//���TF0��־
				TR0 = 1;			//��ʱ��0��ʼ��ʱ
                UpdateVbat = 1;    	//���µ�ص�ѹ��Ϣ
			}
            if (!In_Settings)      //�˳����ý���
			{
				TR0 = 0;		//��ʱ��0ֹͣ��ʱ
				TF0 = 0;		//���TF0��־
                _saveSettings = 1; //��λ�����־
			}
            Stop_Aquire = 1;       //֪ͨADCֹͣ����
            DisplayUpdate = 1;     //֪ͨ��Ļ�����
            ClearDisplay = 1;      //�����Ļ
        }
		//˫������������
		//�л�������ʽ�������½�
        else if (Delay200ms_double_click()) 
        {
            if (!HoldDisplay && !In_Settings) //����hold״̬�����ý���
            {
                k = 1;           //���жϺ������������жϰ����Ƿ�̧�����Ӹ����������ó����ƹ�����̧���жϣ����Լ�ʱˢ��LCD����˫��������Ҫ�жϰ���̧�𣬱���˫�����津��һ���̰�
                TriD = ~TriD;    //�ı䴥������
                Stop_Aquire = 1; //֪ͨADCֹͣ����
            }
        }
		//��������������
		//���������л�Hold״̬
		//�����ý����л�����ѡ��
        else 
        {
            if (In_Settings) //�����ý���
            {
                Option_In_Settings++; //�л�����ѡ��
                if (Option_In_Settings > 1)
                    Option_In_Settings = 0;
                DisplayUpdate = 1; //֪ͨ��Ļ�����
            }
            else //��������
            {
                HoldDisplay = ~HoldDisplay; //�л�Hold״̬
                //ClearDisplay = 1;
                Stop_Aquire = 1; //֪ͨADCֹͣ����
            }
        }
    }
    //   Delay50ms();
    while (!EC11_KEY && k) //�ȴ�˫�������������̧��
        ;
}

void TIMER0_interrupt(void) interrupt TIMER_0 
{
	if(++n>=VBAT_UPDATE_FREQ)
	{
		n=0;
		UpdateVbat=1;
		DisplayUpdate=1;
	}	
}