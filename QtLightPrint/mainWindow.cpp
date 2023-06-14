#include "mainWindow.h"
#include<qdebug.h>
#include"GraphicsItems/mylabel.h"
#include"GraphicsItems/MyGraphicsScene.h"
#include"GraphicsItems/MyGraphicsView.h"
#include<qgraphicsitem.h>
#include<qscrollbar.h>
#include"GraphicsItems/MygraphicsLinePre.h"
#include<qlist.h>
#include<qinputdialog.h>
#include "GraphicsItems/MyKedu.h"
#include<qmessagebox.h>
#include<qfiledialog.h>
#include"FileHandel/qlptfilehandle.h"
#include"FileHandel/pltfilehandle.h"
#include"ItemHandle/itemalignhandle.h"
#include<qimagereader.h>
#include <qxml.h>
#include <QDomDocument>
#include<qbuffer.h>
#include"Widgets/bottomdockwidget.h"
#include"libsHeaders/ZXingWriter.h"
#include"GraphicsItems/mygraphicscodeitem.h"
#include"qtranslator.h"
#include<qfontdatabase.h>
#include"Widgets/advancedwidget.h"
#include"GraphicsItems/mygraphicsgroupitem.h"
#include"ItemHandle/itemsizehandle.h"
#include"ItemHandle/itemprinthandle.h"
#include"ItemAdjust.h"
using namespace std;
int action_state;
int k;
mainWindow::mainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    BottomDockWidget* bottom_dock = new BottomDockWidget;


    qlfilehandler = new qlptfileHandle();
    pltfilehanler = new pltFileHandle();
    itemsizehandler = new ItemSizeHandle();
    itemalignhandler = new ItemAlignHandle();
    itemprinthandler = new ItemPrintHandle();
    //下4行代码用于隐藏底部dockWidget的标题栏
    QWidget* BTitleBar = bottom_dock->titleBarWidget();
    QWidget* BEmptyWidget = new QWidget();
    bottom_dock->setTitleBarWidget(BEmptyWidget);
    delete BTitleBar;
    QWidget* p = takeCentralWidget();
    if (p)
        delete p;
    setDockNestingEnabled(true);


    //添加底部dock
    bottom_dock->setParent(this);
    bottom_dock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    this->addDockWidget(Qt::BottomDockWidgetArea,bottom_dock);
    
    ui.itemtable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui.itemtable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    
    //布局dock界面
    splitDockWidget(ui.dock1, ui.dock7, Qt::Horizontal);
    splitDockWidget(ui.dock1, ui.dock2, Qt::Vertical);
    splitDockWidget(ui.dock7, bottom_dock, Qt::Vertical);
    splitDockWidget(ui.dock7, ui.dock_file, Qt::Horizontal);
    splitDockWidget(ui.dock_file, ui.dock4, Qt::Vertical);
    

    //去除头
    QWidget* lTitleBar = ui.dock4->titleBarWidget();
    QWidget* lEmptyWidget = new QWidget();
    ui.dock4->setTitleBarWidget(lEmptyWidget);
    delete lTitleBar;

    QWidget* lTitleBar1 = ui.dock7->titleBarWidget();
    QWidget* lEmptyWidget1 = new QWidget();
    ui.dock7->setTitleBarWidget(lEmptyWidget1);
    delete lTitleBar1;



    lTitleBar = ui.dock_file->titleBarWidget();
    lEmptyWidget = new QWidget();

    ui.dock_file->setTitleBarWidget(lEmptyWidget);

    QLabel *label = new QLabel("| ");
    label->setStyleSheet("color: black; font-size: 14pt; font-weight: bold;");
    ui.dockWidget_2->setTitleBarWidget(label);
    ui.dockWidget_2->setWidget(ui.widget_31);


    QLabel *label2 = new QLabel("| ");
    label2->setStyleSheet("color: black; font-size: 14pt; font-weight: bold;");
    ui.dockWidget_3->setTitleBarWidget(label2);
    ui.dockWidget_3->setWidget(ui.widget_32);

    QLabel *label3 = new QLabel("| ");
    label3->setStyleSheet("color: black; font-size: 14pt; font-weight: bold;");
    ui.dockWidget_4->setTitleBarWidget(label3);
    ui.dockWidget_4->setWidget(ui.widget_33);


    //设置图片
    ui.bianji->setIcon(QIcon(":/res/Select.png"));
    ui.draw_line->setIcon(QIcon(":/res/Line.png"));
    //ui.draw_quline->setIcon(QIcon(":/res/Line.png"));
    ui.draw_yuan->setIcon(QIcon(":/res/Circle.png"));
    ui.draw_wenzi->setIcon(QIcon(":/res/Font.png"));
    ui.draw_sanjiao->setIcon(QIcon(":/res/Rectangle.png"));
    ui.draw_polygon->setIcon(QIcon(":/res/RegularPolygon.png"));

    //设置铺满dock
    ui.dock1->setWidget(ui.itemtable);
    ui.dock2->setWidget(ui.scrollArea_2);
    ui.dock7->setWidget(ui.widget_5);
    ui.dock_file->setWidget(ui.widget_24);





    connect(ui.leftmove,&QPushButton::clicked,[=](){

        ui.scrollArea_3->horizontalScrollBar()->setValue(ui.scrollArea_3->horizontalScrollBar()->value()-10);
    });
    connect(ui.rightmove,&QPushButton::clicked,[=](){

        ui.scrollArea_3->horizontalScrollBar()->setValue(ui.scrollArea_3->horizontalScrollBar()->value()+10);
    });



    connect(bottom_dock->btnMark, &QPushButton::clicked, this, [=](){
        itemprinthandler->printItem(this);
    });
    connect(bottom_dock->btnRed,&QPushButton::clicked, this, [=](){
        itemprinthandler->printRedItem(this);
    });

    //检测可用字体
    ui.comboBox->clear();
    QStringList fontnames;
    QFontDatabase database;
    foreach (const QString &family, database.families())
    {
         fontnames.append(family);
    }
    ui.comboBox->addItems(fontnames);

    //添加默认文件 及名字。
    creatnewfile();

    ui.widget_30->setVisible(false);
    ui.widget_25->setVisible(false);
    ui.widget_26->setVisible(false);


    dockConnectInit();
    initPenNumberConnect();
    initDrawConnect();
    initItemtableConnect();
    initFileconnect();
    //设置图元表
    ui.itemtable->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);//固定大小
    ui.itemtable->verticalHeader()->setDefaultSectionSize(20);
    ui.itemtable->setShowGrid(false);
    ui.itemtable->verticalHeader()->setVisible(false);
    ui.itemtable->setEditTriggers(QAbstractItemView::NoEditTriggers);//不可编辑
    ui.itemtable->setSelectionBehavior(QAbstractItemView::SelectRows);//按行选择
    ui.itemtable->setColumnHidden(3, true); // 隐藏第四列。
    ui.itemtable->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui.scrollArea_3->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui.scrollArea_3->verticalScrollBar()->hide();



    //设置笔号的背景颜色
    ui.widget_19->setStyleSheet(QString::fromUtf8("#widget_19{border:1px solid rgb(200,200,200)}"));
    ui.colorbuttom->setStyleSheet(QString::fromUtf8("#colorbuttom{border:1px solid rgb(200,200,200)}"));
    ui.pushButton_3->setAutoFillBackground(true);
    ui.pushButton_4->setAutoFillBackground(true);
    ui.pushButton_6->setAutoFillBackground(true);
    ui.pushButton_7->setAutoFillBackground(true);
    ui.pushButton_8->setAutoFillBackground(true);
    ui.pushButton_9->setAutoFillBackground(true);
    ui.pushButton_10->setAutoFillBackground(true);
    ui.pushButton_11->setAutoFillBackground(true);
    QList<QGraphicsItem *> l;
    present_items.append(l);
    //设置笔画表
    setColortable();
}
template<typename T> QPainterPath mainWindow::getpath(QGraphicsItem* node,QPainterPath &path)
{
    T *item = qgraphicsitem_cast<T *>(node);
    for (int i = 0; i < item->ViewPath(1).elementCount(); i++)
    {
        QPainterPath::Element element = item->ViewPath(1).elementAt(i);
        QPointF po = element;
        if (element.isMoveTo())
        {
            path.moveTo(po);
        }
        else if (element.isLineTo())
        {
            path.lineTo(po);
        }
    }
    return path;
}


