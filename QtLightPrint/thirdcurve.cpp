#include "thirdcurve.h"
#include"QDebug"
#include<math.h>
#include<QApplication>
#include"MyGraphicsView.h"
ThirdCurve::ThirdCurve(QPointF st,QPointF c1,QPointF c2, QPointF end)
{
    this->start = st;
    this->c1 = c1;
    this->c2 = c2;
    this->end = end;
}

QList<QPointF> ThirdCurve::intersection(QLineF l)
{
    QPainterPath path1,path2;
    path1.moveTo(start);
    path1.cubicTo(c1,c2,end);

    path2.moveTo(l.p1());
    path2.lineTo(l.p2());
    QList<QPointF> list,intersectionss;
    for(int i=0;i<=5;i++)
    {
        double temp = 0.2*i;
        double tx = f(temp,start.x(),c1.x(),c2.x(),end.x());
        double ty = f(temp,start.y(),c1.y(),c2.y(),end.y());
        list.append(QPointF(tx,ty));
    }
    double s = 0;
    for(int i=0;i<list.length()-1;i++)
    {
        double x1,x2,y1,y2;
        x1 = list[i].x();
        y1 = list[i].y();
        x2 = list[i+1].x();
        y2 = list[i+1].y();
        double m = (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
        m = sqrt(m);
        s += m;
    }

    int num = s ; //10;
    QPointF p1,p2;
    p1 = QPointF(f(0,start.x(),c1.x(),c2.x(),end.x()),f(0,start.y(),c1.y(),c2.y(),end.y()));
    for(int i=1;i<=num;i++)
    {
        double temp = (double(1)/double(num))*i;
        double tx = f(temp,start.x(),c1.x(),c2.x(),end.x());
        double ty = f(temp,start.y(),c1.y(),c2.y(),end.y());
        p2 = QPointF(tx,ty);
        QLineF l2(p1,p2);
        QPointF intersectionPoint;
        auto type = l.intersects(l2,&intersectionPoint);
        if(type == QLineF::BoundedIntersection)
        {
            intersectionss.append(intersectionPoint);
        }
        p1 = p2;

    }

    return intersectionss;
}
bool ThirdCurve::isOnLine(QLineF l , QPointF p)
{
    qreal ab = (l.x1() -l.x2())*(l.x1()-l.x2()) + (l.y1()-l.y2())*(l.y1()-l.y2());
    ab = sqrt(ab);
    qreal ac = (l.x1()-p.x())*(l.x1()-p.x()) + (l.y1()-p.y())*(l.y1()-p.y());
    ac = sqrt(ac);
    qreal bc = (l.x2()-p.x())*(l.x2()-p.x()) + (l.y2()-p.y())*(l.y2()-p.y());
    bc = sqrt(bc);
    qreal x = ac+bc-ab;
    if(x>-0.0001&&x<0.0001)
    {
        return true;
    }
    return false;
}
