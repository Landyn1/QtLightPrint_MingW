#include "itemchangehandle.h"

ItemChangeHandle::ItemChangeHandle(MyGraphicsView *view)
{
    this->view = view;
}

void ItemChangeHandle::lefttop_set(QPointF p1,QPointF pressPos)
{
    QList<QGraphicsItem*> items = view->scene()->selectedItems();
    for(QGraphicsItem* item:items)
    {
        if(item->data(15).toInt()==1)
        {
            items.removeOne(item);
        }
    }
    while(1)
    {
        int k=0;
        for(QGraphicsItem * item : items)
        {
            if(item->type() == 10)
            {
                k=1;
                QList<QGraphicsItem*> chids = qgraphicsitem_cast<MyGraphicsGroupItem *>(item)->childItems();
                items.removeOne(item);
                for(QGraphicsItem * child : chids)
                {
                    child->setData(5,item->data(0).toInt());
                    items.append(child);
                }
            }
        }
        if(k == 0)
        {
            break;
        }
    }
    double s = view->matrix().m11();
    QList<QGraphicsItem *> itemss = view->scene()->items();
    for (QList<QGraphicsItem*>::iterator it = itemss.begin(); it != itemss.end(); it++)
    {
        QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);

        if(node->data(0).toInt()<0)
        {
            view->scene()->removeItem(node);
        }
    }
    QPointF roof;
    roof.setX(view->itemad->mapToScene(view->itemad->rect()).value(1).x()-10/s);
    roof.setY(view->itemad->mapToScene(view->itemad->rect()).value(1).y()+10/s);
    for (QList<QGraphicsItem*>::iterator it = items.begin(); it != items.end(); it++)
    {
        QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);
        if(node->type() == 1)
        {
            MyGraphicsRecItem* item = qgraphicsitem_cast<MyGraphicsRecItem *>(node);
            MyGraphicsRecItem *tmp = new MyGraphicsRecItem();
            QPointF poss  = item->pos();
            double t1 = (pressPos.x()-p1.x())/(view->itemad->rec.width());
            double t2 = (p1.y()-pressPos.y())/(view->itemad->rec.height());
            double proportion = 1;
            if(t1>0&&t2>0)
            {
                proportion = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                proportion = fmax(t1,t2);
            }
            else
            {
                proportion = fmin(t1,t2);
            }
            tmp->setPos((poss-roof)*proportion+poss);
            tmp->setRect(-item->rect().width()*(1+proportion)/2,-item->rect().height()*(1+proportion)/2,item->rect().width()*(1+proportion),item->rect().height()*(1+proportion));
            tmp->setData(0,-1);
            tmp->setData(5,item->data(5).toInt());
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            tmp->set_brush(item->angle,item->space);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 2)
        {
            MyGraphicsEllipseItem* item = qgraphicsitem_cast<MyGraphicsEllipseItem *>(node);
            MyGraphicsEllipseItem *tmp = new MyGraphicsEllipseItem();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t1 = (pressPos.x()-p1.x())/(view->itemad->rec.width());
            double t2 = (p1.y()-pressPos.y())/(view->itemad->rec.height());
            double proportion = 1;
            if(t1>0&&t2>0)
            {
                proportion = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                proportion = fmax(t1,t2);
            }
            else
            {
                proportion = fmin(t1,t2);
            }

            tmp->setPos((poss-roof)*proportion+poss);
            tmp->setRect(-item->rect().width()*(1+proportion)/2,-item->rect().height()*(1+proportion)/2,item->rect().width()*(1+proportion),item->rect().height()*(1+proportion));
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->set_brush(item->angle,item->space);
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 3)
        {
            MyGraphicsCircleItem* item = qgraphicsitem_cast<MyGraphicsCircleItem *>(node);
            MyGraphicsCircleItem *tmp = new MyGraphicsCircleItem();
            QPointF poss = item->pos();
            double t1 = (pressPos.x()-p1.x())/(view->itemad->rec.width());
            double t2 = (p1.y()-pressPos.y())/(view->itemad->rec.height());
            double proportion = 1;
            if(t1>0&&t2>0)
            {
                proportion = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                proportion = fmax(t1,t2);
            }
            else
            {
                proportion = fmin(t1,t2);
            }
            tmp->setPos((poss-roof)*proportion+poss);
            tmp->setRect(-item->rect().width()*(1+proportion)/2,-item->rect().height()*(1+proportion)/2,item->rect().width()*(1+proportion),item->rect().height()*(1+proportion));
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->set_brush(item->angle,item->space);
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 4)
        {
            MyGraphicsLineItem *item = qgraphicsitem_cast<MyGraphicsLineItem *>(node);
            QRectF rect = item->getRect();
            QPointF p2 (rect.x(),rect.y());
            QPointF p3 (rect.x()+rect.width(),rect.y()+rect.height());
            MyGraphicsLineItem *tmp = new MyGraphicsLineItem();
            QPointF poss = item->pos();
            double t1 = (pressPos.x()-p1.x())/(view->itemad->rec.width());
            double t2 = (p1.y()-pressPos.y())/(view->itemad->rec.height());
            double proportion = 1;
            if(t1>0&&t2>0)
            {
                proportion = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                proportion = fmax(t1,t2);
            }
            else
            {
                proportion = fmin(t1,t2);
            }
            QPainterPath path1 = item->path();
            QPainterPath path2 ;
            tmp->setPos((poss-roof)*proportion+poss);
            QPointF offset = tmp->pos() - item->pos();
            for (int i = 0; i < path1.elementCount(); i++)
            {
                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(proportion)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
            }
            tmp->name = item->name;
            tmp->setPath(path2);
            tmp->setData(0,-1);
            tmp->set_brush(item->angle,item->space);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 5)
        {
            MyGraphicsPolygonItem *item = qgraphicsitem_cast<MyGraphicsPolygonItem *>(node);
            QRectF rect = item->getRect();
            QPointF p2 (rect.x(),rect.y());
            QPointF p3 (rect.x()+rect.width(),rect.y()+rect.height());
            MyGraphicsPolygonItem *tmp = new MyGraphicsPolygonItem();
            double w = p3.x()-p2.x(),h = p3.y()-p2.y();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t1 = (pressPos.x()-p1.x())/(view->itemad->rec.width());
            double t2 = (p1.y()-pressPos.y())/(view->itemad->rec.height());
            double proportion = 1;
            if(t1>0&&t2>0)
            {
                proportion = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                proportion = fmax(t1,t2);
            }
            else
            {
                proportion = fmin(t1,t2);
            }
            tmp->num = item->num;
            tmp->setPos((poss-roof)*proportion+poss);
            tmp->setRect(-item->rect().width()*(1+proportion)/2,-item->rect().height()*(1+proportion)/2,item->rect().width()*(1+proportion),item->rect().height()*(1+proportion));
            tmp->setDefault_Path();
            tmp->setData(0,-1);
            tmp->set_brush(item->angle,item->space);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 6)
        {
            MyGraphicsTextItem* item = qgraphicsitem_cast<MyGraphicsTextItem *>(node);
            QPointF p2 = item->mapToScene(item->rect()).value(0);
            QPointF p3 = item->mapToScene(item->rect()).value(2);
            MyGraphicsTextItem *tmp = new MyGraphicsTextItem();
            double w = p3.x()-p2.x(),h = p3.y()-p2.y();
            QPointF poss = item->pos();
            double t1 = (pressPos.x()-p1.x())/(view->itemad->rec.width());
            double t2 = (p1.y()-pressPos.y())/(view->itemad->rec.height());
            double proportion = 1;
            if(t1>0&&t2>0)
            {
                proportion = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                proportion = fmax(t1,t2);
            }
            else
            {
                proportion = fmin(t1,t2);
            }
            QPainterPath path1 = item->path;
            QPainterPath path2 ;
            int k=0;
            QPointF c1,c2;
            tmp->setPos((poss-roof)*proportion+poss);
            QPointF offset = tmp->pos() - item->pos();   //用来计算path2的pos差值
            for (int i = 0; i < path1.elementCount(); i++)
            {

                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(proportion)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
                else if(element.isCurveTo())
                {

                    c1 = po2;
                    k++;
                    //path2.cubicTo(po2);
                }
                else
                {
                    if(k%3 == 1)
                    {

                        c2 = po2;
                        k++;
                    }
                    else if(k%3 == 2)
                    {
                        path2.cubicTo(c1,c2,po2);
                        k++;
                    }

                }
            }
            tmp->setRect(-(item->rect().width()*(1+proportion))/2,-(item->rect().height()*(1+proportion))/2,item->rect().width()*(1+proportion),item->rect().height()*(1+proportion));
            tmp->setPath(path2);
            tmp->setData(0,-1);
            tmp->set_brush(item->angle,item->space);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 7)
        {
            MyGraphicsCurveLineItem *item = qgraphicsitem_cast<MyGraphicsCurveLineItem *>(node);
            //QList<double> list = item->getRect();
            MyGraphicsCurveLineItem *tmp = new MyGraphicsCurveLineItem();
            QPointF poss = item->pos();
            double t1 = (pressPos.x()-p1.x())/(view->itemad->rec.width());
            double t2 = (p1.y()-pressPos.y())/(view->itemad->rec.height());
            double proportion = 1;
            if(t1>0&&t2>0)
            {
                proportion = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                proportion = fmax(t1,t2);
            }
            else
            {
                proportion = fmin(t1,t2);
            }
            QPainterPath path1 = item->path();
            QPainterPath path2 ;
            int k=0;
            QPointF c1,c2;
            tmp->setPos((poss-roof)*proportion+poss);
            QPointF offset = tmp->pos() - item->pos();   //用来计算path2的pos差值
            for (int i = 0; i < path1.elementCount(); i++)
            {

                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(proportion)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
                else if(element.isCurveTo())
                {

                    c1 = po2;
                    k++;
                    //path2.cubicTo(po2);
                }
                else
                {
                    if(k%3 == 1)
                    {

                        c2 = po2;
                        k++;
                    }
                    else if(k%3 == 2)
                    {
                        path2.cubicTo(c1,c2,po2);
                        k++;
                    }

                }
            }

            tmp->setPath(path2);
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 8)
        {
            MyGraphicsPixMapItem* item = qgraphicsitem_cast<MyGraphicsPixMapItem *>(node);
            MyGraphicsPixMapItem *tmp = new MyGraphicsPixMapItem();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t1 = (pressPos.x()-p1.x())/(view->itemad->rec.width());
            double t2 = (p1.y()-pressPos.y())/(view->itemad->rec.height());
            double proportion = 1;
            if(t1>0&&t2>0)
            {
                proportion = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                proportion = fmax(t1,t2);
            }
            else
            {
                proportion = fmin(t1,t2);
            }
            tmp->setPixmap(item->pixmap());
            tmp->setPos((poss-roof)*proportion+poss);
            double w = qAbs(item->rect().width()*(1+proportion));
            double h = qAbs(item->rect().height()*(1+proportion));
            if(item->rect().width()*(1+proportion)<0)
            {
                tmp->setPos((poss-roof)*proportion+poss-QPointF(w,h));
            }

            tmp->setRectF(QRect(0,-h,w,h));
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 9)
        {
            MyGraphicsCodeItem *item = qgraphicsitem_cast<MyGraphicsCodeItem *>(node);
            MyGraphicsCodeItem *tmp = new MyGraphicsCodeItem();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t1 = (pressPos.x()-p1.x())/(view->itemad->rec.width());
            double t2 = (p1.y()-pressPos.y())/(view->itemad->rec.height());
            double proportion = 1;
            if(t1>0&&t2>0)
            {
                proportion = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                proportion = fmax(t1,t2);
            }
            else
            {
                proportion = fmin(t1,t2);
            }
            QPainterPath path1 = item->path;
            QPainterPath path2 ;
            tmp->setPos((poss-roof)*proportion+poss);
            QPointF offset = tmp->pos() - item->pos();
            for (int i = 0; i < path1.elementCount(); i++)
            {
                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(proportion)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
            }
            tmp->setRect(-(item->rect().width()*(1+proportion))/2,-(item->rect().height()*(1+proportion))/2,item->rect().width()*(1+proportion),item->rect().height()*(1+proportion));

            tmp->name = item->name;
            tmp->path = (path2);
            tmp->setData(0,-1);
            tmp->text = item->text;
            tmp->codetype = item->codetype;
            tmp->set_brush(item->angle,item->space);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
    }
    view->scene()->update();
}


