

/*************	功能说明	**************

480x320 3.2寸TFT LCD 的基本驱动程序，控制器是ILI9481BDS。

TFT480x320-V2.c  改进、优化程序.

******************************************/

#include	"TFT480x320.h"
#include	"ASCII5x7.h"
#include	"HZK12.h"
#include	"ASCII_8x16_H.h"
#include	"HZK16.h"

u16	foreground,background;


/****** 定义LCD接口 *********/
sbit LCD_RS  = P4^5;
sbit LCD_WR  = P4^2;
sbit LCD_CS  = P4^3;
sbit LCD_RST = P4^1;
sfr	 LCD_BUS_H = 0xE8;	//P0--0x80,P1=0x90,P2=0xA0,P3=0x0B0, P6= 0xE8
sfr	 LCD_BUS_L = 0xA0;	//P0--0x80,P1=0x90,P2=0xA0,P3=0x0B0, P6= 0xE8



/**** LCD基本操作宏定义 ***********/

#define LCD_CS_SET()		LCD_CS = 1
#define LCD_CS_CLR()		LCD_CS = 0

#define LCD_RST_SET()		LCD_RST = 1
#define LCD_RST_CLR()		LCD_RST = 0

#define LCD_RS_SET()		LCD_RS = 1
#define LCD_RS_CLR()		LCD_RS = 0

#define LCD_WR_SET()		LCD_WR = 1
#define LCD_WR_CLR()		LCD_WR = 0

#define LCD_RD_SET()		LCD_RD = 1
#define LCD_RD_CLR()		LCD_RD = 0

#define LCD_WriteWord(n) 	LCD_BUS_H = (u8)(n>>8); LCD_BUS_L = (u8)n; NOP(1);	LCD_WR_CLR(); NOP(1);	LCD_WR_SET();	NOP(1);	

#define	LCD_WR_PULSE()		NOP(1);	LCD_WR_CLR(); NOP(1);	LCD_WR_SET()


//========================================================================
// 函数: void LCD_delay(u16 ms)
// 描述: 延时函数
// 参数: ms 延时时间 1~65535 ms
// 返回: 无
// 版本:
//========================================================================
void LCD_delay(u16 ms)
{
    u16 i;
	do{
	//	i = MAIN_Fosc / 14000;	//STC12F
	//	i = MAIN_Fosc / 13000;	//STC15F
	//	i = MAIN_Fosc / 10000;	//STC8
		i = MAIN_Fosc / 6000;	//STC32G
		while(--i)	;
    }while(--ms);
}


//========================================================================
// 函数: void LCD_RegWriteComd(u8 cmd)
// 描述: 写一个字节的命令至LCD中的控制寄存器当中
// 参数: cmd: 寄存器命令
// 返回: 无
// 备注: 
// 版本:
//      2007/04/10      First version
//========================================================================
void LCD_RegWriteComd(u8 cmd)
{
	LCD_RS_CLR();			//point to ID register
	LCD_CS_CLR();
	LCD_BUS_H = 0;
	LCD_BUS_L = cmd;
	LCD_WR_PULSE();
	LCD_RS_SET();			//point to GRAM
	LCD_CS_SET();
}

//=========== 写一个字节的数据至LCD中的控制寄存器当中 ===================
void LCD_RegWriteData(u8 dat)
{
//	LCD_RS_SET();			//point to GRAM
	LCD_CS_CLR();
	LCD_BUS_H = 0;
	LCD_BUS_L = dat;
	LCD_WR_PULSE();
	LCD_CS_SET();
}


