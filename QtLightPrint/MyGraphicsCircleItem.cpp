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

QPainterPath MyGraphicsCircleItem::ViewPath()
{
    QPainterPath path;

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


}


bool MyGraphicsCircleItem::selectEvent(QPointF p)
{

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