void ItemChangeHandle::midtop_set(QPointF p1,QPointF pressPos)
{
    QList<QGraphicsItem*> items = view->scene()->selectedItems();
    for(QGraphicsItem* item:items)
    {
        if(item->data(15).toInt()==1)
        {
            items.removeOne(item);
        }
    }
    while(1)
    {
        int k=0;
        for(QGraphicsItem * item : items)
        {
            if(item->type() == 10)
            {
                k=1;
                QList<QGraphicsItem*> chids = qgraphicsitem_cast<MyGraphicsGroupItem *>(item)->childItems();
                items.removeOne(item);
                for(QGraphicsItem * child : chids)
                {
                    child->setData(5,item->data(0).toInt());
                    items.append(child);
                }
            }
        }
        if(k == 0)
        {
            break;
        }
    }
    double s = view->matrix().m11();
    QList<QGraphicsItem *> itemss = view->scene()->items();
    for (QList<QGraphicsItem*>::iterator it = itemss.begin(); it != itemss.end(); it++)
    {
        QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);

        if(node->data(0).toInt()<0)
        {
            view->scene()->removeItem(node);
        }
    }
    QPointF roof;
    roof.setX(view->itemad->mapToScene(view->itemad->rect()).value(1).x()-10/s);
    roof.setY(view->itemad->mapToScene(view->itemad->rect()).value(1).y()+10/s);
    for (QList<QGraphicsItem*>::iterator it = items.begin(); it != items.end(); it++)
    {
        QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);
        if(node->type() == 1)
        {
            MyGraphicsRecItem* item = qgraphicsitem_cast<MyGraphicsRecItem *>(node);

            MyGraphicsRecItem *tmp = new MyGraphicsRecItem();
            QPointF poss = item->pos();
            double t2 = (p1.y()-pressPos.y())/(view->itemad->rec.height());
            double proportion = t2;
            tmp->setPos(poss.x(),((poss-roof)*proportion+poss).y());
            tmp->setRect(-item->rect().width()/2,-item->rect().height()*(1+proportion)/2,item->rect().width(),item->rect().height()*(1+proportion));
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            tmp->set_brush(item->angle,item->space);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 2)
        {
            MyGraphicsEllipseItem* item = qgraphicsitem_cast<MyGraphicsEllipseItem *>(node);
            QPointF p2 = item->mapToScene(item->rect()).value(0);
            QPointF p3 = item->mapToScene(item->rect()).value(2);
            MyGraphicsEllipseItem *tmp = new MyGraphicsEllipseItem();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t2 = (p1.y()-pressPos.y())/(view->itemad->rec.height());
            double proportion = t2;

            tmp->setPos(poss.x(),((poss-roof)*proportion+poss).y());
            tmp->setRect(-item->rect().width()/2,-item->rect().height()*(1+proportion)/2,item->rect().width(),item->rect().height()*(1+proportion));
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->set_brush(item->angle,item->space);
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 3)
        {
            MyGraphicsCircleItem* item = qgraphicsitem_cast<MyGraphicsCircleItem *>(node);
            MyGraphicsCircleItem *tmp = new MyGraphicsCircleItem();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t2 = (p1.y()-pressPos.y())/(view->itemad->rec.height());
            double proportion = t2;
            tmp->setPos(poss.x(),((poss-roof)*proportion+poss).y());
            tmp->setRect(-item->rect().width()/2,-item->rect().height()*(1+proportion)/2,item->rect().width(),item->rect().height()*(1+proportion));
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->set_brush(item->angle,item->space);
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 4)
        {
            MyGraphicsLineItem *item = qgraphicsitem_cast<MyGraphicsLineItem *>(node);
            QRectF rect = item->getRect();
            QPointF p2 (rect.x(),rect.y());
            QPointF p3 (rect.x()+rect.width(),rect.y()+rect.height());
            MyGraphicsLineItem *tmp = new MyGraphicsLineItem();
            double t2 = (p1.y()-pressPos.y())/(view->itemad->rec.height());
            double proportion = t2;
            QPainterPath path1 = item->path();
            QPainterPath path2 ;
            QPointF poss = item->pos();
            tmp->setPos(poss.x(),((poss-roof)*proportion+poss).y());
            QPointF offset = tmp->pos() - item->pos();

            for (int i = 0; i < path1.elementCount(); i++)
            {
                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(proportion)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                po2.setX(item->mapFromScene(po).x());
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
            }
            tmp->setPath(path2);
            tmp->setData(0,-1);
            tmp->set_brush(item->angle,item->space);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 5)
        {
            MyGraphicsPolygonItem *item = qgraphicsitem_cast<MyGraphicsPolygonItem *>(node);
            MyGraphicsPolygonItem *tmp = new MyGraphicsPolygonItem();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t2 = (p1.y()-pressPos.y())/(view->itemad->rec.height());
            double proportion = t2;
            tmp->num = item->num;
            tmp->setPos(poss.x(),((poss-roof)*proportion+poss).y());
            tmp->setRect(-item->rect().width()/2,-item->rect().height()*(1+proportion)/2,item->rect().width(),item->rect().height()*(1+proportion));
            tmp->setData(0,-1);
            tmp->setDefault_Path();
            tmp->setData(0,-1);
            tmp->set_brush(item->angle,item->space);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 6)
        {
            MyGraphicsTextItem* item = qgraphicsitem_cast<MyGraphicsTextItem *>(node);
            MyGraphicsTextItem *tmp = new MyGraphicsTextItem();
            QPointF poss = item->pos();
            double t2 = (p1.y()-pressPos.y())/(view->itemad->rec.height());
            double proportion = t2;
            QPainterPath path1 = item->path;
            QPainterPath path2 ;
            int k=0;
            QPointF c1,c2;
            tmp->setPos(poss.x(),((poss-roof)*proportion+poss).y());
            QPointF offset = tmp->pos() - item->pos();   //用来计算path2的pos差值
            for (int i = 0; i < path1.elementCount(); i++)
            {

                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(proportion)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                po2.setX(item->mapFromScene(po).x());
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
                else if(element.isCurveTo())
                {

                    c1 = po2;
                    k++;
                    //path2.cubicTo(po2);
                }
                else
                {
                    if(k%3 == 1)
                    {

                        c2 = po2;
                        k++;
                    }
                    else if(k%3 == 2)
                    {
                        path2.cubicTo(c1,c2,po2);
                        k++;
                    }

                }
            }
            tmp->setRect(-(item->rect().width())/2,-(item->rect().height()*(1+proportion))/2,item->rect().width(),item->rect().height()*(1+proportion));
            tmp->setPath(path2);
            tmp->setData(0,-1);
            tmp->set_brush(item->angle,item->space);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 7)
        {
            MyGraphicsCurveLineItem* item = qgraphicsitem_cast<MyGraphicsCurveLineItem *>(node);
            MyGraphicsCurveLineItem *tmp = new MyGraphicsCurveLineItem();
            QPointF poss = item->pos();
            double t2 = (p1.y()-pressPos.y())/(view->itemad->rec.height());
            double proportion = t2;
            QPainterPath path1 = item->path();
            QPainterPath path2 ;
            int k=0;
            QPointF c1,c2;
            tmp->setPos(poss.x(),((poss-roof)*proportion+poss).y());
            QPointF offset = tmp->pos() - item->pos();   //用来计算path2的pos差值
            for (int i = 0; i < path1.elementCount(); i++)
            {

                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(proportion)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                po2.setX(item->mapFromScene(po).x());
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
                else if(element.isCurveTo())
                {

                    c1 = po2;
                    k++;
                    //path2.cubicTo(po2);
                }
                else
                {
                    if(k%3 == 1)
                    {

                        c2 = po2;
                        k++;
                    }
                    else if(k%3 == 2)
                    {
                        path2.cubicTo(c1,c2,po2);
                        k++;
                    }

                }
            }
            tmp->setPath(path2);
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 8)
        {
            MyGraphicsPixMapItem* item = qgraphicsitem_cast<MyGraphicsPixMapItem *>(node);
            MyGraphicsPixMapItem *tmp = new MyGraphicsPixMapItem();
            QPointF poss = item->pos();
            double t2 = (p1.y()-pressPos.y())/(view->itemad->rec.height());
            double proportion = t2;
            tmp->setPixmap(item->pixmap());
            tmp->setPos( poss.x(),((poss-roof)*proportion+poss).y());
            double w = qAbs(item->rect().width());
            double h = qAbs(item->rect().height()*(1+proportion));
            if(item->rect().height()*(1+proportion)<0)
            {
                tmp->setPos(tmp->pos()-QPointF(0,h));
            }

            tmp->setRectF(QRect(0,-h,w,h));
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 9)
        {
            MyGraphicsCodeItem *item = qgraphicsitem_cast<MyGraphicsCodeItem *>(node);
            QPointF p2 = item->mapToScene(item->rect()).value(0);
            QPointF p3 = item->mapToScene(item->rect()).value(2);
            MyGraphicsCodeItem *tmp = new MyGraphicsCodeItem();
            double t2 = (p1.y()-pressPos.y())/(view->itemad->rec.height());
            double proportion = t2;
            QPainterPath path1 = item->path;
            QPainterPath path2 ;
            QPointF poss = item->pos();
            tmp->setPos(poss.x(),((poss-roof)*proportion+poss).y());
            QPointF offset = tmp->pos() - item->pos();

            for (int i = 0; i < path1.elementCount(); i++)
            {
                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(proportion)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                po2.setX(item->mapFromScene(po).x());
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
            }
            tmp->setRect(-(item->rect().width())/2,-(item->rect().height()*(1+proportion))/2,item->rect().width(),item->rect().height()*(1+proportion));

            tmp->path = (path2);
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            tmp->text = item->text;
            tmp->codetype = item->codetype;
            tmp->set_brush(item->angle,item->space);
            view->scene()->addItem(tmp);
        }
    }
    view->scene()->update();
}

