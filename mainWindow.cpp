#include "mainWindow.h"
#include<qdebug.h>
#include"MyGraphicsScene.h"
#include"MyGraphicsView.h"
#include<qgraphicsitem.h>
#include<QScrollBar.h>
#include"MygraphicsLinePre.h"
#include<qlist.h>
#include<QInputDialog.h>
#include "MyKedu.h"
#include"CUDrvE.h"
#include<iostream>
#include<qmessagebox.h>
#include<qfiledialog.h>
#include<qimagereader.h>
using namespace std;
int action_state;
int k;
mainWindow::mainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    QWidget* p = takeCentralWidget();
    if (p)
        delete p;
    setDockNestingEnabled(true);
   
    
    ui.itemtable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui.itemtable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    
    //ishdishd
    splitDockWidget(ui.dock1, ui.dock7, Qt::Horizontal);
    

    
    
    splitDockWidget(ui.dock1, ui.dock2, Qt::Vertical);
    
    
    //splitDockWidget(ui.dock4, ui.dock5_button, Qt::Vertical);
    splitDockWidget(ui.dock7, ui.dock5_button, Qt::Vertical);
    splitDockWidget(ui.dock7, ui.dock_leftKedu, Qt::Horizontal);
    splitDockWidget(ui.dock_leftKedu, ui.dock_topKedu, Qt::Horizontal);
   // splitDockWidget(ui.dock_topKedu, ui.dock3, Qt::Horizontal);
    splitDockWidget(ui.dock_topKedu, ui.dock4, Qt::Vertical);
    
    

    //鍒lkl
    QWidget* lTitleBar = ui.dock4->titleBarWidget();
    QWidget* lEmptyWidget = new QWidget();
    ui.dock4->setTitleBarWidget(lEmptyWidget);
    delete lTitleBar;

    QWidget* lTitleBar1 = ui.dock7->titleBarWidget();
    QWidget* lEmptyWidget1 = new QWidget();
    ui.dock7->setTitleBarWidget(lEmptyWidget1);
    delete lTitleBar1;


    lTitleBar = ui.dock_topKedu->titleBarWidget();
    lEmptyWidget = new QWidget();
    ui.dock_topKedu->setTitleBarWidget(lEmptyWidget);
    delete lTitleBar;

    lTitleBar = ui.dock_leftKedu->titleBarWidget();
    lEmptyWidget = new QWidget();
    ui.dock_leftKedu->setTitleBarWidget(lEmptyWidget);
    delete lTitleBar;

    ui.dock4->setWindowTitle("wenjian1");
    //璁剧疆鍥炬爣
    ui.bianji->setIcon(QIcon(":/draw/Res/Select.png"));
    ui.draw_line->setIcon(QIcon(":/draw/Res/Line.png"));
    //ui.draw_quline->setIcon(QIcon(":/draw/Res/Line.png"));
    ui.draw_yuan->setIcon(QIcon(":/draw/Res/Circle.png"));
    ui.draw_wenzi->setIcon(QIcon(":/draw/Res/Font.png"));
    ui.draw_sanjiao->setIcon(QIcon(":/draw/Res/Rectangle.png"));
    ui.draw_polygon->setIcon(QIcon(":/draw/Res/RegularPolygon.png"));
    //璁剧疆鍒濆澶у皬
    
    MyWidget* wi1 = new MyWidget;
    MyWidget* wi2 = new MyWidget;
    MyWidget* wi3 = new MyWidget;
    MyWidget* wi4 = new MyWidget;
    MyWidget* wi5 = new MyWidget;
    //ui.itemtable->setParent(wi1);
    wi1->size = QSize(200, 200);
    QVBoxLayout* layout1 = new QVBoxLayout;
    QVBoxLayout* layout2 = new QVBoxLayout;
    QVBoxLayout* layout3 = new QVBoxLayout;
    QVBoxLayout* layout4 = new QVBoxLayout;
    QVBoxLayout* layout5 = new QVBoxLayout;
   
    /*涓?涓竴涓缃紝涓?鍏辨槸浜斾釜dock*/
    layout1->addWidget(ui.itemtable);
    wi1->setLayout(layout1);
    ui.dock1->setWidget(wi1);

    wi2->size = QSize(200, 400);
    layout2->addWidget(ui.widget_4);
    wi2->setLayout(layout2);
    ui.dock2->setWidget(wi2);

    ui.dock7->setWidget(ui.widget_5);

    /*wi4->size = QSize(600, 600);
    layout4->addWidget(ui.widget_6);
    wi4->setLayout(layout4);
    ui.dock4->setWidget(wi4);*/
    
   // action_state = 0;

    scene = new MyGraphicsScene();
    
    view = new MyGraphicsView(ui.widget_6);

    view->setScene(scene);
    
    view->setMouseTracking(true);

    view->preProcessItem();
    view->setStatusBarPtr(ui.statusBar);


    scene->setBackgroundBrush(Qt::white);
    scene->setSceneRect(-10000, -10000, 20000, 20000);
    view->setAlignment(Qt::AlignCenter);
    ui.dock4->setWidget(view);

    view->centerOn(QPointF(0, 0));
    view->scale(1, -1);
    //鐢婚《閮ㄥ埢搴︾嚎
    
    //view->verticalScrollBar()->setValue(1);

    //RulerWidget* topRuler = new RulerWidget(Qt::Horizontal);
   // ui.dock_topKedu->setWidget(topRuler);

    connect(view->horizontalScrollBar(), &QScrollBar::valueChanged, [=]
        {
           // topRuler->setOffset(view->mapToScene(0, 0).x());
            view->topkedu->setOffset(view->mapToScene(0, 0).x());
            view->leftkedu->setPos(view->mapToScene(0, 0).x(),0);
            view->topkedu->setViewWidth(view->size().width());
            scene->update();
        });
    connect(view->horizontalScrollBar(), &QScrollBar::rangeChanged, [=]
        {
           // topRuler->setOffset(view->mapToScene(0, 0).x());
            view->topkedu->setOffset(view->mapToScene(0, 0).x());
            view->leftkedu->setPos(view->mapToScene(0, 0).x(), 0);
            view->topkedu->setViewWidth(view->size().width());
            scene->update();
        });


    //ui.colortable->horizontalHeader()->setResizeMode(QHeaderView::Stretch);

    ui.colortable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QSize size = ui.dock3->size();
    
    ui.dock_leftKedu->setVisible(false);
    ui.dock_topKedu->setVisible(false);
    //设置图元表
    ui.itemtable->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);//楂樺害鍥哄畾
    ui.itemtable->verticalHeader()->setDefaultSectionSize(20);
    //ui.itemtable->setFrameShape(QFrame::NoFrame);
    ui.itemtable->setShowGrid(false);
    ui.itemtable->verticalHeader()->setVisible(false);
    ui.itemtable->setEditTriggers(QAbstractItemView::NoEditTriggers);//涓嶅彲缂栬緫
    ui.itemtable->setSelectionBehavior(QAbstractItemView::SelectRows);//璁剧疆閫変腑涓?琛?
    ui.itemtable->setColumnHidden(3, true); // 闅愯棌绗笁鍒?
    ui.itemtable->setSelectionMode(QAbstractItemView::ExtendedSelection);




    connect(view->verticalScrollBar(), &QScrollBar::valueChanged, [=]
        {
            view->topkedu->setPos(0, view->mapToScene(0, 0).y() );
            view->myGrid->setshuzhi_Offset(view->mapToScene(0, 0).y());
            view->mainarea->setOffset(view->mapToScene(0, 0).y());
            view->leftkedu->setOffset(view->mapToScene(0, 0).y());
            view->leftkedu->setViewHeight(view->size().height());
            view->leftkedu->update();
            scene->update();
        });

    connect(view->verticalScrollBar(), &QScrollBar::rangeChanged, [=]
        {
           // leftRuler->setOffset(-view->mapToScene(0, 0).y());
            view->topkedu->setPos(0, view->mapToScene(0, 0).y());
            view->myGrid->setshuzhi_Offset(view->mapToScene(0, 0).y());
            view->mainarea->setOffset(view->mapToScene(0, 0).y());
            view->myGrid->setrect(view->sceneRect());
            view->leftkedu->setViewHeight(view->size().height());
            //view->verticalScrollBar()->setValue(1);
            //view->verticalScrollBar()->setValue(7);
            view->verticalScrollBar()->setValue(500);
            view->verticalScrollBar()->setValue(-310);
            scene->update();
        });
    //ui.dock_leftKedu->setVisible(false);

    connect(view, &MyGraphicsView::mouseMovePos, [=](QPointF pos)
        {
            view->leftkedu->setslidingLinePos(pos.y());
            view->topkedu->setslidingLinePos(pos.x());
        });

    //调整scale
    connect(view, &MyGraphicsView::ScaleChanged, [=](double scale)
        {
           // topRuler->setscale(scale);
           // leftRuler->setscale(scale);
            view->topkedu->setscales(scale);
            view->myGrid->setscales(scale);
            view->mainarea->setscales(scale);
            view->leftkedu->setscales(scale);
            scene->update();
        });
    
    //添加
    connect(view, &MyGraphicsView::addItem,ui.itemtable, [=](int row,QGraphicsItem * item) {
        int type = item->type();
        row = scene->items().length()-12;
        QTableWidgetItem* item0;
        QTableWidgetItem* item1;
        QTableWidgetItem* item2;
        QTableWidgetItem* item3;
        int id;
        if (type == 1)
        {
            MyGraphicsRecItem* node;
             node = qgraphicsitem_cast<MyGraphicsRecItem*>(item);
             item0 = new QTableWidgetItem(node->name);
             
             item1 = new QTableWidgetItem("矩形");
             item2 = new QTableWidgetItem("");
             id = node->data(0).value<int>();
             QString s = QString::number(id);
             item3 = new QTableWidgetItem(s);
        }
        else if(type==2)
        {
             MyGraphicsEllipseItem* node;
             node = qgraphicsitem_cast<MyGraphicsEllipseItem*>(item);
             item0 = new QTableWidgetItem(node->name);

             item1 = new QTableWidgetItem("椭圆");
             item2 = new QTableWidgetItem("");
             id = node->data(0).value<int>();
             QString s = QString::number(id);
             item3 = new QTableWidgetItem(s);
        }
        else if(type == 3)
        {
             MyGraphicsCircleItem* node;
             node = qgraphicsitem_cast<MyGraphicsCircleItem*>(item);
             item0 = new QTableWidgetItem(node->name);

             item1 = new QTableWidgetItem("圆形");
             item2 = new QTableWidgetItem("");
             id = node->data(0).value<int>();
             QString s = QString::number(id);
             item3 = new QTableWidgetItem(s);
        }

        else if(type == 4)
        {
            MyGraphicsLineItem *node;
            node = qgraphicsitem_cast<MyGraphicsLineItem*>(item);
            item0 = new QTableWidgetItem(node->name);

            item1 = new QTableWidgetItem("直线");
            item2 = new QTableWidgetItem("");
            id = node->data(0).value<int>();
            QString s = QString::number(id);
            item3 = new QTableWidgetItem(s);
        }
        else if(type == 5)
        {
            MyGraphicsPolygonItem* node;
             node = qgraphicsitem_cast<MyGraphicsPolygonItem*>(item);
             item0 = new QTableWidgetItem(node->name);

             item1 = new QTableWidgetItem("多边形");
             item2 = new QTableWidgetItem("");
             id = node->data(0).value<int>();
             QString s = QString::number(id);
             item3 = new QTableWidgetItem(s);
        }
        else if(type == 6)
        {
            MyGraphicsTextItem* node;
             node = qgraphicsitem_cast<MyGraphicsTextItem*>(item);
             item0 = new QTableWidgetItem(node->name);

             item1 = new QTableWidgetItem("文本");
             item2 = new QTableWidgetItem("");
             id = node->data(0).value<int>();
             QString s = QString::number(id);
             item3 = new QTableWidgetItem(s);
        }
        else if(type == 7)
        {
            MyGraphicsCurveLineItem* node;
             node = qgraphicsitem_cast<MyGraphicsCurveLineItem*>(item);
             item0 = new QTableWidgetItem(node->name);

             item1 = new QTableWidgetItem("曲线");
             item2 = new QTableWidgetItem("");
             id = node->data(0).value<int>();
             QString s = QString::number(id);
             item3 = new QTableWidgetItem(s);
        }
        else if(type == 8)
        {
            MyGraphicsPixMapItem* node;
             node = qgraphicsitem_cast<MyGraphicsPixMapItem*>(item);
             item0 = new QTableWidgetItem(node->name);

             item1 = new QTableWidgetItem("图片");
             item2 = new QTableWidgetItem("");
             id = node->data(0).value<int>();
             QString s = QString::number(id);
             item3 = new QTableWidgetItem(s);
        }
        ui.itemtable->setRowCount(row + 1);
        
        ui.itemtable->setItem(row, 0, item0);
        ui.itemtable->setItem(row, 1, item1);
        ui.itemtable->setItem(row, 2, item2);
        ui.itemtable->setItem(row, 3, item3);
        ui.itemtable->update();
        });


    //修改名字
    connect(ui.itemtable, &QTableWidget::itemDoubleClicked, this, [&]() {
        int row = ui.itemtable->currentRow();
        QTableWidgetItem* item1 = new QTableWidgetItem;
        item1 = ui.itemtable->item(row, 3);
        QString id = item1->text();       
        QTableWidgetItem* item2 = new QTableWidgetItem;
        item2 = ui.itemtable->item(row, 0);
        QString name = item2->text();
        bool isOK;
        QString text = QInputDialog::getText(this, "修改名称",
            NULL,
            QLineEdit::Normal,
            name,
            &isOK,
            Qt::WindowCloseButtonHint );
        if (isOK) {
            QList<QGraphicsItem*> items = scene->items() ;
            for (QList<QGraphicsItem*>::iterator it = items.begin(); it != items.end(); it++)
            {
                QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);
                int id1 = node->data(0).value<int>();
                if (node->isVisible() && id == QString::number(id1))
                {
                    //qDebug() << node->type() << endl;
                    if (node->type() == 1)
                    {
                        MyGraphicsRecItem* rect;
                        rect = qgraphicsitem_cast<MyGraphicsRecItem*>(node);
                        rect->name = text;
                        item2->setText(text);
                        ui.itemtable->setItem(row, 0, item2);
                    }
                    else if(node->type() == 2)
                    {
                        MyGraphicsEllipseItem* rect;
                        rect = qgraphicsitem_cast<MyGraphicsEllipseItem*>(node);
                        rect->name = text;
                        item2->setText(text);
                        ui.itemtable->setItem(row, 0, item2);

                    }
                    else if(node->type() == 3)
                    {
                        MyGraphicsCircleItem* rect;
                        rect = qgraphicsitem_cast<MyGraphicsCircleItem*>(node);
                        rect->name = text;
                        item2->setText(text);
                        ui.itemtable->setItem(row, 0, item2);
                    }
                    else if(node->type() == 4)
                    {
                        MyGraphicsLineItem *line;
                        line = qgraphicsitem_cast<MyGraphicsLineItem*>(node);
                        line->name = text;
                        item2->setText(text);
                        ui.itemtable->setItem(row,0,item2);
                    }
                    else if(node->type() == 5)
                    {
                        MyGraphicsPolygonItem* rect;
                        rect = qgraphicsitem_cast<MyGraphicsPolygonItem*>(node);
                        rect->name = text;
                        item2->setText(text);
                        ui.itemtable->setItem(row, 0, item2);
                    }
                    else if(node->type() == 6)
                    {
                        MyGraphicsTextItem* rect;
                        rect = qgraphicsitem_cast<MyGraphicsTextItem*>(node);
                        rect->name = text;
                        item2->setText(text);
                        ui.itemtable->setItem(row, 0, item2);
                    }
                    else if(node->type() == 7)
                    {
                        MyGraphicsCurveLineItem* rect;
                        rect = qgraphicsitem_cast<MyGraphicsCurveLineItem*>(node);
                        rect->name = text;
                        item2->setText(text);
                        ui.itemtable->setItem(row, 0, item2);
                    }
                    else if(node->type() == 8)
                    {
                        MyGraphicsPixMapItem *rect;
                        rect = qgraphicsitem_cast<MyGraphicsPixMapItem*>(node);
                        rect->name = text;
                        item2->setText(text);
                        ui.itemtable->setItem(row, 0, item2);
                    }
                    break;
                }
                
            }
        }

        });



    //显示坐标
    connect(ui.itemtable, &QTableWidget::itemSelectionChanged, this, [&]() {
        QList<QTableWidgetItem*> selectItems = ui.itemtable->selectedItems();
        QSet<int> rows;
        for (QTableWidgetItem* item : selectItems)
        {
            rows.insert(item->row());
        }
        QSet<int>::iterator iter;
        int zuoxiax = 5100, zuoxiay = 5100, youshangx = -5100, youshangy = -5100;
        int k = 0;
        for (iter = rows.begin(); iter != rows.end(); iter++)
        {
            int row = *iter;
            QTableWidgetItem* item1 = new QTableWidgetItem;
            item1 = ui.itemtable->item(row, 3);
            QString id = item1->text();
            QList<QGraphicsItem*> items = scene->items();
            for (QList<QGraphicsItem*>::iterator it = items.begin(); it != items.end(); it++)
            {
                QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);
                int id1 = node->data(0).value<int>();
                if (node->isVisible() && id == QString::number(id1))
                {
                    k = 1;
                    if (node->type() == 1)
                    {
                        MyGraphicsRecItem* rect;
                        rect = qgraphicsitem_cast<MyGraphicsRecItem*>(node);
                        if (action_state == 0)
                        {
                            rect->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);  
                        }
                        else
                        {
                            rect->setFlags(QGraphicsItem::ItemIsSelectable);
                        }
                        rect->setSelected(true);
                        if (zuoxiax > rect->mapToScene(rect->rect()).value(0).x())
                        {
                            zuoxiax = rect->mapToScene(rect->rect()).value(0).x();
                        }
                        if (zuoxiay > rect->mapToScene(rect->rect()).value(0).y())
                        {
                            zuoxiay = rect->mapToScene(rect->rect()).value(0).y();
                        }
                        if (youshangx < rect->mapToScene(rect->rect()).value(2).x())
                        {
                            youshangx = rect->mapToScene(rect->rect()).value(2).x();
                        }
                        if (youshangy < rect->mapToScene(rect->rect()).value(2).y())
                        {
                            youshangy = rect->mapToScene(rect->rect()).value(2).y();
                        }                        
                        scene->update();
                        
                    }

                    else if(node->type() == 2)
                    {
                        MyGraphicsEllipseItem* rect;
                        rect = qgraphicsitem_cast<MyGraphicsEllipseItem*>(node);
                        if (action_state == 0)
                        {
                            rect->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
                        }
                        else
                        {
                            rect->setFlags(QGraphicsItem::ItemIsSelectable);
                        }
                        rect->setSelected(true);
                        if (zuoxiax > rect->mapToScene(rect->rect()).value(0).x())
                        {
                            zuoxiax = rect->mapToScene(rect->rect()).value(0).x();
                        }
                        if (zuoxiay > rect->mapToScene(rect->rect()).value(0).y())
                        {
                            zuoxiay = rect->mapToScene(rect->rect()).value(0).y();
                        }
                        if (youshangx < rect->mapToScene(rect->rect()).value(2).x())
                        {
                            youshangx = rect->mapToScene(rect->rect()).value(2).x();
                        }
                        if (youshangy < rect->mapToScene(rect->rect()).value(2).y())
                        {
                            youshangy = rect->mapToScene(rect->rect()).value(2).y();
                        }
                        scene->update();
                    }

                    else if(node->type() == 3)
                    {
                        MyGraphicsCircleItem* rect;
                        rect = qgraphicsitem_cast<MyGraphicsCircleItem*>(node);
                        if (action_state == 0)
                        {
                            rect->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
                        }
                        else
                        {
                            rect->setFlags(QGraphicsItem::ItemIsSelectable);
                        }
                        rect->setSelected(true);
                        if (zuoxiax > rect->mapToScene(rect->rect()).value(0).x())
                        {
                            zuoxiax = rect->mapToScene(rect->rect()).value(0).x();
                        }
                        if (zuoxiay > rect->mapToScene(rect->rect()).value(0).y())
                        {
                            zuoxiay = rect->mapToScene(rect->rect()).value(0).y();
                        }
                        if (youshangx < rect->mapToScene(rect->rect()).value(2).x())
                        {
                            youshangx = rect->mapToScene(rect->rect()).value(2).x();
                        }
                        if (youshangy < rect->mapToScene(rect->rect()).value(2).y())
                        {
                            youshangy = rect->mapToScene(rect->rect()).value(2).y();
                        }
                        scene->update();
                    }

                    else if(node->type() == 4)
                    {
                        MyGraphicsLineItem* line;
                        line = qgraphicsitem_cast<MyGraphicsLineItem*>(node);
                        if (action_state == 0)
                        {
                            line->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
                        }
                        else
                        {
                            line->setFlags(QGraphicsItem::ItemIsSelectable);
                        }
                        line->setSelected(true);
                        if (zuoxiax > line->getRect().x())
                        {
                            zuoxiax = line->getRect().x();
                        }
                        if (zuoxiay > line->getRect().y())
                        {
                            zuoxiay = line->getRect().y();
                        }
                        if (youshangx < line->getRect().x()+line->getRect().width())
                        {
                            youshangx = line->getRect().x()+line->getRect().width();
                        }
                        if (youshangy < line->getRect().y()+line->getRect().height())
                        {
                            youshangy = line->getRect().y()+line->getRect().height();
                        }
                        scene->update();
                    }
                    else if(node->type() == 5)
                    {
                        MyGraphicsPolygonItem* line;
                        line = qgraphicsitem_cast<MyGraphicsPolygonItem*>(node);
                        if (action_state == 0)
                        {
                            line->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
                        }
                        else
                        {
                            line->setFlags(QGraphicsItem::ItemIsSelectable);
                        }
                        line->setSelected(true);
                        if (zuoxiax > line->getRect().x())
                        {
                            zuoxiax = line->getRect().x();
                        }
                        if (zuoxiay > line->getRect().y())
                        {
                            zuoxiay = line->getRect().y();
                        }
                        if (youshangx < line->getRect().x()+line->getRect().width())
                        {
                            youshangx = line->getRect().x()+line->getRect().width();
                        }
                        if (youshangy < line->getRect().y()+line->getRect().height())
                        {
                            youshangy = line->getRect().y()+line->getRect().height();
                        }
                        scene->update();
                    }

                    //TODO:
                    else if(node->type() == 6)
                    {
                        MyGraphicsTextItem* rect;
                        rect = qgraphicsitem_cast<MyGraphicsTextItem*>(node);
                        if (action_state == 0)
                        {
                            rect->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
                        }
                        else
                        {
                            rect->setFlags(QGraphicsItem::ItemIsSelectable);
                        }
                        rect->setSelected(true);
                        if (zuoxiax > rect->mapToScene(rect->rect()).value(0).x())
                        {
                            zuoxiax = rect->mapToScene(rect->rect()).value(0).x();
                        }
                        if (zuoxiay > rect->mapToScene(rect->rect()).value(0).y())
                        {
                            zuoxiay = rect->mapToScene(rect->rect()).value(0).y();
                        }
                        if (youshangx < rect->mapToScene(rect->rect()).value(2).x())
                        {
                            youshangx = rect->mapToScene(rect->rect()).value(2).x();
                        }
                        if (youshangy < rect->mapToScene(rect->rect()).value(2).y())
                        {
                            youshangy = rect->mapToScene(rect->rect()).value(2).y();
                        }
                        scene->update();

                    }
                    else if(node->type() == 7)
                    {
                        MyGraphicsCurveLineItem* rect;
                        rect = qgraphicsitem_cast<MyGraphicsCurveLineItem*>(node);
                        if (action_state == 0)
                        {
                            rect->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
                        }
                        else
                        {
                            rect->setFlags(QGraphicsItem::ItemIsSelectable);
                        }
                        rect->setSelected(true);


                        if (zuoxiax > rect->getRect()[0])
                        {
                            zuoxiax = rect->getRect()[0];
                        }
                        if (zuoxiay > rect->getRect()[1])
                        {
                            zuoxiay = rect->getRect()[1];
                        }
                        if (youshangx < rect->getRect()[2])
                        {
                            youshangx = rect->getRect()[2];
                        }
                        if (youshangy < rect->getRect()[3])
                        {
                            youshangy = rect->getRect()[3];
                        }
                        scene->update();
                    }
                    else if(node->type() == 8)
                    {
                            MyGraphicsPixMapItem* rect;
                            rect = qgraphicsitem_cast<MyGraphicsPixMapItem*>(node);
                            if (action_state == 0)
                            {
                                rect->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
                            }
                            else
                            {
                                rect->setFlags(QGraphicsItem::ItemIsSelectable);
                            }
                            rect->setSelected(true);
                            if (zuoxiax > rect->mapToScene(rect->rect()).value(0).x())
                            {
                                zuoxiax = rect->mapToScene(rect->rect()).value(0).x();
                            }
                            if (zuoxiay > rect->mapToScene(rect->rect()).value(0).y())
                            {
                                zuoxiay = rect->mapToScene(rect->rect()).value(0).y();
                            }
                            if (youshangx < rect->mapToScene(rect->rect()).value(2).x())
                            {
                                youshangx = rect->mapToScene(rect->rect()).value(2).x();
                            }
                            if (youshangy < rect->mapToScene(rect->rect()).value(2).y())
                            {
                                youshangy = rect->mapToScene(rect->rect()).value(2).y();
                            }
                            scene->update();
                     }
                }
            }
        }
        int x = zuoxiax, y = youshangy , width = youshangx-zuoxiax,height = youshangy-zuoxiay;
        //qDebug() << zuoxiax << zuoxiay << youshangx << youshangy << endl;
        if (k == 1)
        {
            ui.xposition->setText(QString::number(x));
            ui.yposition->setText(QString::number(y));
            ui.xsize->setText(QString::number(width));
            ui.ysize->setText(QString::number(height));
        }
        else
        {
            ui.xposition->setText("");
            ui.yposition->setText("");
            ui.xsize->setText("");
            ui.ysize->setText("");
        }
        
        QList<int> notSelectRows;
        for(int i=0;i<ui.itemtable->rowCount();i++)
        {
            if (!rows.contains(i))
            {
                notSelectRows.append(i);
            }
        }
        for (int i : notSelectRows)
        {
            QTableWidgetItem* item1 = new QTableWidgetItem;
            item1 = ui.itemtable->item(i, 3);
            QString id = item1->text();
            QList<QGraphicsItem*> items = scene->items();
            for (QList<QGraphicsItem*>::iterator it = items.begin(); it != items.end(); it++)
            {
                QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);
                int id1 = node->data(0).value<int>();
                if (node->isVisible() && id == QString::number(id1))
                {

                        if (action_state == 0)
                        {
                            node->setSelected(false);
                        }
                        else
                        {
                            node->setSelected(false);
                            node->setFlags(NULL);
                            
                        }                      
                        scene->update();

                }
            }
        }


    });


    //璁剧疆鍙充晶鏍峰紡
    ui.widget_19->setStyleSheet(QString::fromUtf8("#widget_19{border:1px solid rgb(200,200,200)}"));
    ui.colorbuttom->setStyleSheet(QString::fromUtf8("#colorbuttom{border:1px solid rgb(200,200,200)}"));
    ui.pushButton_3->setAutoFillBackground(true);
    initConnect();
}


