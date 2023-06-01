#pragma once

#include <QGraphicsRectItem>
#include<math.h>
#include<qdebug.h>
class QRectF;
class MyGraphicsRecItem  : public QGraphicsRectItem
{
	

public:
	explicit MyGraphicsRecItem(QGraphicsItem* parent = nullptr);
	explicit MyGraphicsRecItem(const QRectF& rect, QGraphicsItem* parent = nullptr);
	explicit MyGraphicsRecItem(qreal x, qreal y, qreal w, qreal h, QGraphicsItem* parent = nullptr);
	
	enum { Type = 1 };
    QRect getRect();
	int type() const
	{
		// 针对该 item 启用 qgraphicsitem_cast
		return Type;
	}
    void set_brush(double angle,double space);
	~MyGraphicsRecItem();
	QRectF boundingRect() const;
	QPainterPath shape() const;
    QPainterPath brushpath;

    QPainterPath path()
    {
        QPainterPath p;
        return p;
    }
    double angle = 0;
    double space = 0;
	//QRectF boundingRect() const;
	//QPainterPath shape() const;
	//QRectF boundingRect() const override;
	//QPainterPath shape() const override;
    QPainterPath ViewPath(int k=0);
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
    bool selectEvent(QPointF p,int k = 0);
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
