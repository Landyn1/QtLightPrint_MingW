#include "MyGraphicsView.h"
#include"mainWindow.h"
#include <memory>
#include"ZXingWriter.h"
#include <QMenu>
#include <QPoint>
#include"MyKedu.h"
#include <QSize>
#include <QApplication>
#include <QDebug>
#include <QClipboard>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsPathItem>
#include <QGraphicsLineItem>
#include <QCursor>
#include <QMouseEvent>
#include <QLabel>
#include <QStatusBar>
#include<QApplication>
#include<QDesktopWidget>
#include<QtMath>
#include<QScreen>
#include"MyMianArea.h"
#include "MygraphicsLinePre.h"
#include<math.h>
#include"mygraphicscodeitem.h"
#include<qcursor.h>
#include"mygraphicsheplbrushrectitem.h"
MyGraphicsView::MyGraphicsView(QWidget *parent)
	: QGraphicsView(parent)
{
    
    
}

MyGraphicsView::~MyGraphicsView()
{}


void MyGraphicsView::leaveEvent(QEvent *event)
{

    if(isPaintLine )
    {
        emit mouseleave(0);
    }
    else if(isPaintCurve)
    {
        emit mouseleave(1);
    }
    else
    {
        emit mouseleave(2);
    }
}

void MyGraphicsView::save_lefttop()
{
    QList<QGraphicsItem *> itemss = scene()->items();
    for (QList<QGraphicsItem*>::iterator it = itemss.begin(); it != itemss.end(); it++)
    {
        QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);

        if(node->data(0).toInt()<0)
        {
            for(QList<QGraphicsItem*>::iterator itt = itemss.begin(); itt != itemss.end(); itt++)
            {
                QGraphicsItem* node2 = qgraphicsitem_cast<QGraphicsItem *>(*itt);
                if(node->data(1).toInt() == node2->data(0).toInt())
                {
                    if(node2->type()==1)
                    {
                        MyGraphicsRecItem *item1 = qgraphicsitem_cast<MyGraphicsRecItem*>(node);
                        MyGraphicsRecItem *item2 = qgraphicsitem_cast<MyGraphicsRecItem*>(node2);
                        //
                        QList<QPointF> list;
                        list.append(item1->mapToScene(item1->rect()).value(0));
                        list.append(item1->mapToScene(item1->rect()).value(2));
                        double w = qAbs(list[0].x()-list[1].x());
                        double h = qAbs(list[0].y()-list[1].y());
                        item2->setPos(fmin(list[0].x(),list[1].x())+(w/2),fmin(list[0].y(),list[1].y())+(h/2));
                        item2->setRect(-w/2,-h/2,w,h);
                        break;
                    }
                    else if(node2->type() == 2)
                    {
                        MyGraphicsEllipseItem *item1 = qgraphicsitem_cast<MyGraphicsEllipseItem*>(node);
                        MyGraphicsEllipseItem *item2 = qgraphicsitem_cast<MyGraphicsEllipseItem*>(node2);
                        //
                        QList<QPointF> list;
                        list.append(item1->mapToScene(item1->rect()).value(0));
                        list.append(item1->mapToScene(item1->rect()).value(2));
                        double minx = fmin(list[0].x(),list[1].x()), miny = fmin(list[0].y(),list[1].y());
                        double w = qAbs( list[1].x()-list[0].x());
                        double h = qAbs( list[1].y()-list[0].y());
                        item2->setPos(minx+(w/2),miny+(h/2));
                        item2->setRect(-w/2,-h/2,w,h);
                        break;
                    }
                    else if(node2->type() == 3)
                    {
                        MyGraphicsCircleItem *item1 = qgraphicsitem_cast<MyGraphicsCircleItem*>(node);
                        MyGraphicsCircleItem *item2 = qgraphicsitem_cast<MyGraphicsCircleItem*>(node2);
                        //
                        QList<QPointF> list;
                        list.append(item1->mapToScene(item1->rect()).value(0));
                        list.append(item1->mapToScene(item1->rect()).value(2));
                        double minx = fmin(list[0].x(),list[1].x()), miny = fmin(list[0].y(),list[1].y());
                        double w = qAbs( list[1].x()-list[0].x());
                        double h = qAbs( list[1].y()-list[0].y());
                        item2->setPos(minx+(w/2),miny+(h/2));
                        item2->setRect(-w/2,-h/2,w,h);
                        break;

                    }
                    else if(node2->type() == 4)
                    {
                        MyGraphicsLineItem *item1 = qgraphicsitem_cast<MyGraphicsLineItem*>(node);
                        MyGraphicsLineItem *item2 = qgraphicsitem_cast<MyGraphicsLineItem*>(node2);
                        item2->setPos(item1->pos());
                        item2->setPath(item1->path());
                        break;
                    }
                    else if(node2->type() == 5)
                    {
                        MyGraphicsPolygonItem *item1 = qgraphicsitem_cast<MyGraphicsPolygonItem*>(node);
                        MyGraphicsPolygonItem *item2 = qgraphicsitem_cast<MyGraphicsPolygonItem*>(node2);
                        //
                        QList<QPointF> list;
                        list.append(item1->mapToScene(item1->rect()).value(0));
                        list.append(item1->mapToScene(item1->rect()).value(2));
                        double minx = fmin(list[0].x(),list[1].x()), miny = fmin(list[0].y(),list[1].y());
                        double w = qAbs( list[1].x()-list[0].x());
                        double h = qAbs( list[1].y()-list[0].y());
                        item2->setPos(minx+(w/2),miny+(h/2));
                        item2->setRect(-w/2,-h/2,w,h);
                        item2->setDefault_Path();
                        break;
                    }
                    else if(node2->type() == 6)
                    {
                        MyGraphicsTextItem *item1 = qgraphicsitem_cast<MyGraphicsTextItem*>(node);
                        MyGraphicsTextItem *item2 = qgraphicsitem_cast<MyGraphicsTextItem*>(node2);
                        QList<QPointF> list;
                        list.append(item1->mapToScene(item1->rect()).value(0));
                        list.append(item1->mapToScene(item1->rect()).value(2));
                        double minx = fmin(list[0].x(),list[1].x()), miny = fmin(list[0].y(),list[1].y());
                        double w = qAbs( list[1].x()-list[0].x());
                        double h = qAbs( list[1].y()-list[0].y());
                        item2->setPos(minx+(w/2),miny+(h/2));
                        item2->setRect(-w/2,-h/2,w,h);
                        item2->setPath(item1->path);
                        break;
                    }
                    else if(node2->type() == 7)
                    {
                        MyGraphicsCurveLineItem *item1 = qgraphicsitem_cast<MyGraphicsCurveLineItem*>(node);
                        MyGraphicsCurveLineItem *item2 = qgraphicsitem_cast<MyGraphicsCurveLineItem*>(node2);
                        item2->setPos(item1->pos());
                        item2->setPath(item1->path());
                        break;
                    }
                    else if(node2->type() == 8)
                    {
                        MyGraphicsPixMapItem *item1 = qgraphicsitem_cast<MyGraphicsPixMapItem*>(node);
                        MyGraphicsPixMapItem *item2 = qgraphicsitem_cast<MyGraphicsPixMapItem*>(node2);
                        QList<QPointF> list;
                        list.append(item1->mapToScene(item1->rectf).value(0));
                        list.append(item1->mapToScene(item1->rectf).value(2));
                        //qDebug()<<list<<endl;
                        double minx = fmin(list[0].x(),list[1].x()), maxy = fmax(list[0].y(),list[1].y());
                        double w = qAbs( list[1].x()-list[0].x());
                        double h = qAbs( list[1].y()-list[0].y());
                        item2->setPos(minx,maxy);
                        item2->setRectF(QRect(0,-h,w,h));

                        break;
                    }
                    else if(node2->type() == 9)
                    {
                        MyGraphicsCodeItem *item1 = qgraphicsitem_cast<MyGraphicsCodeItem*>(node);
                        MyGraphicsCodeItem *item2 = qgraphicsitem_cast<MyGraphicsCodeItem*>(node2);
                        item2->setPos(item1->pos());
                        item2->setPath(item1->path());
                        break;
                    }
                }
            }
            scene()->removeItem(node);
        }
    }
    emit selectchange();
}

void MyGraphicsView::mouseReleaseEvent(QMouseEvent* event)
{

    //k=0;
    if(moveble || lefttop_move || righttop_move || leftbuttom_move || midbuttom_move || rightbuttom_move || leftmid_move || rightmid_move)
        k=0;
    if(lefttop_move || midtop_move || righttop_move || leftbuttom_move || midbuttom_move || rightbuttom_move || leftmid_move || rightmid_move)
    {
        save_lefttop();
    }
    moveble = false;
    lefttop_move = false;
    midtop_move = false;
    righttop_move = false;
    leftbuttom_move = false;
    midbuttom_move = false;
    rightbuttom_move = false;
    leftmid_move = false;
    rightmid_move = false;
    emit scene()->selectionChanged();

    scene()->update();
    if (event->button() == Qt::RightButton) {                 // 右键粘贴菜单
        //QPointF scene_pos = mapToScene(event->pos());       // 坐标映射
        //_graphicsRightMousePos->setX(scene_pos.x());        // 鼠标坐标记录--x
        //_graphicsRightMousePos->setY(scene_pos.y());        // 鼠标坐标记录--y
        //_isRightMousePopMenu = true;                        // 记录本次弹出了右键菜单
    }
    else if (event->button() == Qt::LeftButton) {
        if (action_state == 1) {
            
            _tempRectItemPtr->setVisible(false);
            if (_tempRectItemPtr->rect().width() > 5 ||
                _tempRectItemPtr->rect().height() > 5) {
                MyGraphicsRecItem* item = new MyGraphicsRecItem();
                QPointF p(_tempRectItemPtr->mapToScene(_tempRectItemPtr->rect()).value(0).x(),_tempRectItemPtr->mapToScene(_tempRectItemPtr->rect()).value(0).y());
                double w = _tempRectItemPtr->rect().width();
                double h = _tempRectItemPtr->rect().height();
                item->setRect(-w/2,-h/2,w,h);
                item->setPos(p+QPointF(w/2,h/2));
                item->setVisible(true);
                QString str = QString::number(row + 1);
                item->setData(0, item_id);
                item->name = u8"矩形" + str;
                scene()->addItem(item);
                update();
                emit addItem(row,item);
                row++;
                item_id++;
            }
        }
        else if (action_state == 2) {
           
            _tempEllipseItemPtr->setVisible(false);
            if (_tempEllipseItemPtr->rect().width() > 5 ||
                _tempEllipseItemPtr->rect().height() > 5) {
                MyGraphicsEllipseItem* item = new MyGraphicsEllipseItem();
                item->setRect(_tempEllipseItemPtr->rect());
                item->setPos(_tempEllipseItemPtr->pos());
                item->setVisible(true);
                QString str = QString::number(row + 1);
                item->setData(0, item_id);
                item->name = u8"椭圆" + str;
                scene()->addItem(item);
                update();
                emit addItem(row,item);
                row++;
                item_id++;
            }
        }
        else if (action_state == 3) {

            _tempCircleItemPtr->setVisible(false);
            if (_tempCircleItemPtr->rect().width() > 5 ||
                _tempCircleItemPtr->rect().height() > 5) {
                MyGraphicsCircleItem* item = new MyGraphicsCircleItem();
                item->setRect(_tempCircleItemPtr->rect());
                item->setPos(_tempCircleItemPtr->pos());
                item->setVisible(true);
                QString str = QString::number(row + 1);
                item->setData(0, item_id);
                item->name = u8"圆形" + str;
                scene()->addItem(item);
                update();
                emit addItem(row,item);
                row++;
                item_id++;
            }
        }
        else if(action_state == 5)
        {
            _tempPolygonItemPtr->setVisible(false);
            MyGraphicsPolygonItem *item = new MyGraphicsPolygonItem();
            item->setRect(_tempPolygonItemPtr->rect());
            item->setPath(_tempPolygonItemPtr->path);
            item->setPos(_tempPolygonItemPtr->pos());
            item->setVisible(true);
            QString str = QString::number(row + 1);
            item->setData(0, item_id);
            item->name = u8"多边形" + str;
            scene()->addItem(item);
            update();
            emit addItem(row,item);
            row++;
            item_id++;
        }
        else if(action_state == 7)
        {

            if(isPaintCurve == false)
            {
                isPaintCurve = true;
            }
            else
            {
                _tempCurveItemPtr->setIspaint(false);
                _tempCurvePath->cubicTo(_tempCurveItemPtr->ctl_pre,_tempCurveItemPtr->ctl_next,_tempCurveItemPtr->endP);
                _tempCurveItemPtr->setPath(*_tempCurvePath);
            }
            scene()->update();
        }
        /*else if (ModeManager::get_instance().isModeEq(EditMode::Lines)) {
            if (!_editLine) {
                _tempPathItemPtr->reset();
                _tempPathItemPtr->setVisible(true);
                _tempPathItemPtr->setPos(mapToScene(event->pos()));
                _tempPathItemPtr->addPoint(mapToScene(event->pos()));
            }
            _editLine = true;
            _tempPathItemPtr->addPoint(mapToScene(event->pos()));
            update();
        }*/
    }
    QGraphicsView::mouseReleaseEvent(event);
}

