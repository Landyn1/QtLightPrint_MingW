#include "MyGraphicsEllipseItem.h"
#include<qdebug.h>
MyGraphicsEllipseItem::MyGraphicsEllipseItem(QGraphicsEllipseItem *parent)
	: QGraphicsEllipseItem(parent)
{}

MyGraphicsEllipseItem::~MyGraphicsEllipseItem()
{}
QRectF MyGraphicsEllipseItem::boundingRect() const
{
    auto r = qMax(this->rect().width(), this->rect().height());
    
    QRectF temp_rect = this->rect();
    //qDebug() << temp_rect << "wdwewe" << endl;
    return temp_rect;
	
}

void MyGraphicsEllipseItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    /*QPen pen = ScaleManager::get_instance().getMainViewItemPen();
    painter->setPen(pen);*/
    QPen pen;   // 定义一个画笔，设置画笔颜色和宽度
   //pen.setColor(QColor(0, 160, 230));
    pen.setWidthF(1);
    painter->setPen(pen);
    
    if (option != NULL)
    {
        if (option->state & QStyle::State_Selected) {
            float penWidth = pen.widthF();

            painter->setPen(QPen(option->palette.windowText(), 0, Qt::DashLine));

            painter->setBrush(Qt::NoBrush);
            painter->drawEllipse(QPointF(0, 0), this->rect().width() / 2, this->rect().height() / 2);
        }
        else {
              painter->drawEllipse(QPointF(0, 0), this->rect().width()/2, this->rect().height()/2);

        }
    }
    
    else {
        
        painter->drawEllipse(QPointF(0, 0), this->rect().width() / 2, this->rect().height() / 2);
    }
}