//========================================================================
// 函数: void LCD_Init(void)
// 描述: LCD初始化程序，在里面会完成LCD初始所需要设置的许多寄存器，具体如果
//		 用户想了解，建议查看DataSheet当中各个寄存器的意义
// 参数: 无 
// 返回: 无
// 版本: V1.0
//========================================================================
void LCD_Init(void)
{
	P6n_standard(0xff);
	P2n_standard(0xff);
	P4n_standard(0x2e);

	background = 0x00;
	foreground = 0xffff;

	LCD_RS_SET();
	LCD_CS_SET();
	LCD_BUS_H = 0xFF;
	LCD_BUS_L = 0xFF;
	LCD_WR_SET();

	LCD_RST_SET();
	LCD_delay(150);
	LCD_RST_CLR();
	LCD_delay(150);
	LCD_RST_SET();
	LCD_delay(150);

	//************* ILI9481初始化**********//
	LCD_RegWriteComd(0x11);
	LCD_delay(20);
	LCD_RegWriteComd(0xD0);
	LCD_RegWriteData(0x07);
	LCD_RegWriteData(0x42);
	LCD_RegWriteData(0x18);
	
	LCD_RegWriteComd(0xD1);
	LCD_RegWriteData(0x00);
	LCD_RegWriteData(0x07);//07
	LCD_RegWriteData(0x10);
	
	LCD_RegWriteComd(0xD2);
	LCD_RegWriteData(0x01);
	LCD_RegWriteData(0x02);
	
	LCD_RegWriteComd(0xC0);
	LCD_RegWriteData(0x10);
	LCD_RegWriteData(0x3B);
	LCD_RegWriteData(0x00);
	LCD_RegWriteData(0x02);
	LCD_RegWriteData(0x11);
	
	LCD_RegWriteComd(0xC5);
	LCD_RegWriteData(0x03);
	
	LCD_RegWriteComd(0xC8);
	LCD_RegWriteData(0x00);
	LCD_RegWriteData(0x32);
	LCD_RegWriteData(0x36);
	LCD_RegWriteData(0x45);
	LCD_RegWriteData(0x06);
	LCD_RegWriteData(0x16);
	LCD_RegWriteData(0x37);
	LCD_RegWriteData(0x75);
	LCD_RegWriteData(0x77);
	LCD_RegWriteData(0x54);
	LCD_RegWriteData(0x0C);
	LCD_RegWriteData(0x00);
	
	LCD_RegWriteComd(0x36);
	#if (X_DOTS == 320)
		LCD_RegWriteData(0x0A);
	#endif
	#if (X_DOTS == 480)
		LCD_RegWriteData(0x28);
	#endif
	
	LCD_RegWriteComd(0x3A);
	LCD_RegWriteData(0x55);
	
	LCD_RegWriteComd(0x2A);
	LCD_RegWriteData(0x00);
	LCD_RegWriteData(0x00);
//	LCD_RegWriteData(0x01);
//	LCD_RegWriteData(0x3F);
	LCD_RegWriteData(((X_DOTS-1)>>8));
	LCD_RegWriteData(((X_DOTS-1)&0xff));
	
	LCD_RegWriteComd(0x2B);
	LCD_RegWriteData(0x00);
	LCD_RegWriteData(0x00);
//	LCD_RegWriteData(0x01);
//	LCD_RegWriteData(0xE0);
	LCD_RegWriteData(((Y_DOTS-1)>>8));
	LCD_RegWriteData(((Y_DOTS-1)&0xff));

	LCD_delay(120);
//	LCD_RegWriteComd(0x21);	//取反显示, 有的屏要取反才是正常显示
	LCD_RegWriteComd(0x29);
	LCD_RegWriteComd(0x2c);

	//设置LCD属性参数
	SetView_V();		//竖屏
	LCD_delay(1);
	LCD_Fill_XY(0,0,X_DOTS,Y_DOTS,0x0000);

}


/*************************************************
函数: void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd)
功能: 设置lcd显示窗口，在此区域写点数据自动换行. 每行从 xStar开始 到yStar结束, 如果xStar==yStar则只写一点便换行, 可以用于画竖线.
入口: xy起点和终点
返回: 无
*************************************************/
void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd)
{
	LCD_RegWriteComd(0x2a);	
	LCD_RegWriteData((u8)(xStar>>8));
	LCD_RegWriteData((u8)(xStar &0xff));		
	LCD_RegWriteData((u8)(xEnd>>8));
	LCD_RegWriteData((u8)(xEnd &0xff));

	LCD_RegWriteComd(0x2b);	
	LCD_RegWriteData((u8)(yStar>>8));
	LCD_RegWriteData((u8)(yStar &0xff));		
	LCD_RegWriteData((u8)(yEnd>>8));
	LCD_RegWriteData((u8)(yEnd &0xff)); 

	LCD_RegWriteComd(0x2c);	//开始写入GRAM
}   

