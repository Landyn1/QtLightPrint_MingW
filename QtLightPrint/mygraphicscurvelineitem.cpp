#include "mygraphicscurvelineitem.h"
#include"MyGraphicsView.h"
MyGraphicsCurveLineItem::MyGraphicsCurveLineItem(QGraphicsPathItem *parent):QGraphicsPathItem(parent)
{

}

MyGraphicsCurveLineItem::~MyGraphicsCurveLineItem()
{

}


void MyGraphicsCurveLineItem::rotateY()
{
    double rooty = getRect().y()+(getRect().height()/2);
    rooty = rooty-pos().y();
    QPainterPath p;
    QPainterPath path = this->path();

    QPointF lp1,lp2,c1,c2;
    int kl = 0;
    int kc = 0;
    for (int i = 0; i < path.elementCount(); i++)
    {
        QPainterPath::Element element = path.elementAt(i);
        QPointF po = element;
        int x1,y1;
        x1 = po.x();
        y1 = rooty*2-po.y();
        po.setX(x1);
        po.setY(y1);
        if (element.isMoveTo())
        {
            lp1 = po;
            kl = 0;
            p.moveTo(po);
        }
        else if (element.isLineTo())
        {
            if(kl == 0)
            {
                lp2 = po;
                p.lineTo(po);
                kl++;
            }
            else
            {
                lp1 = lp2;
                lp2 = po;
                p.lineTo(po);
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
                p.cubicTo(c1,c2,lp2);
                kc ++;
                lp1 = lp2;
            }
        }
    }
    this->setPath(p);
}

void MyGraphicsCurveLineItem::rotateX()
{
    double rootx = getRect().x()+(getRect().width()/2);
    rootx = rootx-pos().x();
    QPainterPath p;
    QPainterPath path = this->path();

    QPointF lp1,lp2,c1,c2;
    int kl = 0;
    int kc = 0;
    for (int i = 0; i < path.elementCount(); i++)
    {
        QPainterPath::Element element = path.elementAt(i);
        QPointF po = element;
        int x1,y1;
        x1 = rootx*2-po.x();
        y1 = po.y();
        po.setX(x1);
        po.setY(y1);
        if (element.isMoveTo())
        {
            lp1 = po;
            kl = 0;
            p.moveTo(po);
        }
        else if (element.isLineTo())
        {
            if(kl == 0)
            {
                lp2 = po;
                p.lineTo(po);
                kl++;
            }
            else
            {
                lp1 = lp2;
                lp2 = po;
                p.lineTo(po);
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
                p.cubicTo(c1,c2,lp2);
                kc ++;
                lp1 = lp2;
            }
        }
    }
    this->setPath(p);
}


QPainterPath MyGraphicsCurveLineItem::ViewPath(int kk)
{
    QPainterPath p;
    QPainterPath path = this->path();
    int k=0;
    QPointF p0,c1,c2,p3;
    for (int i = 0; i < path.elementCount(); i++)
    {
        QPainterPath::Element element = path.elementAt(i);
        QPointF po = element;
        QPointF po2 = mapToScene(po);
        if (element.isMoveTo())
        {
            p.moveTo(mapToScene(po));
            p0 = po2;
        }
        else if (element.isLineTo())
        {
            p.lineTo(mapToScene(po));
            p0 = po2;
        }
        else if(element.isCurveTo())
        {

            c1 = po2;
            k++;
            //path2.cubicTo(po2);
        }
        else
        {
            if(k%3 == 1)
            {
                c2 = po2;
                k++;
            }
            else if(k%3 == 2)
            {
                p3 = po2;
                QList<QPointF> list;
                for(int i=0;i<=5;i++)
                {
                    double temp = 0.2*i;
                    double tx = f(temp,p0.x(),c1.x(),c2.x(),p3.x());
                    double ty = f(temp,p0.y(),c1.y(),c2.y(),p3.y());
                    list.append(QPointF(tx,ty));
                }
                double s = 0;
                for(int i=0;i<5;i++)
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
                double dpiX = QApplication::primaryScreen()->physicalDotsPerInchX();
                double  t = (dpiX * 10) / 254;   //1mm = t px
                double s_mm = s/t;
                int num = s_mm / 0.1 ; //每隔0.1毫米一个单位;

                for(int i=1;i<=num;i++)
                {
                    double temp = (double(1)/double(num))*i;
                    double tx = f(temp,p0.x(),c1.x(),c2.x(),p3.x());
                    double ty = f(temp,p0.y(),c1.y(),c2.y(),p3.y());
                    p.lineTo(tx,ty);
                }
                k++;
                p0=po2;
            }

        }
    }
    return p;

}
void MyGraphicsCurveLineItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
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
            p.lineTo(symmetryPoint(ctl_next,endP));
        }

        else
        {
            p.moveTo(symmetryPoint(ctl_next,startP));
            p.lineTo(startP);
        }
        painter->drawPath(p);
    }
}
//获取p1关于p2的对称点
QPointF MyGraphicsCurveLineItem::symmetryPoint(QPointF p1 , QPointF p2)
{
    return QPointF(p2.x()*2-p1.x(),p2.y()*2-p1.y());
}


bool MyGraphicsCurveLineItem::selectEvent(QPointF p,int kk)
{

    if(kk == 1)
    {
        setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
        setSelected(true);
        return true;
    }
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
                //判断点（tx，ty）
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
//获取外接矩形
QRect MyGraphicsCurveLineItem::getRect()
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
        //根据极点和0,1判断
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

             //三次贝塞尔曲线导数 y=ax^2+bx+c
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
    qDebug()<<minx<<miny<<maxx<<maxy<<endl;
    return QRect(list[0],list[1],list[2]-list[0],list[3]-list[1]);
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