QList<QGraphicsItem*> mainWindow::copyall(QList<QGraphicsItem*> itemss)
{
    QList<QGraphicsItem*> l ;
    for (QList<QGraphicsItem*>::iterator it = itemss.begin(); it != itemss.end(); it++)
    {

        QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);
        if(node->data(0).toInt()>0)
        {
            if(node->type()==1)
            {
                MyGraphicsRecItem *item1 = qgraphicsitem_cast<MyGraphicsRecItem*>(node);
                MyGraphicsRecItem *item2 = new MyGraphicsRecItem();
                item2->setPos(item1->pos());
                item2->setRect(item1->rect());
                item2->name = item1->name;
                item2->set_brush(item1->angle,item1->space);
                item2->setData(0,item1->data(0).toInt());
                item2->setData(5,item1->data(5).toInt());
                l.append(item2);
            }
            else if(node->type() == 2)
            {
                MyGraphicsEllipseItem *item1 = qgraphicsitem_cast<MyGraphicsEllipseItem*>(node);
                MyGraphicsEllipseItem *item2 = new MyGraphicsEllipseItem();
                //
                item2->setPos(item1->pos());
                item2->setRect(item1->rect());
                item2->name = item1->name;
                item2->set_brush(item1->angle,item1->space);
                item2->setData(0,item1->data(0).toInt());
                item2->setData(5,item1->data(5).toInt());
                l.append(item2);
            }
            else if(node->type() == 3)
            {
                MyGraphicsCircleItem *item1 = qgraphicsitem_cast<MyGraphicsCircleItem*>(node);
                MyGraphicsCircleItem *item2 = new MyGraphicsCircleItem();
                //
                item2->setPos(item1->pos());
                item2->setRect(item1->rect());
                item2->name = item1->name;
                item2->set_brush(item1->angle,item1->space);
                item2->setData(0,item1->data(0).toInt());
                item2->setData(5,item1->data(5).toInt());
                l.append(item2);
            }
            else if(node->type() == 4)
            {
                MyGraphicsLineItem *item1 = qgraphicsitem_cast<MyGraphicsLineItem*>(node);
                MyGraphicsLineItem *item2 = new MyGraphicsLineItem();
                item2->setPath(item1->path());
                item2->setPos(item1->pos());
                item2->set_brush(item1->angle,item1->space);

                item2->name = item1->name;
                item2->setData(0,item1->data(0).toInt());
                item2->setData(5,item1->data(5).toInt());
                l.append(item2);
            }
            else if(node->type() == 5)
            {
                MyGraphicsPolygonItem *item1 = qgraphicsitem_cast<MyGraphicsPolygonItem*>(node);
                MyGraphicsPolygonItem *item2 = new MyGraphicsPolygonItem();
                //
                item2->setPos(item1->pos());
                item2->setRect(item1->rect());
                item2->setPath(item1->path);
                item2->name = item1->name;
                item2->set_brush(item1->angle,item1->space);
                item2->setData(0,item1->data(0).toInt());
                item2->setData(5,item1->data(5).toInt());
                l.append(item2);
            }
            else if(node->type() == 6)
            {
                MyGraphicsTextItem *item1 = qgraphicsitem_cast<MyGraphicsTextItem*>(node);
                MyGraphicsTextItem *item2 = new MyGraphicsTextItem();
                item2->setPos(item1->pos());
                item2->setRect(item1->rect());
                item2->setPath(item1->path);
                item2->name = item1->name;
                item2->set_brush(item1->angle,item1->space);
                item2->setData(0,item1->data(0).toInt());
                item2->setData(5,item1->data(5).toInt());
                l.append(item2);
            }
            else if(node->type() == 7)
            {
                MyGraphicsCurveLineItem *item1 = qgraphicsitem_cast<MyGraphicsCurveLineItem*>(node);
                MyGraphicsCurveLineItem *item2 = new MyGraphicsCurveLineItem();
                item2->setPos(item1->pos());
                item2->setPath(item1->path());
                item2->name = item1->name;
                item2->setData(0,item1->data(0).toInt());
                item2->setData(5,item1->data(5).toInt());
                l.append(item2);
            }
            else if(node->type() == 8)
            {
                MyGraphicsPixMapItem *item1 = qgraphicsitem_cast<MyGraphicsPixMapItem*>(node);
                MyGraphicsPixMapItem *item2 = new MyGraphicsPixMapItem();
                item2->name = item1->name;
                item2->setPos(item1->pos());
                item2->setRectF(item1->rectf);
                item2->setPixmap(item1->pixmap());
                item2->setData(0,item1->data(0).toInt());
                item2->setData(5,item1->data(5).toInt());
                l.append(item2);
            }
            else if(node->type() == 9)
            {
                MyGraphicsCodeItem *item1 = qgraphicsitem_cast<MyGraphicsCodeItem*>(node);
                MyGraphicsCodeItem *item2 = new MyGraphicsCodeItem();
                item2->setPos(item1->pos());
                item2->setRect(item1->rect());
                item2->path = (item1->path);
                item2->set_brush(item1->angle,item1->space);
                item2->name = item1->name;
                item2->setData(0,item1->data(0).toInt());
                item2->setData(5,item1->data(5).toInt());
                l.append(item2);
            }
            else if(node->type() == 10)
            {
                MyGraphicsGroupItem *item3 = qgraphicsitem_cast<MyGraphicsGroupItem*>(node);
                QList<QGraphicsItem*> childs;
                MyGraphicsGroupItem *item2 = new MyGraphicsGroupItem(childs);
                item2->setPos(item3->pos());
                item2->name = item3->name;
                item2->setData(0,item3->data(0).toInt());
                item2->setData(5,item3->data(5).toInt());
                l.append(item2);
            }
        }
    }
    return l;
}

