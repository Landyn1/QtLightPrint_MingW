#pragma once

#include <QGraphicsRectItem>
#include<qgraphicssceneevent.h>
#include<qgraphicsscene.h>
#include"mainWindow.h"
#include"GraphicsItems/MyGraphicsCircleItem.h"
#include"GraphicsItems/MyGraphicsEllipseItem.h"
#include"GraphicsItems/MyGraphicsRecItem.h"
#include"GraphicsItems/mygraphicslineitem.h"
#include"GraphicsItems/mygraphicspolygonitem.h"
#include"GraphicsItems/mygraphicstextitem.h"
#include"GraphicsItems/mygraphicscurvelineitem.h"
#include"GraphicsItems/mygraphicspixmapitem.h"
#include"GraphicsItems/mygraphicscodeitem.h"
#include"GraphicsItems/mygraphicsgroupitem.h"
class ItemAdjust : public QGraphicsRectItem
{
public:
	ItemAdjust(QGraphicsItem* parent = NULL);
	QRectF boundingRect() const;
	double scale = 1;
	QRectF rec = QRectF(0.0, 0.0, 0.00, 0.00);
    enum { Type = 0 };
    int type() const
    {
        // 针对该 item 启用 qgraphicsitem_cast
        return Type;
    }
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
    void setitemad(mainWindow* mw);
};

