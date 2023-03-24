#include "mygraphicscurvelineitem.h"
#include"MyGraphicsView.h"
MyGraphicsCurveLineItem::MyGraphicsCurveLineItem(QGraphicsPathItem *parent):QGraphicsPathItem(parent)
{

}

MyGraphicsCurveLineItem::~MyGraphicsCurveLineItem()
{

}
void MyGraphicsCurveLineItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QPen pen;   // 定义一个画笔，设置画笔颜色和宽度
   //pen.setColor(QColor(0, 160, 230));
    QList<QGraphicsView*> list = scene()->views();
    QGraphicsView* view = list.first();
    double s = view->matrix().m11();
    pen.setWidthF(1/s);
    painter->setPen(pen);
    painter->drawPath(this->path());

    if(ispainting)
    {
        QPainterPath p;
        QPen pen;
        pen.setColor(Qt::blue);
        pen.setWidthF(0.8);
        pen.setStyle(Qt::DashLine);
        painter->setPen(pen);
        if(isfirst == false)
        {
            p.moveTo(ctl_pre);
            p.lineTo(startP);
            p.moveTo(ctl_next);
            p.lineTo(duichengdian(ctl_next,endP));
        }

        else
        {
            p.moveTo(duichengdian(ctl_next,startP));
            p.lineTo(startP);
        }
        painter->drawPath(p);
    }
}
QPointF MyGraphicsCurveLineItem::duichengdian(QPointF p1 , QPointF p2)
{
    return QPointF(p2.x()*2-p1.x(),p2.y()*2-p1.y());
}


bool MyGraphicsCurveLineItem::selectEvent(QPointF p)
{

    if(isSelected())
        return true;
    QPainterPath path = this->path();
    QPointF p0,p1,p2,p3;
    int k=0;
    for (int i = 0; i < path.elementCount(); i++)
    {
        QPainterPath::Element element = path.elementAt(i);
        QPointF po = element;
        if (element.isMoveTo())
        {
            p0 = po;
        }
        else if (element.isCurveTo())
        {
            p1 = po;
        }
        else
        {
            if(k == 2)
                p2 = po;
            else if(k == 3)
                p3 = po;
            else if(k%3 == 2)
                p2 = po;
            else if(k%3 == 0)
            {
                p0 = p3;
                p3 = po;
            }

        }
        if( k >0 && k % 3 == 0)
        {

            for(int i=1;i<=100;i++)
            {
                double temp = 0.01*i;
                double tx = f(temp,p0.x(),p1.x(),p2.x(),p3.x());
                double ty = f(temp,p0.y(),p1.y(),p2.y(),p3.y());

                if(tx-p.x()>-2 && tx-p.x() < 2 && ty-p.y()>-2 && ty-p.y()<2)
                {
                    setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
                    setSelected(true);
                    return true;
                }
            }
        }


        k++;
    }

    setFlags(NULL);
    setSelected(false);
    return false;

}