void mainWindow::dockConnectInit()
{
    connect(ui.groupbtn,&QPushButton::clicked,this,[=](){
        qDebug()<<" 群组"<<endl;
        QList<QGraphicsItem*> selectitems = scene->selectedItems();
        for(QGraphicsItem* item:selectitems)
        {
            if(item->data(15).toInt()==1)
            {
                selectitems.removeOne(item);
            }
        }
        if(selectitems.length() <= 1)
            return;
        MyGraphicsGroupItem *group = new MyGraphicsGroupItem(selectitems);
        QList<QGraphicsItem*> items = group->childItems();

        scene->addItem(group);
        group->setData(0, view->item_id);
        for(int i=0;i<items.length();i++)
        {
            items[i]->setData(5,view->item_id);
            emit view->removeItem(items[i]->data(0).toInt());
        }
        QList<QGraphicsItem*> jjjj = scene->items();
        QString str = QString::number(view->row + 1);
        group->name = tr("群组") + str;
        update();
        emit view->addItem(view->row,group);
        emit view->sceneChange();
        group->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
        group->setSelected(true);
        view->row++;
        view->item_id++;
    });



    connect(ui.deletegroupbtn,&QPushButton::clicked,this,[=](){
        qDebug()<<" 分群"<<endl;
        QList<QGraphicsItem*> selectitem = scene->selectedItems();
        if(selectitem.length() == 1)
        {
            if(selectitem[0]->type() == 10)
            {
                MyGraphicsGroupItem *group = new MyGraphicsGroupItem(qgraphicsitem_cast<MyGraphicsGroupItem*>(selectitem[0])->childItems());
                QList<QGraphicsItem*> items = group->childItems();
                qgraphicsitem_cast<MyGraphicsGroupItem*>(selectitem[0])->set_brush(0,0);
                emit view->removeItem(selectitem[0]->data(0).toInt());
                scene->removeItem(selectitem[0]);
                for(int i=0;i<items.length();i++)
                {
                    scene->addItem(items[i]);
                    emit view->addItem(view->row,items[i]);
                    view->row++;
                }
            }
        }
    });

    connect(ui.pathbtn,&QPushButton::clicked,this,[=](){
        qDebug()<<"组合"<<endl;
        MyGraphicsLineItem *line = new MyGraphicsLineItem();
        QList<QGraphicsItem*> items = scene->selectedItems();
        for(QGraphicsItem* item:items)
        {
            if(item->data(15).toInt()==1)
            {
                items.removeOne(item);
            }
        }
        if(items.length() <= 1)
            return;
        QPainterPath path;
        for(int i=0;i<items.length();i++)
        {
            scene->removeItem(items[i]);
            emit view->removeItem(items[i]->data(0).toInt());
            if(items[i]->type() == 1)
            {
                getpath<MyGraphicsRecItem>(items[i],path);
            }
            else if(items[i]->type() == 2)
            {
                getpath<MyGraphicsEllipseItem>(items[i],path);
            }
            else if(items[i]->type() == 3)
            {
                getpath<MyGraphicsCircleItem>(items[i],path);
            }
            else if(items[i]->type() == 4)
            {
                getpath<MyGraphicsLineItem>(items[i],path);
            }
            else if(items[i]->type() == 5)
            {
                getpath<MyGraphicsPolygonItem>(items[i],path);
            }
            else if(items[i]->type() == 6)
            {
                getpath<MyGraphicsTextItem>(items[i],path);
            }
            else if(items[i]->type() == 7)
            {
                getpath<MyGraphicsCurveLineItem>(items[i],path);
            }
            else if(items[i]->type() == 9)
            {
                getpath<MyGraphicsCodeItem>(items[i],path);
            }
        }
        line->setPath(path);
        line->setPos(0,0);
        scene->addItem(line);
        line->setData(0, view->item_id);
        QString str = QString::number(view->row + 1);
        line->name = tr("组合") + str;
        update();
        emit view->addItem(view->row,line);
        view->row++;
        view->item_id++;
    });


    connect(ui.deletepathbtn,&QPushButton::clicked,this,[=](){
        qDebug()<<"分组"<<endl;

        QList<QGraphicsItem*> selectitem = scene->selectedItems();
        if(selectitem.length() == 1)
        {
            if(selectitem[0]->type() == 4)
            {
                MyGraphicsLineItem *line  = qgraphicsitem_cast<MyGraphicsLineItem*>(selectitem[0]);
                emit view->removeItem(selectitem[0]->data(0).toInt());
                scene->removeItem(selectitem[0]);
                QPainterPath path = line->path();
                int i=0;
                while(i<path.elementCount())
                {
                    QPainterPath::Element element = path.elementAt(i);
                    QPointF po = element;
                    po = po+line->pos();
                    QPainterPath p;
                    p.moveTo(po);
                    i++;
                    while(path.elementAt(i).isLineTo() && i<path.elementCount())
                    {
                        p.lineTo(path.elementAt(i)+line->pos());
                        i++;
                    }
                    MyGraphicsLineItem *l = new MyGraphicsLineItem();
                    l->setPath(p);
                    scene->addItem(l);
                    l->setData(0, view->item_id);
                    QString str = QString::number(view->row + 1);
                    l->name = tr("直线") + str;
                    update();
                    emit view->addItem(view->row,l);
                    view->row++;
                    view->item_id++;

                }
            }
        }


    });

    connect ( ui.newfilebtn, &QPushButton::clicked, this, [=](){
        creatnewfile();
    } );
    connect ( ui.savefilebtn, &QPushButton::clicked, this, [=](){
        savefile();
    });
    connect ( ui.openfilebtn, &QPushButton::clicked, this, [=](){
        openfile();
    });


    connect(ui.copybtn,&QPushButton::clicked,this,[=](){
        copyitems.clear();
        copyitems = scene->selectedItems();
    });

    connect(ui.shearbtn,&QPushButton::clicked,this,[=](){
        copyitems.clear();
        copyitems = scene->selectedItems();
        QList<QGraphicsItem*> items = scene->selectedItems();
        for(int i=0;i<items.length();i++)
        {
            scene->removeItem(items[i]);
            emit view->removeItem(items[i]->data(0).toInt());
        }
        scene->update();
    });

    connect(ui.pastebtn,&QPushButton::clicked,this,[=](){
        QList<QGraphicsItem*> itemss = copyitems;
        QList<QGraphicsItem*> items;
        while(1)
        {
            int k=0;
            for(QGraphicsItem* item:itemss)
            {

                if(item->type() == 10 && (item->data(2).toInt() == 0))
                {
                    k=1;
                    item->setData(2,1);
                    MyGraphicsGroupItem *g =qgraphicsitem_cast<MyGraphicsGroupItem*>(item);
                    for(QGraphicsItem * t:g->childItems())
                    {
                        t->setData(5,g->data(0));
                    }
                    itemss.append(g->childItems());
                }
            }
            if(k == 0)
            {
                break;
            }
        }
        for (QList<QGraphicsItem*>::iterator it = itemss.begin(); it != itemss.end(); it++)
        {
            QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);
            if(node->type()==1)
            {
                MyGraphicsRecItem *item1 = qgraphicsitem_cast<MyGraphicsRecItem*>(node);
                MyGraphicsRecItem *item2 = new MyGraphicsRecItem();
                item2->setPos(item1->pos()+QPointF(5,5));
                item2->setRect(item1->rect());
                item2->name = item1->name+tr("副本");
                item2->set_brush(item1->angle,item1->space);
                item2->setData(0,view->item_id);
                item2->setData(5,item1->data(5).toInt());
                scene->addItem(item2);
                emit view->addItem(view->row,item2);
                view->item_id++;
                view->row++;
                items.append(item2);
            }
            else if(node->type() == 2)
            {
                MyGraphicsEllipseItem *item1 = qgraphicsitem_cast<MyGraphicsEllipseItem*>(node);
                MyGraphicsEllipseItem *item2 = new MyGraphicsEllipseItem();
                //
                item2->setPos(item1->pos()+QPointF(5,5));
                item2->setRect(item1->rect());
                item2->name = item1->name+tr("副本");
                item2->set_brush(item1->angle,item1->space);
                item2->setData(0,view->item_id);
                item2->setData(5,item1->data(5).toInt());
                scene->addItem(item2);
                emit view->addItem(view->row,item2);
                view->item_id++;
                view->row++;
                items.append(item2);
            }
            else if(node->type() == 3)
            {
                MyGraphicsCircleItem *item1 = qgraphicsitem_cast<MyGraphicsCircleItem*>(node);
                MyGraphicsCircleItem *item2 = new MyGraphicsCircleItem();
                //
                item2->setPos(item1->pos()+QPointF(5,5));
                item2->setRect(item1->rect());
                item2->name = item1->name+tr("副本");
                item2->set_brush(item1->angle,item1->space);
                item2->setData(0,view->item_id);
                item2->setData(5,item1->data(5).toInt());
                scene->addItem(item2);
                emit view->addItem(view->row,item2);
                view->item_id++;
                view->row++;
                items.append(item2);
            }
            else if(node->type() == 4)
            {
                MyGraphicsLineItem *item1 = qgraphicsitem_cast<MyGraphicsLineItem*>(node);
                MyGraphicsLineItem *item2 = new MyGraphicsLineItem();
                item2->setPath(item1->path());
                item2->setPos(item1->pos()+QPointF(5,5));
                item2->set_brush(item1->angle,item1->space);
                item2->name = item1->name+tr("副本");
                item2->setData(0,view->item_id);
                item2->setData(5,item1->data(5).toInt());
                scene->addItem(item2);
                emit view->addItem(view->row,item2);
                view->item_id++;
                view->row++;
                items.append(item2);
            }
            else if(node->type() == 5)
            {
                MyGraphicsPolygonItem *item1 = qgraphicsitem_cast<MyGraphicsPolygonItem*>(node);
                MyGraphicsPolygonItem *item2 = new MyGraphicsPolygonItem();
                //
                item2->setPos(item1->pos()+QPointF(5,5));
                item2->setRect(item1->rect());
                item2->setPath(item1->path);
                item2->name = item1->name+tr("副本");
                item2->set_brush(item1->angle,item1->space);
                item2->setData(0,view->item_id);
                item2->setData(5,item1->data(5).toInt());
                scene->addItem(item2);
                emit view->addItem(view->row,item2);
                view->item_id++;
                view->row++;
                items.append(item2);
            }
            else if(node->type() == 6)
            {
                MyGraphicsTextItem *item1 = qgraphicsitem_cast<MyGraphicsTextItem*>(node);
                MyGraphicsTextItem *item2 = new MyGraphicsTextItem();
                item2->setPos(item1->pos()+QPointF(5,5));
                item2->setRect(item1->rect());
                item2->setPath(item1->path);
                item2->name = item1->name+tr("副本");
                item2->set_brush(item1->angle,item1->space);
                item2->setData(0,view->item_id);
                item2->setData(5,item1->data(5).toInt());
                scene->addItem(item2);
                emit view->addItem(view->row,item2);
                view->item_id++;
                view->row++;
                items.append(item2);
            }
            else if(node->type() == 7)
            {
                MyGraphicsCurveLineItem *item1 = qgraphicsitem_cast<MyGraphicsCurveLineItem*>(node);
                MyGraphicsCurveLineItem *item2 = new MyGraphicsCurveLineItem();
                item2->setPos(item1->pos()+QPointF(5,5));
                item2->setPath(item1->path());
                item2->name = item1->name+tr("副本");
                item2->setData(0,view->item_id);
                item2->setData(5,item1->data(5).toInt());
                scene->addItem(item2);
                emit view->addItem(view->row,item2);
                view->item_id++;
                view->row++;
                items.append(item2);
            }
            else if(node->type() == 8)
            {
                MyGraphicsPixMapItem *item1 = qgraphicsitem_cast<MyGraphicsPixMapItem*>(node);
                MyGraphicsPixMapItem *item2 = new MyGraphicsPixMapItem();
                item2->name = item1->name+tr("副本");
                item2->setPos(item1->pos()+QPointF(5,5));
                item2->setRectF(item1->rectf);
                item2->setPixmap(item1->pixmap());
                item2->setData(0,view->item_id);
                item2->setData(5,item1->data(5).toInt());
                scene->addItem(item2);
                emit view->addItem(view->row,item2);
                view->item_id++;
                view->row++;
                items.append(item2);
            }
            else if(node->type() == 9)
            {
                MyGraphicsCodeItem *item1 = qgraphicsitem_cast<MyGraphicsCodeItem*>(node);
                MyGraphicsCodeItem *item2 = new MyGraphicsCodeItem();
                item2->setPos(item1->pos()+QPointF(5,5));
                item2->setRect(item1->rect());
                item2->path = (item1->path);
                item2->set_brush(item1->angle,item1->space);
                item2->name = item1->name+tr("副本");
                item2->setData(0,view->item_id);
                item2->setData(5,item1->data(5).toInt());
                scene->addItem(item2);
                emit view->addItem(view->row,item2);
                view->item_id++;
                view->row++;
                items.append(item2);
            }
            else if(node->type() == 10)
            {
                MyGraphicsGroupItem *item3 = qgraphicsitem_cast<MyGraphicsGroupItem*>(node);
                QList<QGraphicsItem*> childs;
                MyGraphicsGroupItem *item2 = new MyGraphicsGroupItem(childs);
                item2->setPos(item3->pos());
                item2->name = item3->name+tr("副本");
                item2->setData(0,view->item_id);
                item2->setData(1,item3->data(0).toInt());
                item2->setData(5,item3->data(5).toInt());
                scene->addItem(item2);
                emit view->addItem(view->row,item2);
                view->item_id++;
                view->row++;
                items.append(item2);
            }

        }
        for(int i = 0;i<items.length();i++)
        {
            if(items[i]->data(5).toInt()!=0)
            {
                for(int j=0;j<items.length();j++)
                {
                    if(items[i]->data(5).toInt() == items[j]->data(1).toInt())
                    {
                        MyGraphicsGroupItem *g = qgraphicsitem_cast<MyGraphicsGroupItem*>(items[j]);
                        g->addToGroup(items[i]);
                    }
                }
                removeitem_notEmitChange(items[i]->data(0).toInt());
            }
        }
        update();
        for(QGraphicsItem* item:itemss)
        {

            if(item->type() == 10 )
            {
                item->setData(2,0);
            }
        }
        emit view->sceneChange();
    });


    connect(view,&MyGraphicsView::sceneChange,this,[=](){
        while(present_items.length()>present + 1)
        {
            present_items.removeAt(present+1);
        }
        QList<QGraphicsItem*> itemss = scene->items();
        QList<QGraphicsItem*> l;

        //l变了，items也变了，但是由于修改图元针对的是当前图元，所以会同时修改掉这个图元。
        l = copyall(itemss);
        present_items.append(l);
        present++;
    });

    connect(ui.revokebtn,&QPushButton::clicked,this,[=](){
        if(present>0)
            present -- ;
        else
            return;
        QList<QGraphicsItem*> visibleItems = copyall( present_items[present]);
        QList<QGraphicsItem*> deleteitems = scene->items();

        for(int i=0;i<deleteitems.length();i++)
        {
            if(deleteitems[i]->data(0).toInt()>0)
            {
                scene->removeItem(deleteitems[i]);
                removeitem_notEmitChange(deleteitems[i]->data(0).toInt());
            }
        }
        int l = visibleItems.length();
        QGraphicsItem *temp;
        for(int i=0;i<l-1;i++)
        {
            for(int j=0;j<l-i-1;j++)
            {
                if(visibleItems[j]->data(0).toInt()>visibleItems[j+1]->data(0).toInt())
                {
                    temp = visibleItems[j];
                    visibleItems[j] = visibleItems[j+1];
                    visibleItems[j+1] = temp;
                }
            }
        }
        for(int i=0;i<l;i++)
        {
            scene->addItem(visibleItems[i]);
            additem(i,visibleItems[i]);
        }
        int t=0;
        for(int i = 0;i<l;i++)
        {
            if(visibleItems[i]->data(5).toInt() != 0 )
            {
                int id = visibleItems[i]->data(5).toInt();
                for(int j=0;j<l;j++)
                {
                    if(visibleItems[j]->data(0).toInt() == id)
                    {
                        t++;
                        MyGraphicsGroupItem *g = qgraphicsitem_cast<MyGraphicsGroupItem*>(visibleItems[j]);
                        g->addToGroup(visibleItems[i]);
                        removeitem_notEmitChange(visibleItems[i]->data(0).toInt());
                    }
                }
            }
        }
        view->row = l - t;
        update();
    });


    connect(ui.restorebtn,&QPushButton::clicked,this,[=](){
        if(present<present_items.length()-1)
            present ++ ;
        else
            return;
        QList<QGraphicsItem*> visibleItems = copyall( present_items[present]);
        QList<QGraphicsItem*> deleteitems = scene->items();
        for(int i=0;i<deleteitems.length();i++)
        {
            if(deleteitems[i]->data(0).toInt()>0)
            {
                scene->removeItem(deleteitems[i]);
                removeitem_notEmitChange(deleteitems[i]->data(0).toInt());
            }

        }
        int l = visibleItems.length();
        QGraphicsItem *temp;
        for(int i=0;i<l-1;i++)
        {
            for(int j=0;j<l-i-1;j++)
            {
                if(visibleItems[j]->data(0).toInt()>visibleItems[j+1]->data(0).toInt())
                {
                    temp = visibleItems[j];
                    visibleItems[j] = visibleItems[j+1];
                    visibleItems[j+1] = temp;
                }
            }
        }
        for(int i=0;i<l;i++)
        {
            scene->addItem(visibleItems[i]);
            additem(i,visibleItems[i]);
        }
        int t=0;
        for(int i = 0;i<l;i++)
        {
            if(visibleItems[i]->data(5).toInt() != 0 )
            {
                int id = visibleItems[i]->data(5).toInt();
                for(int j=0;j<l;j++)
                {
                    if(visibleItems[j]->data(0).toInt() == id)
                    {
                        t++;
                        MyGraphicsGroupItem *g = qgraphicsitem_cast<MyGraphicsGroupItem*>(visibleItems[j]);
                        g->addToGroup(visibleItems[i]);
                        removeitem_notEmitChange(visibleItems[i]->data(0).toInt());
                    }
                }
            }
        }
        view->row = l - t;
        update();
    });

    connect(ui.verMirrorBtn,&QPushButton::clicked,this,[=](){
       qDebug()<<"水平镜像";
        QList<QGraphicsItem*> selectitems = scene->selectedItems();
        for(QGraphicsItem* item : selectitems)
        {
            if(item->type() == 4)
            {
                qgraphicsitem_cast<MyGraphicsLineItem*>(item)->rotateX();
            }
            else if(item->type() == 5)
            {
                qgraphicsitem_cast<MyGraphicsPolygonItem*>(item)->rotateX();
            }
            else if(item->type() == 6)
            {
                qgraphicsitem_cast<MyGraphicsTextItem*>(item)->rotateX();
            }
            else if(item->type() == 7)
            {
                qgraphicsitem_cast<MyGraphicsCurveLineItem*>(item)->rotateX();
            }
            else if(item->type() == 9)
            {
                qgraphicsitem_cast<MyGraphicsCodeItem*>(item)->rotateX();
            }
        }
        scene->update();
    });


    connect(ui.centerbtn,&QPushButton::clicked,this,[=](){
        qDebug()<<"中心点对齐"<<endl;
        itemalignhandler->center(this);
    });

    connect(ui.leftbtn,&QPushButton::clicked,this,[=](){
        qDebug()<<"左对齐"<<endl;
        itemalignhandler->left(this);
    });


    connect(ui.rightbtn,&QPushButton::clicked,this,[=](){
        qDebug()<<"右对齐"<<endl;
        itemalignhandler->right(this);
    });
    connect(ui.topbtn,&QPushButton::clicked,this,[=](){
        qDebug()<<"上对齐"<<endl;
        itemalignhandler->top(this);
    });

    connect(ui.buttombtn,&QPushButton::clicked,this,[=](){
        qDebug()<<"下对齐"<<endl;
        itemalignhandler->buttom(this);
    });


    connect(ui.visiblebtn,&QPushButton::clicked,this,[=](){
        qDebug()<<"显示图元";
        QList<QTableWidgetItem*> selectItems = ui.itemtable->selectedItems();
        QSet<int> rows;
        for (QTableWidgetItem* item : selectItems)
        {
            rows.insert(item->row());
        }
        QList<QGraphicsItem*> items = scene->items();
        QSet<int>::iterator iter;
        for (iter = rows.begin(); iter != rows.end(); iter++)
        {
            int row = *iter;
            QTableWidgetItem* item1 = new QTableWidgetItem;
            item1 = ui.itemtable->item(row, 3);
            int id = item1->text().toInt();
            for(QGraphicsItem* item:items)
            {
                if(item->data(0).toInt()==id)
                {
                    item->setVisible(true);
                }
            }
        }

    });

    connect(ui.notvisiblebtn,&QPushButton::clicked,this,[=](){
        qDebug()<<"隐藏图元";
        QList<QGraphicsItem*> selectitems = scene->selectedItems();
        for(QGraphicsItem* item : selectitems)
        {
            item->setVisible(false);
        }

    });

    connect(ui.horMirrorBtn,&QPushButton::clicked,this,[=](){
        qDebug()<<"垂直镜像";
        QList<QGraphicsItem*> selectitems = scene->selectedItems();
        for(QGraphicsItem* item : selectitems)
        {
            if(item->type() == 4)
            {
                qgraphicsitem_cast<MyGraphicsLineItem*>(item)->rotateY();
            }
            else if(item->type() == 5)
            {
                qgraphicsitem_cast<MyGraphicsPolygonItem*>(item)->rotateY();
            }
            else if(item->type() == 6)
            {
                qgraphicsitem_cast<MyGraphicsTextItem*>(item)->rotateY();
            }
            else if(item->type() == 7)
            {
                qgraphicsitem_cast<MyGraphicsCurveLineItem*>(item)->rotateY();
            }
            else if(item->type() == 9)
            {
                qgraphicsitem_cast<MyGraphicsCodeItem*>(item)->rotateY();
            }
        }
        scene->update();
    });


    connect(ui.originbtn,&QPushButton::clicked,this,[=](){
        ui.xposition->setText(0);
        ui.yposition->setText(0);
        emit ui.pushButton_2->clicked();
    });

    connect(ui.lockitembtn,&QPushButton::clicked,this,[=](){
        QList<QGraphicsItem*> selectitems = scene->selectedItems();
        for(QGraphicsItem* item : selectitems)
        {
            item->setData(15,1);
        }

        scene->update();
    });

    connect(ui.unlockitembtn,&QPushButton::clicked,this,[=](){
        QList<QGraphicsItem*> selectitems = scene->selectedItems();
        for(QGraphicsItem* item : selectitems)
        {
            item->setData(15,0);
        }
        scene->update();
    });
}

