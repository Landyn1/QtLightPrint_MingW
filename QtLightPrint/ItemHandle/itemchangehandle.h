#ifndef ITEMCHANGEHANDLE_H
#define ITEMCHANGEHANDLE_H
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
#include"GraphicsItems/MyGraphicsView.h"
#include"ItemAdjust.h"
class ItemChangeHandle
{
public:
    MyGraphicsView *view;


    ItemChangeHandle(MyGraphicsView *view);
    void midtop_set(QPointF p1,QPointF p2);
    void lefttop_set(QPointF p1,QPointF p2);
    void righttop_set(QPointF p1,QPointF p2);
    void leftbuttom_set(QPointF p1,QPointF p2);
    void midbuttom_set(QPointF p1,QPointF p2);
    void rightbuttom_set(QPointF p1,QPointF p2);
    void leftmid_set(QPointF p1,QPointF p2);
    void rightmid_set(QPointF p1,QPointF p2);
    void saveItems();
};

#endif // ITEMCHANGEHANDLE_H