void ItemChangeHandle::righttop_set(QPointF p1, QPointF pressPos)
{
    QList<QGraphicsItem*> items = view->scene()->selectedItems();
    for(QGraphicsItem* item:items)
    {
        if(item->data(15).toInt()==1)
        {
            items.removeOne(item);
        }
    }
    while(1)
    {
        int k=0;
        for(QGraphicsItem * item : items)
        {
            if(item->type() == 10)
            {
                k=1;
                QList<QGraphicsItem*> chids = qgraphicsitem_cast<MyGraphicsGroupItem *>(item)->childItems();
                items.removeOne(item);
                for(QGraphicsItem * child : chids)
                {
                    child->setData(5,item->data(0).toInt());
                    items.append(child);
                }
            }
        }
        if(k == 0)
        {
            break;
        }
    }
    double s = view->matrix().m11();
    QList<QGraphicsItem *> itemss = view->scene()->items();
    for (QList<QGraphicsItem*>::iterator it = itemss.begin(); it != itemss.end(); it++)
    {
        QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);

        if(node->data(0).toInt()<0)
        {
            view->scene()->removeItem(node);
        }
    }
    QPointF roof;
    roof.setX(view->itemad->mapToScene(view->itemad->rect()).value(0).x()+10/s);
    roof.setY(view->itemad->mapToScene(view->itemad->rect()).value(0).y()+10/s);
    for (QList<QGraphicsItem*>::iterator it = items.begin(); it != items.end(); it++)
    {
        QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);
        if(node->type() == 1)
        {
            MyGraphicsRecItem* item = qgraphicsitem_cast<MyGraphicsRecItem *>(node);
            QPointF p2 = item->mapToScene(item->rect()).value(0);
            //QPointF p3 = item->mapToScene(item->rect()).value(2);
            MyGraphicsRecItem *tmp = new MyGraphicsRecItem();
            QPointF poss =item->pos();
            double t1 = (-pressPos.x()+p1.x())/(view->itemad->rec.width());
            double t2 = (p1.y()-pressPos.y())/(view->itemad->rec.height());
            double proportion = 1;
            if(t1>0&&t2>0)
            {
                proportion = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                proportion = fmax(t1,t2);
            }
            else
            {
                proportion = fmin(t1,t2);
            }
            tmp->setPos((poss-roof)*proportion+poss);
            tmp->setRect(-item->rect().width()*(1+proportion)/2,-item->rect().height()*(1+proportion)/2,item->rect().width()*(1+proportion),item->rect().height()*(1+proportion));
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            tmp->set_brush(item->angle,item->space);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 2)
        {
            MyGraphicsEllipseItem* item = qgraphicsitem_cast<MyGraphicsEllipseItem *>(node);
            MyGraphicsEllipseItem *tmp = new MyGraphicsEllipseItem();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t1 = (-pressPos.x()+p1.x())/(view->itemad->rec.width());
            double t2 = (p1.y()-pressPos.y())/(view->itemad->rec.height());
            double proportion = 1;
            if(t1>0&&t2>0)
            {
                proportion = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                proportion = fmax(t1,t2);
            }
            else
            {
                proportion = fmin(t1,t2);
            }

            tmp->setPos((poss-roof)*proportion+poss);
            tmp->setRect(-item->rect().width()*(1+proportion)/2,-item->rect().height()*(1+proportion)/2,item->rect().width()*(1+proportion),item->rect().height()*(1+proportion));
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->set_brush(item->angle,item->space);
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 3)
        {
            MyGraphicsCircleItem* item = qgraphicsitem_cast<MyGraphicsCircleItem *>(node);
            MyGraphicsCircleItem *tmp = new MyGraphicsCircleItem();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t1 = (-pressPos.x()+p1.x())/(view->itemad->rec.width());
            double t2 = (p1.y()-pressPos.y())/(view->itemad->rec.height());
            double proportion = 1;
            if(t1>0&&t2>0)
            {
                proportion = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                proportion = fmax(t1,t2);
            }
            else
            {
                proportion = fmin(t1,t2);
            }

            tmp->setPos((poss-roof)*proportion+poss);
            tmp->setRect(-item->rect().width()*(1+proportion)/2,-item->rect().height()*(1+proportion)/2,item->rect().width()*(1+proportion),item->rect().height()*(1+proportion));
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->set_brush(item->angle,item->space);
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 4)
        {
            MyGraphicsLineItem *item = qgraphicsitem_cast<MyGraphicsLineItem *>(node);
            MyGraphicsLineItem *tmp = new MyGraphicsLineItem();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t1 = (-pressPos.x()+p1.x())/(view->itemad->rec.width());
            double t2 = (p1.y()-pressPos.y())/(view->itemad->rec.height());
            double proportion = 1;
            if(t1>0&&t2>0)
            {
                proportion = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                proportion = fmax(t1,t2);
            }
            else
            {
                proportion = fmin(t1,t2);
            }
            QPainterPath path1 = item->path();
            QPainterPath path2 ;
            tmp->setPos((poss-roof)*proportion+poss);
            QPointF offset = tmp->pos() - item->pos();
            for (int i = 0; i < path1.elementCount(); i++)
            {
                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(proportion)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
            }

            tmp->setPath(path2);
            tmp->setData(0,-1);
            tmp->set_brush(item->angle,item->space);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 5)
        {
            MyGraphicsPolygonItem *item = qgraphicsitem_cast<MyGraphicsPolygonItem *>(node);
            MyGraphicsPolygonItem *tmp = new MyGraphicsPolygonItem();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t1 = (-pressPos.x()+p1.x())/(view->itemad->rec.width());
            double t2 = (p1.y()-pressPos.y())/(view->itemad->rec.height());
            double proportion = 1;
            if(t1>0&&t2>0)
            {
                proportion = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                proportion = fmax(t1,t2);
            }
            else
            {
                proportion = fmin(t1,t2);
            }
            tmp->num = item->num;
            tmp->setPos((poss-roof)*proportion+poss);
            tmp->setRect(-item->rect().width()*(1+proportion)/2,-item->rect().height()*(1+proportion)/2,item->rect().width()*(1+proportion),item->rect().height()*(1+proportion));
            tmp->setDefault_Path();
            tmp->setData(0,-1);
            tmp->set_brush(item->angle,item->space);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 6)
        {
            MyGraphicsTextItem* item = qgraphicsitem_cast<MyGraphicsTextItem *>(node);
            MyGraphicsTextItem *tmp = new MyGraphicsTextItem();
            QPointF poss = item->pos();
            double t1 = (-pressPos.x()+p1.x())/(view->itemad->rec.width());
            double t2 = (p1.y()-pressPos.y())/(view->itemad->rec.height());
            double proportion = 1;
            if(t1>0&&t2>0)
            {
                proportion = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                proportion = fmax(t1,t2);
            }
            else
            {
                proportion = fmin(t1,t2);
            }
            QPainterPath path1 = item->path;
            QPainterPath path2 ;
            int k=0;
            QPointF c1,c2;
            tmp->setPos((poss-roof)*proportion+poss);

            QPointF offset = tmp->pos() - item->pos();   //用来计算path2的pos差值
            for (int i = 0; i < path1.elementCount(); i++)
            {

                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(proportion)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
                else if(element.isCurveTo())
                {

                    c1 = po2;
                    k++;
                    //path2.cubicTo(po2);
                }
                else
                {
                    if(k%3 == 1)
                    {

                        c2 = po2;
                        k++;
                    }
                    else if(k%3 == 2)
                    {
                        path2.cubicTo(c1,c2,po2);
                        k++;
                    }

                }
            }
            tmp->setRect(-(item->rect().width()*(1+proportion))/2,-(item->rect().height()*(1+proportion))/2,item->rect().width()*(1+proportion),item->rect().height()*(1+proportion));
            tmp->setPath(path2);
            tmp->setData(0,-1);
            tmp->set_brush(item->angle,item->space);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 7)
        {
            MyGraphicsCurveLineItem *item = qgraphicsitem_cast<MyGraphicsCurveLineItem *>(node);
            //QList<double> list = item->getRect();
            MyGraphicsCurveLineItem *tmp = new MyGraphicsCurveLineItem();
            QPointF poss = item->pos();
            double t1 = (-pressPos.x()+p1.x())/(view->itemad->rec.width());
            double t2 = (p1.y()-pressPos.y())/(view->itemad->rec.height());
            double proportion = 1;
            if(t1>0&&t2>0)
            {
                proportion = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                proportion = fmax(t1,t2);
            }
            else
            {
                proportion = fmin(t1,t2);
            }
            QPainterPath path1 = item->path();
            QPainterPath path2 ;
            int k=0;
            QPointF c1,c2;
            tmp->setPos((poss-roof)*proportion+poss);
            QPointF offset = tmp->pos() - item->pos();   //用来计算path2的pos差值
            for (int i = 0; i < path1.elementCount(); i++)
            {

                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(proportion)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
                else if(element.isCurveTo())
                {

                    c1 = po2;
                    k++;
                    //path2.cubicTo(po2);
                }
                else
                {
                    if(k%3 == 1)
                    {

                        c2 = po2;
                        k++;
                    }
                    else if(k%3 == 2)
                    {
                        path2.cubicTo(c1,c2,po2);
                        k++;
                    }

                }
            }

            tmp->setPath(path2);
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 8)
        {
            MyGraphicsPixMapItem* item = qgraphicsitem_cast<MyGraphicsPixMapItem *>(node);
            MyGraphicsPixMapItem *tmp = new MyGraphicsPixMapItem();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t1 = (-pressPos.x()+p1.x())/(view->itemad->rec.width());
            double t2 = (p1.y()-pressPos.y())/(view->itemad->rec.height());
            double proportion = 1;
            if(t1>0&&t2>0)
            {
                proportion = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                proportion = fmax(t1,t2);
            }
            else
            {
                proportion = fmin(t1,t2);
            }
            tmp->setPixmap(item->pixmap());
            tmp->setPos((poss-roof)*proportion+poss);
            double w = qAbs(item->rect().width()*(1+proportion));
            double h = qAbs(item->rect().height()*(1+proportion));
            if(item->rect().width()*(1+proportion)<0)
            {
                tmp->setPos((poss-roof)*proportion+poss-QPointF(w,h));
            }

            tmp->setRectF(QRect(0,-h,w,h));
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 9)
        {
            MyGraphicsCodeItem *item = qgraphicsitem_cast<MyGraphicsCodeItem *>(node);
            MyGraphicsCodeItem *tmp = new MyGraphicsCodeItem();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t1 = (-pressPos.x()+p1.x())/(view->itemad->rec.width());
            double t2 = (p1.y()-pressPos.y())/(view->itemad->rec.height());
            double proportion = 1;
            if(t1>0&&t2>0)
            {
                proportion = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                proportion = fmax(t1,t2);
            }
            else
            {
                proportion = fmin(t1,t2);
            }
            QPainterPath path1 = item->path;
            QPainterPath path2 ;
            tmp->setPos((poss-roof)*proportion+poss);
            QPointF offset = tmp->pos() - item->pos();
            for (int i = 0; i < path1.elementCount(); i++)
            {
                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(proportion)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
            }
            tmp->setRect(-(item->rect().width()*(1+proportion))/2,-(item->rect().height()*(1+proportion))/2,item->rect().width()*(1+proportion),item->rect().height()*(1+proportion));

            tmp->path = (path2);
            tmp->setData(0,-1);
            tmp->text = item->text;
            tmp->codetype = item->codetype;
            tmp->set_brush(item->angle,item->space);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
    }
    view->scene()->update();
}

