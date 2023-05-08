#include "advancedwidget.h"
#include <QDebug>
#include <QColorDialog>

AdvancedWidget::AdvancedWidget(QWidget *parent) : QWidget(parent)
{
    initUI();

    connect(btnReset,&QPushButton::clicked,this,&AdvancedWidget::ResetSlot);
    connect(btnSet,&QPushButton::clicked,this,&AdvancedWidget::SetSlot);
    connect(btnOk,&QPushButton::clicked,this,&AdvancedWidget::OkSlot);
    connect(btnCancel,&QPushButton::clicked,this,&AdvancedWidget::CancelSlot);
    connect(btnColor,&QPushButton::clicked,this,&AdvancedWidget::ShowColor);
}

void AdvancedWidget::initUI()
{
    this->setWindowTitle(tr("Pen number Config"));
    this->setFixedSize(QSize(1114,853));
    setAttribute(Qt::WA_ShowModal, true);

    //控件初始化
    grpBoxAdvanced = new QGroupBox(tr("Advanced Configs"));
    grpBoxAdvanced->setAlignment(Qt::AlignHCenter);     //设置标题居中
    grpBox1 = new QGroupBox;
    grpBox2 = new QGroupBox;
    grpBoxJump = new QGroupBox(tr("Jump delay Range"));
    grpBox3 = new QGroupBox;
    grpBox4 = new QGroupBox;

    labelCurrentPen = new QLabel(tr("Current pen number"));
    labelCurrentPen->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    labelConfig = new QLabel(tr("Config name"));
    labelConfig->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    checkBoxOpen = new QCheckBox;
    labelColor = new QLabel(tr("color"));
    labelColor->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    //Number of processing (pieces)
    labelNumber = new QLabel(tr("Number of processing(pieces)"));
    labelNumber->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    labelSpeed = new QLabel(tr("Speed(mm/s)"));
    labelSpeed->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    labelPower = new QLabel(tr("power(%)"));
    labelCurrent = new QLabel(tr("current(A)"));
    labelCurrent->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    labelFrequency = new QLabel(tr("Frequeecy(KHZ)"));
    labelFrequency->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    labelMOPA = new QLabel(tr("MOPA pulse width(ns)"));
    labelMOPA->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    labelQ = new QLabel(tr("Q pulse width(us)"));
    labelQ->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    labelOpening = new QLabel(tr("Opening delay(us)"));
    labelOpening->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    labelOff = new QLabel(tr("Off light delay(us)"));
    labelOff->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    labelEnd = new QLabel(tr("End delay(us)"));
    labelEnd->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    labelCorner = new QLabel(tr("Corner delay(us)"));
    labelCorner->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    labelMark = new QLabel(tr("Mark step(mm)"));
    labelMark->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    labelInter = new QLabel(tr("Inter-step delay(us)"));
    labelInter->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    lineEditCurrentPen = new QLineEdit(tr("0"));
    lineEditConfig = new QLineEdit(tr("Default"));
    btnColor = new QPushButton;
    //btnColor->setAutoFillBackground(true);   //设置自动填充部件背景
    frameColor = new QFrame;
    //frameColor->set
//    frameColor = new QFrame;
//    frameColor->setFrameShape(QFrame::Box);
//    frameColor->setAutoFillBackground(true);
    lineEditNumber = new QLineEdit(tr("1"));
    lineEditNumber->setFixedWidth(120);
    lineEditSpeed = new QLineEdit(tr("1000"));
    lineEditSpeed->setFixedWidth(120);
    lineEditPower = new QLineEdit(tr("75"));
    lineEditPower->setFixedWidth(120);
    lineEditCurrent = new QLineEdit(tr("1"));
    lineEditCurrent->setFixedWidth(120);
    lineEditFrequency = new QLineEdit(tr("30"));
    lineEditFrequency->setFixedWidth(120);
    lineEditMOPA = new QLineEdit(tr("10"));
    lineEditMOPA->setFixedWidth(120);
    lineEditQ = new QLineEdit(tr("1"));
    lineEditQ->setFixedWidth(120);
    lineEditOpening = new QLineEdit(tr("0"));
    lineEditOpening->setFixedWidth(120);
    lineEditOff = new QLineEdit(tr("100"));
    lineEditOff->setFixedWidth(120);
    lineEditEnd = new QLineEdit(tr("50"));
    lineEditEnd->setFixedWidth(120);
    lineEditCorner = new QLineEdit(tr("80"));
    lineEditCorner->setFixedWidth(120);
    lineEditMark = new QLineEdit(tr("0.02"));
    lineEditMark->setFixedWidth(120);
    lineEditInter = new QLineEdit(tr("100"));
    lineEditInter->setFixedWidth(120);

    labelJumpSpeed = new QLabel(tr("Jump speed"));
    labelJumpPosition = new QLabel(tr("Jump position"));
    labelJumpDistance = new QLabel(tr("Jump distance"));
    lineEditJumpSpeed = new QLineEdit(tr("4000"));
    lineEditJumpSpeed->setFixedWidth(100);
    lineEditJumpPosition = new QLineEdit(tr("500"));
    lineEditJumpPosition->setFixedWidth(100);
    lineEditJumpDistance = new QLineEdit(tr("100"));
    lineEditJumpDistance->setFixedWidth(100);
    labelJumpMms = new QLabel(tr("mm/s"));
    labelJumpUs = new QLabel(tr("us"));
    labelJumpUsmm = new QLabel(tr("us/mm"));

    labelMinimum = new QLabel(tr("minimum"));
    labelMaximum1 = new QLabel(tr("maximum"));
    labelMaximum2 = new QLabel(tr("maximum(space)"));
    lineEditMin = new QLineEdit(tr("20"));
    lineEditMin->setFixedWidth(100);
    lineEditMax1 = new QLineEdit(tr("500"));
    lineEditMax1->setFixedWidth(100);
    lineEditMax2 = new QLineEdit(tr("20"));
    lineEditMax2->setFixedWidth(100);
    labelMinUs = new QLabel(tr("us"));
    labelMaxUs = new QLabel(tr("us"));
    labelMaxMm = new QLabel(tr("mm"));

    checkBoxVector = new QCheckBox(tr("Vector dot patter"));
    labelNumberOf = new QLabel(tr("Number of"));
    lineEditNumberOf = new QLineEdit(tr("1"));
    lineEditNumberOf->setFixedWidth(100);

    labelOpeningLag = new QLabel(tr("Opening lag"));
    lineEditOpeningLag = new QLineEdit(tr("0"));
    lineEditOpeningLag->setFixedWidth(100);
    labelOpeningLagUs = new QLabel(tr("us"));

    labelDotting = new QLabel(tr("Dotting time"));
    lineEditDotting = new QLineEdit(tr("0.1"));
    lineEditDotting->setFixedWidth(100);
    labelDottingMs = new QLabel(tr("ms"));

    checkBoxJitter = new QCheckBox(tr("Jitter"));
    labelRound = new QLabel(tr("Round"));
    lineEditRound = new QLineEdit(tr("1"));
    lineEditRound->setFixedWidth(100);
    labelRoundMm = new QLabel(tr("mm"));
    labelSpacing = new QLabel(tr("spacing"));
    lineEditSpacing = new QLineEdit(tr("0.5"));
    lineEditSpacing->setFixedWidth(100);
    labelSpacingMm = new QLabel(tr("mm"));

    btnReset= new QPushButton(tr("Reset"));
    btnSet = new QPushButton(tr("Set as default pen number"));
    btnOk = new QPushButton(tr("OK"));
    btnCancel = new QPushButton(tr("Cancel"));

    //设置布局
    //左侧区域布局
    layoutLeft = new QGridLayout;
    layoutLeft->addWidget(labelCurrentPen,0,0);
    layoutLeft->addWidget(lineEditCurrentPen,0,1);
    layoutLeft->addWidget(labelConfig);
    layoutLeft->addWidget(lineEditConfig);
    layoutLeft->addWidget(labelColor);
    layoutLeft->addWidget(btnColor);
    layoutLeft->addWidget(labelNumber);
    layoutLeft->addWidget(lineEditNumber);
    layoutLeft->addWidget(labelSpeed);
    layoutLeft->addWidget(lineEditSpeed);
    layoutLeft->addWidget(labelPower);
    layoutLeft->addWidget(lineEditPower);
    layoutLeft->addWidget(labelCurrent);
    layoutLeft->addWidget(lineEditCurrent);
    layoutLeft->addWidget(labelFrequency);
    layoutLeft->addWidget(lineEditFrequency);
    layoutLeft->addWidget(labelMOPA);
    layoutLeft->addWidget(lineEditMOPA);
    layoutLeft->addWidget(labelQ);
    layoutLeft->addWidget(lineEditQ);
    layoutLeft->addWidget(labelOpening);
    layoutLeft->addWidget(lineEditOpening);
    layoutLeft->addWidget(labelOff);
    layoutLeft->addWidget(lineEditOff);
    layoutLeft->addWidget(labelEnd);
    layoutLeft->addWidget(lineEditEnd);
    layoutLeft->addWidget(labelCorner);
    layoutLeft->addWidget(lineEditCorner);
    layoutLeft->addWidget(labelMark);
    layoutLeft->addWidget(lineEditMark);
    layoutLeft->addWidget(labelInter);
    layoutLeft->addWidget(lineEditInter);
    grpBox1->setLayout(layoutLeft);

    //中部区域布局
    layoutGrpBox2 = new QGridLayout;
    layoutGrpBox2->addWidget(labelJumpSpeed,0,0);
    layoutGrpBox2->addWidget(lineEditJumpSpeed,0,1);
    layoutGrpBox2->addWidget(labelJumpMms,0,2);
    layoutGrpBox2->addWidget(labelJumpPosition);
    layoutGrpBox2->addWidget(lineEditJumpPosition);
    layoutGrpBox2->addWidget(labelJumpUs);
    layoutGrpBox2->addWidget(labelJumpDistance);
    layoutGrpBox2->addWidget(lineEditJumpDistance);
    layoutGrpBox2->addWidget(labelJumpUsmm);
    grpBox2->setLayout(layoutGrpBox2);

    layoutJump = new QGridLayout;
    layoutJump->addWidget(labelMinimum,0,0);
    layoutJump->addWidget(lineEditMin,0,1);
    layoutJump->addWidget(labelMinUs,0,2);
    layoutJump->addWidget(labelMaximum1);
    layoutJump->addWidget(lineEditMax1);
    layoutJump->addWidget(labelMaxUs);
    layoutJump->addWidget(labelMaximum2);
    layoutJump->addWidget(lineEditMax2);
    layoutJump->addWidget(labelMaxMm);
    grpBoxJump->setLayout(layoutJump);

    layoutGrpBox3 = new QGridLayout;
    layoutGrpBox3->addWidget(checkBoxVector,0,0,1,2);
    layoutGrpBox3->addWidget(labelNumberOf,1,0);
    layoutGrpBox3->addWidget(lineEditNumberOf,1,1);
    grpBox3->setLayout(layoutGrpBox3);

    layoutOpening = new QHBoxLayout;
    layoutOpening->addWidget(labelOpeningLag);
    layoutOpening->addWidget(lineEditOpeningLag);
    layoutOpening->addWidget(labelOpeningLagUs);

    layoutDotting = new QHBoxLayout;
    layoutDotting->addWidget(labelDotting);
    layoutDotting->addWidget(lineEditDotting);
    layoutDotting->addWidget(labelDottingMs);

    layoutCentre= new QVBoxLayout;
    layoutCentre->addWidget(grpBox2);
    layoutCentre->addWidget(grpBoxJump);
    layoutCentre->addWidget(grpBox3);
    layoutCentre->addLayout(layoutOpening);
    layoutCentre->addLayout(layoutDotting);
    layoutCentre->addStretch();


    //右侧区域布局
    layoutRight = new QVBoxLayout;
    layoutGrpBox4 = new QGridLayout;
    layoutGrpBox4->addWidget(checkBoxJitter,0,0,1,3);
    layoutGrpBox4->addWidget(labelRound,1,0);
    layoutGrpBox4->addWidget(lineEditRound,1,1);
    layoutGrpBox4->addWidget(labelRoundMm,1,2);
    layoutGrpBox4->addWidget(labelSpacing,2,0);
    layoutGrpBox4->addWidget(lineEditSpacing,2,1);
    layoutGrpBox4->addWidget(labelSpacingMm,2,2);
    layoutGrpBox4->setSizeConstraint(QLayout::SetFixedSize);
    grpBox4->setLayout(layoutGrpBox4);
    layoutRight->addWidget(grpBox4);
    layoutRight->addStretch();

    //底部按钮布局
    layoutBottom = new QHBoxLayout;
    layoutBottom->addWidget(btnReset);
    layoutBottom->addWidget(btnSet);
    layoutBottom->addWidget(btnOk);
    layoutBottom->addWidget(btnCancel);

    //顶部布局
    layoutTop = new QHBoxLayout;
    layoutTop->addWidget(grpBox1);
    layoutTop->addLayout(layoutCentre);
    layoutTop->addLayout(layoutRight);
    grpBoxAdvanced->setLayout(layoutTop);

    //整体布局
    layout = new QVBoxLayout;
    layout->addWidget(grpBoxAdvanced);
    layout->addLayout(layoutBottom);
    this->setLayout(layout);


}

void AdvancedWidget::ShowColor()
{
//    QColor c = QColorDialog::getColor(Qt::black);
//    if(c.isValid())
//    {
//        btnColor->setPalette(QPalette(c));
//    }

}

void AdvancedWidget::ResetSlot()
{
    qDebug() << "Reset";
}

void AdvancedWidget::SetSlot()
{
    qDebug() << "Set as default pen number";
}

void AdvancedWidget::OkSlot()
{
    qDebug() << "OK";
}

void AdvancedWidget::CancelSlot()
{
    this->close();
}