void mainWindow::setColortable()
{
    ui.colortable->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui.colortable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);//楂樺害鍥哄畾
    ui.colortable->verticalHeader()->setVisible(false);
    ui.colortable->setEditTriggers(QAbstractItemView::NoEditTriggers);//涓嶅彲缂栬緫
    ui.colortable->setSelectionBehavior(QAbstractItemView::SelectRows);//璁剧疆閫変腑涓?琛?
    ui.colortable->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui.colortable->setRowCount(255);
    for(int i=0;i<255;i++)
    {
        QTableWidgetItem* item0;
        QTableWidgetItem* item1;
        QTableWidgetItem* item2;
        QTableWidgetItem* item3;
        QTableWidgetItem* item4;
        QTableWidgetItem* item5;
        item0 = new QTableWidgetItem(QString::number(i));
        item1 = new QTableWidgetItem(tr("open"));
        item2 = new QTableWidgetItem(tr("Default"));
        item3 = new QTableWidgetItem("1");
        item4 = new QTableWidgetItem("75");
        item0->setTextColor(QColor(255,255,255));
        if(i == 0)
        {
            item0 ->setBackground(QColor(0,0,0));
        }
        else if( i == 1)
        {
            item0 ->setBackground(QColor(0,0,255));
        }
        else if( i == 2)
        {
            item0 ->setBackground(QColor(255,0,0));
        }
        else if( i == 3)
        {
            item0 ->setBackground(QColor(0,255,0));
            item0->setTextColor(QColor(0,0,0));
        }
        else if( i == 4)
        {
            item0 ->setBackground(QColor(255,0,255));
        }
        else if( i == 5)
        {
            item0 ->setBackground(QColor(255,255,0));
            item0->setTextColor(QColor(0,0,0));
        }
        else if( i == 6)
        {
            item0 ->setBackground(QColor(255,125,64));
            item0->setTextColor(QColor(0,0,0));
        }
        else if( i == 7)
        {
            item0 ->setBackground(QColor(128,42,42));
        }
        else
        {


            item0->setBackground(QColor(0,0,0));
        }
        ui.colortable->setItem(i,0,item0);
        ui.colortable->setItem(i,1,item1);
        ui.colortable->setItem(i,2,item2);
        ui.colortable->setItem(i,3,item3);
        ui.colortable->setItem(i,4,item4);
    }
    ui.colortable->update();
}

