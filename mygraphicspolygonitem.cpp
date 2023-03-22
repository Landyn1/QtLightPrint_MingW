#include "mygraphicspolygonitem.h"
#include<complex>
#include<math.h>
#include"MyGraphicsView.h"
MyGraphicsPolygonItem::MyGraphicsPolygonItem(QGraphicsRectItem *parent) : QGraphicsRectItem(parent)
{

}

MyGraphicsPolygonItem::~MyGraphicsPolygonItem()
{

}


void MyGraphicsPolygonItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{

    QPen pen;   // 定义一个画笔，设置画笔颜色和宽度
   //pen.setColor(QColor(0, 160, 230));
    QList<QGraphicsView*> list = scene()->views();
    QGraphicsView* view = list.first();
    double s = view->matrix().m11();
    pen.setWidthF(1/s);
    painter->setPen(pen);
    //QPolygonF p;
    QPainterPath p;
    p.moveTo(QPointF(0,rect().height()/2));
    int bili1 = rect().width()*100/rect().height();
    double bili = double(bili1)/100;
    int t = 360*100/num;
    double tt = double(t)/100;
    double ttt = tt;
    double r = rect().height()/2;
    for(int i=1;i<num;i++)
    {
        if(tt <= 90)
        {
            double x = r*sin(tt*M_PI/180);
            double y = r*cos(tt*M_PI/180);
            p.lineTo(QPointF(x*bili,y));
        }

        else if(tt>90&&tt<=180)
        {
            double x,y;
            double temp = tt-90;
            x = r*cos(temp*M_PI/180);
            y = -r*sin(temp*M_PI/180);
            p.lineTo(QPointF(x*bili,y));
        }

        else if(tt>180&&tt<=270)
        {
            double x,y;
            double temp = tt-180;
            x = -r*sin(temp*M_PI/180);
            y = -r*cos(temp*M_PI/180);
            p.lineTo(QPointF(x*bili,y));
        }

        else if(tt>270&&tt<360)
        {
            double x,y;
            double temp = tt-270;
            x = -r*cos(temp*M_PI/180);
            y = r*sin(temp*M_PI/180);
            p.lineTo(QPointF(x*bili,y));
        }
        tt = tt + ttt;
    }

    p.lineTo(QPointF(0,rect().height()/2));
    painter->drawPath(p);
}