//========================================================================
// 函数: void LCD_Fill_XY(u8 x0,u16 y0,u8 x,u16 y,u16 color)
// 描述: 给屏填充开始坐标为x0,y0,长x,高y,以color的数据至各点中
// 参数: x0,y0 开始坐标,  x 长,	y 高, color: 要填充的颜色数据
// 返回: 无
// 版本: V1.0
//========================================================================
void LCD_Fill_XY(u16 x0,u16 y0,u16 x,u16 y,u16 color)
{
	u8 i;

	LCD_SetWindows(x0,y0,x0+x-1,y0+y-1);	//设置显示窗口
	LCD_RS = 1;	LCD_CS_CLR();
	LCD_BUS_H = (u8)(color>>8);
	LCD_BUS_L = (u8)color;

	i = (u8)(((u32)x *(u32)y) & 7);	//先写不足8倍的余数
	while(i != 0)
	{
		LCD_WR_PULSE();
		i--;
	}
	x = (u16)(((u32)x *(u32)y) /8);	//写8倍点
	while(x != 0)	//平均每个循坏额外增加8T
	{
		LCD_WR_PULSE();	//发一个写脉冲, 则写入一个点(2字节).
		LCD_WR_PULSE();
		LCD_WR_PULSE();
		LCD_WR_PULSE();
		LCD_WR_PULSE();
		LCD_WR_PULSE();
		LCD_WR_PULSE();
		LCD_WR_PULSE();
		x--;
	}
	LCD_CS_SET();

}


/**********************************************/
/*	x,y为起始坐标,index为ASCII字符	*/
void text_ascii5x7(u16 x,u16 y,u8 index)
{
	u8 const *p;
 	u8 i,s,b;

	if(x > 474)	return;	//溢出
	if(y > 314)	return;	//溢出

	LCD_SetWindows(x,y,x+5-1,y+8-1);
	LCD_RS = 1;	LCD_CS = 0;

	p = (u16)index * 8 + ASCII5x7;
	for(i=0; i<8; i++)
	{    
		b = *p;	p++;
		for(s=0; s<5; s++)
		{
			if(b & 0x10)	{LCD_WriteWord(foreground);}
			else			{LCD_WriteWord(background);}
			b <<= 1;
		}
	}
	LCD_CS = 1;
}

//========================================================================
// 函数: void HZ_12x12s(u16 x,u16 y,u16 hz_code)
// 描述: 以x,y为起始坐标,hz为汉字首地址，显示11*11的汉字。
//		 在背景色background上用前景色foreground显示汉字。
// 参数: x  y轴坐标     hz 汉字首地址
// 返回: 无
// 备注: 使用前景色
//========================================================================
void HZ_12x12s(u16 x,u16 y,u16 hz_code)
{
	u8 const *p;
	u8 i,s,b;

	if(x > 468)	return;	//溢出
	if(y > 308)	return;	//溢出

 	LCD_SetWindows(x,y,x+12-1,y+12-1);
	LCD_RS = 1;	LCD_CS = 0;

	p = hz_code * 18 + HZK12;
	for(i=0; i<18; i++)
	{    
		b = *p;	p++;
 		for(s=0; s<8; s++)
		{
			if(b & 0x80)	{LCD_WriteWord(foreground);}
			else			{LCD_WriteWord(background);}
			b <<= 1;
		}
	}
	LCD_CS = 0;
}

