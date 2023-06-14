#ifndef ITEMPRINTHANDLE_H
#define ITEMPRINTHANDLE_H
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
#include"libsHeaders/CUDrvE.h"
#include<iostream>
class ItemPrintHandle
{
public:
    ItemPrintHandle();

    bool LightDraw(QPixmap pixmap,int printLayer,mainWindow *mw);
    bool LightDraw(QPainterPath path, int printLayer,mainWindow *mw);
    bool printItem(mainWindow *mw);
    bool printRedItem(mainWindow *mw);
    QPoint view2print(QPointF position,mainWindow *mw);
};

#endif // ITEMPRINTHANDLE_H
