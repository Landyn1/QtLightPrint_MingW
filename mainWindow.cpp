#include "mainWindow.h"
#include<qdebug.h>
#include"mylabel.h"
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
#include"itemfileclass.h"
#include <qxml.h>
#include <QDomDocument>
#include<qbuffer.h>
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
    splitDockWidget(ui.dock_leftKedu, ui.dock_file, Qt::Horizontal);
    splitDockWidget(ui.dock_file, ui.dock_topKedu, Qt::Vertical);
   // splitDockWidget(ui.dock_topKedu, ui.dock3, Qt::Horizontal);
    splitDockWidget(ui.dock_topKedu, ui.dock4, Qt::Vertical);
    
    

    //去除头
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


    lTitleBar = ui.dock_file->titleBarWidget();
    lEmptyWidget = new QWidget();
    ui.dock_file->setTitleBarWidget(lEmptyWidget);
    delete lTitleBar;
    //ui.dock4->setWindowTitle("wenjian1");
    //设置图片
    ui.bianji->setIcon(QIcon(":/draw/Res/Select.png"));
    ui.draw_line->setIcon(QIcon(":/draw/Res/Line.png"));
    //ui.draw_quline->setIcon(QIcon(":/draw/Res/Line.png"));
    ui.draw_yuan->setIcon(QIcon(":/draw/Res/Circle.png"));
    ui.draw_wenzi->setIcon(QIcon(":/draw/Res/Font.png"));
    ui.draw_sanjiao->setIcon(QIcon(":/draw/Res/Rectangle.png"));
    ui.draw_polygon->setIcon(QIcon(":/draw/Res/RegularPolygon.png"));

    //设置铺满dock
    MyWidget* wi1 = new MyWidget;
    MyWidget* wi2 = new MyWidget;
    //ui.itemtable->setParent(wi1);
    wi1->size = QSize(200, 200);
    QVBoxLayout* layout1 = new QVBoxLayout;
    QVBoxLayout* layout2 = new QVBoxLayout;
   

    layout1->addWidget(ui.itemtable);
    wi1->setLayout(layout1);
    ui.dock1->setWidget(wi1);

    wi2->size = QSize(200, 400);
    layout2->addWidget(ui.widget_4);
    wi2->setLayout(layout2);
    ui.dock2->setWidget(wi2);

    ui.dock7->setWidget(ui.widget_5);

    ui.dock_file->setWidget(ui.widget_24);
    connect(ui.leftmove,&QPushButton::clicked,[=](){

        ui.scrollArea_3->horizontalScrollBar()->setValue(ui.scrollArea_3->horizontalScrollBar()->value()-10);
    });
    connect(ui.rightmove,&QPushButton::clicked,[=](){

        ui.scrollArea_3->horizontalScrollBar()->setValue(ui.scrollArea_3->horizontalScrollBar()->value()+10);
    });
    //添加默认文件 及名字。
    QWidget *widgetfile = new QWidget();
    widgetfile->setParent(ui.scrollArea_3);
    QHBoxLayout *lay = new QHBoxLayout();
    QPushButton *close_file =new QPushButton("×");
    myLabel *label_file= new myLabel(filenum-1);
    label_file->setText("file"+QString::number(fileid+1));
    lay->addWidget(label_file);
    lay->addWidget(close_file);
    lay->setMargin(0);
    label_file->adjustSize();
    QSize file1_size = label_file->size();
    int file1_w = file1_size.width();
    //label_file->resize(file1_w,30);
    label_file->setMinimumSize(QSize(file1_w,30));
    label_file->setMaximumSize(QSize(file1_w,30));
    close_file->setMinimumSize(QSize(20,20));
    close_file->setMaximumSize(QSize(20,20));
    widgetfile->setStyleSheet("QWidget{background-color:rgb(255,255,255);}");
    close_file->setStyleSheet("QPushButton{background-color:rgb(240,240,240)}");
    widgetfile->setMinimumSize(QSize(file1_w+20,30));
    widgetfile->setMaximumSize(QSize(file1_w+20,30));
    widgetfile->setLayout(lay);
    m_file->setAlignment(Qt::AlignLeft);
    m_file->setMargin(0);
    m_file->addWidget(widgetfile);
    files->setLayout(m_file);
    ui.scrollArea_3->setWidget(files);
    MyGraphicsScene *scene1 = new MyGraphicsScene();
    MyGraphicsView *view1 = new MyGraphicsView();
    scenes.append(scene1);
    views.append(view1);
    isfirst.append(true);
    fileid++;
    connect(label_file,&myLabel::clicked,[=](int id){
        scene = scenes[id];
        view = views[id];
        view->setScene(scene);

        ui.dock4->setWidget(view);
        view->setStatusBarPtr(ui.statusBar);


        while(ui.itemtable->rowCount()>0)
        {
            ui.itemtable->removeRow(0);
        }
        QList<QGraphicsItem*> visibleItems;
        QList<QGraphicsItem*> items = scene->items();
        for(int i=0;i<items.length();i++)
        {
            if(items[i]->data(0).toInt()>0)
            {
                visibleItems.append(items[i]);
            }
        }
        for(int i=visibleItems.length()-1;i>=0;i--)
        {

            emit view->addItem(visibleItems.length()-1-i,visibleItems[i]);
        }

        if(isfirst[id])
        {
            isfirst[id]=false;
        }

        //m_file->findChildren<QWidget *>();

        for(int i=0;i<m_file->count();i++)
        {
            QLayoutItem* item = m_file->itemAt(i);
            QWidget* widget = item->widget();
            widget->setStyleSheet("QWidget{background-color:rgb(190,190,190);}");
            QPushButton *btn = widget->findChild<QPushButton *>();
            btn->setStyleSheet("QPushButton{background-color:rgb(180,180,180)}");
        }

        widgetfile->setStyleSheet("QWidget{background-color:rgb(255,255,255);}");
        close_file->setStyleSheet("QPushButton{background-color:rgb(240,240,240)}");
        view->centerOn(QPointF(0, 0));
        scene->update();

    });

    connect(close_file,&QPushButton::clicked,this,[=](){

        //lay->removeWidget(label_file);
        //lay->removeWidget(close_file);
        if(m_file->count() == 1)
        {
            ui.dock4->setWidget(NULL);
        }

        for(int i=0;i<m_file->count();i++)
        {
            QLayoutItem* item = m_file->itemAt(i);
            QWidget* widget = item->widget();
            myLabel *l = widget->findChild<myLabel *>();
            if(l->id==label_file->id+1)
            {
                emit l->clicked(l->id);
            }
            if(l->id>label_file->id)
            {
                l->id = l->id-1;
            }
        }

        widgetfile->setParent(NULL);
        m_file->removeWidget(widgetfile);
        delete widgetfile;

        isfirst[filenum-1] = true;
        files->setLayout(m_file);
        ui.scrollArea_3->setWidget(files);

        filenum--;

        scenes.removeOne(scene1);
        views.removeOne(view1);

    });
    scene = scenes[0];
    view = views[0];
    view->setScene(scene);
    view->setStatusBarPtr(ui.statusBar);
    view->setMouseTracking(true);
    view->preProcessItem();
    scene->setBackgroundBrush(Qt::white);
    scene->setSceneRect(-10000, -10000, 20000, 20000);
    view->setAlignment(Qt::AlignCenter);
    ui.dock4->setWidget(view);


    view->scale(1, -1);
    initConnect();

    //添加新文件
    connect ( ui.actionnew, SIGNAL ( triggered() ), this, SLOT ( creatnewfile() ) );

    connect ( ui.actionsave, SIGNAL ( triggered() ), this, SLOT ( savefile() ) );

    connect ( ui.actionopen, SIGNAL ( triggered() ), this, SLOT ( openfile() ) );

    //ui.colortable->horizontalHeader()->setResizeMode(QHeaderView::Stretch);

    ui.colortable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    
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

    ui.scrollArea_3->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui.scrollArea_3->verticalScrollBar()->hide();



    //璁剧疆鍙充晶鏍峰紡
    ui.widget_19->setStyleSheet(QString::fromUtf8("#widget_19{border:1px solid rgb(200,200,200)}"));
    ui.colorbuttom->setStyleSheet(QString::fromUtf8("#colorbuttom{border:1px solid rgb(200,200,200)}"));
    ui.pushButton_3->setAutoFillBackground(true);
    //initConnect();
}

