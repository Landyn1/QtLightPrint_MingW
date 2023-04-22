#include "MyGraphicsRecItem.h"
#include"mainWindow.h"
#include <QPen>
#include <QPainter>
#include <QPainterPath>
#include <QPainterPathStroker>
#include <QStyle>
#include <QStyleOptionGraphicsItem>
#include<QKeyEvent>
MyGraphicsRecItem::MyGraphicsRecItem(QGraphicsItem *parent)
	: QGraphicsRectItem(parent)
{
	initVaiables();
}

MyGraphicsRecItem::~MyGraphicsRecItem()
{}

QRectF MyGraphicsRecItem::boundingRect() const
{
    QRectF temp_rect = rect().adjusted(-20,-20,20,20);
    return temp_rect;
	
}
//
QPainterPath MyGraphicsRecItem::shape() const
{
    QPainterPath temp;

    QRectF temp_rect = rect();
    temp.addRect(temp_rect);
    return temp;
}

QPainterPath MyGraphicsRecItem::ViewPath()
{

    QPainterPath path;
    QRectF temp(mapToScene(rect()).value(0).x(), mapToScene(rect()).value(0).y(), rect().width(), rect().height());

    path.addRect(temp);
    return path;
}

void MyGraphicsRecItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
   // QPen pen = ScaleManager::get_instance().getMainViewItemPen();
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
    painter->drawRect(this->rect());
    painter->drawPath(brushpath);

}

void MyGraphicsRecItem::initVaiables()
{
	//setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
}
void MyGraphicsRecItem::keyPressEvent(QKeyEvent *event)
{

}

bool MyGraphicsRecItem::selectEvent(QPointF p)
{
    if(this->isSelected())
        return true;
    double w = rect().width();
    double h = rect().height();
    QLine *lin1 = new QLine(-w/2,-h/2,w/2,-h/2);
    QLine *lin2 = new QLine(w/2,-h/2,w/2,h/2);
    QLine *lin3 = new QLine(-w/2,h/2,w/2,h/2);
    QLine *lin4 = new QLine(-w/2,-h/2,-w/2,h/2);

    if(isOnLine(*lin1,p.toPoint()))
    {
        this->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
        this->setSelected(true);
    }
    else if(isOnLine(*lin2,p.toPoint()))
    {
        this->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
        this->setSelected(true);
    }
    else if(isOnLine(*lin3,p.toPoint()))
    {
        this->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
        this->setSelected(true);
    }
    else if(isOnLine(*lin4,p.toPoint()))
    {
        this->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
        this->setSelected(true);
    }
    else
    {
        this->setFlags(NULL);
        this->setSelected(false);
        return false;
    }
    return true;


}

void MyGraphicsRecItem::set_brush(double jiaodu,int midu)
{
    brushpath.clear();
    QPainterPath path;
    double k = tan(jiaodu*M_PI/180);//斜率
    int w = rect().width();
    int h = rect().height();
    double m = double(h)/double(w);
    if(midu==0)
    {
        update();
        return;
    }
    if(int(jiaodu)%90 != 0 ||  ((int(jiaodu)%180 == 0)&&(int(jiaodu)%90 != 0)))
    {
        if(k>0&&k<=m)
        {
            double t = (w/2*k) + (h/2); //y=kx+t
            double pert = t/(midu/2);

            for(int i=-midu/2;i<midu/2;i++)
            {

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
                path.moveTo(p1);
                path.lineTo(p2);
            }

        }
        else if( k > m )
        {
            double t = (w/2*k) + (h/2); //y=kx+t
            double pert = t/(midu/2);
            for(int i=-midu/2;i<midu/2;i++)
            {
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
                path.moveTo(p1);
                path.lineTo(p2);
            }
        }
        else if( k < -m)
        {
            double t = -(w/2*k) + (h/2); //y=kx+t
            double pert = t/(midu/2);
            for(int i=-midu/2;i<midu/2;i++)
            {
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
                path.moveTo(p1);
                path.lineTo(p2);
            }
        }
        else if( k<0 && k>=-m)
        {
            double t = -(w/2*k) + (h/2); //y=kx+t
            double pert = t/(midu/2);
            for(int i=-midu/2;i<midu/2;i++)
            {
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
                path.moveTo(p1);
                path.lineTo(p2);
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
                QPointF p1(-w/2,pert*i);
                QPointF p2(w/2,pert*i);
                path.moveTo(p1);
                path.lineTo(p2);
            }
        }

        else
        {
            double pert = w/double(midu);
            for(int i=-midu/2;i<midu/2;i++)
            {
                QPointF p1(pert*i,h/2);
                QPointF p2(pert*i,-h/2);
                path.moveTo(p1);
                path.lineTo(p2);
            }
        }

    }
    this->jiaodu = jiaodu;
    this->midu = midu;
    brushpath = path;
    update();
}

void MyGraphicsRecItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{


}
bool MyGraphicsRecItem::isOnLine(QLine l , QPoint p)
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
void MyGraphicsRecItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{

}
void MyGraphicsRecItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    
}
