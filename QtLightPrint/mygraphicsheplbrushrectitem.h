#ifndef MYGRAPHICSHEPLBRUSHRECTITEM_H
#define MYGRAPHICSHEPLBRUSHRECTITEM_H

#include<qgraphicsitem.h>
class MyGraphicsHeplBrushRectItem :public QGraphicsRectItem
{
public:
    MyGraphicsHeplBrushRectItem();


    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

    double angle = 0;

    int linenum = 1000;

};

#endif // MYGRAPHICSHEPLBRUSHRECTITEM_H
