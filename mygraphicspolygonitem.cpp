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
    if(data(0).toInt() == -1)
    {
        pen.setColor(Qt::blue);
    }
    painter->setPen(pen);

    painter->drawPath(path);
}

void MyGraphicsPolygonItem::setPath(QPainterPath path)
{
    this->path.clear();
    this->path = path;
}

void MyGraphicsPolygonItem::setDefault_Path()
{
    path.clear();
    path.moveTo(QPointF(0,rect().height()/2));
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
            path.lineTo(QPointF(x*bili,y));
        }

        else if(tt>90&&tt<=180)
        {
            double x,y;
            double temp = tt-90;
            x = r*cos(temp*M_PI/180);
            y = -r*sin(temp*M_PI/180);
            path.lineTo(QPointF(x*bili,y));
        }

        else if(tt>180&&tt<=270)
        {
            double x,y;
            double temp = tt-180;
            x = -r*sin(temp*M_PI/180);
            y = -r*cos(temp*M_PI/180);
            path.lineTo(QPointF(x*bili,y));
        }

        else if(tt>270&&tt<360)
        {
            double x,y;
            double temp = tt-270;
            x = -r*cos(temp*M_PI/180);
            y = r*sin(temp*M_PI/180);
            path.lineTo(QPointF(x*bili,y));
        }
        tt = tt + ttt;
    }
    path.lineTo(QPointF(0,rect().height()/2));
}


bool MyGraphicsPolygonItem::selectEvent(QPointF p)
{
    if(isSelected())
        return true;

    for (int i = 0; i < path.elementCount() - 1; i++)
    {
        QPointF p1 = path.elementAt(i);
        QPointF p2 = path.elementAt(i+1);
        QLine l(p1.toPoint(),p2.toPoint());
        if(isOnLine(l,p.toPoint()))
        {

            this->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
            this->setSelected(true);
            return true;
        }
    }
    this->setFlags(NULL);
    this->setSelected(false);
    return false;

}

QRect MyGraphicsPolygonItem::getRect()
{
    int x,y,w,h;
    QPoint zuoxia(10000,10000),youshang(-10000,-10000);

    for (int i = 0; i < path.elementCount() ;i++)
    {
        QPointF p1 = path.elementAt(i);
        if(zuoxia.x()>p1.toPoint().x())
        {
            zuoxia.setX( p1.toPoint().x());
        }
        if(zuoxia.y()>p1.toPoint().y())
        {
            zuoxia.setY(p1.toPoint().y());
        }
        if(youshang.x()<p1.toPoint().x())
        {
            youshang.setX(p1.toPoint().x());
        }
        if(youshang.y()<p1.toPoint().y())
        {
            youshang.setY(p1.toPoint().y());
        }
    }
    QPoint pos = this->pos().toPoint();
    x = zuoxia.x()+pos.x();
    y = zuoxia.y()+pos.y();
    w = youshang.x()-zuoxia.x();
    h = youshang.y()-zuoxia.y();
    return QRect(x,y,w,h);
}
bool MyGraphicsPolygonItem::isOnLine(QLine l , QPoint p)
{
    qreal ab = (l.x1() -l.x2())*(l.x1()-l.x2()) + (l.y1()-l.y2())*(l.y1()-l.y2());
    ab = sqrt(ab);
    qreal ac = (l.x1()-p.x())*(l.x1()-p.x()) + (l.y1()-p.y())*(l.y1()-p.y());
    ac = sqrt(ac);
    qreal bc = (l.x2()-p.x())*(l.x2()-p.x()) + (l.y2()-p.y())*(l.y2()-p.y());
    bc = sqrt(bc);
    qreal x = ac+bc-ab;
    if(x<0.1&&x>-0.1)
    {
        return true;
    }
    return false;
}

void MyGraphicsPolygonItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{

}
void MyGraphicsPolygonItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{

}
void MyGraphicsPolygonItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}
