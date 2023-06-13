#include "Widgets/dialogcalculaterecommendvalues.h"
#include <QDebug>

DialogCalculateRecommendValues::DialogCalculateRecommendValues()
{
    //初始化界面
    initUI();
    //连接信号和槽
    connect(btnCalculate,&QPushButton::clicked,this,&DialogCalculateRecommendValues::btnCalculateSlot);
    connect(btnSure,&QPushButton::clicked,this,&DialogCalculateRecommendValues::btnSureSlot);
}

void DialogCalculateRecommendValues::initUI()
{
    this->setWindowTitle(tr("Recommended Values"));
    setWindowFlags(Qt::WindowCloseButtonHint);

    QPixmap icon1(":/res/Config_1.png");
    QPixmap icon2(":/res/Config_2.png");
    QPixmap icon3(":/res/Config_3.png");
    QPixmap icon4(":/res/CalculateRecommendValuesPic.png");

    grpBoxTheoretical = new QGroupBox(tr("Theoretical Value"));
    labelX = new QLabel("X=");
    labelY = new QLabel("Y=");
    lineEditX = new QLineEdit("0");
    lineEditX->setFixedWidth(100);
    lineEditY = new QLineEdit("0");
    lineEditY->setFixedWidth(100);

    grpBoxMeasured = new QGroupBox(tr("Measured Value"));
    labelA = new QLabel("a=");
    labelX1 = new QLabel("X1=");
    labelX2 = new QLabel("X2=");
    labelX3 = new QLabel("X3=");
    labelY1 = new QLabel("Y1=");
    labelY2 = new QLabel("Y2=");
    labelY3 = new QLabel("Y3=");
    lineEditA = new QLineEdit("0");
    lineEditA->setFixedWidth(100);
    lineEditX1 = new QLineEdit("0");
    lineEditX1->setFixedWidth(100);
    lineEditX2 = new QLineEdit("0");
    lineEditX2->setFixedWidth(100);
    lineEditX3 = new QLineEdit("0");
    lineEditX3->setFixedWidth(100);
    lineEditY1 = new QLineEdit("0");
    lineEditY1->setFixedWidth(100);
    lineEditY2 = new QLineEdit("0");
    lineEditY2->setFixedWidth(100);
    lineEditY3 = new QLineEdit("0");
    lineEditY3->setFixedWidth(100);

    btnCalculate = new QPushButton(tr("Calculate Recommended Values"));
    btnSure = new QPushButton(tr("Sure"));

    grpBoxX = new QGroupBox("X");
    labelProportyX = new QLabel(tr("proporty"));
    labelXPic1 = new QLabel;
    labelXPic1->setPixmap(icon1);
    labelXPic2 = new QLabel;
    labelXPic2->setPixmap(icon2);
    labelXPic3 = new QLabel;
    labelXPic3->setPixmap(icon3);
    lineEditProportyX = new QLineEdit("100");
    lineEditProportyX->setFixedWidth(100);
    lineEditXPic1 = new QLineEdit("1");
    lineEditXPic1->setFixedWidth(100);
    lineEditXPic2 = new QLineEdit("1");
    lineEditXPic2->setFixedWidth(100);
    lineEditXPic3 = new QLineEdit("1");
    lineEditXPic3->setFixedWidth(100);

    grpBoxY = new QGroupBox("X");
    labelProportyY = new QLabel(tr("proporty"));
    labelYPic1 = new QLabel;
    labelYPic1->setPixmap(icon1);
    labelYPic2 = new QLabel;
    labelYPic2->setPixmap(icon2);
    labelYPic3 = new QLabel;
    labelYPic3->setPixmap(icon3);
    lineEditProportyY = new QLineEdit("100");
    lineEditProportyY->setFixedWidth(100);
    lineEditYPic1 = new QLineEdit("1");
    lineEditYPic1->setFixedWidth(100);
    lineEditYPic2 = new QLineEdit("1");
    lineEditYPic2->setFixedWidth(100);
    lineEditYPic3 = new QLineEdit("1");
    lineEditYPic3->setFixedWidth(100);

    labelPic = new QLabel;
    labelPic->setPixmap(icon4);

    layoutGrpBoxTheoretical = new QHBoxLayout(grpBoxTheoretical);
    layoutGrpBoxTheoretical->addWidget(labelX);
    layoutGrpBoxTheoretical->addWidget(lineEditX);
    layoutGrpBoxTheoretical->addWidget(labelY);
    layoutGrpBoxTheoretical->addWidget(lineEditY);

    layoutGrpBoxMeasured = new QGridLayout(grpBoxMeasured);
    layoutGrpBoxMeasured->addWidget(labelA,0,0);
    layoutGrpBoxMeasured->addWidget(labelX1,1,0);
    layoutGrpBoxMeasured->addWidget(labelX2,2,0);
    layoutGrpBoxMeasured->addWidget(labelX3,3,0);
    layoutGrpBoxMeasured->addWidget(lineEditA,0,1);
    layoutGrpBoxMeasured->addWidget(lineEditX1,1,1);
    layoutGrpBoxMeasured->addWidget(lineEditX2,2,1);
    layoutGrpBoxMeasured->addWidget(lineEditX3,3,1);
    layoutGrpBoxMeasured->addWidget(labelY1,1,2);
    layoutGrpBoxMeasured->addWidget(labelY2,2,2);
    layoutGrpBoxMeasured->addWidget(labelY3,3,2);
    layoutGrpBoxMeasured->addWidget(lineEditY1,1,3);
    layoutGrpBoxMeasured->addWidget(lineEditY2,2,3);
    layoutGrpBoxMeasured->addWidget(lineEditY3,3,3);

    layoutGrpBoxX = new QGridLayout(grpBoxX);
    layoutGrpBoxX->addWidget(labelProportyX,0,0);
    layoutGrpBoxX->addWidget(lineEditProportyX,0,1);
    layoutGrpBoxX->addWidget(labelXPic1);
    layoutGrpBoxX->addWidget(lineEditXPic1);
    layoutGrpBoxX->addWidget(labelXPic2);
    layoutGrpBoxX->addWidget(lineEditXPic2);
    layoutGrpBoxX->addWidget(labelXPic3);
    layoutGrpBoxX->addWidget(lineEditXPic3);

    layoutGrpBoxY = new QGridLayout(grpBoxY);
    layoutGrpBoxY->addWidget(labelProportyY,0,0);
    layoutGrpBoxY->addWidget(lineEditProportyY,0,1);
    layoutGrpBoxY->addWidget(labelYPic1);
    layoutGrpBoxY->addWidget(lineEditYPic1);
    layoutGrpBoxY->addWidget(labelYPic2);
    layoutGrpBoxY->addWidget(lineEditYPic2);
    layoutGrpBoxY->addWidget(labelYPic3);
    layoutGrpBoxY->addWidget(lineEditYPic3);

    layoutTop = new QGridLayout;
    layoutTop->addWidget(grpBoxTheoretical,0,0,2,2);
    layoutTop->addWidget(btnCalculate,0,2,1,2);
    layoutTop->addWidget(btnSure,1,2);
    layoutTop->addWidget(labelPic,1,3);

    layoutBottom = new QHBoxLayout;
    layoutBottom->addWidget(grpBoxMeasured);
    layoutBottom->addWidget(grpBoxX);
    layoutBottom->addWidget(grpBoxY);

    layout = new QVBoxLayout(this);
    layout->addLayout(layoutTop);
    layout->addLayout(layoutBottom);
    layout->setSizeConstraint(QLayout::SetFixedSize);
}

void DialogCalculateRecommendValues::btnCalculateSlot()
{
    qDebug() << "Calculate Recommended Values";
}

void DialogCalculateRecommendValues::btnSureSlot()
{
    qDebug() <<"Sure";
}
