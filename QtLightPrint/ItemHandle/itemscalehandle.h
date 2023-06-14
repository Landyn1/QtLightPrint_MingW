#ifndef ITEMSCALEHANDLE_H
#define ITEMSCALEHANDLE_H

#include<QObject>
#include"GraphicsItems/MyGraphicsView.h"
class ItemScaleHandle
{
public:
    ItemScaleHandle(MyGraphicsView * view);
    MyGraphicsView * view;
    void changeScale(qreal currentscale,int wheelDeltaValue);
};

#endif // ITEMSCALEHANDLE_H
