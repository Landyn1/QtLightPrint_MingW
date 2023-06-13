#include "itemalignhandle.h"

ItemAlignHandle::ItemAlignHandle()
{

}


template<typename T> void ItemAlignHandle::leftAlign(QGraphicsItem* node,QPointF rootPos)
{
    T *t = qgraphicsitem_cast<T*>(node);
    QRectF rect = t->getRect();
    QPointF tpoint = QPointF(rect.x(),rect.y()+rect.height()/2);
    QPointF offsetPoint = tpoint-rootPos;
    t->setPos((t->pos()-offsetPoint).x(),t->pos().y());
}
template<typename T> void ItemAlignHandle::rightAlign(QGraphicsItem* node,QPointF rootPos)
{
    T *t = qgraphicsitem_cast<T*>(node);
    QRectF rect = t->getRect();
    QPointF tpoint = QPointF(rect.x()+rect.width(),rect.y()+rect.height()/2);
    QPointF offsetPoint = tpoint-rootPos;
    t->setPos((t->pos()-offsetPoint).x(),t->pos().y());
}
template<typename T> void ItemAlignHandle::topAlign(QGraphicsItem* node,QPointF rootPos)
{
    T *t = qgraphicsitem_cast<T*>(node);
    QRectF rect = t->getRect();
    QPointF tpoint = QPointF(rect.x()+rect.width()/2,rect.y()+rect.height());
    QPointF offsetPoint = tpoint-rootPos;
    t->setPos(t->pos().x(),(t->pos()-offsetPoint).y());
}
template<typename T> void ItemAlignHandle::buttomAlign(QGraphicsItem* node,QPointF rootPos)
{
    T *t = qgraphicsitem_cast<T*>(node);
    QRectF rect = t->getRect();
    QPointF tpoint = QPointF(rect.x()+rect.width()/2,rect.y());
    QPointF offsetPoint = tpoint-rootPos;
    t->setPos(t->pos().x(),(t->pos()-offsetPoint).y());
}


void ItemAlignHandle::center(mainWindow* mw)
{
    QList<QGraphicsItem*> selectitems = mw->scene->selectedItems();
    QList<QGraphicsItem*> items;
    QList<QGraphicsItem*> rootgroupitems;
    QList<QGraphicsItem*> groups;
    for(QGraphicsItem* item:selectitems)
    {
        if(item->type() == 10)
        {
            items.append(item);
            rootgroupitems.append(item);
        }
    }
    while(1)
    {
        int k=0;
        for(QGraphicsItem* item:items)
        {
            if(item->type() == 10)
            {
                k=1;
                groups.append(item);
                items.removeOne(item);
                MyGraphicsGroupItem *g =qgraphicsitem_cast<MyGraphicsGroupItem*>(item);
                items.append(g->childItems());
            }
        }
        if(k == 0)
        {
            break;
        }
    }

    QPointF rootPos;
    if(selectitems.length()>0)
        rootPos = selectitems[0]->pos();
    for(QGraphicsItem* item : selectitems)
    {
        if(item->type()>0&&item->type()!=4&&item->type()!=7&&item->type()!=10)
        {
            item->setPos(rootPos);
        }
        if(item->type() == 4)
        {
            MyGraphicsLineItem *t = qgraphicsitem_cast<MyGraphicsLineItem*>(item);
            QRectF rect = t->getRect();
            QPointF tpoint = QPointF(rect.x()+rect.width()/2,rect.y()+rect.height()/2);
            QPointF offsetPoint = tpoint-rootPos;
            t->setPos(t->pos()-offsetPoint);
        }
        if(item->type() == 7)
        {
            MyGraphicsCurveLineItem *t = qgraphicsitem_cast<MyGraphicsCurveLineItem*>(item);
            QRectF rect = t->getRect();
            QPointF tpoint = QPointF(rect.x()+rect.width()/2,rect.y()+rect.height()/2);
            QPointF offsetPoint = tpoint-rootPos;
            t->setPos(t->pos()-offsetPoint);
        }
    }
    for(QGraphicsItem* item : rootgroupitems)
    {
        MyGraphicsGroupItem *g = qgraphicsitem_cast<MyGraphicsGroupItem*>(item);
        QRect rect = g->getRect();
        QPointF gpoint = QPoint(rect.x()+rect.width()/2,rect.y()+rect.height()/2);
        QPointF offsetPoint = gpoint-rootPos;
        for(QGraphicsItem* child:items)
        {
            if(findroot(child->data(5).toInt(),groups) == item->data(0).toInt())
            {
                child->setPos(child->pos()-offsetPoint);
            }
        }
    }
    mw->scene->update();
    emit mw->scene->selectionChanged();
}


