#pragma once
#include<qgraphicsitem.h>
#include <QObject>

#include<qdebug.h>
class MygraphicsLinePre  : public QGraphicsItem
{


public:
	MygraphicsLinePre(QGraphicsItem *parent=NULL);
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)override ;
	~MygraphicsLinePre();

    enum { Type = 0 };

    int type() const
    {
        // 针对该 item 启用 qgraphicsitem_cast
        return Type;
    }
    //QRectF MygraphicsLinePre::sceneboundingRect() const
    //{
    //    //QRectF //temp_rect(-5000,-5000,10000,10000);
    //    return rect;
    //}
    QRectF boundingRect() const
    {
        QRectF temp_rect(-5000,-5000,10000,10000);
        
        return temp_rect;
    }
    void setshuzhi_Offset(double value)
    {
        shuzhi_offset = value;
        //qDebug() << shuzhi_offset << endl;
        update();
    }
    void setscales(double scale_m)
    {
        scale = scale_m;
        //this->setScale(1 / scale);
        update();
    }
    void setrect(QRectF rectt)
    {
        //qDebug() << rectt <<"    set" << endl;
        rect = rectt;
        update();
    }
private:
	double shuzhi_offset{ 0 };
	double shuiping_offset{ 0 };
    double scale = 1;
    QRectF rect;
};
