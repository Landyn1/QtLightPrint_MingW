#include "MyGraphicsEllipseItem.h"
#include<qdebug.h>
#include<qgraphicsscene.h>'
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
    auto r = qMax(this->rect().width(), this->rect().height());
    
    QRectF temp_rect = this->rect();

    return temp_rect;
	
}

QPainterPath MyGraphicsEllipseItem::ViewPath()
{
    QPainterPath p;
    double w = this->rect().width();
    double h = this->rect().height();
    p.moveTo(mapToScene(0,h/2));
    int s = 6*w+4*(w-h);

    double dpiX = QApplication::primaryScreen()->physicalDotsPerInchX();

    double ms1 = (dpiX * 10) / 254; //1mm是几个像素
    int num = s/ms1*10;//mm*10 一微米一个线段;
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
    
        
    painter->drawEllipse(QPointF(0, 0), this->rect().width() / 2, this->rect().height() / 2);

}

bool MyGraphicsEllipseItem::selectEvent(QPointF p)
{

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


void MyGraphicsEllipseItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{

}
void MyGraphicsEllipseItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{

}
void MyGraphicsEllipseItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}