QList<double> MyGraphicsCurveLineItem::getRect()
{
    QPainterPath path = this->path();
    QPointF p0,p1,p2,p3;
    int k=0;
    double minx = 10000,maxx = -10000,miny = 10000,maxy = -10000;
    for (int i = 0; i < path.elementCount(); i++)
    {
        QPainterPath::Element element = path.elementAt(i);
        QPointF po = element;
        if (element.isMoveTo())
        {
            p0 = po;
        }
        else if (element.isCurveTo())
        {
            p1 = po;
        }
        else
        {
            if(k == 2)
                p2 = po;
            else if(k == 3)
                p3 = po;
            else if(k%3 == 2)
                p2 = po;
            else if(k%3 == 0)
            {
                p0 = p3;
                p3 = po;
            }
        }
        if( k >0 && k % 3 == 0)
        {
             if(minx>f(0,p0.x(),p1.x(),p2.x(),p3.x()))
             {
                 minx = f(0,p0.x(),p1.x(),p2.x(),p3.x());
             }
             if(minx > f(1,p0.x(),p1.x(),p2.x(),p3.x()))
             {
                 minx = f(1,p0.x(),p1.x(),p2.x(),p3.x());
             }
             if(maxx<f(0,p0.x(),p1.x(),p2.x(),p3.x()))
             {
                 maxx = f(0,p0.x(),p1.x(),p2.x(),p3.x());
             }
             if(maxx < f(1,p0.x(),p1.x(),p2.x(),p3.x()))
             {
                 maxx = f(1,p0.x(),p1.x(),p2.x(),p3.x());
             }
             if(miny>f(0,p0.y(),p1.y(),p2.y(),p3.y()))
             {
                 miny = f(0,p0.y(),p1.y(),p2.y(),p3.y());
             }
             if(miny > f(1,p0.y(),p1.y(),p2.y(),p3.y()))
             {
                 miny = f(1,p0.y(),p1.y(),p2.y(),p3.y());
             }
             if(maxy<f(0,p0.y(),p1.y(),p2.y(),p3.y()))
             {
                 maxy = f(0,p0.y(),p1.y(),p2.y(),p3.y());
             }
             if(maxy < f(1,p0.y(),p1.y(),p2.y(),p3.y()))
             {
                 maxy = f(1,p0.y(),p1.y(),p2.y(),p3.y());
             }

             double a,b,c;
             a = 3*(p3.x()-3*p2.x()+3*p1.x()-p0.x());
             b = 6*(p2.x()-2*p1.x()+p0.x());
             c = 3*(p1.x()-p0.x());
             if(getDeta(a,b,c)>0)
             {
                   double deta = getDeta(a,b,c);
                   double t1 = ((-b)+pow(deta,0.5))/(2*a);
                   double t2 = ((-b)-pow(deta,0.5))/(2*a);
                   if(t1>=0&&t1<=1&& minx > f(t1,p0.x(),p1.x(),p2.x(),p3.x()) )
                   {
                       minx = f(t1,p0.x(),p1.x(),p2.x(),p3.x());
                   }
                   if(t2>=0&&t2<=1&& minx > f(t2,p0.x(),p1.x(),p2.x(),p3.x()))
                   {
                       minx = f(t2,p0.x(),p1.x(),p2.x(),p3.x());
                   }
                   if(t1>=0&&t1<=1&&maxx < f(t1,p0.x(),p1.x(),p2.x(),p3.x()))
                   {
                       maxx = f(t1,p0.x(),p1.x(),p2.x(),p3.x());
                   }
                   if(t2>=0&&t2<=1&&maxx < f(t2,p0.x(),p1.x(),p2.x(),p3.x()))
                   {
                       maxx = f(t2,p0.x(),p1.x(),p2.x(),p3.x());
                   }
             }
             a = 3*(p3.y()-3*p2.y()+3*p1.y()-p0.y());
             b = 6*(p2.y()-2*p1.y()+p0.y());
             c = 3*(p1.y()-p0.y());

             if(getDeta(a,b,c)>0)
             {
                   double deta = getDeta(a,b,c);
                   double t1 = ((-b)+pow(deta,0.5))/(2*a);
                   double t2 = ((-b)-pow(deta,0.5))/(2*a);
                   if(t1>=0&&t1<=1&&miny > f(t1,p0.y(),p1.y(),p2.y(),p3.y()))
                   {
                       miny = f(t1,p0.y(),p1.y(),p2.y(),p3.y());
                   }
                   if(t2>=0&&t2<=1&&miny > f(t2,p0.y(),p1.y(),p2.y(),p3.y()))
                   {
                       miny = f(t2,p0.y(),p1.y(),p2.y(),p3.y());
                   }
                   if(t1>=0&&t1<=1&&maxy < f(t1,p0.y(),p1.y(),p2.y(),p3.y()))
                   {
                       maxy = f(t1,p0.y(),p1.y(),p2.y(),p3.y());
                   }
                   if(t2>=0&&t2<=1&&maxy < f(t2,p0.y(),p1.y(),p2.y(),p3.y()))
                   {
                       maxy = f(t2,p0.y(),p1.y(),p2.y(),p3.y());
                   }

             }
        }
        k++;
    }
    QList<double> list;
    list.append(minx+this->pos().x());
    list.append(miny+this->pos().y());
    list.append(maxx+this->pos().x());
    list.append(maxy+this->pos().y());
    return list;
}

void MyGraphicsCurveLineItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{

}
void MyGraphicsCurveLineItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{

}
void MyGraphicsCurveLineItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}


