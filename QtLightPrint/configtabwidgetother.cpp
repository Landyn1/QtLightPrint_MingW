#include "configtabwidgetother.h"

ConfigTabWidgetOther::ConfigTabWidgetOther(QWidget *parent) : QWidget(parent)
{
    initUI();
}

void ConfigTabWidgetOther::initUI()
{
    //初始化控件
    labelStartMarkDelay = new QLabel("Start Mark delay");
    lineEditStartMarkDelay = new QLineEdit("0");
    lineEditStartMarkDelay->setFixedWidth(80);
    labelStartMarkDelayms = new QLabel("ms");

    labelEndMarkDelay = new QLabel("End Mark delay");
    lineEditEndMarkDelay = new QLineEdit("0");
    lineEditEndMarkDelay->setFixedWidth(80);
    labelEndMarkDelayms = new QLabel("ms");

    labelMaxSpeed = new QLabel("Max speed");
    lineEditMaxSpeed = new QLineEdit("10000.000");
    lineEditMaxSpeed->setFixedWidth(80);
    labelMaxSpeedmms = new QLabel("mm/s");

    labelMinSpeed = new QLabel("Min speed");
    lineEditMinSpeed = new QLineEdit("1.000");
    lineEditMinSpeed->setFixedWidth(80);
    labelMinSpeedmms = new QLabel("mm/s");

    checkBoxShowStartMarkDialog = new QCheckBox("Show start Mark dialog");

    checkBoxProhibit = new QCheckBox("Prohibit processing after processing to the special");

    labelTotalProcessing = new QLabel("Total processing");
    labelTotalProcessingNum = new QLabel("0");
    labelms = new QLabel("ms");

    labelTotalNumberOf = new QLabel("Total number of");
    labelTotalNumberOfNum = new QLabel("0");

    checkBoxSingleFileMode = new QCheckBox("Single file mode");

    checkBoxContinuousMakingOfMovingShapes = new QCheckBox("Continuous making of moving shapes");

    checkBoxPowerFailureAutomaticProtectionFile = new QCheckBox("Power failure automatic protection file");

    //设置布局
    layout = new QGridLayout;
//        //layout->SetFixedSize(QSize(400, 180));
    layout->addWidget(labelStartMarkDelay,0,0);
    layout->addWidget(lineEditStartMarkDelay,0,1);
    layout->addWidget(labelStartMarkDelayms,0,2);

    layout->addWidget(labelEndMarkDelay,1,0);
    layout->addWidget(lineEditEndMarkDelay,1,1);
    layout->addWidget(labelEndMarkDelayms,1,2);

    layout->addWidget(labelMaxSpeed,2,0);
    layout->addWidget(lineEditMaxSpeed,2,1);
    layout->addWidget(labelMaxSpeedmms,2,2);

    layout->addWidget(labelMinSpeed,3,0);
    layout->addWidget(lineEditMinSpeed,3,1);
    layout->addWidget(labelMinSpeedmms,3,2);

    layout->addWidget(checkBoxShowStartMarkDialog,4,0);

    layout->addWidget(checkBoxProhibit,5,0,1,3);

    layout->addWidget(labelTotalProcessing,6,0);
    layout->addWidget(labelTotalProcessingNum,6,1);
    layout->addWidget(labelms,6,2);

    layout->addWidget(labelTotalNumberOf,7,0);
    layout->addWidget(labelTotalNumberOfNum,7,1);

    layout->addWidget(checkBoxSingleFileMode,8,0);

    layout->addWidget(checkBoxContinuousMakingOfMovingShapes,9,0,1,3);

    layout->addWidget(checkBoxPowerFailureAutomaticProtectionFile,10,0,1,3);

    this->setLayout(layout);
    layout->setSizeConstraint(QLayout::SetFixedSize);
//        QVBoxLayout* layoutWidgetOtherAll = new QVBoxLayout;
//        //layoutWidgetOtherAll->addLayout(layout);
//        //layoutWidgetOtherAll->addWidget()
//        widgetOther->setLayout(layout);
}
