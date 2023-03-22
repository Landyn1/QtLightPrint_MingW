#include "mygraphicspixmapitem.h"

MyGraphicsPixMapItem::MyGraphicsPixMapItem(QGraphicsPixmapItem *parent):QGraphicsPixmapItem(parent)
{
    setFlags(GraphicsItemFlag::ItemIsMovable | GraphicsItemFlag::ItemIsSelectable);
}

MyGraphicsPixMapItem::~MyGraphicsPixMapItem(){

}

QRectF MyGraphicsPixMapItem::boundingRect() const
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
    return QRectF(0,0,w,h);
}

void MyGraphicsPixMapItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{

    QPixmap pix = this->pixmap();

    int w,h;
    w=boundingRect().width();
    h = boundingRect().height();



    painter->scale(1,-1);

    painter->drawPixmap(QRect(0,-h,w,h),pix,pix.rect());

}
