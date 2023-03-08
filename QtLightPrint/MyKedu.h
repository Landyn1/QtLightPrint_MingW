#pragma once

#include <QObject>
#include<qgraphicsitem.h>
#include<QApplication>

#include<QDesktopWidget>
#include<QtMath>
#include<QScreen>
class MyKedu  : public QGraphicsRectItem
{

public:
	MyKedu(QGraphicsRectItem *parent = NULL);
	~MyKedu();
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
	QRectF MyKedu::boundingRect() const
	{
		QRectF temp_rect(-5000*scale, 0, 10000*scale, 20*scale);
		return temp_rect;
	}
    void setscales(double scale_m)
    {
        scale = scale_m;
        this->setScale(1/scale);
        update();
    }
    void setOffset(double value)
    {
        offset = value;
        update();
    }

    void setViewWidth(double value)
    {
        viewWidth = value;
        update();
    }
private:
    QColor backgroundColor{ Qt::white };//背景色
    QColor textAndLineColor{ Qt::black };//文本和刻度颜色
    QColor slidingLineColor{ "#D56161" };//游标颜色
    Qt::Orientations orientation;
    int slidingLinePos{ 0 };
    double offset{ 0 };
    QFont font{ "微软雅黑",8 };
    float horizontalDPI;
    float verticalDPI;
    double scale = 1;
    double viewWidth = 0;
};
