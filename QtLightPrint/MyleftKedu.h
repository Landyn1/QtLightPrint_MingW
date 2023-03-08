#pragma once

#include <QGraphicsItem>
#include<qgraphicsitem.h>
#include<QApplication>

#include<QDesktopWidget>
#include<QtMath>
#include<QScreen>
#include<qdebug.h>
class MyleftKedu  : public QGraphicsRectItem
{


public:
	MyleftKedu(QGraphicsRectItem* parent = NULL);
	~MyleftKedu();
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    QRectF MyleftKedu::boundingRect() const
    {
        QRectF temp_rect(0, -5000*scale,  20 * scale, 10000 * scale);
        return temp_rect;
    }
    void setscales(double scale_m)
    {
        scale = scale_m;
        this->setScale(1 / scale);
       
        update();
    }
    void setOffset(double value)
    {
        offset = value;
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
};
