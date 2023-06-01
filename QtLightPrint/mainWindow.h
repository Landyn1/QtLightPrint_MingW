#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_mainWindow.h"
#include"MyGraphicsView.h"
#include"MyGraphicsScene.h"
#include"PrintParams.h"
#include"itemfileclass.h"
extern int action_state;
extern int k;
class mainWindow : public QMainWindow
{
    Q_OBJECT

public:
    mainWindow(QWidget *parent = nullptr);
    int findroot(int id,QList<QGraphicsItem*> items);
    ~mainWindow();
    void setItemMoveble(bool moveble);
    MyGraphicsScene* scene;
    MyGraphicsView* view;
    void dockConnectInit();
    Ui::mainWindowClass ui;
    void initConnect();
    PrintParams print_layer[255];
    bool LightDraw(QPixmap pixmap,int printLayer);
    bool setLayer(int i, PrintParams p);
    bool LightDraw(QPainterPath path, int printLayer);
    bool printItem();
    QPoint view2print(QPointF position);
    int kkkk = 2;  //0：正在绘制曲线 1：正在绘制直线 2：不在绘制
    int filenum = 0;
    int fileid = 0;
    QWidget *files = new QWidget();
    QHBoxLayout *m_file = new QHBoxLayout();
    QList<QList<QGraphicsItem*>> present_items; //二维数组，记录items的情况
    int present = 0;                   //用于当前的item定位。
    QList<QGraphicsItem*> copyall(QList<QGraphicsItem*> itemss);
    QList<MyGraphicsView *> views;
    QList<MyGraphicsScene *> scenes;
    void additem_notEmitChange(int row, QGraphicsItem *item);
    void removeitem_notEmitChange(int id);
    QList<bool> isfirst;
    void creatnewfile(QString filename);
    QPointF pre_Pos;
    double pre_w;
    double pre_h;
    void setpreRect();
    int clicknum = 0;
    void setColortable();
    void initFileconnect();
    void initPenNumberConnect();
    void initDrawConnect();
    void initItemtableConnect();

    double spaceadjust = 1;   //用来调整实际打印的距离
    QList<QGraphicsItem*> copyitems;
    template<typename T> void setItemRect_XandY(QGraphicsItem* node, int &x,int &y);
    template<typename T> void leftAlign(QGraphicsItem* node,QPointF rootPos);
    template<typename T> void setItemRect_WandH(QGraphicsItem* node, int x,int y,int &w,int &h);
    template<typename T> void saveItems(QGraphicsItem* node, ItemFileClass *&iff,int type);
    template<typename T> void saveBrush(QGraphicsItem* node, double temp,int num , double space,double angle);
    template<typename T> void setItemPosition(QGraphicsItem* node, int &leftbuttomx,int &leftbuttomy,int &righttopx,int &righttopy);
    template<typename T> QPainterPath getpath(QGraphicsItem* node,QPainterPath &path);
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void additem(int row,QGraphicsItem * item);
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
