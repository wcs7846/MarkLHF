/* Includes ------------------------------------------------------------------*/
#include "OLED_I2C.h"
/*----------------------------------------------------------------------------*/
void WriteCmd(uint8_t command);
void WriteDat(uint8_t data);

void WriteCmd(uint8_t command)
{
	I2C_WriteByte(OLED_ADDRESS, 0x00, command);
};

void WriteDat(uint8_t data)
{
	I2C_WriteByte(OLED_ADDRESS, 0x40, data);
};

void OLED_Init(void)
{
	HAL_Delay(100); //这里的延时很重要
	
	WriteCmd(0xAE); //display off
	WriteCmd(0x20);	//Set Memory Addressing Mode	
	WriteCmd(0x10);	//00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	WriteCmd(0xb0);	//Set Page Start Address for Page Addressing Mode,0-7
	WriteCmd(0xc8);	//Set COM Output Scan Direction
	WriteCmd(0x00); //---set low column address
	WriteCmd(0x10); //---set high column address
	WriteCmd(0x40); //--set start line address
	WriteCmd(0x81); //--set contrast control register
	WriteCmd(0xff); //亮度调节 0x00~0xff
	WriteCmd(0xa1); //--set segment re-map 0 to 127
	WriteCmd(0xa6); //--set normal display
	WriteCmd(0xa8); //--set multiplex ratio(1 to 64)
	WriteCmd(0x3F); //
	WriteCmd(0xa4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	WriteCmd(0xd3); //-set display offset
	WriteCmd(0x00); //-not offset
	WriteCmd(0xd5); //--set display clock divide ratio/oscillator frequency
	WriteCmd(0xf0); //--set divide ratio
	WriteCmd(0xd9); //--set pre-charge period
	WriteCmd(0x22); //
	WriteCmd(0xda); //--set com pins hardware configuration
	WriteCmd(0x12);
	WriteCmd(0xdb); //--set vcomh
	WriteCmd(0x20); //0x20,0.77xVcc
	WriteCmd(0x8d); //--set DC-DC enable
	WriteCmd(0x14); //
	WriteCmd(0xaf); //--turn on oled panel
}

void OLED_SetPos(unsigned char x, unsigned char y) //设置起始点坐标
{ 
	WriteCmd(0xb0+y);
	WriteCmd(((x&0xf0)>>4)|0x10);
	WriteCmd((x&0x0f)|0x01);
}

void OLED_Fill(unsigned char fill_Data)//全屏填充
{
	unsigned char m,n;
	for(m=0;m<8;m++)
	{
		WriteCmd(0xb0+m);		//page0-page1
		WriteCmd(0x00);		//low column start address
		WriteCmd(0x10);		//high column start address
		for(n=0;n<128;n++)
			{
				WriteDat(fill_Data);
			}
	}
}

void OLED_CLS(void)//清屏
{
	OLED_Fill(0x00);
}

//--------------------------------------------------------------
// Prototype      : void OLED_ON(void)
// Calls          : 
// Parameters     : none
// Description    : 将OLED从休眠中唤醒
//--------------------------------------------------------------
void OLED_ON(void)
{
	WriteCmd(0X8D);  //设置电荷泵
	WriteCmd(0X14);  //开启电荷泵
	WriteCmd(0XAF);  //OLED唤醒
}

//--------------------------------------------------------------
// Prototype      : void OLED_OFF(void)
// Calls          : 
// Parameters     : none
// Description    : 让OLED休眠 -- 休眠模式下,OLED功耗不到10uA
//--------------------------------------------------------------
void OLED_OFF(void)
{
	WriteCmd(0X8D);  //设置电荷泵
	WriteCmd(0X10);  //关闭电荷泵
	WriteCmd(0XAE);  //OLED休眠
}

//--------------------------------------------------------------
// Prototype      : void OLED_ShowChar(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize)
// Calls          : 
// Parameters     : x,y -- 起始点坐标(x:0~127, y:0~7); ch[] -- 要显示的字符串; TextSize -- 字符大小(1:6*8 ; 2:8*16)
// Description    : 显示codetab.h中的ASCII字符,有6*8和8*16可选择
//--------------------------------------------------------------
//使用注意：如果要直接用字符串显示则要把字符串加上一个32
void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize)
{
	unsigned char c = 0,i = 0,j = 0;
	switch(TextSize)
	{
		case 1:
		{
			while(ch[j] != '\0')
			{
				c = ch[j] - 32;
				if(x > 126)
				{
					x = 0;
					y++;
				}
				OLED_SetPos(x,y);
				for(i=0;i<6;i++)
					WriteDat(F6x8[c][i]);
				x += 6;
				j++;
			}
		}break;
		case 2:
		{
			while(ch[j] != '\0')
			{
				c = ch[j] - 32;
				if(x > 120)
				{
					x = 0;
					y++;
				}
				OLED_SetPos(x,y);
				for(i=0;i<8;i++)
					WriteDat(F8X16[c*16+i]);
				OLED_SetPos(x,y+1);
				for(i=0;i<8;i++)
					WriteDat(F8X16[c*16+i+8]);
				x += 8;
				j++;
			}
		}break;
	}
}