void mainWindow::savefile()
{

        QString fileName = QFileDialog::getSaveFileName(this,
            tr("保存"),
            "",
            tr("TEXT Files (*.dat)"));
        if(fileName.isNull())
        {
            return;
        }
        QFile file(fileName);
        if (!file.open(QFileDevice::WriteOnly | QFileDevice::Truncate))
        {
            QMessageBox::warning(this, "Error", "打开文件错误!");
        }

        //下附各个图元
        QDataStream out(&file);
        QList<QGraphicsItem*> items = scene->items();
        for(QGraphicsItem * node:items)
        {
            if(node->data(0).toInt()>0)
            {
                ItemFileClass *iff = new ItemFileClass();
                if(node->type() == 1 )
                {
                    MyGraphicsRecItem *item = qgraphicsitem_cast<MyGraphicsRecItem *>(node);
                    iff->name = item->name;
                    iff->id = item->data(0).toInt();
                    iff->rec = item->rect();
                    iff->pos = item->pos();
                    iff->type = 1;
                }
                else if(node->type() == 2)
                {
                    MyGraphicsEllipseItem *item = qgraphicsitem_cast<MyGraphicsEllipseItem *>(node);
                    iff->name = item->name;
                    iff->id = item->data(0).toInt();
                    iff->rec = item->rect();
                    iff->pos = item->pos();
                    iff->type =2;
                }
                else if(node->type() == 3)
                {
                    MyGraphicsCircleItem *item = qgraphicsitem_cast<MyGraphicsCircleItem *>(node);
                    iff->name = item->name;
                    iff->id = item->data(0).toInt();
                    iff->rec = item->rect();
                    iff->pos = item->pos();
                    iff->type =item->type();
                }
                else if(node->type() ==  4)
                {
                    MyGraphicsLineItem *item = qgraphicsitem_cast<MyGraphicsLineItem *>(node);
                    iff->name = item->name;
                    iff->id = item->data(0).toInt();
                    iff->path = item->path();
                    iff->pos = item->pos();
                    iff->type =item->type();
                }
                else if(node->type() == 5)
                {
                    MyGraphicsPolygonItem *item = qgraphicsitem_cast<MyGraphicsPolygonItem *>(node);
                    iff->name = item->name;
                    iff->id = item->data(0).toInt();
                    iff->rec = item->rect();
                    iff->pos = item->pos();
                    iff->path = item->path;
                    iff->bian_num = item->num;
                    iff->type =item->type();
                }
                else if(node->type() == 6)
                {
                    MyGraphicsTextItem *item = qgraphicsitem_cast<MyGraphicsTextItem *>(node);
                    iff->name = item->name;
                    iff->id = item->data(0).toInt();
                    iff->rec = item->rect();
                    iff->pos = item->pos();
                    iff->path = item->path;
                    iff->font = item->font;
                    iff->text = item->str;
                    iff->type =item->type();
                }
                else if(node->type() == 7)
                {
                    MyGraphicsCurveLineItem *item = qgraphicsitem_cast<MyGraphicsCurveLineItem *>(node);
                    iff->name = item->name;
                    iff->id = item->data(0).toInt();
                    iff->path = item->path();
                    iff->pos = item->pos();
                    iff->type =item->type();
                }
                else if(node->type() == 8)
                {
                    MyGraphicsPixMapItem *item = qgraphicsitem_cast<MyGraphicsPixMapItem *>(node);
                    iff->name = item->name;
                    iff->id = item->data(0).toInt();
                    iff->rec = item->rectf;
                    iff->pos = item->pos();
                    iff->pixAdr = item->filename;
                    iff->type =item->type();
                    QImage img = item->pixmap().toImage();

                    QByteArray ba;
                    QBuffer buf(&ba);
                    img.save(&buf, "png");
                    iff->pix = ba.toBase64();

                }
                out<<*iff;

            }
        }
        file.close();
}

