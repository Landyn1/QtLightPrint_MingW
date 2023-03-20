#include "mygraphicscurvelineitem.h"

MyGraphicsCurveLineItem::MyGraphicsCurveLineItem(QGraphicsPathItem *parent):QGraphicsPathItem(parent)
{

}

MyGraphicsCurveLineItem::~MyGraphicsCurveLineItem()
{

}
void MyGraphicsCurveLineItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->drawPath(this->path());

    if(ispainting)
    {
        QPainterPath p;
        QPen pen;
        pen.setColor(Qt::blue);
        pen.setWidthF(0.8);
        pen.setStyle(Qt::DashLine);
        painter->setPen(pen);
        if(isfirst == false)
        {
            p.moveTo(ctl_pre);
            p.lineTo(startP);
            p.moveTo(ctl_next);
            p.lineTo(duichengdian(ctl_next,endP));
        }

        else
        {
            p.moveTo(duichengdian(ctl_next,startP));
            p.lineTo(startP);
        }
        painter->drawPath(p);
    }
}
QPointF MyGraphicsCurveLineItem::duichengdian(QPointF p1 , QPointF p2)
{
    return QPointF(p2.x()*2-p1.x(),p2.y()*2-p1.y());
}
