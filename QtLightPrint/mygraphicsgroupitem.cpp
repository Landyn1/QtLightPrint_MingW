#include "mygraphicsgroupitem.h"
#include<qdebug.h>
#include"MyGraphicsView.h"
#include"mygraphicscodeitem.h"
#include"mainWindow.h"
MyGraphicsGroupItem::MyGraphicsGroupItem(QList<QGraphicsItem*> items)
{
    setFlags(NULL);
    setSelected(false);
    for(int i=0;i<items.length();i++)
    {
        this->addToGroup(items[i]);
    }
}
MyGraphicsGroupItem::~MyGraphicsGroupItem()
{

}
QRect MyGraphicsGroupItem::getRect()
{
    QList<QGraphicsItem*> items = this->childItems();
    int x, y, w, h;
    x = 5000;
    y = 5000;
    w = -5000;
    h = -5000;
    //先确定左下角的坐标
    for (QList<QGraphicsItem*>::iterator it = items.begin(); it != items.end(); it++)
    {
        QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);

        if(node->type() == 1)
        {
            MyGraphicsRecItem *t = qgraphicsitem_cast<MyGraphicsRecItem *>(node);
            if(x > t->getRect().x())
            {
                x = t->getRect().x();
            }
            if(y > t->getRect().y())
            {
                y = t->getRect().y();
            }
        }
        else if( node ->type() == 2)
        {
            MyGraphicsEllipseItem *t = qgraphicsitem_cast<MyGraphicsEllipseItem *>(node);
            if(x > t->getRect().x())
            {
                x = t->getRect().x();
            }
            if(y > t->getRect().y())
            {
                y = t->getRect().y();
            }
        }
        else if(node->type() == 3)
        {
            MyGraphicsCircleItem *t = qgraphicsitem_cast<MyGraphicsCircleItem *>(node);
            if(x > t->getRect().x())
            {
                x = t->getRect().x();
            }
            if(y > t->getRect().y())
            {
                y = t->getRect().y();
            }
        }
        else if(node->type() == 4)
        {
            MyGraphicsLineItem *t = qgraphicsitem_cast<MyGraphicsLineItem *>(node);
            if(x > t->getRect().x())
            {
                x = t->getRect().x();
            }
            if(y > t->getRect().y())
            {
                y = t->getRect().y();
            }
        }

        else if(node->type() == 5)
        {
            MyGraphicsPolygonItem *t = qgraphicsitem_cast<MyGraphicsPolygonItem *>(node);
            if(x > t->getRect().x())
            {
                x = t->getRect().x();
            }
            if(y > t->getRect().y())
            {
                y = t->getRect().y();
            }
        }
        else if(node->type() == 6)
        {
            MyGraphicsTextItem *t = qgraphicsitem_cast<MyGraphicsTextItem *>(node);
            if(x > t->getRect().x())
            {
                x = t->getRect().x();
            }
            if(y > t->getRect().y())
            {
                y = t->getRect().y();
            }

        }
        else if(node->type() == 7)
        {
            MyGraphicsCurveLineItem *t = qgraphicsitem_cast<MyGraphicsCurveLineItem *>(node);
            if(x > t->getRect().x())
            {
                x = t->getRect().x();
            }
            if(y > t->getRect().y())
            {
                y = t->getRect().y();
            }
        }
        else if(node->type() == 8)
        {
            MyGraphicsPixMapItem *t = qgraphicsitem_cast<MyGraphicsPixMapItem *>(node);
            if(x > t->getRect().x())
            {
                x = t->getRect().x();
            }
            if(y > t->getRect().y())
            {
                y = t->getRect().y();
            }
        }
        else if(node->type() == 9)
        {
            MyGraphicsCodeItem *t = qgraphicsitem_cast<MyGraphicsCodeItem *>(node);
            if(x > t->getRect().x())
            {
                x = t->getRect().x();
            }
            if(y > t->getRect().y())
            {
                y = t->getRect().y();
            }
        }
    }
    //再确定宽高
    for (QList<QGraphicsItem*>::iterator it = items.begin(); it != items.end(); it++)
    {
        QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);
        if(node->type() == 1)
        {
            MyGraphicsRecItem *item = qgraphicsitem_cast<MyGraphicsRecItem *>(node);
            if(w<item->getRect().x()+item->getRect().width() - x)
            {
                w = item->getRect().x()+item->getRect().width() - x;
            }
            if(h<item->getRect().y()+item->getRect().height() - y)
            {
                h = item->getRect().y()+item->getRect().height() - y;
            }
        }
        else if( node ->type() == 2)
        {
            MyGraphicsEllipseItem *item = qgraphicsitem_cast<MyGraphicsEllipseItem *>(node);
            if(w<item->getRect().x()+item->getRect().width() - x)
            {
                w = item->getRect().x()+item->getRect().width() - x;
            }
            if(h<item->getRect().y()+item->getRect().height() - y)
            {
                h = item->getRect().y()+item->getRect().height() - y;
            }
        }
        else if(node->type() == 3)
        {
            MyGraphicsCircleItem *item = qgraphicsitem_cast<MyGraphicsCircleItem *>(node);
            if(w<item->getRect().x()+item->getRect().width() - x)
            {
                w = item->getRect().x()+item->getRect().width() - x;
            }
            if(h<item->getRect().y()+item->getRect().height() - y)
            {
                h = item->getRect().y()+item->getRect().height() - y;
            }

        }
        else if(node->type() == 4)
        {
            MyGraphicsLineItem *item = qgraphicsitem_cast<MyGraphicsLineItem *>(node);
            if(w<item->getRect().x()+item->getRect().width() - x)
            {
                w = item->getRect().x()+item->getRect().width() - x;
            }
            if(h<item->getRect().y()+item->getRect().height() - y)
            {
                h = item->getRect().y()+item->getRect().height() - y;
            }
        }

        else if(node->type() == 5)
        {
            MyGraphicsPolygonItem *item = qgraphicsitem_cast<MyGraphicsPolygonItem *>(node);
            if(w<item->getRect().x()+item->getRect().width() - x)
            {
                w = item->getRect().x()+item->getRect().width() - x;
            }
            if(h<item->getRect().y()+item->getRect().height() - y)
            {
                h = item->getRect().y()+item->getRect().height() - y;
            }
        }
        else if(node->type() == 6)
        {
            MyGraphicsTextItem *item = qgraphicsitem_cast<MyGraphicsTextItem *>(node);
            if(w<item->getRect().x()+item->getRect().width() - x)
            {
                w = item->getRect().x()+item->getRect().width() - x;
            }
            if(h<item->getRect().y()+item->getRect().height() - y)
            {
                h = item->getRect().y()+item->getRect().height() - y;
            }

        }
        else if(node->type() == 7)
        {
            MyGraphicsCurveLineItem *item = qgraphicsitem_cast<MyGraphicsCurveLineItem *>(node);
            if(w<item->getRect().x()+item->getRect().width() - x)
            {
                w = item->getRect().x()+item->getRect().width() - x;
            }
            if(h<item->getRect().y()+item->getRect().height() - y)
            {
                h = item->getRect().y()+item->getRect().height() - y;
            }
        }
        else if(node->type() == 8)
        {
            MyGraphicsPixMapItem *item = qgraphicsitem_cast<MyGraphicsPixMapItem *>(node);
            if(w<item->getRect().x()+item->getRect().width() - x)
            {
                w = item->getRect().x()+item->getRect().width() - x;
            }
            if(h<item->getRect().y()+item->getRect().height() - y)
            {
                h = item->getRect().y()+item->getRect().height() - y;
            }
        }
        else if(node->type() == 9)
        {
            MyGraphicsCodeItem *item = qgraphicsitem_cast<MyGraphicsCodeItem *>(node);
            if(w<item->getRect().x()+item->getRect().width() - x)
            {
                w = item->getRect().x()+item->getRect().width() - x;
            }
            if(h<item->getRect().y()+item->getRect().height() - y)
            {
                h = item->getRect().y()+item->getRect().height() - y;
            }
        }
    }
    x = x+pos().x();
    y = y+pos().y();
    return QRect(x,y,w,h);
}
QRectF MyGraphicsGroupItem::boundingRect() const
{
    QList<QGraphicsItem*> items = this->childItems();
    int x, y, w, h;
    x = 5000;
    y = 5000;
    w = -5000;
    h = -5000;
    //先确定左下角的坐标
    for (QList<QGraphicsItem*>::iterator it = items.begin(); it != items.end(); it++)
    {
        QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);

        if(node->type() == 1)
        {
            MyGraphicsRecItem *t = qgraphicsitem_cast<MyGraphicsRecItem *>(node);
            if(x > t->getRect().x())
            {
                x = t->getRect().x();
            }
            if(y > t->getRect().y())
            {
                y = t->getRect().y();
            }
        }
        else if( node ->type() == 2)
        {
            MyGraphicsEllipseItem *t = qgraphicsitem_cast<MyGraphicsEllipseItem *>(node);
            if(x > t->getRect().x())
            {
                x = t->getRect().x();
            }
            if(y > t->getRect().y())
            {
                y = t->getRect().y();
            }
        }
        else if(node->type() == 3)
        {
            MyGraphicsCircleItem *t = qgraphicsitem_cast<MyGraphicsCircleItem *>(node);
            if(x > t->getRect().x())
            {
                x = t->getRect().x();
            }
            if(y > t->getRect().y())
            {
                y = t->getRect().y();
            }
        }
        else if(node->type() == 4)
        {
            MyGraphicsLineItem *t = qgraphicsitem_cast<MyGraphicsLineItem *>(node);
            if(x > t->getRect().x())
            {
                x = t->getRect().x();
            }
            if(y > t->getRect().y())
            {
                y = t->getRect().y();
            }
        }

        else if(node->type() == 5)
        {
            MyGraphicsPolygonItem *t = qgraphicsitem_cast<MyGraphicsPolygonItem *>(node);
            if(x > t->getRect().x())
            {
                x = t->getRect().x();
            }
            if(y > t->getRect().y())
            {
                y = t->getRect().y();
            }
        }
        else if(node->type() == 6)
        {
            MyGraphicsTextItem *t = qgraphicsitem_cast<MyGraphicsTextItem *>(node);
            if(x > t->getRect().x())
            {
                x = t->getRect().x();
            }
            if(y > t->getRect().y())
            {
                y = t->getRect().y();
            }

        }
        else if(node->type() == 7)
        {
            MyGraphicsCurveLineItem *t = qgraphicsitem_cast<MyGraphicsCurveLineItem *>(node);
            if(x > t->getRect().x())
            {
                x = t->getRect().x();
            }
            if(y > t->getRect().y())
            {
                y = t->getRect().y();
            }
        }
        else if(node->type() == 8)
        {
            MyGraphicsPixMapItem *t = qgraphicsitem_cast<MyGraphicsPixMapItem *>(node);
            if(x > t->getRect().x())
            {
                x = t->getRect().x();
            }
            if(y > t->getRect().y())
            {
                y = t->getRect().y();
            }
        }
        else if(node->type() == 9)
        {
            MyGraphicsCodeItem *t = qgraphicsitem_cast<MyGraphicsCodeItem *>(node);
            if(x > t->getRect().x())
            {
                x = t->getRect().x();
            }
            if(y > t->getRect().y())
            {
                y = t->getRect().y();
            }
        }
    }
    //再确定宽高
    for (QList<QGraphicsItem*>::iterator it = items.begin(); it != items.end(); it++)
    {
        QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);
        if(node->type() == 1)
        {
            MyGraphicsRecItem *item = qgraphicsitem_cast<MyGraphicsRecItem *>(node);
            if(w<item->getRect().x()+item->getRect().width() - x)
            {
                w = item->getRect().x()+item->getRect().width() - x;
            }
            if(h<item->getRect().y()+item->getRect().height() - y)
            {
                h = item->getRect().y()+item->getRect().height() - y;
            }
        }
        else if( node ->type() == 2)
        {
            MyGraphicsEllipseItem *item = qgraphicsitem_cast<MyGraphicsEllipseItem *>(node);
            if(w<item->getRect().x()+item->getRect().width() - x)
            {
                w = item->getRect().x()+item->getRect().width() - x;
            }
            if(h<item->getRect().y()+item->getRect().height() - y)
            {
                h = item->getRect().y()+item->getRect().height() - y;
            }
        }
        else if(node->type() == 3)
        {
            MyGraphicsCircleItem *item = qgraphicsitem_cast<MyGraphicsCircleItem *>(node);
            if(w<item->getRect().x()+item->getRect().width() - x)
            {
                w = item->getRect().x()+item->getRect().width() - x;
            }
            if(h<item->getRect().y()+item->getRect().height() - y)
            {
                h = item->getRect().y()+item->getRect().height() - y;
            }

        }
        else if(node->type() == 4)
        {
            MyGraphicsLineItem *item = qgraphicsitem_cast<MyGraphicsLineItem *>(node);
            if(w<item->getRect().x()+item->getRect().width() - x)
            {
                w = item->getRect().x()+item->getRect().width() - x;
            }
            if(h<item->getRect().y()+item->getRect().height() - y)
            {
                h = item->getRect().y()+item->getRect().height() - y;
            }
        }

        else if(node->type() == 5)
        {
            MyGraphicsPolygonItem *item = qgraphicsitem_cast<MyGraphicsPolygonItem *>(node);
            if(w<item->getRect().x()+item->getRect().width() - x)
            {
                w = item->getRect().x()+item->getRect().width() - x;
            }
            if(h<item->getRect().y()+item->getRect().height() - y)
            {
                h = item->getRect().y()+item->getRect().height() - y;
            }
        }
        else if(node->type() == 6)
        {
            MyGraphicsTextItem *item = qgraphicsitem_cast<MyGraphicsTextItem *>(node);
            if(w<item->getRect().x()+item->getRect().width() - x)
            {
                w = item->getRect().x()+item->getRect().width() - x;
            }
            if(h<item->getRect().y()+item->getRect().height() - y)
            {
                h = item->getRect().y()+item->getRect().height() - y;
            }

        }
        else if(node->type() == 7)
        {
            MyGraphicsCurveLineItem *item = qgraphicsitem_cast<MyGraphicsCurveLineItem *>(node);
            if(w<item->getRect().x()+item->getRect().width() - x)
            {
                w = item->getRect().x()+item->getRect().width() - x;
            }
            if(h<item->getRect().y()+item->getRect().height() - y)
            {
                h = item->getRect().y()+item->getRect().height() - y;
            }
        }
        else if(node->type() == 8)
        {
            MyGraphicsPixMapItem *item = qgraphicsitem_cast<MyGraphicsPixMapItem *>(node);
            if(w<item->getRect().x()+item->getRect().width() - x)
            {
                w = item->getRect().x()+item->getRect().width() - x;
            }
            if(h<item->getRect().y()+item->getRect().height() - y)
            {
                h = item->getRect().y()+item->getRect().height() - y;
            }
        }
        else if(node->type() == 9)
        {
            MyGraphicsCodeItem *item = qgraphicsitem_cast<MyGraphicsCodeItem *>(node);
            if(w<item->getRect().x()+item->getRect().width() - x)
            {
                w = item->getRect().x()+item->getRect().width() - x;
            }
            if(h<item->getRect().y()+item->getRect().height() - y)
            {
                h = item->getRect().y()+item->getRect().height() - y;
            }
        }
    }
    x = x+pos().x();
    y = y+pos().y();
    return QRectF(x,y,w,h);
}

void MyGraphicsGroupItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{

}



bool MyGraphicsGroupItem::selectEvent(QPointF p)
{
    if(isSelected())
        return true;
    if(boundingRect().contains(p))
    {
          setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
          setSelected(true);
          return true;
    }
    setFlags(NULL);
    setSelected(false);
    return false;
}
