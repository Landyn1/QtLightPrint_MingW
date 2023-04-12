#include "configtabwidgetarea.h"
#include "dialogcalculationratio.h"
#include "dialogpasswordsetting.h"
#include "dialogcalculaterecommendvalues.h"
#include <QFileDialog>
#include <QDebug>

ConfigTabWidgetArea::ConfigTabWidgetArea(QWidget *parent) : QWidget(parent)
{
    //初始化界面
    initUI();

    //建立信号和槽的连接
    connect(btnUse,&QPushButton::clicked,this,&ConfigTabWidgetArea::btnUseSlot);
    connect(propertyXBtn,&QPushButton::clicked,this,&ConfigTabWidgetArea::proportyXBtnSlot);
    connect(propertyYBtn,&QPushButton::clicked,this,&ConfigTabWidgetArea::proportyYBtnSlot);
    connect(btnConfigFileLocation,&QPushButton::clicked,this,&ConfigTabWidgetArea::btnConfigFileLocationSlot);
    connect(btnSaveConfigAs,&QPushButton::clicked,this,&ConfigTabWidgetArea::btnSaveConfigAsSlot);
    connect(btnPassword,&QPushButton::clicked,this,&ConfigTabWidgetArea::btnPasswordSlot);
    connect(btnCalculateRecommendValues,&QPushButton::clicked,this,&ConfigTabWidgetArea::btnCalculateRecommendValuesSlot);
}

