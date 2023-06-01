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
    void rotateY();
    void rotateX();
    int type() const
    {
        // 针对该 item 启用 qgraphicsitem_cast
        return Type;
    }
    int printLayer = 0;
    QPainterPath ViewPath(int k=0);
    QString name="";
    QString text="";
    ~MyGraphicsCodeItem();
    void setPathByStr(QString str,QString type);
    bool selectEvent(QPointF p,int k=0);
    bool set_brush(double angle,double space);
    QRect getRect();
    QPainterPath brushPath;
    QString codetype="";
    double angle = 0;
    QPainterPath path;
    void setBrushpath(QList<QLineF> lins,QLineF l,QList<QPointF> intersections,QPainterPath &path2,int k=0);
    void setLinsAndCurves(QPainterPath path2,QList<QLineF> &lins);
    double space = 0;
    void makePath_fill_Rect();
private:
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};


