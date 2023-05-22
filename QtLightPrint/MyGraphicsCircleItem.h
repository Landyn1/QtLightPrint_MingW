#pragma once

#include <QGraphicsItem>
#include <QPainter>
#include <QtWidgets/qstyleoption.h>
#include<qgraphicsitem.h>
class MyGraphicsCircleItem  : public QGraphicsEllipseItem
{
public:
	MyGraphicsCircleItem(QGraphicsEllipseItem*parent=NULL);
	~MyGraphicsCircleItem();
    QRectF boundingRect() const;
    enum { Type = 3 };
    QPainterPath brushpath;
    double angle = 0;
    int linenum = 0;
    QRect getRect();
    QPainterPath path()
    {
        QPainterPath p;
        return p;
    }
    void set_brush(double angle,int linenum);
    int type() const
    {
        // 针对该 item 启用 qgraphicsitem_cast
        return Type;
    }
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    int printLayer = 0;

    QString name="";
    QPainterPath ViewPath();
    bool selectEvent(QPointF p,int k=0);
private:
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};