void MyGraphicsView::mousePressEvent(QMouseEvent* event)
{
    _lastMousePos = event->pos();
    lastPos = event->pos();
    moveble = QRectF(itemad->pos().x() + itemad->mid.x(), itemad->pos().y() + itemad->mid.y(), itemad->mid.width(), itemad->mid.height()).contains(mapToScene( event->pos()));
    lefttop_move = QRectF(itemad->pos().x() + itemad->lefttop.x(),itemad->pos().y() + itemad->lefttop.y(),itemad->lefttop.width(),itemad->lefttop.height()).contains(mapToScene(event->pos()));
    midtop_move = QRectF(itemad->pos().x() + itemad->midtop.x(),itemad->pos().y() + itemad->midtop.y(),itemad->midtop.width(),itemad->midtop.height()).contains(mapToScene(event->pos()));
    righttop_move = QRectF(itemad->pos().x() + itemad->righttop.x(),itemad->pos().y() + itemad->righttop.y(),itemad->righttop.width(),itemad->righttop.height()).contains(mapToScene(event->pos()));
    leftbuttom_move = QRectF(itemad->pos().x() + itemad->leftbuttom.x(),itemad->pos().y() + itemad->leftbuttom.y(),itemad->leftbuttom.width(),itemad->leftbuttom.height()).contains(mapToScene(event->pos()));
    midbuttom_move = QRectF(itemad->pos().x() + itemad->midbuttom.x(),itemad->pos().y() + itemad->midbuttom.y(),itemad->midbuttom.width(),itemad->midbuttom.height()).contains(mapToScene(event->pos()));
    rightbuttom_move = QRectF(itemad->pos().x() + itemad->rightbuttom.x(),itemad->pos().y() + itemad->rightbuttom.y(),itemad->rightbuttom.width(),itemad->rightbuttom.height()).contains(mapToScene(event->pos()));
    leftmid_move = QRectF(itemad->pos().x() + itemad->leftmid.x(),itemad->pos().y() + itemad->leftmid.y(),itemad->leftmid.width(),itemad->leftmid.height()).contains(mapToScene(event->pos()));
    rightmid_move = QRectF(itemad->pos().x() + itemad->rightmid.x(),itemad->pos().y() + itemad->rightmid.y(),itemad->rightmid.width(),itemad->rightmid.height()).contains(mapToScene(event->pos()));

    if(moveble || lefttop_move || midtop_move || righttop_move || leftbuttom_move || midbuttom_move || rightbuttom_move || leftmid_move ||rightmid_move)
        k=1;


    //if (ModeManager::get_instance().isModeEq(EditMode::Lines)) {
    //    if (event->button() == Qt::RightButton) {
    //        _tempPathItemPtr->setVisible(false);
    //        _tempPathItemPtr->undoPoint();
    //        CustomGraphicsPolylineItem* item = new CustomGraphicsPolylineItem(*_tempPathItemPtr);
    //        _tempPathItemPtr->reset();
    //        item->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
    //        item->setPos(_tempPathItemPtr->pos());
    //        item->setVisible(true);
    //        scene()->addItem(item);
    //        update();
    //        _editLine = false;
    //    }
    //}
    if(action_state == 0)
    {
        setSelecT();
    }

    else if (action_state == 1) {
    
        _tempRectItemPtr->setPos(mapToScene(_lastMousePos));
        _tempRectItemPtr->setRect(QRectF(0, 0, 0, 0));
        QPen pen;   // 定义一个画笔，设置画笔颜色和宽度
        //pen.setColor(QColor(0, 160, 230));
        pen.setWidthF(1);

        _tempRectItemPtr->setPen(pen);
        _tempRectItemPtr->setVisible(false);
    }
    else if (action_state==2) {
        _tempEllipseItemPtr->setPos(mapToScene(_lastMousePos));
        _tempEllipseItemPtr->setRect(QRectF(0, 0, 0, 0));
        //_tempEllipseItemPtr->setPen(ScaleManager::get_instance().getMainViewItemPen());
        QPen pen;   // 定义一个画笔，设置画笔颜色和宽度
//pen.setColor(QColor(0, 160, 230));
        pen.setWidthF(1);

        _tempEllipseItemPtr->setPen(pen);
        _tempEllipseItemPtr->setVisible(false);
       // scene()->addItem(_tempEllipseItemPtr);
    }
    else if (action_state == 3) {
        _tempCircleItemPtr->setPos(mapToScene(_lastMousePos));
        _tempCircleItemPtr->setRect(QRectF(0, 0, 0, 0));
        //_tempEllipseItemPtr->setPen(ScaleManager::get_instance().getMainViewItemPen());
        QPen pen;   // 定义一个画笔，设置画笔颜色和宽度
        pen.setWidthF(1);

        _tempCircleItemPtr->setPen(pen);
        _tempCircleItemPtr->setVisible(false);
        // scene()->addItem(_tempEllipseItemPtr);
    }
    else if (action_state == 4)
    {
        if (event->button() == Qt::LeftButton ) {

                    if(isPaintLine == false)
                    {
                        //QPainterPath tpath;
                        //tpath.moveTo(_lastMousePos);
                        _tempLinePath->moveTo(mapToScene(_lastMousePos));
                        _tempLineItemPtr->setPath(*_tempLinePath);

                        isPaintLine = true;
                    }
                    else
                    {
                        _tempLinePath->lineTo(mapToScene(_lastMousePos));
                        _tempLineItemPtr->setPath(*_tempLinePath);
                    }
        }
        else if(event->button() == Qt::RightButton)
        {
            isPaintLine = false;
            _tempLineItemPtr->setPath(*_tempLinePath);
            if( _tempLinePath->length()>1)
            {

                MyGraphicsLineItem *item = new MyGraphicsLineItem();
                item->setPath(_tempLineItemPtr->path());
                item->setVisible(true);
                item->setData(0, item_id);
                QString str = QString::number(row+1);
                item->name="直线"+str;
                scene()->addItem(item);
                emit addItem(row,item);
                row++;
                item_id++;
            }
            _tempLinePath->clear();
            _tempLineItemPtr->setVisible(false);


        }
    }

    else if(action_state == 5)
    {
        _tempPolygonItemPtr->setPos(mapToScene(_lastMousePos));
        _tempPolygonItemPtr->setRect(QRectF(0,0,0,0));
        QPen pen;   // 定义一个画笔，设置画笔颜色和宽度
        pen.setWidthF(1);
        _tempPolygonItemPtr->setPen(pen);
        _tempPolygonItemPtr->setVisible(false);
    }
    else if(action_state == 6)
    {
        QPointF p = mapToScene(_lastMousePos);
        MyGraphicsTextItem *item = new MyGraphicsTextItem();
        item->setPos(p);
        item->setRectF();

        item->setRect(-(item->rectf.width()/2),-(item->rectf.height()-item->rectf.height()/3*1.2)/2,item->rectf.width(),item->rectf.height()-item->rectf.height()/3*1.2);
        item->setDefault_Path();
        item->setRect(-item->path.boundingRect().width()/2,-item->path.boundingRect().height()/2,item->path.boundingRect().width(),item->path.boundingRect().height());
        item->makePath_fill_Rect();
        item->setVisible(true);
        item->setData(0, item_id);
        QString str = QString::number(row+1);
        item->name="文本"+str;
        scene()->addItem(item);
        scene()->update();
        emit addItem(row,item);
        row++;
        item_id++;

    }
    else if(action_state == 7)
    {
        if (event->button() == Qt::LeftButton ) {

                    _tempCurveItemPtr->setIspaint(true);
                    if(isPaintCurve == false)
                    {
                        //QPainterPath tpath;
                        //tpath.moveTo(_lastMousePos);
                        _tempCurveItemPtr->isfirst = true;
                        QPointF p =mapToScene(_lastMousePos);
                        _tempCurvePath->moveTo(p);
                        _tempCurveItemPtr->setPath(*_tempLinePath);
                        _tempCurveItemPtr->ctl_pre = p;
                        _tempCurveItemPtr->ctl_next = p;
                        _tempCurveItemPtr->endP = p;
                        _tempCurveItemPtr->startP = p;

                    }
                    else
                    {
                        _tempCurveItemPtr->isfirst = false;
                          QPointF p =mapToScene(_lastMousePos);
                          _tempCurveItemPtr->startP = _tempCurveItemPtr->endP;
                          _tempCurveItemPtr->endP = p;
                          _tempCurveItemPtr->ctl_pre = _tempCurveItemPtr->duichengdian(_tempCurveItemPtr->ctl_next,_tempCurveItemPtr->startP);
                          _tempCurveItemPtr->ctl_next = p;
//                        _tempLinePath->lineTo(mapToScene(_lastMousePos));
//                        _tempLineItemPtr->setPath(*_tempLinePath);
                    }
        }
        else if(event->button() == Qt::RightButton)
        {
            isPaintCurve = false;
            _tempCurveItemPtr->setPath(*_tempCurvePath);

            //qDebug()<<*_tempCurvePath<<endl;
            _tempCurvePath->clear();
            MyGraphicsCurveLineItem *item = new MyGraphicsCurveLineItem();
            item->setPath(_tempCurveItemPtr->path());
            item->setVisible(true);
            item->setData(0, item_id);
            QString str = QString::number(row+1);
            item->name="曲线"+str;
            scene()->addItem(item);
            emit addItem(row,item);
            row++;
            item_id++;
            _tempCurveItemPtr->setPath(*_tempCurvePath);
        }
    }
    else if(action_state == 9)
    {
        QPointF p = mapToScene(_lastMousePos);

        MyGraphicsCodeItem *item = new MyGraphicsCodeItem();

        item->setPathByStr("text","QRCode");
        double w = item->path().boundingRect().width();
        double h = item->path().boundingRect().height();
        item->setPos(p-QPointF(w/2,h/2));
        item->setData(0, item_id);
        QString str = QString::number(row+1);
        item->name="二维码"+str;
        scene()->addItem(item);
        scene()->update();
        emit addItem(row,item);
        row++;
        item_id++;
    }

    QGraphicsView::mousePressEvent(event);
}
void MyGraphicsView::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Control)
    {
        k = 1;
    }
    if(event->key() == Qt::Key_Backspace)
    {
        QList<QGraphicsItem*> items = scene()->selectedItems();
        for(int i=0;i<items.length();i++)
        {
            scene()->removeItem(items[i]);
            emit removeItem(items[i]->data(0).toInt());
        }

        scene()->update();
       return;
    }
    if(event->key() == Qt::Key_A)
    {
        qDebug()<<"test"<<endl;
        MyGraphicsHeplBrushRectItem *help = new MyGraphicsHeplBrushRectItem();
        help->setPos(0,0);
        help->jiaodu=30;
        help->midu=1000;
        help->setRect(-100,-100,200,200);
        scene()->addItem(help);
        scene()->update();
    }
}
void MyGraphicsView::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Control)
        k=0;

}

void MyGraphicsView::lefttop_set(QPointF p1,QPointF pressPos)
{
    QList<QGraphicsItem*> items = scene()->selectedItems();

    double s = this->matrix().m11();
    QList<QGraphicsItem *> itemss = scene()->items();
    for (QList<QGraphicsItem*>::iterator it = itemss.begin(); it != itemss.end(); it++)
    {
        QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);

        if(node->data(0).toInt()<0)
        {
            scene()->removeItem(node);
        }
    }
    QPointF roof;
    roof.setX(itemad->mapToScene(itemad->rect()).value(1).x()-10/s);
    roof.setY(itemad->mapToScene(itemad->rect()).value(1).y()+10/s);
    for (QList<QGraphicsItem*>::iterator it = items.begin(); it != items.end(); it++)
    {
        QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);
        if(node->type() == 1)
        {
            MyGraphicsRecItem* item = qgraphicsitem_cast<MyGraphicsRecItem *>(node);
            QPointF p2 = item->mapToScene(item->rect()).value(0);
            QPointF p3 = item->mapToScene(item->rect()).value(2);
            MyGraphicsRecItem *tmp = new MyGraphicsRecItem();
            QPointF poss (p3.x(),p2.y());
            double t1 = (pressPos.x()-p1.x())/(itemad->rec.width());
            double t2 = (p1.y()-pressPos.y())/(itemad->rec.height());
            double bili = 1;
            if(t1>0&&t2>0)
            {
                bili = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                bili = fmax(t1,t2);
            }
            else
            {
                bili = fmin(t1,t2);
            }

            tmp->setPos((poss-roof)*bili+poss);
            tmp->setRect(-item->rect().width()*(1+bili),0,item->rect().width()*(1+bili),item->rect().height()*(1+bili));
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 2)
        {
            MyGraphicsEllipseItem* item = qgraphicsitem_cast<MyGraphicsEllipseItem *>(node);
            QPointF p2 = item->mapToScene(item->rect()).value(0);
            QPointF p3 = item->mapToScene(item->rect()).value(2);
            MyGraphicsEllipseItem *tmp = new MyGraphicsEllipseItem();
            double w = p3.x()-p2.x(),h = p3.y()-p2.y();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t1 = (pressPos.x()-p1.x())/(itemad->rec.width());
            double t2 = (p1.y()-pressPos.y())/(itemad->rec.height());
            double bili = 1;
            if(t1>0&&t2>0)
            {
                bili = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                bili = fmax(t1,t2);
            }
            else
            {
                bili = fmin(t1,t2);
            }

            tmp->setPos((poss-roof)*bili+poss);
            tmp->setRect(-item->rect().width()*(1+bili)/2,-item->rect().height()*(1+bili)/2,item->rect().width()*(1+bili),item->rect().height()*(1+bili));
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 3)
        {
            MyGraphicsCircleItem* item = qgraphicsitem_cast<MyGraphicsCircleItem *>(node);
            QPointF p2 = item->mapToScene(item->rect()).value(0);
            QPointF p3 = item->mapToScene(item->rect()).value(2);
            MyGraphicsCircleItem *tmp = new MyGraphicsCircleItem();
            double w = p3.x()-p2.x(),h = p3.y()-p2.y();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t1 = (pressPos.x()-p1.x())/(itemad->rec.width());
            double t2 = (p1.y()-pressPos.y())/(itemad->rec.height());
            double bili = 1;
            if(t1>0&&t2>0)
            {
                bili = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                bili = fmax(t1,t2);
            }
            else
            {
                bili = fmin(t1,t2);
            }

            tmp->setPos((poss-roof)*bili+poss);
            tmp->setRect(-item->rect().width()*(1+bili)/2,-item->rect().height()*(1+bili)/2,item->rect().width()*(1+bili),item->rect().height()*(1+bili));
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 4)
        {
            MyGraphicsLineItem *item = qgraphicsitem_cast<MyGraphicsLineItem *>(node);
            QRectF rect = item->getRect();
            QPointF p2 (rect.x(),rect.y());
            QPointF p3 (rect.x()+rect.width(),rect.y()+rect.height());
            MyGraphicsLineItem *tmp = new MyGraphicsLineItem();
            double w = p3.x()-p2.x(),h = p3.y()-p2.y();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t1 = (pressPos.x()-p1.x())/(itemad->rec.width());
            double t2 = (p1.y()-pressPos.y())/(itemad->rec.height());
            double bili = 1;
            if(t1>0&&t2>0)
            {
                bili = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                bili = fmax(t1,t2);
            }
            else
            {
                bili = fmin(t1,t2);
            }
            QPainterPath path1 = item->path();
            QPainterPath path2 ;
            tmp->setPos((poss-roof)*bili+poss);
            QPointF offset = tmp->pos() - item->pos();
            for (int i = 0; i < path1.elementCount(); i++)
            {
                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(bili)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
            }
            tmp->name = item->name;
            tmp->setPath(path2);
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 5)
        {
            MyGraphicsPolygonItem *item = qgraphicsitem_cast<MyGraphicsPolygonItem *>(node);
            QRectF rect = item->getRect();
            QPointF p2 (rect.x(),rect.y());
            QPointF p3 (rect.x()+rect.width(),rect.y()+rect.height());
            MyGraphicsPolygonItem *tmp = new MyGraphicsPolygonItem();
            double w = p3.x()-p2.x(),h = p3.y()-p2.y();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t1 = (pressPos.x()-p1.x())/(itemad->rec.width());
            double t2 = (p1.y()-pressPos.y())/(itemad->rec.height());
            double bili = 1;
            if(t1>0&&t2>0)
            {
                bili = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                bili = fmax(t1,t2);
            }
            else
            {
                bili = fmin(t1,t2);
            }
            tmp->num = item->num;
            tmp->setPos((poss-roof)*bili+poss);
            tmp->setRect(-item->rect().width()*(1+bili)/2,-item->rect().height()*(1+bili)/2,item->rect().width()*(1+bili),item->rect().height()*(1+bili));
            tmp->setDefault_Path();
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 6)
        {
            MyGraphicsTextItem* item = qgraphicsitem_cast<MyGraphicsTextItem *>(node);
            QPointF p2 = item->mapToScene(item->rect()).value(0);
            QPointF p3 = item->mapToScene(item->rect()).value(2);
            MyGraphicsTextItem *tmp = new MyGraphicsTextItem();
            double w = p3.x()-p2.x(),h = p3.y()-p2.y();
            QPointF poss = item->pos();
            double t1 = (pressPos.x()-p1.x())/(itemad->rec.width());
            double t2 = (p1.y()-pressPos.y())/(itemad->rec.height());
            double bili = 1;
            if(t1>0&&t2>0)
            {
                bili = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                bili = fmax(t1,t2);
            }
            else
            {
                bili = fmin(t1,t2);
            }
            QPainterPath path1 = item->path;
            QPainterPath path2 ;
            int k=0;
            QPointF c1,c2;
            tmp->setPos((poss-roof)*bili+poss);
            QPointF offset = tmp->pos() - item->pos();   //用来计算path2的pos差值
            for (int i = 0; i < path1.elementCount(); i++)
            {

                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(bili)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
                else if(element.isCurveTo())
                {

                    c1 = po2;
                    k++;
                    //path2.cubicTo(po2);
                }
                else
                {
                    if(k%3 == 1)
                    {

                        c2 = po2;
                        k++;
                    }
                    else if(k%3 == 2)
                    {
                        path2.cubicTo(c1,c2,po2);
                        k++;
                    }

                }
            }
            tmp->setRect(-(item->rect().width()*(1+bili))/2,-(item->rect().height()*(1+bili))/2,item->rect().width()*(1+bili),item->rect().height()*(1+bili));
            tmp->setPath(path2);
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 7)
        {
            MyGraphicsCurveLineItem *item = qgraphicsitem_cast<MyGraphicsCurveLineItem *>(node);
            QList<double> list = item->getRect();
            MyGraphicsCurveLineItem *tmp = new MyGraphicsCurveLineItem();
            QPointF poss = item->pos();
            double t1 = (pressPos.x()-p1.x())/(itemad->rec.width());
            double t2 = (p1.y()-pressPos.y())/(itemad->rec.height());
            double bili = 1;
            if(t1>0&&t2>0)
            {
                bili = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                bili = fmax(t1,t2);
            }
            else
            {
                bili = fmin(t1,t2);
            }
            QPainterPath path1 = item->path();
            QPainterPath path2 ;
            int k=0;
            QPointF c1,c2;
            tmp->setPos((poss-roof)*bili+poss);
            QPointF offset = tmp->pos() - item->pos();   //用来计算path2的pos差值
            for (int i = 0; i < path1.elementCount(); i++)
            {

                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(bili)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
                else if(element.isCurveTo())
                {

                    c1 = po2;
                    k++;
                    //path2.cubicTo(po2);
                }
                else
                {
                    if(k%3 == 1)
                    {

                        c2 = po2;
                        k++;
                    }
                    else if(k%3 == 2)
                    {
                        path2.cubicTo(c1,c2,po2);
                        k++;
                    }

                }
            }

            tmp->setPath(path2);
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 8)
        {
            MyGraphicsPixMapItem* item = qgraphicsitem_cast<MyGraphicsPixMapItem *>(node);
            MyGraphicsPixMapItem *tmp = new MyGraphicsPixMapItem();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t1 = (pressPos.x()-p1.x())/(itemad->rec.width());
            double t2 = (p1.y()-pressPos.y())/(itemad->rec.height());
            double bili = 1;
            if(t1>0&&t2>0)
            {
                bili = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                bili = fmax(t1,t2);
            }
            else
            {
                bili = fmin(t1,t2);
            }
            tmp->setPixmap(item->pixmap());
            tmp->setPos((poss-roof)*bili+poss);
            double w = qAbs(item->rect().width()*(1+bili));
            double h = qAbs(item->rect().height()*(1+bili));
            if(item->rect().width()*(1+bili)<0)
            {
                tmp->setPos((poss-roof)*bili+poss-QPointF(w,h));
            }

            tmp->setRectF(QRect(0,-h,w,h));
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 9)
        {
            MyGraphicsCodeItem *item = qgraphicsitem_cast<MyGraphicsCodeItem *>(node);
            QRectF rect = item->getRect();
            QPointF p2 (rect.x(),rect.y());
            QPointF p3 (rect.x()+rect.width(),rect.y()+rect.height());
            MyGraphicsCodeItem *tmp = new MyGraphicsCodeItem();
            double w = p3.x()-p2.x(),h = p3.y()-p2.y();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t1 = (pressPos.x()-p1.x())/(itemad->rec.width());
            double t2 = (p1.y()-pressPos.y())/(itemad->rec.height());
            double bili = 1;
            if(t1>0&&t2>0)
            {
                bili = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                bili = fmax(t1,t2);
            }
            else
            {
                bili = fmin(t1,t2);
            }
            QPainterPath path1 = item->path();
            QPainterPath path2 ;
            tmp->setPos((poss-roof)*bili+poss);
            QPointF offset = tmp->pos() - item->pos();
            for (int i = 0; i < path1.elementCount(); i++)
            {
                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(bili)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
            }
            tmp->name = item->name;
            tmp->setPath(path2);
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
    }
    scene()->update();
}

