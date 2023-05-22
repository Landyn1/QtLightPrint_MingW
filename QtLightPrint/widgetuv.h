#ifndef WIDGETUV_H
#define WIDGETUV_H

#include <QWidget>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

class WidgetUV : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetUV(QWidget *parent = nullptr);

    QGroupBox* grpBoxPWM;
    QCheckBox* checkBoxEnable;
    QLabel* labelMax;
    QLineEdit* lineEditMax;
    QLabel* labelMaxKhz;
    QLabel* labelMin;
    QLineEdit* lineEditMin;
    QLabel* labelMinKhz;
    QLabel* labelInitial;
    QLineEdit* lineEditInitial;
    QLabel* labelInitialPercent;
    QLabel* labelFirst;
    QLineEdit* lineEditFirst;
    QLabel* labelFirstPercent;

    QGroupBox* grpBoxAnalog;
    QCheckBox* checkBoxEnablePowerAnalog;
    QPushButton* btnCurrent;

    QGroupBox* grpBoxSwitch;
    QCheckBox* checkBoxEnableThe;
    QLineEdit* lineEditEnableThe;
    QLabel* labelEnableTheUs;
    QCheckBox* checkBoxOpen;
    QCheckBox* checkBoxPulse;
    QCheckBox* checkBoxEnablePulse;
    QCheckBox* checkBoxRed;

    QGroupBox* grpBoxQ;
    QLabel* labelMinQ;
    QLineEdit* lineEditMinQ;
    QLabel* labelMinUs;
    QLabel* labelMaxQ;
    QLineEdit* lineEditMaxQ;
    QLabel* labelMaxQUs;


    QCheckBox* checkBoxDoes;
    QCheckBox* checkBoxLight;
    QLabel* labelTurn;
    QLineEdit* lineEditTurn;
    QLabel* labelMs;

    QPushButton* btnTest;

    //布局
    QGridLayout* layoutPWM;
    QHBoxLayout* layoutAnalog;
    QGridLayout* layoutRight;
    QGridLayout* layoutSwitch;
    QGridLayout* layoutQ;
    QHBoxLayout* layoutBottom;
    QGridLayout* layout;    //整体布局

    void initUI();

signals:

};

#endif // WIDGETUV_H
