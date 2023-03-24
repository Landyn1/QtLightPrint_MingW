#ifndef MYGRAPHICSTEXTITEM_H
#define MYGRAPHICSTEXTITEM_H

#include <QObject>
#include <QWidget>
#include<qgraphicsitem.h>

class MyGraphicsTextItem : public QGraphicsRectItem
{
public:
    MyGraphicsTextItem(QGraphicsTextItem *parent = NULL,QString str = "TEXT");
    ~MyGraphicsTextItem();

    QRectF boundingRect() const
    {
        return rect();
    }
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
    enum { Type = 6 };

    int type() const
    {
        // 针对该 item 启用 qgraphicsitem_cast
        return Type;
    }
    int printLayer = 0;
    QString str="";
    QRectF rectf;
    QString name="";
    QFont font = QFont(u8"微软雅黑",72);
    void setStr(QString str,QFont font);
    bool selectEvent(QPointF p);
    void setRectF();

private:
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // MYGRAPHICSTEXTITEM_H
