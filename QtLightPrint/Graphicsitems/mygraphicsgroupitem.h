#ifndef MYGRAPHICSGROUPITEM_H
#define MYGRAPHICSGROUPITEM_H

#include <QObject>
#include<qgraphicsitem.h>
class MyGraphicsGroupItem :public QGraphicsItemGroup
{
public:
    int printLayer = 0;
    QString name="";
    QRectF rectf;
    QPainterPath brushPath;
    double angle = 0;
    double space = 0;


    MyGraphicsGroupItem(QList<QGraphicsItem*> items);
    ~MyGraphicsGroupItem();
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    enum { Type = 10 };
    bool selectEvent(QPointF p);
    int type() const
    {
        // 针对该 item 启用 qgraphicsitem_cast
        return Type;
    }
    void setRectF();
    QPainterPath ViewPath(int k=0);
    QRect getRect();
    template<typename T> QPainterPath getpath(QGraphicsItem* node,QPainterPath &path);
    bool set_brush(double angle,double space);
    void setBrushpath(QList<QLineF> lins,QLineF l,QList<QPointF> intersections,QPainterPath &path2,QPainterPath path,int k=0);
    void setLinsAndCurves(QPainterPath path2,QList<QLineF> &lins);
    QPainterPath path()
    {
        QPainterPath p;
        return p;
    }

};

#endif // MYGRAPHICSGROUPITEM_H