void mainWindow::openfile()
{
    qlfilehandler->openfile(this,this);
}

void mainWindow::initFileconnect()
{
    //添加新文件
    connect ( ui.actionnew, SIGNAL ( triggered() ), this, SLOT ( creatnewfile() ) );
    connect ( ui.actionsave, SIGNAL ( triggered() ), this, SLOT ( savefile() ) );
    connect ( ui.actionopen, SIGNAL ( triggered() ), this, SLOT ( openfile() ) );

    connect(ui.bianji_11,&QPushButton::clicked,this,[=](){
        QFileDialog dialog(this);
        QStringList fileNames;
        QStringList types;
        types.append("PLT (*.plt))");
        types.append("ALL (*.*))");
        dialog.setNameFilters(types);
        if (dialog.exec()) {
            fileNames = dialog.selectedFiles();
            QString fileName = fileNames[0];
            QFile file(fileName);
            QStringList name = fileName.split('/');
            QStringList types = fileName.split('.');
            QString type = types[types.length()-1];
            if(type == "plt")
            {
                MyGraphicsLineItem *item = new MyGraphicsLineItem();
                item->setPath(pltfilehanler->readPLT(fileName));
                item->name = tr("群组")+QString::number(view->row+1);
                item->setPos(0,0);
                item->setVisible(true);
                scene->addItem(item);
                view->row++;
                item->setData(0,view->item_id);
                view->item_id++;
                emit view->addItem(view->row-1,item);
                return;
            }
        }
    });
}

