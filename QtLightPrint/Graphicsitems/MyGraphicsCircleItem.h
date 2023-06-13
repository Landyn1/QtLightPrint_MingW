#pragma once
#ifndef MYGRAPHICSCIRCLEITEM_H
#define MYGRAPHICSCIRCLEITEM_H
#include <QGraphicsItem>
#include <QPainter>
#include <QtWidgets/qstyleoption.h>
#include<qgraphicsitem.h>
class MyGraphicsCircleItem  : public QGraphicsEllipseItem
{
public:

    QPainterPath brushpath;
    double angle = 0;
    double space = 0;
    int printLayer = 0;
    QString name="";


    MyGraphicsCircleItem(QGraphicsEllipseItem*parent=NULL);
    ~MyGraphicsCircleItem();
    QRectF boundingRect() const;
    enum { Type = 3 };
    QRect getRect();
    QPainterPath path()
    {
        QPainterPath p;
        return p;
    }
    void set_brush(double angle,double space);
    int type() const
    {
        // 针对该 item 启用 qgraphicsitem_cast
        return Type;
    }
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    QPainterPath ViewPath(int k=0);
    bool selectEvent(QPointF p,int k=0);

private:
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif
