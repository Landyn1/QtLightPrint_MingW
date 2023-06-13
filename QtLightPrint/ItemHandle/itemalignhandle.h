#ifndef ITEMALIGNHANDLE_H
#define ITEMALIGNHANDLE_H
#include<QWidget>
#include"mainWindow.h"
#include<QObject>
#include"GraphicsItems/MyGraphicsCircleItem.h"
#include"GraphicsItems/MyGraphicsEllipseItem.h"
#include"GraphicsItems/MyGraphicsRecItem.h"
#include"GraphicsItems/mygraphicslineitem.h"
#include"GraphicsItems/mygraphicspolygonitem.h"
#include"GraphicsItems/mygraphicstextitem.h"
#include"GraphicsItems/mygraphicscurvelineitem.h"
#include"GraphicsItems/mygraphicspixmapitem.h"
#include"GraphicsItems/mygraphicscodeitem.h"
#include"GraphicsItems/mygraphicsgroupitem.h"

class ItemAlignHandle
{
public:
    ItemAlignHandle();
    template<typename T> void leftAlign(QGraphicsItem* node,QPointF rootPos);
    template<typename T> void rightAlign(QGraphicsItem* node,QPointF rootPos);
    template<typename T> void topAlign(QGraphicsItem* node,QPointF rootPos);
    template<typename T> void buttomAlign(QGraphicsItem* node,QPointF rootPos);
    int findroot(int id,QList<QGraphicsItem*> items);
    void center(mainWindow* mw);
    void left(mainWindow* mw);
    void right(mainWindow* mw);
    void top(mainWindow* mw);
    void buttom(mainWindow* mw);
};

#endif // ITEMALIGNHANDLE_H
