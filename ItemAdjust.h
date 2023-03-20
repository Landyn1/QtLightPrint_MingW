#pragma once

#include <QGraphicsRectItem>
#include<qgraphicssceneevent.h>
#include<qgraphicsscene.h>
class ItemAdjust : public QGraphicsRectItem
{
public:
	ItemAdjust(QGraphicsItem* parent = NULL);
	QRectF boundingRect() const;
	double scale = 1;
	QRectF rec = QRectF(0.0, 0.0, 0.00, 0.00);

	QRectF lefttop;
	QRectF midtop;
	QRectF righttop;
	QRectF leftbuttom;
	QRectF midbuttom;
	QRectF rightbuttom;
	QRectF leftmid;
	QRectF rightmid;
	QRectF mid;
	void setRec(QRectF f);

    void mousePressEvent(QGraphicsSceneMouseEvent* event);
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
};

