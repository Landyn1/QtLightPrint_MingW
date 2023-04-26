#include <QGraphicsItem>
#include <QPainter>
#include <QtWidgets/qstyleoption.h>
#include<qgraphicsitem.h>
class MyGraphicsCodeItem: public QGraphicsRectItem
{
public:
    MyGraphicsCodeItem();
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    enum { Type = 9 };
    QRectF boundingRect() const;
    int type() const
    {
        // 针对该 item 启用 qgraphicsitem_cast
        return Type;
    }
    int printLayer = 0;
    QPainterPath ViewPath();
    QString name="";
    QString text="";
    ~MyGraphicsCodeItem();
    void setPathByStr(QString str,QString type);
    bool selectEvent(QPointF p);
    bool set_brush(double jiaodu,int midu);
    QRectF getRect();
    QPainterPath brushPath;
    QString codetype="";
    double jiaodu = 0;
    QPainterPath path;
    int midu = 0;
    void makePath_fill_Rect();
private:
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};