void ItemChangeHandle::leftbuttom_set(QPointF p1,QPointF pressPos)
{
    QList<QGraphicsItem*> items = view->scene()->selectedItems();
    for(QGraphicsItem* item:items)
    {
        if(item->data(15).toInt()==1)
        {
            items.removeOne(item);
        }
    }
    while(1)
    {
        int k=0;
        for(QGraphicsItem * item : items)
        {
            if(item->type() == 10)
            {
                k=1;
                QList<QGraphicsItem*> chids = qgraphicsitem_cast<MyGraphicsGroupItem *>(item)->childItems();
                items.removeOne(item);
                for(QGraphicsItem * child : chids)
                {
                    child->setData(5,item->data(0).toInt());
                    items.append(child);
                }
            }
        }
        if(k == 0)
        {
            break;
        }
    }
    double s = view->matrix().m11();
    QList<QGraphicsItem *> itemss = view->scene()->items();
    for (QList<QGraphicsItem*>::iterator it = itemss.begin(); it != itemss.end(); it++)
    {
        QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);

        if(node->data(0).toInt()<0)
        {
            view->scene()->removeItem(node);
        }
    }
    QPointF roof;
    roof.setX(view->itemad->mapToScene(view->itemad->rect()).value(2).x()-10/s);
    roof.setY(view->itemad->mapToScene(view->itemad->rect()).value(2).y()-10/s);
    for (QList<QGraphicsItem*>::iterator it = items.begin(); it != items.end(); it++)
    {
        QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);
        if(node->type() == 1)
        {
            MyGraphicsRecItem* item = qgraphicsitem_cast<MyGraphicsRecItem *>(node);
            MyGraphicsRecItem *tmp = new MyGraphicsRecItem();
            QPointF poss =item->pos();
            double t1 = (pressPos.x()-p1.x())/(view->itemad->rec.width());
            double t2 = (-p1.y()+pressPos.y())/(view->itemad->rec.height());
            double proportion = 1;
            if(t1>0&&t2>0)
            {
                proportion = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                proportion = fmax(t1,t2);
            }
            else
            {
                proportion = fmin(t1,t2);
            }
            tmp->setPos((poss-roof)*proportion+poss);
            tmp->setRect(-item->rect().width()*(1+proportion)/2,-item->rect().height()*(1+proportion)/2,item->rect().width()*(1+proportion),item->rect().height()*(1+proportion));
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            tmp->set_brush(item->angle,item->space);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 2)
        {
            MyGraphicsEllipseItem* item = qgraphicsitem_cast<MyGraphicsEllipseItem *>(node);
            MyGraphicsEllipseItem *tmp = new MyGraphicsEllipseItem();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t1 = (pressPos.x()-p1.x())/(view->itemad->rec.width());
            double t2 = -(p1.y()-pressPos.y())/(view->itemad->rec.height());
            double proportion = 1;
            if(t1>0&&t2>0)
            {
                proportion = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                proportion = fmax(t1,t2);
            }
            else
            {
                proportion = fmin(t1,t2);
            }

            tmp->setPos((poss-roof)*proportion+poss);
            tmp->setRect(-item->rect().width()*(1+proportion)/2,-item->rect().height()*(1+proportion)/2,item->rect().width()*(1+proportion),item->rect().height()*(1+proportion));
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->set_brush(item->angle,item->space);
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 3)
        {
            MyGraphicsCircleItem* item = qgraphicsitem_cast<MyGraphicsCircleItem *>(node);
            MyGraphicsCircleItem *tmp = new MyGraphicsCircleItem();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t1 = -(-pressPos.x()+p1.x())/(view->itemad->rec.width());
            double t2 = -(p1.y()-pressPos.y())/(view->itemad->rec.height());
            double proportion = 1;
            if(t1>0&&t2>0)
            {
                proportion = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                proportion = fmax(t1,t2);
            }
            else
            {
                proportion = fmin(t1,t2);
            }

            tmp->setPos((poss-roof)*proportion+poss);
            tmp->setRect(-item->rect().width()*(1+proportion)/2,-item->rect().height()*(1+proportion)/2,item->rect().width()*(1+proportion),item->rect().height()*(1+proportion));
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->set_brush(item->angle,item->space);
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 4)
        {
            MyGraphicsLineItem *item = qgraphicsitem_cast<MyGraphicsLineItem *>(node);
            QRectF rect = item->getRect();
            MyGraphicsLineItem *tmp = new MyGraphicsLineItem();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t1 = -(-pressPos.x()+p1.x())/(view->itemad->rec.width());
            double t2 = -(p1.y()-pressPos.y())/(view->itemad->rec.height());
            double proportion = 1;
            if(t1>0&&t2>0)
            {
                proportion = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                proportion = fmax(t1,t2);
            }
            else
            {
                proportion = fmin(t1,t2);
            }
            QPainterPath path1 = item->path();
            QPainterPath path2 ;
            tmp->setPos((poss-roof)*proportion+poss);
            QPointF offset = tmp->pos() - item->pos();
            for (int i = 0; i < path1.elementCount(); i++)
            {
                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(proportion)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
            }

            tmp->setPath(path2);
            tmp->setData(0,-1);
            tmp->set_brush(item->angle,item->space);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 5)
        {
            MyGraphicsPolygonItem *item = qgraphicsitem_cast<MyGraphicsPolygonItem *>(node);
            MyGraphicsPolygonItem *tmp = new MyGraphicsPolygonItem();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t1 = -(-pressPos.x()+p1.x())/(view->itemad->rec.width());
            double t2 = -(p1.y()-pressPos.y())/(view->itemad->rec.height());
            double proportion = 1;
            if(t1>0&&t2>0)
            {
                proportion = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                proportion = fmax(t1,t2);
            }
            else
            {
                proportion = fmin(t1,t2);
            }
            tmp->num = item->num;
            tmp->setPos((poss-roof)*proportion+poss);
            tmp->setRect(-item->rect().width()*(1+proportion)/2,-item->rect().height()*(1+proportion)/2,item->rect().width()*(1+proportion),item->rect().height()*(1+proportion));
            tmp->setDefault_Path();
            tmp->setData(0,-1);
            tmp->set_brush(item->angle,item->space);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 6)
        {
            MyGraphicsTextItem* item = qgraphicsitem_cast<MyGraphicsTextItem *>(node);
            MyGraphicsTextItem *tmp = new MyGraphicsTextItem();
            QPointF poss = item->pos();
            double t1 = -(-pressPos.x()+p1.x())/(view->itemad->rec.width());
            double t2 = -(p1.y()-pressPos.y())/(view->itemad->rec.height());
            double proportion = 1;
            if(t1>0&&t2>0)
            {
                proportion = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                proportion = fmax(t1,t2);
            }
            else
            {
                proportion = fmin(t1,t2);
            }
            QPainterPath path1 = item->path;
            QPainterPath path2 ;
            int k=0;
            QPointF c1,c2;
            tmp->setPos((poss-roof)*proportion+poss);

            QPointF offset = tmp->pos() - item->pos();   //用来计算path2的pos差值
            for (int i = 0; i < path1.elementCount(); i++)
            {

                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(proportion)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
                else if(element.isCurveTo())
                {

                    c1 = po2;
                    k++;
                    //path2.cubicTo(po2);
                }
                else
                {
                    if(k%3 == 1)
                    {

                        c2 = po2;
                        k++;
                    }
                    else if(k%3 == 2)
                    {
                        path2.cubicTo(c1,c2,po2);
                        k++;
                    }

                }
            }
            tmp->setRect(-(item->rect().width()*(1+proportion))/2,-(item->rect().height()*(1+proportion))/2,item->rect().width()*(1+proportion),item->rect().height()*(1+proportion));
            tmp->setPath(path2);
            tmp->setData(0,-1);
            tmp->set_brush(item->angle,item->space);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 7)
        {
            MyGraphicsCurveLineItem *item = qgraphicsitem_cast<MyGraphicsCurveLineItem *>(node);
            //QList<double> list = item->getRect();
            MyGraphicsCurveLineItem *tmp = new MyGraphicsCurveLineItem();
            QPointF poss = item->pos();
            double t1 = -(-pressPos.x()+p1.x())/(view->itemad->rec.width());
            double t2 = -(p1.y()-pressPos.y())/(view->itemad->rec.height());
            double proportion = 1;
            if(t1>0&&t2>0)
            {
                proportion = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                proportion = fmax(t1,t2);
            }
            else
            {
                proportion = fmin(t1,t2);
            }
            QPainterPath path1 = item->path();
            QPainterPath path2 ;
            int k=0;
            QPointF c1,c2;
            tmp->setPos((poss-roof)*proportion+poss);
            QPointF offset = tmp->pos() - item->pos();   //用来计算path2的pos差值
            for (int i = 0; i < path1.elementCount(); i++)
            {

                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(proportion)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
                else if(element.isCurveTo())
                {

                    c1 = po2;
                    k++;
                    //path2.cubicTo(po2);
                }
                else
                {
                    if(k%3 == 1)
                    {

                        c2 = po2;
                        k++;
                    }
                    else if(k%3 == 2)
                    {
                        path2.cubicTo(c1,c2,po2);
                        k++;
                    }

                }
            }

            tmp->setPath(path2);
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 8)
        {
            MyGraphicsPixMapItem* item = qgraphicsitem_cast<MyGraphicsPixMapItem *>(node);
            MyGraphicsPixMapItem *tmp = new MyGraphicsPixMapItem();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t1 = -(-pressPos.x()+p1.x())/(view->itemad->rec.width());
            double t2 = -(p1.y()-pressPos.y())/(view->itemad->rec.height());
            double proportion = 1;
            if(t1>0&&t2>0)
            {
                proportion = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                proportion = fmax(t1,t2);
            }
            else
            {
                proportion = fmin(t1,t2);
            }
            tmp->setPixmap(item->pixmap());
            tmp->setPos((poss-roof)*proportion+poss);
            double w = qAbs(item->rect().width()*(1+proportion));
            double h = qAbs(item->rect().height()*(1+proportion));
            if(item->rect().width()*(1+proportion)<0)
            {
                tmp->setPos((poss-roof)*proportion+poss-QPointF(w,h));
            }

            tmp->setRectF(QRect(0,-h,w,h));
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 9)
        {
            MyGraphicsCodeItem *item = qgraphicsitem_cast<MyGraphicsCodeItem *>(node);
            MyGraphicsCodeItem *tmp = new MyGraphicsCodeItem();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t1 = -(-pressPos.x()+p1.x())/(view->itemad->rec.width());
            double t2 = -(p1.y()-pressPos.y())/(view->itemad->rec.height());
            double proportion = 1;
            if(t1>0&&t2>0)
            {
                proportion = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                proportion = fmax(t1,t2);
            }
            else
            {
                proportion = fmin(t1,t2);
            }
            QPainterPath path1 = item->path;
            QPainterPath path2 ;
            tmp->setPos((poss-roof)*proportion+poss);
            QPointF offset = tmp->pos() - item->pos();
            for (int i = 0; i < path1.elementCount(); i++)
            {
                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(proportion)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
            }
            tmp->setRect(-(item->rect().width()*(1+proportion))/2,-(item->rect().height()*(1+proportion))/2,item->rect().width()*(1+proportion),item->rect().height()*(1+proportion));

            tmp->path = (path2);
            tmp->setData(0,-1);
            tmp->text = item->text;
            tmp->codetype = item->codetype;
            tmp->set_brush(item->angle,item->space);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
    }
    view->scene()->update();
}