void mainWindow::openfile()
{
    QFileDialog dialog(this);
    QStringList fileNames;
    dialog.setNameFilter("text (*.dat)");
    if (dialog.exec()) {
        fileNames = dialog.selectedFiles();
        QString fileName = fileNames[0];
        QFile file(fileName);
        QStringList name = fileName.split('/');
        creatnewfile(name[name.length()-1]);
        if (!file.open (QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "Error", "Selected file is not  correct.");
        }
        else {

            QDataStream in(&file);
            QList<QGraphicsItem *> items;
            while (!in.atEnd())
            {
                ItemFileClass t;
                in>>t;
                if(t.type == 1)
                {
                    MyGraphicsRecItem *item = new MyGraphicsRecItem();
                    item->setPos(t.pos);
                    item->setRect(t.rec);
                    item->name = t.name;
                    item->setData(0,t.id);
                    scene->addItem(item);
                    item->setVisible(true);
                    scene->update();
                    items.append(item);
                    //emit view->addItem(view->row,item);
                    view->row++;
                    if(view->item_id<t.id)
                        view->item_id = t.id;
                }
                else if(t.type == 2)
                {
                    MyGraphicsEllipseItem* item = new MyGraphicsEllipseItem();
                    item->setPos(t.pos);
                    item->setRect(t.rec);
                    item->name = t.name;
                    item->setData(0,t.id);
                    scene->addItem(item);
                    item->setVisible(true);
                    scene->update();
                    items.append(item);
                    //emit view->addItem(view->row,item);
                    view->row++;
                    if(view->item_id<t.id)
                        view->item_id = t.id;
                }
                else if(t.type == 3)
                {
                    MyGraphicsCircleItem *item = new MyGraphicsCircleItem();
                    item->setPos(t.pos);
                    item->setRect(t.rec);
                    item->name = t.name;
                    item->setData(0,t.id);
                    scene->addItem(item);
                    item->setVisible(true);
                    scene->update();
                    items.append(item);
                    //emit view->addItem(view->row,item);
                    view->row++;
                    if(view->item_id<t.id)
                        view->item_id = t.id;
                }
                else if(t.type == 4)
                {
                    MyGraphicsLineItem *item = new MyGraphicsLineItem();
                    item->setPath(t.path);
                    item->setVisible(true);
                    item->setData(0, t.id);
                    item->setPos( t.pos);
                    item->name=t.name;
                    scene->addItem(item);
                    items.append(item);
                    //emit view->addItem(view->row,item);
                    view->row++;
                    if(view->item_id<t.id)
                        view->item_id = t.id;
                }
                else if(t.type == 5)
                {
                    MyGraphicsPolygonItem *item = new MyGraphicsPolygonItem();
                    item->setPath(t.path);
                    item->setRect(t.rec);
                    item->setVisible(true);
                    item->setData(0, t.id);
                    item->setPos( t.pos);
                    item->name=t.name;
                    scene->addItem(item);
                    items.append(item);
                    //emit view->addItem(view->row,item);
                    view->row++;
                    if(view->item_id<t.id)
                        view->item_id = t.id;
                }
                else if(t.type == 6)
                {
                    MyGraphicsTextItem *item = new MyGraphicsTextItem();
                    item->name = t.name;
                    item->setRect(t.rec);
                    item->setVisible(true);
                    item->setData(0, t.id);
                    item->setPos( t.pos);
                    item->path = t.path;
                    item->setStr(t.text,t.font);
                    scene->addItem(item);
                    items.append(item);
                    //emit view->addItem(view->row,item);
                    view->row++;
                    if(view->item_id<t.id)
                        view->item_id = t.id;
                }
                else if(t.type == 7)
                {
                    MyGraphicsCurveLineItem * item = new MyGraphicsCurveLineItem();
                    item->name = t.name;
                    item->setVisible(true);
                    item->setData(0, t.id);
                    item->setPos( t.pos);
                    item->setPath(t.path);
                    scene->addItem(item);
                    items.append(item);
                    //emit view->addItem(view->row,item);
                    view->row++;
                    if(view->item_id<t.id)
                        view->item_id = t.id;
                }

                else if(t.type == 8)
                {
                    QPixmap pix;
                    pix.loadFromData(QByteArray::fromBase64(t.pix.toLocal8Bit()));

                    MyGraphicsPixMapItem *item = new MyGraphicsPixMapItem();
                    item->name = t.name;
                    item->setVisible(true);
                    item->setData(0, t.id);
                    item->setPos( t.pos);
                    item->setRectF(t.rec.toRect());
                    item->setPixmap(pix);
                    scene->addItem(item);
                    items.append(item);
                    //emit view->addItem(view->row,item);
                    view->row++;
                    if(view->item_id<t.id)
                        view->item_id = t.id;
                }

            }
            view->item_id++;
            int l = items.length();
            QGraphicsItem *temp;
            for(int i=0;i<l-1;i++)
            {
                for(int j=0;j<l-i-1;j++)
                {
                    if(items[j]->data(0).toInt()>items[j+1]->data(0).toInt())
                    {
                        temp = items[j];
                        items[j] = items[j+1];
                        items[j+1] = temp;
                    }
                }
            }
            for(int i=0;i<l;i++)
            {
                emit view->addItem(i,items[i]);
            }

        }
        file.close ();
    }

}


