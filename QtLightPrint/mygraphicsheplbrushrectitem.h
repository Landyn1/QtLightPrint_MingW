#ifndef MYGRAPHICSHEPLBRUSHRECTITEM_H
#define MYGRAPHICSHEPLBRUSHRECTITEM_H

#include<qgraphicsitem.h>
class MyGraphicsHeplBrushRectItem :public QGraphicsRectItem
{
public:
    MyGraphicsHeplBrushRectItem();


    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

    double angle = 0;

    double space = 1000;

};

#endif // MYGRAPHICSHEPLBRUSHRECTITEM_H
