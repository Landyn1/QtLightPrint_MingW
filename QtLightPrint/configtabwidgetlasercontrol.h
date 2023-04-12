#ifndef CONFIGTABWIDGETLASERCONTROL_H
#define CONFIGTABWIDGETLASERCONTROL_H

#include <QWidget>
#include <QGroupBox>
#include <QButtonGroup>
#include <QRadioButton>
#include <QHBoxLayout>
#include "widgetco2.h"
#include "widgetyag.h"
#include "widgetfiber.h"
#include "widgetuv.h"

class ConfigTabWidgetLaserControl : public QWidget
{
    Q_OBJECT
public:
    explicit ConfigTabWidgetLaserControl(QWidget *parent = nullptr);

    void initUI();

    QButtonGroup * btnGroup;

    QGroupBox* grpBoxLaserType;

    QRadioButton* radioBtnCO2;
    QRadioButton* radioBtnYAG;
    QRadioButton* radioBtnFiber;
    QRadioButton* radioBtnUV;

    WidgetCO2* widgetCO2;
    WidgetYAG* widgetYAG;
    WidgetFiber* widgetFiber;
    WidgetUV* widgetUV;

    QHBoxLayout* layoutLaserType;
    QVBoxLayout* layout;

    void LaserTypeSlot(int);



signals:

};

#endif // CONFIGTABWIDGETLASERCONTROL_H
