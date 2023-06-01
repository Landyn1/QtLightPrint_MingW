#pragma once


#include <QObject>
#include <QPainter>
#include <QtWidgets/qstyleoption.h>
#include<qgraphicsitem.h>
#include<qpainterpath.h>
#include<qfile.h>
class MyGraphicsLineItem : public QGraphicsPathItem
{
public:
    MyGraphicsLineItem(QGraphicsPathItem *parent = nullptr);
    ~MyGraphicsLineItem();
    //QRectF boundingRect() const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    enum { Type = 4 };
    QPainterPath ViewPath(int k=0);
    bool set_brush(double angle,double space);
    QPainterPath brushPath;
    void setBrushpath(QList<QLineF> lins,QLineF l,QList<QPointF> intersections,QPainterPath &path2,int k=0);
    void setLinsAndCurves(QPainterPath path2,QList<QLineF> &lins);
    double angle = 0;
    double space = 0;
    int type() const
    {
        // 针对该 item 启用 qgraphicsitem_cast
        return Type;
    }
    void rotateY();
    void rotateX();
    bool readPLT(QString file);
    int printLayer = 0;
    bool selectEvent(QPointF p,int k=0);
    QString name="";
    bool isOnLine(QLine l , QPoint p);
    QRectF getRect();
    QRect rect()
    {
        return QRect(0,0,0,0);
    }
private:
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
signals:

};

