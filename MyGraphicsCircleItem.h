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

    int type() const
    {
        // 针对该 item 启用 qgraphicsitem_cast
        return Type;
    }
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    int printLayer = 0;

    QString name="";
};
