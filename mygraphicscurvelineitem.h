#ifndef MYGRAPHICSCURVELINEITEM_H
#define MYGRAPHICSCURVELINEITEM_H

#include <QObject>
#include<qgraphicsitem.h>
#include<qpainterpath.h>
#include<qpainter.h>
#include<math.h>
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
    bool selectEvent(QPointF p);
    QList<double> getRect();
    double f(double t,double p0,double p1,double p2,double p3)
    {
        return pow((1-t),3)*p0+3*t*pow((1-t),2)*p1 + 3*t*t*(1-t)*p2 + pow(t,3)*p3;
    }

    double getf_daoshu(double t,double a,double b,double c)
    {
        return a*t*t+b*t+c;
    }

    double getDeta(double a,double b,double c)
    {
        return b*b-4*a*c;
    }
private:
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
signals:

};

#endif // MYGRAPHICSCURVELINEITEM_H