void mainWindow::initConnect()
{

    connect(view,&MyGraphicsView::mouseleave,this,[&](int k){
       kkkk=k;

    });


    connect(ui.draw_sanjiao, &QPushButton::clicked, this, [&]() {

        if(kkkk == 2)
        {
            action_state = 1;
            setItemMoveble(false);
        }
        else if( kkkk == 1)
        {
            ui.draw_quline->click();
            QMessageBox::information(NULL, "警告", "请先完成曲线绘制",
                                     QMessageBox::Yes , QMessageBox::Yes);
        }
        else
        {
            ui.draw_line->click();
            QMessageBox::information(NULL, "警告", "请先完成直线绘制",
                                     QMessageBox::Yes , QMessageBox::Yes);
        }

        });
    connect(ui.bianji, &QPushButton::clicked, this, [&]() {
        if(kkkk == 2)
        {
            action_state = 0;
            setItemMoveble(true);
        }
        else if( kkkk == 1)
        {
            ui.draw_quline->click();
            QMessageBox::information(NULL, "警告", "请先完成曲线绘制",
                                     QMessageBox::Yes, QMessageBox::Yes);
        }
        else
        {
            ui.draw_line->click();
            QMessageBox::information(NULL, "警告", "请先完成直线绘制",
                                     QMessageBox::Yes , QMessageBox::Yes);
        }
        });
    connect(ui.draw_yuan, &QPushButton::clicked, this, [&]() {
        if(kkkk == 2)
        {
            action_state = 3;
            setItemMoveble(false);
        }
        else if( kkkk == 1)
        {
            ui.draw_quline->click();
            QMessageBox::information(NULL, "警告", "请先完成曲线绘制",
                                     QMessageBox::Yes , QMessageBox::Yes);
        }
        else
        {
            ui.draw_line->click();
            QMessageBox::information(NULL, "警告", "请先完成直线绘制",
                                     QMessageBox::Yes, QMessageBox::Yes);
        }
        });
    connect(ui.draw_ellipse, &QPushButton::clicked, this, [&]() {
        if(kkkk == 2)
        {
            action_state = 2;
            setItemMoveble(false);
        }
        else if( kkkk == 1)
        {
            ui.draw_quline->click();
            QMessageBox::information(NULL, "警告", "请先完成曲线绘制",
                                     QMessageBox::Yes , QMessageBox::Yes);
        }
        else
        {
            ui.draw_line->click();
            QMessageBox::information(NULL, "警告", "请先完成直线绘制",
                                     QMessageBox::Yes, QMessageBox::Yes);
        }
        });

    connect(ui.draw_line, &QPushButton::clicked, this, [&]() {
        if(kkkk == 2)
        {
            action_state = 4;
            setItemMoveble(false);
        }
        else if( kkkk == 1)
        {
            ui.draw_quline->click();
            QMessageBox::information(NULL, "警告", "请先完成曲线绘制",
                                     QMessageBox::Yes , QMessageBox::Yes);
        }
        else
        {

        }
        });
    connect(ui.draw_polygon, &QPushButton::clicked, this, [&]() {
        if(kkkk == 2)
        {
            action_state = 5;
            setItemMoveble(false);
        }
        else if( kkkk == 1)
        {
            ui.draw_quline->click();
            QMessageBox::information(NULL, "警告", "请先完成曲线绘制",
                                     QMessageBox::Yes, QMessageBox::Yes);
        }
        else
        {
            ui.draw_line->click();
            QMessageBox::information(NULL, "警告", "请先完成直线绘制",
                                     QMessageBox::Yes , QMessageBox::Yes);
        }
        });
    connect(ui.draw_wenzi, &QPushButton::clicked, this, [&]() {
        if(kkkk == 2)
        {
            action_state = 6;
            setItemMoveble(false);
        }
        else if( kkkk == 1)
        {
            ui.draw_quline->click();
            QMessageBox::information(NULL, "警告", "请先完成曲线绘制",
                                     QMessageBox::Yes, QMessageBox::Yes);
        }
        else
        {
            ui.draw_line->click();
            QMessageBox::information(NULL, "警告", "请先完成直线绘制",
                                     QMessageBox::Yes, QMessageBox::Yes);
        }
        });
    connect(ui.draw_quline, &QPushButton::clicked, this, [&]() {
        if(kkkk == 2)
        {
            action_state = 7;
            setItemMoveble(false);
        }
        else if( kkkk == 1)
        {

        }
        else
        {
            ui.draw_line->click();
            QMessageBox::information(NULL, "警告", "请先完成直线绘制",
                                     QMessageBox::Yes , QMessageBox::Yes);
        }
        });



    connect(ui.draw_pixmap, &QPushButton::clicked, this, [&]() {
        if(kkkk == 2)
        {
            action_state = 8;
            MyGraphicsPixMapItem *item = new MyGraphicsPixMapItem();
            QFileDialog dialog(this);
            QStringList fileNames;
            dialog.setNameFilter("Images (*.png *.xpm *.jpg)");
            if (dialog.exec()) {
                fileNames = dialog.selectedFiles();
                QString fileName = fileNames[0];
                if (QImageReader::imageFormat(fileName) == "") {
                    QMessageBox::warning(this, "Error", "Selected file is not an image file.");
                } else {
                    QPixmap pixmap(fileName);
                    item->setPixmap(pixmap);
                    int w,h;
                    w=item->boundingRect().width();
                    h = item->boundingRect().height();
                    item->setPos(-w/2,-h/2);
                    item->setData(0,view->item_id);
                    QString str = QString::number(view->row + 1);
                    item->name = u8"图片" + str;
                    scene->addItem(item);
                    emit view->addItem(view->row,item);
                }
            }





            setItemMoveble(false);
        }
        else if( kkkk == 1)
        {
            ui.draw_quline->click();
            QMessageBox::information(NULL, "警告", "请先完成曲线绘制",
                                     QMessageBox::Yes, QMessageBox::Yes);
        }
        else
        {
            ui.draw_line->click();
            QMessageBox::information(NULL, "警告", "请先完成直线绘制",
                                     QMessageBox::Yes , QMessageBox::Yes);
        }
        });
    connect(scene,&QGraphicsScene::selectionChanged, [=]() {
        QList<QGraphicsItem*> items = scene->selectedItems();
        QList<int> ids;
        QList<int> notselectids;
        for (QList<QGraphicsItem*>::iterator it = items.begin(); it != items.end(); it++)
        {
            QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);
            int id1 = node->data(0).value<int>();
            ids.append(id1);

        }
        for (int i = 0;i<ui.itemtable->rowCount();i++)
        {
            QTableWidgetItem* item1 = new QTableWidgetItem;
            item1 = ui.itemtable->item(i, 3);
            QString tid = item1->text();
            int k = 0;
            for (int id : ids)
            {  
                if (QString::number(id) == tid)
                {
                    //ui.itemtable->setCurrentCell(i, QItemSelectionModel::Select);
                    ui.itemtable->blockSignals(true);
                    ui.itemtable->setItemSelected(ui.itemtable->item(i, 0), true);
                    ui.itemtable->setItemSelected(ui.itemtable->item(i, 1), true);
                    ui.itemtable->blockSignals(false);
                    ui.itemtable->setItemSelected(ui.itemtable->item(i, 2), true);

                    //ui.itemtable->setItemSelected(ui.itemtable->item(i, 3), true);
                    k = 1;
                    break;
                }
            }
            if (k == 0)
                notselectids.append(i);
        }
        for (int i : notselectids)
        {
            ui.itemtable->blockSignals(true);
            ui.itemtable->setItemSelected(ui.itemtable->item(i, 0), false);
            ui.itemtable->setItemSelected(ui.itemtable->item(i, 1), false);
            ui.itemtable->blockSignals(false);
            ui.itemtable->setItemSelected(ui.itemtable->item(i, 2), false);

        }      
        });



    

    connect(scene, &QGraphicsScene::selectionChanged, [=]() {
        

        QList<QGraphicsItem*> items = scene->selectedItems();
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
            else if(node->type() == 3)
            {
                MyGraphicsCircleItem * item = qgraphicsitem_cast<MyGraphicsCircleItem *>(node);

                if (x > item->mapRectToScene(item->rect()).x())
                {
                    x = item->mapRectToScene(item->rect()).x();

                }
                if (y > item->mapRectToScene(item->rect()).y())
                {
                    y = item->mapRectToScene(item->rect()).y();
                }
            }
            else if(node->type() == 4)
            {
                MyGraphicsLineItem * item = qgraphicsitem_cast<MyGraphicsLineItem *>(node);
                if(x > item->getRect().x())
                {
                    x = item->getRect().x();
                }
                if(y > item->getRect().y())
                {
                    y = item->getRect().y();
                }
            }

            else if(node->type() == 5)
            {
                MyGraphicsPolygonItem *item = qgraphicsitem_cast<MyGraphicsPolygonItem *>(node);
                if(x > item->getRect().x())
                {
                    x = item->getRect().x();
                }
                if(y > item->getRect().y())
                {
                    y = item->getRect().y();
                }
            }
            else if(node->type() == 6)
            {
                MyGraphicsTextItem * item = qgraphicsitem_cast<MyGraphicsTextItem *>(node);
                if (x > item->mapRectToScene(item->rect()).x())
                {
                    x = item->mapRectToScene(item->rect()).x();

                }
                if (y > item->mapRectToScene(item->rect()).y())
                {
                    y = item->mapRectToScene(item->rect()).y();
                }

            }
            else if(node->type() == 7)
            {
                MyGraphicsCurveLineItem *item = qgraphicsitem_cast<MyGraphicsCurveLineItem *>(node);
                if(x> item->getRect()[0])
                {
                    x = item->getRect()[0];
                }
                if(y > item->getRect()[1])
                {
                    y = item->getRect()[1];
                }
            }
            else if(node->type() == 8)
            {
                MyGraphicsPixMapItem * rect = qgraphicsitem_cast<MyGraphicsPixMapItem *>(node);

                if (x > rect->mapRectToScene(rect->rect()).x())
                {
                    x = rect->mapRectToScene(rect->rect()).x();

                }
                if (y > rect->mapRectToScene(rect->rect()).y())
                {
                    y = rect->mapRectToScene(rect->rect()).y();
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
            else if(node->type() == 3)
            {
                MyGraphicsCircleItem * item = qgraphicsitem_cast<MyGraphicsCircleItem*>(node);
                if (w < item->mapToScene(item->rect()).value(1).x() - x)
                {
                    w = item->mapToScene(item->rect()).value(1).x() - x;
                }
                if (h < item->mapToScene(item->rect()).value(2).y() - y)
                {
                    h = item->mapToScene(item->rect()).value(2).y() - y;
                }
            }
            else if(node->type() == 4)
            {
                MyGraphicsLineItem *item = qgraphicsitem_cast<MyGraphicsLineItem *>(node);
                if(w<item->getRect().x()+item->getRect().width() - x)
                {
                    w = item->getRect().x()+item->getRect().width() - x;
                }
                if(h<item->getRect().y()+item->getRect().height() - y)
                {
                    h = item->getRect().y()+item->getRect().height() - y;
                }
            }
            else if(node->type() == 5)
            {
                MyGraphicsPolygonItem *item = qgraphicsitem_cast<MyGraphicsPolygonItem *>(node);
                if(w<item->getRect().x()+item->getRect().width() - x)
                {
                    w = item->getRect().x()+item->getRect().width() - x;
                }
                if(h<item->getRect().y()+item->getRect().height() - y)
                {
                    h = item->getRect().y()+item->getRect().height() - y;
                }
            }
            else if(node->type() == 6)
            {
                MyGraphicsTextItem * item = qgraphicsitem_cast<MyGraphicsTextItem *>(node);
                if (w < item->mapToScene(item->rect()).value(1).x() - x)
                {
                    w = item->mapToScene(item->rect()).value(1).x() - x;

                }
                if (h < item->mapToScene(item->rect()).value(2).y() - y)
                {
                    h = item->mapToScene(item->rect()).value(2).y() - y;
                }
            }
            else if(node->type() == 7)
            {
                MyGraphicsCurveLineItem *item = qgraphicsitem_cast<MyGraphicsCurveLineItem *>(node);
                if(w<item->getRect()[2] - x)
                {
                    w = item->getRect()[2] - x;
                }
                if(h<item->getRect()[3] - y)
                {
                    h = item->getRect()[3]-y;
                }
            }
            else if(node->type() == 8)
            {
                MyGraphicsPixMapItem * item = qgraphicsitem_cast<MyGraphicsPixMapItem*>(node);
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
        //qDebug()<<x<<y<<w<<h<<endl;
        view->itemad->setPos(x - 10 / view->itemad->scale, y - 10 / view->itemad->scale);
        view->itemad->setRect(0, 0, w + 20 / view->itemad->scale, h + 20 / view->itemad->scale);
        view->itemad->setRec(QRectF(0, 0, w , h ));
        view->itemad->setVisible(true);
        scene->update();
        });
    
    //connect(ui.markButton, &QPushButton::clicked, this, &mainWindow::printItem);
    
}

void mainWindow::setItemMoveble(bool moveble)
{

    QList<QGraphicsItem*> items = scene->items();
    for (QList<QGraphicsItem*>::iterator it = items.begin(); it != items.end(); it++)
    {
        QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);
        if (node->type() == 0)
            continue;
        if(moveble)
            //node->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
            ;

        else
            node->setFlags(NULL);

    }
}

mainWindow::~mainWindow()
{}




bool mainWindow::setLayer(int i, PrintParams p)
{
    try
    {
        print_layer[i].processnums = p.processnums;
        print_layer[i].speed = p.speed;
        print_layer[i].power = p.power;
        print_layer[i].frequence = p.frequence;
        print_layer[i].maikuan = p.maikuan;
        print_layer[i].openDelay = p.openDelay;
        print_layer[i].closeDelay = p.closeDelay;
        print_layer[i].endDelay = p.endDelay;
        print_layer[i].turnDelay = p.turnDelay;
        return true;
    }
    catch (const std::exception&)
    {
        return false;
    }
}

bool mainWindow::printItem()
{
    QList<QGraphicsItem*> items = scene->items();
    cout << CUIsOpen() << endl;
    CUOpenDevice();
    cout << CUIsOpen() << endl;

    CULaserOut(ST_MO, 1, 3);
    for (QList<QGraphicsItem*>::iterator it = items.begin(); it != items.end(); it++)
    {
        QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);
        int id = node->data(0).value<int>();
        if (node->type() == 1 && id>0)
        {
            MyGraphicsRecItem* rect = qgraphicsitem_cast<MyGraphicsRecItem*>(*it);
            LightDraw(rect->ViewPath(), node, 1);
        }
       
        
    }
    CULaserOut(ST_MO, 0, 3);
    CUWriteBuf();

    CUSetNullDelayUs(50, 3);
    CULaserOut(6, 0, 3 );//AP
    CULaserOut(5, 0, 3);//MO
    CUBufFill(); //实际打印
    return true;
}

