#ifndef MYGRAPHICSTEXTITEM_H
#define MYGRAPHICSTEXTITEM_H

#include <QObject>
#include <QWidget>
#include<qgraphicsitem.h>
#include<math.h>
#include"thirdcurve.h"
class MyGraphicsTextItem : public QGraphicsRectItem
{
public:
    MyGraphicsTextItem(QGraphicsTextItem *parent = NULL,QString str = "C");
    ~MyGraphicsTextItem();
    QPainterPath ViewPath(int k=0);
    QRectF boundingRect() const
    {
        return rect();
    }
    double f(double t,double p0,double p1,double p2,double p3)
    {
        return pow((1-t),3)*p0+3*t*pow((1-t),2)*p1 + 3*t*t*(1-t)*p2 + pow(t,3)*p3;
    }
    double getDeta(double a,double b,double c)
    {
        return b*b-4*a*c;
    }
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
    enum { Type = 6 };
    QPainterPath brushpath;
    double angle = 0;
    double space = 0;
    void set_brush(double angle,double space);
    int type() const
    {
        // 针对该 item 启用 qgraphicsitem_cast
        return Type;
    }
    void setBrushpath(QList<QLineF> lins,QList<ThirdCurve> curves,QLineF l,QList<QPointF> intersections,QPainterPath &path2,int k=0);
    void setLinsAndCurves(QPainterPath path2,QList<QLineF> &lins,QList<ThirdCurve> &curves);
    int printLayer = 0;
    QString str="";
    QRectF rectf;
    QString name="";
    QRectF getRect();
    QFont font = QFont(u8"微软雅黑",72);
    void setStr(QString str,QFont font);
    bool selectEvent(QPointF p,int k=0);
    void setRectF();
    QPainterPath path;
    void rotateY();
    void rotateX();
    void setDefault_Path();
    void makePath_fill_Rect();
    void setPath(QPainterPath path)
    {
        this->path.clear();
        this->path = path;
    }
private:
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // MYGRAPHICSTEXTITEM_H
