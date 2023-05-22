#pragma once
#include <QGraphicsRectItem>

class PrintParams
{
public:
	int processnums = 1;
    int speed = 1000; //mm/s
	int power = 75; //∞Ÿ∑÷÷∆ [0,100]
	qreal frequence = 30; //KHZ
	qreal maikuan = 10;
	int openDelay = 0; //us
	int closeDelay = 100;
	int endDelay = 50;
	int turnDelay = 80;
	PrintParams();

	
};

