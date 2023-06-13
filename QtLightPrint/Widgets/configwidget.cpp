#include "Widgets/configwidget.h"

ConfigWidget::ConfigWidget(QWidget *parent) : QWidget(parent)
{
    initUI();
}

void ConfigWidget::initUI()
{
    //设置ConfigWidget窗口标题
    this->setWindowTitle(tr("Configuration Config[default]"));
    //设置窗口固定大小
    this->setFixedSize(QSize(1080,980));
    //设置窗口为模态窗口
    setAttribute(Qt::WA_ShowModal, true);

    tabWidget = new ConfigTabWidget;
    tabWidget->setParent(this);
    btnOk = new QPushButton(tr("OK"));
    btnCancel = new QPushButton(tr("Cancel"));

    layoutBottom = new QHBoxLayout;
    layoutBottom->addStretch();
    layoutBottom->addWidget(btnOk);
    layoutBottom->addWidget(btnCancel);

    layout = new QVBoxLayout;
    layout->addWidget(tabWidget);
    layout->addLayout(layoutBottom);
    this->setLayout(layout);

    connect(btnCancel,&QPushButton::clicked,this,&ConfigWidget::SlotCancel);
}

void ConfigWidget::SlotCancel()
{
    this->close();
}
