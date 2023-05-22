#include "widgetuv.h"

WidgetUV::WidgetUV(QWidget *parent) : QWidget(parent)
{
    initUI();
}

void WidgetUV::initUI()
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
    btnCurrent = new QPushButton(tr("Current mapping"));
    btnCurrent->setFixedSize(QSize(205,40));

    checkBoxDoes = new QCheckBox(tr("Does not detect the laser feedback signal"));
    checkBoxLight = new QCheckBox(tr("Light leakage treament"));
    labelTurn = new QLabel(tr("Turn on the MO delay"));
    lineEditTurn = new QLineEdit("8");
    lineEditTurn->setFixedWidth(100);
    labelMs = new QLabel("ms");

    grpBoxSwitch = new QGroupBox(tr("switch"));
    checkBoxEnableThe = new QCheckBox(tr("Enable the first pulse \nsuppression of the simulation"));
    lineEditEnableThe = new QLineEdit("20");
    lineEditEnableThe->setFixedWidth(100);
    labelEnableTheUs = new QLabel("us");
    checkBoxOpen = new QCheckBox(tr("Open Q switch when the first \npuls suppression ends"));
    checkBoxPulse =new QCheckBox(tr("Pulse width reversal"));
    checkBoxEnablePulse = new QCheckBox(tr("Enable pulse width setting"));
    checkBoxRed = new QCheckBox(tr("Red Light Mode of Viol"));

    grpBoxQ = new QGroupBox(tr("Q pulse width"));
    labelMinQ = new QLabel(tr("Min Q pulse"));
    lineEditMinQ = new QLineEdit("0");
    lineEditMinQ->setFixedWidth(100);
    labelMinUs = new QLabel("us");
    labelMaxQ = new QLabel(tr("Max Q pulse"));
    lineEditMaxQ = new QLineEdit("200");
    lineEditMaxQ->setFixedWidth(100);
    labelMaxQUs =new QLabel("us");

    btnTest = new QPushButton(tr("Test laser"));
    btnTest->setFixedSize(QSize(150,60));

    layoutPWM = new QGridLayout(grpBoxPWM);
    layoutPWM->addWidget(checkBoxEnable,0,0,1,3);
    layoutPWM->addWidget(labelMax,1,0);
    layoutPWM->addWidget(lineEditMax,1,1);
    layoutPWM->addWidget(labelMaxKhz,1,2);
    layoutPWM->addWidget(labelMin,2,0);
    layoutPWM->addWidget(lineEditMin,2,1);
    layoutPWM->addWidget(labelMinKhz,2,2);
    layoutPWM->addWidget(labelInitial);
    layoutPWM->addWidget(lineEditInitial);
    layoutPWM->addWidget(labelInitialPercent);
    layoutPWM->addWidget(labelFirst);
    layoutPWM->addWidget(lineEditFirst);
    layoutPWM->addWidget(labelFirstPercent);

    layoutAnalog = new QHBoxLayout(grpBoxAnalog);
    layoutAnalog->addWidget(checkBoxEnablePowerAnalog);
    layoutAnalog->addWidget(btnCurrent);
    layoutAnalog->setSizeConstraint(QLayout::SetFixedSize);

    layoutSwitch = new QGridLayout(grpBoxSwitch);
    layoutSwitch->addWidget(checkBoxEnableThe,0,0);
    layoutSwitch->addWidget(lineEditEnableThe,0,1);
    layoutSwitch->addWidget(labelEnableTheUs,0,2);
    layoutSwitch->addWidget(checkBoxOpen,1,0,1,3);
    layoutSwitch->addWidget(checkBoxPulse,2,0);
    layoutSwitch->addWidget(checkBoxEnablePulse,3,0);
    layoutSwitch->addWidget(checkBoxRed,4,0);

    layoutQ = new QGridLayout(grpBoxQ);
    layoutQ->addWidget(labelMinQ,0,0);
    layoutQ->addWidget(lineEditMinQ,0,1);
    layoutQ->addWidget(labelMinUs,0,2);
    layoutQ->addWidget(labelMaxQ);
    layoutQ->addWidget(lineEditMaxQ);
    layoutQ->addWidget(labelMaxQUs);
    layoutQ->setSizeConstraint(QLayout::SetFixedSize);

    layoutRight = new QGridLayout;
    layoutRight->addWidget(checkBoxDoes,0,0,1,3);
    layoutRight->addWidget(checkBoxLight,1,0,1,3);
    layoutRight->addWidget(labelTurn,2,0);
    layoutRight->addWidget(lineEditTurn,2,1);
    layoutRight->addWidget(labelMs,2,2);
    layoutRight->addWidget(grpBoxSwitch,3,0,1,3);
    layoutRight->addWidget(grpBoxQ,4,0,1,3);

    layoutBottom = new QHBoxLayout;
    layoutBottom->addWidget(grpBoxAnalog);
    layoutBottom->addWidget(btnTest);

    layout = new QGridLayout(this);
    layout->addWidget(grpBoxPWM);
    layout->addLayout(layoutRight,0,1);
    layout->addLayout(layoutBottom,1,0,1,2,Qt::AlignLeft);

}
