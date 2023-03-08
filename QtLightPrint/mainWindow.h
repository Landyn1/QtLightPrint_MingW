#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_mainWindow.h"
#include"MyGraphicsView.h"
#include"MyGraphicsScene.h"
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
