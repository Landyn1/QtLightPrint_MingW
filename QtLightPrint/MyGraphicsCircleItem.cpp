#include "MyGraphicsCircleItem.h"

MyGraphicsCircleItem::MyGraphicsCircleItem(QGraphicsEllipseItem*parent)
	: QGraphicsEllipseItem(parent)
{}

MyGraphicsCircleItem::~MyGraphicsCircleItem()
{}
QRectF MyGraphicsCircleItem::boundingRect() const
{
    auto r = qMax(this->rect().width(), this->rect().height());

    QRectF temp_rect(this->rect().left(), this->rect().top(), r, r);
    
    return temp_rect;

}
void MyGraphicsCircleItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    /*QPen pen = ScaleManager::get_instance().getMainViewItemPen();
    painter->setPen(pen);*/
    QPen pen;   // 定义一个画笔，设置画笔颜色和宽度
   //pen.setColor(QColor(0, 160, 230));
    pen.setWidthF(1);
    painter->setPen(pen);
    auto r = qMax(this->rect().width(), this->rect().height());
    if (option->state & QStyle::State_Selected) {
            float penWidth = pen.widthF();

            painter->setPen(QPen(option->palette.windowText(), 0, Qt::DashLine));

            painter->setBrush(Qt::NoBrush);
            
            painter->drawEllipse(QPointF(0, 0), r / 2, r / 2);
        }
    else {
        painter->drawEllipse(QPointF(0, 0), r / 2, r / 2);
    }

}
