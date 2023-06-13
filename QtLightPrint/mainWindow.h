#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_mainWindow.h"
#include"GraphicsItems/MyGraphicsView.h"
#include"GraphicsItems/MyGraphicsScene.h"
#include"PrintParams.h"
#include"FileHandel/itemfileclass.h"
extern int action_state;
extern int k;
class qlptfileHandle ;
class pltFileHandle;
class ItemSizeHandle;
class ItemAlignHandle;
class ItemPrintHandle;
class mainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MyGraphicsScene* scene;
    MyGraphicsView* view;
    Ui::mainWindowClass ui;
    PrintParams print_layer[255];   
    int kkkk = 2;  //0：正在绘制曲线 1：正在绘制直线 2：不在绘制
    int filenum = 0;
    int fileid = 0;
    QWidget *files = new QWidget();
    QHBoxLayout *m_file = new QHBoxLayout();
    QList<QList<QGraphicsItem*>> present_items; //二维数组，记录items的情况
    int present = 0;                   //用于当前的item定位。
    QList<MyGraphicsView *> views;
    QList<MyGraphicsScene *> scenes;
    QList<bool> isfirst;    
    QPointF pre_Pos;
    double pre_w;
    double pre_h;
    int clicknum = 0;
    double spaceadjust = 1;   //用来调整实际打印的距离
    QList<QGraphicsItem*> copyitems;
    qlptfileHandle *qlfilehandler;
    pltFileHandle *pltfilehanler;
    ItemSizeHandle *itemsizehandler;
    ItemAlignHandle *itemalignhandler;
    ItemPrintHandle *itemprinthandler;


    mainWindow(QWidget *parent = nullptr);
    ~mainWindow();
    void setItemMoveble(bool moveble);
    void dockConnectInit();
    void initConnect();
    bool setLayer(int i, PrintParams p);
    QList<QGraphicsItem*> copyall(QList<QGraphicsItem*> itemss);
    void additem_notEmitChange(int row, QGraphicsItem *item);
    void removeitem_notEmitChange(int id);
    void creatnewfile(QString filename);
    void setColortable();
    void initFileconnect();
    void initPenNumberConnect();
    void initDrawConnect();
    void initItemtableConnect();
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void additem(int row,QGraphicsItem * item);
    template<typename T> void saveItems(QGraphicsItem* node, ItemFileClass *&iff,int type);
    template<typename T> void saveBrush(QGraphicsItem* node, double temp,int num , double space,double angle);
    template<typename T> QPainterPath getpath(QGraphicsItem* node,QPainterPath &path);

public slots:
    void creatnewfile();
    void savefile();
    void openfile();
    void swich2Cn();
    void swich2En();
};

class MyWidget : public QWidget
{
public:
    QSize sizeHint() const
    {
        return size; /* 在这里定义dock的初始大小 */
    }
    QSize size;
};