void MyGraphicsView::midtop_set(QPointF p1,QPointF pressPos)
{
    QList<QGraphicsItem*> items = scene()->selectedItems();

    double s = this->matrix().m11();
    QList<QGraphicsItem *> itemss = scene()->items();
    for (QList<QGraphicsItem*>::iterator it = itemss.begin(); it != itemss.end(); it++)
    {
        QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);

        if(node->data(0).toInt()<0)
        {
            scene()->removeItem(node);
        }
    }
    QPointF roof;
    roof.setX(itemad->mapToScene(itemad->rect()).value(1).x()-10/s);
    roof.setY(itemad->mapToScene(itemad->rect()).value(1).y()+10/s);
    for (QList<QGraphicsItem*>::iterator it = items.begin(); it != items.end(); it++)
    {
        QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);
        if(node->type() == 1)
        {
            MyGraphicsRecItem* item = qgraphicsitem_cast<MyGraphicsRecItem *>(node);
            QPointF p2 = item->mapToScene(item->rect()).value(0);
            QPointF p3 = item->mapToScene(item->rect()).value(2);
            MyGraphicsRecItem *tmp = new MyGraphicsRecItem();
            QPointF poss (p3.x(),p2.y());
            double t2 = (p1.y()-pressPos.y())/(itemad->rec.height());
            double bili = t2;
            tmp->setPos(poss.x(),((poss-roof)*bili+poss).y());
            tmp->setRect(-item->rect().width(),0,item->rect().width(),item->rect().height()*(1+bili));
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 2)
        {
            MyGraphicsEllipseItem* item = qgraphicsitem_cast<MyGraphicsEllipseItem *>(node);
            QPointF p2 = item->mapToScene(item->rect()).value(0);
            QPointF p3 = item->mapToScene(item->rect()).value(2);
            MyGraphicsEllipseItem *tmp = new MyGraphicsEllipseItem();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t2 = (p1.y()-pressPos.y())/(itemad->rec.height());
            double bili = t2;

            tmp->setPos(poss.x(),((poss-roof)*bili+poss).y());
            tmp->setRect(-item->rect().width()/2,-item->rect().height()*(1+bili)/2,item->rect().width(),item->rect().height()*(1+bili));
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 3)
        {
            MyGraphicsCircleItem* item = qgraphicsitem_cast<MyGraphicsCircleItem *>(node);
            MyGraphicsCircleItem *tmp = new MyGraphicsCircleItem();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t2 = (p1.y()-pressPos.y())/(itemad->rec.height());
            double bili = t2;
            tmp->setPos(poss.x(),((poss-roof)*bili+poss).y());
            tmp->setRect(-item->rect().width()/2,-item->rect().height()*(1+bili)/2,item->rect().width(),item->rect().height()*(1+bili));
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 4)
        {
            MyGraphicsLineItem *item = qgraphicsitem_cast<MyGraphicsLineItem *>(node);
            QRectF rect = item->getRect();
            QPointF p2 (rect.x(),rect.y());
            QPointF p3 (rect.x()+rect.width(),rect.y()+rect.height());
            MyGraphicsLineItem *tmp = new MyGraphicsLineItem();
            double t2 = (p1.y()-pressPos.y())/(itemad->rec.height());
            double bili = t2;
            QPainterPath path1 = item->path();
            QPainterPath path2 ;
            QPointF poss = item->pos();
            tmp->setPos(poss.x(),((poss-roof)*bili+poss).y());
            QPointF offset = tmp->pos() - item->pos();

            for (int i = 0; i < path1.elementCount(); i++)
            {
                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(bili)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                po2.setX(item->mapFromScene(po).x());
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
            }
            tmp->setPath(path2);
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 5)
        {
            MyGraphicsPolygonItem *item = qgraphicsitem_cast<MyGraphicsPolygonItem *>(node);
            MyGraphicsPolygonItem *tmp = new MyGraphicsPolygonItem();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t2 = (p1.y()-pressPos.y())/(itemad->rec.height());
            double bili = t2;
            tmp->num = item->num;
            tmp->setPos(poss.x(),((poss-roof)*bili+poss).y());
            tmp->setRect(-item->rect().width()/2,-item->rect().height()*(1+bili)/2,item->rect().width(),item->rect().height()*(1+bili));
            tmp->setData(0,-1);
            tmp->setDefault_Path();
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 6)
        {
            MyGraphicsTextItem* item = qgraphicsitem_cast<MyGraphicsTextItem *>(node);
            MyGraphicsTextItem *tmp = new MyGraphicsTextItem();
            QPointF poss = item->pos();
            double t2 = (p1.y()-pressPos.y())/(itemad->rec.height());
            double bili = t2;
            QPainterPath path1 = item->path;
            QPainterPath path2 ;
            int k=0;
            QPointF c1,c2;
            tmp->setPos(poss.x(),((poss-roof)*bili+poss).y());
            QPointF offset = tmp->pos() - item->pos();   //用来计算path2的pos差值
            for (int i = 0; i < path1.elementCount(); i++)
            {

                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(bili)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                po2.setX(item->mapFromScene(po).x());
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
                else if(element.isCurveTo())
                {

                    c1 = po2;
                    k++;
                    //path2.cubicTo(po2);
                }
                else
                {
                    if(k%3 == 1)
                    {

                        c2 = po2;
                        k++;
                    }
                    else if(k%3 == 2)
                    {
                        path2.cubicTo(c1,c2,po2);
                        k++;
                    }

                }
            }
            tmp->setRect(-(item->rect().width())/2,-(item->rect().height()*(1+bili))/2,item->rect().width(),item->rect().height()*(1+bili));
            tmp->setPath(path2);
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 7)
        {
            MyGraphicsCurveLineItem* item = qgraphicsitem_cast<MyGraphicsCurveLineItem *>(node);
            MyGraphicsCurveLineItem *tmp = new MyGraphicsCurveLineItem();
            QPointF poss = item->pos();
            double t2 = (p1.y()-pressPos.y())/(itemad->rec.height());
            double bili = t2;
            QPainterPath path1 = item->path();
            QPainterPath path2 ;
            int k=0;
            QPointF c1,c2;
            tmp->setPos(poss.x(),((poss-roof)*bili+poss).y());
            QPointF offset = tmp->pos() - item->pos();   //用来计算path2的pos差值
            for (int i = 0; i < path1.elementCount(); i++)
            {

                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(bili)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                po2.setX(item->mapFromScene(po).x());
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
                else if(element.isCurveTo())
                {

                    c1 = po2;
                    k++;
                    //path2.cubicTo(po2);
                }
                else
                {
                    if(k%3 == 1)
                    {

                        c2 = po2;
                        k++;
                    }
                    else if(k%3 == 2)
                    {
                        path2.cubicTo(c1,c2,po2);
                        k++;
                    }

                }
            }
            tmp->setPath(path2);
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 8)
        {
            MyGraphicsPixMapItem* item = qgraphicsitem_cast<MyGraphicsPixMapItem *>(node);
            MyGraphicsPixMapItem *tmp = new MyGraphicsPixMapItem();
            QPointF poss = item->pos();
            double t2 = (p1.y()-pressPos.y())/(itemad->rec.height());
            double bili = t2;
            tmp->setPixmap(item->pixmap());
            tmp->setPos( poss.x(),((poss-roof)*bili+poss).y());
            double w = qAbs(item->rect().width());
            double h = qAbs(item->rect().height()*(1+bili));
            if(item->rect().height()*(1+bili)<0)
            {
                tmp->setPos(tmp->pos()-QPointF(0,h));
            }

            tmp->setRectF(QRect(0,-h,w,h));
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 9)
        {
            MyGraphicsCodeItem *item = qgraphicsitem_cast<MyGraphicsCodeItem *>(node);
            QRectF rect = item->getRect();
            QPointF p2 (rect.x(),rect.y());
            QPointF p3 (rect.x()+rect.width(),rect.y()+rect.height());
            MyGraphicsCodeItem *tmp = new MyGraphicsCodeItem();
            double t2 = (p1.y()-pressPos.y())/(itemad->rec.height());
            double bili = t2;
            QPainterPath path1 = item->path();
            QPainterPath path2 ;
            QPointF poss = item->pos();
            tmp->setPos(poss.x(),((poss-roof)*bili+poss).y());
            QPointF offset = tmp->pos() - item->pos();

            for (int i = 0; i < path1.elementCount(); i++)
            {
                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(bili)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                po2.setX(item->mapFromScene(po).x());
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
            }
            tmp->setPath(path2);
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
    }
    scene()->update();
}

void MyGraphicsView::righttop_set(QPointF p1, QPointF pressPos)
{
    QList<QGraphicsItem*> items = scene()->selectedItems();
    double s = this->matrix().m11();
    QList<QGraphicsItem *> itemss = scene()->items();
    for (QList<QGraphicsItem*>::iterator it = itemss.begin(); it != itemss.end(); it++)
    {
        QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);

        if(node->data(0).toInt()<0)
        {
            scene()->removeItem(node);
        }
    }
    QPointF roof;
    roof.setX(itemad->mapToScene(itemad->rect()).value(0).x()+10/s);
    roof.setY(itemad->mapToScene(itemad->rect()).value(0).y()+10/s);
    for (QList<QGraphicsItem*>::iterator it = items.begin(); it != items.end(); it++)
    {
        QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);
        if(node->type() == 1)
        {
            MyGraphicsRecItem* item = qgraphicsitem_cast<MyGraphicsRecItem *>(node);
            QPointF p2 = item->mapToScene(item->rect()).value(0);
            //QPointF p3 = item->mapToScene(item->rect()).value(2);
            MyGraphicsRecItem *tmp = new MyGraphicsRecItem();
            QPointF poss (p2);
            double t1 = (-pressPos.x()+p1.x())/(itemad->rec.width());
            double t2 = (p1.y()-pressPos.y())/(itemad->rec.height());
            double bili = 1;
            if(t1>0&&t2>0)
            {
                bili = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                bili = fmax(t1,t2);
            }
            else
            {
                bili = fmin(t1,t2);
            }

            tmp->setPos(poss);
            tmp->setRect(0,0,item->rect().width()*(1+bili),item->rect().height()*(1+bili));
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 2)
        {
            MyGraphicsEllipseItem* item = qgraphicsitem_cast<MyGraphicsEllipseItem *>(node);
            MyGraphicsEllipseItem *tmp = new MyGraphicsEllipseItem();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t1 = (-pressPos.x()+p1.x())/(itemad->rec.width());
            double t2 = (p1.y()-pressPos.y())/(itemad->rec.height());
            double bili = 1;
            if(t1>0&&t2>0)
            {
                bili = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                bili = fmax(t1,t2);
            }
            else
            {
                bili = fmin(t1,t2);
            }

            tmp->setPos((poss-roof)*bili+poss);
            tmp->setRect(-item->rect().width()*(1+bili)/2,-item->rect().height()*(1+bili)/2,item->rect().width()*(1+bili),item->rect().height()*(1+bili));
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 3)
        {
            MyGraphicsCircleItem* item = qgraphicsitem_cast<MyGraphicsCircleItem *>(node);
            MyGraphicsCircleItem *tmp = new MyGraphicsCircleItem();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t1 = (-pressPos.x()+p1.x())/(itemad->rec.width());
            double t2 = (p1.y()-pressPos.y())/(itemad->rec.height());
            double bili = 1;
            if(t1>0&&t2>0)
            {
                bili = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                bili = fmax(t1,t2);
            }
            else
            {
                bili = fmin(t1,t2);
            }

            tmp->setPos((poss-roof)*bili+poss);
            tmp->setRect(-item->rect().width()*(1+bili)/2,-item->rect().height()*(1+bili)/2,item->rect().width()*(1+bili),item->rect().height()*(1+bili));
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 4)
        {
            MyGraphicsLineItem *item = qgraphicsitem_cast<MyGraphicsLineItem *>(node);
            QRectF rect = item->getRect();
            MyGraphicsLineItem *tmp = new MyGraphicsLineItem();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t1 = (-pressPos.x()+p1.x())/(itemad->rec.width());
            double t2 = (p1.y()-pressPos.y())/(itemad->rec.height());
            double bili = 1;
            if(t1>0&&t2>0)
            {
                bili = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                bili = fmax(t1,t2);
            }
            else
            {
                bili = fmin(t1,t2);
            }
            QPainterPath path1 = item->path();
            QPainterPath path2 ;
            tmp->setPos((poss-roof)*bili+poss);
            QPointF offset = tmp->pos() - item->pos();
            for (int i = 0; i < path1.elementCount(); i++)
            {
                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(bili)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
            }

            tmp->setPath(path2);
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 5)
        {
            MyGraphicsPolygonItem *item = qgraphicsitem_cast<MyGraphicsPolygonItem *>(node);
            MyGraphicsPolygonItem *tmp = new MyGraphicsPolygonItem();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t1 = (-pressPos.x()+p1.x())/(itemad->rec.width());
            double t2 = (p1.y()-pressPos.y())/(itemad->rec.height());
            double bili = 1;
            if(t1>0&&t2>0)
            {
                bili = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                bili = fmax(t1,t2);
            }
            else
            {
                bili = fmin(t1,t2);
            }
            tmp->num = item->num;
            tmp->setPos((poss-roof)*bili+poss);
            tmp->setRect(-item->rect().width()*(1+bili)/2,-item->rect().height()*(1+bili)/2,item->rect().width()*(1+bili),item->rect().height()*(1+bili));
            tmp->setDefault_Path();
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 6)
        {
            MyGraphicsTextItem* item = qgraphicsitem_cast<MyGraphicsTextItem *>(node);
            MyGraphicsTextItem *tmp = new MyGraphicsTextItem();
            QPointF poss = item->pos();
            double t1 = (-pressPos.x()+p1.x())/(itemad->rec.width());
            double t2 = (p1.y()-pressPos.y())/(itemad->rec.height());
            double bili = 1;
            if(t1>0&&t2>0)
            {
                bili = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                bili = fmax(t1,t2);
            }
            else
            {
                bili = fmin(t1,t2);
            }
            QPainterPath path1 = item->path;
            QPainterPath path2 ;
            int k=0;
            QPointF c1,c2;
            tmp->setPos((poss-roof)*bili+poss);

            QPointF offset = tmp->pos() - item->pos();   //用来计算path2的pos差值
            for (int i = 0; i < path1.elementCount(); i++)
            {

                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(bili)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
                else if(element.isCurveTo())
                {

                    c1 = po2;
                    k++;
                    //path2.cubicTo(po2);
                }
                else
                {
                    if(k%3 == 1)
                    {

                        c2 = po2;
                        k++;
                    }
                    else if(k%3 == 2)
                    {
                        path2.cubicTo(c1,c2,po2);
                        k++;
                    }

                }
            }
            tmp->setRect(-(item->rect().width()*(1+bili))/2,-(item->rect().height()*(1+bili))/2,item->rect().width()*(1+bili),item->rect().height()*(1+bili));
            tmp->setPath(path2);
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 7)
        {
            MyGraphicsCurveLineItem *item = qgraphicsitem_cast<MyGraphicsCurveLineItem *>(node);
            QList<double> list = item->getRect();
            MyGraphicsCurveLineItem *tmp = new MyGraphicsCurveLineItem();
            QPointF poss = item->pos();
            double t1 = (-pressPos.x()+p1.x())/(itemad->rec.width());
            double t2 = (p1.y()-pressPos.y())/(itemad->rec.height());
            double bili = 1;
            if(t1>0&&t2>0)
            {
                bili = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                bili = fmax(t1,t2);
            }
            else
            {
                bili = fmin(t1,t2);
            }
            QPainterPath path1 = item->path();
            QPainterPath path2 ;
            int k=0;
            QPointF c1,c2;
            tmp->setPos((poss-roof)*bili+poss);
            QPointF offset = tmp->pos() - item->pos();   //用来计算path2的pos差值
            for (int i = 0; i < path1.elementCount(); i++)
            {

                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(bili)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
                else if(element.isCurveTo())
                {

                    c1 = po2;
                    k++;
                    //path2.cubicTo(po2);
                }
                else
                {
                    if(k%3 == 1)
                    {

                        c2 = po2;
                        k++;
                    }
                    else if(k%3 == 2)
                    {
                        path2.cubicTo(c1,c2,po2);
                        k++;
                    }

                }
            }

            tmp->setPath(path2);
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 8)
        {
            MyGraphicsPixMapItem* item = qgraphicsitem_cast<MyGraphicsPixMapItem *>(node);
            MyGraphicsPixMapItem *tmp = new MyGraphicsPixMapItem();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t1 = (-pressPos.x()+p1.x())/(itemad->rec.width());
            double t2 = (p1.y()-pressPos.y())/(itemad->rec.height());
            double bili = 1;
            if(t1>0&&t2>0)
            {
                bili = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                bili = fmax(t1,t2);
            }
            else
            {
                bili = fmin(t1,t2);
            }
            tmp->setPixmap(item->pixmap());
            tmp->setPos((poss-roof)*bili+poss);
            double w = qAbs(item->rect().width()*(1+bili));
            double h = qAbs(item->rect().height()*(1+bili));
            if(item->rect().width()*(1+bili)<0)
            {
                tmp->setPos((poss-roof)*bili+poss-QPointF(w,h));
            }

            tmp->setRectF(QRect(0,-h,w,h));
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 9)
        {
            MyGraphicsCodeItem *item = qgraphicsitem_cast<MyGraphicsCodeItem *>(node);
            QRectF rect = item->getRect();
            MyGraphicsCodeItem *tmp = new MyGraphicsCodeItem();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t1 = (-pressPos.x()+p1.x())/(itemad->rec.width());
            double t2 = (p1.y()-pressPos.y())/(itemad->rec.height());
            double bili = 1;
            if(t1>0&&t2>0)
            {
                bili = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                bili = fmax(t1,t2);
            }
            else
            {
                bili = fmin(t1,t2);
            }
            QPainterPath path1 = item->path();
            QPainterPath path2 ;
            tmp->setPos((poss-roof)*bili+poss);
            QPointF offset = tmp->pos() - item->pos();
            for (int i = 0; i < path1.elementCount(); i++)
            {
                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(bili)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
            }

            tmp->setPath(path2);
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
    }
    scene()->update();
}