/************ 字符串显示 *************************/
void	printf_text(u16 x,u16 y,u8 *ptr)
{
    u8 c1,c2,i;
	
	for (;;)
	{
        c1 = *ptr;
		ptr++;
		if(c1 == 0)		return;	//遇到停止符0结束
		if(c1 < 0xa0)			//ASCII码
		{
			text_ascii5x7(x,y+2,c1);
			x += 6;
		}
		else					//汉字
		{
			c2 = *ptr;
			ptr++;
			if(c2 == 0)		return;	//遇到停止符0结束

			for(i=0; i < sizeof(HZK)/2; i++)    // 查找定位
			{				
				if((c1 == HZK[i*2]) && (c2 == HZK[i*2+1]))
				{
					HZ_12x12s(x,y,(u16)i);
					x += 12;
				}
			}
		}
	}
} 

//========================================================================
// 函数: void Line_h(u8 x,u16 y,u8 lenth,u16 color)
// 描述: 在x、y为起始坐标，lenth为长度，color为颜色绘制一条横线
// 参数: x  X轴坐标     y  Y轴坐标
// 返回: 无
// 备注: 使用前景色
// 版本: V1.0
//========================================================================
void	Line_h(u16 x,u16 y,u16 lenth,u16 color)
{  
	u8	i;
	
	LCD_SetWindows(x,y,x+lenth-1, y);
	LCD_CS_CLR();
	LCD_BUS_H = (u8)(color>>8);
	LCD_BUS_L = (u8)color;

	i = (u8)lenth & 7;
	while(i != 0)
	{
		LCD_WR_PULSE();
		i--;
	}
	i = (u8)(lenth >> 3);
	while(i != 0)
	{
		LCD_WR_PULSE();	//发一个写脉冲, 则写入一个点(2字节).
		LCD_WR_PULSE();
		LCD_WR_PULSE();
		LCD_WR_PULSE();
		LCD_WR_PULSE();
		LCD_WR_PULSE();
		LCD_WR_PULSE();
		LCD_WR_PULSE();
		i--;
	}
	LCD_CS_SET();
}

//========================================================================
// 函数: void Line_v(u8 x,u16 y,u16 lenth,u16 color)
// 描述: 在x、y为起始坐标，lenth为长度，color为颜色绘制一条竖线
// 参数: x  X轴坐标     y  Y轴坐标
// 返回: 无
// 备注: 使用前景色
// 版本: V1.0
//========================================================================
void	Line_v(u16 x,u16 y,u16 lenth,u16 color)
{  
	u8	i;

	LCD_SetWindows(x,y,x,y+lenth-1);
	LCD_CS_CLR();
	LCD_BUS_H = (u8)(color>>8);
	LCD_BUS_L = (u8)color;

	i = (u8)lenth & 7;
	while(i != 0)
	{
		LCD_WR_PULSE();
		i--;
	}
	i = (u8)(lenth >> 3);
	while(i != 0)
	{
		LCD_WR_PULSE();	//发一个写脉冲, 则写入一个点(2字节).
		LCD_WR_PULSE();
		LCD_WR_PULSE();
		LCD_WR_PULSE();
		LCD_WR_PULSE();
		LCD_WR_PULSE();
		LCD_WR_PULSE();
		LCD_WR_PULSE();
		i--;
	}
	LCD_CS_SET();
}


//========================================================================
// 函数: void Rectangle(u8 x0,u16 y0,u8 x,u16 y,u16 color)
// 描述: 画矩形
// 参数: x0,y0开始坐标,	x 长,	y 高, colcr 颜色
// 返回: 无
// 版本:
//========================================================================
void Rectangle(u16 x0,u16 y0,u16 x,u16 y,u16 color)
{
	Line_h(x0,y0,x,color);
	Line_h(x0,y0+y-1,x,color);
	Line_v(x0,y0,y,color);
	Line_v(x0+x-1,y0,y,color);
}

