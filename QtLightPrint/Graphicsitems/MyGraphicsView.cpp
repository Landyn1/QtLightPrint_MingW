#include "GraphicsItems/MyGraphicsView.h"
#include"mainWindow.h"
#include <memory>
#include"libsHeaders/ZXingWriter.h"
#include <QMenu>
#include <QPoint>
#include"GraphicsItems/MyKedu.h"
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
#include"GraphicsItems/MyMianArea.h"
#include "GraphicsItems/MygraphicsLinePre.h"
#include<math.h>
#include"GraphicsItems/mygraphicscodeitem.h"
#include<qcursor.h>
#include"thirdcurve.h"
#include"GraphicsItems/mygraphicsgroupitem.h"
#include"ItemAdjust.h"
#include"ItemHandle/itemchangehandle.h"
#include"ItemHandle/itemscalehandle.h"
#include"ItemHandle/itemselecthandle.h"
MyGraphicsView::MyGraphicsView(QWidget *parent)
	: QGraphicsView(parent)
{
    
    itemad = new ItemAdjust();
    itemchangehandler = new ItemChangeHandle(this);
    itemscalehandler = new ItemScaleHandle(this);
    itemselecthandler = new ItemSelectHandle(this);
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
    if(moveble || lefttop_move || righttop_move || leftbuttom_move || midbuttom_move || rightbuttom_move || leftmid_move || rightmid_move)
    {
        k=0;
    }
    if(moveble)
    {
        emit sceneChange();
    }
    if(lefttop_move || midtop_move || righttop_move || leftbuttom_move || midbuttom_move || rightbuttom_move || leftmid_move || rightmid_move)
    {
        itemchangehandler->saveItems();
        emit sceneChange();
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
                item->name = tr("矩形") + str;
                scene()->addItem(item);
                update();
                emit addItem(row,item);
                emit sceneChange();
                row++;
                item_id++;
                item->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
                item->setSelected(true);
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
                item->name = tr("椭圆") + str;
                scene()->addItem(item);
                update();
                emit addItem(row,item);
                emit sceneChange();
                row++;
                item_id++;
                item->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
                item->setSelected(true);
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
                item->name = tr("圆形") + str;
                scene()->addItem(item);
                update();
                emit addItem(row,item);
                emit sceneChange();
                row++;
                item_id++;
                item->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
                item->setSelected(true);
            }
        }
        else if(action_state == 5)
        {
            _tempPolygonItemPtr->setVisible(false);
            MyGraphicsPolygonItem *item = new MyGraphicsPolygonItem();
            item->setRect(_tempPolygonItemPtr->rect());

            item->setDefault_Path();
            item->setPos(_tempPolygonItemPtr->pos());
            item->setVisible(true);
            QString str = QString::number(row + 1);
            item->setData(0, item_id);
            item->name = tr("多边形") + str;
            scene()->addItem(item);
            update();
            emit addItem(row,item);
            emit sceneChange();
            row++;
            item_id++;
            item->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
            item->setSelected(true);
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
    {
        k=1;

    }
    if(action_state == 0)
    {
        itemselecthandler->setSelecT(k);
    }

    else if (action_state == 1) {
    
        _tempRectItemPtr->setPos(mapToScene(_lastMousePos));
        _tempRectItemPtr->setRect(QRectF(0, 0, 0, 0));
        QPen pen;   // 定义一个画笔，设置画笔颜色和宽度
        pen.setWidthF(1);

        _tempRectItemPtr->setPen(pen);
        _tempRectItemPtr->setVisible(false);
    }
    else if (action_state==2) {
        _tempEllipseItemPtr->setPos(mapToScene(_lastMousePos));
        _tempEllipseItemPtr->setRect(QRectF(0, 0, 0, 0));
        QPen pen;   // 定义一个画笔，设置画笔颜色和宽度
        pen.setWidthF(1);
        _tempEllipseItemPtr->setPen(pen);
        _tempEllipseItemPtr->setVisible(false);
    }
    else if (action_state == 3) {
        _tempCircleItemPtr->setPos(mapToScene(_lastMousePos));
        _tempCircleItemPtr->setRect(QRectF(0, 0, 0, 0));       
        QPen pen;   // 定义一个画笔，设置画笔颜色和宽度
        pen.setWidthF(1);
        _tempCircleItemPtr->setPen(pen);
        _tempCircleItemPtr->setVisible(false);
    }
    else if (action_state == 4)
    {
        if (event->button() == Qt::LeftButton ) {

                    if(isPaintLine == false)
                    {
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
                item->name=tr("直线")+str;
                scene()->addItem(item);
                emit addItem(row,item);
                emit sceneChange();
                row++;
                item_id++;
                item->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
                item->setSelected(true);
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
        item->setDefault_Path();
        item->setRect(-item->path.boundingRect().width()/2,-item->path.boundingRect().height()/2,item->path.boundingRect().width(),item->path.boundingRect().height());
        item->makePath_fill_Rect();
        item->setVisible(true);
        item->setData(0, item_id);
        QString str = QString::number(row+1);
        item->name=tr("文本")+str;
        scene()->addItem(item);
        scene()->update();
        emit addItem(row,item);
        emit sceneChange();
        row++;
        item_id++;
        item->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
        item->setSelected(true);

    }
    else if(action_state == 7)
    {
        if (event->button() == Qt::LeftButton ) {

                    _tempCurveItemPtr->setIspaint(true);
                    if(isPaintCurve == false)
                    {
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
                          _tempCurveItemPtr->ctl_pre = _tempCurveItemPtr->symmetryPoint(_tempCurveItemPtr->ctl_next,_tempCurveItemPtr->startP);
                          _tempCurveItemPtr->ctl_next = p;
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
            item->name=tr("曲线")+str;
            scene()->addItem(item);
            emit addItem(row,item);
            emit sceneChange();
            row++;
            item_id++;
            _tempCurveItemPtr->setPath(*_tempCurvePath);
            item->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
            item->setSelected(true);
        }
    }
    else if(action_state == 9)
    {
        QPointF p = mapToScene(_lastMousePos);
        MyGraphicsCodeItem *item = new MyGraphicsCodeItem();
        item->setPathByStr("TEXT","QRCode");
        double w = item->path.boundingRect().width();
        double h = item->path.boundingRect().height();
        item->setPos(p);
        item->set_brush(0,0);
        item->setRect(-w/2,-h/2,w,h);
        item->setData(0, item_id);
        QString str = QString::number(row+1);
        item->name=tr("二维码")+str;
        scene()->addItem(item);
        scene()->update();
        emit addItem(row,item);
        emit sceneChange();
        row++;
        item_id++;
        item->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
        item->setSelected(true);
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
        emit sceneChange();
        return;
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

        for(QGraphicsItem* item:items)
        {
            if(item->data(15).toInt()==1)
            {
                items.removeOne(item);
            }
        }
        double s = this->matrix().m11();
        itemad->setPos(itemad->pos().x() + offsetPos.x()/s,itemad->pos().y()-offsetPos.y()/s);
        for (QList<QGraphicsItem*>::iterator it = items.begin(); it != items.end(); it++)
        {
            QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);
            if(node->type() != 10)
                node->setPos(node->pos().x() + offsetPos.x()/s, node->pos().y() - offsetPos.y()/s);
            else
            {
                MyGraphicsGroupItem *group = qgraphicsitem_cast<MyGraphicsGroupItem*>(node);
                QList<QGraphicsItem*> childs = group->childItems();

                while(1)
                {
                    int k=0;
                    for(QGraphicsItem* item:childs)
                    {
                        if(item->type() == 10)
                        {
                            k=1;
                            childs.removeOne(item);
                            MyGraphicsGroupItem *g =qgraphicsitem_cast<MyGraphicsGroupItem*>(item);
                            childs.append(g->childItems());
                        }
                    }
                    if(k == 0)
                    {
                        break;
                    }
                }

                for(QGraphicsItem* child:childs)
                {
                    child->setPos(child->pos().x() + offsetPos.x()/s, child->pos().y() - offsetPos.y()/s);
                }
                group->set_brush(group->angle,group->space);
            }
        }
        emit selectchange();
    }
    if(action_state == 0 && (event->buttons()& Qt::LeftButton)&&lefttop_move)
    {
        setCursor(Qt::SizeFDiagCursor);
        itemchangehandler->lefttop_set(scenePos,mapToScene(_lastMousePos));
    }
    if(action_state == 0 && (event->buttons()& Qt::LeftButton)&& midtop_move)
    {
        setCursor(Qt::SizeVerCursor);
        itemchangehandler->midtop_set(scenePos,mapToScene(_lastMousePos));
    }
    if(action_state == 0 && (event->buttons()& Qt::LeftButton)&& righttop_move)
    {
        setCursor(Qt::SizeBDiagCursor);
        itemchangehandler->righttop_set(scenePos,mapToScene(_lastMousePos));
    }
    if(action_state == 0 && (event->buttons()& Qt::LeftButton)&& leftbuttom_move)
    {
        setCursor(Qt::SizeBDiagCursor);
        itemchangehandler->leftbuttom_set(scenePos,mapToScene(_lastMousePos));
    }
    if(action_state == 0 && (event->buttons()& Qt::LeftButton)&& midbuttom_move)
    {
        setCursor(Qt::SizeVerCursor);
        itemchangehandler->midbuttom_set(scenePos,mapToScene(_lastMousePos));
    }
    if(action_state == 0 && (event->buttons()& Qt::LeftButton)&&rightbuttom_move)
    {
        setCursor(Qt::SizeFDiagCursor);
        itemchangehandler->rightbuttom_set(scenePos,mapToScene(_lastMousePos));
    }
    if(action_state == 0 && (event->buttons()& Qt::LeftButton)&&leftmid_move)
    {
        setCursor(Qt::SizeHorCursor);
        itemchangehandler->leftmid_set(scenePos,mapToScene(_lastMousePos));
    }
    if(action_state == 0 && (event->buttons()& Qt::LeftButton)&&rightmid_move)
    {
        setCursor(Qt::SizeHorCursor);
        itemchangehandler->rightmid_set(scenePos,mapToScene(_lastMousePos));
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
            _tempPolygonItemPtr->setVisible(true);
            update();
        }
        else if(action_state == 7)
        {
            if(isPaintCurve == false)
            {
                _tempCurveItemPtr->ctl_next = _tempCurveItemPtr->symmetryPoint(scenePos,_tempCurveItemPtr->endP);
            }
            else
            {

                _tempCurveItemPtr->ctl_next = _tempCurveItemPtr->symmetryPoint(scenePos,_tempCurveItemPtr->endP);
                QPainterPath tpath = *_tempCurvePath;
                tpath.cubicTo(_tempCurveItemPtr->ctl_pre,_tempCurveItemPtr->ctl_next,_tempCurveItemPtr->endP);
                _tempCurveItemPtr->setPath(tpath);
                _tempCurveItemPtr->setVisible(true);
            }
            scene()->update();
        }
    }
    emit mouseMovePos(mapToScene(event->pos()).toPoint());
    //QGraphicsView::mouseMoveEvent(event);
}

void MyGraphicsView::wheelEvent(QWheelEvent* event)
{
    // 获取鼠标滚轮的距离
    int wheelDeltaValue = event->delta();
    // 向上滚动，放大
    qreal currentscale = this->matrix().m11();
    itemscalehandler->changeScale(currentscale,wheelDeltaValue);

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
    if(lan == 0)
        _scaleLabel = new QLabel(u8"缩放倍数：1.00", this);
    else
        _scaleLabel = new QLabel(u8"scale：1.00", this);
    _scaleLabel->setMidLineWidth(375);

    _statusBarPtr->addWidget(_posLabel);
    _statusBarPtr->addWidget(_scaleLabel);
}


