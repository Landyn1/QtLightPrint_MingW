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
#include"thirdcurve.h"
#include"mygraphicscodeitem.h"
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
    int w = rect().width()*2;
    int h = rect().height()*2;

    //
    MyGraphicsCodeItem *item = new MyGraphicsCodeItem();
    item->setPathByStr("text","QRCode");
    double ww = item->path().boundingRect().width();
    double hh = item->path().boundingRect().height();
    item->setPos(QPointF(0,0)-QPointF(ww/2,hh/2));
    QList<QPointF> jiaodians;
    path2.addText(-100,0,QFont("微软雅黑",48),"HP");
    //path2 = item->path();
    QList<QLineF> lins;
    QList<ThirdCurve> curves;
    QPointF lp1,lp2,c1,c2;
    int kl = 0;
    int kc = 0;
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
        else if(element.isCurveTo())
        {
            if(kl != 0)
                lp1 = lp2;
            c1 = po;
            kc++;
        }
        else
        {
            if(kc%3==1)
            {
                c2 = po;
                kc++;
            }
            else if(kc%3 == 2)
            {
                lp2 = po;
                //curve lp1,c1,c2,lp2
                //qDebug()<<lp1<<c1<<c2<<lp2<<endl;
                ThirdCurve curve(lp1,c1,c2,lp2);
                curves.append(curve);
                kc ++;
            }
        }
    }
    //qDebug()<<path2<<lins<<endl;


//    for(int i=0;i<lins.length();i++)
//    {
//                QPointF intersectionPoint;
//                auto type = QLineF(0,0,200,-100).intersect(lins[i],&intersectionPoint);
//                if(type == QLineF::BoundedIntersection)
//                {
//                    qDebug()<<intersectionPoint<<endl;
//                }
//    }

    painter->drawLine(0,0,200,-100);



    if(jiaodu>=0&&jiaodu<=45)
    {
        double t = (w/2*k) + (h/2); //y=kx+t
        double pert = t/(midu/2);
        for(int i=-midu/2;i<midu/2;i++)
        {
            jiaodians.clear();

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
            QLineF l(p1,p2);
            for(int i=0;i<curves.length();i++)
            {
                QList<QPointF> cjiaodians = curves[i].jiaodian(l);
                for(int j = 0;j<cjiaodians.length();j++)
                {
                    if(cjiaodians[j]!=QPointF(-20000,-20000) )
                    {
                         jiaodians.append(cjiaodians[j]);
                    }
                }
            }
            for(int i=0;i<lins.length();i++)
            {
                QPointF intersectionPoint;
                auto type = l.intersect(lins[i],&intersectionPoint);
                if(type == QLineF::BoundedIntersection)
                {
                    jiaodians.append(intersectionPoint);
                }
            }
            qDebug()<<jiaodians.length()<<endl;
            for(int i = 1;i<jiaodians.length();i++)
            {
                for(int j=0;j<jiaodians.length()-i;j++)
                {
                    if(jiaodians[j].x()>jiaodians[j+1].x())
                    {
                        QPointF tm = jiaodians[j];
                        jiaodians[j] = jiaodians[j+1];
                        jiaodians[j+1] = tm;
                    }
                }
            }
            for(int i = 0;i<jiaodians.length()-1;i++)
            {
                if(path2.contains((jiaodians[i]+QPointF(0.1,0.1))) && path2.contains((jiaodians[i+1]-QPointF(0.1,0.1))) )
                {
                    path2.moveTo(jiaodians[i]);
                    path2.lineTo(jiaodians[i+1]);
                }
            }


//            double x1 = fmin(p1.x(),p2.x());
//            double x2 = fmax(p1.x(),p2.x());
//            int s = (x2 - x1) * 2;
//            double t = (x2-x1)/s;
//            QList<QPointF> lists;
//            for(int j=0;j<=s;j++)
//            {

//                double x = x1+t*j;
//                double y = k*x+(pert*i);
//                if(path2.contains(QPointF(x,y)))
//                {
//                    lists.append(QPointF(x,y));
//                }
//            }

//            if(lists.length()>1)
//            {
//                path2.moveTo(lists[0]);

//                for(int j=1;j<lists.length();j++)
//                {
//                    if(lists[j].x()-lists[j-1].x() - t >=  -0.01 && lists[j].x()-lists[j-1].x() - t <=  0.01)
//                    {

//                    }
//                    else
//                    {
//                        path2.lineTo(lists[j-1]);
//                        path2.moveTo(lists[j]);
//                    }
//                }
//                path2.lineTo(lists[lists.length()-1]);
//            }

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
    //painter->drawPath(path);
    pen.setColor(Qt::blue);
    painter->setPen(pen);
    painter->drawPath(path2);

}
