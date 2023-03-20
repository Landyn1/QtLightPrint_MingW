#ifndef MYGRAPHICSCURVELINEITEM_H
#define MYGRAPHICSCURVELINEITEM_H

#include <QObject>
#include<qgraphicsitem.h>
#include<qpainterpath.h>
#include<qpainter.h>
class MyGraphicsCurveLineItem : public QGraphicsPathItem
{
public:
    MyGraphicsCurveLineItem(QGraphicsPathItem *parent = nullptr);
    ~MyGraphicsCurveLineItem();
    //QRectF boundingRect() const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    enum { Type = 7 };
    QPointF duichengdian(QPointF p1 , QPointF p2);
    int type() const
    {
        // 针对该 item 启用 qgraphicsitem_cast
        return Type;
    }
    void setIspaint(bool b)
    {
        ispainting = b;
        update();
    }
    int printLayer = 0;

    QString name="";

    QPointF ctl_pre;
    QPointF ctl_next;
    QPointF endP;
    QPointF startP;

    bool  isfirst = true;
    bool  ispainting = false;
signals:

};

#endif // MYGRAPHICSCURVELINEITEM_H