void ConfigTabWidgetArea::initUI()
{
    QPixmap icon1(":/res/Config_1.png");
    QPixmap icon2(":/res/Config_2.png");
    QPixmap icon3(":/res/Config_3.png");

    //1.给grpBoxExterior添加控件
    grpBoxExterior = new QGroupBox("Exterior");
    labelAreaSize = new QLabel("Area size", grpBoxExterior);
    lineEditAreaSize = new QLineEdit("120.000", grpBoxExterior);
    lineEditAreaSize->setFixedWidth(100);
    lineEditMaxLine = new QLineEdit("2", grpBoxExterior);
    lineEditMaxLine->setFixedWidth(100);
    labelMaxLine = new QLabel("Max line", grpBoxExterior);
    labelmm1 = new QLabel("mm", grpBoxExterior);
    labelmm2 = new QLabel("mm", grpBoxExterior);
    labelmm3 = new QLabel("mm", grpBoxExterior);
    labelmm4 = new QLabel("mm", grpBoxExterior);
    labelOffsetX = new QLabel("Offset X", grpBoxExterior);
    labelOffsetY = new QLabel("Offset Y", grpBoxExterior);
    labelAngle = new QLabel("angle", grpBoxExterior);
    lineEditOffsetX = new QLineEdit("2.0000", grpBoxExterior);
    lineEditOffsetX->setFixedWidth(100);
    lineEditOffsetY = new QLineEdit("0.0000", grpBoxExterior);
    lineEditOffsetY->setFixedWidth(100);
    lineEditAngle = new QLineEdit("0.0000", grpBoxExterior);
    lineEditAngle->setFixedWidth(100);
    labelPoint = new QLabel(".", grpBoxExterior);
    //1.给grpBoxExterior进行布局
    gridLayoutExterior = new QGridLayout(grpBoxExterior);
    gridLayoutExterior->addWidget(labelAreaSize, 0, 0);
    gridLayoutExterior->addWidget(lineEditAreaSize,0,1);
    gridLayoutExterior->addWidget(labelMaxLine,2,0);
    gridLayoutExterior->addWidget(lineEditMaxLine,2,1);
    gridLayoutExterior->addWidget(labelmm1,0,2);
    gridLayoutExterior->addWidget(labelmm2, 2, 2);
    gridLayoutExterior->addWidget(labelOffsetX,0,3);
    gridLayoutExterior->addWidget(labelOffsetY,1,3);
    gridLayoutExterior->addWidget(lineEditOffsetX,0,4);
    gridLayoutExterior->addWidget(lineEditOffsetY,1,4);
    gridLayoutExterior->addWidget(labelAngle,2,3);
    gridLayoutExterior->addWidget(lineEditAngle,2,4);
    gridLayoutExterior->addWidget(labelmm3, 0, 5);
    gridLayoutExterior->addWidget(labelmm4, 1, 5);
    gridLayoutExterior->addWidget(labelPoint, 2, 5);
    gridLayoutExterior->setSizeConstraint(QLayout::SetFixedSize);
    grpBoxExterior->setLayout(gridLayoutExterior);

    //2. 给Use calibration file行三个控件初始化
    checkBoxUseCalibrationFile = new QCheckBox("Use calibration file");
    lineEdit = new QLineEdit;
    btnUse = new QPushButton(">>");
    btnUse->setFixedWidth(30);
    //2. 给Use calibration file行三个控件布局
    layoutUse = new QHBoxLayout;
    layoutUse->addWidget(checkBoxUseCalibrationFile);
    layoutUse->addWidget(lineEdit);
    layoutUse->addWidget(btnUse);
    layoutUse->setSizeConstraint(QLayout::SetFixedSize);

    //3. 给grpReverse初始化控件
    grpBoxReverse = new QGroupBox;
    checkBoxXYInterchange = new QCheckBox("XY interchange");
    checkBoxXreverse = new QCheckBox("X reverse");
    checkBoxYreverse = new QCheckBox("Y reverse");
    //3. 给grpReverse布局
    layoutReverse = new QHBoxLayout;
    layoutReverse->addWidget(checkBoxXYInterchange);
    layoutReverse->addWidget(checkBoxXreverse);
    layoutReverse->addWidget(checkBoxYreverse);
    layoutReverse->setSizeConstraint(QLayout::SetFixedSize);
    grpBoxReverse->setLayout(layoutReverse);

    //4. 给grpBoxX添加控件
    grpBoxX =  new QGroupBox("X");
    labelXProperty = new QLabel("property", grpBoxX);
    lineEditXProperty = new QLineEdit("100.000000", grpBoxX);
    lineEditXProperty->setFixedWidth(100);
    propertyXBtn = new QPushButton(">>", grpBoxX);
    propertyXBtn->setFixedWidth(30);
    labelX1 = new QLabel(grpBoxX);
    labelX1->setPixmap(icon1);
    labelX1->resize(icon1.size());
    labelX2 = new QLabel(grpBoxX);
    labelX2->setPixmap(icon2);
    labelX2->resize(icon2.size());
    labelX3 = new QLabel(grpBoxX);
    labelX3->setPixmap(icon3);
    labelX3->resize(icon3.size());
    lineEditX1 = new QLineEdit("1.000000", grpBoxX);
    lineEditX1->setFixedWidth(100);
    lineEditX2 = new QLineEdit("1.000000", grpBoxX);
    lineEditX2->setFixedWidth(100);
    lineEditX3 = new QLineEdit("1.000000", grpBoxX);
    lineEditX3->setFixedWidth(100);
    //4. 给grpBoxX布局
    layoutX = new QGridLayout(grpBoxX);
    layoutX->addWidget(labelXProperty, 0, 0);
    layoutX->addWidget(lineEditXProperty, 0, 1);
    layoutX->addWidget(propertyXBtn, 0, 2);
    layoutX->addWidget(labelX1, 1, 0);
    layoutX->addWidget(labelX2, 2, 0);
    layoutX->addWidget(labelX3, 3, 0);
    layoutX->addWidget(lineEditX1, 1, 1);
    layoutX->addWidget(lineEditX2, 2, 1);
    layoutX->addWidget(lineEditX3, 3, 1);
    layoutX->setSizeConstraint(QLayout::SetFixedSize);

    //5. 给grpBoxY添加控件
    grpBoxY = new QGroupBox("Y");
    labelYProperty = new QLabel("property", grpBoxY);
    lineEditYProperty = new QLineEdit("100.000000", grpBoxY);
    lineEditYProperty->setFixedWidth(100);
    propertyYBtn = new QPushButton(">>", grpBoxY);
    propertyYBtn->setFixedWidth(30);
    labelY1 = new QLabel(grpBoxY);
    labelY1->setPixmap(icon1);
    labelY1->resize(icon1.size());
    labelY2 = new QLabel(grpBoxY);
    labelY2->setPixmap(icon2);
    labelY2->resize(icon2.size());
    labelY3 = new QLabel(grpBoxY);
    labelY3->setPixmap(icon3);
    labelY3->resize(icon3.size());
    lineEditY1 = new QLineEdit("1.000000", grpBoxY);
    lineEditY1->setFixedWidth(100);
    lineEditY2 = new QLineEdit("1.000000", grpBoxY);
    lineEditY2->setFixedWidth(100);
    lineEditY3 = new QLineEdit("1.000000", grpBoxY);
    lineEditY3->setFixedWidth(100);
    //5. 给grpBoxY布局
    layoutY = new QGridLayout(grpBoxY);
    layoutY->addWidget(labelYProperty, 0, 0);
    layoutY->addWidget(lineEditYProperty, 0, 1);
    layoutY->addWidget(propertyYBtn, 0, 2);
    layoutY->addWidget(labelY1, 1, 0);
    layoutY->addWidget(labelY2, 2, 0);
    layoutY->addWidget(labelY3, 3, 0);
    layoutY->addWidget(lineEditY1, 1, 1);
    layoutY->addWidget(lineEditY2, 2, 1);
    layoutY->addWidget(lineEditY3, 3, 1);
    layoutY->setSizeConstraint(QLayout::SetFixedSize);

    //6.
    checkBoxEqualProportionMethod = new QCheckBox("Equal proportion method");
    checkBoxEqualProportionMethod->setCheckState(Qt::Checked);
    labelProportional = new QLabel("Proportional");
    lineEditProportional = new QLineEdit("25");
    lineEditProportional->setFixedWidth(70);
    btnSetX = new QPushButton("Set X-scale Config");
    btnSetY = new QPushButton("Set Y-scale Config");
    //6.Proportional行水平布局
    layoutProportional = new QHBoxLayout;
    layoutProportional->addWidget(labelProportional);
    layoutProportional->addWidget(lineEditProportional);
    layoutProportional->addWidget(btnSetX);
    layoutProportional->addWidget(btnSetY);

    //7.
    checkBoxUseConfigurationFile = new QCheckBox("Use configuration file");
    lineEditConfigFileLocation = new QLineEdit;
    //lineEditConfigFileLocation->setFixedWidth(350);
    btnConfigFileLocation = new QPushButton(">>");
    btnConfigFileLocation->setFixedWidth(30);
    btnSaveConfigAs = new QPushButton("Save Config as");
    layoutUseConfigurationFile = new QGridLayout;
    //layoutUseConfigurationFile->setColumnStretch
    layoutUseConfigurationFile->addWidget(checkBoxUseConfigurationFile,0,0);
    layoutUseConfigurationFile->addWidget(lineEditConfigFileLocation,1,0);
    layoutUseConfigurationFile->addWidget(btnConfigFileLocation,1,7);
    layoutUseConfigurationFile->addWidget(btnSaveConfigAs,1,8);
    layoutUseConfigurationFile->setSizeConstraint(QLayout::SetFixedSize);

    //8. 给grpBoxGo添加控件
    grpBoxGo = new QGroupBox("Go to the Designated Location After Mark");
    radioBtnDoNotMove = new QRadioButton("Do not move", grpBoxGo);
    radioBtnGalvanicCenter = new QRadioButton("Galvanic center", grpBoxGo);
    radioBtnTopLeftCornerOfTheProject = new QRadioButton("Top left corner of the project", grpBoxGo);
    radioBtnObjectUpperRightCorner = new QRadioButton("Object upper right corner", grpBoxGo);
    radioBtnObjectBottomRightCorner = new QRadioButton("Object bottom right corner", grpBoxGo);
    radioBtnLowerLeftCornerOfTheProject = new QRadioButton("Lower left corner of the project", grpBoxGo);
    radioBtnSpecifiedLocation = new QRadioButton("Specified location", grpBoxGo);
    labelX = new QLabel("X", grpBoxGo);
    labelY = new QLabel("Y", grpBoxGo);
    lineEditX = new QLineEdit("0.0000", grpBoxGo);
    lineEditX->setFixedWidth(100);
    lineEditY = new QLineEdit("0.0000", grpBoxGo);
    lineEditY->setFixedWidth(100);
    //8. 给grpBoxGo进行垂直布局
    layoutGo = new QVBoxLayout;
    layoutGo->addWidget(radioBtnDoNotMove);
    layoutGo->addWidget(radioBtnGalvanicCenter);
    layoutGo->addWidget(radioBtnTopLeftCornerOfTheProject);
    layoutGo->addWidget(radioBtnObjectUpperRightCorner);
    layoutGo->addWidget(radioBtnObjectBottomRightCorner);
    layoutGo->addWidget(radioBtnLowerLeftCornerOfTheProject);
    layoutGo->addWidget(radioBtnSpecifiedLocation);
    layoutGoX = new QHBoxLayout;
    layoutGoX->addWidget(labelX);
    layoutGoX->addWidget(lineEditX);
    layoutGoX->setSizeConstraint(QLayout::SetFixedSize);
    layoutGoY = new QHBoxLayout;
    layoutGoY->addWidget(labelY);
    layoutGoY->addWidget(lineEditY);
    layoutGo->addLayout(layoutGoX);
    layoutGo->addLayout(layoutGoY);
    grpBoxGo->setLayout(layoutGo);
    layoutGo->setSizeConstraint(QLayout::SetFixedSize);

    //9.
    btnCalculateRecommendValues = new QPushButton("Calculate recommend values");
    btnCalculateRecommendValues->setFixedSize(QSize(250,80));

    //10. 给grpBoxPassWord添加控件
    grpBoxPassWord = new QGroupBox("password");
    btnPassword = new QPushButton("Password");
    btnPassword->setFixedSize(QSize(130,50));
    //10. 给grpBoxPassWord设置布局
    layoutPassword = new QHBoxLayout;
    layoutPassword->addWidget(btnPassword,0,Qt::AlignHCenter);
    grpBoxPassWord->setLayout(layoutPassword);

    //grpBoxX,grpBoxY布局
    layoutXY = new QHBoxLayout;
    layoutXY->addWidget(grpBoxX);
    layoutXY->addWidget(grpBoxY);

    //左侧布局
    layoutLeft = new QVBoxLayout;
    layoutLeft->addWidget(grpBoxExterior);
    layoutLeft->addLayout(layoutUse);
    layoutLeft->addWidget(grpBoxReverse);
    layoutLeft->addLayout(layoutXY);
    layoutLeft->addWidget(checkBoxEqualProportionMethod);
    layoutLeft->addLayout(layoutProportional);
    layoutLeft->addLayout(layoutUseConfigurationFile);

    //右侧布局
    layoutRight = new QVBoxLayout;
    layoutRight->addWidget(grpBoxGo);
    layoutRight->addWidget(btnCalculateRecommendValues,0,Qt::AlignCenter);
    layoutRight->addWidget(grpBoxPassWord);
    layoutRight->setSizeConstraint(QLayout::SetFixedSize);

    //整体布局
    layout = new QHBoxLayout;
    layout->addLayout(layoutLeft);
    layout->addLayout(layoutRight);
    this->setLayout(layout);
}

