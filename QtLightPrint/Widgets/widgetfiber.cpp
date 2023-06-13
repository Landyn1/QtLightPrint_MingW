#include "Widgets/widgetfiber.h"

WidgetFiber::WidgetFiber(QWidget *parent) : QWidget(parent)
{
    initUI();
}

void WidgetFiber::initUI()
{
    grpBoxPWM = new QGroupBox("PWM",this);
    labelMax = new QLabel(tr("Max PWM signal"),this);
    lineEditMax = new QLineEdit("200.000",this);
    lineEditMax->setFixedWidth(100);
    labelMaxKhz = new QLabel("KHZ");
    labelMin = new QLabel(tr("Min PWM signal"));
    lineEditMin = new QLineEdit("20.000");
    lineEditMin->setFixedWidth(100);
    labelMinKhz = new QLabel("KHZ");
    btnPowerMapping = new QPushButton(tr("Power mapping"));

    grpBoxFiber = new QGroupBox(tr("Fiber"));
    labelTypes = new QLabel(tr("Types of"));
    comboBoxTypes = new QComboBox;
    QStringList types = {"IPG-YLP","IPG-YLPM","RAYCUS","QUANTEL_M20HF","QUANTEL_M20","MANLIGHT_PL","VGEN_YPFL","JPT","EO"};
    comboBoxTypes->addItems(types);

    checkBoxDoes = new QCheckBox(tr("Does not detect the laser feedback signal"));
    checkBoxLight = new QCheckBox(tr("Light leakage treament"));
    labelTurn = new QLabel(tr("Turn on the MO"));
    lineEditTurn = new QLineEdit("8");
    lineEditTurn->setFixedWidth(100);
    labelMs = new QLabel("ms");

    btnTest = new QPushButton(tr("Test laser"));
    btnTest->setFixedSize(QSize(150,60));

    layoutPWM = new QGridLayout(grpBoxPWM);
    layoutPWM->addWidget(labelMax,1,0);
    layoutPWM->addWidget(lineEditMax,1,1);
    layoutPWM->addWidget(labelMaxKhz,1,2);
    layoutPWM->addWidget(labelMin);
    layoutPWM->addWidget(lineEditMin);
    layoutPWM->addWidget(labelMinKhz);
    layoutPWM->addWidget(btnPowerMapping,3,0,1,2);

    layoutFiber = new QHBoxLayout(grpBoxFiber);
    layoutFiber->addWidget(labelTypes);
    layoutFiber->addWidget(comboBoxTypes);

    layoutRight = new QGridLayout;
    layoutRight->addWidget(checkBoxDoes,0,0,1,3);
    layoutRight->addWidget(checkBoxLight,1,0,1,3);
    layoutRight->addWidget(labelTurn,2,0);
    layoutRight->addWidget(lineEditTurn,2,1);
    layoutRight->addWidget(labelMs,2,2);
    layoutRight->addWidget(grpBoxFiber,3,0,1,3);
    layoutRight->setSizeConstraint(QLayout::SetFixedSize);

    layoutTop = new QHBoxLayout;
    layoutTop->addWidget(grpBoxPWM);
    layoutTop->addLayout(layoutRight);

    layout = new QVBoxLayout(this);
    layout->addLayout(layoutTop);
    layout->addWidget(btnTest,0,Qt::AlignRight);
}
