#include "GraphicsItems/MyGraphicsEllipseItem.h"
#include<qdebug.h>
#include<qgraphicsscene.h>
#include<qgraphicsview.h>
#include<math.h>
#include<QApplication>
#include<QScreen>
MyGraphicsEllipseItem::MyGraphicsEllipseItem(QGraphicsEllipseItem *parent)
	: QGraphicsEllipseItem(parent)
{}

MyGraphicsEllipseItem::~MyGraphicsEllipseItem()
{}
QRectF MyGraphicsEllipseItem::boundingRect() const
{
    
    QRectF temp_rect = this->rect();

    return temp_rect;
	
}
QRect MyGraphicsEllipseItem::getRect()
{
    int x,y,w,h;
    x = rect().x()+pos().x();
    y = rect().y()+pos().y();
    w = rect().width();
    h = rect().height();
    return QRect(x,y,w,h);
}
QPainterPath MyGraphicsEllipseItem::ViewPath(int k)
{
    QPainterPath p;
    double w = this->rect().width();
    double h = this->rect().height();
    p.moveTo(mapToScene(0,h/2));
    int s = 6*w+4*(w-h); //周长
    QPainterPath path2 = brushpath;
    double dpiX = QApplication::primaryScreen()->physicalDotsPerInchX();

    double ms1 = (dpiX * 10) / 254; //1mm是几个像素
    int num = s/ms1*5;//mm*10 0.1mm一个线段;
    int t = 360*100/num;

    double tt = double(t)/100;
    double ttt = tt;
    double r;
    for(int i=1;i<num;i++)
    {
        if(tt <= 90)
        {

            double hudu = tt*M_PI/180;
            r = w*w*h*h/(4*((h*h*sin(hudu)*sin(hudu))+(w*w*cos(hudu)*cos(hudu))));
            r = sqrt(r);
            double x = r*sin(tt*M_PI/180);
            double y = r*cos(tt*M_PI/180);
            p.lineTo(mapToScene(QPointF(x,y)));
        }

        else if(tt>90&&tt<=180)
        {
            double temp = tt-90;
            double hudu = temp*M_PI/180;
            r = w*w*h*h/(4*(h*h*cos(hudu)*cos(hudu)+w*w*sin(hudu)*sin(hudu)));
            r = sqrt(r);
            double x,y;

            x = r*cos(temp*M_PI/180);
            y = -r*sin(temp*M_PI/180);
            p.lineTo(mapToScene(QPointF(x,y)));
        }

        else if(tt>180&&tt<=270)
        {
            double temp = tt-180;
            double hudu = temp*M_PI/180;
            r = w*w*h*h/(4*(h*h*sin(hudu)*sin(hudu)+w*w*cos(hudu)*cos(hudu)));
            r = sqrt(r);
            double x,y;

            x = -r*sin(temp*M_PI/180);
            y = -r*cos(temp*M_PI/180);
            p.lineTo(mapToScene(QPointF(x,y)));
        }

        else if(tt>270&&tt<360)
        {
            double temp = tt-270;
            double hudu = temp*M_PI/180;
            r = w*w*h*h/(4*(h*h*cos(hudu)*cos(hudu)+w*w*sin(hudu)*sin(hudu)));
            r = sqrt(r);
            double x,y;

            x = -r*cos(temp*M_PI/180);
            y = r*sin(temp*M_PI/180);
            p.lineTo(mapToScene(QPointF(x,y)));
        }
        tt = tt + ttt;
    }
    p.lineTo(mapToScene(0,h/2));

    if(k == 0)
    {
        for (int i = 0; i < path2.elementCount(); i++)
        {
            QPainterPath::Element element = path2.elementAt(i);
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
    }
    return p;
}
void MyGraphicsEllipseItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
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
    if(data(15).toInt() == 1)
    {
        double w = rect().width()/2;
        double h = rect().height()/2;
        QPointF p1;
        p1.setX((w-10)/s);
        p1.setY((h+10)/s);
        QPixmap pix;
        pix.load(":/res/lock.png");
        painter->scale(1,-1);
        painter->drawPixmap(QRectF(p1.x()-w,p1.y()-h-20/s,20/s,20/s),pix,pix.rect());
        painter->scale(1,1);
    }
        
    painter->drawEllipse(QPointF(0, 0), this->rect().width() / 2, this->rect().height() / 2);
    if(data(0).toInt() > 0)
    {
            painter->drawPath(brushpath);
    }

}

bool MyGraphicsEllipseItem::selectEvent(QPointF p,int k)
{
    if(k == 1)
    {
        setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
        setSelected(true);
        return true;
    }

    if(isSelected())
        return true;
    double w = rect().width()/2;
    double h = rect().height()/2;

    double x = p.x();
    double y = p.y();


    if((x*x)/(w*w)+(y*y)/(h*h) - 1 >= -0.2 && (x*x)/(w*w)+(y*y)/(h*h) - 1 <=0.2)
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

void MyGraphicsEllipseItem::set_brush(double angle,double space)
{
    brushpath.clear();
    this->angle = angle;
    double dpiX = QApplication::primaryScreen()->physicalDotsPerInchX();
    double  temp = (dpiX * 10) / 254; //1mm = tpx
    double maxh = fmax(this->getRect().width(),this->getRect().height());
    double linenum = (maxh/temp) / space;
    this->space = space;
    if(space == 0)
    {
        update();
        return;
    }
    QPainterPath path;
    double k = tan(angle*M_PI/180);//斜率
    int w = rect().width();
    int h = rect().height();
    double m = double(h)/double(w);
    if(space==0)
    {
        update();
        return;
    }
    if(int(angle)%90 != 0 ||  ((int(angle)%180 == 0)&&(int(angle)%90 != 0)))
    {
        if(k==0)
        {
            double t = (w/2*k) + (h/2); //y=kx+t
            double pert = t/(linenum/2);
            for(int i=-linenum/2;i<linenum/2;i++)
            {

                //y=kx+n;
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
        else if(k>0&&k<=m)
        {
            double t = (w/2*k) + (h/2); //y=kx+t
            double pert = t/(linenum/2);
            for(int i=-linenum/2;i<linenum/2;i++)
            {
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

void MyGraphicsEllipseItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{

}
void MyGraphicsEllipseItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{

}
void MyGraphicsEllipseItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}