bool mainWindow::LightDraw(QPainterPath path,QGraphicsItem *item,int type)
{
    switch (type)
    {
    case 1:
        MyGraphicsRecItem * rect = qgraphicsitem_cast<MyGraphicsRecItem*>(item);
        
        unsigned int speed = print_layer[rect->printLayer].speed/100*65536;//转化
        CUSchSetSpeed(speed, 3);


        unsigned int frequnce = print_layer[rect->printLayer].frequence * 1000;
        CUSetPWM(PWM2, frequnce, 3, false);
        CUSetNullDelayUs(20000, 3);
        unsigned int power = print_layer[rect->printLayer].power * 2.56; //0-255之间代表0-100
        CULaserOut(ST_DATA, power, 3);
        CUSetNullDelayUs(100, 3);
        CULaserOut(ST_LATCH, 1, 3);
        CUSetNullDelayUs(5000, 3);
        CULaserOut(ST_LATCH, 0, 3);
        unsigned int openDealy = print_layer[rect->printLayer].openDelay;
        unsigned int closeDealy = print_layer[rect->printLayer].closeDelay;
        unsigned int endDealy = print_layer[rect->printLayer].endDelay;
        unsigned int turnDealy = print_layer[rect->printLayer].turnDelay;
        //CUSetOpenDelayUs(openDealy,3);//2023-1-12
        //CUSetCloseDelayUs(closeDealy, 3);//2023-1-13
        //CUSetTuneDelayUs(turnDealy, 3);//2023-1-13
       // CUSetNullDelayUs(5000, 3);
        //结束延时没找到啊

        //开始画
        //QPolygonF polu = path.toFillPolygon();

        for (int i = 0; i < path.elementCount(); i++)
        {
            QPainterPath::Element element = path.elementAt(i);
            QPointF po = element;
            QPoint printpo = view2print(po);
            qDebug() << printpo << endl;
            if (element.isMoveTo())
            {
             //   CUSchJmpLinear(printpo.x(), printpo.y(), 3);
            }
            else if (element.isLineTo())
            {
                CUSchOutLinear(printpo.x(), printpo.y(), 3);
            }
        }
        break;
    }
    return true;

}

QPoint mainWindow::view2print(QPointF position)
{
    double dpiX = QApplication::primaryScreen()->physicalDotsPerInchX();
    double dpiY = QApplication::primaryScreen()->physicalDotsPerInchY();
    auto tx = (dpiX * 10) / 254;
    auto ty = (dpiY * 10) / 254;

    QPointF p(position.x() / tx, position.y() / ty);

    int x = p.x() * 1000 + 0.5;
    int y = p.y() * 1000 + 0.5;
    double xx = double(x) / 1000;
    double yy = double(y) / 1000;
    QPointF pf((xx+50.000)*655.36, (yy+50.000)*655.36);
    QPoint pp = pf.toPoint();
    return pp;
}