void ItemAlignHandle::left(mainWindow *mw)
{
    QList<QGraphicsItem*> selectitems = mw->scene->selectedItems();
    QList<QGraphicsItem*> items;
    QList<QGraphicsItem*> rootgroupitems;
    QList<QGraphicsItem*> groups;
    for(QGraphicsItem* item:selectitems)
    {
        if(item->type() == 10)
        {
            items.append(item);
            rootgroupitems.append(item);
        }
    }
    while(1)
    {
        int k=0;
        for(QGraphicsItem* item:items)
        {
            if(item->type() == 10)
            {
                k=1;
                groups.append(item);
                items.removeOne(item);
                MyGraphicsGroupItem *g =qgraphicsitem_cast<MyGraphicsGroupItem*>(item);
                items.append(g->childItems());
            }
        }
        if(k == 0)
        {
            break;
        }
    }
    QPointF rootPos(0,0);
    if(selectitems.length()>0)
    {
        if(selectitems[0]->type() == 1)
        {
            rootPos.setX(qgraphicsitem_cast<MyGraphicsRecItem*>(selectitems[0])->getRect().x());
        }
        else if(selectitems[0]->type() == 2)
        {
            rootPos.setX(qgraphicsitem_cast<MyGraphicsEllipseItem*>(selectitems[0])->getRect().x());
        }
        else if(selectitems[0]->type() == 3)
        {
            rootPos.setX(qgraphicsitem_cast<MyGraphicsCircleItem*>(selectitems[0])->getRect().x());
        }
        else if(selectitems[0]->type() == 4)
        {
            rootPos.setX(qgraphicsitem_cast<MyGraphicsLineItem*>(selectitems[0])->getRect().x());
        }
        else if(selectitems[0]->type() == 5)
        {
            rootPos.setX(qgraphicsitem_cast<MyGraphicsPolygonItem*>(selectitems[0])->getRect().x());
        }
        else if(selectitems[0]->type() == 6)
        {
            rootPos.setX(qgraphicsitem_cast<MyGraphicsTextItem*>(selectitems[0])->getRect().x());
        }
        else if(selectitems[0]->type() == 7)
        {
            rootPos.setX(qgraphicsitem_cast<MyGraphicsCurveLineItem*>(selectitems[0])->getRect().x());
        }
        else if(selectitems[0]->type() == 8)
        {
            rootPos.setX(qgraphicsitem_cast<MyGraphicsPixMapItem*>(selectitems[0])->getRect().x());
        }
        else if(selectitems[0]->type() == 9)
        {
            rootPos.setX(qgraphicsitem_cast<MyGraphicsCodeItem*>(selectitems[0])->getRect().x());
        }
        else if(selectitems[0]->type() == 10)
        {
            rootPos.setX(qgraphicsitem_cast<MyGraphicsGroupItem*>(selectitems[0])->getRect().x());
        }
    }
    for(QGraphicsItem* item : selectitems)
    {
        if(item->type() == 1)
        {
            leftAlign<MyGraphicsRecItem>(item,rootPos);
        }
        else if(item->type() == 2)
        {
            leftAlign<MyGraphicsEllipseItem>(item,rootPos);
        }
        else if(item->type() == 3)
        {
            leftAlign<MyGraphicsCircleItem>(item,rootPos);
        }
        else if(item->type() == 4)
        {
            leftAlign<MyGraphicsLineItem>(item,rootPos);
        }
        else if(item->type() == 5)
        {
            leftAlign<MyGraphicsPolygonItem>(item,rootPos);
        }
        else if(item->type() == 6)
        {
            leftAlign<MyGraphicsTextItem>(item,rootPos);
        }
        else if(item->type() == 7)
        {
            leftAlign<MyGraphicsCurveLineItem>(item,rootPos);
        }
        else if(item->type() == 8)
        {
            leftAlign<MyGraphicsPixMapItem>(item,rootPos);
        }
        else if(item->type() == 9)
        {
            leftAlign<MyGraphicsCodeItem>(item,rootPos);
        }
    }
    for(QGraphicsItem* item : rootgroupitems)
    {
        MyGraphicsGroupItem *g = qgraphicsitem_cast<MyGraphicsGroupItem*>(item);
        QRect rect = g->getRect();
        QPointF gpoint = QPoint(rect.x(),rect.y()+rect.height()/2);
        QPointF offsetPoint = gpoint-rootPos;
        for(QGraphicsItem* child:items)
        {
            if(findroot(child->data(5).toInt(),groups) == item->data(0).toInt())
            {
                child->setPos((child->pos()-offsetPoint).x(),child->y());
            }
        }
    }
    mw->scene->update();
    emit mw->scene->selectionChanged();
}

