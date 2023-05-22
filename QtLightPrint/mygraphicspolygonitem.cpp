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
    path.clear();
    path = brushpath;
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

//根据边数和外接矩形确定多边形的path
void MyGraphicsPolygonItem::setDefault_Path()
{
    path.clear();
    path.moveTo(QPointF(0,rect().height()/2));
    int proportion1 = rect().width()*100/rect().height();
    double proportion = double(proportion1)/100; //w/h
    int t = 360*100/num;
    double tt = double(t)/100; //将360分为num份
    double ttt = tt; //复制这个参数， 作为叠加参数
    double r = rect().height()/2;
    for(int i=1;i<num;i++)
    {
        if(tt <= 90)
        {
            double x = r*sin(tt*M_PI/180);
            double y = r*cos(tt*M_PI/180);
            path.lineTo(QPointF(x*proportion,y));
        }

        else if(tt>90&&tt<=180)
        {
            double x,y;
            double temp = tt-90;
            x = r*cos(temp*M_PI/180);
            y = -r*sin(temp*M_PI/180);
            path.lineTo(QPointF(x*proportion,y));
        }

        else if(tt>180&&tt<=270)
        {
            double x,y;
            double temp = tt-180;
            x = -r*sin(temp*M_PI/180);
            y = -r*cos(temp*M_PI/180);
            path.lineTo(QPointF(x*proportion,y));
        }

        else if(tt>270&&tt<360)
        {
            double x,y;
            double temp = tt-270;
            x = -r*cos(temp*M_PI/180);
            y = r*sin(temp*M_PI/180);
            path.lineTo(QPointF(x*proportion,y));
        }
        tt = tt + ttt;
    }
    path.lineTo(QPointF(0,rect().height()/2));

}

void MyGraphicsPolygonItem::setLinsAndCurves(QPainterPath path2, QList<QLineF> &lins)
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

void MyGraphicsPolygonItem::setBrushpath(QList<QLineF> lins, QLineF l, QList<QPointF> intersections, QPainterPath &path2, int k)
{

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
    if(intersections.length()>1)
    {
        path2.moveTo(intersections[0]);
        path2.lineTo(intersections[1]);
    }
}
bool MyGraphicsPolygonItem::set_brush(double angle,int linenum)
{
    brushpath.clear();
    this->angle = angle;
    this->linenum = linenum;
    if(linenum == 0)
        return true;
    QPainterPath path2;
    double k = tan(angle*M_PI/180);//斜率
    double w = rect().width();
    double h = rect().height();
    QList<QPointF> intersections;
    QList<QLineF> lins;
    setLinsAndCurves(this->path,lins);
    double m = double(h)/double(w);
    if(int(angle)%90 != 0 ||  ((int(angle)%180 == 0)&&(int(angle)%90 != 0)))
    {
        if(k>0&&k<=m)
        {
            double t = (w/2*k) + (h/2); //y=kx+t
            double pert = t/(linenum/2);

            for(int i=-linenum/2;i<linenum/2;i++)
            {
                intersections.clear();
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
                setBrushpath(lins,l,intersections,path2);
            }

        }
        else if( k>m )
        {
            double t = (w/2*k) + (h/2); //y=kx+t
            double pert = t/(linenum/2);
            for(int i=-linenum/2;i<linenum/2;i++)
            {
                intersections.clear();
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
                setBrushpath(lins,l,intersections,path2);
            }

        }
        else if( k<-m)
        {

            double t = -(w/2*k) + (h/2); //y=kx+t
            double pert = t/(linenum/2);
            for(int i=-linenum/2;i<linenum/2;i++)
            {
                intersections.clear();
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
                setBrushpath(lins,l,intersections,path2);
            }
        }
        else if( k>=-m && k<0)
        {

            double t = -(w/2*k) + (h/2); //y=kx+t
            double pert = t/(linenum/2);
            for(int i=-linenum/2;i<linenum/2;i++)
            {
                intersections.clear();
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
                setBrushpath(lins,l,intersections,path2);
            }
        }

    }
    else
    {

        if(int(angle)%180 == 0)
        {
            double t = (w/2*k) + (h/2); //y=kx+t
            double pert = t/(linenum/2);
            for(int i=-linenum/2;i<linenum/2;i++)
            {
                intersections.clear();
                QPointF p1(-w/2,pert*i);
                QPointF p2(w/2,pert*i);
                QLineF l(p1,p2);
                setBrushpath(lins,l,intersections,path2);
            }
        }
        else
        {
            double pert = w/(linenum);
            for(int i=-linenum/2;i<linenum/2;i++)
            {
                intersections.clear();
                QPointF p1(pert*i,h/2);
                QPointF p2(pert*i,-h/2);
                QLineF l(p1,p2);
                setBrushpath(lins,l,intersections,path2);
            }
        }

    }
    brushpath = path2;
    update();
}

bool MyGraphicsPolygonItem::selectEvent(QPointF p,int k)
{

    if(k == 1)
    {
        setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
        setSelected(true);
        return true;
    }
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
    QPoint leftbuttom(10000,10000),righttop(-10000,-10000);
    for (int i = 0; i < path.elementCount() ;i++)
    {
        QPointF p1 = path.elementAt(i);
        if(leftbuttom.x()>p1.toPoint().x())
        {
            leftbuttom.setX( p1.toPoint().x());
        }
        if(leftbuttom.y()>p1.toPoint().y())
        {
            leftbuttom.setY(p1.toPoint().y());
        }
        if(righttop.x()<p1.toPoint().x())
        {
            righttop.setX(p1.toPoint().x());
        }
        if(righttop.y()<p1.toPoint().y())
        {
            righttop.setY(p1.toPoint().y());
        }
    }
    QPoint pos = this->pos().toPoint();
    x = leftbuttom.x()+pos.x();
    y = leftbuttom.y()+pos.y();
    w = righttop.x()-leftbuttom.x();
    h = righttop.y()-leftbuttom.y();
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
