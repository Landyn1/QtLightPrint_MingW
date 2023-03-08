#include "MygraphicsLinePre.h"
#include <QPen>
#include <QPainter>
#include <QPainterPath>
#include <QPainterPathStroker>
#include <QStyle>
#include <QStyleOptionGraphicsItem>
#include<QApplication>
#include<QDesktopWidget>
#include<QtMath>
#include<QScreen>
#include<qdebug.h>
MygraphicsLinePre::MygraphicsLinePre(QGraphicsItem *parent)
	: QGraphicsItem(parent)
{
		
    
    setFlags(flags() & ~ItemIsSelectable);
}

void MygraphicsLinePre::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    // QPen pen = ScaleManager::get_instance().getMainViewItemPen();
    QPen pen;   // 定义一个画笔，设置画笔颜色和宽度
    //pen.setColor(QColor(0, 160, 230));
    pen.setWidth(1);
    pen.setColor(Qt::lightGray);
    
    auto rec = widget->rect();
    
    int width = 5000;
    int height = 5000;
    double dpiX = QApplication::primaryScreen()->physicalDotsPerInchX();

    double dpiY = QApplication::primaryScreen()->physicalDotsPerInchY();
    
    auto  t = (dpiX * 10) / 254;
    int temp = 0;
    QPointF tempp = mapFromScene(0, shuzhi_offset);
    double y = tempp.y();

    for (double i = 0; i < width; i += t)
    {
        if (temp % 10 == 0)
        {
            if (temp == 0)
            {
                painter->setPen(QPen(option->palette.windowText(), 0, Qt::DashLine));
            }
            else
            {
                painter->setPen(pen);
            }
            painter->drawLine(QPointF(i, -height), QPointF(i, height));
            
        }
        ++temp;
    }
    temp = 0;
    for (double i = 0; i > -width; i -= t)
    {
        if (temp % 10 == 0)
        {
            if (temp == 0)
            {
                painter->setPen(QPen(option->palette.windowText(), 0, Qt::DashLine));
            }
            else
            {
                painter->setPen(pen);
            }
            painter->drawLine(QPointF(i, -height), QPointF(i, height));
        }
        ++temp;
    }
    temp = 0;
    t = (dpiY * 10) / 254;
    for (double i = 0; i < height; i += t)
    {
        if (temp % 10 == 0)
        {
            if (temp == 0)
            {
                painter->setPen(QPen(option->palette.windowText(), 0, Qt::DashLine));
            }
            else
            {
                painter->setPen(pen);
            }
            painter->drawLine(QPointF(-width, i), QPointF(width, i));
        }
        ++temp;
    }
    temp = 0;
    for (double i = 0; i > -height; i -= t)
    {
        if (temp % 10 == 0)
        {
            if (temp == 0)
            {
                painter->setPen(QPen(option->palette.windowText(), 0, Qt::DashLine));
            }
            else
            {
                painter->setPen(pen);
            }
            painter->drawLine(QPointF(-width, i), QPointF(width, i));
        }
        ++temp;
    }
    //painter->eraseRect(-5000, y-(20.0/scale), 10000, 20.0);
    
}

MygraphicsLinePre::~MygraphicsLinePre()
{}
