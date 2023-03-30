#include "mygraphicstextitem.h"
#include<qdebug.h>
#include"mainWindow.h"
#include <QPen>
#include <QPainter>
#include <QPainterPath>
#include <QPainterPathStroker>
#include <QStyle>
#include <QStyleOptionGraphicsItem>
#include<QKeyEvent>
MyGraphicsTextItem::MyGraphicsTextItem(QGraphicsTextItem *p,QString str):QGraphicsRectItem()
{

    this->str = str;
}


void MyGraphicsTextItem::setStr(QString str,QFont font)
{

    this->str = str;
    this->font = font;

}
void MyGraphicsTextItem::setRectF()
{
    QFontMetrics fm(this->font);
    rectf = fm.boundingRect(str);
}

void MyGraphicsTextItem::setDefault_Path()
{
    path.addText(rect().x(),-rect().y(), font, str);
}
void MyGraphicsTextItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QPen pen;   // 定义一个画笔，设置画笔颜色和宽度
    //pen.setColor(QColor(0, 160, 230));
    QList<QGraphicsView*> list = scene()->views();
    QGraphicsView* view = list.first();
    double s = view->matrix().m11();
    pen.setWidthF(1/s);
    if(data(0).toInt() == -1)
    {
        pen.setColor(Qt::blue);
    }
    painter->setPen(pen);
    painter->scale(1,-1);

    painter->drawPath(path);


}
MyGraphicsTextItem::~MyGraphicsTextItem()
{

}

bool MyGraphicsTextItem::selectEvent(QPointF p)
{

    if(isSelected())
        return true;
    if(rect().contains(p))
    {
        setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
        this->setSelected(true);
        return true;
    }
    this->setFlags(NULL);
    this->setSelected(false);
    return false;
}

void MyGraphicsTextItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{

}
void MyGraphicsTextItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{

}
void MyGraphicsTextItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}
