#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_mainWindow.h"
#include"MyGraphicsView.h"
#include"MyGraphicsScene.h"
#include"PrintParams.h"
extern int action_state;
class mainWindow : public QMainWindow
{
    Q_OBJECT

public:
    mainWindow(QWidget *parent = nullptr);
    
    ~mainWindow();
    void mainWindow::setItemMoveble(bool moveble);
    MyGraphicsScene* scene;
    MyGraphicsView* view;

    Ui::mainWindowClass ui;
    void initConnect();
    PrintParams print_layer[255];
    bool setLayer(int i, PrintParams p);
    bool LightDraw(QPainterPath path, QGraphicsItem* item, int type);
    bool printItem();
    QPoint view2print(QPointF position);
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