void mainWindow::swich2Cn()
{

}
void mainWindow::swich2En()
{

}


void mainWindow::savefile()
{
    qlfilehandler->savefile(scene->items(),this);
}




void mainWindow::creatnewfile(QString filename)
{
    qlfilehandler->createnewfile(this,this,filename);
}


void mainWindow::creatnewfile()
{
    qlfilehandler->createnewfile(this,this);
}

void mainWindow::initPenNumberConnect()
{
    connect(ui.pushButton_3,&QPushButton::clicked,ui.colortable,[&](){
       ui.colortable->selectRow(0);
    });

    connect(ui.pushButton_4,&QPushButton::clicked,ui.colortable,[&](){
       ui.colortable->selectRow(7);
    });
    connect(ui.pushButton_6,&QPushButton::clicked,ui.colortable,[&](){
       ui.colortable->selectRow(1);
    });
    connect(ui.pushButton_7,&QPushButton::clicked,ui.colortable,[&](){
       ui.colortable->selectRow(2);
    });
    connect(ui.pushButton_8,&QPushButton::clicked,ui.colortable,[&](){
       ui.colortable->selectRow(4);
    });
    connect(ui.pushButton_9,&QPushButton::clicked,ui.colortable,[&](){
       ui.colortable->selectRow(3);
    });
    connect(ui.pushButton_10,&QPushButton::clicked,ui.colortable,[&](){
       ui.colortable->selectRow(5);
    });
    connect(ui.pushButton_11,&QPushButton::clicked,ui.colortable,[&](){
       ui.colortable->selectRow(6);
    });
    //笔号修改
     connect(ui.colortable, &QTableWidget::itemSelectionChanged, this, [&]() {
             QList<QTableWidgetItem*> selectItems = ui.colortable->selectedItems();
             ui.lineEdit->setText( QString::number(selectItems[0]->row()));

     });

}