void MyGraphicsView::leftbuttom_set(QPointF p1,QPointF pressPos)
{
    QList<QGraphicsItem*> items = scene()->selectedItems();
    double s = this->matrix().m11();
    QList<QGraphicsItem *> itemss = scene()->items();
    for (QList<QGraphicsItem*>::iterator it = itemss.begin(); it != itemss.end(); it++)
    {
        QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);

        if(node->data(0).toInt()<0)
        {
            scene()->removeItem(node);
        }
    }
    QPointF roof;
    roof.setX(itemad->mapToScene(itemad->rect()).value(2).x()-10/s);
    roof.setY(itemad->mapToScene(itemad->rect()).value(2).y()-10/s);
    for (QList<QGraphicsItem*>::iterator it = items.begin(); it != items.end(); it++)
    {
        QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);
        if(node->type() == 1)
        {
            MyGraphicsRecItem* item = qgraphicsitem_cast<MyGraphicsRecItem *>(node);
            QPointF p3 = item->mapToScene(item->rect()).value(2);
            MyGraphicsRecItem *tmp = new MyGraphicsRecItem();
            QPointF poss (p3);
            double t1 = (pressPos.x()-p1.x())/(itemad->rec.width());
            double t2 = (-p1.y()+pressPos.y())/(itemad->rec.height());
            double bili = 1;
            if(t1>0&&t2>0)
            {
                bili = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                bili = fmax(t1,t2);
            }
            else
            {
                bili = fmin(t1,t2);
            }

            tmp->setPos(poss);
            tmp->setRect(0,0,-item->rect().width()*(1+bili),-item->rect().height()*(1+bili));
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 2)
        {
            MyGraphicsEllipseItem* item = qgraphicsitem_cast<MyGraphicsEllipseItem *>(node);
            MyGraphicsEllipseItem *tmp = new MyGraphicsEllipseItem();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t1 = (pressPos.x()-p1.x())/(itemad->rec.width());
            double t2 = -(p1.y()-pressPos.y())/(itemad->rec.height());
            double bili = 1;
            if(t1>0&&t2>0)
            {
                bili = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                bili = fmax(t1,t2);
            }
            else
            {
                bili = fmin(t1,t2);
            }

            tmp->setPos((poss-roof)*bili+poss);
            tmp->setRect(-item->rect().width()*(1+bili)/2,-item->rect().height()*(1+bili)/2,item->rect().width()*(1+bili),item->rect().height()*(1+bili));
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 3)
        {
            MyGraphicsCircleItem* item = qgraphicsitem_cast<MyGraphicsCircleItem *>(node);
            MyGraphicsCircleItem *tmp = new MyGraphicsCircleItem();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t1 = -(-pressPos.x()+p1.x())/(itemad->rec.width());
            double t2 = -(p1.y()-pressPos.y())/(itemad->rec.height());
            double bili = 1;
            if(t1>0&&t2>0)
            {
                bili = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                bili = fmax(t1,t2);
            }
            else
            {
                bili = fmin(t1,t2);
            }

            tmp->setPos((poss-roof)*bili+poss);
            tmp->setRect(-item->rect().width()*(1+bili)/2,-item->rect().height()*(1+bili)/2,item->rect().width()*(1+bili),item->rect().height()*(1+bili));
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 4)
        {
            MyGraphicsLineItem *item = qgraphicsitem_cast<MyGraphicsLineItem *>(node);
            QRectF rect = item->getRect();
            MyGraphicsLineItem *tmp = new MyGraphicsLineItem();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t1 = -(-pressPos.x()+p1.x())/(itemad->rec.width());
            double t2 = -(p1.y()-pressPos.y())/(itemad->rec.height());
            double bili = 1;
            if(t1>0&&t2>0)
            {
                bili = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                bili = fmax(t1,t2);
            }
            else
            {
                bili = fmin(t1,t2);
            }
            QPainterPath path1 = item->path();
            QPainterPath path2 ;
            tmp->setPos((poss-roof)*bili+poss);
            QPointF offset = tmp->pos() - item->pos();
            for (int i = 0; i < path1.elementCount(); i++)
            {
                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(bili)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
            }

            tmp->setPath(path2);
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 5)
        {
            MyGraphicsPolygonItem *item = qgraphicsitem_cast<MyGraphicsPolygonItem *>(node);
            MyGraphicsPolygonItem *tmp = new MyGraphicsPolygonItem();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t1 = -(-pressPos.x()+p1.x())/(itemad->rec.width());
            double t2 = -(p1.y()-pressPos.y())/(itemad->rec.height());
            double bili = 1;
            if(t1>0&&t2>0)
            {
                bili = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                bili = fmax(t1,t2);
            }
            else
            {
                bili = fmin(t1,t2);
            }
            tmp->num = item->num;
            tmp->setPos((poss-roof)*bili+poss);
            tmp->setRect(-item->rect().width()*(1+bili)/2,-item->rect().height()*(1+bili)/2,item->rect().width()*(1+bili),item->rect().height()*(1+bili));
            tmp->setDefault_Path();
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 6)
        {
            MyGraphicsTextItem* item = qgraphicsitem_cast<MyGraphicsTextItem *>(node);
            MyGraphicsTextItem *tmp = new MyGraphicsTextItem();
            QPointF poss = item->pos();
            double t1 = -(-pressPos.x()+p1.x())/(itemad->rec.width());
            double t2 = -(p1.y()-pressPos.y())/(itemad->rec.height());
            double bili = 1;
            if(t1>0&&t2>0)
            {
                bili = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                bili = fmax(t1,t2);
            }
            else
            {
                bili = fmin(t1,t2);
            }
            QPainterPath path1 = item->path;
            QPainterPath path2 ;
            int k=0;
            QPointF c1,c2;
            tmp->setPos((poss-roof)*bili+poss);

            QPointF offset = tmp->pos() - item->pos();   //用来计算path2的pos差值
            for (int i = 0; i < path1.elementCount(); i++)
            {

                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(bili)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
                else if(element.isCurveTo())
                {

                    c1 = po2;
                    k++;
                    //path2.cubicTo(po2);
                }
                else
                {
                    if(k%3 == 1)
                    {

                        c2 = po2;
                        k++;
                    }
                    else if(k%3 == 2)
                    {
                        path2.cubicTo(c1,c2,po2);
                        k++;
                    }

                }
            }
            tmp->setRect(-(item->rect().width()*(1+bili))/2,-(item->rect().height()*(1+bili))/2,item->rect().width()*(1+bili),item->rect().height()*(1+bili));
            tmp->setPath(path2);
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 7)
        {
            MyGraphicsCurveLineItem *item = qgraphicsitem_cast<MyGraphicsCurveLineItem *>(node);
            QList<double> list = item->getRect();
            MyGraphicsCurveLineItem *tmp = new MyGraphicsCurveLineItem();
            QPointF poss = item->pos();
            double t1 = -(-pressPos.x()+p1.x())/(itemad->rec.width());
            double t2 = -(p1.y()-pressPos.y())/(itemad->rec.height());
            double bili = 1;
            if(t1>0&&t2>0)
            {
                bili = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                bili = fmax(t1,t2);
            }
            else
            {
                bili = fmin(t1,t2);
            }
            QPainterPath path1 = item->path();
            QPainterPath path2 ;
            int k=0;
            QPointF c1,c2;
            tmp->setPos((poss-roof)*bili+poss);
            QPointF offset = tmp->pos() - item->pos();   //用来计算path2的pos差值
            for (int i = 0; i < path1.elementCount(); i++)
            {

                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(bili)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
                else if(element.isCurveTo())
                {

                    c1 = po2;
                    k++;
                    //path2.cubicTo(po2);
                }
                else
                {
                    if(k%3 == 1)
                    {

                        c2 = po2;
                        k++;
                    }
                    else if(k%3 == 2)
                    {
                        path2.cubicTo(c1,c2,po2);
                        k++;
                    }

                }
            }

            tmp->setPath(path2);
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 8)
        {
            MyGraphicsPixMapItem* item = qgraphicsitem_cast<MyGraphicsPixMapItem *>(node);
            MyGraphicsPixMapItem *tmp = new MyGraphicsPixMapItem();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t1 = -(-pressPos.x()+p1.x())/(itemad->rec.width());
            double t2 = -(p1.y()-pressPos.y())/(itemad->rec.height());
            double bili = 1;
            if(t1>0&&t2>0)
            {
                bili = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                bili = fmax(t1,t2);
            }
            else
            {
                bili = fmin(t1,t2);
            }
            tmp->setPixmap(item->pixmap());
            tmp->setPos((poss-roof)*bili+poss);
            double w = qAbs(item->rect().width()*(1+bili));
            double h = qAbs(item->rect().height()*(1+bili));
            if(item->rect().width()*(1+bili)<0)
            {
                tmp->setPos((poss-roof)*bili+poss-QPointF(w,h));
            }

            tmp->setRectF(QRect(0,-h,w,h));
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 9)
        {
            MyGraphicsCodeItem *item = qgraphicsitem_cast<MyGraphicsCodeItem *>(node);
            QRectF rect = item->getRect();
            MyGraphicsCodeItem *tmp = new MyGraphicsCodeItem();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t1 = -(-pressPos.x()+p1.x())/(itemad->rec.width());
            double t2 = -(p1.y()-pressPos.y())/(itemad->rec.height());
            double bili = 1;
            if(t1>0&&t2>0)
            {
                bili = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                bili = fmax(t1,t2);
            }
            else
            {
                bili = fmin(t1,t2);
            }
            QPainterPath path1 = item->path();
            QPainterPath path2 ;
            tmp->setPos((poss-roof)*bili+poss);
            QPointF offset = tmp->pos() - item->pos();
            for (int i = 0; i < path1.elementCount(); i++)
            {
                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(bili)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
            }

            tmp->setPath(path2);
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
    }
    scene()->update();
}

