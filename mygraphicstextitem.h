#ifndef MYGRAPHICSTEXTITEM_H
#define MYGRAPHICSTEXTITEM_H

#include <QObject>
#include <QWidget>
#include<qgraphicsitem.h>
class MyGraphicsTextItem : public QGraphicsTextItem
{
public:
    MyGraphicsTextItem(QGraphicsTextItem *parent = NULL,QString str = "这是一串字符串");
    ~MyGraphicsTextItem();

    QRectF boundingRect() const
    {
        QRectF temp_rect(0,12,420,66);

        return temp_rect;
    }

    enum { Type = 6 };

    int type() const
    {
        // 针对该 item 启用 qgraphicsitem_cast
        return Type;
    }
    int printLayer = 0;

    QString name="";
};

#endif // MYGRAPHICSTEXTITEM_H
