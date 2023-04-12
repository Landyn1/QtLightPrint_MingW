#include "mygraphicslineitem.h"
#include<MyGraphicsView.h>
MyGraphicsLineItem::MyGraphicsLineItem(QGraphicsPathItem *parent) : QGraphicsPathItem(parent)
{

}

MyGraphicsLineItem::~MyGraphicsLineItem()
{

}
QPainterPath MyGraphicsLineItem::ViewPath()
{
    QPainterPath p;
    QPainterPath path = this->path();
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
void MyGraphicsLineItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
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

}

QRect MyGraphicsLineItem::getRect()
{
    int x,y,w,h;
    QPoint zuoxia(10000,10000),youshang(-10000,-10000);

    QPainterPath path = this->path();

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

bool MyGraphicsLineItem::selectEvent(QPointF p)
{
    if(isSelected())
        return true;
    QPainterPath path = this->path();

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

bool MyGraphicsLineItem::isOnLine(QLine l , QPoint p)
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

void MyGraphicsLineItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{

}
void MyGraphicsLineItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{

}
void MyGraphicsLineItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}
