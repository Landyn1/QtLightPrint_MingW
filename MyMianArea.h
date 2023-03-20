#pragma once

#include <QObject>
#include<qgraphicsitem.h>
#include<QApplication>

#include<QDesktopWidget>
#include<QtMath>
#include<QScreen>

class MyMianArea  : public QGraphicsRectItem
{
public:
	MyMianArea(QGraphicsRectItem *parent);
	~MyMianArea();
	enum { Type = 4 };

	int type() const
	{
		// 针对该 item 启用 qgraphicsitem_cast
		return Type;
	}
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    QRectF boundingRect() const
	{
		double dpiX = QApplication::primaryScreen()->physicalDotsPerInchX();

		double dpiY = QApplication::primaryScreen()->physicalDotsPerInchY();
		auto  t = (dpiX * 10) / 254;
		auto  tt = (dpiY * 10) / 254;
		auto width = t * 100;
		auto height = tt * 100;
		QRectF temp_rect(-width / 2, -height / 2, width, height);
		return temp_rect;
	}
	void setOffset(double value)
	{
		offset = value;
		update();
	}
	void setscales(double scale_m)
	{
		scale = scale_m;
		//this->setScale(1 / scale);
		update();
	}
private:
	double offset{ 0 };
	double scale = 1;
};
