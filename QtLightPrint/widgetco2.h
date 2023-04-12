#ifndef WIDGETCO2_H
#define WIDGETCO2_H

#include <QWidget>
#include <QGroupBox>
#include <QCheckBox>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

class WidgetCO2 : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetCO2(QWidget *parent = nullptr);

    void initUI();

    QGroupBox* grpBoxPWM;
    QCheckBox* checkBoxEnable;
    QLabel* labelMax;
    QLineEdit* lineEditMax;
    QLabel* labelMaxKhz;
    QLabel* labelMin;
    QLineEdit* lineEditMin;
    QLabel* labelMinKhz;
    QPushButton* btnPowerMapping1;
    QCheckBox* checkBoxEnablePre;
    QLabel* labelPulseWidth;
    QLineEdit* lineEditPulseWidth;
    QLabel* labelMicron;
    QLabel* labelPulseFrequency;
    QLineEdit* lineEditPulseFrequency;
    QLabel* labelPulseFrequencyKhz;
    QCheckBox* checkBoxEnablePower;
    QLabel* labelInitial;
    QLineEdit* lineEditInitial;
    QLabel* labelInitialPercent;
    QLabel* labelFirst;
    QLineEdit* lineEditFirst;
    QLabel* labelFirstPercent;

    QGroupBox* grpBoxAnalog;
    QCheckBox* checkBoxEnablePowerAnalog;
    QPushButton* btnPowerMapping2;

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
    QHBoxLayout* layoutBottom;
    QGridLayout* layout;    //整体布局

signals:

};

#endif // WIDGETCO2_H
