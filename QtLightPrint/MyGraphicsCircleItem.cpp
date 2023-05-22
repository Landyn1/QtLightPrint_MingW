#include "MyGraphicsCircleItem.h"
#include<qdebug.h>
#include<qgraphicsscene.h>
#include<MyGraphicsView.h>

MyGraphicsCircleItem::MyGraphicsCircleItem(QGraphicsEllipseItem*parent)
	: QGraphicsEllipseItem(parent)
{}

MyGraphicsCircleItem::~MyGraphicsCircleItem()
{}
QRectF MyGraphicsCircleItem::boundingRect() const
{  
    return rect();

}
QRect MyGraphicsCircleItem::getRect()
{
    int x,y,w,h;
    x = rect().x()+pos().x();
    y = rect().y()+pos().y();
    w = rect().width();
    h = rect().height();
    return QRect(x,y,w,h);
}
void MyGraphicsCircleItem::set_brush(double angle,int linenum)
{
    brushpath.clear();
    this->angle = angle;
    this->linenum = linenum;
    if(linenum == 0)
    {
        update();
        return;
    }
    QPainterPath path;
    double k = tan(angle*M_PI/180);//斜率
    int w = rect().width();
    int h = rect().height();
    double m = double(h)/double(w);
    if(linenum==0)
    {
        update();
        return;
    }

    if(int(angle)%90 != 0 ||  ((int(angle)%180 == 0)&&(int(angle)%90 != 0)))
    {
        if(k>0&&k<=m)
        {
            double t = (w/2*k) + (h/2); //y=kx+t
            double pert = t/(linenum/2);
            for(int i=-linenum/2;i<linenum/2;i++)
            {
                //y=kx+pert*i;
                //x^2/(w/2)^2+……=1
                double a=w/2,b=h/2;
                double n = pert*i;
                double A = b*b+a*a*k*k,B=2*a*a*k*n,C=a*a*((n*n)-(b*b));
                double deta = (B*B)-(4*A*C);
                if(deta>0)
                {
                    double x1 = (-B+sqrt(deta))/(2*A);
                    double x2 = (-B-sqrt(deta))/(2*A);
                    double y1 = k*x1+n;
                    double y2 = k*x2+n;
                    path.moveTo(x1,y1);
                    path.lineTo(x2,y2);
                }

            }

        }
        else if( k > m )
        {
            double t = (w/2*k) + (h/2); //y=kx+t
            double pert = t/(linenum/2);
            for(int i=-linenum/2;i<linenum/2;i++)
            {
                //y=kx+pert*i;
                //x^2/(w/2)^2+……=1
                double a=w/2,b=h/2;
                double n = pert*i;
                double A = b*b+a*a*k*k,B=2*a*a*k*n,C=a*a*((n*n)-(b*b));
                double deta = (B*B)-(4*A*C);
                if(deta>0)
                {
                    double x1 = (-B+sqrt(deta))/(2*A);
                    double x2 = (-B-sqrt(deta))/(2*A);
                    double y1 = k*x1+n;
                    double y2 = k*x2+n;
                    path.moveTo(x1,y1);
                    path.lineTo(x2,y2);
                }
            }
        }
        else if( k < -m)
        {
            double t = -(w/2*k) + (h/2); //y=kx+t
            double pert = t/(linenum/2);
            for(int i=-linenum/2;i<linenum/2;i++)
            {
                //y=kx+pert*i;
                //x^2/(w/2)^2+……=1
                double a=w/2,b=h/2;
                double n = pert*i;
                double A = b*b+a*a*k*k,B=2*a*a*k*n,C=a*a*((n*n)-(b*b));
                double deta = (B*B)-(4*A*C);
                if(deta>0)
                {
                    double x1 = (-B+sqrt(deta))/(2*A);
                    double x2 = (-B-sqrt(deta))/(2*A);
                    double y1 = k*x1+n;
                    double y2 = k*x2+n;
                    path.moveTo(x1,y1);
                    path.lineTo(x2,y2);
                }
            }
        }
        else if( k<0 && k>=-m)
        {
            double t = -(w/2*k) + (h/2); //y=kx+t
            double pert = t/(linenum/2);
            for(int i=-linenum/2;i<linenum/2;i++)
            {
                //y=kx+pert*i;
                //x^2/(w/2)^2+……=1
                double a=w/2,b=h/2;
                double n = pert*i;
                double A = b*b+a*a*k*k,B=2*a*a*k*n,C=a*a*((n*n)-(b*b));
                double deta = (B*B)-(4*A*C);
                if(deta>0)
                {
                    double x1 = (-B+sqrt(deta))/(2*A);
                    double x2 = (-B-sqrt(deta))/(2*A);
                    double y1 = k*x1+n;
                    double y2 = k*x2+n;
                    path.moveTo(x1,y1);
                    path.lineTo(x2,y2);
                }
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

                //y=kx+pert*i;
                //x^2/(w/2)^2+……=1
                double a=w/2,b=h/2;
                double n = pert*i;
                double x1 = sqrt((a*a)-(a*a*n*n/b/b));
                double x2 = -x1;
                double y1 = n;
                double y2 = n;
                path.moveTo(x1,y1);
                path.lineTo(x2,y2);
            }
        }

        else
        {
            double pert = w/double(linenum);
            for(double i=-w/2;i<=w/2;i+=pert)
            {
                double a=w/2,b=h/2;
                double x1=i,x2=i;
                double y1 = sqrt((1-(x1*x1)/a/a)*b*b);
                double y2 = -y1;

                path.moveTo(x1,y1);
                path.lineTo(x2,y2);
            }
        }
    }

    brushpath = path;
    update();
}

