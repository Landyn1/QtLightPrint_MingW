#pragma once

#include <QGraphicsView>
#include<qgraphicsitem.h>
#include"MyGraphicsRecItem.h"
#include "MyGraphicsEllipseItem.h"
#include"MyGraphicsCircleItem.h"
#include"MyKedu.h"
#include"MygraphicsLinePre.h"
#include"MyMianArea.h"
#include"MyleftKedu.h"
#include"ItemAdjust.h"
#include<qrect.h>
#include<QKeyEvent>
#include"mygraphicslineitem.h"
#include"mygraphicspolygonitem.h"
#include"mygraphicstextitem.h"
#include"mygraphicscurvelineitem.h"
#include"mygraphicspixmapitem.h"
class QMenu;
class QMouseEvent;
class QResizeEvent;
class QWidget;
class QPoint;
class QStatusBar;
class QLabel;
class QGraphicsPathItem;
class QGraphicsLineItem;

class MyGraphicsView  : public QGraphicsView
{
	Q_OBJECT

public:
	
	MyGraphicsView(QWidget* parent = NULL);
    
//MyGraphicsView(QWidget* parent);

    
    

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
    MyKedu* topkedu = new MyKedu();
    MygraphicsLinePre* myGrid = new MygraphicsLinePre();
    MyMianArea* mainarea = new MyMianArea(NULL);
    MyleftKedu* leftkedu = new MyleftKedu();
    ItemAdjust* itemad = new ItemAdjust();
    QRectF p ;
    bool moveble;
    bool lefttop_move;
    bool leftmid_move;
    void leftmid_set(QPointF p1,QPointF p2);
    void lefttop_set(QPointF p1,QPointF p2);
    void setItemAd(QList<QGraphicsItem*> items);
    QList<int> selectedId;
    bool isPaintLine = false;
    bool isPaintCurve = false;
    int item_id = 1;
    int row = 0;
    void setSelecT();
    QPointF lastPos;
private:
   // QMenu* _generalMenu;              // 主要的右键菜单

   // QPoint* _graphicsRightMousePos;    // 记录触发右键菜单的鼠标位置
    //bool                            _isRightMousePopMenu;       // 动作是否由右键菜单触发

    QPoint                          _lastMousePos;              // 用于鼠标移动事件中记录上次鼠标位置的变量

    //float                           _setRatioWidth;             // 设置的比例宽度
    //float                           _setRatioHeight;            // 设置的比例高度

    //float                           _selfScale;                 // 记录当前的绝对放缩比例

    //CustomGraphicsMainItem* _mainItem;                 // 窗口中间的主方框，代表打印机边界

    //EditMode                        _selfMode;                  // 当前的编辑模式
    //MyGraphicsRectItem* _tempRectItemPtr;          // 临时用来添加新矩形对象的指针
    MyGraphicsRecItem* _tempRectItemPtr = new MyGraphicsRecItem();
    MyGraphicsEllipseItem* _tempEllipseItemPtr = new MyGraphicsEllipseItem();       // 临时用来添加新圆形对象的指针
    MyGraphicsCircleItem* _tempCircleItemPtr = new MyGraphicsCircleItem();       // 临时用来添加新圆形对象的指针

//    QGraphicsPathItem               *_tempPathItemPtr;          // 临时用来创建新路径对象的指针
//    QPainterPath                    *_tempPath;                 // 临时用来存储新路径对象的路径指针
    //CustomGraphicsPolylineItem* _tempPathItemPtr;
   // bool                            _editLine = false;
    //    QGraphicsLineItem               *_tempLineItemPtr;          // 临时用来存储线的对象的路径指针
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

    void mouseleave(int k);
};
