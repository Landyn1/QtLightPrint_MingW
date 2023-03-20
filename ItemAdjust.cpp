#include "ItemAdjust.h"
#include<qpainter.h>
#include<qdebug.h>

ItemAdjust::ItemAdjust(QGraphicsItem* parent) : QGraphicsRectItem(parent)
{


}
QRectF ItemAdjust::boundingRect() const
{
	QRectF temp_rect = rect();
	
	return temp_rect;

}
void ItemAdjust::setRec(QRectF f)
{
	rec = f;
	lefttop = QRectF(0, rec.height() + (15 / scale), 5 / scale, 5 / scale);
	midtop = QRectF((10 / scale) + (rec.width() / 2), rec.height() + (15 / scale), 5 / scale, 5 / scale);
	righttop = QRectF(rec.width() + (15 / scale), rec.height() + (15 / scale), 5 / scale, 5 / scale);
	leftbuttom = QRectF(0, 0, 5 / scale, 5 / scale);
	midbuttom = QRectF((10 / scale) + (rec.width() / 2), 0, 5 / scale, 5 / scale);
	rightbuttom = QRectF(rec.width() + (15 / scale), 0, 5 / scale, 5 / scale);
	leftmid = QRectF(0, (10 / scale) + (rec.height() / 2), 5 / scale, 5 / scale);
	rightmid = QRectF(rec.width() + (15 / scale), (10 / scale) + (rec.height() / 2), 5 / scale, 5 / scale);

    mid = QRectF((10 / scale) + (rec.width() / 2), (10 / scale) + (rec.height() / 2), 8 / scale, 8 / scale);

    scene()->update();

}
void ItemAdjust::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	QPen pen;
	pen.setWidth(1);
	pen.setColor(QColor(Qt::black));
	painter->setPen(pen);
	painter->setBrush(QBrush(QColor(Qt::black)));
	
	painter->drawRect(leftbuttom);
	painter->drawRect(midbuttom);
	painter->drawRect(rightbuttom);
	painter->drawRect(lefttop);
	painter->drawRect(midtop);
	painter->drawRect(righttop);
	painter->drawRect(leftmid);
	painter->drawRect(rightmid);
	painter->drawLine(QPointF( mid.left(), mid.top()),QPointF(mid.right(),mid.bottom()));
	painter->drawLine(QPointF( mid.left(), mid.bottom()),QPointF(mid.right(),mid.top()));


	//painter->drawRect(QRectF(0, rect().height() + (15 / scale), 5 / scale, 5 / scale));

}

void ItemAdjust::mousePressEvent(QGraphicsSceneMouseEvent* event)
{

}