void	SetView_H(void)		//横屏
{
	LCD_RegWriteComd(0x36);
//	LCD_RegWriteData(0x28);		//横屏
	LCD_RegWriteData(0x2B);		//横屏 旋转180度

	LCD_RegWriteComd(0x2A);
	LCD_RegWriteData(0x00);
	LCD_RegWriteData(0x00);
	LCD_RegWriteData(((480-1)>>8));
	LCD_RegWriteData(((480-1)&0xff));

	LCD_RegWriteComd(0x2B);
	LCD_RegWriteData(0x00);
	LCD_RegWriteData(0x00);
	LCD_RegWriteData(((320-1)>>8));
	LCD_RegWriteData(((320-1)&0xff));
}
void	SetView_V(void)		//竖屏
{
	LCD_RegWriteComd(0x36);
//	LCD_RegWriteData(0x0A);		//竖屏
	LCD_RegWriteData(0x09);		//竖屏 旋转180度

	LCD_RegWriteComd(0x2A);
	LCD_RegWriteData(0x00);
	LCD_RegWriteData(0x00);
	LCD_RegWriteData(((320-1)>>8));
	LCD_RegWriteData(((320-1)&0xff));

	LCD_RegWriteComd(0x2B);
	LCD_RegWriteData(0x00);
	LCD_RegWriteData(0x00);
	LCD_RegWriteData(((480-1)>>8));
	LCD_RegWriteData(((480-1)&0xff));
}

//=============== 画单个点函数 =============================
void	WriteSingleDot(u16 x, u16 y, u16 color)
{
	LCD_SetWindows(x,y, x,y);
	LCD_CS_CLR();
	LCD_WriteWord(color);
	LCD_CS_SET();
}

//专门针对示波器写格子函数, 为了尽量快, 空间换时间, 加速处理.
//写入8个点
void  Write_8dots(void)
{
	LCD_WR_PULSE();	//发一个写脉冲, 则写入一个点(2字节).
	LCD_WR_PULSE();
	LCD_WR_PULSE();
	LCD_WR_PULSE();
	LCD_WR_PULSE();
	LCD_WR_PULSE();
	LCD_WR_PULSE();
	LCD_WR_PULSE();
}
//写入7个点
void  Write_7dots(void)
{
	LCD_WR_PULSE();	//发一个写脉冲, 则写入一个点(2字节).
	LCD_WR_PULSE();
	LCD_WR_PULSE();
	LCD_WR_PULSE();
	LCD_WR_PULSE();
	LCD_WR_PULSE();
	LCD_WR_PULSE();
}

//每隔25点画一个标记点
void	Line_Grid25(u16 x,u16 y,u16 color)
{  
	u8	i;
	
	LCD_SetWindows(x,y,x+251-1, y);
	LCD_CS_CLR();
	for(i=0; i<4; i++)
	{
		LCD_BUS_H = (u8)(BLACK>>8);
		LCD_BUS_L = (u8)BLACK;
		Write_8dots();	//写24个点黑色
		Write_8dots();
		Write_8dots();
		LCD_WriteWord(color);	//写一个点
	}
		LCD_BUS_H = (u8)(BLACK>>8);
		LCD_BUS_L = (u8)BLACK;
		Write_8dots();	//写23个点黑色
		Write_8dots();
		Write_7dots();
		LCD_BUS_H = (u8)(color>>8);
		LCD_BUS_L = (u8)color;
		LCD_WR_PULSE();	//写一个点
		LCD_WR_PULSE();	//写一个点
		LCD_WR_PULSE();	//写一个点

		LCD_BUS_H = (u8)(BLACK>>8);
		LCD_BUS_L = (u8)BLACK;
		Write_8dots();	//写23个点黑色
		Write_8dots();
		Write_7dots();
		LCD_WriteWord(color);	//写一个点

	for(i=0; i<3; i++)
	{
		LCD_BUS_H = (u8)(BLACK>>8);
		LCD_BUS_L = (u8)BLACK;
		Write_8dots();	//写24个点黑色
		Write_8dots();
		Write_8dots();
		LCD_WriteWord(color);	//写一个点
	}

		LCD_BUS_H = (u8)(BLACK>>8);
		LCD_BUS_L = (u8)BLACK;
		Write_8dots();	//写26个点黑色
		Write_8dots();
		Write_8dots();
		LCD_WR_PULSE();	//写一个点
		LCD_WR_PULSE();	//写一个点
	LCD_CS_SET();
}

