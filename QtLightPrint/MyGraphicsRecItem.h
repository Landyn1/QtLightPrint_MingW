#pragma once

#include <QGraphicsRectItem>
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

	QString name = "";
	int printLayer = 0;
private:
	void initVaiables();
};