void ItemAlignHandle::right(mainWindow *mw)
{
    QList<QGraphicsItem*> selectitems = mw->scene->selectedItems();
    QList<QGraphicsItem*> items;
    QList<QGraphicsItem*> rootgroupitems;
    QList<QGraphicsItem*> groups;
    for(QGraphicsItem* item:selectitems)
    {
        if(item->type() == 10)
        {
            items.append(item);
            rootgroupitems.append(item);
        }
    }
    while(1)
    {
        int k=0;
        for(QGraphicsItem* item:items)
        {
            if(item->type() == 10)
            {
                k=1;
                groups.append(item);
                items.removeOne(item);
                MyGraphicsGroupItem *g =qgraphicsitem_cast<MyGraphicsGroupItem*>(item);
                items.append(g->childItems());
            }
        }
        if(k == 0)
        {
            break;
        }
    }
    QPointF rootPos(0,0);
    if(selectitems.length()>0)
    {
        if(selectitems[0]->type() == 1)
        {
            rootPos.setX(qgraphicsitem_cast<MyGraphicsRecItem*>(selectitems[0])->getRect().x()+qgraphicsitem_cast<MyGraphicsRecItem*>(selectitems[0])->getRect().width());
        }
        else if(selectitems[0]->type() == 2)
        {
            rootPos.setX(qgraphicsitem_cast<MyGraphicsEllipseItem*>(selectitems[0])->getRect().x()+qgraphicsitem_cast<MyGraphicsEllipseItem*>(selectitems[0])->getRect().width());
        }
        else if(selectitems[0]->type() == 3)
        {
            rootPos.setX(qgraphicsitem_cast<MyGraphicsCircleItem*>(selectitems[0])->getRect().x()+qgraphicsitem_cast<MyGraphicsCircleItem*>(selectitems[0])->getRect().width());
        }
        else if(selectitems[0]->type() == 4)
        {
            rootPos.setX(qgraphicsitem_cast<MyGraphicsLineItem*>(selectitems[0])->getRect().x()+qgraphicsitem_cast<MyGraphicsLineItem*>(selectitems[0])->getRect().width());
        }
        else if(selectitems[0]->type() == 5)
        {
            rootPos.setX(qgraphicsitem_cast<MyGraphicsPolygonItem*>(selectitems[0])->getRect().x()+qgraphicsitem_cast<MyGraphicsPolygonItem*>(selectitems[0])->getRect().width());
        }
        else if(selectitems[0]->type() == 6)
        {
            rootPos.setX(qgraphicsitem_cast<MyGraphicsTextItem*>(selectitems[0])->getRect().x()+qgraphicsitem_cast<MyGraphicsTextItem*>(selectitems[0])->getRect().width());
        }
        else if(selectitems[0]->type() == 7)
        {
            rootPos.setX(qgraphicsitem_cast<MyGraphicsCurveLineItem*>(selectitems[0])->getRect().x()+qgraphicsitem_cast<MyGraphicsCurveLineItem*>(selectitems[0])->getRect().width());
        }
        else if(selectitems[0]->type() == 8)
        {
            rootPos.setX(qgraphicsitem_cast<MyGraphicsPixMapItem*>(selectitems[0])->getRect().x()+qgraphicsitem_cast<MyGraphicsPixMapItem*>(selectitems[0])->getRect().width());
        }
        else if(selectitems[0]->type() == 9)
        {
            rootPos.setX(qgraphicsitem_cast<MyGraphicsCodeItem*>(selectitems[0])->getRect().x()+qgraphicsitem_cast<MyGraphicsCodeItem*>(selectitems[0])->getRect().width());
        }
        else if(selectitems[0]->type() == 10)
        {
            rootPos.setX(qgraphicsitem_cast<MyGraphicsGroupItem*>(selectitems[0])->getRect().x()+qgraphicsitem_cast<MyGraphicsGroupItem*>(selectitems[0])->getRect().width());
        }
    }
    for(QGraphicsItem* item : selectitems)
    {
        if(item->type() == 1)
        {
            rightAlign<MyGraphicsRecItem>(item,rootPos);
        }
        else if(item->type() == 2)
        {
            rightAlign<MyGraphicsEllipseItem>(item,rootPos);
        }
        else if(item->type() == 3)
        {
            rightAlign<MyGraphicsCircleItem>(item,rootPos);
        }
        else if(item->type() == 4)
        {
            rightAlign<MyGraphicsLineItem>(item,rootPos);
        }
        else if(item->type() == 5)
        {
            rightAlign<MyGraphicsPolygonItem>(item,rootPos);
        }
        else if(item->type() == 6)
        {
            rightAlign<MyGraphicsTextItem>(item,rootPos);
        }
        else if(item->type() == 7)
        {
            rightAlign<MyGraphicsCurveLineItem>(item,rootPos);
        }
        else if(item->type() == 8)
        {
            rightAlign<MyGraphicsPixMapItem>(item,rootPos);
        }
        else if(item->type() == 9)
        {
            rightAlign<MyGraphicsCodeItem>(item,rootPos);
        }
    }
    for(QGraphicsItem* item : rootgroupitems)
    {
        MyGraphicsGroupItem *g = qgraphicsitem_cast<MyGraphicsGroupItem*>(item);
        QRect rect = g->getRect();
        QPointF gpoint = QPoint(rect.x()+rect.width(),rect.y()+rect.height()/2);
        QPointF offsetPoint = gpoint-rootPos;
        for(QGraphicsItem* child:items)
        {
            if(findroot(child->data(5).toInt(),groups) == item->data(0).toInt())
            {
                child->setPos((child->pos()-offsetPoint).x(),child->y());
            }
        }
    }
    mw->scene->update();
    emit mw->scene->selectionChanged();
}