void ItemChangeHandle::midbuttom_set(QPointF p1,QPointF pressPos)
{
    QList<QGraphicsItem*> items = view->scene()->selectedItems();
    for(QGraphicsItem* item:items)
    {
        if(item->data(15).toInt()==1)
        {
            items.removeOne(item);
        }
    }
    while(1)
    {
        int k=0;
        for(QGraphicsItem * item : items)
        {
            if(item->type() == 10)
            {
                k=1;
                QList<QGraphicsItem*> chids = qgraphicsitem_cast<MyGraphicsGroupItem *>(item)->childItems();
                items.removeOne(item);
                for(QGraphicsItem * child : chids)
                {
                    child->setData(5,item->data(0).toInt());
                    items.append(child);
                }
            }
        }
        if(k == 0)
        {
            break;
        }
    }
    double s = view->matrix().m11();
    QList<QGraphicsItem *> itemss = view->scene()->items();
    for (QList<QGraphicsItem*>::iterator it = itemss.begin(); it != itemss.end(); it++)
    {
        QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);

        if(node->data(0).toInt()<0)
        {
            view->scene()->removeItem(node);
        }
    }
    QPointF roof;
    roof.setX(view->itemad->mapToScene(view->itemad->rect()).value(2).x()-10/s);
    roof.setY(view->itemad->mapToScene(view->itemad->rect()).value(2).y()-10/s);
    for (QList<QGraphicsItem*>::iterator it = items.begin(); it != items.end(); it++)
    {
        QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);
        if(node->type() == 1)
        {
            MyGraphicsRecItem* item = qgraphicsitem_cast<MyGraphicsRecItem *>(node);
            QPointF p2 = item->mapToScene(item->rect()).value(0);
            QPointF p3 = item->mapToScene(item->rect()).value(2);
            MyGraphicsRecItem *tmp = new MyGraphicsRecItem();
            QPointF poss =item->pos();
            double t2 = -(p1.y()-pressPos.y())/(view->itemad->rec.height());
            double proportion = t2;
            tmp->setPos(poss.x(),((poss-roof)*proportion+poss).y());
            tmp->setRect(-item->rect().width()/2,-item->rect().height()*(1+proportion)/2,item->rect().width(),item->rect().height()*(1+proportion));
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            tmp->set_brush(item->angle,item->space);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 2)
        {
            MyGraphicsEllipseItem* item = qgraphicsitem_cast<MyGraphicsEllipseItem *>(node);
            QPointF p2 = item->mapToScene(item->rect()).value(0);
            QPointF p3 = item->mapToScene(item->rect()).value(2);
            MyGraphicsEllipseItem *tmp = new MyGraphicsEllipseItem();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t2 = -(p1.y()-pressPos.y())/(view->itemad->rec.height());
            double proportion = t2;

            tmp->setPos(poss.x(),((poss-roof)*proportion+poss).y());
            tmp->setRect(-item->rect().width()/2,-item->rect().height()*(1+proportion)/2,item->rect().width(),item->rect().height()*(1+proportion));
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            tmp->set_brush(item->angle,item->space);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 3)
        {
            MyGraphicsCircleItem* item = qgraphicsitem_cast<MyGraphicsCircleItem *>(node);
            MyGraphicsCircleItem *tmp = new MyGraphicsCircleItem();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t2 = -(p1.y()-pressPos.y())/(view->itemad->rec.height());
            double proportion = t2;
            tmp->setPos(poss.x(),((poss-roof)*proportion+poss).y());
            tmp->setRect(-item->rect().width()/2,-item->rect().height()*(1+proportion)/2,item->rect().width(),item->rect().height()*(1+proportion));
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->set_brush(item->angle,item->space);
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 4)
        {
            MyGraphicsLineItem *item = qgraphicsitem_cast<MyGraphicsLineItem *>(node);
            QRectF rect = item->getRect();
            QPointF p2 (rect.x(),rect.y());
            QPointF p3 (rect.x()+rect.width(),rect.y()+rect.height());
            MyGraphicsLineItem *tmp = new MyGraphicsLineItem();
            double t2 = -(p1.y()-pressPos.y())/(view->itemad->rec.height());
            double proportion = t2;
            QPainterPath path1 = item->path();
            QPainterPath path2 ;
            QPointF poss = item->pos();
            tmp->setPos(poss.x(),((poss-roof)*proportion+poss).y());
            QPointF offset = tmp->pos() - item->pos();

            for (int i = 0; i < path1.elementCount(); i++)
            {
                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(proportion)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                po2.setX(item->mapFromScene(po).x());
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
            }

            tmp->setPath(path2);
            tmp->setData(0,-1);
            tmp->set_brush(item->angle,item->space);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 5)
        {
            MyGraphicsPolygonItem *item = qgraphicsitem_cast<MyGraphicsPolygonItem *>(node);
            MyGraphicsPolygonItem *tmp = new MyGraphicsPolygonItem();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t2 = -(p1.y()-pressPos.y())/(view->itemad->rec.height());
            double proportion = t2;
            tmp->num = item->num;
            tmp->setPos(poss.x(),((poss-roof)*proportion+poss).y());
            tmp->setRect(-item->rect().width()/2,-item->rect().height()*(1+proportion)/2,item->rect().width(),item->rect().height()*(1+proportion));
            tmp->setData(0,-1);
            tmp->setDefault_Path();
            tmp->setData(0,-1);
            tmp->set_brush(item->angle,item->space);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 6)
        {
            MyGraphicsTextItem* item = qgraphicsitem_cast<MyGraphicsTextItem *>(node);
            MyGraphicsTextItem *tmp = new MyGraphicsTextItem();
            QPointF poss = item->pos();
            double t2 = -(p1.y()-pressPos.y())/(view->itemad->rec.height());
            double proportion = t2;
            QPainterPath path1 = item->path;
            QPainterPath path2 ;
            int k=0;
            QPointF c1,c2;
            tmp->setPos(poss.x(),((poss-roof)*proportion+poss).y());
            QPointF offset = tmp->pos() - item->pos();   //用来计算path2的pos差值
            for (int i = 0; i < path1.elementCount(); i++)
            {

                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(proportion)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                po2.setX(item->mapFromScene(po).x());
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
                else if(element.isCurveTo())
                {

                    c1 = po2;
                    k++;
                    //path2.cubicTo(po2);
                }
                else
                {
                    if(k%3 == 1)
                    {

                        c2 = po2;
                        k++;
                    }
                    else if(k%3 == 2)
                    {
                        path2.cubicTo(c1,c2,po2);
                        k++;
                    }

                }
            }
            tmp->setRect(-(item->rect().width())/2,-(item->rect().height()*(1+proportion))/2,item->rect().width(),item->rect().height()*(1+proportion));
            tmp->setPath(path2);
            tmp->setData(0,-1);
            tmp->set_brush(item->angle,item->space);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 7)
        {
            MyGraphicsCurveLineItem* item = qgraphicsitem_cast<MyGraphicsCurveLineItem *>(node);
            MyGraphicsCurveLineItem *tmp = new MyGraphicsCurveLineItem();
            QPointF poss = item->pos();
            double t2 = -(p1.y()-pressPos.y())/(view->itemad->rec.height());
            double proportion = t2;
            QPainterPath path1 = item->path();
            QPainterPath path2 ;
            int k=0;
            QPointF c1,c2;
            tmp->setPos(poss.x(),((poss-roof)*proportion+poss).y());
            QPointF offset = tmp->pos() - item->pos();   //用来计算path2的pos差值
            for (int i = 0; i < path1.elementCount(); i++)
            {

                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(proportion)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                po2.setX(item->mapFromScene(po).x());
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
                else if(element.isCurveTo())
                {

                    c1 = po2;
                    k++;
                    //path2.cubicTo(po2);
                }
                else
                {
                    if(k%3 == 1)
                    {

                        c2 = po2;
                        k++;
                    }
                    else if(k%3 == 2)
                    {
                        path2.cubicTo(c1,c2,po2);
                        k++;
                    }

                }
            }
            tmp->setPath(path2);
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 8)
        {
            MyGraphicsPixMapItem* item = qgraphicsitem_cast<MyGraphicsPixMapItem *>(node);
            MyGraphicsPixMapItem *tmp = new MyGraphicsPixMapItem();
            QPointF poss = item->pos();
            double t2 = -(p1.y()-pressPos.y())/(view->itemad->rec.height());
            double proportion = t2;
            tmp->setPixmap(item->pixmap());
            tmp->setPos( poss.x(),((poss-roof)*proportion+poss).y());
            double w = qAbs(item->rect().width());
            double h = qAbs(item->rect().height()*(1+proportion));
            if(item->rect().height()*(1+proportion)<0)
            {
                tmp->setPos(tmp->pos()-QPointF(0,h));
            }

            tmp->setRectF(QRect(0,-h,w,h));
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 9)
        {
            MyGraphicsCodeItem *item = qgraphicsitem_cast<MyGraphicsCodeItem *>(node);
            QPointF p2 = item->mapToScene(item->rect()).value(0);
            QPointF p3 = item->mapToScene(item->rect()).value(2);
            MyGraphicsCodeItem *tmp = new MyGraphicsCodeItem();
            double t2 = -(p1.y()-pressPos.y())/(view->itemad->rec.height());
            double proportion = t2;
            QPainterPath path1 = item->path;
            QPainterPath path2 ;
            QPointF poss = item->pos();
            tmp->setPos(poss.x(),((poss-roof)*proportion+poss).y());
            QPointF offset = tmp->pos() - item->pos();

            for (int i = 0; i < path1.elementCount(); i++)
            {
                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(proportion)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                po2.setX(item->mapFromScene(po).x());
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
            }
            tmp->setRect(-(item->rect().width())/2,-(item->rect().height()*(1+proportion))/2,item->rect().width(),item->rect().height()*(1+proportion));

            tmp->path = (path2);
            tmp->setData(0,-1);
            tmp->text = item->text;
            tmp->codetype = item->codetype;
            tmp->set_brush(item->angle,item->space);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
    }
    view->scene()->update();
}

void ItemChangeHandle::rightbuttom_set(QPointF p1,QPointF pressPos)
{
    QList<QGraphicsItem*> items = view->scene()->selectedItems();
    for(QGraphicsItem* item:items)
    {
        if(item->data(15).toInt()==1)
        {
            items.removeOne(item);
        }
    }
    while(1)
    {
        int k=0;
        for(QGraphicsItem * item : items)
        {
            if(item->type() == 10)
            {
                k=1;
                QList<QGraphicsItem*> chids = qgraphicsitem_cast<MyGraphicsGroupItem *>(item)->childItems();
                items.removeOne(item);
                for(QGraphicsItem * child : chids)
                {
                    child->setData(5,item->data(0).toInt());
                    items.append(child);
                }
            }
        }
        if(k == 0)
        {
            break;
        }
    }
    double s = view->matrix().m11();
    QList<QGraphicsItem *> itemss = view->scene()->items();
    for (QList<QGraphicsItem*>::iterator it = itemss.begin(); it != itemss.end(); it++)
    {
        QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);

        if(node->data(0).toInt()<0)
        {
            view->scene()->removeItem(node);
        }
    }
    QPointF roof;
    roof.setX(view->itemad->mapToScene(view->itemad->rect()).value(3).x()+10/s);
    roof.setY(view->itemad->mapToScene(view->itemad->rect()).value(3).y()-10/s);
    for (QList<QGraphicsItem*>::iterator it = items.begin(); it != items.end(); it++)
    {
        QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);
        if(node->type() == 1)
        {
            MyGraphicsRecItem* item = qgraphicsitem_cast<MyGraphicsRecItem *>(node);
            QPointF p2 = item->mapToScene(item->rect()).value(0);
            QPointF p3 = item->mapToScene(item->rect()).value(2);
            MyGraphicsRecItem *tmp = new MyGraphicsRecItem();
            QPointF poss =item->pos();
            double t1 = -(pressPos.x()-p1.x())/(view->itemad->rec.width());
            double t2 = -(p1.y()-pressPos.y())/(view->itemad->rec.height());
            double proportion = 1;
            if(t1>0&&t2>0)
            {
                proportion = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                proportion = fmax(t1,t2);
            }
            else
            {
                proportion = fmin(t1,t2);
            }
            tmp->setPos((poss-roof)*proportion+poss);
            tmp->setRect(-item->rect().width()*(1+proportion)/2,-item->rect().height()*(1+proportion)/2,item->rect().width()*(1+proportion),item->rect().height()*(1+proportion));
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            tmp->set_brush(item->angle,item->space);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 2)
        {
            MyGraphicsEllipseItem* item = qgraphicsitem_cast<MyGraphicsEllipseItem *>(node);
            QPointF p2 = item->mapToScene(item->rect()).value(0);
            QPointF p3 = item->mapToScene(item->rect()).value(2);
            MyGraphicsEllipseItem *tmp = new MyGraphicsEllipseItem();
            double w = p3.x()-p2.x(),h = p3.y()-p2.y();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t1 = -(pressPos.x()-p1.x())/(view->itemad->rec.width());
            double t2 = -(p1.y()-pressPos.y())/(view->itemad->rec.height());
            double proportion = 1;
            if(t1>0&&t2>0)
            {
                proportion = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                proportion = fmax(t1,t2);
            }
            else
            {
                proportion = fmin(t1,t2);
            }

            tmp->setPos((poss-roof)*proportion+poss);
            tmp->setRect(-item->rect().width()*(1+proportion)/2,-item->rect().height()*(1+proportion)/2,item->rect().width()*(1+proportion),item->rect().height()*(1+proportion));
            tmp->setData(0,-1);
            tmp->set_brush(item->angle,item->space);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 3)
        {
            MyGraphicsCircleItem* item = qgraphicsitem_cast<MyGraphicsCircleItem *>(node);
            QPointF p2 = item->mapToScene(item->rect()).value(0);
            QPointF p3 = item->mapToScene(item->rect()).value(2);
            MyGraphicsCircleItem *tmp = new MyGraphicsCircleItem();
            double w = p3.x()-p2.x(),h = p3.y()-p2.y();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t1 = -(pressPos.x()-p1.x())/(view->itemad->rec.width());
            double t2 = -(p1.y()-pressPos.y())/(view->itemad->rec.height());
            double proportion = 1;
            if(t1>0&&t2>0)
            {
                proportion = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                proportion = fmax(t1,t2);
            }
            else
            {
                proportion = fmin(t1,t2);
            }

            tmp->setPos((poss-roof)*proportion+poss);
            tmp->setRect(-item->rect().width()*(1+proportion)/2,-item->rect().height()*(1+proportion)/2,item->rect().width()*(1+proportion),item->rect().height()*(1+proportion));
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->set_brush(item->angle,item->space);
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 4)
        {
            MyGraphicsLineItem *item = qgraphicsitem_cast<MyGraphicsLineItem *>(node);
            QRectF rect = item->getRect();
            QPointF p2 (rect.x(),rect.y());
            QPointF p3 (rect.x()+rect.width(),rect.y()+rect.height());
            MyGraphicsLineItem *tmp = new MyGraphicsLineItem();
            double w = p3.x()-p2.x(),h = p3.y()-p2.y();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t1 = -(pressPos.x()-p1.x())/(view->itemad->rec.width());
            double t2 = -(p1.y()-pressPos.y())/(view->itemad->rec.height());
            double proportion = 1;
            if(t1>0&&t2>0)
            {
                proportion = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                proportion = fmax(t1,t2);
            }
            else
            {
                proportion = fmin(t1,t2);
            }
            QPainterPath path1 = item->path();
            QPainterPath path2 ;
            tmp->setPos((poss-roof)*proportion+poss);
            QPointF offset = tmp->pos() - item->pos();
            for (int i = 0; i < path1.elementCount(); i++)
            {
                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(proportion)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
            }

            tmp->setPath(path2);
            tmp->setData(0,-1);
            tmp->set_brush(item->angle,item->space);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 5)
        {
            MyGraphicsPolygonItem *item = qgraphicsitem_cast<MyGraphicsPolygonItem *>(node);
            QRectF rect = item->getRect();
            QPointF p2 (rect.x(),rect.y());
            QPointF p3 (rect.x()+rect.width(),rect.y()+rect.height());
            MyGraphicsPolygonItem *tmp = new MyGraphicsPolygonItem();
            double w = p3.x()-p2.x(),h = p3.y()-p2.y();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t1 = -(pressPos.x()-p1.x())/(view->itemad->rec.width());
            double t2 = -(p1.y()-pressPos.y())/(view->itemad->rec.height());
            double proportion = 1;
            if(t1>0&&t2>0)
            {
                proportion = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                proportion = fmax(t1,t2);
            }
            else
            {
                proportion = fmin(t1,t2);
            }
            tmp->num = item->num;
            tmp->setPos((poss-roof)*proportion+poss);
            tmp->setRect(-item->rect().width()*(1+proportion)/2,-item->rect().height()*(1+proportion)/2,item->rect().width()*(1+proportion),item->rect().height()*(1+proportion));
            tmp->setDefault_Path();
            tmp->setData(0,-1);
            tmp->set_brush(item->angle,item->space);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 6)
        {
            MyGraphicsTextItem* item = qgraphicsitem_cast<MyGraphicsTextItem *>(node);
            QPointF p2 = item->mapToScene(item->rect()).value(0);
            QPointF p3 = item->mapToScene(item->rect()).value(2);
            MyGraphicsTextItem *tmp = new MyGraphicsTextItem();
            double w = p3.x()-p2.x(),h = p3.y()-p2.y();
            QPointF poss = item->pos();
            double t1 = -(pressPos.x()-p1.x())/(view->itemad->rec.width());
            double t2 = -(p1.y()-pressPos.y())/(view->itemad->rec.height());
            double proportion = 1;
            if(t1>0&&t2>0)
            {
                proportion = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                proportion = fmax(t1,t2);
            }
            else
            {
                proportion = fmin(t1,t2);
            }
            QPainterPath path1 = item->path;
            QPainterPath path2 ;
            int k=0;
            QPointF c1,c2;
            tmp->setPos((poss-roof)*proportion+poss);
            QPointF offset = tmp->pos() - item->pos();   //用来计算path2的pos差值
            for (int i = 0; i < path1.elementCount(); i++)
            {

                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(proportion)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
                else if(element.isCurveTo())
                {

                    c1 = po2;
                    k++;
                    //path2.cubicTo(po2);
                }
                else
                {
                    if(k%3 == 1)
                    {

                        c2 = po2;
                        k++;
                    }
                    else if(k%3 == 2)
                    {
                        path2.cubicTo(c1,c2,po2);
                        k++;
                    }

                }
            }
            tmp->setRect(-(item->rect().width()*(1+proportion))/2,-(item->rect().height()*(1+proportion))/2,item->rect().width()*(1+proportion),item->rect().height()*(1+proportion));
            tmp->setPath(path2);
            tmp->setData(0,-1);
            tmp->set_brush(item->angle,item->space);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 7)
        {
            MyGraphicsCurveLineItem *item = qgraphicsitem_cast<MyGraphicsCurveLineItem *>(node);
            //QList<double> list = item->getRect();
            MyGraphicsCurveLineItem *tmp = new MyGraphicsCurveLineItem();
            QPointF poss = item->pos();
            double t1 = -(pressPos.x()-p1.x())/(view->itemad->rec.width());
            double t2 = -(p1.y()-pressPos.y())/(view->itemad->rec.height());
            double proportion = 1;
            if(t1>0&&t2>0)
            {
                proportion = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                proportion = fmax(t1,t2);
            }
            else
            {
                proportion = fmin(t1,t2);
            }
            QPainterPath path1 = item->path();
            QPainterPath path2 ;
            int k=0;
            QPointF c1,c2;
            tmp->setPos((poss-roof)*proportion+poss);
            QPointF offset = tmp->pos() - item->pos();   //用来计算path2的pos差值
            for (int i = 0; i < path1.elementCount(); i++)
            {

                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(proportion)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
                else if(element.isCurveTo())
                {

                    c1 = po2;
                    k++;
                    //path2.cubicTo(po2);
                }
                else
                {
                    if(k%3 == 1)
                    {

                        c2 = po2;
                        k++;
                    }
                    else if(k%3 == 2)
                    {
                        path2.cubicTo(c1,c2,po2);
                        k++;
                    }

                }
            }

            tmp->setPath(path2);
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 8)
        {
            MyGraphicsPixMapItem* item = qgraphicsitem_cast<MyGraphicsPixMapItem *>(node);
            MyGraphicsPixMapItem *tmp = new MyGraphicsPixMapItem();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t1 = -(pressPos.x()-p1.x())/(view->itemad->rec.width());
            double t2 = -(p1.y()-pressPos.y())/(view->itemad->rec.height());
            double proportion = 1;
            if(t1>0&&t2>0)
            {
                proportion = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                proportion = fmax(t1,t2);
            }
            else
            {
                proportion = fmin(t1,t2);
            }
            tmp->setPixmap(item->pixmap());
            tmp->setPos((poss-roof)*proportion+poss);
            double w = qAbs(item->rect().width()*(1+proportion));
            double h = qAbs(item->rect().height()*(1+proportion));
            if(item->rect().width()*(1+proportion)<0)
            {
                tmp->setPos((poss-roof)*proportion+poss-QPointF(w,h));
            }

            tmp->setRectF(QRect(0,-h,w,h));
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 9)
        {
            MyGraphicsCodeItem *item = qgraphicsitem_cast<MyGraphicsCodeItem *>(node);
            QPointF p2 = item->mapToScene(item->rect()).value(0);
            QPointF p3 = item->mapToScene(item->rect()).value(2);
            MyGraphicsCodeItem *tmp = new MyGraphicsCodeItem();
            double w = p3.x()-p2.x(),h = p3.y()-p2.y();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t1 = -(pressPos.x()-p1.x())/(view->itemad->rec.width());
            double t2 = -(p1.y()-pressPos.y())/(view->itemad->rec.height());
            double proportion = 1;
            if(t1>0&&t2>0)
            {
                proportion = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                proportion = fmax(t1,t2);
            }
            else
            {
                proportion = fmin(t1,t2);
            }
            QPainterPath path1 = item->path;
            QPainterPath path2 ;
            tmp->setPos((poss-roof)*proportion+poss);
            QPointF offset = tmp->pos() - item->pos();
            for (int i = 0; i < path1.elementCount(); i++)
            {
                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(proportion)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
            }
            tmp->setRect(-(item->rect().width()*(1+proportion))/2,-(item->rect().height()*(1+proportion))/2,item->rect().width()*(1+proportion),item->rect().height()*(1+proportion));

            tmp->path = (path2);
            tmp->setData(0,-1);
            tmp->text = item->text;
            tmp->codetype = item->codetype;
            tmp->set_brush(item->angle,item->space);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
    }
    view->scene()->update();
}