//--------------------------------------------------------------
// Prototype      : void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N)
// Calls          : 
// Parameters     : x,y -- 起始点坐标(x:0~127, y:0~7); N:汉字在codetab.h中的索引
// Description    : 显示codetab.h中的汉字,16*16点阵
//--------------------------------------------------------------
void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N)
{
	unsigned char wm=0;
	unsigned int  adder=32*N;
	OLED_SetPos(x , y);
	for(wm = 0;wm < 16;wm++)
	{
		WriteDat(F16x16[adder]);
		adder += 1;
	}
	OLED_SetPos(x,y + 1);
	for(wm = 0;wm < 16;wm++)
	{
		WriteDat(F16x16[adder]);
		adder += 1;
	}
}

//--------------------------------------------------------------
// Prototype      : void OLED_ShowNum(unsigned char x, unsigned char y, unsigned char N)
// Calls          : 
// Parameters     : x,y -- 起始点坐标(x:0~127, y:0~7); N:数字在codetab.h中的索引
// Description    : 显示codetab.h中的汉字,16*16点阵
//--------------------------------------------------------------
void OLED_ShowNum(unsigned char x, unsigned char y, unsigned char N)
{
	unsigned char wm=0;
	unsigned int  adder=(N+16);
	OLED_SetPos(x , y);
	for(wm = 0;wm < 6;wm++)
	{
		WriteDat(F6x8[adder][wm]);
	}
}


//--------------------------------------------------------------
// Prototype      : void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);
// Calls          : 
// Parameters     : x0,y0 -- 起始点坐标(x0:0~127, y0:0~7); x1,y1 -- 起点对角线(结束点)的坐标(x1:1~128,y1:1~8)
// Description    : 显示BMP位图
//--------------------------------------------------------------
void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,const unsigned char *BMP)
{
	unsigned int j=0;
	unsigned char x,y;

  if(y1%8==0)
		y = y1/8;
  else
		y = y1/8 + 1;
	for(y=y0;y<y1;y++)
	{
		OLED_SetPos(x0,y);
    for(x=x0;x<x1;x++)
		{
			WriteDat(BMP[j++]);
		}
	}
}

