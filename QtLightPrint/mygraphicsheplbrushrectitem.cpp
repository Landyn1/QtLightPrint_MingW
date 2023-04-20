#include "mygraphicsheplbrushrectitem.h"
#include"mainWindow.h"
#include <QPen>
#include <QPainter>
#include <QPainterPath>
#include <QPainterPathStroker>
#include <QStyle>
#include <QStyleOptionGraphicsItem>
#include<QKeyEvent>
#include<math.h>
MyGraphicsHeplBrushRectItem::MyGraphicsHeplBrushRectItem():QGraphicsRectItem()
{

}
void MyGraphicsHeplBrushRectItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QPen pen;   // 定义一个画笔，设置画笔颜色和宽度
    //pen.setColor(QColor(0, 160, 230));
    QList<QGraphicsView*> list = scene()->views();
    QGraphicsView* view = list.first();
    double s = view->matrix().m11();
    pen.setWidthF(1/s);
    QPainterPath path;
    if(data(0).toInt() == -1)
    {
        pen.setColor(Qt::blue);
    }
    painter->setPen(pen);
    path.addRect(this->rect());
    QPainterPath path2;

    double k = tan(jiaodu*M_PI/180);//斜率
    int w = rect().width();
    int h = rect().height();

    //
    path2.addText(0,0,QFont("微软雅黑",48),"HP");
    //painter->drawPath(path2);

    if(jiaodu>=0&&jiaodu<=45)
    {
        double t = (w/2*k) + (h/2); //y=kx+t
        double pert = t/(midu/2);
        for(int i=-midu/2;i<midu/2;i++)
        {

            QPointF p1(w/2,(w/2*k)+(pert*i));
            QPointF p2(-w/2,(-w/2*k)+(pert*i));
            if(pert * i > (h/2)- (w/2*k))
            {
                p1 = QPointF(((h/2)-(pert*i))/k,h/2);
            }
            else if( pert * i < -(h/2)+(w/2*k))
            {
                p2 = QPointF(((-h/2)-(pert*i))/k,-h/2);
            }
            path.moveTo(p1);
            path.lineTo(p2);
            double x1 = fmin(p1.x(),p2.x());
            double x2 = fmax(p1.x(),p2.x());
            int s = (x2 - x1) * 2;
            double t = (x2-x1)/s;
            QList<QPointF> lists;
            for(int j=0;j<=s;j++)
            {

                double x = x1+t*j;
                double y = k*x+(pert*i);
                if(path2.contains(QPointF(x,y)))
                {
                    lists.append(QPointF(x,y));
                }
            }

            if(lists.length()>1)
            {
                path2.moveTo(lists[0]);

                for(int j=1;j<lists.length();j++)
                {
                    if(lists[j].x()-lists[j-1].x() - t >=  -0.01 && lists[j].x()-lists[j-1].x() - t <=  0.01)
                    {

                    }
                    else
                    {
                        path2.lineTo(lists[j-1]);
                        path2.moveTo(lists[j]);
                    }
                }
                path2.lineTo(lists[lists.length()-1]);
            }

        }

    }
    else if( jiaodu > 45 && jiaodu < 90)
    {
        double t = (w/2*k) + (h/2); //y=kx+t
        double pert = t/(midu/2);
        for(int i=-midu/2;i<midu/2;i++)
        {
            QPointF p1(((h/2)-(pert*i))/k,h/2);
            QPointF p2(((-h/2)-(pert*i))/k,-h/2);
            if(pert * i < (h/2)- (w/2*k))
            {
                p1 = QPointF(w/2,(w/2*k)+(pert*i));
            }
            else if( pert * i > -(h/2)+(w/2*k))
            {
                p2 = QPointF(-w/2,(-w/2*k)+(pert*i));
            }
            path.moveTo(p1);
            path.lineTo(p2);
        }
    }
    else if( jiaodu > 90 && jiaodu <135)
    {
        double t = -(w/2*k) + (h/2); //y=kx+t
        double pert = t/(midu/2);
        for(int i=-midu/2;i<midu/2;i++)
        {
            QPointF p1(((h/2)-(pert*i))/k,h/2);
            QPointF p2(((-h/2)-(pert*i))/k,-h/2);
            if(pert * i < (h/2)+(w/2*k))
            {
                p1 = QPointF(-w/2,(-w/2*k)+(pert*i));
            }
            else if( pert * i > -(h/2)+(-w/2*k))
            {
                p2 = QPointF(w/2,(w/2*k)+(pert*i));
            }
            path.moveTo(p1);
            path.lineTo(p2);
        }
    }
    else if( jiaodu >=135 && jiaodu < 180)
    {
        double t = -(w/2*k) + (h/2); //y=kx+t
        double pert = t/(midu/2);
        for(int i=-midu/2;i<midu/2;i++)
        {
            QPointF p1(w/2,(w/2*k)+(pert*i));
            QPointF p2(-w/2,(-w/2*k)+(pert*i));
            if(pert * i > (h/2)+(w/2*k))
            {
                p2 = QPointF(((h/2)-(pert*i))/k,h/2);
            }
            else if( pert * i < -(h/2)-(w/2*k))
            {
                p1 = QPointF(((-h/2)-(pert*i))/k,-h/2);
            }
            path.moveTo(p1);
            path.lineTo(p2);
        }
    }
    else if(jiaodu == 90)
    {

        double pert = w/(midu);
        for(int i=-midu/2;i<midu/2;i++)
        {
            QPointF p1(pert*i,h/2);
            QPointF p2(pert*i,-h/2);
            path.moveTo(p1);
            path.lineTo(p2);
        }

    }







    //painter->drawPolygon(f1);
//    qDebug()<<in.toList()<<endl;
//    QList<QPointF> lisst = in.toList();
//    QPainterPath p3 ;
//    for(int i=0;i<lisst.length();i++)
//    {
//        if(i%2 == 0)
//        {
//            p3.moveTo(lisst[i]);
//        }
//        else
//            p3.lineTo(lisst[i]);
//    }
    //painter->drawPath(path);
    pen.setColor(Qt::blue);
    painter->setPen(pen);
    painter->drawPath(path2);
    //qDebug()<<path2<<endl;
    //painter->drawPath(p3);
    //painter->drawPolygon(in);

}