void ItemChangeHandle::leftmid_set(QPointF p1,QPointF pressPos)
{
    QList<QGraphicsItem*> items = view->scene()->selectedItems();
    for(QGraphicsItem* item:items)
    {
        if(item->data(15).toInt()==1)
        {
            items.removeOne(item);
        }
    }
    while(1)
    {
        int k=0;
        for(QGraphicsItem * item : items)
        {
            if(item->type() == 10)
            {
                k=1;
                QList<QGraphicsItem*> chids = qgraphicsitem_cast<MyGraphicsGroupItem *>(item)->childItems();
                items.removeOne(item);
                for(QGraphicsItem * child : chids)
                {
                    child->setData(5,item->data(0).toInt());
                    items.append(child);
                }
            }
        }
        if(k == 0)
        {
            break;
        }
    }
    double s = view->matrix().m11();
    QList<QGraphicsItem *> itemss = view->scene()->items();
    for (QList<QGraphicsItem*>::iterator it = itemss.begin(); it != itemss.end(); it++)
    {
        QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);

        if(node->data(0).toInt()<0)
        {
            view->scene()->removeItem(node);
        }
    }
    QPointF roof;
    roof.setX(view->itemad->mapToScene(view->itemad->rect()).value(1).x()-10/s);
    roof.setY(view->itemad->mapToScene(view->itemad->rect()).value(1).y()+10/s);
    for (QList<QGraphicsItem*>::iterator it = items.begin(); it != items.end(); it++)
    {
        QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);
        if(node->type() == 1)
        {
            MyGraphicsRecItem* item = qgraphicsitem_cast<MyGraphicsRecItem *>(node);
            MyGraphicsRecItem *tmp = new MyGraphicsRecItem();
            QPointF poss=item->pos();
            double t2 = -(p1.x()-pressPos.x())/(view->itemad->rec.width());
            double proportion = t2;
            tmp->setPos(((poss-roof)*proportion+poss).x(),poss.y());
            tmp->setRect(-item->rect().width()*(1+proportion)/2,-item->rect().height()/2,item->rect().width()*(1+proportion),item->rect().height());
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            tmp->set_brush(item->angle,item->space);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 2)
        {
            MyGraphicsEllipseItem* item = qgraphicsitem_cast<MyGraphicsEllipseItem *>(node);
            QPointF p2 = item->mapToScene(item->rect()).value(0);
            QPointF p3 = item->mapToScene(item->rect()).value(2);
            MyGraphicsEllipseItem *tmp = new MyGraphicsEllipseItem();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t2 = -(p1.x()-pressPos.x())/(view->itemad->rec.width());
            double proportion = t2;
            tmp->setPos(((poss-roof)*proportion+poss).x(),poss.y());
            tmp->setRect(-item->rect().width()*(1+proportion)/2,-item->rect().height()/2,item->rect().width()*(1+proportion),item->rect().height());
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            tmp->set_brush(item->angle,item->space);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 3)
        {
            MyGraphicsCircleItem* item = qgraphicsitem_cast<MyGraphicsCircleItem *>(node);
            MyGraphicsCircleItem *tmp = new MyGraphicsCircleItem();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t2 = -(p1.x()-pressPos.x())/(view->itemad->rec.width());
            double proportion = t2;
            tmp->setPos(((poss-roof)*proportion+poss).x(),poss.y());
            tmp->setRect(-item->rect().width()*(1+proportion)/2,-item->rect().height()/2,item->rect().width()*(1+proportion),item->rect().height());
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->set_brush(item->angle,item->space);
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 4)
        {
            MyGraphicsLineItem *item = qgraphicsitem_cast<MyGraphicsLineItem *>(node);
            QRectF rect = item->getRect();
            QPointF p2 (rect.x(),rect.y());
            QPointF p3 (rect.x()+rect.width(),rect.y()+rect.height());
            MyGraphicsLineItem *tmp = new MyGraphicsLineItem();
            double t2 = -(p1.x()-pressPos.x())/(view->itemad->rec.width());
            double proportion = t2;
            QPainterPath path1 = item->path();
            QPainterPath path2 ;
            QPointF poss = item->pos();
            tmp->setPos(((poss-roof)*proportion+poss).x(),poss.y());
            QPointF offset = tmp->pos() - item->pos();

            for (int i = 0; i < path1.elementCount(); i++)
            {
                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(proportion)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                po2.setY(item->mapFromScene(po).y());
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
            }
            tmp->setPath(path2);
            tmp->setData(0,-1);
            tmp->set_brush(item->angle,item->space);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 5)
        {
            MyGraphicsPolygonItem *item = qgraphicsitem_cast<MyGraphicsPolygonItem *>(node);
            MyGraphicsPolygonItem *tmp = new MyGraphicsPolygonItem();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t2 = -(p1.x()-pressPos.x())/(view->itemad->rec.width());
            double proportion = t2;
            tmp->num = item->num;
            tmp->setPos(((poss-roof)*proportion+poss).x(),poss.y());
            tmp->setRect(-item->rect().width()*(1+proportion)/2,-item->rect().height()/2,item->rect().width()*(1+proportion),item->rect().height());
            tmp->setData(0,-1);
            tmp->setDefault_Path();
            tmp->setData(0,-1);
            tmp->set_brush(item->angle,item->space);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 6)
        {
            MyGraphicsTextItem* item = qgraphicsitem_cast<MyGraphicsTextItem *>(node);
            MyGraphicsTextItem *tmp = new MyGraphicsTextItem();
            QPointF poss = item->pos();
            double t2 = -(p1.x()-pressPos.x())/(view->itemad->rec.width());
            double proportion = t2;
            QPainterPath path1 = item->path;
            QPainterPath path2 ;
            int k=0;
            QPointF c1,c2;
            tmp->setPos(((poss-roof)*proportion+poss).x(),poss.y());
            QPointF offset = tmp->pos() - item->pos();   //用来计算path2的pos差值
            for (int i = 0; i < path1.elementCount(); i++)
            {

                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(proportion)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                po2.setY(item->mapFromScene(po).y());
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
                else if(element.isCurveTo())
                {

                    c1 = po2;
                    k++;
                    //path2.cubicTo(po2);
                }
                else
                {
                    if(k%3 == 1)
                    {

                        c2 = po2;
                        k++;
                    }
                    else if(k%3 == 2)
                    {
                        path2.cubicTo(c1,c2,po2);
                        k++;
                    }

                }
            }
            tmp->setRect(-item->rect().width()*(1+proportion)/2,-item->rect().height()/2,item->rect().width()*(1+proportion),item->rect().height());
            tmp->setPath(path2);
            tmp->setData(0,-1);
            tmp->set_brush(item->angle,item->space);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 7)
        {
            MyGraphicsCurveLineItem* item = qgraphicsitem_cast<MyGraphicsCurveLineItem *>(node);
            MyGraphicsCurveLineItem *tmp = new MyGraphicsCurveLineItem();
            QPointF poss = item->pos();
            double t2 = -(p1.x()-pressPos.x())/(view->itemad->rec.width());
            double proportion = t2;
            QPainterPath path1 = item->path();
            QPainterPath path2 ;
            int k=0;
            QPointF c1,c2;
            tmp->setPos(((poss-roof)*proportion+poss).x(),poss.y());
            QPointF offset = tmp->pos() - item->pos();   //用来计算path2的pos差值
            for (int i = 0; i < path1.elementCount(); i++)
            {

                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(proportion)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                po2.setY(item->mapFromScene(po).y());
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
                else if(element.isCurveTo())
                {

                    c1 = po2;
                    k++;
                    //path2.cubicTo(po2);
                }
                else
                {
                    if(k%3 == 1)
                    {

                        c2 = po2;
                        k++;
                    }
                    else if(k%3 == 2)
                    {
                        path2.cubicTo(c1,c2,po2);
                        k++;
                    }

                }
            }
            tmp->setPath(path2);
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 8)
        {
            MyGraphicsPixMapItem* item = qgraphicsitem_cast<MyGraphicsPixMapItem *>(node);
            MyGraphicsPixMapItem *tmp = new MyGraphicsPixMapItem();
            QPointF poss = item->pos();
            double t2 = -(p1.x()-pressPos.x())/(view->itemad->rec.width());
            double proportion = t2;
            tmp->setPixmap(item->pixmap());
            tmp->setPos(((poss-roof)*proportion+poss).x(),poss.y());
            double w = qAbs(item->rect().width()*(1+proportion));
            double h = qAbs(item->rect().height());
            if(item->rect().width()*(1+proportion)<0)
            {
                tmp->setPos(tmp->pos()-QPointF(w,0));
            }

            tmp->setRectF(QRect(0,-h,w,h));
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 9)
        {
            MyGraphicsCodeItem *item = qgraphicsitem_cast<MyGraphicsCodeItem *>(node);
            QPointF p2 = item->mapToScene(item->rect()).value(0);
            QPointF p3 = item->mapToScene(item->rect()).value(2);
            MyGraphicsCodeItem *tmp = new MyGraphicsCodeItem();
            double t2 = -(p1.x()-pressPos.x())/(view->itemad->rec.width());
            double proportion = t2;
            QPainterPath path1 = item->path;
            QPainterPath path2 ;
            QPointF poss = item->pos();
            tmp->setPos(((poss-roof)*proportion+poss).x(),poss.y());
            QPointF offset = tmp->pos() - item->pos();

            for (int i = 0; i < path1.elementCount(); i++)
            {
                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(proportion)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                po2.setY(item->mapFromScene(po).y());
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
            }
            tmp->setRect(-item->rect().width()*(1+proportion)/2,-item->rect().height()/2,item->rect().width()*(1+proportion),item->rect().height());

            tmp->path = (path2);
            tmp->setData(0,-1);
            tmp->text = item->text;
            tmp->codetype = item->codetype;
            tmp->set_brush(item->angle,item->space);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
    }
    view->scene()->update();
}