//每隔5点画一个标记点
void	Line_Grid5(u16 x,u16 y,u16 color)
{  
	u8	i;
	
	LCD_SetWindows(x,y,x+251-1, y);
	LCD_CS_CLR();
	for(i=0; i<120; i +=5)
	{
		LCD_BUS_H = (u8)(BLACK>>8);
		LCD_BUS_L = (u8)BLACK;
		LCD_WR_PULSE();	//写4个点
		LCD_WR_PULSE();
		LCD_WR_PULSE();
		LCD_WR_PULSE();
		LCD_WriteWord(color);	//写一个点
	}
		LCD_BUS_H = (u8)(BLACK>>8);
		LCD_BUS_L = (u8)BLACK;
		LCD_WR_PULSE();	//写3个点
		LCD_WR_PULSE();
		LCD_WR_PULSE();
		LCD_BUS_H = (u8)(color>>8);
		LCD_BUS_L = (u8)color;
		LCD_WR_PULSE();	//写一个点
		LCD_WR_PULSE();	//写一个点
		LCD_WR_PULSE();	//写一个点

		LCD_BUS_H = (u8)(BLACK>>8);
		LCD_BUS_L = (u8)BLACK;
		LCD_WR_PULSE();	//写3个点
		LCD_WR_PULSE();
		LCD_WR_PULSE();
		LCD_WriteWord(color);	//写一个点

	for(i=130; i<245; i +=5)
	{
		LCD_BUS_H = (u8)(BLACK>>8);
		LCD_BUS_L = (u8)BLACK;
		LCD_WR_PULSE();	//写4个点
		LCD_WR_PULSE();
		LCD_WR_PULSE();
		LCD_WR_PULSE();
		LCD_WriteWord(color);	//写一个点
	}
		LCD_BUS_H = (u8)(BLACK>>8);
		LCD_BUS_L = (u8)BLACK;
		LCD_WR_PULSE();	//写6个点
		LCD_WR_PULSE();
		LCD_WR_PULSE();
		LCD_WR_PULSE();
		LCD_WR_PULSE();
		LCD_WR_PULSE();
	LCD_CS_SET();
}


u16 xdata DMA_tmp[256];

/**********************************************/
/*	x,y为起始坐标,index为ASCII字符	*/
void DMA_text_ascii_8x16(u16 x,u16 y,u8 index)
{
	u8 const *p;
 	u8 i,s,b;
	u16	j;

	if(x > 472)	return;	//溢出
	if(y > 312)	return;	//溢出
	if(index < 0x20)	return;	//溢出

	p = (u16)(index-0x20) * 16 + ASCII_8x16_H;
	for(j=0, i=0; i<16; i++)
	{    
		b = *p;	p++;
		for(s=0; s<8; s++)
		{
			if(b & 0x80)	DMA_tmp[j] = foreground;
			else			DMA_tmp[j] = background;
			b <<= 1;
			j++;
		}
	}
	LCD_SetWindows(x,y,x+8-1,y+16-1);
	LCD_RS = 1;	LCD_CS = 0;
	DMA_LCM_AMT  = (u8)(128-1);			//设置传输总字节数(低8位)：n+1
	DMA_LCM_AMTH = (u8)((128-1)>>8);	//设置传输总字节数(高8位)：n+1
	DMA_LCM_STA  = 0x00;
	DMA_LCM_CR   = 0xa0;	//启动DMA传输数据功能
	while((DMA_LCM_STA & 0x01) == 0)	{	NOP(1);	}	//等待DMA传输完成
	DMA_LCM_STA  = 0x00;
	DMA_LCM_CR   = 0x00;	//禁止DMA
	LCD_CS = 1;
}
	

