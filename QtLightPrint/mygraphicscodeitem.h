#include <QGraphicsItem>
#include <QPainter>
#include <QtWidgets/qstyleoption.h>
#include<qgraphicsitem.h>
class MyGraphicsCodeItem: public QGraphicsPathItem
{
public:
    MyGraphicsCodeItem();
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    enum { Type = 9 };
    QPointF duichengdian(QPointF p1 , QPointF p2);
    int type() const
    {
        // 针对该 item 启用 qgraphicsitem_cast
        return Type;
    }
    int printLayer = 0;
    QPainterPath ViewPath();
    QString name="";
    ~MyGraphicsCodeItem();
    void setPathByStr(QString str,QString type);
    bool selectEvent(QPointF p);
    QRectF getRect();
private:
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};


