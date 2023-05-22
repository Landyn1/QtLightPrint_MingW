#include "mygraphicspixmapitem.h"
#include<qdebug.h>
MyGraphicsPixMapItem::MyGraphicsPixMapItem(QGraphicsPixmapItem *parent):QGraphicsPixmapItem(parent)
{
    setFlags(NULL);
    setSelected(false);
}

MyGraphicsPixMapItem::~MyGraphicsPixMapItem(){

}

QRectF MyGraphicsPixMapItem::boundingRect() const
{
    QPixmap pix = this->pixmap();
    int w,h;
    w=rectf.width();
    h=rectf.height();
    return QRectF(0,0,w,h);
}
void MyGraphicsPixMapItem::setDefault_Rect()
{
    QPixmap pix = this->pixmap();
    int w,h;
    w=pix.width();
    h = pix.height();

    if(w>300||h>300)
    {
        w = w/3;
        h = h/3;
    }
    rectf = QRect(0,-h,w,h);
}

void MyGraphicsPixMapItem::setRectF(QRect re)
{
    this->rectf = re;
}

void MyGraphicsPixMapItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{

    QPixmap pix = this->pixmap();

    painter->scale(1,-1);
    painter->drawPixmap(rectf,pix,pix.rect());

}

bool MyGraphicsPixMapItem::selectEvent(QPointF p,int k)
{
    if(k == 1)
    {
        setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
        setSelected(true);
        return true;
    }
    if(isSelected())
        return true;
    int w,h;
    w=rectf.width();
    h=rectf.height();
    QRectF rrr(0,0,w,h);
    if(rrr.contains(p))
    {
        setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
        setSelected(true);
        return true;
    }
    setFlags(NULL);
    setSelected(false);
    return false;




}
QRect MyGraphicsPixMapItem::getRect()
{
    int x,y,w,h;
    x = rect().x()+pos().x();
    y = rect().y()+pos().y();
    w = rect().width();
    h = rect().height();
    return QRect(x,y,w,h);
}
QRectF MyGraphicsPixMapItem::rect()
{
    return boundingRect();
}

void MyGraphicsPixMapItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{

}
void MyGraphicsPixMapItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{

}
void MyGraphicsPixMapItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}
