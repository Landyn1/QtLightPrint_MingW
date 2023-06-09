﻿#include "MyGraphicsView.h"
#include"mainWindow.h"
#include <memory>

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
#include<qcursor.h>
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

void MyGraphicsView::mouseReleaseEvent(QMouseEvent* event)
{

    //k=0;
    if(moveble)
        k=0;
    moveble = false;
    selectedId.clear();

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

                item->setRect(0,0,_tempRectItemPtr->rect().width(),_tempRectItemPtr->rect().height());
                item->setPos(p);
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

    moveble = QRectF(itemad->pos().x() + itemad->mid.x(), itemad->pos().y() + itemad->mid.y(), itemad->mid.width(), itemad->mid.height()).contains(mapToScene( event->pos()));
    if(moveble)
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
            }

        }

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
        item->setPos(p.x(),p.y()+12);
        item->setVisible(true);
        item->setData(0, item_id);
        QString str = QString::number(row+1);
        item->name="文本"+str;
        scene()->addItem(item);
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
    QGraphicsView::mousePressEvent(event);
}
void MyGraphicsView::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Control)

    {
        k = 1;

    }
}
void MyGraphicsView::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Control)
        k=0;

}

void MyGraphicsView::mouseMoveEvent(QMouseEvent* event)
{
    QPointF scenePos = mapToScene(event->pos());
    QString posLabelText;
    posLabelText.sprintf("x: %.2f, y: %.2f px", scenePos.x(), scenePos.y());
    _posLabel->setText(posLabelText);
    _statusBarPtr->update();
    //_lastMousePos = QPoint(_lastMousePos.x(), -_lastMousePos.y());
    QPointF offsetPos = event->pos() - _lastMousePos;
    _lastMousePos = event->pos();
    
    if (action_state == 0  && QRectF(itemad->pos().x() + itemad->mid.x(), itemad->pos().y() + itemad->mid.y(), itemad->mid.width(), itemad->mid.height()).contains(mapToScene( event->pos())))
    {
        setCursor(Qt::SizeAllCursor);

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
            float newPos_x = qMin(mapToScene(_lastMousePos).x(), tmp_pos.x());
            float newPos_y = qMin(mapToScene(_lastMousePos).y(), tmp_pos.y());
            float newWidth = qAbs(mapToScene(_lastMousePos).x() - tmp_pos.x());
            float newHeight = qAbs(mapToScene(_lastMousePos).y() - tmp_pos.y());
            _tempRectItemPtr->setRect(newPos_x - tmp_pos.x(), newPos_y - tmp_pos.y(), newWidth, newHeight);



            _tempRectItemPtr->setVisible(true);

        }
        else if (action_state==2) {
            QPointF tmp_pos = _tempEllipseItemPtr->pos();
            float newWidth = qAbs(mapToScene(_lastMousePos).x() - tmp_pos.x());
            float newHeight = qAbs(mapToScene(_lastMousePos).y() - tmp_pos.y());
            _tempEllipseItemPtr->setRect(-newWidth , -newHeight , newWidth*2, newHeight*2);
            _tempEllipseItemPtr->setVisible(true);
        }
        else if (action_state == 3) {
            QPointF tmp_pos = _tempCircleItemPtr->pos();
            float newWidth = qAbs(mapToScene(_lastMousePos).x() - tmp_pos.x());
            float newHeight = qAbs(mapToScene(_lastMousePos).y() - tmp_pos.y());
            auto r = qMax(newWidth, newHeight);
            _tempCircleItemPtr->setRect(-r, -r, r * 2, r * 2);
            _tempCircleItemPtr->setVisible(true);
        }
        else if(action_state == 5)
        {
            QPointF tmp_pos = _tempPolygonItemPtr->pos();
            float newWidth = qAbs(mapToScene(_lastMousePos).x() - tmp_pos.x());
            float newHeight = qAbs(mapToScene(_lastMousePos).y() - tmp_pos.y());
            float r = qMax(newWidth, newHeight);
            _tempPolygonItemPtr->setRect(-newWidth , -newHeight , newWidth*2, newHeight*2);
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
    _posLabel = new QLabel("x: 0.00, y : 0.00 px", this);
    _posLabel->setMinimumWidth(375);
    _scaleLabel = new QLabel(u8"缩放倍数：1.00", this);
    _scaleLabel->setMidLineWidth(375);
    
    _statusBarPtr->addWidget(_posLabel);
    _statusBarPtr->addWidget(_scaleLabel);
}