//这个函数获取绘画的path，对应的坐标为scene坐标
QPainterPath MyGraphicsCircleItem::ViewPath()
{
    QPainterPath path;
    QPainterPath path2 = brushpath;
    path.moveTo(mapToScene(0,rect().height()/2));
    double r = rect().height()/2;
    int s = 6*r;

    double dpiX = QApplication::primaryScreen()->physicalDotsPerInchX();

    double ms1 = (dpiX * 10) / 254; //1mm是几个像素
    int num = s/ms1*10;//mm*10 0.1mm一个线段;
    int t = 360*100/num;

    double tt = double(t)/100;
    double ttt = tt;

    for(int i=1;i<num;i++)
    {
        if(tt <= 90)
        {
            double x = r*sin(tt*M_PI/180);
            double y = r*cos(tt*M_PI/180);
            path.lineTo(mapToScene(x,y));
        }

        else if(tt>90&&tt<=180)
        {
            double x,y;
            double temp = tt-90;
            x = r*cos(temp*M_PI/180);
            y = -r*sin(temp*M_PI/180);
            path.lineTo(mapToScene(x,y));
        }

        else if(tt>180&&tt<=270)
        {
            double x,y;
            double temp = tt-180;
            x = -r*sin(temp*M_PI/180);
            y = -r*cos(temp*M_PI/180);
            path.lineTo(mapToScene(x,y));
        }

        else if(tt>270&&tt<360)
        {
            double x,y;
            double temp = tt-270;
            x = -r*cos(temp*M_PI/180);
            y = r*sin(temp*M_PI/180);
            path.lineTo(mapToScene(x,y));
        }
        tt = tt + ttt;
    }
    path.lineTo(mapToScene(0,rect().height()/2));

    for (int i = 0; i < path2.elementCount(); i++)
    {
        QPainterPath::Element element = path2.elementAt(i);
        QPointF po = element;
        if (element.isMoveTo())
        {
            path.moveTo(mapToScene(po));
        }
        else if (element.isLineTo())
        {
            path.lineTo(mapToScene(po));
        }
    }
    return path;

}
void MyGraphicsCircleItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    /*QPen pen = ScaleManager::get_instance().getMainViewItemPen();
    painter->setPen(pen);*/
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

    painter->drawEllipse(QPointF(0, 0), rect().width() / 2, rect().height() / 2);

    painter->drawPath(brushpath);
}


bool MyGraphicsCircleItem::selectEvent(QPointF p,int k)
{

    if(k == 1)
    {
        setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
        setSelected(true);
        return true;
    }
    if(isSelected())
        return true;

    double r = qMax(this->rect().width(), this->rect().height());
    r = r/2;
    double x = p.x();
    double y = p.y();

    if((x*x)/(r*r)+(y*y)/(r*r) - 1 >= -0.2 && (x*x)/(r*r)+(y*y)/(r*r) - 1 <=0.2)
    {
        setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
        setSelected(true);
        return true;
    }
    else
    {
        setFlags(NULL);
        setSelected(false);
        return false;
    }

}


void MyGraphicsCircleItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{

}
void MyGraphicsCircleItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{

}
void MyGraphicsCircleItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}
