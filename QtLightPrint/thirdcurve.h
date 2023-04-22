#ifndef THIRDCURVE_H
#define THIRDCURVE_H
#include<math.h>
#include<qwidget.h>
class ThirdCurve
{
public:
    ThirdCurve(QPointF st,QPointF c1,QPointF c2, QPointF end);
    double f(double t,double p0,double p1,double p2,double p3)
    {
        return pow((1-t),3)*p0+3*t*pow((1-t),2)*p1 + 3*t*t*(1-t)*p2 + pow(t,3)*p3;
    }
    bool isOnLine(QLineF l , QPointF p);
    QList<QPointF> jiaodian(QLineF l);
    QPointF start = QPointF();
    QPointF c1 = QPointF();
    QPointF c2;
    QPointF end;
};

#endif // THIRDCURVE_H
