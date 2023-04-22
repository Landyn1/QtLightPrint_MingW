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
QPainterPath MyGraphicsPolygonItem::ViewPath()
{
    QPainterPath p;
    QPainterPath path = this->path;
    for (int i = 0; i < path.elementCount(); i++)
    {
        QPainterPath::Element element = path.elementAt(i);
        QPointF po = element;
        if (element.isMoveTo())
        {
            p.moveTo(mapToScene(po));
        }
        else if (element.isLineTo())
        {
            p.lineTo(mapToScene(po));
        }
    }
    return p;

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
    painter->drawPath(brushpath);
}

void MyGraphicsPolygonItem::setPath(QPainterPath path)
{
    this->path.clear();
    this->path = path;
    update();
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

bool MyGraphicsPolygonItem::set_brush(double jiaodu,int midu)
{
    brushpath.clear();
    QPainterPath path2;
    double k = tan(jiaodu*M_PI/180);//斜率
    double w = rect().width();
    double h = rect().height();
    QList<QPointF> jiaodians;
    path2 = path;
    QList<QLineF> lins;
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
                //ThirdCurve curve(lp1,c1,c2,lp2);
               // curves.append(curve);
                kc ++;
            }
        }
    }
    double m = double(h)/double(w);

    if(int(jiaodu)%90 != 0 ||  ((int(jiaodu)%180 == 0)&&(int(jiaodu)%90 != 0)))
    {
        if(k>0&&k<=m)
        {
            double t = (w/2*k) + (h/2); //y=kx+t
            double pert = t/(midu/2);

            for(int i=-midu/2;i<midu/2;i++)
            {
                jiaodians.clear();
                QPointF p1(w/2,(w/2*k)+(pert*i));
                QPointF p2(-w/2,(-w/2*k)+(pert*i));
                if(pert * i >= (h/2)- (w/2*k))
                {
                    p1 = QPointF(((h/2)-(pert*i))/k,h/2);
                }
                else if( pert * i <= -(h/2)+(w/2*k))
                {
                    p2 = QPointF(((-h/2)-(pert*i))/k,-h/2);
                }
                QLineF l(p1,p2);
                for(int i=0;i<lins.length();i++)
                {
                    QPointF intersectionPoint;
                    auto type = l.intersects(lins[i],&intersectionPoint);
                    if(type == QLineF::BoundedIntersection)
                    {
                        jiaodians.append(intersectionPoint);
                    }
                }
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
                if(jiaodians.length()>1)
                {
                    path2.moveTo(jiaodians[0]);
                    path2.lineTo(jiaodians[1]);
                }
            }

        }
        else if( k>m )
        {
            double t = (w/2*k) + (h/2); //y=kx+t
            double pert = t/(midu/2);
            for(int i=-midu/2;i<midu/2;i++)
            {
                jiaodians.clear();
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
                QLineF l(p1,p2);
                for(int i=0;i<lins.length();i++)
                {
                    QPointF intersectionPoint;
                    auto type = l.intersects(lins[i],&intersectionPoint);
                    if(type == QLineF::BoundedIntersection)
                    {
                        jiaodians.append(intersectionPoint);
                    }
                }
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
                if(jiaodians.length()>1)
                {
                    path2.moveTo(jiaodians[0]);
                    path2.lineTo(jiaodians[1]);
                }
            }

        }
        else if( k<-m)
        {

            double t = -(w/2*k) + (h/2); //y=kx+t
            double pert = t/(midu/2);
            for(int i=-midu/2;i<midu/2;i++)
            {
                jiaodians.clear();
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
                QLineF l(p1,p2);
                for(int i=0;i<lins.length();i++)
                {
                    QPointF intersectionPoint;
                    auto type = l.intersects(lins[i],&intersectionPoint);
                    if(type == QLineF::BoundedIntersection)
                    {
                        jiaodians.append(intersectionPoint);
                    }
                }
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
                if(jiaodians.length()>1)
                {
                    path2.moveTo(jiaodians[0]);
                    path2.lineTo(jiaodians[1]);
                }
            }
        }
        else if( k>=-m && k<0)
        {

            double t = -(w/2*k) + (h/2); //y=kx+t
            double pert = t/(midu/2);
            for(int i=-midu/2;i<midu/2;i++)
            {
                jiaodians.clear();
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
                QLineF l(p1,p2);
                for(int i=0;i<lins.length();i++)
                {
                    QPointF intersectionPoint;
                    auto type = l.intersects(lins[i],&intersectionPoint);
                    if(type == QLineF::BoundedIntersection)
                    {
                        jiaodians.append(intersectionPoint);
                    }
                }
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
                if(jiaodians.length()>1)
                {
                    path2.moveTo(jiaodians[0]);
                    path2.lineTo(jiaodians[1]);
                }
            }
        }

    }
    else
    {

        if(int(jiaodu)%180 == 0)
        {
            double t = (w/2*k) + (h/2); //y=kx+t
            double pert = t/(midu/2);
            for(int i=-midu/2;i<midu/2;i++)
            {
                jiaodians.clear();
                QPointF p1(-w/2,pert*i);
                QPointF p2(w/2,pert*i);
                QLineF l(p1,p2);
                for(int i=0;i<lins.length();i++)
                {
                    QPointF intersectionPoint;
                    auto type = l.intersects(lins[i],&intersectionPoint);
                    if(type == QLineF::BoundedIntersection)
                    {
                        jiaodians.append(intersectionPoint);
                    }
                }

                for(int i = 1;i<jiaodians.length();i++)
                {
                    for(int j=0;j<jiaodians.length()-i;j++)
                    {
                        if(jiaodians[j].y()>jiaodians[j+1].y())
                        {
                            QPointF tm = jiaodians[j];
                            jiaodians[j] = jiaodians[j+1];
                            jiaodians[j+1] = tm;
                        }
                    }
                }
                qDebug()<<jiaodians<<endl;
                if(jiaodians.length()>1)
                {
                    path2.moveTo(jiaodians[0]);
                    path2.lineTo(jiaodians[1]);
                }
            }
        }
        else
        {
            double pert = w/(midu);
            for(int i=-midu/2;i<midu/2;i++)
            {
                jiaodians.clear();
                QPointF p1(pert*i,h/2);
                QPointF p2(pert*i,-h/2);
                QLineF l(p1,p2);
                for(int i=0;i<lins.length();i++)
                {
                    QPointF intersectionPoint;
                    auto type = l.intersect(lins[i],&intersectionPoint);
                    if(type == QLineF::BoundedIntersection)
                    {
                        jiaodians.append(intersectionPoint);
                    }
                }

                for(int i = 1;i<jiaodians.length();i++)
                {
                    for(int j=0;j<jiaodians.length()-i;j++)
                    {
                        if(jiaodians[j].y()>jiaodians[j+1].y())
                        {
                            QPointF tm = jiaodians[j];
                            jiaodians[j] = jiaodians[j+1];
                            jiaodians[j+1] = tm;
                        }
                    }
                }
                if(jiaodians.length()>1)
                {
                    path2.moveTo(jiaodians[0]);
                    path2.lineTo(jiaodians[1]);
                }
            }
        }

    }
    brushpath = path2;
    this->jiaodu = jiaodu;
    this->midu = midu;
    update();
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
