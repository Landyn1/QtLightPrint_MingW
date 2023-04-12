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
    insertTab(0, widgetArea, "area");
    insertTab(1, widgetLaserControl, "Laser Control");
    insertTab(2,widgetPort,"port");
    insertTab(3,widgetOther,"other");
    insertTab(4,widgetRed,"Red");
}
