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
    prepareGeometryChange();
    QList<QGraphicsItem*> items = this->childItems();

    while(1)
    {
        int k=0;
        for(QGraphicsItem* item:items)
        {
            if(item->type() == 10)
            {
                k=1;
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
//        else if(node->type() == 10)
//        {
//            MyGraphicsGroupItem *t = qgraphicsitem_cast<MyGraphicsGroupItem *>(node);
//            if(x > t->getRect().x())
//            {
//                x = t->getRect().x();
//            }
//            if(y > t->getRect().y())
//            {
//                y = t->getRect().y();
//            }
//        }
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


    QRect rec(x,y,w,h);
    return rec;
}


void MyGraphicsGroupItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
        painter->drawPath(brushPath);
}


void MyGraphicsGroupItem::setLinsAndCurves(QPainterPath path2, QList<QLineF> &lins)
{
    QPointF lp1,lp2;
    int kl = 0;
    for (int i = 0; i < path2.elementCount(); i++)
    {
        QPainterPath::Element element = path2.elementAt(i);
        QPointF po = element;
        if (element.isMoveTo())
        {
            lp1 = po;
            kl = 0;
        }
        else if (element.isLineTo())
        {
            if(kl == 0)
            {
                lp2 = po;
                lins.append(QLineF(lp1,lp2));
                kl++;
            }
            else
            {
                lp1 = lp2;
                lp2 = po;
                lins.append(QLineF(lp1,lp2));
            }
        }
    }
}

void MyGraphicsGroupItem::setBrushpath(QList<QLineF> lins, QLineF l, QList<QPointF> intersections, QPainterPath &path2, QPainterPath path,int k)
{

    //延长l以确保不会丢失交点
    QPointF p1,p2;
    QPointF pp1,pp2;
    p1 = l.p1();
    p2 = l.p2();
    l.setLength(-2);
    pp1 = l.p2();
    l.setP1(p1);
    l.setP2(p2);
    l.setLength(l.length()+2);
    pp2 = l.p2();
    l.setP1(pp1);
    l.setP2(pp2);



    for(int i=0;i<lins.length();i++)
    {
        QPointF intersectionPoint;
        auto type = l.intersects(lins[i],&intersectionPoint);
        if(type == QLineF::BoundedIntersection)
        {
            intersections.append(intersectionPoint);
        }
    }
    if(k == 0)
    {
        for(int i = 1;i<intersections.length();i++)
        {
            for(int j=0;j<intersections.length()-i;j++)
            {
                if(intersections[j].x()>intersections[j+1].x())
                {
                    QPointF tm = intersections[j];
                    intersections[j] = intersections[j+1];
                    intersections[j+1] = tm;
                }
            }
        }
        for(int i=0;i<intersections.length()-1;i++)
        {
            double x1,y1;
            x1 = (intersections[i].x()+intersections[i+1].x())/2;
            y1 = (intersections[i].y()+intersections[i+1].y())/2;
            if(path.contains((QPointF(x1,y1))))
            {
                     path2.moveTo(intersections[i]);
                     path2.lineTo(intersections[i+1]);
            }
        }

    }
    else if( k == 1)
    {
        for(int i = 1;i<intersections.length();i++)
        {
            for(int j=0;j<intersections.length()-i;j++)
            {
                if(intersections[j].x()>intersections[j+1].x())
                {
                    QPointF tm = intersections[j];
                    intersections[j] = intersections[j+1];
                    intersections[j+1] = tm;
                }
            }
        }
        for(int i=0;i<intersections.length()-1;i++)
        {
            if(path.contains((intersections[i]+QPointF(1,0))) && path.contains((intersections[i+1]-QPointF(1,0))))
            {
                     path2.moveTo(intersections[i]);
                     path2.lineTo(intersections[i+1]);
            }
        }
    }
    else
    {
        for(int i = 1;i<intersections.length();i++)
        {
            for(int j=0;j<intersections.length()-i;j++)
            {
                if(intersections[j].y()>intersections[j+1].y())
                {
                    QPointF tm = intersections[j];
                    intersections[j] = intersections[j+1];
                    intersections[j+1] = tm;
                }
            }
        }

        for(int i=0;i<intersections.length()-1;i++)
        {
            double x1,y1;
            x1 = (intersections[i].x()+intersections[i+1].x())/2;
            y1 = (intersections[i].y()+intersections[i+1].y())/2;
            if(path.contains((QPointF(x1,y1))))
            {
                     path2.moveTo(intersections[i]);
                     path2.lineTo(intersections[i+1]);
            }
        }
    }
}
template<typename T> QPainterPath MyGraphicsGroupItem::getpath(QGraphicsItem* node,QPainterPath &path)
{
    T *item = qgraphicsitem_cast<T *>(node);
    for (int i = 0; i < item->ViewPath().elementCount(); i++)
    {
        QPainterPath::Element element = item->ViewPath().elementAt(i);
        QPointF po = element;
        if (element.isMoveTo())
        {
            path.moveTo(po);
        }
        else if (element.isLineTo())
        {
            path.lineTo(po);
        }
    }
    return path;
}
bool MyGraphicsGroupItem::set_brush(double angle,double space)
{
    brushPath.clear();
    this->angle = angle;
    double dpiX = QApplication::primaryScreen()->physicalDotsPerInchX();
    double  temp = (dpiX * 10) / 254; //1mm = tpx
    double maxh = fmax(this->getRect().width(),this->getRect().height());
    double linenum = (maxh/temp) / space;
    this->space = space;
    if(space == 0)
    {
        update();
        return true;
    }
    QPainterPath path2;
    double k = tan(angle*M_PI/180);//斜率
    double w = this->boundingRect().width();
    double h = this->boundingRect().height();
    QList<QPointF> intersections;
    QList<QLineF> lins;
    QList<QGraphicsItem*> items = this->childItems();

    while(1)
    {
        int k=0;
        for(QGraphicsItem* item:items)
        {
            if(item->type() == 10)
            {
                k=1;
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

    QPainterPath path;
    for(int i=0;i<items.length();i++)
    {
        if(items[i]->type() == 1)
        {
            getpath<MyGraphicsRecItem>(items[i],path);
        }
        else if(items[i]->type() == 2)
        {
            getpath<MyGraphicsEllipseItem>(items[i],path);
        }
        else if(items[i]->type() == 3)
        {
            getpath<MyGraphicsCircleItem>(items[i],path);
        }
        else if(items[i]->type() == 4)
        {
            getpath<MyGraphicsLineItem>(items[i],path);
        }
        else if(items[i]->type() == 5)
        {
            getpath<MyGraphicsPolygonItem>(items[i],path);
        }
        else if(items[i]->type() == 6)
        {
            getpath<MyGraphicsTextItem>(items[i],path);
        }
        else if(items[i]->type() == 7)
        {
            getpath<MyGraphicsCurveLineItem>(items[i],path);
        }
        else if(items[i]->type() == 9)
        {
            getpath<MyGraphicsCodeItem>(items[i],path);
        }
    }
    setLinsAndCurves(path,lins);
    double m = double(h)/double(w);
    double offsetx = path.boundingRect().x();
    double offsety = path.boundingRect().y();
    QPointF offset(offsetx,offsety);
    if(int(angle)%90 != 0 ||  ((int(angle)%180 == 0)&&(int(angle)%90 != 0)))
    {
        if(k>0&&k<=m)
        {
            double t = h + k*w; //y=kx+t
            double pert = t/(linenum);
            for(double ii=-k*w-1;ii<h+1;ii += pert)
            {
                intersections.clear();
                QPointF p1(w,(w*k)+(ii));
                QPointF p2(0,(ii));
                if( ii > (h)- (w*k))
                {
                    p1 = QPointF(((h)-(ii))/k,h);
                }
                else if( ii < 0)
                {
                    p2 = QPointF((-(ii))/k,0);
                }
                QLineF l(p1+offset,p2+offset);
                setBrushpath(lins,l,intersections,path2,path);
            }

        }
        else if( k>m )
        {
            double t = h + w*k; //y=kx+t
            double pert = t/double(linenum);
            for(double ii=-k*w-1;ii<h+1;ii= ii + pert)
            {
                intersections.clear();
                QPointF p1(((h)-(ii))/k,h);
                QPointF p2((-(ii))/k,0);

                if(ii <= (h)- (w*k))
                {

                    p1 = QPointF(w,(w*k)+(ii));
                }
                else if( ii > 0)
                {
                    p2 = QPointF(0,(ii));
                }
                QLineF l(p1+offset,p2+offset);
                setBrushpath(lins,l,intersections,path2,path);
            }

        }
        else if( k<-m)
        {

            double t = -(w*k) + (h); //y=kx+t
            double pert = t/double(linenum);
            for(int ii=0;ii<=linenum;ii++)
            {
                intersections.clear();
                QPointF p1(((h)-(pert*ii))/k,h);
                QPointF p2((-(pert*ii))/k,0);
                if(pert * ii < h)
                {
                    p1 = QPointF(0,(pert*ii));
                }
                else if( pert * ii > (-w*k))
                {
                    p2 = QPointF(w,(w*k)+(pert*ii));
                }
                QLineF l(p1+offset,p2+offset);
                setBrushpath(lins,l,intersections,path2,path);
            }
        }
        else if( k>=-m && k<0)
        {

            double t = -(w*k) + (h); //y=kx+t
            double pert = t/double(linenum);
            for(int ii=0;ii<=linenum;ii++)
            {
                intersections.clear();
                QPointF p1(w,(w*k)+(pert*ii));
                QPointF p2(0,(pert*ii));
                if(pert * ii > h)
                {
                    p2 = QPointF(((h)-(pert*ii))/k,h);
                }
                else if( pert * ii < (-w*k))
                {
                    p1 = QPointF((-(pert*ii))/k,0);
                }
                QLineF l(p1+offset,p2+offset);

                setBrushpath(lins,l,intersections,path2,path);
            }
        }

    }
    else
    {

        if(int(angle)%180 == 0)
        {
            double t = h + k*w; //y=kx+t
            double pert = t/(linenum);
            for(double ii=-k*w-1;ii<h+1;ii += pert)
            {
                intersections.clear();
                QPointF p1(w,(ii));
                QPointF p2(0,(ii));
                QLineF l(p1+offset,p2+offset);
                setBrushpath(lins,l,intersections,path2,path,1);
            }
        }

        else
        {
            double pert = w/double(linenum);
            for(int ii=0;ii<=linenum;ii++)
            {
                intersections.clear();
                QPointF p1(pert*ii,h);
                QPointF p2(pert*ii,0);
                QLineF l(p1+offset,p2+offset);
                setBrushpath(lins,l,intersections,path2,path,2);
            }
        }

    }
    brushPath = path2;
    update();
}



bool MyGraphicsGroupItem::selectEvent(QPointF p)
{
    if(isSelected())
        return true;
    if(getRect().contains(p.toPoint()))
    {
          setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
          setSelected(true);
          return true;
    }
    setFlags(NULL);
    setSelected(false);
    return false;
}
