#pragma once

#include <QGraphicsRectItem>
#include<math.h>
class QRectF;
class MyGraphicsRecItem  : public QGraphicsRectItem
{
	

public:
	explicit MyGraphicsRecItem(QGraphicsItem* parent = nullptr);
	explicit MyGraphicsRecItem(const QRectF& rect, QGraphicsItem* parent = nullptr);
	explicit MyGraphicsRecItem(qreal x, qreal y, qreal w, qreal h, QGraphicsItem* parent = nullptr);
	
	enum { Type = 1 };

	int type() const
	{
		// 针对该 item 启用 qgraphicsitem_cast
		return Type;
	}

	~MyGraphicsRecItem();
	QRectF boundingRect() const;
	QPainterPath shape() const;
	//QRectF boundingRect() const;
	//QPainterPath shape() const;
	//QRectF boundingRect() const override;
	//QPainterPath shape() const override;
	QPainterPath ViewPath();
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
    bool selectEvent(QPointF p);
	QString name = "";
	int printLayer = 0;
private:
	void initVaiables();
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    bool isOnLine(QLine l , QPoint p);
};
