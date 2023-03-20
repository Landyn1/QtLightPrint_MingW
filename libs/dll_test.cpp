#include <iostream>
#include "CUDrvE.h"

//#include <Windows.h>

using namespace std;
#include <fstream>
int mode = 3;//3 缓存   2立即

void JumpP(int speed, int x, int y)
{
	CUSchSetSpeed(1310700, mode);
	CUSchJmpLinear(x, y, mode);//内嵌了跳转延时

}

void Myline(int x, int y)
{
	CUSchSetSpeed(1765851, mode);
	CUSchOutLinear(x, y, mode);

}

void Mylinedelta(int opendelay, int closedelay, int deltax, int deltay)
{
	CUSchSetSpeed(1310700, mode);
	CUSchJmpLinear(29631 + deltax, 4146, mode);//new
	//	CULaserOut(6, 1, 3);//AP
	CUSetOpenDelayUs(opendelay, mode);//new
	CUSchSetSpeed(1765851, mode);
	CUSchOutLinear(29631 + deltax, 29006 + deltay, mode);
	//	CULaserOut(6, 0, 3);//AP
}
//画正方形
void test1(int ld,int ru)
{
	JumpP(1310700, ru, ld);
	Myline( ru, ru);
	Myline( ld, ru);
	Myline(ld, ld);
	Myline( ru, ld);
	JumpP(1310700, 32767, 32767);
}
//45度填充一半，画外圈
void test2()
{
	int delta = 200;
	CUSetRedLight(0, mode);//设置红光状态，应该在此处同时关红光
	CUSetOpenDelayUs(90, mode);//new
	CUSetCloseDelayUs(150, mode);//new
	CUSetTuneDelayUs(250, mode);//new
	CUSetJumpDelayUs(200, mode);//new

	for (int i = 0; i < 30; i++)//0,24
	{
		JumpP(1310700, 32000+i*delta, 32000);
		Myline(38000, 38000-i*delta);
	}
	test1(32000,38000);
}
//水平填充
void test3()
{
	int delta = 200;
	CUSetOpenDelayUs(90, mode);//new
	CUSetCloseDelayUs(150, mode);//new
	CUSetTuneDelayUs(250, mode);//new
	CUSetJumpDelayUs(200, mode);//new

	for (int i = 0; i < 25; i++)//0,24
	{
		JumpP(1310700, 34000, 34000 + i*delta);
		Myline(39000, 34000 + i*delta);
	}
	test1(34000,39000);
}


void test4()//长斜线
{
	int delta = 200;
	CUSetOpenDelayUs(90, mode);//new
	CUSetCloseDelayUs(150, mode);//new
	CUSetTuneDelayUs(250, mode);//new
	CUSetJumpDelayUs(200, mode);//new

		JumpP(1310700, 1000, 1000);
		Myline(64000, 64000);
}

void test5()//红光测试
{
//	CUIOOut(2, 1, 2);//开红光
	CUSetRedLight(1, mode);//设置红光状态，应该在此处同时开红光
	for (int i = 0; i < 100;i++)
	test1(32000,38000);
	CUSetRedLight(0, mode);//设置红光状态，应该在此处同时关红光

//	CUIOOut(2, 0, mode);//关红光
}
void test6()//焊接出光测试
{
	//	CUIOOut(2, 1, 2);//开红光
	char in1;
	bool end=false;
	mode = 2;
	while (1)
	{
		//	CUIOOut(2, 0, mode);//关红光
		cin >> in1;
		switch (in1)
		{
		case '3':
			CUSetPWM(PWM2, 4000, 30, mode);//
			break;
		case '8':
			CUSetPWM(PWM2, 4000, 80, mode);//
			break;
		case 'M':
				CULaserOut(5, 1, mode);//MO
				break;
		case 'm':
			CULaserOut(5, 0, mode);//MO
			break;
		case 'A':
			CULaserOut(6, 1, mode);//MO
			break;
		case 'a':
			CULaserOut(6, 0, mode);//MO
			break;
		case 'E':
			end=true;//MO
			break;
		}
		if (end) break;
	}
}

void test7()//图像打标测试
{
	//	读数据，字节方式
	short row;
	short column;
/*	ifstream inf("e:\\output", ios::binary | ios_base::in);
	inf.read((char*)&row,sizeof(char)*2);
	inf.read((char*)&column, sizeof(char) * 2);

	char *gray=new char[row*column];
	inf.read(gray, sizeof(char)*row*column);*/
	row = 5;
	column = 600;
	char *gray = new char[row*column];
	for (int i = 0; i < row; i++)
		for (int j = 0; j < column; j++)
		{
			gray[i*column + j] = j / 30 + 1;
		}
//	CUSchSetSpeed(165851, mode);
	CUSetImgPara(column, row, 55,55, mode);
	CUWriteBuf();//要把缓存写入到卡上去。
	CUOutImg((byte *)gray,5000,20000);
	//inf.close();
}

void test8()//出光测试
{
	//	CUIOOut(2, 1, 2);//开红光
	int in1;
	bool end = false;
	cin >> in1;
	CULaserOut(6, 1, mode);//AP
	CUSetNullDelayUs(in1*1000000, mode);
	CULaserOut(6, 0, mode);//AP

}

int test_main( )
{
	cout << CUIsOpen() << endl;
	CUOpenDevice();
	cout << CUIsOpen() << endl;

	CUSetPWM(PWM2, 5000, 50, mode);//

	CUSetNullDelayUs(20000, mode);
	//SetLaserPower
	CULaserOut(ST_DATA, 127, mode);
	CUSetNullDelayUs(100, mode);

	CULaserOut(ST_LATCH, 1, mode);
	CUSetNullDelayUs(5000, mode);
	CULaserOut(ST_LATCH, 0, mode);
	//
	CULaserOut(5, 1, mode);//MO
	CUSetNullDelayUs(5000, mode);
	CUSetOpenDelayUs(100, mode);
	CUSetCloseDelayUs(100, mode);
	CUSetTuneDelayUs(100, mode);

	//	test1(34000, 39000);
	test7();

	CULaserOut(5, 0, mode);//MO

	CUWriteBuf();

	CUSetNullDelayUs(50, mode);
	CULaserOut(6, 0, mode);//AP
	CULaserOut(5, 0, mode);//MO
	CUBufFill(); //实际打印

	return 0;
}

