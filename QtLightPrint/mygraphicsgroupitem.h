#ifndef MYGRAPHICSGROUPITEM_H
#define MYGRAPHICSGROUPITEM_H

#include <QObject>
#include<qgraphicsitem.h>
class MyGraphicsGroupItem :public QGraphicsItemGroup
{
public:
    MyGraphicsGroupItem(QList<QGraphicsItem*> items);
    ~MyGraphicsGroupItem();
    QRectF boundingRect() const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    enum { Type = 10 };

    bool selectEvent(QPointF p);
    int type() const
    {
        // 针对该 item 启用 qgraphicsitem_cast
        return Type;
    }
    void setRectF();
    int printLayer = 0;
    QPainterPath ViewPath();
    QString name="";
    QRect getRect();
    QPainterPath path()
    {
        QPainterPath p;
        return p;
    }
    QRectF rectf;
};

#endif // MYGRAPHICSGROUPITEM_H