void mainWindow::initDrawConnect()
{


    connect(ui.adSettingBtn,&QPushButton::clicked,this,[&](){
        AdvancedWidget * advancedWidget = new AdvancedWidget;
        advancedWidget->show();
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
            QMessageBox::information(NULL, tr("警告"), tr("请先完成曲线绘制"),
                                     QMessageBox::Yes , QMessageBox::Yes);
        }
        else
        {
            ui.draw_line->click();
            QMessageBox::information(NULL, tr("警告"), tr("请先完成直线绘制"),
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
            QMessageBox::information(NULL, tr("警告"), tr("请先完成曲线绘制"),
                                     QMessageBox::Yes, QMessageBox::Yes);
        }
        else
        {
            ui.draw_line->click();
            QMessageBox::information(NULL, tr("警告"), tr("请先完成直线绘制"),
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
            QMessageBox::information(NULL, tr("警告"), tr("请先完成曲线绘制"),
                                     QMessageBox::Yes , QMessageBox::Yes);
        }
        else
        {
            ui.draw_line->click();
            QMessageBox::information(NULL, tr("警告"), tr("请先完成直线绘制"),
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
            QMessageBox::information(NULL, tr("警告"), tr("请先完成曲线绘制"),
                                     QMessageBox::Yes , QMessageBox::Yes);
        }
        else
        {
            ui.draw_line->click();
            QMessageBox::information(NULL, tr("警告"), tr("请先完成直线绘制"),
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
            QMessageBox::information(NULL, tr("警告"), tr("请先完成曲线绘制"),
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
            QMessageBox::information(NULL,tr("警告"), tr("请先完成曲线绘制"),
                                     QMessageBox::Yes, QMessageBox::Yes);
        }
        else
        {
            ui.draw_line->click();
            QMessageBox::information(NULL, tr("警告"), tr("请先完成直线绘制"),
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
            QMessageBox::information(NULL, tr("警告"), tr("请先完成曲线绘制"),
                                     QMessageBox::Yes, QMessageBox::Yes);
        }
        else
        {
            ui.draw_line->click();
            QMessageBox::information(NULL, tr("警告"), tr("请先完成直线绘制"),
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
            QMessageBox::information(NULL, tr("警告"), tr("请先完成直线绘制"),
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
                    QMessageBox::warning(this, tr("Error"), tr("Selected file is not an image file."));
                } else {
                    QPixmap pixmap(fileName);
                    item->filename = fileName;
                    item->setPixmap(pixmap);
                    int w,h;
                    item->setDefault_Rect();
                    w=item->boundingRect().width();
                    h = item->boundingRect().height();
                    item->setPos(-w/2,-h/2);
                    item->setData(0,view->item_id);


                    QString str = QString::number(view->row + 1);
                    item->name = tr(u8"图片") + str;
                    scene->addItem(item);
                    emit view->addItem(view->row,item);
                    emit view->sceneChange();
                    view->item_id++;
                    view->row++;
                    item->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
                    item->setSelected(true);
                }
            }
            setItemMoveble(false);
        }
        else if( kkkk == 1)
        {
            ui.draw_quline->click();
            QMessageBox::information(NULL, tr("警告"), tr("请先完成曲线绘制"),
                                     QMessageBox::Yes, QMessageBox::Yes);
        }
        else
        {
            ui.draw_line->click();
            QMessageBox::information(NULL, tr("警告"), tr("请先完成直线绘制"),
                                     QMessageBox::Yes , QMessageBox::Yes);
        }
        });

    connect(ui.bianji_10, &QPushButton::clicked, this, [&]() {
        if(kkkk == 2)
        {
            action_state = 9;
            setItemMoveble(false);
        }
        else if( kkkk == 1)
        {
            ui.draw_quline->click();
            QMessageBox::information(NULL, tr("警告"), tr("请先完成曲线绘制"),
                                     QMessageBox::Yes, QMessageBox::Yes);
        }
        else
        {
            ui.draw_line->click();
            QMessageBox::information(NULL, tr("警告"), tr("请先完成直线绘制"),
                                     QMessageBox::Yes , QMessageBox::Yes);
        }
        });
}


void mainWindow::additem(int row,QGraphicsItem * item)
{
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
         item1 = new QTableWidgetItem(tr("矩形"));
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

         item1 = new QTableWidgetItem(tr("椭圆"));
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

         item1 = new QTableWidgetItem(tr("圆形"));
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
        item1 = new QTableWidgetItem(tr("直线"));
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

         item1 = new QTableWidgetItem(tr("多边形"));
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

         item1 = new QTableWidgetItem(tr("文本"));
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

         item1 = new QTableWidgetItem(tr("曲线"));
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

         item1 = new QTableWidgetItem(tr("图片"));
         item2 = new QTableWidgetItem("");
         id = node->data(0).value<int>();
         QString s = QString::number(id);
         item3 = new QTableWidgetItem(s);
    }
    else if(type == 9)
    {
         MyGraphicsCodeItem* node;
         node = qgraphicsitem_cast<MyGraphicsCodeItem*>(item);
         item0 = new QTableWidgetItem(node->name);

         item1 = new QTableWidgetItem(tr("二维码"));
         item2 = new QTableWidgetItem("");
         id = node->data(0).value<int>();
         QString s = QString::number(id);
         item3 = new QTableWidgetItem(s);
    }
    else if(type == 10)
    {
        MyGraphicsGroupItem* node;
         node = qgraphicsitem_cast<MyGraphicsGroupItem*>(item);
         item0 = new QTableWidgetItem(node->name);

         item1 = new QTableWidgetItem(tr("组合"));
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
}

void mainWindow::removeitem_notEmitChange(int id)
{
    for (int i = 0;i<ui.itemtable->rowCount();i++)
    {
        QTableWidgetItem* item1 = new QTableWidgetItem;
        item1 = ui.itemtable->item(i, 3);
        QString tid = item1->text();
        int table_id = tid.toInt();
        if(table_id  == id)
        {
            ui.itemtable->removeRow(i);
            view->row--;
        }
    }
}


void mainWindow::initItemtableConnect()
{

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


    connect(view,&MyGraphicsView::selectchange,this,[=]{

        emit ui.itemtable->itemSelectionChanged();
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
        QString text = QInputDialog::getText(this, tr("修改名称"),
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
                    else if(node->type() == 9)
                    {
                        MyGraphicsCodeItem *rect;
                        rect = qgraphicsitem_cast<MyGraphicsCodeItem*>(node);
                        rect->name = text;
                        item2->setText(text);
                        ui.itemtable->setItem(row, 0, item2);
                    }
                    break;
                }

            }
        }

        });




    //同步删除表格里的东西
    connect(view,&MyGraphicsView::removeItem,ui.itemtable,[=](int id){
        for (int i = 0;i<ui.itemtable->rowCount();i++)
        {
            QTableWidgetItem* item1 = new QTableWidgetItem;
            item1 = ui.itemtable->item(i, 3);
            QString tid = item1->text();
            int table_id = tid.toInt();
            if(table_id  == id)
            {
                ui.itemtable->removeRow(i);
                view->row--;
            }
        }
    });
}



void mainWindow::initConnect()
{

    ui.widget_29->move(0,200);
        //动态显示左侧东西
    connect(scene, &QGraphicsScene::selectionChanged, [=]() {

            QList<QGraphicsItem*> items = scene->selectedItems();
            if(items.length() == 1)
            {
                if(items[0]->type() == 6)
                {
                    MyGraphicsTextItem *item = qgraphicsitem_cast<MyGraphicsTextItem *>(items[0]);
                    ui.textEdit->setText( item->str);
                    ui.widget_25->setVisible(true);
                    ui.widget_29->move(0,370);
                }
                if(items[0]->type() == 5)
                {
                    MyGraphicsPolygonItem *item = qgraphicsitem_cast<MyGraphicsPolygonItem *>(items[0]);
                    ui.bian_num->setText(QString::number(item->num));
                    ui.widget_26->setVisible(true);
                    ui.widget_29->move(0,230);
                }
                if(items[0]->type() == 9)
                {
                    MyGraphicsCodeItem *item = qgraphicsitem_cast<MyGraphicsCodeItem *>(items[0]);
                    ui.textEdit_2->setText( item->text);
                    ui.widget_30->setVisible(true);
                    ui.widget_29->move(0,370);
                }
            }
            else
            {
                ui.widget_30->setVisible(false);
                ui.widget_29->move(0,200);
                ui.widget_25->setVisible(false);
                ui.widget_26->setVisible(false);
            }

    });

    //设置打印参数
    connect(ui.pushButton_14,&QPushButton::clicked,this,[=](){
        int i = ui.lineEdit->text().toInt();
        PrintParams p ;
        p.processnums = ui.spinBox->value();
        p.closeDelay = ui.spinBox_10->value();
        p.turnDelay = ui.spinBox_14->value();
        p.openDelay = ui.spinBox_9->value();
        p.frequence = ui.doubleSpinBox->value();
        p.endDelay = ui.spinBox_13->value();
        p.maikuan = ui.doubleSpinBox_2->value();
        p.speed = ui.spinBox_2->value();
        p.power = ui.spinBox_4->value();
        setLayer(i,p);

    });



    //设置修改框
    connect(scene, &QGraphicsScene::selectionChanged, [=]() {
        view->itemad->setitemad(this);
    });
    


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
            view->itemad->scale = scale;
            scene->update();
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
        int leftbuttomx = 5100, leftbuttomy = 5100, righttopx = -5100, righttopy = -5100;
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
                        itemsizehandler->setItemPosition<MyGraphicsRecItem>(node,leftbuttomx,leftbuttomy,righttopx,righttopy);
                    }

                    else if(node->type() == 2)
                    {
                        itemsizehandler->setItemPosition<MyGraphicsEllipseItem>(node,leftbuttomx,leftbuttomy,righttopx,righttopy);
                    }

                    else if(node->type() == 3)
                    {
                        itemsizehandler->setItemPosition<MyGraphicsCircleItem>(node,leftbuttomx,leftbuttomy,righttopx,righttopy);
                    }

                    else if(node->type() == 4)
                    {
                        itemsizehandler->setItemPosition<MyGraphicsLineItem>(node,leftbuttomx,leftbuttomy,righttopx,righttopy);
                    }
                    else if(node->type() == 5)
                    {
                        itemsizehandler->setItemPosition<MyGraphicsPolygonItem>(node,leftbuttomx,leftbuttomy,righttopx,righttopy);
                    }

                    //TODO:
                    else if(node->type() == 6)
                    {
                        itemsizehandler->setItemPosition<MyGraphicsTextItem>(node,leftbuttomx,leftbuttomy,righttopx,righttopy);

                    }
                    else if(node->type() == 7)
                    {
                        itemsizehandler->setItemPosition<MyGraphicsCurveLineItem>(node,leftbuttomx,leftbuttomy,righttopx,righttopy);
                    }
                    else if(node->type() == 8)
                    {
                        itemsizehandler->setItemPosition<MyGraphicsPixMapItem>(node,leftbuttomx,leftbuttomy,righttopx,righttopy);
                    }
                    else if(node->type() == 9)
                    {
                        itemsizehandler->setItemPosition<MyGraphicsCodeItem>(node,leftbuttomx,leftbuttomy,righttopx,righttopy);
                    }
                    else if(node->type() == 10)
                    {
                        itemsizehandler->setItemPosition<MyGraphicsGroupItem>(node,leftbuttomx,leftbuttomy,righttopx,righttopy);
                    }
                }
            }
        }
        double x = leftbuttomx, y = leftbuttomy , width = righttopx-leftbuttomx,height = righttopy-leftbuttomy;
        double dpiX = QApplication::primaryScreen()->physicalDotsPerInchX();
        double t = (dpiX*10)/254;
        if (k == 1)
        {
            pre_Pos = QPointF(x+(width/2),y+(height/2));
            pre_w = width;pre_h = height;
            x = x/t;
            y = y/t;
            width = width/t;
            height = height/t;
            ui.xposition->setText(QString::number(x+(width/2),'f',3));
            ui.yposition->setText(QString::number(y+(height/2),'f',3));
            ui.xsize->setText(QString::number(width,'f',3));
            ui.ysize->setText(QString::number(height,'f',3));
        }
        else
        {
            ui.xposition->setText("");
            ui.yposition->setText("");
            ui.xsize->setText("");
            ui.ysize->setText("");
            pre_Pos = QPointF(0,0);
            pre_w = 0;pre_h = 0;
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
        scene->update();
    });
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

    //应用，修改图元位置和大小
    connect(ui.pushButton_2,&QPushButton::clicked,this,[=](){
            itemsizehandler->setItemByLable(this);
    });

    connect(ui.brushbutton,&QPushButton::clicked,this,[=](){
        qDebug()<<"brush"<<endl;
        QList<QGraphicsItem *> selectitems = scene->selectedItems();
        for(QGraphicsItem* item:selectitems)
        {
            if(item->data(15).toInt()==1)
            {
                selectitems.removeOne(item);
            }
        }
        bool m,j;
        double space = ui.space_text->text().toDouble(&m);
        int num ;
        double angle = ui.angle_text->text().toDouble(&j);
        if(selectitems.length()==1 && m && j)
        {
            double dpiX = QApplication::primaryScreen()->physicalDotsPerInchX();
            double  temp = (dpiX * 10) / 254; //1mm = tpx
            view->angle = angle;
            int type = selectitems[0]->type();
            if(type == 1)
            {
                saveBrush<MyGraphicsRecItem>(selectitems[0],temp,num,space,angle);
            }
            else if(type == 2)
            {
                saveBrush<MyGraphicsEllipseItem>(selectitems[0],temp,num,space,angle);
            }
            else if(type == 3)
            {
                saveBrush<MyGraphicsCircleItem>(selectitems[0],temp,num,space,angle);
            }
            else if(type == 4)
            {
                saveBrush<MyGraphicsLineItem>(selectitems[0],temp,num,space,angle);
            }
            else if(type == 5)
            {
                saveBrush<MyGraphicsPolygonItem>(selectitems[0],temp,num,space,angle);
            }
            else if(type == 6)
            {
                saveBrush<MyGraphicsTextItem>(selectitems[0],temp,num,space,angle);
            }

            else if(type == 9)
            {
                saveBrush<MyGraphicsCodeItem>(selectitems[0],temp,num,space,angle);
            }

            else if(type == 10)
            {
                saveBrush<MyGraphicsGroupItem>(selectitems[0],temp,num,space,angle);
            }

        }
        else if(selectitems.length() > 1 && m && j)
        {
            emit ui.groupbtn->clicked();
            selectitems.clear();
            selectitems = scene->selectedItems();
            saveBrush<MyGraphicsGroupItem>(selectitems[0],0,num,space,angle);
        }

    });
}

template<typename T> void mainWindow::saveBrush(QGraphicsItem* node, double temp,int num , double space,double angle)
{
    T* item =  qgraphicsitem_cast<T*>(node);
    item->set_brush(angle,space);
}

void mainWindow::setItemMoveble(bool moveble)
{

    QList<QGraphicsItem*> items = scene->items();
    for (QList<QGraphicsItem*>::iterator it = items.begin(); it != items.end(); it++)
    {
        QGraphicsItem* node = qgraphicsitem_cast<QGraphicsItem*>(*it);
        node->setFlags(NULL);
    }
}

mainWindow::~mainWindow()
{}




void mainWindow::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key() == Qt::Key_Backspace)
    {
        QList<QGraphicsItem*> items = scene->selectedItems();
        for(int i=0;i<items.length();i++)
        {
            scene->removeItem(items[i]);
            emit view->removeItem(items[i]->data(0).toInt());
        }
        scene->update();
       return;
    }
    QWidget::keyPressEvent(ev);
}



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
