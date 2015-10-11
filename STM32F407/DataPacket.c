#include "DataPacket.h"

#define n 8
//本函数实现的打包处理仅仅只是简单处理并没有对数据进行压缩
//NeedPack为需要打包处理的数据
//Packed为打包好的数据
void DataPack(uint8_t* NeedPack, uint8_t* Packed)
{
	/*
		数据结构定义：
		Packed[0]--70;
		Packed[1]--Second;
		Packed[2]--Miniture;
		Packed[3]--Hours;
	*/
	Packed[0]=70;
	//
	Packed[1]=NeedPack[0];
	Packed[2]=NeedPack[1];
	Packed[3]=NeedPack[2];
};

//先对这个数据包进行数据变换以后才进行数据的解包
void DataUnpack(uint8_t* Packed, uint8_t* PData)
{
	uint8_t temp[6];
	//数据变换
	DataConversion(Packed,temp);
	//
	if(temp[0]==70)
	{
		PData[0]=temp[1];
		PData[1]=temp[2];
		PData[2]=temp[3];
	}
};

//由于接受到的数据包的第一位不一定是70，所以先要确定第一位的位置
//数据包的容量为6
void DataConversion(uint8_t* Packed, uint8_t* temp)
{
	uint8_t i=0;	//计算初始位
	uint8_t j=0;
	//uint8_t temp[6];
	uint8_t Start=70;	//自己定义的数据包初始
	
	//i从0开始
	for(i=0;i<4;)
	{
		if(Start==Packed[i])
			break;
		i++;	//i得到的数值为起始位的位置
	}
	//将数据存入暂存的里面
	for(j=0;j<4;j++)
	{
		if((i+j)<4)
			temp[j]=Packed[i+j];
		else
			temp[j]=Packed[i+j-4];
	}
	//Packed=&temp[0];
};

//本函数用来确定数组中出现次数最多的数
uint8_t JudgeData(uint8_t* NeedJudge)
{
	uint8_t i,j;
	uint8_t max;
	uint8_t times[n]={0};
	//由于数组中一个有5个元素
	for(i=0;i<n-1;i++)
	{
		for(j=i+1;j<n;j++)
		{
			if(NeedJudge[i]==NeedJudge[j])
				times[i]++;
		}
	}
	//
	max=times[0];
	for(i=1;i<n;i++)
	{
		if(times[i]>max)
			max=times[i];
	}
	//
	for(i=0;i<n;i++)
	{
		if(times[i]==max)
			return NeedJudge[i];
	}		
};
	
	
