#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_mainWindow.h"
#include"MyGraphicsView.h"
#include"MyGraphicsScene.h"
#include"PrintParams.h"
extern int action_state;
extern int k;
class mainWindow : public QMainWindow
{
    Q_OBJECT

public:
    mainWindow(QWidget *parent = nullptr);
    
    ~mainWindow();
    void setItemMoveble(bool moveble);
    MyGraphicsScene* scene;
    MyGraphicsView* view;

    Ui::mainWindowClass ui;
    void initConnect();
    PrintParams print_layer[255];
    bool LightDraw(QPixmap pixmap,int printLayer);
    bool setLayer(int i, PrintParams p);
    bool LightDraw(QPainterPath path, int printLayer);
    bool printItem();
    QPoint view2print(QPointF position);
    int kkkk = 2;
    int filenum = 1;
    int fileid = 0;
    QWidget *files = new QWidget();
    QHBoxLayout *m_file = new QHBoxLayout();
    QList<MyGraphicsScene *> scenes;
    QList<MyGraphicsView *> views;
    QList<bool> isfirst;
    void creatnewfile(QString filename);
    QPointF pre_Pos;
    double pre_w;
    double pre_h;
    void setpreRect();
    int clicknum = 0;
public slots:
    void creatnewfile();
    void savefile();
    void openfile();
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
