#pragma once

#include <QGraphicsView>
#include<qgraphicsitem.h>
#include"GraphicsItems/MyGraphicsRecItem.h"
#include "GraphicsItems/MyGraphicsEllipseItem.h"
#include"GraphicsItems/MyGraphicsCircleItem.h"
#include"GraphicsItems/MyKedu.h"
#include"GraphicsItems/MygraphicsLinePre.h"
#include"GraphicsItems/MyMianArea.h"
#include"GraphicsItems/MyleftKedu.h"
#include<qrect.h>
#include<QKeyEvent>
#include"GraphicsItems/mygraphicslineitem.h"
#include"GraphicsItems/mygraphicspolygonitem.h"
#include"GraphicsItems/mygraphicstextitem.h"
#include"GraphicsItems/mygraphicscurvelineitem.h"
#include"GraphicsItems/mygraphicspixmapitem.h"

class QMenu;
class QMouseEvent;
class QResizeEvent;
class QWidget;
class QPoint;
class QStatusBar;
class QLabel;
class QGraphicsPathItem;
class QGraphicsLineItem;
class ItemAdjust;
class MyGraphicsView  : public QGraphicsView
{
	Q_OBJECT

public:

    QList<QGraphicsItem*> sceneItems;
    MyKedu* topkedu = new MyKedu();
    MygraphicsLinePre* myGrid = new MygraphicsLinePre();
    MyMianArea* mainarea = new MyMianArea(NULL);
    MyleftKedu* leftkedu = new MyleftKedu();
    ItemAdjust* itemad;
    QRectF p ;
    bool moveble;
    bool lefttop_move;
    bool midtop_move;
    bool righttop_move;
    bool leftbuttom_move;
    bool midbuttom_move;
    bool rightbuttom_move;
    bool leftmid_move;
    bool rightmid_move;
    int lan = 0;
    QList<int> selectedId;
    bool isPaintLine = false;
    bool isPaintCurve = false;
    int item_id = 1;
    int row = 0;
    QPointF lastPos;
    double angle = 0;
    double space = 0 ;



    MyGraphicsView(QWidget* parent = NULL);
    ~MyGraphicsView();
    void wheelEvent(QWheelEvent* event) Q_DECL_OVERRIDE;
    void preProcessItem();
    void setStatusBarPtr(QStatusBar* statusBarPtr);
    void mouseReleaseEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void keyReleaseEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void save_lefttop();
    //void enterEvent(QEvent *event) Q_DECL_OVERRIDE;
    void leaveEvent(QEvent *event) Q_DECL_OVERRIDE;
    void midtop_set(QPointF p1,QPointF p2);
    void lefttop_set(QPointF p1,QPointF p2);
    void righttop_set(QPointF p1,QPointF p2);
    void leftbuttom_set(QPointF p1,QPointF p2);
    void midbuttom_set(QPointF p1,QPointF p2);
    void rightbuttom_set(QPointF p1,QPointF p2);
    void leftmid_set(QPointF p1,QPointF p2);
    void rightmid_set(QPointF p1,QPointF p2);
    void setItemAd(QList<QGraphicsItem*> items);
    void setSelecT();

private:
   // QMenu* _generalMenu;              // 主要的右键菜单

   // QPoint* _graphicsRightMousePos;    // 记录触发右键菜单的鼠标位置
    //bool                            _isRightMousePopMenu;       // 动作是否由右键菜单触发

    QPoint                          _lastMousePos;              // 用于鼠标移动事件中记录上次鼠标位置的变量

    MyGraphicsRecItem* _tempRectItemPtr = new MyGraphicsRecItem();
    MyGraphicsEllipseItem* _tempEllipseItemPtr = new MyGraphicsEllipseItem();       // 临时用来添加新圆形对象的指针
    MyGraphicsCircleItem* _tempCircleItemPtr = new MyGraphicsCircleItem();       // 临时用来添加新圆形对象的指针
    MyGraphicsLineItem                  *_tempLineItemPtr = new MyGraphicsLineItem();
    QPainterPath                        *_tempLinePath = new QPainterPath();
    MyGraphicsCurveLineItem             *_tempCurveItemPtr = new MyGraphicsCurveLineItem();
    QPainterPath                        *_tempCurvePath = new QPainterPath();
    MyGraphicsPolygonItem               *_tempPolygonItemPtr = new MyGraphicsPolygonItem();
    //MyGraphicsTextItem                  *_tempTextItemPtr = new MyGraphicsTextItem();
    MyGraphicsPixMapItem                *_tempPixMapItemPtr = new MyGraphicsPixMapItem();
    QStatusBar* _statusBarPtr;             // 指向主窗口状态栏的对象
    QLabel* _posLabel;                 // 状态栏位置指示对象
    QLabel* _objLabel;                 // 状态栏对象指示
    QLabel* _scaleLabel;
    QColor backgroundColor{ Qt::white };//背景色
    QColor textAndLineColor{ Qt::black };//文本和刻度颜色
    QColor slidingLineColor{ "#D56161" };//游标颜色
    Qt::Orientations orientation;
    int slidingLinePos{ 0 };
    int offset{ 0 };
    QFont font{ "微软雅黑",8 };


    
signals:
    void mouseMovePos(QPoint p);
    void ScaleChanged(double p);
    void addItem(int row,QGraphicsItem * item);
    void sceneChange();
    void selectchange();
    void mouseleave(int k);
    void removeItem(int id);
};
