#pragma once

#include <QObject>
#include <QPainter>
#include <QtWidgets/qstyleoption.h>
#include<qgraphicsitem.h>
class MyGraphicsEllipseItem  : public QGraphicsEllipseItem
{


public:

    QPainterPath brushpath;
    double angle = 0;
    double space = 0;
    int printLayer = 0;
    QString name="";

    MyGraphicsEllipseItem(QGraphicsEllipseItem *parent=NULL);
    ~MyGraphicsEllipseItem();
    QRectF boundingRect() const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    enum { Type = 2 };
    void set_brush(double angle,double space);
    bool selectEvent(QPointF p,int k=0);
    int type() const
    {
        // 针对该 item 启用 qgraphicsitem_cast
        return Type;
    }
    QPainterPath ViewPath(int k=0);
    QRect getRect();
    QPainterPath path()
    {
        QPainterPath p;
        return p;
    }
private:
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};
