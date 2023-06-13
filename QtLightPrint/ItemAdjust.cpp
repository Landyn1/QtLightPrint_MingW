#include "ItemAdjust.h"
#include<qpainter.h>
#include<qdebug.h>
#include"ItemHandle/itemsizehandle.h"
ItemAdjust::ItemAdjust(QGraphicsItem* parent) : QGraphicsRectItem(parent)
{


}
QRectF ItemAdjust::boundingRect() const
{
	QRectF temp_rect = rect();
	
	return temp_rect;

}
void ItemAdjust::setRec(QRectF f)
{
	rec = f;
	lefttop = QRectF(0, rec.height() + (15 / scale), 5 / scale, 5 / scale);
	midtop = QRectF((10 / scale) + (rec.width() / 2), rec.height() + (15 / scale), 5 / scale, 5 / scale);
	righttop = QRectF(rec.width() + (15 / scale), rec.height() + (15 / scale), 5 / scale, 5 / scale);
	leftbuttom = QRectF(0, 0, 5 / scale, 5 / scale);
	midbuttom = QRectF((10 / scale) + (rec.width() / 2), 0, 5 / scale, 5 / scale);
	rightbuttom = QRectF(rec.width() + (15 / scale), 0, 5 / scale, 5 / scale);
	leftmid = QRectF(0, (10 / scale) + (rec.height() / 2), 5 / scale, 5 / scale);
	rightmid = QRectF(rec.width() + (15 / scale), (10 / scale) + (rec.height() / 2), 5 / scale, 5 / scale);

    mid = QRectF((10 / scale) + (rec.width() / 2), (10 / scale) + (rec.height() / 2), 8 / scale, 8 / scale);

    scene()->update();

}
void ItemAdjust::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	QPen pen;
	pen.setWidth(1);
	pen.setColor(QColor(Qt::black));
	painter->setPen(pen);
	painter->setBrush(QBrush(QColor(Qt::black)));
	
	painter->drawRect(leftbuttom);
	painter->drawRect(midbuttom);
	painter->drawRect(rightbuttom);
	painter->drawRect(lefttop);
	painter->drawRect(midtop);
	painter->drawRect(righttop);
	painter->drawRect(leftmid);
	painter->drawRect(rightmid);

    QPen pen1;
    pen1.setWidth(3);
    pen1.setColor(QColor(Qt::blue));
    painter->setPen(pen1);
	painter->drawLine(QPointF( mid.left(), mid.top()),QPointF(mid.right(),mid.bottom()));
	painter->drawLine(QPointF( mid.left(), mid.bottom()),QPointF(mid.right(),mid.top()));

	//painter->drawRect(QRectF(0, rect().height() + (15 / scale), 5 / scale, 5 / scale));

}

void ItemAdjust::mousePressEvent(QGraphicsSceneMouseEvent* event)
{

}


void ItemAdjust::setitemad(mainWindow* mw)
{
            ItemSizeHandle *itemsizehandler = new ItemSizeHandle();

            QList<QGraphicsItem*> items = mw->scene->selectedItems();
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
                    itemsizehandler->setItemRect_XandY<MyGraphicsRecItem>(node,x,y);
                }
                else if( node ->type() == 2)
                {
                    itemsizehandler->setItemRect_XandY<MyGraphicsEllipseItem>(node,x,y);
                }
                else if(node->type() == 3)
                {
                    itemsizehandler->setItemRect_XandY<MyGraphicsCircleItem>(node,x,y);
                }
                else if(node->type() == 4)
                {
                    itemsizehandler->setItemRect_XandY<MyGraphicsLineItem>(node,x,y);
                }
                else if(node->type() == 5)
                {
                    itemsizehandler->setItemRect_XandY<MyGraphicsPolygonItem>(node,x,y);
                }
                else if(node->type() == 6)
                {
                    itemsizehandler->setItemRect_XandY<MyGraphicsTextItem>(node,x,y);

                }
                else if(node->type() == 7)
                {
                    itemsizehandler->setItemRect_XandY<MyGraphicsCurveLineItem>(node,x,y);
                }
                else if(node->type() == 8)
                {
                    itemsizehandler->setItemRect_XandY<MyGraphicsPixMapItem>(node,x,y);
                }
                else if(node->type() == 9)
                {
                    itemsizehandler->setItemRect_XandY<MyGraphicsCodeItem>(node,x,y);
                }
                else if(node->type() == 10)
                {
                    itemsizehandler->setItemRect_XandY<MyGraphicsGroupItem>(node,x,y);
                }
            }
            //再确定宽高
            for (QList<QGraphicsItem*>::iterator it = items.begin(); it != items.end(); it++)
            {
                QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);
                if(node->type() == 1)
                {
                    itemsizehandler->setItemRect_WandH<MyGraphicsRecItem>(node,x,y,w,h);
                }
                else if(node->type()==2)
                {
                    itemsizehandler->setItemRect_WandH<MyGraphicsEllipseItem>(node,x,y,w,h);
                }
                else if(node->type() == 3)
                {
                    itemsizehandler->setItemRect_WandH<MyGraphicsCircleItem>(node,x,y,w,h);
                }
                else if(node->type() == 4)
                {
                    itemsizehandler->setItemRect_WandH<MyGraphicsLineItem>(node,x,y,w,h);
                }
                else if(node->type() == 5)
                {
                    itemsizehandler->setItemRect_WandH<MyGraphicsPolygonItem>(node,x,y,w,h);
                }
                else if(node->type() == 6)
                {
                    itemsizehandler->setItemRect_WandH<MyGraphicsTextItem>(node,x,y,w,h);
                }
                else if(node->type() == 7)
                {
                    itemsizehandler->setItemRect_WandH<MyGraphicsCurveLineItem>(node,x,y,w,h);
                }
                else if(node->type() == 8)
                {
                    itemsizehandler->setItemRect_WandH<MyGraphicsPixMapItem>(node,x,y,w,h);
                }
                else if(node->type() == 9)
                {
                    itemsizehandler->setItemRect_WandH<MyGraphicsCodeItem>(node,x,y,w,h);
                }
                else if(node->type() == 10)
                {
                    itemsizehandler->setItemRect_WandH<MyGraphicsGroupItem>(node,x,y,w,h);
                }
            }
            mw->view->itemad->setPos(x - 10 / mw->view->itemad->scale, y - 10 / mw->view->itemad->scale);
            mw->view->itemad->setRect(0, 0, w + 20 / mw->view->itemad->scale, h + 20 / mw->view->itemad->scale);
            mw->view->itemad->setRec(QRectF(0, 0, w , h ));
            mw->view->itemad->setVisible(true);
            mw->scene->update();

}
template<typename T> void ItemSizeHandle::setItemRect_WandH(QGraphicsItem* node , int x,int y,int &w,int &h)
{
    T *item = qgraphicsitem_cast<T *>(node);
    if(w<item->getRect().x()+item->getRect().width() - x)
    {
        w = item->getRect().x()+item->getRect().width() - x;
    }
    if(h<item->getRect().y()+item->getRect().height() - y)
    {
        h = item->getRect().y()+item->getRect().height() - y;
    }
}

template<typename T> void ItemSizeHandle::setItemRect_XandY(QGraphicsItem* node,int &x,int &y)
{
    T *t = qgraphicsitem_cast<T *>(node);
    if(x > t->getRect().x())
    {
        x = t->getRect().x();
    }
    if(y > t->getRect().y())
    {
        y = t->getRect().y();
    }

}
