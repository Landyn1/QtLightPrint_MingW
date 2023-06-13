#include "Widgets/dialogcalculationratio.h"
#include <QDebug>

DialogCalculationRatio::DialogCalculationRatio()
{
    initUI();
    //初始化信号和槽
    connect(btnOk,&QPushButton::clicked,this,&DialogCalculationRatio::btnOkSlot);
    connect(btnCancel,&QPushButton::clicked,this,&DialogCalculationRatio::btnCancelSlot);
}

void DialogCalculationRatio::initUI()
{
    setWindowTitle(tr("Calculation ratio"));
    setWindowFlags(Qt::WindowCloseButtonHint);   //去掉标题栏的"?"，只显示"X"

    labelTarget = new QLabel(tr("Target Mark size"));
    labelActual = new QLabel(tr("Actual Mark size"));
    lineEditTarget = new QLineEdit("80");
    lineEditActual =new QLineEdit("80");
    btnOk = new QPushButton(tr("OK"));
    btnCancel = new QPushButton(tr("Cancel"));

    layout = new QGridLayout(this);
    layout->addWidget(labelTarget,0,0);
    layout->addWidget(btnOk,0,2);
    layout->addWidget(lineEditTarget,1,0);
    layout->addWidget(labelActual,2,0);
    layout->addWidget(btnCancel,2,2);
    layout->addWidget(lineEditActual,3,0);
}

void DialogCalculationRatio::btnOkSlot()
{
    qDebug() << "OK";
}

void DialogCalculationRatio::btnCancelSlot()
{
    this->close();
}
