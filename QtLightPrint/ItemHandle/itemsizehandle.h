#ifndef ITEMSIZEHANDLE_H
#define ITEMSIZEHANDLE_H
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

class ItemSizeHandle
{
public:
    ItemSizeHandle();
    void setItemByLable(mainWindow *mw);
    void setpreRect(mainWindow *mw);
    template<typename T> void setItemPosition(QGraphicsItem* node, int &leftbuttomx,int &leftbuttomy,int &righttopx,int &righttopy);
    template<typename T> void setItemRect_XandY(QGraphicsItem* node, int &x,int &y);
    template<typename T> void setItemRect_WandH(QGraphicsItem* node, int x,int y,int &w,int &h);
};

#endif // ITEMSIZEHANDLE_H
