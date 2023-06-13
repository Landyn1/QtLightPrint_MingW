#ifndef QLPTFILEHANDLE_H
#define QLPTFILEHANDLE_H
#include<QWidget>
#include"mainWindow.h"
#include<QObject>
#include"FileHandel/itemfileclass.h"
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
#include"FileHandel/pltfilehandle.h"
class qlptfileHandle
{
public:
    qlptfileHandle();
    void savefile(QList<QGraphicsItem*> items,QWidget *mw);
    void createnewfile(mainWindow *mw,QWidget *th);
    void createnewfile(mainWindow *mw,QWidget *th,QString filename);
    void openfile(mainWindow *mw,QWidget *th);
    template<typename T> void saveItems(QGraphicsItem* node, ItemFileClass *&iff,int type);
};

#endif // QLPTFILEHANDLE_H
