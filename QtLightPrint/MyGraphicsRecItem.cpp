#include "MyGraphicsRecItem.h"
#include"mainWindow.h"
#include <QPen>
#include <QPainter>
#include <QPainterPath>
#include <QPainterPathStroker>
#include <QStyle>
#include <QStyleOptionGraphicsItem>
#include<qdebug.h>
MyGraphicsRecItem::MyGraphicsRecItem(QGraphicsItem *parent)
	: QGraphicsRectItem(parent)
{
	initVaiables();
}

MyGraphicsRecItem::~MyGraphicsRecItem()
{}

//QRectF MyGraphicsRecItem::boundingRect() const
//{
//    QRectF temp_rect = rect().adjusted(-10, -10, 10, 10);
//    return temp_rect;
//	
//}
//
//QPainterPath MyGraphicsRecItem::shape() const
//{
//    QPainterPath temp;
//    float temp_safe_dis = 10 / 1;
//
//    QRectF temp_rect = rect();
//    temp.addRect(temp_rect);
//
//    QPainterPathStroker ps;
//
//    ps.setWidth(temp_safe_dis * 2);
//    QPainterPath p = ps.createStroke(temp);
//
//    return p;
//}

void MyGraphicsRecItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
   // QPen pen = ScaleManager::get_instance().getMainViewItemPen();
    QPen pen;   // 定义一个画笔，设置画笔颜色和宽度
    //pen.setColor(QColor(0, 160, 230));
    pen.setWidthF(1);
    painter->setPen(pen);

    if ((option->state & QStyle::State_Selected) ) {
        float penWidth = pen.widthF();

        painter->setPen(QPen(option->palette.windowText(), 0, Qt::DashLine));

        painter->setBrush(Qt::NoBrush);
        painter->drawRect(this->rect());
       // emit item_selected();
    }
    else {
        painter->drawRect(this->rect());
    }

}

void MyGraphicsRecItem::initVaiables()
{
	//setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
}
