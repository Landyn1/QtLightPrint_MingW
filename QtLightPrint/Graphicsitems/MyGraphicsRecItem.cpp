#include "GraphicsItems/MyGraphicsRecItem.h"
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

QRect MyGraphicsRecItem::getRect()
{
    int x,y,w,h;
    x = rect().x()+pos().x();
    y = rect().y()+pos().y();
    w = rect().width();
    h = rect().height();
    return QRect(x,y,w,h);
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

QPainterPath MyGraphicsRecItem::ViewPath(int k)
{

    QPainterPath path;
    QPainterPath path2 = brushpath;
    QRectF temp(mapToScene(rect()).value(0).x(), mapToScene(rect()).value(0).y(), rect().width(), rect().height());
    if(k == 0)
    {
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
    }

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
    int k=0;
    if(data(0).toInt() == -1)
    {
        pen.setColor(Qt::blue);
        k=1;
    }
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
    painter->setPen(pen);
    painter->drawRect(this->rect());
    if(k == 0)
        painter->drawPath(brushpath);

}

void MyGraphicsRecItem::initVaiables()
{
    setFlags(NULL);
    setSelected(false);
}
void MyGraphicsRecItem::keyPressEvent(QKeyEvent *event)
{

}

bool MyGraphicsRecItem::selectEvent(QPointF p,int k)
{
    if(k == 1)
    {
        this->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
        this->setSelected(true);
        return true;
    }

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

void MyGraphicsRecItem::set_brush(double angle,double space)
{

    brushpath.clear();
    this->angle = angle;
    double dpiX = QApplication::primaryScreen()->physicalDotsPerInchX();
    double  temp = (dpiX * 10) / 254; //1mm = tpx
    double maxh = fmax(this->getRect().width(),this->getRect().height());
    double linenum = (maxh/temp) / space;
    this->space = space;
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
        if(k>0&&k<=m)
        {
            double t = (w/2*k) + (h/2); //y=kx+t
            double pert = t/(linenum/2);
            for(int i=-linenum/2;i<linenum/2;i++)
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
            double pert = t/(linenum/2);
            for(int i=-linenum/2;i<linenum/2;i++)
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
            double pert = t/(linenum/2);
            for(int i=-linenum/2;i<linenum/2;i++)
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
            double pert = t/(linenum/2);
            for(int i=-linenum/2;i<linenum/2;i++)
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
        if(int(angle)%180 == 0)
        {
            double t = (w/2*k) + (h/2); //y=kx+t
            double pert = t/(linenum/2);
            for(int i=-linenum/2;i<linenum/2;i++)
            {
                QPointF p1(-w/2,pert*i);
                QPointF p2(w/2,pert*i);
                path.moveTo(p1);
                path.lineTo(p2);
            }
        }

        else
        {
            double pert = w/double(linenum);
            for(int i=-linenum/2;i<linenum/2;i++)
            {
                QPointF p1(pert*i,h/2);
                QPointF p2(pert*i,-h/2);
                path.moveTo(p1);
                path.lineTo(p2);
            }
        }

    }
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