void MyGraphicsView::midbuttom_set(QPointF p1,QPointF pressPos)
{
    QList<QGraphicsItem*> items = scene()->selectedItems();

    double s = this->matrix().m11();
    QList<QGraphicsItem *> itemss = scene()->items();
    for (QList<QGraphicsItem*>::iterator it = itemss.begin(); it != itemss.end(); it++)
    {
        QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);

        if(node->data(0).toInt()<0)
        {
            scene()->removeItem(node);
        }
    }
    QPointF roof;
    roof.setX(itemad->mapToScene(itemad->rect()).value(2).x()-10/s);
    roof.setY(itemad->mapToScene(itemad->rect()).value(2).y()-10/s);
    for (QList<QGraphicsItem*>::iterator it = items.begin(); it != items.end(); it++)
    {
        QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);
        if(node->type() == 1)
        {
            MyGraphicsRecItem* item = qgraphicsitem_cast<MyGraphicsRecItem *>(node);
            QPointF p2 = item->mapToScene(item->rect()).value(0);
            QPointF p3 = item->mapToScene(item->rect()).value(2);
            MyGraphicsRecItem *tmp = new MyGraphicsRecItem();
            QPointF poss (p3.x(),p2.y());
            double t2 = -(p1.y()-pressPos.y())/(itemad->rec.height());
            double bili = t2;
            tmp->setPos(poss.x(),((poss-roof)*bili+poss).y());
            tmp->setRect(-item->rect().width(),0,item->rect().width(),item->rect().height()*(1+bili));
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 2)
        {
            MyGraphicsEllipseItem* item = qgraphicsitem_cast<MyGraphicsEllipseItem *>(node);
            QPointF p2 = item->mapToScene(item->rect()).value(0);
            QPointF p3 = item->mapToScene(item->rect()).value(2);
            MyGraphicsEllipseItem *tmp = new MyGraphicsEllipseItem();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t2 = -(p1.y()-pressPos.y())/(itemad->rec.height());
            double bili = t2;

            tmp->setPos(poss.x(),((poss-roof)*bili+poss).y());
            tmp->setRect(-item->rect().width()/2,-item->rect().height()*(1+bili)/2,item->rect().width(),item->rect().height()*(1+bili));
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 3)
        {
            MyGraphicsCircleItem* item = qgraphicsitem_cast<MyGraphicsCircleItem *>(node);
            MyGraphicsCircleItem *tmp = new MyGraphicsCircleItem();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t2 = -(p1.y()-pressPos.y())/(itemad->rec.height());
            double bili = t2;
            tmp->setPos(poss.x(),((poss-roof)*bili+poss).y());
            tmp->setRect(-item->rect().width()/2,-item->rect().height()*(1+bili)/2,item->rect().width(),item->rect().height()*(1+bili));
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 4)
        {
            MyGraphicsLineItem *item = qgraphicsitem_cast<MyGraphicsLineItem *>(node);
            QRectF rect = item->getRect();
            QPointF p2 (rect.x(),rect.y());
            QPointF p3 (rect.x()+rect.width(),rect.y()+rect.height());
            MyGraphicsLineItem *tmp = new MyGraphicsLineItem();
            double t2 = -(p1.y()-pressPos.y())/(itemad->rec.height());
            double bili = t2;
            QPainterPath path1 = item->path();
            QPainterPath path2 ;
            QPointF poss = item->pos();
            tmp->setPos(poss.x(),((poss-roof)*bili+poss).y());
            QPointF offset = tmp->pos() - item->pos();

            for (int i = 0; i < path1.elementCount(); i++)
            {
                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(bili)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                po2.setX(item->mapFromScene(po).x());
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
            }

            tmp->setPath(path2);
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 5)
        {
            MyGraphicsPolygonItem *item = qgraphicsitem_cast<MyGraphicsPolygonItem *>(node);
            MyGraphicsPolygonItem *tmp = new MyGraphicsPolygonItem();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t2 = -(p1.y()-pressPos.y())/(itemad->rec.height());
            double bili = t2;
            tmp->num = item->num;
            tmp->setPos(poss.x(),((poss-roof)*bili+poss).y());
            tmp->setRect(-item->rect().width()/2,-item->rect().height()*(1+bili)/2,item->rect().width(),item->rect().height()*(1+bili));
            tmp->setData(0,-1);
            tmp->setDefault_Path();
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 6)
        {
            MyGraphicsTextItem* item = qgraphicsitem_cast<MyGraphicsTextItem *>(node);
            MyGraphicsTextItem *tmp = new MyGraphicsTextItem();
            QPointF poss = item->pos();
            double t2 = -(p1.y()-pressPos.y())/(itemad->rec.height());
            double bili = t2;
            QPainterPath path1 = item->path;
            QPainterPath path2 ;
            int k=0;
            QPointF c1,c2;
            tmp->setPos(poss.x(),((poss-roof)*bili+poss).y());
            QPointF offset = tmp->pos() - item->pos();   //用来计算path2的pos差值
            for (int i = 0; i < path1.elementCount(); i++)
            {

                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(bili)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                po2.setX(item->mapFromScene(po).x());
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
                else if(element.isCurveTo())
                {

                    c1 = po2;
                    k++;
                    //path2.cubicTo(po2);
                }
                else
                {
                    if(k%3 == 1)
                    {

                        c2 = po2;
                        k++;
                    }
                    else if(k%3 == 2)
                    {
                        path2.cubicTo(c1,c2,po2);
                        k++;
                    }

                }
            }
            tmp->setRect(-(item->rect().width())/2,-(item->rect().height()*(1+bili))/2,item->rect().width(),item->rect().height()*(1+bili));
            tmp->setPath(path2);
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 7)
        {
            MyGraphicsCurveLineItem* item = qgraphicsitem_cast<MyGraphicsCurveLineItem *>(node);
            MyGraphicsCurveLineItem *tmp = new MyGraphicsCurveLineItem();
            QPointF poss = item->pos();
            double t2 = -(p1.y()-pressPos.y())/(itemad->rec.height());
            double bili = t2;
            QPainterPath path1 = item->path();
            QPainterPath path2 ;
            int k=0;
            QPointF c1,c2;
            tmp->setPos(poss.x(),((poss-roof)*bili+poss).y());
            QPointF offset = tmp->pos() - item->pos();   //用来计算path2的pos差值
            for (int i = 0; i < path1.elementCount(); i++)
            {

                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(bili)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                po2.setX(item->mapFromScene(po).x());
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
                else if(element.isCurveTo())
                {

                    c1 = po2;
                    k++;
                    //path2.cubicTo(po2);
                }
                else
                {
                    if(k%3 == 1)
                    {

                        c2 = po2;
                        k++;
                    }
                    else if(k%3 == 2)
                    {
                        path2.cubicTo(c1,c2,po2);
                        k++;
                    }

                }
            }
            tmp->setPath(path2);
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 8)
        {
            MyGraphicsPixMapItem* item = qgraphicsitem_cast<MyGraphicsPixMapItem *>(node);
            MyGraphicsPixMapItem *tmp = new MyGraphicsPixMapItem();
            QPointF poss = item->pos();
            double t2 = -(p1.y()-pressPos.y())/(itemad->rec.height());
            double bili = t2;
            tmp->setPixmap(item->pixmap());
            tmp->setPos( poss.x(),((poss-roof)*bili+poss).y());
            double w = qAbs(item->rect().width());
            double h = qAbs(item->rect().height()*(1+bili));
            if(item->rect().height()*(1+bili)<0)
            {
                tmp->setPos(tmp->pos()-QPointF(0,h));
            }

            tmp->setRectF(QRect(0,-h,w,h));
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 9)
        {
            MyGraphicsCodeItem *item = qgraphicsitem_cast<MyGraphicsCodeItem *>(node);
            QRectF rect = item->getRect();
            QPointF p2 (rect.x(),rect.y());
            QPointF p3 (rect.x()+rect.width(),rect.y()+rect.height());
            MyGraphicsCodeItem *tmp = new MyGraphicsCodeItem();
            double t2 = -(p1.y()-pressPos.y())/(itemad->rec.height());
            double bili = t2;
            QPainterPath path1 = item->path();
            QPainterPath path2 ;
            QPointF poss = item->pos();
            tmp->setPos(poss.x(),((poss-roof)*bili+poss).y());
            QPointF offset = tmp->pos() - item->pos();

            for (int i = 0; i < path1.elementCount(); i++)
            {
                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(bili)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                po2.setX(item->mapFromScene(po).x());
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
            }

            tmp->setPath(path2);
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
    }
    scene()->update();
}

void MyGraphicsView::rightbuttom_set(QPointF p1,QPointF pressPos)
{
    QList<QGraphicsItem*> items = scene()->selectedItems();

    double s = this->matrix().m11();
    QList<QGraphicsItem *> itemss = scene()->items();
    for (QList<QGraphicsItem*>::iterator it = itemss.begin(); it != itemss.end(); it++)
    {
        QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);

        if(node->data(0).toInt()<0)
        {
            scene()->removeItem(node);
        }
    }
    QPointF roof;
    roof.setX(itemad->mapToScene(itemad->rect()).value(3).x()+10/s);
    roof.setY(itemad->mapToScene(itemad->rect()).value(3).y()-10/s);
    for (QList<QGraphicsItem*>::iterator it = items.begin(); it != items.end(); it++)
    {
        QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);
        if(node->type() == 1)
        {
            MyGraphicsRecItem* item = qgraphicsitem_cast<MyGraphicsRecItem *>(node);
            QPointF p2 = item->mapToScene(item->rect()).value(0);
            QPointF p3 = item->mapToScene(item->rect()).value(2);
            MyGraphicsRecItem *tmp = new MyGraphicsRecItem();
            QPointF poss (p3.x(),p2.y());
            double t1 = -(pressPos.x()-p1.x())/(itemad->rec.width());
            double t2 = -(p1.y()-pressPos.y())/(itemad->rec.height());
            double bili = 1;
            if(t1>0&&t2>0)
            {
                bili = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                bili = fmax(t1,t2);
            }
            else
            {
                bili = fmin(t1,t2);
            }

            tmp->setPos((poss-roof)*bili+poss);
            tmp->setRect(-item->rect().width()*(1+bili),0,item->rect().width()*(1+bili),item->rect().height()*(1+bili));
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 2)
        {
            MyGraphicsEllipseItem* item = qgraphicsitem_cast<MyGraphicsEllipseItem *>(node);
            QPointF p2 = item->mapToScene(item->rect()).value(0);
            QPointF p3 = item->mapToScene(item->rect()).value(2);
            MyGraphicsEllipseItem *tmp = new MyGraphicsEllipseItem();
            double w = p3.x()-p2.x(),h = p3.y()-p2.y();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t1 = -(pressPos.x()-p1.x())/(itemad->rec.width());
            double t2 = -(p1.y()-pressPos.y())/(itemad->rec.height());
            double bili = 1;
            if(t1>0&&t2>0)
            {
                bili = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                bili = fmax(t1,t2);
            }
            else
            {
                bili = fmin(t1,t2);
            }

            tmp->setPos((poss-roof)*bili+poss);
            tmp->setRect(-item->rect().width()*(1+bili)/2,-item->rect().height()*(1+bili)/2,item->rect().width()*(1+bili),item->rect().height()*(1+bili));
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 3)
        {
            MyGraphicsCircleItem* item = qgraphicsitem_cast<MyGraphicsCircleItem *>(node);
            QPointF p2 = item->mapToScene(item->rect()).value(0);
            QPointF p3 = item->mapToScene(item->rect()).value(2);
            MyGraphicsCircleItem *tmp = new MyGraphicsCircleItem();
            double w = p3.x()-p2.x(),h = p3.y()-p2.y();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t1 = -(pressPos.x()-p1.x())/(itemad->rec.width());
            double t2 = -(p1.y()-pressPos.y())/(itemad->rec.height());
            double bili = 1;
            if(t1>0&&t2>0)
            {
                bili = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                bili = fmax(t1,t2);
            }
            else
            {
                bili = fmin(t1,t2);
            }

            tmp->setPos((poss-roof)*bili+poss);
            tmp->setRect(-item->rect().width()*(1+bili)/2,-item->rect().height()*(1+bili)/2,item->rect().width()*(1+bili),item->rect().height()*(1+bili));
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 4)
        {
            MyGraphicsLineItem *item = qgraphicsitem_cast<MyGraphicsLineItem *>(node);
            QRectF rect = item->getRect();
            QPointF p2 (rect.x(),rect.y());
            QPointF p3 (rect.x()+rect.width(),rect.y()+rect.height());
            MyGraphicsLineItem *tmp = new MyGraphicsLineItem();
            double w = p3.x()-p2.x(),h = p3.y()-p2.y();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t1 = -(pressPos.x()-p1.x())/(itemad->rec.width());
            double t2 = -(p1.y()-pressPos.y())/(itemad->rec.height());
            double bili = 1;
            if(t1>0&&t2>0)
            {
                bili = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                bili = fmax(t1,t2);
            }
            else
            {
                bili = fmin(t1,t2);
            }
            QPainterPath path1 = item->path();
            QPainterPath path2 ;
            tmp->setPos((poss-roof)*bili+poss);
            QPointF offset = tmp->pos() - item->pos();
            for (int i = 0; i < path1.elementCount(); i++)
            {
                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(bili)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
            }

            tmp->setPath(path2);
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 5)
        {
            MyGraphicsPolygonItem *item = qgraphicsitem_cast<MyGraphicsPolygonItem *>(node);
            QRectF rect = item->getRect();
            QPointF p2 (rect.x(),rect.y());
            QPointF p3 (rect.x()+rect.width(),rect.y()+rect.height());
            MyGraphicsPolygonItem *tmp = new MyGraphicsPolygonItem();
            double w = p3.x()-p2.x(),h = p3.y()-p2.y();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t1 = -(pressPos.x()-p1.x())/(itemad->rec.width());
            double t2 = -(p1.y()-pressPos.y())/(itemad->rec.height());
            double bili = 1;
            if(t1>0&&t2>0)
            {
                bili = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                bili = fmax(t1,t2);
            }
            else
            {
                bili = fmin(t1,t2);
            }
            tmp->num = item->num;
            tmp->setPos((poss-roof)*bili+poss);
            tmp->setRect(-item->rect().width()*(1+bili)/2,-item->rect().height()*(1+bili)/2,item->rect().width()*(1+bili),item->rect().height()*(1+bili));
            tmp->setDefault_Path();
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 6)
        {
            MyGraphicsTextItem* item = qgraphicsitem_cast<MyGraphicsTextItem *>(node);
            QPointF p2 = item->mapToScene(item->rect()).value(0);
            QPointF p3 = item->mapToScene(item->rect()).value(2);
            MyGraphicsTextItem *tmp = new MyGraphicsTextItem();
            double w = p3.x()-p2.x(),h = p3.y()-p2.y();
            QPointF poss = item->pos();
            double t1 = -(pressPos.x()-p1.x())/(itemad->rec.width());
            double t2 = -(p1.y()-pressPos.y())/(itemad->rec.height());
            double bili = 1;
            if(t1>0&&t2>0)
            {
                bili = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                bili = fmax(t1,t2);
            }
            else
            {
                bili = fmin(t1,t2);
            }
            QPainterPath path1 = item->path;
            QPainterPath path2 ;
            int k=0;
            QPointF c1,c2;
            tmp->setPos((poss-roof)*bili+poss);
            QPointF offset = tmp->pos() - item->pos();   //用来计算path2的pos差值
            for (int i = 0; i < path1.elementCount(); i++)
            {

                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(bili)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
                else if(element.isCurveTo())
                {

                    c1 = po2;
                    k++;
                    //path2.cubicTo(po2);
                }
                else
                {
                    if(k%3 == 1)
                    {

                        c2 = po2;
                        k++;
                    }
                    else if(k%3 == 2)
                    {
                        path2.cubicTo(c1,c2,po2);
                        k++;
                    }

                }
            }
            tmp->setRect(-(item->rect().width()*(1+bili))/2,-(item->rect().height()*(1+bili))/2,item->rect().width()*(1+bili),item->rect().height()*(1+bili));
            tmp->setPath(path2);
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 7)
        {
            MyGraphicsCurveLineItem *item = qgraphicsitem_cast<MyGraphicsCurveLineItem *>(node);
            QList<double> list = item->getRect();
            MyGraphicsCurveLineItem *tmp = new MyGraphicsCurveLineItem();
            QPointF poss = item->pos();
            double t1 = -(pressPos.x()-p1.x())/(itemad->rec.width());
            double t2 = -(p1.y()-pressPos.y())/(itemad->rec.height());
            double bili = 1;
            if(t1>0&&t2>0)
            {
                bili = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                bili = fmax(t1,t2);
            }
            else
            {
                bili = fmin(t1,t2);
            }
            QPainterPath path1 = item->path();
            QPainterPath path2 ;
            int k=0;
            QPointF c1,c2;
            tmp->setPos((poss-roof)*bili+poss);
            QPointF offset = tmp->pos() - item->pos();   //用来计算path2的pos差值
            for (int i = 0; i < path1.elementCount(); i++)
            {

                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(bili)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
                else if(element.isCurveTo())
                {

                    c1 = po2;
                    k++;
                    //path2.cubicTo(po2);
                }
                else
                {
                    if(k%3 == 1)
                    {

                        c2 = po2;
                        k++;
                    }
                    else if(k%3 == 2)
                    {
                        path2.cubicTo(c1,c2,po2);
                        k++;
                    }

                }
            }

            tmp->setPath(path2);
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 8)
        {
            MyGraphicsPixMapItem* item = qgraphicsitem_cast<MyGraphicsPixMapItem *>(node);
            MyGraphicsPixMapItem *tmp = new MyGraphicsPixMapItem();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t1 = -(pressPos.x()-p1.x())/(itemad->rec.width());
            double t2 = -(p1.y()-pressPos.y())/(itemad->rec.height());
            double bili = 1;
            if(t1>0&&t2>0)
            {
                bili = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                bili = fmax(t1,t2);
            }
            else
            {
                bili = fmin(t1,t2);
            }
            tmp->setPixmap(item->pixmap());
            tmp->setPos((poss-roof)*bili+poss);
            double w = qAbs(item->rect().width()*(1+bili));
            double h = qAbs(item->rect().height()*(1+bili));
            if(item->rect().width()*(1+bili)<0)
            {
                tmp->setPos((poss-roof)*bili+poss-QPointF(w,h));
            }

            tmp->setRectF(QRect(0,-h,w,h));
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 9)
        {
            MyGraphicsCodeItem *item = qgraphicsitem_cast<MyGraphicsCodeItem *>(node);
            QRectF rect = item->getRect();
            QPointF p2 (rect.x(),rect.y());
            QPointF p3 (rect.x()+rect.width(),rect.y()+rect.height());
            MyGraphicsCodeItem *tmp = new MyGraphicsCodeItem();
            double w = p3.x()-p2.x(),h = p3.y()-p2.y();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t1 = -(pressPos.x()-p1.x())/(itemad->rec.width());
            double t2 = -(p1.y()-pressPos.y())/(itemad->rec.height());
            double bili = 1;
            if(t1>0&&t2>0)
            {
                bili = fmin(t1,t2);
            }
            else if(t1<0 && t2 <0)
            {
                bili = fmax(t1,t2);
            }
            else
            {
                bili = fmin(t1,t2);
            }
            QPainterPath path1 = item->path();
            QPainterPath path2 ;
            tmp->setPos((poss-roof)*bili+poss);
            QPointF offset = tmp->pos() - item->pos();
            for (int i = 0; i < path1.elementCount(); i++)
            {
                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(bili)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
            }

            tmp->setPath(path2);
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
    }
    scene()->update();
}

