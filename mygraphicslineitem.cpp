#include "mygraphicslineitem.h"

MyGraphicsLineItem::MyGraphicsLineItem(QGraphicsPathItem *parent) : QGraphicsPathItem(parent)
{

}

MyGraphicsLineItem::~MyGraphicsLineItem()
{

}
void MyGraphicsLineItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{


    painter->drawPath(this->path());

}