void ConfigTabWidgetArea::btnUseSlot()
{
    QString path = QFileDialog::getOpenFileName(this,"Open",".","Cali Files(*.cor)");
    if(!path.isEmpty())
        qDebug() << path;
}

void ConfigTabWidgetArea::proportyXBtnSlot()
{
    DialogCalculationRatio* dialog = new DialogCalculationRatio;
    dialog->open();
}

void ConfigTabWidgetArea::proportyYBtnSlot()
{
    DialogCalculationRatio* dialog = new DialogCalculationRatio;
    dialog->open();
}

void ConfigTabWidgetArea::btnConfigFileLocationSlot()
{
    QString path = QFileDialog::getOpenFileName(this,"Open",".","Config Files(*.cfg)");
    if(!path.isEmpty())
        qDebug() << path;
}

void ConfigTabWidgetArea::btnSaveConfigAsSlot()
{
    QFileDialog::getSaveFileName(this,"Save As",".","All Files(*.*)");
}

void ConfigTabWidgetArea::btnCalculateRecommendValuesSlot()
{
    DialogCalculateRecommendValues* dialog = new DialogCalculateRecommendValues;
    dialog->open();
}

void ConfigTabWidgetArea::btnPasswordSlot()
{
    DialogPasswordSetting* dialog = new DialogPasswordSetting;
    dialog->open();

}
