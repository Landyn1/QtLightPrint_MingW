#include "mygraphicstextitem.h"
#include<qdebug.h>
#include"mainWindow.h"
#include <QPen>
#include <QPainter>
#include <QPainterPath>
#include <QPainterPathStroker>
#include <QStyle>
#include <QStyleOptionGraphicsItem>
#include<QKeyEvent>
MyGraphicsTextItem::MyGraphicsTextItem(QGraphicsTextItem *p,QString str):QGraphicsRectItem()
{

    this->str = str;
}


void MyGraphicsTextItem::setStr(QString str,QFont font)
{

    this->str = str;
    this->font = font;
    //setDefault_Path();
    //update();
}
void MyGraphicsTextItem::setRectF()
{
    QFontMetrics fm(this->font);
    rectf = fm.boundingRect(str);
}
QPainterPath MyGraphicsTextItem::ViewPath()
{
    QPainterPath p;
    QPainterPath path = this->path;
    int k=0;
    QPointF p0,c1,c2,p3;
    for (int i = 0; i < path.elementCount(); i++)
    {
        QPainterPath::Element element = path.elementAt(i);
        QPointF po = element;
        QPointF po2 = mapToScene(po);
        if (element.isMoveTo())
        {
            p.moveTo(mapToScene(po));
            p0 = po2;
        }
        else if (element.isLineTo())
        {
            p.lineTo(mapToScene(po));
            p0 = po2;
        }
        else if(element.isCurveTo())
        {

            c1 = po2;
            k++;
            //path2.cubicTo(po2);
        }
        else
        {
            if(k%3 == 1)
            {
                c2 = po2;
                k++;
            }
            else if(k%3 == 2)
            {
                p3 = po2;
                QList<QPointF> list;
                for(int i=0;i<=5;i++)
                {
                    double temp = 0.2*i;
                    double tx = f(temp,p0.x(),c1.x(),c2.x(),p3.x());
                    double ty = f(temp,p0.y(),c1.y(),c2.y(),p3.y());
                    list.append(QPointF(tx,ty));
                }
                double s = 0;
                for(int i=0;i<5;i++)
                {
                    double x1,x2,y1,y2;
                    x1 = list[i].x();
                    y1 = list[i].y();
                    x2 = list[i+1].x();
                    y2 = list[i+1].y();
                    double m = (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
                    m = sqrt(m);
                    s += m;
                }
                double dpiX = QApplication::primaryScreen()->physicalDotsPerInchX();
                double  t = (dpiX * 10) / 254;   //1mm = t px
                double s_mm = s/t;
                int num = s_mm / 0.1 ; //每隔0.1毫米一个单位;

                for(int i=1;i<=num;i++)
                {
                    double temp = (double(1)/double(num))*i;
                    double tx = f(temp,p0.x(),c1.x(),c2.x(),p3.x());
                    double ty = f(temp,p0.y(),c1.y(),c2.y(),p3.y());
                    p.lineTo(tx,ty);
                }
                k++;
                p0=po2;
            }

        }
    }
    return p;
}

void MyGraphicsTextItem::setDefault_Path()
{
    path.addText(rect().x(),-rect().y(), font, str);
}

void MyGraphicsTextItem::makePath_fill_Rect()
{
    QPainterPath path = this->path;
    QRectF rect = path.boundingRect();

    QRectF tarRect = this->rect();
    qDebug()<<tarRect<<endl;
    qreal scaleX = tarRect.width() / rect.width();
    qreal scaleY = tarRect.height() / rect.height();



    QTransform trans;
    trans.scale(scaleX, scaleY);
    QPainterPath tmp_path = trans.map(path);

    QPointF delta = tarRect.center() - tmp_path.boundingRect().center();
    tmp_path.translate(delta.x(), delta.y());
    this->setPath(tmp_path);
}
void MyGraphicsTextItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
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
    //painter->setBrush(Qt::blue);
    painter->scale(1,-1);

    painter->drawPath(path);

    painter->drawRect(rect());
    pen.setColor(Qt::blue);
     painter->setPen(pen);
    painter->drawRect(path.boundingRect());
}
MyGraphicsTextItem::~MyGraphicsTextItem()
{

}

bool MyGraphicsTextItem::selectEvent(QPointF p)
{

    if(isSelected())
        return true;
    if(rect().contains(p))
    {
        setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
        this->setSelected(true);
        return true;
    }
    this->setFlags(NULL);
    this->setSelected(false);
    return false;
}

void MyGraphicsTextItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{

}
void MyGraphicsTextItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{

}
void MyGraphicsTextItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}
