#include "Widgets/configtabwidgetred.h"
#include <QDebug>

ConfigTabWidgetRed::ConfigTabWidgetRed(QWidget *parent) : QWidget(parent)
{
    initUI();
    connect(btnRedPreview,&QPushButton::clicked,this,&ConfigTabWidgetRed::btnRedPreviewSlot);
}

void ConfigTabWidgetRed::initUI()
{
    //初始化控件
    this->groupBox = new QGroupBox;

    this->labelRedLightStyle = new QLabel(tr("Red light style"));
    this->comBox = new QComboBox;
    this->comBox->addItem(tr("Graphic circumscried rectangle"));
    this->comBox->addItem(tr("Graphic outline"));

    this->labelRedLight = new QLabel(tr("Red light"));
    this->lineEditRedLight = new QLineEdit("3000");
    lineEditRedLight->setFixedWidth(100);
    this->labelMms = new QLabel("mm/s");

    this->labelOffsetX = new QLabel(tr("Offset X"));
    this->lineEditOffsetX = new QLineEdit("0.0000");
    lineEditOffsetX->setFixedWidth(100);
    this->labelMm1 = new QLabel("mm");

    this->labelOffsetY = new QLabel(tr("Offset Y"));
    this->lineEditOffsetY = new QLineEdit("0.0000");
    lineEditOffsetY->setFixedWidth(100);
    this->labelMm2 = new QLabel("mm");

    this->labelSizeRatioX = new QLabel(tr("Size ratio X"));
    this->lineEditSizeRatioX = new QLineEdit("1.0000");
    lineEditSizeRatioX->setFixedWidth(100);

    this->labelSizeRatioY = new QLabel(tr("Size ratio Y"));
    this->lineEditSizeRatioY = new QLineEdit("1.0000");
    lineEditSizeRatioY->setFixedWidth(100);

    this->labelTime = new QLabel("00:00:00.000");

    this->checkBoxLaser = new QCheckBox(tr("Laser contains redlight Mode"));
    this->checkBoxEnable = new QCheckBox(tr("Enable red light output all the time"));

    this->btnRedPreview = new QPushButton(tr("Red Preview"));
    btnRedPreview->setFixedSize(QSize(190,90));

    //布局
    //1. 左侧布局
    this->layoutGrpBox = new QGridLayout;
    layoutGrpBox->addWidget(labelRedLightStyle,0,0);
    layoutGrpBox->addWidget(comBox,0,1,1,2);
    layoutGrpBox->addWidget(labelRedLight,1,0);
    layoutGrpBox->addWidget(lineEditRedLight,1,1);
    layoutGrpBox->addWidget(labelMms,1,2);
    layoutGrpBox->addWidget(labelOffsetX,2,0);
    layoutGrpBox->addWidget(lineEditOffsetX,2,1);
    layoutGrpBox->addWidget(labelMm1,2,2);
    layoutGrpBox->addWidget(labelOffsetY,3,0);
    layoutGrpBox->addWidget(lineEditOffsetY,3,1);
    layoutGrpBox->addWidget(labelMm2,3,2);
    layoutGrpBox->addWidget(labelSizeRatioX,4,0);
    layoutGrpBox->addWidget(lineEditSizeRatioX,4,1);
    layoutGrpBox->addWidget(labelSizeRatioY,5,0);
    layoutGrpBox->addWidget(lineEditSizeRatioY,5,1);
    groupBox->setLayout(layoutGrpBox);
    //2.右侧布局
    layoutRight = new QVBoxLayout;
    layoutRight->addWidget(checkBoxLaser);
    layoutRight->addWidget(checkBoxEnable);
    layoutRight->addWidget(btnRedPreview);
    //3.整体布局
    layout = new QGridLayout;
    layout->addWidget(groupBox);
    layout->addLayout(layoutRight,0,1);
    layout->addWidget(labelTime,1,0);
    layout->setSizeConstraint(QLayout::SetFixedSize);
    this->setLayout(layout);
}

void ConfigTabWidgetRed::btnRedPreviewSlot()
{
    qDebug() << "Red Preview";
}
