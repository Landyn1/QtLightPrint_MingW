#include "Widgets/dialogpasswordsetting.h"
#include <QDebug>

DialogPasswordSetting::DialogPasswordSetting()
{
    //初始化界面
    initUI();
    //连接信号和槽
    connect(btnOk,&QPushButton::clicked,this,&DialogPasswordSetting::btnOkSlot);
    connect(btnCancel,&QPushButton::clicked,this,&DialogPasswordSetting::btnCancelSlot);
    connect(btnCancel,&QPushButton::clicked,this,&DialogPasswordSetting::btnDeleteSlot);
}

void DialogPasswordSetting::initUI()
{
    setWindowTitle(tr("Password setting"));
    setWindowFlags(Qt::WindowCloseButtonHint);   //去掉标题栏的"?"，只显示"X"

    labelPassword = new QLabel(tr("Password"));
    lineEditPassword1 = new QLineEdit;
    lineEditPassword2 = new QLineEdit;
    btnOk = new QPushButton(tr("OK"));
    btnCancel = new QPushButton(tr("Cancel"));
    btnDelete = new QPushButton(tr("Delete"));

    layout = new QGridLayout(this);
    layout->addWidget(labelPassword,0,0);
    layout->addWidget(lineEditPassword1,1,0);
    layout->addWidget(lineEditPassword2,2,0);
    layout->addWidget(btnOk,0,2);
    layout->addWidget(btnCancel,1,2);
    layout->addWidget(btnDelete,2,2);

}

void DialogPasswordSetting::btnOkSlot()
{
    qDebug() << "OK";
}

void DialogPasswordSetting::btnCancelSlot()
{
    this->close();
}

void DialogPasswordSetting::btnDeleteSlot()
{
    qDebug() << "Delete";
}
