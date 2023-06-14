#include "itemselecthandle.h"
#include<QObject>
ItemSelectHandle::ItemSelectHandle(MyGraphicsView *view)
{
    this->view = view;
}


void ItemSelectHandle::setSelecT(int k)
{
    QList<QGraphicsItem*> items = view->scene()->items();
    for (QList<QGraphicsItem*>::iterator it = items.begin(); it != items.end(); it++)
    {
        QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);
        if(node->data(0)>0)
        {
                if(node->type()==1)
                {
                    MyGraphicsRecItem *rect = qgraphicsitem_cast<MyGraphicsRecItem*>(node);
                    QPointF p = rect->mapFromScene(view->mapToScene(view->_lastMousePos));
                    if(rect->selectEvent(p))
                    {
                        if(k==0)
                        {
                            QList<QGraphicsItem *> selectItems = view->scene()->selectedItems();
                            for(QGraphicsItem* selectitem : selectItems)
                            {
                                if(rect->data(0)!= selectitem->data(0))
                                {
                                    selectitem->setFlags(NULL);
                                }
                            }
                        }
                    }
                }
                else if(node->type()==2)
                {
                    MyGraphicsEllipseItem *item = qgraphicsitem_cast<MyGraphicsEllipseItem*>(node);
                    QPointF p = item->mapFromScene(view->mapToScene(view->_lastMousePos));

                    if(item->selectEvent(p))
                    {
                        if( k==0 )
                        {
                            QList<QGraphicsItem *> selectItems = view->scene()->selectedItems();
                            for(QGraphicsItem* selectitem : selectItems)
                            {
                                if(item->data(0)!= selectitem->data(0))
                                {
                                    selectitem->setFlags(NULL);
                                }
                            }
                        }
                    }


                }
                else if(node->type() == 3)
                {
                    MyGraphicsCircleItem *item = qgraphicsitem_cast<MyGraphicsCircleItem*>(node);
                    QPointF p = item->mapFromScene(view->mapToScene(view->_lastMousePos));

                    if(item->selectEvent(p))
                    {
                        if( k==0 )
                        {
                            QList<QGraphicsItem *> selectItems = view->scene()->selectedItems();
                            for(QGraphicsItem* selectitem : selectItems)
                            {
                                if(item->data(0)!= selectitem->data(0))
                                {
                                    selectitem->setFlags(NULL);
                                }
                            }
                        }
                    }
                }
                else if(node->type() == 4)
                {
                    MyGraphicsLineItem *item = qgraphicsitem_cast<MyGraphicsLineItem *>(node);
                    QPointF p = item->mapFromScene(view->mapToScene(view->_lastMousePos));
                    if(item->selectEvent(p))
                    {
                        if( k==0 )
                        {
                            QList<QGraphicsItem *> selectItems = view->scene()->selectedItems();
                            for(QGraphicsItem* selectitem : selectItems)
                            {
                                if(item->data(0)!= selectitem->data(0))
                                {
                                    selectitem->setFlags(NULL);
                                }
                            }
                        }
                    }
                }
                else if(node->type() == 5)
                {
                    MyGraphicsPolygonItem *item = qgraphicsitem_cast<MyGraphicsPolygonItem *>(node);
                    QPointF p = item->mapFromScene(view->mapToScene(view->_lastMousePos));
                    if(item->selectEvent(p))
                    {
                        if( k==0 )
                        {
                            QList<QGraphicsItem *> selectItems = view->scene()->selectedItems();
                            for(QGraphicsItem* selectitem : selectItems)
                            {
                                if(item->data(0)!= selectitem->data(0))
                                {
                                    selectitem->setFlags(NULL);
                                }
                            }
                        }
                    }
                }
                else if(node->type() == 6)
                {
                    MyGraphicsTextItem *item = qgraphicsitem_cast<MyGraphicsTextItem *>(node);
                    QPointF p = item->mapFromScene(view->mapToScene(view->_lastMousePos));
                    if(item->selectEvent(p))
                    {
                        if( k==0 )
                        {
                            QList<QGraphicsItem *> selectItems = view->scene()->selectedItems();
                            for(QGraphicsItem* selectitem : selectItems)
                            {
                                if(item->data(0)!= selectitem->data(0))
                                {
                                    selectitem->setFlags(NULL);
                                }
                            }
                        }
                    }
                }
                else if(node->type() == 7)
                {
                    MyGraphicsCurveLineItem *item = qgraphicsitem_cast<MyGraphicsCurveLineItem *>(node);
                    QPointF p = item->mapFromScene(view->mapToScene(view->_lastMousePos));
                    if(item->selectEvent(p))
                    {

                        if( k==0 )
                        {
                            QList<QGraphicsItem *> selectItems = view->scene()->selectedItems();
                            for(QGraphicsItem* selectitem : selectItems)
                            {
                                if(item->data(0)!= selectitem->data(0))
                                {
                                    selectitem->setFlags(NULL);
                                }
                            }
                        }
                    }
                }
                else if(node->type() == 8)
                {
                    MyGraphicsPixMapItem *item = qgraphicsitem_cast<MyGraphicsPixMapItem *>(node);
                    QPointF p = item->mapFromScene(view->mapToScene(view->_lastMousePos));
                    if(item->selectEvent(p))
                    {
                        if( k==0 )
                        {
                            QList<QGraphicsItem *> selectItems = view->scene()->selectedItems();
                            for(QGraphicsItem* selectitem : selectItems)
                            {
                                if(item->data(0)!= selectitem->data(0))
                                {
                                    selectitem->setFlags(NULL);
                                }
                            }
                        }
                    }
                }
                else if( node->type() == 9)
                {
                    MyGraphicsCodeItem *item = qgraphicsitem_cast<MyGraphicsCodeItem *>(node);
                    QPointF p = item->mapFromScene(view->mapToScene(view->_lastMousePos));
                    if(item->selectEvent(p))
                    {
                        if( k==0 )
                        {
                            QList<QGraphicsItem *> selectItems = view->scene()->selectedItems();
                            for(QGraphicsItem* selectitem : selectItems)
                            {
                                if(item->data(0)!= selectitem->data(0))
                                {
                                    selectitem->setFlags(NULL);
                                }
                            }
                        }
                    }
                }
                if(node->type()==10)
                {
                    MyGraphicsGroupItem *item = qgraphicsitem_cast<MyGraphicsGroupItem*>(node);
                    QPointF p = (view->mapToScene(view->_lastMousePos));
                    if(item->selectEvent(p))
                    {
                        if( k==0 )
                        {
                            QList<QGraphicsItem *> selectItems = view->scene()->selectedItems();
                            for(QGraphicsItem* selectitem : selectItems)
                            {
                                if(item->data(0)!= selectitem->data(0))
                                {
                                    selectitem->setFlags(NULL);
                                }
                            }
                        }
                    }
                }
        }

    }
    items = view->scene()->selectedItems();

}
