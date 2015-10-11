#include "fifo.h"
#define n 50
#define m 500
//端口时钟
/*
	wrclk---PE8
	wrreq---PE9
	wrfull--PE10
	data----PE11
*/
//上升沿写入也是上升沿读出
//用来写入FIFO
//写FIFO已经完成调整 
void FIFOWriteData(uint8_t Data)
{
	uint8_t i;
	//如果没有写满则可以写入
	//Test:测试写入的数据为0xaa--10101010(8bit)
	//从高位开始输入
	wrreq=0;
	wrclk=1;
	if(wrfull==0)
	{
		wrreq=1;
		//
		wrclk=0;
		Delay_us(n);
		wrclk=1;
		Delay_us(n);
		wrclk=0;
		Delay_us(n);
		wrclk=1;
		Delay_us(n);
		//
		for(i=0;i<8;i++)
		{
			wrclk=0;
			data=(Data&0x80)>>7;
			Delay_us(n);
			wrclk=1;
			Delay_us(n);
			Data<<=1;
		}	
		wrclk=1;
		wrreq=0;
	}
};
/*
	rdclk----PE12
	rdreq----PE13
	rdempty--PE14
	q--------PE15
*/
//用来读出数据
uint8_t FIFOReadData(void)
{
	uint8_t i;
	uint8_t DataOut=0;
	//如果没有读空则可以读出
	//Test:测试写入的数据为0xaa--10101010(8bit)
	//从高位开始读出
	rdreq=0;
	rdclk=0;
	if(rdempty==0)
	{
		rdreq=1;
		for(i=0;i<8;i++)
		{
			rdclk=0;
			Delay_us(m);
			rdclk=1;
			Delay_us(m);
			DataOut=DataOut+q;
			rdclk=0;
			if(i<7)
				DataOut<<=1;
		}
	}
	//DataOut>>=1;
	rdreq=0;
	return DataOut;
};

