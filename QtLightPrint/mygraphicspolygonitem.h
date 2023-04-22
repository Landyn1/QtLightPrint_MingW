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
    MyGraphicsPolygonItem(QGraphicsRectItem *parent = nullptr);
    ~MyGraphicsPolygonItem();

    QPainterPath ViewPath();
    QRectF boundingRect() const
    {
        return rect();
    }

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    enum { Type = 5 };
    bool set_brush(double jiaodu,int midu);
    int type() const
    {
        // 针对该 item 启用 qgraphicsitem_cast
        return Type;
    }
    int printLayer = 0;

    QString name="";
    int num = 5;
    bool selectEvent(QPointF p);
    QPainterPath path;
    void setPath(QPainterPath path);
    QPainterPath brushpath;
    double jiaodu = 0;
    int midu = 0;
    void setDefault_Path();
    bool isOnLine(QLine l , QPoint p);
    QRect getRect();
private:
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
signals:

};

#endif // MYGRAPHICSPOLYGONITEM_H
