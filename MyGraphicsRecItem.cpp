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
    /*QFont font;
    font.setFamily("微软雅黑");
    path.addText(100, 100, font, "你好");*/
    path.addRect(temp);
    return path;
}

void MyGraphicsRecItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
   // QPen pen = ScaleManager::get_instance().getMainViewItemPen();
    QPen pen;   // 定义一个画笔，设置画笔颜色和宽度
    //pen.setColor(QColor(0, 160, 230));
    pen.setWidthF(1);
    painter->setPen(pen);

    if ((option->state & QStyle::State_Selected) ) {
        float penWidth = pen.widthF();

        //painter->setPen(QPen(option->palette.windowText(), 0, Qt::DashLine));

        painter->setBrush(Qt::NoBrush);
        painter->drawRect(this->rect());
       // emit item_selected();
    }
    else {
        painter->drawRect(this->rect());
    }

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

    QLine *lin1 = new QLine(0,0,rect().width(),0);
    QLine *lin2 = new QLine(rect().width(),0,rect().width(),rect().height());
    QLine *lin3 = new QLine(0,rect().height(),rect().width(),rect().height());
    QLine *lin4 = new QLine(0,0,0,rect().height());

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
