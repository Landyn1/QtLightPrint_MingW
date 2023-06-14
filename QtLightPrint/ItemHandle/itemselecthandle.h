#ifndef ITEMSELECTHANDLE_H
#define ITEMSELECTHANDLE_H
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
class ItemSelectHandle
{
public:
    MyGraphicsView *view;


    ItemSelectHandle(MyGraphicsView *view);
    void setSelecT(int k);
};

#endif // ITEMSELECTHANDLE_H