void MyGraphicsView::leftmid_set(QPointF p1,QPointF pressPos)
{
    QList<QGraphicsItem*> items = scene()->selectedItems();

    double s = this->matrix().m11();
    QList<QGraphicsItem *> itemss = scene()->items();
    for (QList<QGraphicsItem*>::iterator it = itemss.begin(); it != itemss.end(); it++)
    {
        QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);

        if(node->data(0).toInt()<0)
        {
            scene()->removeItem(node);
        }
    }
    QPointF roof;
    roof.setX(itemad->mapToScene(itemad->rect()).value(1).x()-10/s);
    roof.setY(itemad->mapToScene(itemad->rect()).value(1).y()+10/s);
    for (QList<QGraphicsItem*>::iterator it = items.begin(); it != items.end(); it++)
    {
        QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);
        if(node->type() == 1)
        {
            MyGraphicsRecItem* item = qgraphicsitem_cast<MyGraphicsRecItem *>(node);
            QPointF p2 = item->mapToScene(item->rect()).value(0);
            QPointF p3 = item->mapToScene(item->rect()).value(2);
            MyGraphicsRecItem *tmp = new MyGraphicsRecItem();
            QPointF poss (p3.x(),p2.y());
            double t2 = -(p1.x()-pressPos.x())/(itemad->rec.width());
            double bili = t2;
            tmp->setPos(((poss-roof)*bili+poss).x(),poss.y());
            tmp->setRect(-item->rect().width()*(1+bili),0,item->rect().width()*(1+bili),item->rect().height());
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 2)
        {
            MyGraphicsEllipseItem* item = qgraphicsitem_cast<MyGraphicsEllipseItem *>(node);
            QPointF p2 = item->mapToScene(item->rect()).value(0);
            QPointF p3 = item->mapToScene(item->rect()).value(2);
            MyGraphicsEllipseItem *tmp = new MyGraphicsEllipseItem();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t2 = -(p1.x()-pressPos.x())/(itemad->rec.width());
            double bili = t2;
            tmp->setPos(((poss-roof)*bili+poss).x(),poss.y());
            tmp->setRect(-item->rect().width()*(1+bili)/2,-item->rect().height()/2,item->rect().width()*(1+bili),item->rect().height());
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 3)
        {
            MyGraphicsCircleItem* item = qgraphicsitem_cast<MyGraphicsCircleItem *>(node);
            MyGraphicsCircleItem *tmp = new MyGraphicsCircleItem();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t2 = -(p1.x()-pressPos.x())/(itemad->rec.width());
            double bili = t2;
            tmp->setPos(((poss-roof)*bili+poss).x(),poss.y());
            tmp->setRect(-item->rect().width()*(1+bili)/2,-item->rect().height()/2,item->rect().width()*(1+bili),item->rect().height());
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 4)
        {
            MyGraphicsLineItem *item = qgraphicsitem_cast<MyGraphicsLineItem *>(node);
            QRectF rect = item->getRect();
            QPointF p2 (rect.x(),rect.y());
            QPointF p3 (rect.x()+rect.width(),rect.y()+rect.height());
            MyGraphicsLineItem *tmp = new MyGraphicsLineItem();
            double t2 = -(p1.x()-pressPos.x())/(itemad->rec.width());
            double bili = t2;
            QPainterPath path1 = item->path();
            QPainterPath path2 ;
            QPointF poss = item->pos();
            tmp->setPos(((poss-roof)*bili+poss).x(),poss.y());
            QPointF offset = tmp->pos() - item->pos();

            for (int i = 0; i < path1.elementCount(); i++)
            {
                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(bili)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                po2.setY(item->mapFromScene(po).y());
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
            }
            tmp->setPath(path2);
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 5)
        {
            MyGraphicsPolygonItem *item = qgraphicsitem_cast<MyGraphicsPolygonItem *>(node);
            MyGraphicsPolygonItem *tmp = new MyGraphicsPolygonItem();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t2 = -(p1.x()-pressPos.x())/(itemad->rec.width());
            double bili = t2;
            tmp->num = item->num;
            tmp->setPos(((poss-roof)*bili+poss).x(),poss.y());
            tmp->setRect(-item->rect().width()*(1+bili)/2,-item->rect().height()/2,item->rect().width()*(1+bili),item->rect().height());
            tmp->setData(0,-1);
            tmp->setDefault_Path();
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 6)
        {
            MyGraphicsTextItem* item = qgraphicsitem_cast<MyGraphicsTextItem *>(node);
            MyGraphicsTextItem *tmp = new MyGraphicsTextItem();
            QPointF poss = item->pos();
            double t2 = -(p1.x()-pressPos.x())/(itemad->rec.width());
            double bili = t2;
            QPainterPath path1 = item->path;
            QPainterPath path2 ;
            int k=0;
            QPointF c1,c2;
            tmp->setPos(((poss-roof)*bili+poss).x(),poss.y());
            QPointF offset = tmp->pos() - item->pos();   //用来计算path2的pos差值
            for (int i = 0; i < path1.elementCount(); i++)
            {

                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(bili)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                po2.setY(item->mapFromScene(po).y());
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
                else if(element.isCurveTo())
                {

                    c1 = po2;
                    k++;
                    //path2.cubicTo(po2);
                }
                else
                {
                    if(k%3 == 1)
                    {

                        c2 = po2;
                        k++;
                    }
                    else if(k%3 == 2)
                    {
                        path2.cubicTo(c1,c2,po2);
                        k++;
                    }

                }
            }
            tmp->setRect(-item->rect().width()*(1+bili)/2,-item->rect().height()/2,item->rect().width()*(1+bili),item->rect().height());
            tmp->setPath(path2);
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 7)
        {
            MyGraphicsCurveLineItem* item = qgraphicsitem_cast<MyGraphicsCurveLineItem *>(node);
            MyGraphicsCurveLineItem *tmp = new MyGraphicsCurveLineItem();
            QPointF poss = item->pos();
            double t2 = -(p1.x()-pressPos.x())/(itemad->rec.width());
            double bili = t2;
            QPainterPath path1 = item->path();
            QPainterPath path2 ;
            int k=0;
            QPointF c1,c2;
            tmp->setPos(((poss-roof)*bili+poss).x(),poss.y());
            QPointF offset = tmp->pos() - item->pos();   //用来计算path2的pos差值
            for (int i = 0; i < path1.elementCount(); i++)
            {

                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(bili)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                po2.setY(item->mapFromScene(po).y());
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
                else if(element.isCurveTo())
                {

                    c1 = po2;
                    k++;
                    //path2.cubicTo(po2);
                }
                else
                {
                    if(k%3 == 1)
                    {

                        c2 = po2;
                        k++;
                    }
                    else if(k%3 == 2)
                    {
                        path2.cubicTo(c1,c2,po2);
                        k++;
                    }

                }
            }
            tmp->setPath(path2);
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 8)
        {
            MyGraphicsPixMapItem* item = qgraphicsitem_cast<MyGraphicsPixMapItem *>(node);
            MyGraphicsPixMapItem *tmp = new MyGraphicsPixMapItem();
            QPointF poss = item->pos();
            double t2 = -(p1.x()-pressPos.x())/(itemad->rec.width());
            double bili = t2;
            tmp->setPixmap(item->pixmap());
            tmp->setPos(((poss-roof)*bili+poss).x(),poss.y());
            double w = qAbs(item->rect().width()*(1+bili));
            double h = qAbs(item->rect().height());
            if(item->rect().width()*(1+bili)<0)
            {
                tmp->setPos(tmp->pos()-QPointF(w,0));
            }

            tmp->setRectF(QRect(0,-h,w,h));
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 9)
        {
            MyGraphicsCodeItem *item = qgraphicsitem_cast<MyGraphicsCodeItem *>(node);
            QRectF rect = item->getRect();
            QPointF p2 (rect.x(),rect.y());
            QPointF p3 (rect.x()+rect.width(),rect.y()+rect.height());
            MyGraphicsCodeItem *tmp = new MyGraphicsCodeItem();
            double t2 = -(p1.x()-pressPos.x())/(itemad->rec.width());
            double bili = t2;
            QPainterPath path1 = item->path();
            QPainterPath path2 ;
            QPointF poss = item->pos();
            tmp->setPos(((poss-roof)*bili+poss).x(),poss.y());
            QPointF offset = tmp->pos() - item->pos();

            for (int i = 0; i < path1.elementCount(); i++)
            {
                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(bili)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                po2.setY(item->mapFromScene(po).y());
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
            }
            tmp->setPath(path2);
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
    }
    scene()->update();
}

void MyGraphicsView::rightmid_set(QPointF p1,QPointF pressPos)
{
    QList<QGraphicsItem*> items = scene()->selectedItems();

    double s = this->matrix().m11();
    QList<QGraphicsItem *> itemss = scene()->items();
    for (QList<QGraphicsItem*>::iterator it = itemss.begin(); it != itemss.end(); it++)
    {
        QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);

        if(node->data(0).toInt()<0)
        {
            scene()->removeItem(node);
        }
    }
    QPointF roof;
    roof.setX(itemad->mapToScene(itemad->rect()).value(0).x()+10/s);
    roof.setY(itemad->mapToScene(itemad->rect()).value(0).y()+10/s);
    for (QList<QGraphicsItem*>::iterator it = items.begin(); it != items.end(); it++)
    {
        QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);
        if(node->type() == 1)
        {
            MyGraphicsRecItem* item = qgraphicsitem_cast<MyGraphicsRecItem *>(node);
            QPointF p2 = item->mapToScene(item->rect()).value(0);
            QPointF p3 = item->mapToScene(item->rect()).value(2);
            MyGraphicsRecItem *tmp = new MyGraphicsRecItem();
            QPointF poss (p3.x(),p2.y());
            double t2 = (p1.x()-pressPos.x())/(itemad->rec.width());
            double bili = t2;
            tmp->setPos(((poss-roof)*bili+poss).x(),poss.y());
            tmp->setRect(-item->rect().width()*(1+bili),0,item->rect().width()*(1+bili),item->rect().height());
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 2)
        {
            MyGraphicsEllipseItem* item = qgraphicsitem_cast<MyGraphicsEllipseItem *>(node);
            QPointF p2 = item->mapToScene(item->rect()).value(0);
            QPointF p3 = item->mapToScene(item->rect()).value(2);
            MyGraphicsEllipseItem *tmp = new MyGraphicsEllipseItem();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t2 = (p1.x()-pressPos.x())/(itemad->rec.width());
            double bili = t2;
            tmp->setPos(((poss-roof)*bili+poss).x(),poss.y());
            tmp->setRect(-item->rect().width()*(1+bili)/2,-item->rect().height()/2,item->rect().width()*(1+bili),item->rect().height());
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 3)
        {
            MyGraphicsCircleItem* item = qgraphicsitem_cast<MyGraphicsCircleItem *>(node);
            MyGraphicsCircleItem *tmp = new MyGraphicsCircleItem();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t2 = (p1.x()-pressPos.x())/(itemad->rec.width());
            double bili = t2;
            tmp->setPos(((poss-roof)*bili+poss).x(),poss.y());
            tmp->setRect(-item->rect().width()*(1+bili)/2,-item->rect().height()/2,item->rect().width()*(1+bili),item->rect().height());
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 4)
        {
            MyGraphicsLineItem *item = qgraphicsitem_cast<MyGraphicsLineItem *>(node);
            QRectF rect = item->getRect();
            QPointF p2 (rect.x(),rect.y());
            QPointF p3 (rect.x()+rect.width(),rect.y()+rect.height());
            MyGraphicsLineItem *tmp = new MyGraphicsLineItem();
            double t2 = (p1.x()-pressPos.x())/(itemad->rec.width());
            double bili = t2;
            QPainterPath path1 = item->path();
            QPainterPath path2 ;
            QPointF poss = item->pos();
            tmp->setPos(((poss-roof)*bili+poss).x(),poss.y());
            QPointF offset = tmp->pos() - item->pos();

            for (int i = 0; i < path1.elementCount(); i++)
            {
                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(bili)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                po2.setY(item->mapFromScene(po).y());
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
            }
            tmp->setPath(path2);
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 5)
        {
            MyGraphicsPolygonItem *item = qgraphicsitem_cast<MyGraphicsPolygonItem *>(node);
            MyGraphicsPolygonItem *tmp = new MyGraphicsPolygonItem();
            QPointF poss = item->pos();
            //QPointF offset(w/2,-h/2);
            double t2 = (p1.x()-pressPos.x())/(itemad->rec.width());
            double bili = t2;
            tmp->num = item->num;
            tmp->setPos(((poss-roof)*bili+poss).x(),poss.y());
            tmp->setRect(-item->rect().width()*(1+bili)/2,-item->rect().height()/2,item->rect().width()*(1+bili),item->rect().height());
            tmp->setData(0,-1);
            tmp->setDefault_Path();
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 6)
        {
            MyGraphicsTextItem* item = qgraphicsitem_cast<MyGraphicsTextItem *>(node);
            MyGraphicsTextItem *tmp = new MyGraphicsTextItem();
            QPointF poss = item->pos();
            double t2 = (p1.x()-pressPos.x())/(itemad->rec.width());
            double bili = t2;
            QPainterPath path1 = item->path;
            QPainterPath path2 ;
            int k=0;
            QPointF c1,c2;
            tmp->setPos(((poss-roof)*bili+poss).x(),poss.y());
            QPointF offset = tmp->pos() - item->pos();   //用来计算path2的pos差值
            for (int i = 0; i < path1.elementCount(); i++)
            {

                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(bili)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                po2.setY(item->mapFromScene(po).y());
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
                else if(element.isCurveTo())
                {

                    c1 = po2;
                    k++;
                    //path2.cubicTo(po2);
                }
                else
                {
                    if(k%3 == 1)
                    {

                        c2 = po2;
                        k++;
                    }
                    else if(k%3 == 2)
                    {
                        path2.cubicTo(c1,c2,po2);
                        k++;
                    }

                }
            }
            tmp->setRect(-item->rect().width()*(1+bili)/2,-item->rect().height()/2,item->rect().width()*(1+bili),item->rect().height());
            tmp->setPath(path2);
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 7)
        {
            MyGraphicsCurveLineItem* item = qgraphicsitem_cast<MyGraphicsCurveLineItem *>(node);
            MyGraphicsCurveLineItem *tmp = new MyGraphicsCurveLineItem();
            QPointF poss = item->pos();
            double t2 = (p1.x()-pressPos.x())/(itemad->rec.width());
            double bili = t2;
            QPainterPath path1 = item->path();
            QPainterPath path2 ;
            int k=0;
            QPointF c1,c2;
            tmp->setPos(((poss-roof)*bili+poss).x(),poss.y());
            QPointF offset = tmp->pos() - item->pos();   //用来计算path2的pos差值
            for (int i = 0; i < path1.elementCount(); i++)
            {

                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(bili)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                po2.setY(item->mapFromScene(po).y());
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
                else if(element.isCurveTo())
                {

                    c1 = po2;
                    k++;
                    //path2.cubicTo(po2);
                }
                else
                {
                    if(k%3 == 1)
                    {

                        c2 = po2;
                        k++;
                    }
                    else if(k%3 == 2)
                    {
                        path2.cubicTo(c1,c2,po2);
                        k++;
                    }

                }
            }
            tmp->setPath(path2);
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 8)
        {
            MyGraphicsPixMapItem* item = qgraphicsitem_cast<MyGraphicsPixMapItem *>(node);
            MyGraphicsPixMapItem *tmp = new MyGraphicsPixMapItem();
            QPointF poss = item->pos();
            double t2 = (p1.x()-pressPos.x())/(itemad->rec.width());
            double bili = t2;
            tmp->setPixmap(item->pixmap());
            tmp->setPos(((poss-roof)*bili+poss).x(),poss.y());
            double w = qAbs(item->rect().width()*(1+bili));
            double h = qAbs(item->rect().height());
            if(item->rect().width()*(1+bili)<0)
            {
                tmp->setPos(tmp->pos()-QPointF(w,0));
            }

            tmp->setRectF(QRect(0,-h,w,h));
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
        else if(node->type() == 9)
        {
            MyGraphicsCodeItem *item = qgraphicsitem_cast<MyGraphicsCodeItem *>(node);
            QRectF rect = item->getRect();
            QPointF p2 (rect.x(),rect.y());
            QPointF p3 (rect.x()+rect.width(),rect.y()+rect.height());
            MyGraphicsCodeItem *tmp = new MyGraphicsCodeItem();
            double t2 = (p1.x()-pressPos.x())/(itemad->rec.width());
            double bili = t2;
            QPainterPath path1 = item->path();
            QPainterPath path2 ;
            QPointF poss = item->pos();
            tmp->setPos(((poss-roof)*bili+poss).x(),poss.y());
            QPointF offset = tmp->pos() - item->pos();

            for (int i = 0; i < path1.elementCount(); i++)
            {
                QPainterPath::Element element = path1.elementAt(i);
                QPointF po = element;
                po = item->mapToScene(po);
                QPointF po2 = (po-roof)*(bili)+po;

                po2 = item->mapFromScene(po2);
                po2 = po2-offset;
                po2.setY(item->mapFromScene(po).y());
                if (element.isMoveTo())
                {
                    path2.moveTo(po2);
                }
                else if (element.isLineTo())
                {
                    path2.lineTo(po2);
                }
            }
            tmp->setPath(path2);
            tmp->setData(0,-1);
            tmp->setData(1,item->data(0).toInt());
            tmp->setVisible(true);
            scene()->addItem(tmp);
        }
    }
    scene()->update();
}