const uint8_t PICTURE[]={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x7F,0x3F,0x1F,0xF,0x7,0x7,0x7,0x3,0x1,0x1,0x0,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x1,0x3,0x3,0x7,0xF,0xF,0x1F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x7F,0x1F,0x3F,0xF,0x7,0x7,0x3,0x3,0x3,0x1,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x1,0x3,0x3,0x3,0x7,0xF,0x3F,0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xDF,0x3F,0xB,0x7,0x1,0x0,0x0,0x0,0x0,0x80,0xC0,0xE0,0xF0,0xF0,0xF8,0xF8,0xFC,0xFC,0xFE,0xFE,0xFF,0xFE,0xFC,0xFC,0xFC,0xF8,0xF0,0xE0,0xC0,0x80,0x0,0x0,0x0,0x0,0x0,0x0,0x3,0x7,0x1F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF,0xF,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x1,0x1,0x3,0xF,0x7F,0xFF
,0xFF,0xFF,0xF7,0x37,0xB7,0xB7,0xB7,0x87,0x87,0xB7,0xB7,0xB7,0x37,0xF7,0xFF,0xFF,0xBF,0xCF,0x63,0x6F,0x6F,0x6F,0xF,0x6F,0x6F,0x6F,0x6F,0x6F,0xFF,0xFF,0xFF,0xFF,0xFF,0x3F,0x0,0x0,0x0,0x0,0x0,0x0,0xE0,0xF8,0xFE,0xFF,0xFF,0xFF,0x7F,0x7F,0x7F,0x7F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFC,0xF8,0xC0,0x80,0x0,0x0,0x0,0x0,0x29,0x83,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0x17,0x0,0x0,0x0,0x0,0x0,0x80,0xC0,0xF0,0x60,0x40,0x0,0x0,0x0,0x0,0x0,0x80,0xC0,0xC0,0xC0,0xC0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xF0,0xF0,0xF0,0xF0,0xE0,0xE0,0xC0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xC0,0xFD
,0xFF,0xFF,0xFF,0x80,0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,0x80,0xFF,0xFF,0xFF,0xF7,0xF7,0xF0,0xF7,0xF7,0xF7,0x80,0xF7,0xF7,0xF7,0xF7,0xFF,0xFF,0xFF,0xFF,0x9F,0x3,0x0,0x80,0x0,0x0,0xE0,0xF0,0xC7,0x7,0xC7,0xFB,0xFB,0xE3,0xF3,0xC3,0xC7,0xC7,0x87,0x87,0xC7,0xEF,0x1F,0x1F,0x9F,0x1F,0x1F,0xCF,0x8F,0xE,0xC,0xC,0x8C,0x8C,0x8F,0x8F,0xCD,0x5B,0x9F,0x3E,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xA0,0x0,0x0,0xFC,0x7,0xC3,0xF3,0xD6,0x9A,0xCA,0xCE,0x86,0x86,0x94,0x84,0xAC,0x4F,0x1F,0x1F,0x1F,0x1F,0xDF,0xDB,0xD9,0x19,0x9,0x39,0x18,0x18,0x58,0x59,0x9B,0x3F,0x3F,0x3F,0xC0,0x80,0x0,0x0,0x0,0x40,0x3A,0x3F,0x3F
,0xFF,0xFF,0xDF,0x3,0xDF,0xDF,0x1F,0xDF,0xF7,0xF7,0xF7,0x37,0xD7,0xE7,0xFF,0xFF,0x7F,0xBF,0x5F,0x5F,0x6F,0x73,0x77,0x6F,0x5F,0x5F,0xBF,0x7F,0xFF,0xFF,0xFF,0xFF,0xFE,0x8,0x31,0x3C,0x3C,0xFF,0xFF,0xFF,0xFF,0xFE,0xFE,0xFD,0xFD,0xFD,0xFD,0xF9,0xFB,0xF9,0xF9,0x7D,0x7C,0xFE,0xFF,0x7F,0x7E,0xFC,0xFB,0xF3,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xFB,0xFC,0xFE,0xE0,0x80,0x10,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3B,0xFF,0xE0,0xD8,0xFF,0xFF,0xFE,0xFD,0xFB,0xFB,0xFB,0xF3,0xF3,0xF7,0xF7,0x73,0x39,0x7C,0x7E,0x7F,0x7E,0x78,0xF1,0xE7,0xEF,0xEF,0xEF,0xEE,0xEF,0xEF,0xEE,0xEF,0xEF,0xF3,0xF8,0xFE,0x3,0x80,0x30,0xF8,0x30,0x0,0x0,0x0,0x0
,0xFF,0xFF,0xBF,0xD0,0xEF,0xC7,0x90,0xFF,0xFE,0xBE,0xBE,0x80,0xFE,0xFE,0xFF,0xFF,0xFF,0x81,0xBD,0xBD,0xBD,0xBD,0xBD,0xBD,0xBD,0xBD,0x81,0xFF,0xFF,0xFF,0x7F,0x1F,0x1,0x0,0x0,0x0,0x0,0x7,0x3F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDE,0xDF,0x9E,0x9E,0xBF,0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x1F,0x3,0x1,0x1,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x9F,0x9F,0x9F,0x9E,0x9F,0x9F,0x9E,0x1E,0x1E,0x14,0x3C,0x1F,0x7E,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0xF,0x0,0xF,0xF,0xE,0x3,0x0,0x0,0x0,0x0,0x0
,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x7F,0x7F,0x3F,0x3F,0x1F,0x1F,0xF,0xF,0x7,0x3,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x7F,0x7E,0x7E,0x7E,0x7E,0x7E,0x7F,0x7F,0xBF,0xBF,0xDF,0xDF,0xEF,0xF,0x7,0x3,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x80,0x60,0x0,0x80,0xF3,0x87,0xF,0x1F,0x3F,0x3F,0x7F,0xFF,0xFF,0xFD,0xF9,0x79,0xF9,0xF9,0xF9,0xF9,0xF9,0xFE,0xEE,0xFF,0x7F,0x3F,0x7F,0x3F,0xBF,0x1F,0x7,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
,0x7F,0x3F,0x3F,0x3F,0x1F,0xF,0x7,0x7,0x3,0x3,0x1,0x1,0x1,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x80,0x80,0xC0,0x60,0x30,0x58,0xF2,0xE6,0x0,0x0,0x0,0x0,0x0,0x30,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFC,0xF8,0xF8,0xF8,0xFC,0xFC,0xFF,0xFF,0xFF,0x3F,0x3F,0xF,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xC0,0x81,0x0,0x0,0x1,0x13,0x7F,0xF8,0xE0,0xC0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x84,0x1C,0x18,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
};

//--------------------------------------------------------------
// Prototype      : void OLED_ShowString(unsigned char ch[]);
// Calls          : 
// Parameters     : ch[] -- 要显示的数组; 
// Description    : 1.为了使得OLED显示无误而特别添加的预处理
//									2.同时输出这个数组一共有多少数据
//--------------------------------------------------------------

uint8_t OLED_ShowString(unsigned char ch[])
{
	uint8_t len=0;
	uint8_t i=0;
	while(1)
	{
		if(ch[i]!='\0') i = i+1;
		else
		{
			len = i;
			break;
		}
	}
	for(i=0;i<len;i++)
	{
		if((ch[i]>0&&ch[i]<9)||(ch[i]==9))
			ch[i] = ch[i]+32+16;
		if(((ch[i]>'a')||(ch[i]=='a'))&&((ch[i]<'z')||(ch[i]=='z')))
			ch[i] = ch[i];
	}
	return len;
};

