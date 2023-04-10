#pragma once


#include <QObject>
#include <QPainter>
#include <QtWidgets/qstyleoption.h>
#include<qgraphicsitem.h>
#include<qpainterpath.h>
class MyGraphicsLineItem : public QGraphicsPathItem
{
public:
    MyGraphicsLineItem(QGraphicsPathItem *parent = nullptr);
    ~MyGraphicsLineItem();
    //QRectF boundingRect() const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    enum { Type = 4 };
    QPainterPath ViewPath();
    int type() const
    {
        // 针对该 item 启用 qgraphicsitem_cast
        return Type;
    }
    int printLayer = 0;
    bool selectEvent(QPointF p);
    QString name="";
    bool isOnLine(QLine l , QPoint p);
    QRect getRect();
private:
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
signals:

};