void MyGraphicsView::mouseMoveEvent(QMouseEvent* event)
{
    QPointF scenePos = mapToScene(event->pos());
    QString posLabelText;
    posLabelText.sprintf("x: %.2f, y: %.2f px", scenePos.x(), scenePos.y());
    _posLabel->setText(posLabelText);
    _statusBarPtr->update();
    //_lastMousePos = QPoint(_lastMousePos.x(), -_lastMousePos.y());
    //QPointF pressPos = mapToScene(_lastMousePos);
    QPointF offsetPos = event->pos() - lastPos;
    lastPos = event->pos();
    
    if (action_state == 0  && QRectF(itemad->pos().x() + itemad->mid.x(), itemad->pos().y() + itemad->mid.y(), itemad->mid.width(), itemad->mid.height()).contains(mapToScene( event->pos())))
    {
        setCursor(Qt::SizeAllCursor);
    }
    else if(action_state == 0 && QRectF(itemad->pos().x() + itemad->lefttop.x(),itemad->pos().y() + itemad->lefttop.y(),itemad->lefttop.width(),itemad->lefttop.height()).contains(mapToScene(event->pos())))
    {
        setCursor(Qt::SizeFDiagCursor);
    }
    else if(action_state == 0 && QRectF(itemad->pos().x() + itemad->midtop.x(),itemad->pos().y() + itemad->midtop.y(),itemad->midtop.width(),itemad->midtop.height()).contains(mapToScene(event->pos())))
    {
        setCursor(Qt::SizeVerCursor);
    }
    else if(action_state == 0 && QRectF(itemad->pos().x() + itemad->righttop.x(),itemad->pos().y() + itemad->righttop.y(),itemad->righttop.width(),itemad->righttop.height()).contains(mapToScene(event->pos())))
    {
        setCursor(Qt::SizeBDiagCursor);
    }
    else if(action_state == 0 && QRectF(itemad->pos().x() + itemad->leftbuttom.x(),itemad->pos().y() + itemad->leftbuttom.y(),itemad->leftbuttom.width(),itemad->leftbuttom.height()).contains(mapToScene(event->pos())))
    {
        setCursor(Qt::SizeBDiagCursor);
    }
    else if(action_state == 0 && QRectF(itemad->pos().x() + itemad->midbuttom.x(),itemad->pos().y() + itemad->midbuttom.y(),itemad->midbuttom.width(),itemad->midbuttom.height()).contains(mapToScene(event->pos())))
    {
        setCursor(Qt::SizeVerCursor);
    }
    else if(action_state == 0 && QRectF(itemad->pos().x() + itemad->rightbuttom.x(),itemad->pos().y() + itemad->rightbuttom.y(),itemad->rightbuttom.width(),itemad->rightbuttom.height()).contains(mapToScene(event->pos())))
    {
        setCursor(Qt::SizeFDiagCursor);
    }
    else if(action_state == 0 && QRectF(itemad->pos().x() + itemad->leftmid.x(),itemad->pos().y() + itemad->leftmid.y(),itemad->leftmid.width(),itemad->leftmid.height()).contains(mapToScene(event->pos())))
    {
        setCursor(Qt::SizeHorCursor);
    }
    else if(action_state == 0 && QRectF(itemad->pos().x() + itemad->rightmid.x(),itemad->pos().y() + itemad->rightmid.y(),itemad->rightmid.width(),itemad->rightmid.height()).contains(mapToScene(event->pos())))
    {
        setCursor(Qt::SizeHorCursor);
    }
    else
    {
        setCursor(Qt::ArrowCursor);
    }

    if (action_state == 0 && (event->buttons() & Qt::LeftButton) && moveble)
    {
        setCursor(Qt::SizeAllCursor);
        QList<QGraphicsItem*> items = scene()->selectedItems();
        double s = this->matrix().m11();
        itemad->setPos(itemad->pos().x() + offsetPos.x()/s,itemad->pos().y()-offsetPos.y()/s);

        for (QList<QGraphicsItem*>::iterator it = items.begin(); it != items.end(); it++)
        {
            QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);
            node->setPos(node->pos().x() + offsetPos.x()/s, node->pos().y() - offsetPos.y()/s);
        }
        emit selectchange();
    }
    if(action_state == 0 && (event->buttons()& Qt::LeftButton)&&lefttop_move)
    {
        setCursor(Qt::SizeFDiagCursor);
        lefttop_set(scenePos,mapToScene(_lastMousePos));
    }
    if(action_state == 0 && (event->buttons()& Qt::LeftButton)&& midtop_move)
    {
        setCursor(Qt::SizeVerCursor);
        midtop_set(scenePos,mapToScene(_lastMousePos));
    }
    if(action_state == 0 && (event->buttons()& Qt::LeftButton)&& righttop_move)
    {
        setCursor(Qt::SizeBDiagCursor);
        righttop_set(scenePos,mapToScene(_lastMousePos));
    }
    if(action_state == 0 && (event->buttons()& Qt::LeftButton)&& leftbuttom_move)
    {
        setCursor(Qt::SizeBDiagCursor);
        leftbuttom_set(scenePos,mapToScene(_lastMousePos));
    }
    if(action_state == 0 && (event->buttons()& Qt::LeftButton)&& midbuttom_move)
    {
        setCursor(Qt::SizeVerCursor);
        midbuttom_set(scenePos,mapToScene(_lastMousePos));
    }
    if(action_state == 0 && (event->buttons()& Qt::LeftButton)&&rightbuttom_move)
    {
        setCursor(Qt::SizeFDiagCursor);
        rightbuttom_set(scenePos,mapToScene(_lastMousePos));
    }
    if(action_state == 0 && (event->buttons()& Qt::LeftButton)&&leftmid_move)
    {
        setCursor(Qt::SizeHorCursor);
        leftmid_set(scenePos,mapToScene(_lastMousePos));
    }
    if(action_state == 0 && (event->buttons()& Qt::LeftButton)&&rightmid_move)
    {
        setCursor(Qt::SizeHorCursor);
        rightmid_set(scenePos,mapToScene(_lastMousePos));
    }
    if(isPaintLine)
    {
        QPainterPath tpath = *_tempLinePath;
        tpath.lineTo(scenePos);
        _tempLineItemPtr->setPath(tpath);
        _tempLineItemPtr->setVisible(true);
    }

    // 这里由于move动作的过程中event->button返回no_button
    // 而event->buttons返回当前正在按下的按键，使用“与”运算来判定
    if (event->buttons() & Qt::MiddleButton) {
        // 移动前的scene的sceneRect
        //QRectF originSceneRect = scene()->sceneRect();
        //float adjust_x = -offsetPos.x() / _selfScale;
        //float adjust_y = -offsetPos.y() / _selfScale;
        //scene()->setSceneRect(originSceneRect.adjusted(adjust_x, adjust_y, adjust_x, adjust_y));
    }
    else if (event->buttons() & Qt::LeftButton) {
        if (action_state==1) {
            QPointF tmp_pos = _tempRectItemPtr->pos();
            float newPos_x = qMin(scenePos.x(), tmp_pos.x());
            float newPos_y = qMin(scenePos.y(), tmp_pos.y());
            float newWidth = qAbs(scenePos.x() - tmp_pos.x());
            float newHeight = qAbs(scenePos.y() - tmp_pos.y());
            _tempRectItemPtr->setRect(newPos_x - tmp_pos.x(), newPos_y - tmp_pos.y(), newWidth, newHeight);



            _tempRectItemPtr->setVisible(true);

        }
        else if (action_state==2) {
            QPointF tmp_pos = _tempEllipseItemPtr->pos();
            float newWidth = qAbs(scenePos.x() - tmp_pos.x());
            float newHeight = qAbs(scenePos.y() - tmp_pos.y());
            _tempEllipseItemPtr->setRect(-newWidth , -newHeight , newWidth*2, newHeight*2);
            _tempEllipseItemPtr->setVisible(true);
        }
        else if (action_state == 3) {
            QPointF tmp_pos = _tempCircleItemPtr->pos();
            float newWidth = qAbs(scenePos.x() - tmp_pos.x());
            float newHeight = qAbs(scenePos.y() - tmp_pos.y());
            auto r = qMax(newWidth, newHeight);
            _tempCircleItemPtr->setRect(-r, -r, r * 2, r * 2);
            _tempCircleItemPtr->setVisible(true);
        }
        else if(action_state == 5)
        {
            QPointF tmp_pos = _tempPolygonItemPtr->pos();
            float newWidth = qAbs(scenePos.x() - tmp_pos.x());
            float newHeight = qAbs(scenePos.y() - tmp_pos.y());
            float r = qMax(newWidth, newHeight);
            _tempPolygonItemPtr->setRect(-newWidth , -newHeight , newWidth*2, newHeight*2);
            _tempPolygonItemPtr->setDefault_Path();
//            QPainter *p = new QPainter(this);

//            _tempPolygonItemPtr->paint(p,NULL,this);
            _tempPolygonItemPtr->setVisible(true);
            update();
        }
        else if(action_state == 7)
        {
            if(isPaintCurve == false)
            {
                _tempCurveItemPtr->ctl_next = _tempCurveItemPtr->duichengdian(scenePos,_tempCurveItemPtr->endP);
            }
            else
            {

                _tempCurveItemPtr->ctl_next = _tempCurveItemPtr->duichengdian(scenePos,_tempCurveItemPtr->endP);
                QPainterPath tpath = *_tempCurvePath;
                tpath.cubicTo(_tempCurveItemPtr->ctl_pre,_tempCurveItemPtr->ctl_next,_tempCurveItemPtr->endP);
                _tempCurveItemPtr->setPath(tpath);
                _tempCurveItemPtr->setVisible(true);
            }
            scene()->update();
        }
    }
    //else {
    //    if (ModeManager::get_instance().isModeEq(EditMode::Lines)) {
    //        _tempPathItemPtr->modifyPoint(mapToScene(_lastMousePos));
    //        update();
    //    }
    //}
    emit mouseMovePos(mapToScene(event->pos()).toPoint());
    QGraphicsView::mouseMoveEvent(event);
}