void ItemChangeHandle::rightmid_set(QPointF p1,QPointF pressPos)
{
    QList<QGraphicsItem*> items = view->scene()->selectedItems();
    for(QGraphicsItem* item:items)
    {
        if(item->data(15).toInt()==1)
        {
            items.removeOne(item);
        }
    }
    while(1)
    {
        int k=0;
        for(QGraphicsItem * item : items)
        {
            if(item->type() == 10)
            {
                k=1;
                QList<QGraphicsItem*> chids = qgraphicsitem_cast<MyGraphicsGroupItem *>(item)->childItems();
                items.removeOne(item);
                for(QGraphicsItem * child : chids)
                {
                    child->setData(5,item->data(0).toInt());
                    items.append(child);
                }
            }
        }
        if(k == 0)
        {
            break;
        }
    }
    double s = view->matrix().m11();
    QList<QGraphicsItem *> itemss = view->scene()->items();
    for (QList<QGraphicsItem*>::iterator it = itemss.begin(); it != itemss.end(); it++)
    {
        QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);

        if(node->data(0).toInt()<0)
        {
            view->scene()->removeItem(node);
        }
    }
    QPointF roof;
    roof.setX(view->itemad->mapToScene(view->itemad->rect()).value(0).x()+10/s);
    roof.setY(view->itemad->mapToScene(view->itemad->rect()).value(0).y()+10/s);
    for (QList<QGraphicsItem*>::iterator it = items.begin(); it != items.end(); it++)
    {
        QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);
        if(node->type() == 1)
        {
            MyGraphicsRecItem* item = qgraphicsitem_cast<MyGraphicsRecItem *>(node);
            MyGraphicsRecItem *tmp = new MyGraphicsRecItem();
            QPointF poss =item->pos();
            double t2 = (p1.x()-pressPos.x())/(view->itemad->rec.width());
            double proportion = t2;
            tmp->setPos(((poss-roof)*proportion+poss).x(),poss.y());
            tmp->setRect(-item->rect().width()*(1+proportion)/2,-item->rect().height()/2,item->rect().width()*(1+proportion),item->rect().height());
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            tmp->set_brush(item->angle,item->space);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 2)
        {
            MyGraphicsEllipseItem* item = qgraphicsitem_cast<MyGraphicsEllipseItem *>(node);
            QPointF p2 = item->mapToScene(item->rect()).value(0);
            QPointF p3 = item->mapToScene(item->rect()).value(2);
            MyGraphicsEllipseItem *tmp = new MyGraphicsEllipseItem();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t2 = (p1.x()-pressPos.x())/(view->itemad->rec.width());
            double proportion = t2;
            tmp->setPos(((poss-roof)*proportion+poss).x(),poss.y());
            tmp->setRect(-item->rect().width()*(1+proportion)/2,-item->rect().height()/2,item->rect().width()*(1+proportion),item->rect().height());
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            tmp->set_brush(item->angle,item->space);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 3)
        {
            MyGraphicsCircleItem* item = qgraphicsitem_cast<MyGraphicsCircleItem *>(node);
            MyGraphicsCircleItem *tmp = new MyGraphicsCircleItem();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t2 = (p1.x()-pressPos.x())/(view->itemad->rec.width());
            double proportion = t2;
            tmp->setPos(((poss-roof)*proportion+poss).x(),poss.y());
            tmp->setRect(-item->rect().width()*(1+proportion)/2,-item->rect().height()/2,item->rect().width()*(1+proportion),item->rect().height());
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->set_brush(item->angle,item->space);
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 4)
        {
            MyGraphicsLineItem *item = qgraphicsitem_cast<MyGraphicsLineItem *>(node);
            QRectF rect = item->getRect();
            QPointF p2 (rect.x(),rect.y());
            QPointF p3 (rect.x()+rect.width(),rect.y()+rect.height());
            MyGraphicsLineItem *tmp = new MyGraphicsLineItem();
            double t2 = (p1.x()-pressPos.x())/(view->itemad->rec.width());
            double proportion = t2;
            QPainterPath path1 = item->path();
            QPainterPath path2 ;
            QPointF poss = item->pos();
            tmp->setPos(((poss-roof)*proportion+poss).x(),poss.y());
            QPointF offset = tmp->pos() - item->pos();

            for (int i = 0; i < path1.elementCount(); i++)
            {
                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(proportion)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                po2.setY(item->mapFromScene(po).y());
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
            }
            tmp->setPath(path2);
            tmp->setData(0,-1);
            tmp->set_brush(item->angle,item->space);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 5)
        {
            MyGraphicsPolygonItem *item = qgraphicsitem_cast<MyGraphicsPolygonItem *>(node);
            MyGraphicsPolygonItem *tmp = new MyGraphicsPolygonItem();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t2 = (p1.x()-pressPos.x())/(view->itemad->rec.width());
            double proportion = t2;
            tmp->num = item->num;
            tmp->setPos(((poss-roof)*proportion+poss).x(),poss.y());
            tmp->setRect(-item->rect().width()*(1+proportion)/2,-item->rect().height()/2,item->rect().width()*(1+proportion),item->rect().height());
            tmp->setData(0,-1);
            tmp->setDefault_Path();
            tmp->setData(0,-1);
            tmp->set_brush(item->angle,item->space);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 6)
        {
            MyGraphicsTextItem* item = qgraphicsitem_cast<MyGraphicsTextItem *>(node);
            MyGraphicsTextItem *tmp = new MyGraphicsTextItem();
            QPointF poss = item->pos();
            double t2 = (p1.x()-pressPos.x())/(view->itemad->rec.width());
            double proportion = t2;
            QPainterPath path1 = item->path;
            QPainterPath path2 ;
            int k=0;
            QPointF c1,c2;
            tmp->setPos(((poss-roof)*proportion+poss).x(),poss.y());
            QPointF offset = tmp->pos() - item->pos();   //用来计算path2的pos差值
            for (int i = 0; i < path1.elementCount(); i++)
            {

                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(proportion)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                po2.setY(item->mapFromScene(po).y());
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
                else if(element.isCurveTo())
                {

                    c1 = po2;
                    k++;
                    //path2.cubicTo(po2);
                }
                else
                {
                    if(k%3 == 1)
                    {

                        c2 = po2;
                        k++;
                    }
                    else if(k%3 == 2)
                    {
                        path2.cubicTo(c1,c2,po2);
                        k++;
                    }

                }
            }
            tmp->setRect(-item->rect().width()*(1+proportion)/2,-item->rect().height()/2,item->rect().width()*(1+proportion),item->rect().height());
            tmp->setPath(path2);
            tmp->setData(0,-1);
            tmp->set_brush(item->angle,item->space);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 7)
        {
            MyGraphicsCurveLineItem* item = qgraphicsitem_cast<MyGraphicsCurveLineItem *>(node);
            MyGraphicsCurveLineItem *tmp = new MyGraphicsCurveLineItem();
            QPointF poss = item->pos();
            double t2 = (p1.x()-pressPos.x())/(view->itemad->rec.width());
            double proportion = t2;
            QPainterPath path1 = item->path();
            QPainterPath path2 ;
            int k=0;
            QPointF c1,c2;
            tmp->setPos(((poss-roof)*proportion+poss).x(),poss.y());
            QPointF offset = tmp->pos() - item->pos();   //用来计算path2的pos差值
            for (int i = 0; i < path1.elementCount(); i++)
            {

                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(proportion)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                po2.setY(item->mapFromScene(po).y());
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
                else if(element.isCurveTo())
                {

                    c1 = po2;
                    k++;
                    //path2.cubicTo(po2);
                }
                else
                {
                    if(k%3 == 1)
                    {

                        c2 = po2;
                        k++;
                    }
                    else if(k%3 == 2)
                    {
                        path2.cubicTo(c1,c2,po2);
                        k++;
                    }

                }
            }
            tmp->setPath(path2);
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 8)
        {
            MyGraphicsPixMapItem* item = qgraphicsitem_cast<MyGraphicsPixMapItem *>(node);
            MyGraphicsPixMapItem *tmp = new MyGraphicsPixMapItem();
            QPointF poss = item->pos();
            double t2 = (p1.x()-pressPos.x())/(view->itemad->rec.width());
            double proportion = t2;
            tmp->setPixmap(item->pixmap());
            tmp->setPos(((poss-roof)*proportion+poss).x(),poss.y());
            double w = qAbs(item->rect().width()*(1+proportion));
            double h = qAbs(item->rect().height());
            if(item->rect().width()*(1+proportion)<0)
            {
                tmp->setPos(tmp->pos()-QPointF(w,0));
            }

            tmp->setRectF(QRect(0,-h,w,h));
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
        else if(node->type() == 9)
        {
            MyGraphicsCodeItem *item = qgraphicsitem_cast<MyGraphicsCodeItem *>(node);
            QPointF p2 = item->mapToScene(item->rect()).value(0);
            QPointF p3 = item->mapToScene(item->rect()).value(2);
            MyGraphicsCodeItem *tmp = new MyGraphicsCodeItem();
            double t2 = (p1.x()-pressPos.x())/(view->itemad->rec.width());
            double proportion = t2;
            QPainterPath path1 = item->path;
            QPainterPath path2 ;
            QPointF poss = item->pos();
            tmp->setPos(((poss-roof)*proportion+poss).x(),poss.y());
            QPointF offset = tmp->pos() - item->pos();

            for (int i = 0; i < path1.elementCount(); i++)
            {
                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(proportion)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                po2.setY(item->mapFromScene(po).y());
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
            }
            tmp->setRect(-item->rect().width()*(1+proportion)/2,-item->rect().height()/2,item->rect().width()*(1+proportion),item->rect().height());
            tmp->path = (path2);
            tmp->setData(0,-1);
            tmp->text = item->text;
            tmp->codetype = item->codetype;
            tmp->set_brush(item->angle,item->space);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            view->scene()->addItem(tmp);
        }
    }
    view->scene()->update();
}


