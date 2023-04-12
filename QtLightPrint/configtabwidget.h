#ifndef CONFIGTABWIDGET_H
#define CONFIGTABWIDGET_H

#include <QTabWidget>
#include "configtabwidgetarea.h"
#include "configtabwidgetlasercontrol.h"
#include "configtabwidgetport.h"
#include "configtabwidgetother.h"
#include "configtabwidgetred.h"
#include <QPushButton>

class ConfigTabWidget : public QTabWidget
{
public:
    ConfigTabWidgetArea * widgetArea;
    ConfigTabWidgetLaserControl* widgetLaserControl;
    ConfigTabWidgetPort* widgetPort;
    ConfigTabWidgetOther* widgetOther;
    ConfigTabWidgetRed* widgetRed;
    ConfigTabWidget();


    void initUI();
};

#endif // CONFIGTABWIDGET_H
