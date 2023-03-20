#ifndef MYGRAPHICSPOLYGONITEM_H
#define MYGRAPHICSPOLYGONITEM_H

#include <QObject>
#include <QQuickItem>
#include <QWidget>
#include<qgraphicsitem.h>
#include<qpainter.h>
#include<qpolygon.h>
#include<qpainterpath.h>
#include<qdebug.h>
class MyGraphicsPolygonItem : public QGraphicsRectItem
{
public:
    MyGraphicsPolygonItem(QGraphicsRectItem *parent = nullptr);
    ~MyGraphicsPolygonItem();


    QRectF boundingRect() const
    {
        return rect();
    }

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    enum { Type = 5 };

    int type() const
    {
        // 针对该 item 启用 qgraphicsitem_cast
        return Type;
    }
    int printLayer = 0;

    QString name="";
    int num = 5;

signals:

};

#endif // MYGRAPHICSPOLYGONITEM_H
