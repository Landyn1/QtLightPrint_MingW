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

    qDebug()<<x<<y<<r<<endl;
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
