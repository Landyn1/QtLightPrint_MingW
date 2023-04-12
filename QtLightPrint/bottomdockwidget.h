#ifndef BOTTOMDOCKWIDGET_H
#define BOTTOMDOCKWIDGET_H

#include <QDockWidget>
#include <QPushButton>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>


class BottomDockWidget : public QDockWidget
{
public:
   QPushButton* btnRed;
   QPushButton* btnMark;
   QCheckBox* checkBoxContinuousMark;
   QCheckBox* checkBoxSelectMark;
   QCheckBox* checkBoxAutoRed;
   QLabel* label00;
   QLabel* labelPart;
   QLabel* labelTotal;
   QLineEdit* lineEditPart;
   QLineEdit* lineEditTotal;
   QPushButton* btnR;
   QPushButton* btnRepeatMark;
   QPushButton* btnConfig;
   QCheckBox* checkBoxRedOutline;
   QCheckBox* checkBoxContinuousRedMode;

   QWidget * widget;
   QGridLayout* gridLayout;

    BottomDockWidget();
    void initUI();       //初始化界面
    void initSignalAndSlots();
public slots:
    void BtnRedSlot();
    void BtnMarkSlot();
    void ConfigSlot();
    void RepeatMarkSlot();
    void BtnRSlot();
};

#endif // BOTTOMDOCKWIDGET_H