void ItemAlignHandle::top(mainWindow *mw)
{
    QList<QGraphicsItem*> selectitems = mw->scene->selectedItems();
    QList<QGraphicsItem*> items;
    QList<QGraphicsItem*> rootgroupitems;
    QList<QGraphicsItem*> groups;
    for(QGraphicsItem* item:selectitems)
    {
        if(item->type() == 10)
        {
            items.append(item);
            rootgroupitems.append(item);
        }
    }
    while(1)
    {
        int k=0;
        for(QGraphicsItem* item:items)
        {
            if(item->type() == 10)
            {
                k=1;
                groups.append(item);
                items.removeOne(item);
                MyGraphicsGroupItem *g =qgraphicsitem_cast<MyGraphicsGroupItem*>(item);
                items.append(g->childItems());
            }
        }
        if(k == 0)
        {
            break;
        }
    }
    QPointF rootPos(0,0);
    if(selectitems.length()>0)
    {
        if(selectitems[0]->type() == 1)
        {
            rootPos.setY(qgraphicsitem_cast<MyGraphicsRecItem*>(selectitems[0])->getRect().y()+qgraphicsitem_cast<MyGraphicsRecItem*>(selectitems[0])->getRect().height());
        }
        else if(selectitems[0]->type() == 2)
        {
            rootPos.setY(qgraphicsitem_cast<MyGraphicsEllipseItem*>(selectitems[0])->getRect().y()+qgraphicsitem_cast<MyGraphicsEllipseItem*>(selectitems[0])->getRect().height());
        }
        else if(selectitems[0]->type() == 3)
        {
            rootPos.setY(qgraphicsitem_cast<MyGraphicsCircleItem*>(selectitems[0])->getRect().y()+qgraphicsitem_cast<MyGraphicsCircleItem*>(selectitems[0])->getRect().height());
        }
        else if(selectitems[0]->type() == 4)
        {
            rootPos.setY(qgraphicsitem_cast<MyGraphicsLineItem*>(selectitems[0])->getRect().y()+qgraphicsitem_cast<MyGraphicsLineItem*>(selectitems[0])->getRect().height());
        }
        else if(selectitems[0]->type() == 5)
        {
            rootPos.setY(qgraphicsitem_cast<MyGraphicsPolygonItem*>(selectitems[0])->getRect().y()+qgraphicsitem_cast<MyGraphicsPolygonItem*>(selectitems[0])->getRect().height());
        }
        else if(selectitems[0]->type() == 6)
        {
            rootPos.setY(qgraphicsitem_cast<MyGraphicsTextItem*>(selectitems[0])->getRect().y()+qgraphicsitem_cast<MyGraphicsTextItem*>(selectitems[0])->getRect().height());
        }
        else if(selectitems[0]->type() == 7)
        {
            rootPos.setY(qgraphicsitem_cast<MyGraphicsCurveLineItem*>(selectitems[0])->getRect().y()+qgraphicsitem_cast<MyGraphicsCurveLineItem*>(selectitems[0])->getRect().height());
        }
        else if(selectitems[0]->type() == 8)
        {
            rootPos.setY(qgraphicsitem_cast<MyGraphicsPixMapItem*>(selectitems[0])->getRect().y()+qgraphicsitem_cast<MyGraphicsPixMapItem*>(selectitems[0])->getRect().height());
        }
        else if(selectitems[0]->type() == 9)
        {
            rootPos.setY(qgraphicsitem_cast<MyGraphicsCodeItem*>(selectitems[0])->getRect().y()+qgraphicsitem_cast<MyGraphicsCodeItem*>(selectitems[0])->getRect().height());
        }
        else if(selectitems[0]->type() == 10)
        {
            rootPos.setY(qgraphicsitem_cast<MyGraphicsGroupItem*>(selectitems[0])->getRect().y()+qgraphicsitem_cast<MyGraphicsGroupItem*>(selectitems[0])->getRect().height());
        }
    }
    for(QGraphicsItem* item : selectitems)
    {
        if(item->type() == 1)
        {
            topAlign<MyGraphicsRecItem>(item,rootPos);
        }
        else if(item->type() == 2)
        {
            topAlign<MyGraphicsEllipseItem>(item,rootPos);
        }
        else if(item->type() == 3)
        {
            topAlign<MyGraphicsCircleItem>(item,rootPos);
        }
        else if(item->type() == 4)
        {
            topAlign<MyGraphicsLineItem>(item,rootPos);
        }
        else if(item->type() == 5)
        {
            topAlign<MyGraphicsPolygonItem>(item,rootPos);
        }
        else if(item->type() == 6)
        {
            topAlign<MyGraphicsTextItem>(item,rootPos);
        }
        else if(item->type() == 7)
        {
            topAlign<MyGraphicsCurveLineItem>(item,rootPos);
        }
        else if(item->type() == 8)
        {
            topAlign<MyGraphicsPixMapItem>(item,rootPos);
        }
        else if(item->type() == 9)
        {
            topAlign<MyGraphicsCodeItem>(item,rootPos);
        }
    }
    for(QGraphicsItem* item : rootgroupitems)
    {
        MyGraphicsGroupItem *g = qgraphicsitem_cast<MyGraphicsGroupItem*>(item);
        QRect rect = g->getRect();
        QPointF gpoint = QPoint(rect.x()+rect.width()/2,rect.y()+rect.height());
        QPointF offsetPoint = gpoint-rootPos;
        for(QGraphicsItem* child:items)
        {
            if(findroot(child->data(5).toInt(),groups) == item->data(0).toInt())
            {
                child->setPos(child->pos().x(),(child->pos()-offsetPoint).y());
            }
        }
    }
    mw->scene->update();
    emit mw->scene->selectionChanged();
}