void MyGraphicsView::wheelEvent(QWheelEvent* event)
{
    // 获取鼠标滚轮的距离
    int wheelDeltaValue = event->delta();
    // 向上滚动，放大
    qreal currentscale = this->matrix().m11();

    int ccc = currentscale * 100 + 0.5;
    currentscale = qreal(ccc) / 100;
    QString str;
    int t = 1;

    if (currentscale > 1)
    {
        QString str = QString::number(currentscale);
        t = str.toInt() ;
        if (t == 0)
            t = 1;
    }
    
    int danwei = t / 10;
    if (wheelDeltaValue > 0)
    {
        if (currentscale >= 0.9 && currentscale*100 < 195)
        {
            this->scale(1 / currentscale, 1 / currentscale);
            this->scale(currentscale + 0.2, currentscale + 0.2);
        }
        
        if (t == 2)
        {
            
            this->scale(1 / currentscale, 1 / currentscale);
            this->scale(currentscale + 2, currentscale + 2);
        }
        
        if (t == 4)
        {
            
            this->scale(1 / currentscale, 1 / currentscale);
            this->scale(currentscale + 1, currentscale + 1);
        }

        if (t == 5)
        {

            this->scale(1 / currentscale, 1 / currentscale);
            this->scale(currentscale + 3, currentscale + 3);
        }
        
        if ( t == 8 )
        {
            this->scale(1 / currentscale, 1 / currentscale);
            this->scale(currentscale + 2, currentscale + 2);
        }

        if (t % 10 == 0)
        {
            if (currentscale == 2000)
                return;
            int x = t,num = 0;
            while (1)
            {
                x = x / 10;
                num++;
                if (x < 10)
                {
                    break;
                }

            }

            if (x == 1)
            {
                this->scale(1 / currentscale, 1 / currentscale);
                this->scale(currentscale + 1*pow(10, num), currentscale + 1* pow(10, num));
            }
            if (x == 2)
            {
                this->scale(1 / currentscale, 1 / currentscale);
                this->scale(currentscale + 2 * pow(10, num), currentscale + 2 * pow(10, num));
            }
            if (x == 4)
            {
                this->scale(1 / currentscale, 1 / currentscale);
                this->scale(currentscale + 1 * pow(10, num), currentscale + 1 * pow(10, num));
            }
            if (x == 5)
            {
                this->scale(1 / currentscale, 1 / currentscale);
                this->scale(currentscale + 3 * pow(10, num), currentscale + 3 * pow(10, num));
            }
            if (x == 8)
            {
                this->scale(1 / currentscale, 1 / currentscale);
                this->scale(currentscale + 2 * pow(10, num), currentscale + 2 * pow(10, num));
            }
        }
   
        
        if (currentscale < 1)
        {
            double x = currentscale;
            int num = 0;
            while (1)
            {
                x = x * 10;
                num--;
                if (x > 1)
                {
                    break;
                }

            }
            if (x == 10)
            {
                if (currentscale != 2000)
                {
                    this->scale(1 / currentscale, 1 / currentscale);
                    this->scale(currentscale + 1 * pow(10, num + 1), currentscale + 1 * pow(10, num + 1));

                }
                else
                {
                    this->scale(1 / currentscale, 1 / currentscale);
                    this->scale(currentscale - 1 * pow(10, num), currentscale - 1 * pow(10, num));
                }
            }
            if (x == 2)
            {
                this->scale(1 / currentscale, 1 / currentscale);
                this->scale(currentscale + 2 * pow(10, num), currentscale + 2 * pow(10, num));
            }
            if (x == 4)
            {
                this->scale(1 / currentscale, 1 / currentscale);
                this->scale(currentscale + 1 * pow(10, num), currentscale + 1 * pow(10, num));
            }
            if (x == 5)
            {
                this->scale(1 / currentscale, 1 / currentscale);
                this->scale(currentscale + 3 * pow(10, num), currentscale + 3 * pow(10, num));
            }
            if (x == 8)
            {
                this->scale(1 / currentscale, 1 / currentscale);
                this->scale(currentscale + 2 * pow(10, num), currentscale + 2 * pow(10, num));
            }
        }


    }

    // 向下滚动，缩小
    else
    {
        if (currentscale >= 1 && currentscale * 100 < 195)
        {
            this->scale(1 / currentscale, 1 / currentscale);
            this->scale(currentscale - 0.2, currentscale - 0.2);
        }

        if (t == 2)
        {

            this->scale(1 / currentscale, 1 / currentscale);
            this->scale(currentscale - 0.2, currentscale - 0.2);
        }

        if (t == 4)
        {

            this->scale(1 / currentscale, 1 / currentscale);
            this->scale(currentscale - 2, currentscale - 2);
        }

        if (t == 5)
        {

            this->scale(1 / currentscale, 1 / currentscale);
            this->scale(currentscale - 1, currentscale - 1);
        }

        if (t == 8)
        {
            this->scale(1 / currentscale, 1 / currentscale);
            this->scale(currentscale - 3, currentscale - 3);
        }

        if (t % 10 == 0)
        {
            int x = t, num = 0;
            while (1)
            {
                x = x / 10;
                num++;
                if (x < 10)
                {
                    break;
                }

            }

            if (x == 1)
            {
                if (currentscale != 2000)
                {
                    this->scale(1 / currentscale, 1 / currentscale);
                    this->scale(currentscale - 2 * pow(10, num - 1), currentscale - 2 * pow(10, num-1));

                }
                else
                {
                    this->scale(1 / currentscale, 1 / currentscale);
                    this->scale(currentscale - 1 * pow(10, num), currentscale - 1 * pow(10, num));
                }
            }
            if (x == 2)
            {
                this->scale(1 / currentscale, 1 / currentscale);
                this->scale(currentscale - 1 * pow(10, num), currentscale - 1 * pow(10, num));
            }
            if (x == 4)
            {
                this->scale(1 / currentscale, 1 / currentscale);
                this->scale(currentscale - 2 * pow(10, num), currentscale - 2 * pow(10, num));
            }
            if (x == 5)
            {
                this->scale(1 / currentscale, 1 / currentscale);
                this->scale(currentscale - 1 * pow(10, num), currentscale - 1 * pow(10, num));
            }
            if (x == 8)
            {
                this->scale(1 / currentscale, 1 / currentscale);
                this->scale(currentscale - 3 * pow(10, num), currentscale - 3 * pow(10, num));
            }
        }


        if (currentscale < 1)
        {
            double x = currentscale;
            int num = 0;
            if (x == 0.1)
                return;
            while (1)
            {
                x = x * 10;
                num--;
                if (x > 1)
                {
                    break;
                }

            }
            if (x == 10)
            {
                if (currentscale != 2000)
                {
                    this->scale(1 / currentscale, 1 / currentscale);
                    this->scale(currentscale - 2 * pow(10, num), currentscale - 2 * pow(10, num ));

                }
                else
                {
                    this->scale(1 / currentscale, 1 / currentscale);
                    this->scale(currentscale - 1 * pow(10, num), currentscale - 1 * pow(10, num));
                }
            }
            if (x == 2)
            {
                this->scale(1 / currentscale, 1 / currentscale);
                this->scale(currentscale - 1 * pow(10, num), currentscale - 1 * pow(10, num));
            }
            if (x == 4)
            {
                this->scale(1 / currentscale, 1 / currentscale);
                this->scale(currentscale - 2 * pow(10, num), currentscale - 2 * pow(10, num));
            }
            if (x == 5)
            {
                this->scale(1 / currentscale, 1 / currentscale);
                this->scale(currentscale - 1 * pow(10, num), currentscale - 1 * pow(10, num));
            }
            if (x == 8)
            {
                this->scale(1 / currentscale, 1 / currentscale);
                this->scale(currentscale - 3 * pow(10, num), currentscale - 3 * pow(10, num));
            }

        }
        
        //if (currentscale < 1)
        //{
        //    this->scale(1 / 1.2, 1 / 1.2);
        //}
    }


    emit ScaleChanged(this->matrix().m11());
    QString scaleLabelText;
    scaleLabelText.sprintf(u8"缩放倍数：%.2f", this->matrix().m11());
    _scaleLabel->setText(scaleLabelText);
    _statusBarPtr->update();
    leftkedu->update();
    topkedu->update();
    //scene()->update();
}

void MyGraphicsView::setItemAd(QList<QGraphicsItem*> items)
{
    int x, y, w, h;
    x = 5000;
    y = 5000;
    w = -5000;
    h = -5000;


    //先确定左下角的坐标
    for (QList<QGraphicsItem*>::iterator it = items.begin(); it != items.end(); it++)
    {
        QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);

        if(node->type() == 1)
        {
            MyGraphicsRecItem * rect = qgraphicsitem_cast<MyGraphicsRecItem *>(node);

            if (x > rect->mapRectToScene(rect->rect()).x())
            {
                x = rect->mapRectToScene(rect->rect()).x();

            }
            if (y > rect->mapRectToScene(rect->rect()).y())
            {
                y = rect->mapRectToScene(rect->rect()).y();
            }
        }
        else if( node ->type() == 2)
        {
            MyGraphicsEllipseItem * item = qgraphicsitem_cast<MyGraphicsEllipseItem *>(node);

            if (x > item->mapRectToScene(item->rect()).x())
            {
                x = item->mapRectToScene(item->rect()).x();

            }
            if (y > item->mapRectToScene(item->rect()).y())
            {
                y = item->mapRectToScene(item->rect()).y();
            }
        }

    }
    //再确定宽高
    for (QList<QGraphicsItem*>::iterator it = items.begin(); it != items.end(); it++)
    {
        QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);
        if(node->type() == 1)
        {
            MyGraphicsRecItem * rect = qgraphicsitem_cast<MyGraphicsRecItem*>(node);
            if (w < rect->mapToScene(rect->rect()).value(1).x() - x)
            {
                w = rect->mapToScene(rect->rect()).value(1).x() - x;

            }
            if (h < rect->mapToScene(rect->rect()).value(2).y() - y)
            {
                h = rect->mapToScene(rect->rect()).value(2).y() - y;
            }
        }
        else if(node->type()==2)
        {
            MyGraphicsEllipseItem * item = qgraphicsitem_cast<MyGraphicsEllipseItem*>(node);
            if (w < item->mapToScene(item->rect()).value(1).x() - x)
            {
                w = item->mapToScene(item->rect()).value(1).x() - x;

            }
            if (h < item->mapToScene(item->rect()).value(2).y() - y)
            {
                h = item->mapToScene(item->rect()).value(2).y() - y;
            }
        }
    }
    itemad->setPos(x - 10 / itemad->scale, y - 10 / itemad->scale);
    itemad->setRect(0, 0, w + 20 / itemad->scale, h + 20 / itemad->scale);
    itemad->setRec(QRectF(0, 0, w , h ));
    itemad->setVisible(true);
    scene()->update();
}

void MyGraphicsView::preProcessItem()
{
    _tempRectItemPtr->setVisible(false);
    _tempRectItemPtr->setPos(50, -50);
    scene()->addItem(_tempRectItemPtr);

    _tempEllipseItemPtr->setVisible(false);
    _tempEllipseItemPtr->setPos(50, -50);
    scene()->addItem(_tempEllipseItemPtr);

    _tempCircleItemPtr->setVisible(false);
    _tempCircleItemPtr->setPos(50, -50);
    scene()->addItem(_tempCircleItemPtr);

    ////    _tempPathItemPtr->setVisible(false);
    ////    _tempPathItemPtr->setPos(50, -50);
    //scene()->addItem(_tempPathItemPtr);
    
    //画板
    

    mainarea->setPos(0, 0);
    mainarea->setZValue(2);
    scene()->addItem(mainarea);
    

    ////刻度
    
    //topkedu->setPos(0, 400)


    //画格子
    
    myGrid->setZValue(0);
    myGrid->setPos(0,0);
    scene()->addItem(myGrid);
    
    //左侧刻度
    leftkedu->setZValue(3);
    scene()->addItem(leftkedu);
    topkedu->setZValue(3);
    scene()->addItem(topkedu);



    //八个点;

    itemad->setPos(0, 0);
    itemad->setVisible(false);
    //itemad->setData(0,1000);
    scene()->addItem(itemad);

    //加直线
    _tempLineItemPtr->setVisible(false);
    scene()->addItem(_tempLineItemPtr);


    //多边形
    _tempPolygonItemPtr->setVisible(false);
    _tempPolygonItemPtr->setPos(0,0);
    _tempPolygonItemPtr->setRect(QRectF(0,0,0,0));
    scene()->addItem(_tempPolygonItemPtr);

    //文字



    //曲线
    _tempCurveItemPtr->setVisible(true);
    scene()->addItem(_tempCurveItemPtr);

}
void MyGraphicsView::setStatusBarPtr(QStatusBar* statusBarPtr)
{
    _statusBarPtr = statusBarPtr;
    QList<QLabel*> labelList = _statusBarPtr->findChildren<QLabel*>();
    for(int i = 0; i < labelList.size(); i++)
    {
        QLabel* label = labelList.at(i);
        _statusBarPtr->removeWidget(label);
    }
    _posLabel = new QLabel("x: 0.00, y : 0.00 px", this);
    _posLabel->setMinimumWidth(375);
    _scaleLabel = new QLabel(u8"缩放倍数：1.00", this);
    _scaleLabel->setMidLineWidth(375);

    _statusBarPtr->addWidget(_posLabel);
    _statusBarPtr->addWidget(_scaleLabel);
}


void MyGraphicsView::setSelecT()
{
    QList<QGraphicsItem*> items = scene()->items();
    for (QList<QGraphicsItem*>::iterator it = items.begin(); it != items.end(); it++)
    {
        QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);
        if(node->data(0)>0)
        {
                if(node->type()==1)
                {
                    MyGraphicsRecItem *rect = qgraphicsitem_cast<MyGraphicsRecItem*>(node);
                    QPointF p = rect->mapFromScene(mapToScene(_lastMousePos));
                    if(rect->selectEvent(p))
                    {
                        if(k==0)
                        {
                            QList<QGraphicsItem *> selectItems = scene()->selectedItems();
                            for(QGraphicsItem* selectitem : selectItems)
                            {
                                if(rect->data(0)!= selectitem->data(0))
                                {
                                    selectitem->setFlags(NULL);
                                }
                            }
                        }
                    }
                }
                else if(node->type()==2)
                {
                    MyGraphicsEllipseItem *item = qgraphicsitem_cast<MyGraphicsEllipseItem*>(node);
                    QPointF p = item->mapFromScene(mapToScene(_lastMousePos));

                    if(item->selectEvent(p))
                    {
                        if( k==0 )
                        {
                            QList<QGraphicsItem *> selectItems = scene()->selectedItems();
                            for(QGraphicsItem* selectitem : selectItems)
                            {
                                if(item->data(0)!= selectitem->data(0))
                                {
                                    selectitem->setFlags(NULL);
                                }
                            }
                        }
                    }


                }
                else if(node->type() == 3)
                {
                    MyGraphicsCircleItem *item = qgraphicsitem_cast<MyGraphicsCircleItem*>(node);
                    QPointF p = item->mapFromScene(mapToScene(_lastMousePos));

                    if(item->selectEvent(p))
                    {
                        if( k==0 )
                        {
                            QList<QGraphicsItem *> selectItems = scene()->selectedItems();
                            for(QGraphicsItem* selectitem : selectItems)
                            {
                                if(item->data(0)!= selectitem->data(0))
                                {
                                    selectitem->setFlags(NULL);
                                }
                            }
                        }
                    }
                }
                else if(node->type() == 4)
                {
                    MyGraphicsLineItem *item = qgraphicsitem_cast<MyGraphicsLineItem *>(node);
                    QPointF p = item->mapFromScene(mapToScene(_lastMousePos));
                    if(item->selectEvent(p))
                    {
                        if( k==0 )
                        {
                            QList<QGraphicsItem *> selectItems = scene()->selectedItems();
                            for(QGraphicsItem* selectitem : selectItems)
                            {
                                if(item->data(0)!= selectitem->data(0))
                                {
                                    selectitem->setFlags(NULL);
                                }
                            }
                        }
                    }
                }
                else if(node->type() == 5)
                {
                    MyGraphicsPolygonItem *item = qgraphicsitem_cast<MyGraphicsPolygonItem *>(node);
                    QPointF p = item->mapFromScene(mapToScene(_lastMousePos));
                    if(item->selectEvent(p))
                    {
                        if( k==0 )
                        {
                            QList<QGraphicsItem *> selectItems = scene()->selectedItems();
                            for(QGraphicsItem* selectitem : selectItems)
                            {
                                if(item->data(0)!= selectitem->data(0))
                                {
                                    selectitem->setFlags(NULL);
                                }
                            }
                        }
                    }
                }
                else if(node->type() == 6)
                {
                    MyGraphicsTextItem *item = qgraphicsitem_cast<MyGraphicsTextItem *>(node);
                    QPointF p = item->mapFromScene(mapToScene(_lastMousePos));
                    if(item->selectEvent(p))
                    {
                        if( k==0 )
                        {
                            QList<QGraphicsItem *> selectItems = scene()->selectedItems();
                            for(QGraphicsItem* selectitem : selectItems)
                            {
                                if(item->data(0)!= selectitem->data(0))
                                {
                                    selectitem->setFlags(NULL);
                                }
                            }
                        }
                    }
                }
                else if(node->type() == 7)
                {
                    MyGraphicsCurveLineItem *item = qgraphicsitem_cast<MyGraphicsCurveLineItem *>(node);
                    QPointF p = item->mapFromScene(mapToScene(_lastMousePos));
                    if(item->selectEvent(p))
                    {

                        if( k==0 )
                        {
                            QList<QGraphicsItem *> selectItems = scene()->selectedItems();
                            for(QGraphicsItem* selectitem : selectItems)
                            {
                                if(item->data(0)!= selectitem->data(0))
                                {
                                    selectitem->setFlags(NULL);
                                }
                            }
                        }
                    }
                }
                else if(node->type() == 8)
                {
                    MyGraphicsPixMapItem *item = qgraphicsitem_cast<MyGraphicsPixMapItem *>(node);
                    QPointF p = item->mapFromScene(mapToScene(_lastMousePos));
                    if(item->selectEvent(p))
                    {

                        if( k==0 )
                        {
                            QList<QGraphicsItem *> selectItems = scene()->selectedItems();
                            for(QGraphicsItem* selectitem : selectItems)
                            {
                                if(item->data(0)!= selectitem->data(0))
                                {
                                    selectitem->setFlags(NULL);
                                }
                            }
                        }
                    }
                }
                else if( node->type() == 9)
                {
                    MyGraphicsCodeItem *item = qgraphicsitem_cast<MyGraphicsCodeItem *>(node);
                    QPointF p = item->mapFromScene(mapToScene(_lastMousePos));
                    if(item->selectEvent(p))
                    {

                        if( k==0 )
                        {
                            QList<QGraphicsItem *> selectItems = scene()->selectedItems();
                            for(QGraphicsItem* selectitem : selectItems)
                            {
                                if(item->data(0)!= selectitem->data(0))
                                {
                                    selectitem->setFlags(NULL);
                                }
                            }
                        }
                    }
                }
        }

    }

}

