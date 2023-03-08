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
int action_state;
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


    //QPen pen;   // 瀹氫箟涓?涓敾绗旓紝璁剧疆鐢荤瑪棰滆壊鍜屽搴?
    //pen.setColor(QColor(0, 160, 230));
    //pen.setWidth(10);
    scene->setBackgroundBrush(Qt::white);
    scene->setSceneRect(-5000, -5000, 10000, 10000);
    view->setAlignment(Qt::AlignCenter);
    ui.dock4->setWidget(view);

    view->centerOn(QPointF(0, 0));
    view->scale(1, -1);
    //鐢婚《閮ㄥ埢搴︾嚎
    


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

    //璁剧疆鍙充晶琛ㄦ牸
    //ui.colortable->horizontalHeader()->setResizeMode(QHeaderView::Stretch);

    ui.colortable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QSize size = ui.dock3->size();
    
    ui.dock_leftKedu->setVisible(false);
    ui.dock_topKedu->setVisible(false);
    //璁剧疆琛ㄦ牸
    ui.itemtable->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);//楂樺害鍥哄畾
    ui.itemtable->verticalHeader()->setDefaultSectionSize(20);
    //ui.itemtable->setFrameShape(QFrame::NoFrame);
    ui.itemtable->setShowGrid(false);
    ui.itemtable->verticalHeader()->setVisible(false);
    ui.itemtable->setEditTriggers(QAbstractItemView::NoEditTriggers);//涓嶅彲缂栬緫
    ui.itemtable->setSelectionBehavior(QAbstractItemView::SelectRows);//璁剧疆閫変腑涓?琛?
    ui.itemtable->setColumnHidden(3, true); // 闅愯棌绗笁鍒?
    ui.itemtable->setSelectionMode(QAbstractItemView::ExtendedSelection);




  //  RulerWidget* leftRuler = new RulerWidget(Qt::Vertical);
  //  ui.dock_leftKedu->setWidget(leftRuler);
//leftRuler->setSlidingLinePos(27);
    connect(view->verticalScrollBar(), &QScrollBar::valueChanged, [=]
        {
           // leftRuler->setOffset(-view->mapToScene(0, 0).y());
            view->topkedu->setPos(0, view->mapToScene(0, 0).y() );
            view->myGrid->setshuzhi_Offset(view->mapToScene(0, 0).y());
            view->mainarea->setOffset(view->mapToScene(0, 0).y());
            view->leftkedu->setOffset(view->mapToScene(0, 0).y());
            /*qDebug() << view->mapToScene(0, 0).y() << "y" << endl;
            qDebug() << view->size() << endl;*/
            //view->myGrid->setrect(QRectF(view->mapToScene(0, 0).x(), view->mapToScene(0, 0).y(), view->size().width(), view->size().height()));
            //view->myGrid->setrect(view->sceneRect());
           // view->myGrid->setrect(QRectF(-385, 312, 794, 648));
            scene->update();
        });

    connect(view->verticalScrollBar(), &QScrollBar::rangeChanged, [=]
        {
           // leftRuler->setOffset(-view->mapToScene(0, 0).y());
            view->topkedu->setPos(0, view->mapToScene(0, 0).y());
            view->myGrid->setshuzhi_Offset(view->mapToScene(0, 0).y());
            view->mainarea->setOffset(view->mapToScene(0, 0).y());
           // qDebug() << view->mapToScene(0, 0).y() << "y" << endl;
           // view->leftkedu->setOffset(view->mapToScene(0, 0).y());
           // qDebug() << view->size() << endl;
            view->myGrid->setrect(view->sceneRect());
            
            scene->update();
        });
    //ui.dock_leftKedu->setVisible(false);

    //connect(view, &MyGraphicsView::mouseMovePos, [topRuler, leftRuler](QPointF pos)
    //    {
    //        topRuler->setSlidingLinePos(pos.x());
    //        leftRuler->setSlidingLinePos(pos.y()+27);
    //    });

    //缂╂斁鐨勪俊鍙峰拰妲?
    connect(view, &MyGraphicsView::ScaleChanged, [=](double scale)
        {
           // topRuler->setscale(scale);
           // leftRuler->setscale(scale);
            view->topkedu->setscales(scale);
            view->myGrid->setscales(scale);
            view->mainarea->setscales(scale);
            view->leftkedu->setscales(scale);
        });
    
    //娣诲姞琛ㄦ牸淇℃伅鐨勪俊鍙峰拰妲?
    connect(view, &MyGraphicsView::addItem,ui.itemtable, [&](int row,QGraphicsItem * item) {
        int type = item->type();
        
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
        ui.itemtable->setRowCount(row + 1);
        
        ui.itemtable->setItem(row, 0, item0);
        ui.itemtable->setItem(row, 1, item1);
        ui.itemtable->setItem(row, 2, item2);
        ui.itemtable->setItem(row, 3, item3);
        ui.itemtable->update();
        });


    //鍙屽嚮琛ㄦ牸淇敼鍚嶇О
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
                    break;
                }
                
            }
        }

        });



    //鍗曞嚮鏌愯鑾峰彇鍥惧厓淇℃伅
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
                    if (node->type() == 1)
                    {
                        MyGraphicsRecItem* rect;
                        rect = qgraphicsitem_cast<MyGraphicsRecItem*>(node);
                        if (action_state == 0)
                        {
                            rect->setSelected(false);
                        }
                        else
                        {
                            rect->setSelected(false);
                            rect->setFlags(NULL);
                            
                        }                      
                        scene->update();
                    }
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
    connect(ui.draw_sanjiao, &QPushButton::clicked, this, [&]() {
        action_state = 1;
        setItemMoveble(false);
        });
    connect(ui.bianji, &QPushButton::clicked, this, [&]() {
        action_state = 0;
        setItemMoveble(true);
        });
    connect(ui.draw_yuan, &QPushButton::clicked, this, [&]() {
        action_state = 3;
        setItemMoveble(false);
        });
    connect(ui.draw_ellipse, &QPushButton::clicked, this, [&]() {
        action_state = 2;
        setItemMoveble(false);
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

    
    connect(ui.markButton, &QPushButton::clicked, this, &mainWindow::printItem);
    
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
            node->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
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
    for (QList<QGraphicsItem*>::iterator it = items.begin(); it != items.end(); it++)
    {
        QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);
        int id = node->data(0).value<int>();
        if (node->type() == 1 && id>0)
        {
            MyGraphicsRecItem* rect = qgraphicsitem_cast<MyGraphicsRecItem*>(*it);
            qDebug() << rect->ViewPath() << endl;
            
        }
       

    }
    return true;
}