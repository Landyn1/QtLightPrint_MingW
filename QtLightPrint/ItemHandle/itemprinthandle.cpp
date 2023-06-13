#include "itemprinthandle.h"

ItemPrintHandle::ItemPrintHandle()
{

}


bool ItemPrintHandle::printItem(mainWindow *mw)
{
    QList<QGraphicsItem*> items = mw->scene->items();
    CUOpenDevice();

    CULaserOut(ST_MO, 1, 3);
    for (QList<QGraphicsItem*>::iterator it = items.begin(); it != items.end(); it++)
    {
        QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);
        int id = node->data(0).value<int>();
        if(id>0)
        {
            if (node->type() == 1)
            {
                MyGraphicsRecItem* rect = qgraphicsitem_cast<MyGraphicsRecItem*>(*it);
                LightDraw(rect->ViewPath(), rect->printLayer,mw);
            }
            else if(node->type() == 2 )
            {
                MyGraphicsEllipseItem *item = qgraphicsitem_cast<MyGraphicsEllipseItem*>(*it);
                LightDraw(item->ViewPath(),item->printLayer,mw);
            }
            else if(node->type() == 3)
            {
                MyGraphicsCircleItem *item = qgraphicsitem_cast<MyGraphicsCircleItem*>(*it);
                LightDraw(item->ViewPath(),item->printLayer,mw);
            }
            else if(node->type() == 4)
            {
                MyGraphicsLineItem *item = qgraphicsitem_cast<MyGraphicsLineItem*>(*it);
                LightDraw(item->ViewPath(),item->printLayer,mw);
            }
            else if(node->type() == 5)
            {
                MyGraphicsPolygonItem *item = qgraphicsitem_cast<MyGraphicsPolygonItem*>(*it);
                LightDraw(item->ViewPath(),item->printLayer,mw);
            }
            else if(node->type() == 6)
            {
                MyGraphicsTextItem *item = qgraphicsitem_cast<MyGraphicsTextItem*>(*it);
                LightDraw(item->ViewPath(),item->printLayer,mw);
            }
            else if(node->type() == 7)
            {
                MyGraphicsCurveLineItem *item = qgraphicsitem_cast<MyGraphicsCurveLineItem*>(*it);
                LightDraw(item->ViewPath(),item->printLayer,mw);
            }
            else if(node->type() == 8)
            {
                MyGraphicsPixMapItem *item = qgraphicsitem_cast<MyGraphicsPixMapItem*>(*it);
                LightDraw(item->pixmap(),item->printLayer,mw);
            }
            else if(node->type() == 9)
            {
                MyGraphicsCodeItem *item = qgraphicsitem_cast<MyGraphicsCodeItem *>(*it);
                LightDraw(item->ViewPath(),item->printLayer,mw);
            }
        }

    }
    CULaserOut(ST_MO, 0, 3);
    CUWriteBuf();

    CUSetNullDelayUs(50, 3);
    CULaserOut(6, 0, 3 );//AP
    CULaserOut(5, 0, 3);//MO
    CUBufFill(); //实际打印
    return true;
}
bool ItemPrintHandle::printRedItem(mainWindow *mw)
{
    QList<QGraphicsItem*> items = mw->scene->items();
    CUOpenDevice();
    CUIOOut(2, 1, 2);//开红光
    CUSetRedLight(1, 3);//设置红光状态，应该在此处同时开红光
    CULaserOut(ST_MO, 1, 3);
    for (QList<QGraphicsItem*>::iterator it = items.begin(); it != items.end(); it++)
    {
        QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);
        int id = node->data(0).value<int>();
        if(id>0)
        {
            if (node->type() == 1)
            {
                MyGraphicsRecItem* rect = qgraphicsitem_cast<MyGraphicsRecItem*>(*it);
                LightDraw(rect->ViewPath(), rect->printLayer,mw);
            }
            else if(node->type() == 2 )
            {
                MyGraphicsEllipseItem *item = qgraphicsitem_cast<MyGraphicsEllipseItem*>(*it);
                LightDraw(item->ViewPath(),item->printLayer,mw);
            }
            else if(node->type() == 3)
            {
                MyGraphicsCircleItem *item = qgraphicsitem_cast<MyGraphicsCircleItem*>(*it);
                LightDraw(item->ViewPath(),item->printLayer,mw);
            }
            else if(node->type() == 4)
            {
                MyGraphicsLineItem *item = qgraphicsitem_cast<MyGraphicsLineItem*>(*it);
                LightDraw(item->ViewPath(),item->printLayer,mw);
            }
            else if(node->type() == 5)
            {
                MyGraphicsPolygonItem *item = qgraphicsitem_cast<MyGraphicsPolygonItem*>(*it);
                LightDraw(item->ViewPath(),item->printLayer,mw);
            }
            else if(node->type() == 6)
            {
                MyGraphicsTextItem *item = qgraphicsitem_cast<MyGraphicsTextItem*>(*it);
                LightDraw(item->ViewPath(),item->printLayer,mw);
            }
            else if(node->type() == 7)
            {
                MyGraphicsCurveLineItem *item = qgraphicsitem_cast<MyGraphicsCurveLineItem*>(*it);
                LightDraw(item->ViewPath(),item->printLayer,mw);
            }
            else if(node->type() == 8)
            {
                MyGraphicsPixMapItem *item = qgraphicsitem_cast<MyGraphicsPixMapItem*>(*it);
                LightDraw(item->pixmap(),item->printLayer,mw);
            }
            else if(node->type() == 9)
            {
                MyGraphicsCodeItem *item = qgraphicsitem_cast<MyGraphicsCodeItem *>(*it);
                LightDraw(item->ViewPath(),item->printLayer,mw);
            }
        }

    }
    CULaserOut(ST_MO, 0, 3);
    CUWriteBuf();

    CUSetNullDelayUs(50, 3);
    CULaserOut(6, 0, 3 );//AP
    CULaserOut(5, 0, 3);//MO
    CUBufFill(); //实际打印
    CUSetRedLight(0, 3);//设置红光状态，应该在此处同时关红光

    CUIOOut(2, 0, 3);//关红光
    return true;
}
bool ItemPrintHandle::LightDraw(QPainterPath path,int printLayer,mainWindow *mw)
{
        unsigned int speed = mw->print_layer[printLayer].speed/100*65536;//转化
        CUSchSetSpeed(speed, 3);


        unsigned int frequnce = mw->print_layer[printLayer].frequence * 1000;
        CUSetPWM(PWM2, frequnce, 3, false);
        CUSetNullDelayUs(20000, 3);
        unsigned int power = mw->print_layer[printLayer].power * 2.56; //0-255之间代表0-100
        CULaserOut(ST_DATA, power, 3);
        CUSetNullDelayUs(100, 3);
        CULaserOut(ST_LATCH, 1, 3);
        CUSetNullDelayUs(5000, 3);
        CULaserOut(ST_LATCH, 0, 3);
        unsigned int openDealy = mw->print_layer[printLayer].openDelay;
        unsigned int closeDealy = mw->print_layer[printLayer].closeDelay;
        unsigned int endDealy = mw->print_layer[printLayer].endDelay;
        unsigned int turnDealy = mw->print_layer[printLayer].turnDelay;
        CUSetOpenDelayUs(openDealy,3);//2023-1-12
        CUSetCloseDelayUs(closeDealy, 3);//2023-1-13
        CUSetTuneDelayUs(turnDealy, 3);//2023-1-13
        CUSetNullDelayUs(5000, 3);
        //结束延时没找到啊

        //开始画
        //QPolygonF polu = path.toFillPolygon();

        for (int i = 0; i < path.elementCount(); i++)
        {
            QPainterPath::Element element = path.elementAt(i);
            QPointF po = element;
            QPoint printpo = view2print(po,mw);
            if (element.isMoveTo())
            {
                CUSchJmpLinear(printpo.x(), printpo.y(), 3);
            }
            else if (element.isLineTo())
            {
                CUSchOutLinear(printpo.x(), printpo.y(), 3);
            }
        }
    return true;

}
bool ItemPrintHandle::LightDraw(QPixmap pixmap,int printLayer,mainWindow *mw)
{

        unsigned int speed = mw->print_layer[printLayer].speed/100*65536;//转化
        CUSchSetSpeed(speed, 3);


        unsigned int frequnce = mw->print_layer[printLayer].frequence * 1000;
        CUSetPWM(PWM2, frequnce, 3, false);
        CUSetNullDelayUs(20000, 3);
        unsigned int power = mw->print_layer[printLayer].power * 2.56; //0-255之间代表0-100
        CULaserOut(ST_DATA, power, 3);
        CUSetNullDelayUs(100, 3);
        CULaserOut(ST_LATCH, 1, 3);
        CUSetNullDelayUs(5000, 3);
        CULaserOut(ST_LATCH, 0, 3);
        unsigned int openDealy = mw->print_layer[printLayer].openDelay;
        unsigned int closeDealy = mw->print_layer[printLayer].closeDelay;
        unsigned int endDealy = mw->print_layer[printLayer].endDelay;
        unsigned int turnDealy = mw->print_layer[printLayer].turnDelay;
        CUSetOpenDelayUs(openDealy,3);//2023-1-12
        CUSetCloseDelayUs(closeDealy, 3);//2023-1-13
        CUSetTuneDelayUs(turnDealy, 3);//2023-1-13
        CUSetNullDelayUs(5000, 3);
        //结束延时没找到啊

        //开始画
        //QPolygonF polu = path.toFillPolygon();
        QImage image= pixmap.toImage();
        QImage *gray_image = new QImage;
        *gray_image = image.convertToFormat(QImage::Format_Grayscale8,Qt::AutoColor);
        uchar *grayvalue = new uchar[gray_image->width()*gray_image->height()];
        int sum=0;
        int k=0;
        for(int i=0;i<gray_image->width();i++)
        {
            for(int j=0;j<gray_image->height();j++)
            {
                QImage tempimg = gray_image->copy(i,j,1,1);
                grayvalue[k] = *tempimg.bits() ;
                sum = sum + grayvalue[k];
               // qDebug()<<grayvalue[k]<<k<<endl;
                k++;
            }
        }
        int pj =  sum / k;

        for(int i=0;i<k;i++)
        {
            //qDebug()<<i<<pj<<grayvalue[i];
            if(grayvalue[i] <= pj)
                grayvalue[i] = 0;
            else
                grayvalue[i] = 255;
            //qDebug()<<grayvalue[i]<<endl;

        }

        CUSchSetSpeed(65851, 3);

        ushort w = gray_image->width();
        ushort h = gray_image->height();
        CUSetImgPara(w,h, 25, 25, 3);
        CUWriteBuf();//要把缓存写入到卡上去。
        byte* b = (byte *)grayvalue;

        CUOutImg(b, 10000, 25000);
        return true;

}
QPoint ItemPrintHandle::view2print(QPointF position,mainWindow *mw)
{
    double dpiX = QApplication::primaryScreen()->physicalDotsPerInchX();
    double dpiY = QApplication::primaryScreen()->physicalDotsPerInchY();
    auto tx = (dpiX * 10) / 254;
    auto ty = (dpiY * 10) / 254;

    QPointF p(position.x() / tx, position.y() / ty);

    int x = p.x() * 1000 + 0.5;
    int y = p.y() * 1000 + 0.5;
    double xx = double(x) / 1000;
    double yy = double(y) / 1000;
    QPointF pf((xx+50.000)*655.36*mw->spaceadjust, (yy+50.000)*655.36*mw->spaceadjust);
    QPoint pp = pf.toPoint();
    return pp;
}
