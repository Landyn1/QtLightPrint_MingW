#include "Widgets/widgetco2.h"

WidgetCO2::WidgetCO2(QWidget *parent) : QWidget(parent)
{
    initUI();
}

void WidgetCO2::initUI()
{
    grpBoxPWM = new QGroupBox("PWM");
    checkBoxEnable = new QCheckBox(tr("Enabel PWM signal output"));
    labelMax = new QLabel(tr("Max PWM signal"));
    lineEditMax = new QLineEdit("200.000");
    lineEditMax->setFixedWidth(100);
    labelMaxKhz = new QLabel("KHZ");
    labelMin = new QLabel(tr("Min PWM signal"));
    lineEditMin = new QLineEdit("20.000");
    lineEditMin->setFixedWidth(100);
    labelMinKhz = new QLabel("KHZ");
    btnPowerMapping1 = new QPushButton(tr("Power mapping"));
    checkBoxEnablePre = new QCheckBox(tr("Enable pre-ionizatio"));
    labelPulseWidth = new QLabel(tr("Pulse Width"));
    lineEditPulseWidth = new QLineEdit("1");
    lineEditPulseWidth->setFixedWidth(100);
    labelMicron = new QLabel(tr("Micron"));
    labelPulseFrequency = new QLabel(tr("Pulse frequency"));
    lineEditPulseFrequency = new QLineEdit("5.000");
    lineEditPulseFrequency->setFixedWidth(100);
    labelPulseFrequencyKhz = new QLabel("KHZ");
    checkBoxEnablePower = new QCheckBox(tr("Enable power ramp up/slow down"));
    labelInitial = new QLabel(tr("Initial power"));
    lineEditInitial = new QLineEdit("100.0");
    lineEditInitial->setFixedWidth(100);
    labelInitialPercent = new QLabel("%");
    labelFirst = new QLabel(tr("First pulse suppression"));
    lineEditFirst = new QLineEdit("1.0");
    lineEditFirst->setFixedWidth(100);
    labelFirstPercent = new QLabel("%");

    grpBoxAnalog = new QGroupBox(tr("Analog output"));
    checkBoxEnablePowerAnalog = new QCheckBox(tr("Enable power analog port output"));
    btnPowerMapping2 = new QPushButton(tr("Power mapping"));
    btnPowerMapping2->setFixedSize(QSize(205,40));

    checkBoxDoes = new QCheckBox(tr("Does not detect the laser feedback signal"));
    checkBoxLight = new QCheckBox(tr("Light leakage treament"));
    labelTurn = new QLabel(tr("Turn on the MO"));
    lineEditTurn = new QLineEdit("8");
    lineEditTurn->setFixedWidth(100);
    labelMs = new QLabel("ms");

    btnTest = new QPushButton(tr("Test laser"));
    btnTest->setFixedSize(QSize(150,60));

    layoutPWM = new QGridLayout(grpBoxPWM);
    layoutPWM->addWidget(checkBoxEnable,0,0,1,3);
    layoutPWM->addWidget(labelMax,1,0);
    layoutPWM->addWidget(lineEditMax,1,1);
    layoutPWM->addWidget(labelMaxKhz,1,2);
    layoutPWM->addWidget(labelMin);
    layoutPWM->addWidget(lineEditMin);
    layoutPWM->addWidget(labelMinKhz);
    layoutPWM->addWidget(btnPowerMapping1,3,0,1,2);
    layoutPWM->addWidget(checkBoxEnablePre,4,0,1,2);
    layoutPWM->addWidget(labelPulseWidth,5,0);
    layoutPWM->addWidget(lineEditPulseWidth,5,1);
    layoutPWM->addWidget(labelMicron,5,2);
    layoutPWM->addWidget(labelPulseFrequency);
    layoutPWM->addWidget(lineEditPulseFrequency);
    layoutPWM->addWidget(checkBoxEnablePower,7,0,1,3);
    layoutPWM->addWidget(labelInitial);
    layoutPWM->addWidget(lineEditInitial);
    layoutPWM->addWidget(labelInitialPercent);
    layoutPWM->addWidget(labelFirst);
    layoutPWM->addWidget(lineEditFirst);
    layoutPWM->addWidget(labelFirstPercent);


    layoutAnalog = new QHBoxLayout(grpBoxAnalog);
    layoutAnalog->addWidget(checkBoxEnablePowerAnalog);
    layoutAnalog->addWidget(btnPowerMapping2);
    layoutAnalog->setSizeConstraint(QLayout::SetFixedSize);

    layoutRight = new QGridLayout;
    layoutRight->addWidget(checkBoxDoes,0,0,1,3);
    layoutRight->addWidget(checkBoxLight,1,0,1,3);
    layoutRight->addWidget(labelTurn,2,0);
    layoutRight->addWidget(lineEditTurn,2,1);
    layoutRight->addWidget(labelMs,2,2);
    layoutRight->setSizeConstraint(QLayout::SetFixedSize);

    layoutBottom = new QHBoxLayout;
    layoutBottom->addWidget(grpBoxAnalog);
    layoutBottom->addWidget(btnTest);

    layout = new QGridLayout(this);
    layout->addWidget(grpBoxPWM);
    layout->addLayout(layoutRight,0,1);
    layout->addLayout(layoutBottom,1,0,1,2);

}
