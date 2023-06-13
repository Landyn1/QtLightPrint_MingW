#ifndef PIXMAP_H
#define PIXMAP_H
#include <QObject>
#include<qgraphicsitem.h>
#include<qpainter.h>
#include<qpainterpath.h>
class MyGraphicsPixMapItem : public QGraphicsPixmapItem
{
public:

    int printLayer = 0;
    QString name="";
    QRect rectf;
    QString filename = "";

    MyGraphicsPixMapItem(QGraphicsPixmapItem *parent = nullptr);
    ~MyGraphicsPixMapItem();
    enum { Type = 8 };
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    int type() const
    {
        // 针对该 item 启用 qgraphicsitem_cast
        return Type;
    }
    QRectF boundingRect() const;
    QRectF rect();
    bool selectEvent(QPointF p,int k=0);
    void setDefault_Rect();
    void setRectF(QRect re);
    QRect getRect();
private:
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

};
#endif
