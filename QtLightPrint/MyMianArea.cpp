#include "MyMianArea.h"
#include <QPen>
#include <QPainter>
#include <QPainterPath>
#include <QPainterPathStroker>
#include <QStyle>
#include <QStyleOptionGraphicsItem>
#include"mainWindow.h"


MyMianArea::MyMianArea(QGraphicsRectItem *parent)
	: QGraphicsRectItem(parent)
{

}

MyMianArea::~MyMianArea()
{}
void MyMianArea::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    // QPen pen = ScaleManager::get_instance().getMainViewItemPen();
    QPen pen;   // 定义一个画笔，设置画笔颜色和宽度
    //pen.setColor(QColor(0, 160, 230));
    pen.setWidthF(2);
    painter->setPen(pen);
    double dpiX = QApplication::primaryScreen()->physicalDotsPerInchX();

    double dpiY = QApplication::primaryScreen()->physicalDotsPerInchY();
    auto  t = (dpiX * 10) / 254;
    auto  tt = (dpiY * 10) / 254;
    auto width = t * 100;
    auto height = tt * 100;
    painter->drawRect(-width/2,-height/2,width,height);
    pen.setWidthF(8/scale);
    painter->setPen(pen);
    painter->drawLine(QPointF(-width / 2 + 5/scale, -height / 2-5/scale), QPointF(width / 2, -height / 2-5/scale));
    painter->drawLine(QPointF(width / 2 + 5/scale, height / 2-5/scale), QPointF(width / 2+5/scale, -height / 2-5/scale));

    QPointF tempp = mapFromScene(0, offset);
    double y = tempp.y();
    painter->eraseRect(-5000, y - (20.0 / scale), 10000, 20.0 / scale);
}