//========================================================================
// 函数: void HZ_12x12s(u16 x,u16 y,u16 hz_code)
// 描述: 以x,y为起始坐标,hz为汉字首地址，显示11*11的汉字。
//		 在背景色background上用前景色foreground显示汉字。
// 参数: x  y轴坐标     hz 汉字首地址
// 返回: 无
// 备注: 使用前景色
//========================================================================
void DMA_HZ_16x16(u16 x,u16 y,u16 hz_code)
{
	u8	const *p;
	u8	i,s,b;
	u16	j;

	if(x > 464)	return;	//溢出
	if(y > 304)	return;	//溢出
	
	p = hz_code * 32 + HZK_16;
	for(j=0, i=0; i<32; i++)
	{    
		b = *p;	p++;
 		for(s=0; s<8; s++)
		{
			if(b & 0x80)	DMA_tmp[j] = foreground;
			else			DMA_tmp[j] = background;
			b <<= 1;
			j++;
		}
	}
 	LCD_SetWindows(x,y,x+16-1,y+16-1);
	LCD_RS = 1;	LCD_CS = 0;
	DMA_LCM_AMT  = (u8)(256-1);			//设置传输总字节数(低8位)：n+1
	DMA_LCM_AMTH = (u8)((256-1)>>8);	//设置传输总字节数(高8位)：n+1
	DMA_LCM_STA  = 0x00;
	DMA_LCM_CR   = 0xa0;	//启动DMA传输数据功能
	while((DMA_LCM_STA & 0x01) == 0)	{	NOP(1);	}	//等待DMA传输完成
	DMA_LCM_STA  = 0x00;
	DMA_LCM_CR   = 0x00;	//禁止DMA
	LCD_CS = 1;
}
/************ DMA字符串显示 *************************/
//传输显示数据时使用DMA.
void	DMA_printf_text16(u16 x,u16 y,u8 *ptr)
{
    u8 c1,c2,i;
	
	for (;;)
	{
        c1 = *ptr;
		ptr++;
		if(c1 == 0)		return;	//遇到停止符0结束
		if(c1 < 0xa0)			//ASCII码
		{
			DMA_text_ascii_8x16(x,y+2,c1);
			x += 8;
		}
		else					//汉字
		{
			c2 = *ptr;
			ptr++;
			if(c2 == 0)		return;	//遇到停止符0结束

			for(i=0; i < sizeof(HZK16)/2; i++)    // 查找定位
			{				
				if((c1 == HZK16[i*2]) && (c2 == HZK16[i*2+1]))
				{
					DMA_HZ_16x16(x,y,(u16)i);
					x += 16;
				}
			}
		}
	}
}


/*****************************************************************************
 * @name       :void LCM_Config(void)
 * @date       :2018-11-13 
 * @function   :Config LCM
 * @parameters :None
 * @retvalue   :None
******************************************************************************/	
void LCM_Config(void)
{
	P_SW2 |= 0x80;
	LCMIFCFG  = 0x06;	//P6高字节, P2低字节, 16为数据, 8080接口.
	LCMIFCFG2 = 0x09;	//RS:P45,RD:P44,WR:P42; Setup Time=2,HOLD Time=1
	LCMIFSTA  = 0x00;
	LCMIFCR   = 0x80;		//Enable interface, write command out
}

/*****************************************************************************
 * @name       :void DMA_Config(void)
 * @date       :2020-12-09 
 * @function   :Config DMA
 * @parameters :None
 * @retvalue   :None
******************************************************************************/	
void DMA_Config(void)
{
	P_SW2 |= 0x80;
	DMA_LCM_AMT  = (u8)(512-1);			//设置传输总字节数(低8位)：n+1
	DMA_LCM_AMTH = (u8)((512-1)>>8);	//设置传输总字节数(高8位)：n+1
	DMA_LCM_TXAH = (u8)((u16)&DMA_tmp >> 8);	//发送地址寄存器高字节
	DMA_LCM_TXAL = (u8)((u16)&DMA_tmp);			//发送地址寄存器低字节
	DMA_LCM_STA  = 0x00;
	DMA_LCM_CFG  = 0x00;		//不用中断
	DMA_LCM_CR   = 0x00;
}


