#pragma once

#include <QObject>
#include <QPainter>
#include <QtWidgets/qstyleoption.h>
#include<qgraphicsitem.h>
class MyGraphicsEllipseItem  : public QGraphicsEllipseItem
{


public:
	MyGraphicsEllipseItem(QGraphicsEllipseItem *parent=NULL);
	~MyGraphicsEllipseItem();
	QRectF boundingRect() const;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
	enum { Type = 2 };
    QPainterPath brushpath;
    double angle = 0;
    int linenum = 0;
    void set_brush(double angle,int linenum);
    bool selectEvent(QPointF p,int k=0);
	int type() const
	{
		// 针对该 item 启用 qgraphicsitem_cast
		return Type;
	}
    int printLayer = 0;
    QPainterPath ViewPath();
    QString name="";
    QRect getRect();
    QPainterPath path()
    {
        QPainterPath p;
        return p;
    }
private:
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};
