#include "mygraphicscodeitem.h"
#include"mainWindow.h"
#include"ZXingWriter.h"
MyGraphicsCodeItem::MyGraphicsCodeItem():QGraphicsPathItem()
{

}

MyGraphicsCodeItem::~MyGraphicsCodeItem(){

}

QRectF MyGraphicsCodeItem::getRect()
{
    return this->path().boundingRect();
}

bool MyGraphicsCodeItem::selectEvent(QPointF p)
{
    if(isSelected())
        return true;
    if(this->path().boundingRect().contains(p))
    {
        setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
        this->setSelected(true);
        return true;
    }
    this->setFlags(NULL);
    this->setSelected(false);
    return false;
}

void MyGraphicsCodeItem::setPathByStr(QString str,QString codeType)
{
    vector<dPoint> vdPoint;
    double dpiX = QApplication::primaryScreen()->physicalDotsPerInchX();
    double  t = (dpiX * 10) / 254; //1mm=tpx
    vdPoint = Border(20*t, 20*t, str.toStdString(), codeType.toStdString());
    QPainterPath path;
    for (vector<dPoint>::iterator it = vdPoint.begin(); it != vdPoint.end(); it++)
    {
        if(!(*it).flag)
        {
            path.moveTo(QPointF((*it).x,(*it).y));
        }
        else
        {
            path.lineTo(QPointF((*it).x,(*it).y));
        }
    }
    this->setPath(path);
}

void MyGraphicsCodeItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
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
    //painter->setBrush(Qt::blue);
    painter->setPen(pen);
    painter->drawPath(this->path());

}
QPainterPath MyGraphicsCodeItem::ViewPath()
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
void MyGraphicsCodeItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{

}
void MyGraphicsCodeItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{

}
void MyGraphicsCodeItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}