void ItemChangeHandle::saveItems()
{
    QList<QGraphicsItem *> itemss = view->scene()->items();
    for (QList<QGraphicsItem*>::iterator it = itemss.begin(); it != itemss.end(); it++)
    {
        QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);

        if(node->data(0).toInt()<0)
        {
            for(QList<QGraphicsItem*>::iterator itt = itemss.begin(); itt != itemss.end(); itt++)
            {
                QGraphicsItem* node2 = qgraphicsitem_cast<QGraphicsItem *>(*itt);
                if(node->data(1).toInt() == node2->data(0).toInt())
                {
                    if(node2->type()==1)
                    {
                        MyGraphicsRecItem *item1 = qgraphicsitem_cast<MyGraphicsRecItem*>(node);
                        MyGraphicsRecItem *item2 = qgraphicsitem_cast<MyGraphicsRecItem*>(node2);
                        //
                        QList<QPointF> list;
                        list.append(item1->mapToScene(item1->rect()).value(0));
                        list.append(item1->mapToScene(item1->rect()).value(2));
                        double w = qAbs(list[0].x()-list[1].x());
                        double h = qAbs(list[0].y()-list[1].y());
                        item2->setPos(fmin(list[0].x(),list[1].x())+(w/2),fmin(list[0].y(),list[1].y())+(h/2));
                        item2->setRect(-w/2,-h/2,w,h);
                        item2->set_brush(item1->angle,item1->space);
                        if(item2->data(5).toInt() != 0)
                        {
                            for(int i = 0;i<itemss.length();i++)
                            {
                                if(itemss[i]->type() == 10)
                                {
                                    if(item2->data(5).toInt() == itemss[i]->data(0).toInt())
                                    {
                                        //item2->setPos(item2->pos()+qgraphicsitem_cast<MyGraphicsGroupItem*>(itemss[i])->pos());
                                        qgraphicsitem_cast<MyGraphicsGroupItem*>(itemss[i])->addToGroup(item2);
                                        //qDebug()<<item2->pos()<<endl;
                                    }
                                }
                            }
                        }
                        break;
                    }
                    else if(node2->type() == 2)
                    {
                        MyGraphicsEllipseItem *item1 = qgraphicsitem_cast<MyGraphicsEllipseItem*>(node);
                        MyGraphicsEllipseItem *item2 = qgraphicsitem_cast<MyGraphicsEllipseItem*>(node2);
                        //
                        QList<QPointF> list;
                        list.append(item1->mapToScene(item1->rect()).value(0));
                        list.append(item1->mapToScene(item1->rect()).value(2));
                        double minx = fmin(list[0].x(),list[1].x()), miny = fmin(list[0].y(),list[1].y());
                        double w = qAbs( list[1].x()-list[0].x());
                        double h = qAbs( list[1].y()-list[0].y());
                        item2->setPos(minx+(w/2),miny+(h/2));
                        item2->setRect(-w/2,-h/2,w,h);
                        item2->set_brush(item1->angle,item1->space);
                        if(item2->data(5).toInt() != 0)
                        {
                            for(int i = 0;i<itemss.length();i++)
                            {
                                if(itemss[i]->type() == 10)
                                {
                                    if(item2->data(5).toInt() == itemss[i]->data(0).toInt())
                                    {
                                        qgraphicsitem_cast<MyGraphicsGroupItem*>(itemss[i])->addToGroup(item2);
                                    }
                                }
                            }
                        }
                        break;
                    }
                    else if(node2->type() == 3)
                    {
                        MyGraphicsCircleItem *item1 = qgraphicsitem_cast<MyGraphicsCircleItem*>(node);
                        MyGraphicsCircleItem *item2 = qgraphicsitem_cast<MyGraphicsCircleItem*>(node2);
                        //
                        QList<QPointF> list;
                        list.append(item1->mapToScene(item1->rect()).value(0));
                        list.append(item1->mapToScene(item1->rect()).value(2));
                        double minx = fmin(list[0].x(),list[1].x()), miny = fmin(list[0].y(),list[1].y());
                        double w = qAbs( list[1].x()-list[0].x());
                        double h = qAbs( list[1].y()-list[0].y());
                        item2->setPos(minx+(w/2),miny+(h/2));
                        item2->setRect(-w/2,-h/2,w,h);
                        item2->set_brush(item1->angle,item1->space);
                        if(item2->data(5).toInt() != 0)
                        {
                            for(int i = 0;i<itemss.length();i++)
                            {
                                if(itemss[i]->type() == 10)
                                {
                                    if(item2->data(5).toInt() == itemss[i]->data(0).toInt())
                                    {
                                        qgraphicsitem_cast<MyGraphicsGroupItem*>(itemss[i])->addToGroup(item2);
                                    }
                                }
                            }
                        }
                        break;

                    }
                    else if(node2->type() == 4)
                    {
                        MyGraphicsLineItem *item1 = qgraphicsitem_cast<MyGraphicsLineItem*>(node);
                        MyGraphicsLineItem *item2 = qgraphicsitem_cast<MyGraphicsLineItem*>(node2);
                        item2->setPos(item1->pos());
                        item2->setPath(item1->path());
                        item2->set_brush(item1->angle,item1->space);
                        if(item2->data(5).toInt() != 0)
                        {
                            for(int i = 0;i<itemss.length();i++)
                            {
                                if(itemss[i]->type() == 10)
                                {
                                    if(item2->data(5).toInt() == itemss[i]->data(0).toInt())
                                    {
                                        qgraphicsitem_cast<MyGraphicsGroupItem*>(itemss[i])->addToGroup(item2);
                                    }
                                }
                            }
                        }
                        break;
                    }
                    else if(node2->type() == 5)
                    {
                        MyGraphicsPolygonItem *item1 = qgraphicsitem_cast<MyGraphicsPolygonItem*>(node);
                        MyGraphicsPolygonItem *item2 = qgraphicsitem_cast<MyGraphicsPolygonItem*>(node2);
                        //
                        QList<QPointF> list;
                        list.append(item1->mapToScene(item1->rect()).value(0));
                        list.append(item1->mapToScene(item1->rect()).value(2));
                        double minx = fmin(list[0].x(),list[1].x()), miny = fmin(list[0].y(),list[1].y());
                        double w = qAbs( list[1].x()-list[0].x());
                        double h = qAbs( list[1].y()-list[0].y());
                        item2->setPos(minx+(w/2),miny+(h/2));
                        item2->setRect(-w/2,-h/2,w,h);
                        item2->setPath(item1->path);
                        item2->set_brush(item1->angle,item1->space);
                        if(item2->data(5).toInt() != 0)
                        {
                            for(int i = 0;i<itemss.length();i++)
                            {
                                if(itemss[i]->type() == 10)
                                {
                                    if(item2->data(5).toInt() == itemss[i]->data(0).toInt())
                                    {
                                        qgraphicsitem_cast<MyGraphicsGroupItem*>(itemss[i])->addToGroup(item2);
                                    }
                                }
                            }
                        }
                        break;
                    }
                    else if(node2->type() == 6)
                    {
                        MyGraphicsTextItem *item1 = qgraphicsitem_cast<MyGraphicsTextItem*>(node);
                        MyGraphicsTextItem *item2 = qgraphicsitem_cast<MyGraphicsTextItem*>(node2);
                        QList<QPointF> list;
                        list.append(item1->mapToScene(item1->rect()).value(0));
                        list.append(item1->mapToScene(item1->rect()).value(2));
                        double minx = fmin(list[0].x(),list[1].x()), miny = fmin(list[0].y(),list[1].y());
                        double w = qAbs( list[1].x()-list[0].x());
                        double h = qAbs( list[1].y()-list[0].y());
                        item2->setPos(minx+(w/2),miny+(h/2));
                        item2->setRect(-w/2,-h/2,w,h);
                        item2->setPath(item1->path);
                        item2->set_brush(item1->angle,item1->space);
                        if(item2->data(5).toInt() != 0)
                        {
                            for(int i = 0;i<itemss.length();i++)
                            {
                                if(itemss[i]->type() == 10)
                                {
                                    if(item2->data(5).toInt() == itemss[i]->data(0).toInt())
                                    {
                                        qgraphicsitem_cast<MyGraphicsGroupItem*>(itemss[i])->addToGroup(item2);
                                    }
                                }
                            }
                        }
                        break;
                    }
                    else if(node2->type() == 7)
                    {
                        MyGraphicsCurveLineItem *item1 = qgraphicsitem_cast<MyGraphicsCurveLineItem*>(node);
                        MyGraphicsCurveLineItem *item2 = qgraphicsitem_cast<MyGraphicsCurveLineItem*>(node2);
                        item2->setPos(item1->pos());
                        item2->setPath(item1->path());
                        if(item2->data(5).toInt() != 0)
                        {
                            for(int i = 0;i<itemss.length();i++)
                            {
                                if(itemss[i]->type() == 10)
                                {
                                    if(item2->data(5).toInt() == itemss[i]->data(0).toInt())
                                    {
                                        qgraphicsitem_cast<MyGraphicsGroupItem*>(itemss[i])->addToGroup(item2);
                                    }
                                }
                            }
                        }
                        break;
                    }
                    else if(node2->type() == 8)
                    {
                        MyGraphicsPixMapItem *item1 = qgraphicsitem_cast<MyGraphicsPixMapItem*>(node);
                        MyGraphicsPixMapItem *item2 = qgraphicsitem_cast<MyGraphicsPixMapItem*>(node2);
                        QList<QPointF> list;
                        list.append(item1->mapToScene(item1->rectf).value(0));
                        list.append(item1->mapToScene(item1->rectf).value(2));
                        //qDebug()<<list<<endl;
                        double minx = fmin(list[0].x(),list[1].x()), maxy = fmax(list[0].y(),list[1].y());
                        double w = qAbs( list[1].x()-list[0].x());
                        double h = qAbs( list[1].y()-list[0].y());
                        item2->setPos(minx,maxy);
                        item2->setRectF(QRect(0,-h,w,h));
                        if(item2->data(5).toInt() != 0)
                        {
                            for(int i = 0;i<itemss.length();i++)
                            {
                                if(itemss[i]->type() == 10)
                                {
                                    if(item2->data(5).toInt() == itemss[i]->data(0).toInt())
                                    {
                                        qgraphicsitem_cast<MyGraphicsGroupItem*>(itemss[i])->addToGroup(item2);
                                    }
                                }
                            }
                        }
                        break;
                    }
                    else if(node2->type() == 9)
                    {
                        MyGraphicsCodeItem *item1 = qgraphicsitem_cast<MyGraphicsCodeItem*>(node);
                        MyGraphicsCodeItem *item2 = qgraphicsitem_cast<MyGraphicsCodeItem*>(node2);
                        QList<QPointF> list;
                        list.append(item1->mapToScene(item1->rect()).value(0));
                        list.append(item1->mapToScene(item1->rect()).value(2));
                        double minx = fmin(list[0].x(),list[1].x()), miny = fmin(list[0].y(),list[1].y());
                        double w = qAbs( list[1].x()-list[0].x());
                        double h = qAbs( list[1].y()-list[0].y());
                        item2->setPos(minx+(w/2),miny+(h/2));
                        item2->setRect(-w/2,-h/2,w,h);
                        item2->path = (item1->path);
                        item2->set_brush(item1->angle,item1->space);
                        if(item2->data(5).toInt() != 0)
                        {
                            for(int i = 0;i<itemss.length();i++)
                            {
                                if(itemss[i]->type() == 10)
                                {
                                    if(item2->data(5).toInt() == itemss[i]->data(0).toInt())
                                    {
                                        qgraphicsitem_cast<MyGraphicsGroupItem*>(itemss[i])->addToGroup(item2);
                                    }
                                }
                            }
                        }
                        break;
                    }
                }
            }

            for(int i = 0;i<itemss.length();i++)
            {
                if(itemss[i]->type() == 10)
                {
                      qgraphicsitem_cast<MyGraphicsGroupItem*>(itemss[i])->set_brush(qgraphicsitem_cast<MyGraphicsGroupItem*>(itemss[i])->angle,qgraphicsitem_cast<MyGraphicsGroupItem*>(itemss[i])->space);
                }
            }
            view->scene()->removeItem(node);
        }
    }
    emit view->selectchange();
}
