#include "configtabwidgetlasercontrol.h"
#include <QDebug>

ConfigTabWidgetLaserControl::ConfigTabWidgetLaserControl(QWidget *parent) : QWidget(parent)
{
    initUI();
    connect(btnGroup, QOverload<int, bool>::of(&QButtonGroup::buttonToggled),
        this,&ConfigTabWidgetLaserControl::LaserTypeSlot);
}

void ConfigTabWidgetLaserControl::initUI()
{

    grpBoxLaserType = new QGroupBox(tr("Laser type"));

    radioBtnCO2 = new QRadioButton(("CO2"));
    radioBtnYAG = new QRadioButton(("YAG"));
    radioBtnFiber = new QRadioButton(("Fiber"));
    radioBtnUV = new QRadioButton(("UV"));
//    radioBtnUV->setChecked(true);     //设置UV为默认选中状态

    //将Laser type中的4种type作为一组统一管理,这样可以不用挨个设置信号槽的连接
    btnGroup = new QButtonGroup(this);
    btnGroup->addButton(radioBtnCO2,0);
    btnGroup->addButton(radioBtnYAG,1);
    btnGroup->addButton(radioBtnFiber,2);
    btnGroup->addButton(radioBtnUV,3);

    layoutLaserType = new QHBoxLayout;
    layoutLaserType->addWidget(radioBtnCO2);
    layoutLaserType->addWidget(radioBtnYAG);
    layoutLaserType->addWidget(radioBtnFiber);
    layoutLaserType->addWidget(radioBtnUV);
    layoutLaserType->setSizeConstraint(QLayout::SetFixedSize);
    grpBoxLaserType->setLayout(layoutLaserType);

    //整体布局
    layout = new QVBoxLayout;
    layout->addWidget(grpBoxLaserType);

    widgetCO2 = new WidgetCO2(this);
    widgetYAG = new WidgetYAG(this);
    widgetFiber = new WidgetFiber(this);
    widgetUV = new WidgetUV(this);
    widgetCO2->hide();
    widgetYAG->hide();
    widgetFiber->hide();
    widgetUV->hide();

    //后续工作是通过读取文件，默认显示文件中保存的widget类型
    int x = 0;    //该值通过读取文件获得，这里先设置为为1，表示默认laser type = CO2
    switch(x)
    {
    case 0:
        radioBtnCO2->setChecked(true);
        widgetCO2->show();
        layout->addWidget(widgetCO2);
        break;
    case 1:
        radioBtnYAG->setChecked(true);
        widgetYAG->show();
        layout->addWidget(widgetYAG);
        break;
    case 2:
        radioBtnFiber->setChecked(true);
        widgetFiber->show();
        layout->addWidget(widgetFiber);
        break;
    case 3:
        radioBtnUV->setChecked(true);
        widgetUV->show();
         layout->addWidget(widgetUV);
        break;
    }

    layout->setSizeConstraint(QLayout::SetFixedSize);
    this->setLayout(layout);
}

void ConfigTabWidgetLaserControl::LaserTypeSlot(int id)
{
    switch(id)
    {
    case 0:
        if(radioBtnCO2->isChecked())
        {
            widgetYAG->hide();
            widgetFiber->hide();
            widgetUV->hide();
            layout->addWidget(widgetCO2);
            widgetCO2->show();
        }
        break;
    case 1:
        if(radioBtnYAG->isChecked())
        {
            widgetCO2->hide();
            widgetFiber->hide();
            widgetUV->hide();
            layout->addWidget(widgetYAG);
            widgetYAG->show();
        }
        break;
    case 2:
        if(radioBtnFiber->isChecked())
        {
            widgetCO2->hide();
            widgetYAG->hide();
            widgetUV->hide();
            layout->addWidget(widgetFiber);
            widgetFiber->show();
        }
        break;
    case 3:
        if(radioBtnUV->isChecked())
        {
            widgetCO2->hide();
            widgetYAG->hide();
            widgetFiber->hide();
            layout->addWidget(widgetUV);
            widgetUV->show();
        }
        break;
    }
}
