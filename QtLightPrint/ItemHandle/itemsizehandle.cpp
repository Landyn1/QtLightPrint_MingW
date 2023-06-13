#include "itemsizehandle.h"

ItemSizeHandle::ItemSizeHandle()
{

}


void ItemSizeHandle::setItemByLable(mainWindow *mw){
    QList<QGraphicsItem *> selectitems = mw->scene->selectedItems();
    for(QGraphicsItem* item:selectitems)
    {
        if(item->data(15).toInt()==1)
        {
            selectitems.removeOne(item);
        }
    }
    while(1)
    {
        int k=0;
        for(QGraphicsItem* item:selectitems)
        {
            if(item->type() == 10)
            {
                k=1;
                selectitems.removeOne(item);
                MyGraphicsGroupItem *g =qgraphicsitem_cast<MyGraphicsGroupItem*>(item);
                selectitems.append(g->childItems());
            }
        }
        if(k == 0)
        {
            break;
        }
    }

    double dpiX = QApplication::primaryScreen()->physicalDotsPerInchX();
    double t = (dpiX*10)/254;; //1mm = tpx;
    double x = mw->ui.xposition->text().toDouble();
    double y = mw->ui.yposition->text().toDouble();
    QPointF offset = QPointF(x*t,y*t)-mw->pre_Pos;
    double w = mw->ui.xsize->text().toDouble();
    double h = mw->ui.ysize->text().toDouble();
    double offset_w = w*t - mw->pre_w;
    double offset_h = h*t -mw->pre_h;
    double bilix = offset_w/mw->pre_w;
    double biliy = offset_h/mw->pre_h;
    QPointF roof = mw->pre_Pos;
    for(int i=0;i<selectitems.length();i++)
    {
        int type = selectitems[i]->type();
        if(type == 1)
        {
            MyGraphicsRecItem *item = qgraphicsitem_cast<MyGraphicsRecItem *>(selectitems[i]);
            double ww = item->rect().width();
            double hh = item->rect().height();
            item->setPos(((item->pos().x()-roof.x())*(bilix)+item->pos().x()),((item->pos().y()-roof.y())*(biliy)+item->pos().y()));
            ww = (ww)*(bilix)+ww;
            hh = (hh)*(biliy)+hh;
            item->setRect(-ww/2,-hh/2,ww,hh);
            item->set_brush(item->angle,item->space);
        }
        else if(type == 2)
        {
            MyGraphicsEllipseItem *item = qgraphicsitem_cast<MyGraphicsEllipseItem *>(selectitems[i]);
            double ww = item->rect().width();
            double hh = item->rect().height();
            item->setPos(((item->pos().x()-roof.x())*(bilix)+item->pos().x()),((item->pos().y()-roof.y())*(biliy)+item->pos().y()));
            ww = (ww)*(bilix)+ww;
            hh = (hh)*(biliy)+hh;
            item->setRect(-ww/2,-hh/2,ww,hh);
            item->set_brush(item->angle,item->space);
        }
        else if(type == 3)
        {
            MyGraphicsCircleItem *item = qgraphicsitem_cast<MyGraphicsCircleItem *>(selectitems[i]);
            double ww = item->rect().width();
            double hh = item->rect().height();
            item->setPos(((item->pos().x()-roof.x())*(bilix)+item->pos().x()),((item->pos().y()-roof.y())*(biliy)+item->pos().y()));
            ww = (ww)*(bilix)+ww;
            hh = (hh)*(biliy)+hh;
            item->setRect(-ww/2,-hh/2,ww,hh);
            item->set_brush(item->angle,item->space);
        }
        else if(type == 4)
        {
            MyGraphicsLineItem *item = qgraphicsitem_cast<MyGraphicsLineItem *>(selectitems[i]);

            QPainterPath path1 = item->path();
            QPainterPath path2 ;
            for (int i = 0; i < path1.elementCount(); i++)
            {
                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2(((po-roof)*(bilix)+po).x(),((po-roof)*(biliy)+po).y());
                po2 = item->mapFromScene(po2);
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
            }
            item->setPath(path2);
            item->set_brush(item->angle,item->space);
        }
        else if(type == 5)
        {
            MyGraphicsPolygonItem *item = qgraphicsitem_cast<MyGraphicsPolygonItem *>(selectitems[i]);
            item->num=mw->ui.bian_num->text().toInt();
            double ww = item->rect().width();
            double hh = item->rect().height();
            item->setPos(((item->pos().x()-roof.x())*(bilix)+item->pos().x()),((item->pos().y()-roof.y())*(biliy)+item->pos().y()));
            ww = (ww)*(bilix)+ww;
            hh = (hh)*(biliy)+hh;
            item->setRect(-ww/2,-hh/2,ww,hh);
            item->setDefault_Path();
            item->set_brush(item->angle,item->space);
        }
        else if(type == 6)
        {
            MyGraphicsTextItem* item = qgraphicsitem_cast<MyGraphicsTextItem *>(selectitems[i]);
            QString fontname = mw->ui.comboBox->currentText();
            item->setStr(mw->ui.textEdit->toPlainText(),QFont(fontname));
            double ww = item->rect().width();
            double hh = item->rect().height();
            ww = (ww)*(bilix)+ww;
            hh = (hh)*(biliy)+hh;
            item->setPos(((item->pos().x()-roof.x())*(bilix)+item->pos().x()),((item->pos().y()-roof.y())*(biliy)+item->pos().y()));

            item->setRect(-ww/2,-hh/2,ww,hh);
            item->makePath_fill_Rect();
            item->set_brush(item->angle,item->space);
        }
        else if(type == 7)
        {
            MyGraphicsCurveLineItem* item = qgraphicsitem_cast<MyGraphicsCurveLineItem *>(selectitems[i]);
            QPainterPath path1 = item->path();
            QPainterPath path2 ;
            int k=0;
            QPointF c1,c2;
            for (int i = 0; i < path1.elementCount(); i++)
            {

                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2(((po-roof)*(bilix)+po).x(),((po-roof)*(biliy)+po).y());
                po2 = item->mapFromScene(po2);
                //po2 = po2-offs;
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
            item->setPath(path2);
        }
        else if(type == 8)
        {
            MyGraphicsPixMapItem *item = qgraphicsitem_cast<MyGraphicsPixMapItem *>(selectitems[i]);
            double ww = item->rect().width();
            double hh = item->rect().height();
            item->setPos(((item->pos().x()-roof.x())*(bilix)+item->pos().x()),((item->pos().y()-roof.y())*(biliy)+item->pos().y()));
            ww = (ww)*(bilix)+ww;
            hh = (hh)*(biliy)+hh;
            item->setRectF(QRect(0,-hh,ww,hh));
        }
        else if(type == 9)
        {
            MyGraphicsCodeItem *item = qgraphicsitem_cast<MyGraphicsCodeItem *>(selectitems[i]);
            QString codetype = mw->ui.Codetype->currentText();
            if(selectitems.length() == 1)
                item->setPathByStr(mw->ui.textEdit_2->toPlainText(),codetype);
            double ww = item->rect().width();
            double hh = item->rect().height();
            ww = (ww)*(bilix)+ww;
            hh = (hh)*(biliy)+hh;
            item->setPos(((item->pos().x()-roof.x())*(bilix)+item->pos().x()),((item->pos().y()-roof.y())*(biliy)+item->pos().y()));
            item->setRect(-ww/2,-hh/2,ww,hh);
            item->makePath_fill_Rect();

            item->set_brush(item->angle,item->space);
        }
    }
    for(int i=0;i<selectitems.length();i++)
    {
        selectitems[i]->setPos(selectitems[i]->pos()+offset);
    }
    emit mw->scene->selectionChanged();
    emit mw->view->sceneChange();
    setpreRect(mw);
    mw->scene->update();
}
template<typename T> void ItemSizeHandle::setItemPosition(QGraphicsItem* node, int &leftbuttomx,int &leftbuttomy,int &righttopx,int &righttopy)
{
    T* line;
    line = qgraphicsitem_cast<T*>(node);
    if (action_state == 0)
    {
        line->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
    }
    else
    {
        line->setFlags(QGraphicsItem::ItemIsSelectable);
    }
    line->setSelected(true);
    if (leftbuttomx > line->getRect().x())
    {
        leftbuttomx = line->getRect().x();
    }
    if (leftbuttomy > line->getRect().y())
    {
        leftbuttomy = line->getRect().y();
    }
    if (righttopx < line->getRect().x()+line->getRect().width())
    {
        righttopx = line->getRect().x()+line->getRect().width();
    }
    if (righttopy < line->getRect().y()+line->getRect().height())
    {
        righttopy = line->getRect().y()+line->getRect().height();
    }
}
void ItemSizeHandle::setpreRect(mainWindow *mw)
{
    QList<QTableWidgetItem*> selectItems = mw->ui.itemtable->selectedItems();
    QSet<int> rows;
    for (QTableWidgetItem* item : selectItems)
    {
        rows.insert(item->row());
    }
    QSet<int>::iterator iter;
    int leftbuttomx = 5100, leftbuttomy = 5100, righttopx = -5100, righttopy = -5100;
    int k = 0;
    for (iter = rows.begin(); iter != rows.end(); iter++)
    {
        int row = *iter;
        QTableWidgetItem* item1 = new QTableWidgetItem;
        item1 = mw->ui.itemtable->item(row, 3);
        QString id = item1->text();
        QList<QGraphicsItem*> items = mw->scene->items();
        for (QList<QGraphicsItem*>::iterator it = items.begin(); it != items.end(); it++)
        {
            QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);
            int id1 = node->data(0).value<int>();
            if (node->isVisible() && id == QString::number(id1))
            {
                k = 1;
                if (node->type() == 1)
                {
                    setItemPosition<MyGraphicsRecItem>(node,leftbuttomx,leftbuttomy,righttopx,righttopy);
                }

                else if(node->type() == 2)
                {
                    setItemPosition<MyGraphicsEllipseItem>(node,leftbuttomx,leftbuttomy,righttopx,righttopy);
                }

                else if(node->type() == 3)
                {
                    setItemPosition<MyGraphicsCircleItem>(node,leftbuttomx,leftbuttomy,righttopx,righttopy);
                }

                else if(node->type() == 4)
                {
                    setItemPosition<MyGraphicsLineItem>(node,leftbuttomx,leftbuttomy,righttopx,righttopy);
                }
                else if(node->type() == 5)
                {
                    setItemPosition<MyGraphicsPolygonItem>(node,leftbuttomx,leftbuttomy,righttopx,righttopy);
                }

                //TODO:
                else if(node->type() == 6)
                {
                    setItemPosition<MyGraphicsTextItem>(node,leftbuttomx,leftbuttomy,righttopx,righttopy);

                }
                else if(node->type() == 7)
                {
                    setItemPosition<MyGraphicsCurveLineItem>(node,leftbuttomx,leftbuttomy,righttopx,righttopy);
                }
                else if(node->type() == 8)
                {
                    setItemPosition<MyGraphicsPixMapItem>(node,leftbuttomx,leftbuttomy,righttopx,righttopy);
                }
                else if(node->type() == 9)
                {
                    setItemPosition<MyGraphicsCodeItem>(node,leftbuttomx,leftbuttomy,righttopx,righttopy);
                }
                else if(node->type() == 10)
                {
                    setItemPosition<MyGraphicsGroupItem>(node,leftbuttomx,leftbuttomy,righttopx,righttopy);
                }
            }
        }
    }
    double x = leftbuttomx, y = leftbuttomy , width = righttopx-leftbuttomx,height = righttopy-leftbuttomy;

    if (k == 1)
    {
        mw->pre_Pos = QPointF(x+(width/2),y+(height/2));
        mw->pre_w = width;mw->pre_h = height;
    }
    else
    {
        mw->pre_Pos = QPointF(0,0);
        mw->pre_w = 0;mw->pre_h = 0;
    }
}

