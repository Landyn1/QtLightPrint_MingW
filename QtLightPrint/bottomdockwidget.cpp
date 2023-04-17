#include "bottomdockwidget.h"
#include <QDebug>
#include "configwidget.h"
#include "advancedwidget.h"

BottomDockWidget::BottomDockWidget()
{
    initUI();
    initSignalAndSlots();
}

void BottomDockWidget::initUI()
{
    //控件初始化
    widget = new QWidget;
    btnRed = new QPushButton("Red(F1)",this);
    btnRed->setFixedSize(115, 65);    //设置按钮大小
    btnRed->setShortcut(QKeySequence("F1"));      //设置快捷键
    btnMark = new QPushButton("Mark(F2)", this);
    btnMark->setFixedSize(115, 65);
    btnMark->setShortcut(QKeySequence("F2"));
    checkBoxContinuousMark = new QCheckBox("Continuous Mark", this);
    checkBoxSelectMark = new QCheckBox("Select Mark", this);
    checkBoxAutoRed = new QCheckBox("Auto Red", this);
    label00 = new QLabel("00:00:00.000",this);
    label00->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    labelPart = new QLabel("Part", this);
    labelTotal = new QLabel("Total", this);
    lineEditPart = new QLineEdit("0",this);
    lineEditPart->setFixedWidth(80);
    lineEditTotal = new QLineEdit("1",this);
    lineEditTotal->setFixedWidth(80);
    btnR = new QPushButton("R", this);
    btnR->setFixedWidth(30);
    btnRepeatMark = new QPushButton("RepeatMark", this);
    btnConfig = new QPushButton("Config(F3)", this);
    btnConfig->setShortcut(QKeySequence("F3"));
    checkBoxRedOutline = new QCheckBox("Red Outline", this);
    checkBoxContinuousRedMode = new QCheckBox("Continuous Red Mode", this);

    //设置布局
    gridLayout = new QGridLayout;
    gridLayout->addWidget(btnRed, 0, 0, 2, 1);
    gridLayout->addWidget(btnMark, 0, 1, 2, 1);
    gridLayout->addWidget(checkBoxContinuousMark,0,2);
    gridLayout->addWidget(checkBoxSelectMark,1,2);
    gridLayout->addWidget(checkBoxAutoRed,0,3);
    gridLayout->addWidget(label00,1,3);
    gridLayout->addWidget(labelPart, 0, 5);
    gridLayout->addWidget(labelTotal, 1, 5);
    gridLayout->addWidget(lineEditPart, 0, 6);
    gridLayout->addWidget(lineEditTotal, 1, 6);
    gridLayout->addWidget(btnR, 0, 7);
    gridLayout->addWidget(btnRepeatMark, 0, 8);
    gridLayout->addWidget(btnConfig, 1, 8);
    gridLayout->addWidget(checkBoxRedOutline,0,9);
    gridLayout->addWidget(checkBoxContinuousRedMode,1,9);

    widget->setLayout(gridLayout);
    this->setWidget(widget);
    this->setFixedHeight(80);
}

void BottomDockWidget::initSignalAndSlots()
{
    connect(btnRed,&QPushButton::clicked,this,&BottomDockWidget::BtnRedSlot);
    connect(btnMark,&QPushButton::clicked,this,&BottomDockWidget::BtnMarkSlot);
    connect(btnConfig,&QPushButton::clicked,this,&BottomDockWidget::ConfigSlot);
    connect(btnRepeatMark,&QPushButton::clicked,this,&BottomDockWidget::RepeatMarkSlot);
    connect(btnR,&QPushButton::clicked,this,&BottomDockWidget::BtnRSlot);
}

void BottomDockWidget::BtnRedSlot()
{
    qDebug() << "you clicked PushButton Red(F1)";
}

void BottomDockWidget::BtnMarkSlot()
{
    qDebug() << "you clicked PushButton Mark(F2)";

}

void BottomDockWidget::ConfigSlot()
{
    qDebug() << "you clicked PushButton Config(F3)";
    ConfigWidget* configWidget = new ConfigWidget;
    configWidget->show();
}

void BottomDockWidget::RepeatMarkSlot()
{
    qDebug() << "you clicked PushButton RepeatMark";
    AdvancedWidget * advancedWidget = new AdvancedWidget;
    advancedWidget->show();
}

void BottomDockWidget::BtnRSlot()
{
    qDebug() << "R";
}

