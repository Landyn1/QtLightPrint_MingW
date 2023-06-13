#ifndef MYGRAPHICSPOLYGONITEM_H
#define MYGRAPHICSPOLYGONITEM_H

#include <QObject>
#include <QQuickItem>
#include <QWidget>
#include<qgraphicsitem.h>
#include<qpainter.h>
#include<qpolygon.h>
#include<qpainterpath.h>
#include<qdebug.h>
class MyGraphicsPolygonItem : public QGraphicsRectItem
{
public:
    int printLayer = 0;
    QString name="";
    int num = 5;
    QPainterPath path;
    QPainterPath brushpath;
    double angle = 0;
    double space = 0;


    MyGraphicsPolygonItem(QGraphicsRectItem *parent = nullptr);
    ~MyGraphicsPolygonItem();
    void rotateY();
    void rotateX();
    QPainterPath ViewPath(int k=0);
    QRectF boundingRect() const
    {
        return rect();
    }
    void setBrushpath(QList<QLineF> lins,QLineF l,QList<QPointF> intersections,QPainterPath &path2,int k=0);
    void setLinsAndCurves(QPainterPath path2,QList<QLineF> &lins);
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    enum { Type = 5 };
    bool set_brush(double angle,double space);
    int type() const
    {
        // 针对该 item 启用 qgraphicsitem_cast
        return Type;
    }
    bool selectEvent(QPointF p,int k=0);
    void setPath(QPainterPath path);
    void setDefault_Path();
    bool isOnLine(QLine l , QPoint p);
    QRectF getRect();
private:
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
signals:

};

#endif // MYGRAPHICSPOLYGONITEM_H