void mainWindow::creatnewfile(QString filename)
{
    QWidget *widgetfile = new QWidget();

    //widgetfile->setParent(ui.scrollArea_3);
    QHBoxLayout *lay = new QHBoxLayout();
    QPushButton *close_file =new QPushButton("×");
    myLabel *label_file= new myLabel(filenum);
    label_file->setText(filename);
    lay->addWidget(label_file);
    lay->addWidget(close_file);
    lay->setMargin(0);
    label_file->adjustSize();
    QSize file1_size = label_file->size();
    int file1_w = file1_size.width();
    //label_file->resize(file1_w,30);
    label_file->setMinimumSize(QSize(file1_w,30));
    label_file->setMaximumSize(QSize(file1_w,30));

    close_file->setMinimumSize(QSize(20,20));
    close_file->setMaximumSize(QSize(20,20));
    widgetfile->setStyleSheet("QWidget{background-color:rgb(255,255,255);}");
    close_file->setStyleSheet("QPushButton{background-color:rgb(240,240,240)}");
    widgetfile->setMinimumSize(QSize(file1_w+20,30));
    widgetfile->setMaximumSize(QSize(file1_w+20,30));
    widgetfile->setLayout(lay);
    m_file->setAlignment(Qt::AlignLeft);
    m_file->setMargin(0);
    m_file->addWidget(widgetfile);
    files->setLayout(m_file);
    ui.scrollArea_3->setWidget(files);
    filenum++;
    fileid++;
    MyGraphicsScene *scene1 = new MyGraphicsScene();
    MyGraphicsView *view1 = new MyGraphicsView();
    scenes.append(scene1);
    views.append(view1);
    isfirst.append(true);
    connect(label_file,&myLabel::clicked,[=](int id){
        scene = scenes[id];
        view = views[id];
        view->setScene(scene);
        view->setStatusBarPtr(ui.statusBar);
        while(ui.itemtable->rowCount()>0)
        {
            ui.itemtable->removeRow(0);
        }
        //ui.itemtable->removeRow(0);

        QList<QGraphicsItem*> visibleItems;
        QList<QGraphicsItem*> items = scene->items();
        for(int i=0;i<items.length();i++)
        {
            if(items[i]->data(0).toInt()>0)
            {
                visibleItems.append(items[i]);
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
            emit view->addItem(i,visibleItems[i]);
        }
        if(isfirst[id])
        {
            view->setMouseTracking(true);
            view->preProcessItem();


            scene->setBackgroundBrush(Qt::white);
            scene->setSceneRect(-10000, -10000, 20000, 20000);
            view->setAlignment(Qt::AlignCenter);

            view->scale(1, -1);
            view->topkedu->setPos(0, view->mapToScene(0, 0).y() );
            view->leftkedu->setPos(view->mapToScene(0, 0).x(),0);

            scene->update();
            initConnect();
            isfirst[id]=false;
        }
        ui.dock4->setWidget(view);
        view->centerOn(QPointF(0, 0));
        for(int i=0;i<m_file->count();i++)
        {
            QLayoutItem* item = m_file->itemAt(i);
            QWidget* widget = item->widget();
            widget->setStyleSheet("QWidget{background-color:rgb(190,190,190);}");
            QPushButton *btn = widget->findChild<QPushButton *>();
            btn->setStyleSheet("QPushButton{background-color:rgb(180,180,180)}");
        }

        widgetfile->setStyleSheet("QWidget{background-color:rgb(255,255,255);}");
        close_file->setStyleSheet("QPushButton{background-color:rgb(240,240,240)}");

    });
    emit label_file->clicked(label_file->id);

    connect(close_file,&QPushButton::clicked,this,[=](){

        //lay->removeWidget(label_file);
        //lay->removeWidget(close_file);
        if(m_file->count() == 1)
        {
            ui.dock4->setWidget(NULL);
        }
        for(int i=0;i<m_file->count();i++)
        {
            QLayoutItem* item = m_file->itemAt(i);
            QWidget* widget = item->widget();
            myLabel *l = widget->findChild<myLabel *>();
            if(l->id==label_file->id-1)
            {
                emit l->clicked(l->id);
            }
            if(l->id>label_file->id)
            {
                l->id = l->id-1;
            }
        }

        widgetfile->setParent(NULL);
        m_file->removeWidget(widgetfile);
        delete widgetfile;

        isfirst[filenum-1] = true;
        files->setLayout(m_file);
        ui.scrollArea_3->setWidget(files);

        filenum--;

        scenes.removeOne(scene1);
        views.removeOne(view1);

    });
}


void mainWindow::creatnewfile()
{
    QWidget *widgetfile = new QWidget();

    //widgetfile->setParent(ui.scrollArea_3);
    QHBoxLayout *lay = new QHBoxLayout();
    QPushButton *close_file =new QPushButton("×");
    myLabel *label_file= new myLabel(filenum);
    label_file->setText("file"+QString::number(fileid+1));
    lay->addWidget(label_file);
    lay->addWidget(close_file);
    lay->setMargin(0);
    label_file->adjustSize();
    QSize file1_size = label_file->size();
    int file1_w = file1_size.width();
    //label_file->resize(file1_w,30);
    label_file->setMinimumSize(QSize(file1_w,30));
    label_file->setMaximumSize(QSize(file1_w,30));

    close_file->setMinimumSize(QSize(20,20));
    close_file->setMaximumSize(QSize(20,20));
    widgetfile->setStyleSheet("QWidget{background-color:rgb(255,255,255);}");
    close_file->setStyleSheet("QPushButton{background-color:rgb(240,240,240)}");
    widgetfile->setMinimumSize(QSize(file1_w+20,30));
    widgetfile->setMaximumSize(QSize(file1_w+20,30));
    widgetfile->setLayout(lay);
    m_file->setAlignment(Qt::AlignLeft);
    m_file->setMargin(0);
    m_file->addWidget(widgetfile);
    files->setLayout(m_file);
    ui.scrollArea_3->setWidget(files);
    filenum++;
    fileid++;
    MyGraphicsScene *scene1 = new MyGraphicsScene();
    MyGraphicsView *view1 = new MyGraphicsView();
    scenes.append(scene1);
    views.append(view1);
    isfirst.append(true);
    connect(label_file,&myLabel::clicked,[=](int id){
        scene = scenes[id];
        view = views[id];
        view->setScene(scene);
        view->setStatusBarPtr(ui.statusBar);
        while(ui.itemtable->rowCount()>0)
        {
            ui.itemtable->removeRow(0);
        }
        //ui.itemtable->removeRow(0);

        QList<QGraphicsItem*> visibleItems;
        QList<QGraphicsItem*> items = scene->items();
        for(int i=0;i<items.length();i++)
        {
            if(items[i]->data(0).toInt()>0)
            {
                visibleItems.append(items[i]);
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
            emit view->addItem(i,visibleItems[i]);
        }
        if(isfirst[id])
        {
            view->setMouseTracking(true);
            view->preProcessItem();


            scene->setBackgroundBrush(Qt::white);
            scene->setSceneRect(-10000, -10000, 20000, 20000);
            view->setAlignment(Qt::AlignCenter);

            view->scale(1, -1);
            view->topkedu->setPos(0, view->mapToScene(0, 0).y() );
            view->leftkedu->setPos(view->mapToScene(0, 0).x(),0);

            scene->update();
            initConnect();
            isfirst[id]=false;
        }
        ui.dock4->setWidget(view);
        view->centerOn(QPointF(0, 0));
        for(int i=0;i<m_file->count();i++)
        {
            QLayoutItem* item = m_file->itemAt(i);
            QWidget* widget = item->widget();
            widget->setStyleSheet("QWidget{background-color:rgb(190,190,190);}");
            QPushButton *btn = widget->findChild<QPushButton *>();
            btn->setStyleSheet("QPushButton{background-color:rgb(180,180,180)}");
        }

        widgetfile->setStyleSheet("QWidget{background-color:rgb(255,255,255);}");
        close_file->setStyleSheet("QPushButton{background-color:rgb(240,240,240)}");

    });
    emit label_file->clicked(label_file->id);

    connect(close_file,&QPushButton::clicked,this,[=](){

        //lay->removeWidget(label_file);
        //lay->removeWidget(close_file);
        if(m_file->count() == 1)
        {
            ui.dock4->setWidget(NULL);
        }
        for(int i=0;i<m_file->count();i++)
        {
            QLayoutItem* item = m_file->itemAt(i);
            QWidget* widget = item->widget();
            myLabel *l = widget->findChild<myLabel *>();
            if(l->id==label_file->id-1)
            {
                emit l->clicked(l->id);
            }
            if(l->id>label_file->id)
            {
                l->id = l->id-1;
            }
        }

        widgetfile->setParent(NULL);
        m_file->removeWidget(widgetfile);
        delete widgetfile;

        isfirst[filenum-1] = true;
        files->setLayout(m_file);
        ui.scrollArea_3->setWidget(files);

        filenum--;

        scenes.removeOne(scene1);
        views.removeOne(view1);

    });
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
                    item->filename = fileName;
                    item->setPixmap(pixmap);
                    int w,h;
                    item->setDefault_Rect();
                    w=item->boundingRect().width();
                    h = item->boundingRect().height();
                    item->setPos(-w/2,-h/2);
                    item->setData(0,view->item_id);


                    QString str = QString::number(view->row + 1);
                    item->name = u8"图片" + str;
                    scene->addItem(item);
                    emit view->addItem(view->row,item);
                    view->item_id++;
                    view->row++;
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
    
    connect(ui.markButton, &QPushButton::clicked, this, &mainWindow::printItem);
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
        //row = scene->items().length()-12;
        //qDebug()<<row<<"row"<<endl;
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
        int x = zuoxiax, y = zuoxiay , width = youshangx-zuoxiax,height = youshangy-zuoxiay;
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
        if(id>0)
        {
            if (node->type() == 1)
            {
                MyGraphicsRecItem* rect = qgraphicsitem_cast<MyGraphicsRecItem*>(*it);
                LightDraw(rect->ViewPath(), rect->printLayer);
            }
            else if(node->type() == 2 )
            {
                MyGraphicsEllipseItem *item = qgraphicsitem_cast<MyGraphicsEllipseItem*>(*it);
                LightDraw(item->ViewPath(),item->printLayer);
            }
            else if(node->type() == 3)
            {
                MyGraphicsCircleItem *item = qgraphicsitem_cast<MyGraphicsCircleItem*>(*it);
                LightDraw(item->ViewPath(),item->printLayer);
            }
            else if(node->type() == 4)
            {
                MyGraphicsLineItem *item = qgraphicsitem_cast<MyGraphicsLineItem*>(*it);
                LightDraw(item->ViewPath(),item->printLayer);
            }
            else if(node->type() == 5)
            {
                MyGraphicsPolygonItem *item = qgraphicsitem_cast<MyGraphicsPolygonItem*>(*it);
                LightDraw(item->ViewPath(),item->printLayer);
            }
            else if(node->type() == 6)
            {
                MyGraphicsTextItem *item = qgraphicsitem_cast<MyGraphicsTextItem*>(*it);
                LightDraw(item->ViewPath(),item->printLayer);
            }
            else if(node->type() == 7)
            {

            }
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

bool mainWindow::LightDraw(QPainterPath path,int printLayer)
{      
        unsigned int speed = print_layer[printLayer].speed/100*65536;//转化
        CUSchSetSpeed(speed, 3);


        unsigned int frequnce = print_layer[printLayer].frequence * 1000;
        CUSetPWM(PWM2, frequnce, 3, false);
        CUSetNullDelayUs(20000, 3);
        unsigned int power = print_layer[printLayer].power * 2.56; //0-255之间代表0-100
        CULaserOut(ST_DATA, power, 3);
        CUSetNullDelayUs(100, 3);
        CULaserOut(ST_LATCH, 1, 3);
        CUSetNullDelayUs(5000, 3);
        CULaserOut(ST_LATCH, 0, 3);
        unsigned int openDealy = print_layer[printLayer].openDelay;
        unsigned int closeDealy = print_layer[printLayer].closeDelay;
        unsigned int endDealy = print_layer[printLayer].endDelay;
        unsigned int turnDealy = print_layer[printLayer].turnDelay;
        CUSetOpenDelayUs(openDealy,3);//2023-1-12
        CUSetCloseDelayUs(closeDealy, 3);//2023-1-13
        CUSetTuneDelayUs(turnDealy, 3);//2023-1-13
        CUSetNullDelayUs(5000, 3);
        //结束延时没找到啊

        //开始画
        //QPolygonF polu = path.toFillPolygon();

        for (int i = 0; i < path.elementCount(); i++)
        {
            QPainterPath::Element element = path.elementAt(i);
            QPointF po = element;
            QPoint printpo = view2print(po);
            if (element.isMoveTo())
            {
                CUSchJMPLinear(printpo.x(), printpo.y(), 3);
            }
            else if (element.isLineTo())
            {
                CUSchOutLinear(printpo.x(), printpo.y(), 3);
            }
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
