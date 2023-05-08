#include "configtabwidget.h"

ConfigTabWidget::ConfigTabWidget()
{
   initUI();
}

void ConfigTabWidget::initUI()
{

    //初始化每一个Tab
    this->widgetArea = new ConfigTabWidgetArea;
    this->widgetLaserControl = new ConfigTabWidgetLaserControl;
    this->widgetPort = new ConfigTabWidgetPort;
    this->widgetOther = new ConfigTabWidgetOther;
    this->widgetRed = new ConfigTabWidgetRed;

    //插入每个Tab
    insertTab(0, widgetArea,tr("区域"));
    insertTab(1, widgetLaserControl, tr("Laser Control"));
    insertTab(2,widgetPort,tr("port"));
    insertTab(3,widgetOther,tr("other"));
    insertTab(4,widgetRed,tr("Red"));
}
