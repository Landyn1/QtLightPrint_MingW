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
    double jiaodu = 0;
    int midu = 0;
    void set_brush(double jiaodu,int midu);
    bool selectEvent(QPointF p);
	int type() const
	{
		// 针对该 item 启用 qgraphicsitem_cast
		return Type;
	}
    int printLayer = 0;
    QPainterPath ViewPath();
    QString name="";
private:
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};
