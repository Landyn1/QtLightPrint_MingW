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

	int type() const
	{
		// 针对该 item 启用 qgraphicsitem_cast
		return Type;
	}
};