void ItemAlignHandle::buttom(mainWindow *mw)
{
    QList<QGraphicsItem*> selectitems = mw->scene->selectedItems();
    QList<QGraphicsItem*> items;
    QList<QGraphicsItem*> rootgroupitems;
    QList<QGraphicsItem*> groups;
    for(QGraphicsItem* item:selectitems)
    {
        if(item->type() == 10)
        {
            items.append(item);
            rootgroupitems.append(item);
        }
    }
    while(1)
    {
        int k=0;
        for(QGraphicsItem* item:items)
        {
            if(item->type() == 10)
            {
                k=1;
                groups.append(item);
                items.removeOne(item);
                MyGraphicsGroupItem *g =qgraphicsitem_cast<MyGraphicsGroupItem*>(item);
                items.append(g->childItems());
            }
        }
        if(k == 0)
        {
            break;
        }
    }
    QPointF rootPos(0,0);
    if(selectitems.length()>0)
    {
        if(selectitems[0]->type() == 1)
        {
            rootPos.setY(qgraphicsitem_cast<MyGraphicsRecItem*>(selectitems[0])->getRect().y());
        }
        else if(selectitems[0]->type() == 2)
        {
            rootPos.setY(qgraphicsitem_cast<MyGraphicsEllipseItem*>(selectitems[0])->getRect().y());
        }
        else if(selectitems[0]->type() == 3)
        {
            rootPos.setY(qgraphicsitem_cast<MyGraphicsCircleItem*>(selectitems[0])->getRect().y());
        }
        else if(selectitems[0]->type() == 4)
        {
            rootPos.setY(qgraphicsitem_cast<MyGraphicsLineItem*>(selectitems[0])->getRect().y());
        }
        else if(selectitems[0]->type() == 5)
        {
            rootPos.setY(qgraphicsitem_cast<MyGraphicsPolygonItem*>(selectitems[0])->getRect().y());
        }
        else if(selectitems[0]->type() == 6)
        {
            rootPos.setY(qgraphicsitem_cast<MyGraphicsTextItem*>(selectitems[0])->getRect().y());
        }
        else if(selectitems[0]->type() == 7)
        {
            rootPos.setY(qgraphicsitem_cast<MyGraphicsCurveLineItem*>(selectitems[0])->getRect().y());
        }
        else if(selectitems[0]->type() == 8)
        {
            rootPos.setY(qgraphicsitem_cast<MyGraphicsPixMapItem*>(selectitems[0])->getRect().y());
        }
        else if(selectitems[0]->type() == 9)
        {
            rootPos.setY(qgraphicsitem_cast<MyGraphicsCodeItem*>(selectitems[0])->getRect().y());
        }
        else if(selectitems[0]->type() == 10)
        {
            rootPos.setY(qgraphicsitem_cast<MyGraphicsGroupItem*>(selectitems[0])->getRect().y());
        }
    }
    for(QGraphicsItem* item : selectitems)
    {
        if(item->type() == 1)
        {
            buttomAlign<MyGraphicsRecItem>(item,rootPos);
        }
        else if(item->type() == 2)
        {
            buttomAlign<MyGraphicsEllipseItem>(item,rootPos);
        }
        else if(item->type() == 3)
        {
            buttomAlign<MyGraphicsCircleItem>(item,rootPos);
        }
        else if(item->type() == 4)
        {
            buttomAlign<MyGraphicsLineItem>(item,rootPos);
        }
        else if(item->type() == 5)
        {
            buttomAlign<MyGraphicsPolygonItem>(item,rootPos);
        }
        else if(item->type() == 6)
        {
            buttomAlign<MyGraphicsTextItem>(item,rootPos);
        }
        else if(item->type() == 7)
        {
            buttomAlign<MyGraphicsCurveLineItem>(item,rootPos);
        }
        else if(item->type() == 8)
        {
            buttomAlign<MyGraphicsPixMapItem>(item,rootPos);
        }
        else if(item->type() == 9)
        {
            buttomAlign<MyGraphicsCodeItem>(item,rootPos);
        }
    }
    for(QGraphicsItem* item : rootgroupitems)
    {
        MyGraphicsGroupItem *g = qgraphicsitem_cast<MyGraphicsGroupItem*>(item);
        QRect rect = g->getRect();
        QPointF gpoint = QPoint(rect.x()+rect.width()/2,rect.y());
        QPointF offsetPoint = gpoint-rootPos;
        for(QGraphicsItem* child:items)
        {
            if(findroot(child->data(5).toInt(),groups) == item->data(0).toInt())
            {
                child->setPos(child->pos().x(),(child->pos()-offsetPoint).y());
            }
        }
    }
    mw->scene->update();
    emit mw->scene->selectionChanged();
}

int ItemAlignHandle::findroot(int id,QList<QGraphicsItem*> items)
{


        int maxid = 0;
        for(QGraphicsItem* item : items)
        {
            if(item->data(0).toInt()>maxid)
                maxid = item->data(0).toInt();
        }
        maxid = maxid +1;
        int *ids = new int[maxid];
        //qDebug()<<"maxid"<<maxid<<"id"<<id;
        for(int i =0;i<maxid;i++)
            ids[i]=0;
        for(QGraphicsItem* item : items)
        {
            ids[item->data(0).toInt()] = item->data(5).toInt();
        }
        for(int i=0;i<maxid;i++)
        {
            //qDebug()<<i<<ids[i];
        }
        while(1)
        {
            if(ids[id] == 0)
            {
                //qDebug()<<"ddd"<<id;
                return id;
            }
            id = ids[id];
        }
}
