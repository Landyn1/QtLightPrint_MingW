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

    int type() const
    {
        // 针对该 item 启用 qgraphicsitem_cast
        return Type;
    }
    int printLayer = 0;

    QString name="";
signals:

};

