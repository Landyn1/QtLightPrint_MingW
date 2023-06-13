#ifndef PLTFILEHANDLE_H
#define PLTFILEHANDLE_H
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

class pltFileHandle
{
public:
    pltFileHandle();
    QPainterPath readPLT(QString filename);
};

#endif // PLTFILEHANDLE_H
