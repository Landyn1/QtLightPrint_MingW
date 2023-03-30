#include "MyGraphicsEllipseItem.h"
#include<qdebug.h>
#include<qgraphicsscene.h>'
#include<qgraphicsview.h>
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
