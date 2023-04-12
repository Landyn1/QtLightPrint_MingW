#include "configtabwidgetport.h"

ConfigTabWidgetPort::ConfigTabWidgetPort(QWidget *parent) : QWidget(parent)
{
    initUI();
}

void ConfigTabWidgetPort::initUI()
{
    //初始化控件
    QPixmap icon1(":/res/high.png");
    QPixmap icon2(":/res/low.png");
    grpBoxStop = new QGroupBox("Stop processing input port");
    labelPromptMessageWhen = new QLabel("Prompt message when");
    checkBox0 = new QCheckBox("0");
    checkBox0->setTristate();    //设置复选框为一个三态复选框
    checkBox0->setCheckState(Qt::PartiallyChecked);  //设置默认状态
    checkBox1 = new QCheckBox("1");
    checkBox1->setTristate();
    checkBox1->setCheckState(Qt::PartiallyChecked);
    checkBox2 = new QCheckBox("2");
    checkBox2->setTristate();
    checkBox2->setCheckState(Qt::PartiallyChecked);
    labelStopOutputPort = new QLabel("Output port");
    initComboBoxOutput(comboBoxStopOutputPort);
    btnStop1 = new QPushButton;
    btnStop1->setIcon(icon1);
    btnStop1->setFixedSize(icon1.size());
    labelPulseWidth = new QLabel("Pulse Width");
    lineEditPulseWidth = new QLineEdit("1");
    lineEditPulseWidth->setFixedWidth(120);
    labelMs = new QLabel("ms");


    grpBoxDoor = new QGroupBox("Door port");
    labelInputPort = new QLabel("Input port");
    initComboBoxInput(comboBoxInputPort);
    btnDoor1 = new QPushButton;
    btnDoor1->setIcon(icon1);
    btnDoor1->setFixedSize(icon1.size());
    checkBoxEnableMarkPauseMode = new QCheckBox("Enable mark pause mode");
    initComboBoxOutput(comboBoxEnableMarkPauseMode);
    btnDoor2 = new QPushButton;
    btnDoor2->setIcon(icon1);
    btnDoor2->setFixedSize(icon1.size());

    grpBoxLaserReady = new QGroupBox("Laser ready port");
    labelLaserOutputPort = new QLabel("Out port");
    comboBoxLaserOutputPort = new QComboBox;
    comboBoxLaserOutputPort->addItem("NULL");
    comboBoxLaserOutputPort->addItem("0");
    comboBoxLaserOutputPort->addItem("1");
    btnLaserReady1 = new QPushButton;
    btnLaserReady1->setIcon(icon1);
    btnLaserReady1->setFixedSize(icon1.size());
    labelLaserInputPort = new QLabel("Input port");
    comboBoxLaserInputPort = new QComboBox;
    comboBoxLaserInputPort->addItem("NULL");
    comboBoxLaserInputPort->addItem("0");
    comboBoxLaserInputPort->addItem("1");
    comboBoxLaserInputPort->addItem("2");
    btnLaserReady2 = new QPushButton;
    btnLaserReady2->setIcon(icon1);
    btnLaserReady2->setFixedSize(icon1.size());

    grpBoxLaserPower = new QGroupBox("Laser power outlet");
    labelPort = new QLabel("port");
    comboBoxPort = new QComboBox;
    initComboBoxOutput(comboBoxPort);
    btnLaserPower = new QPushButton;
    btnLaserPower->setIcon(icon1);
    btnLaserPower->setFixedSize(icon1.size());

    grpBoxRed = new QGroupBox("Red light output");
    labelOutput = new QLabel("Output");
    initComboBoxOutput(comboBoxOutput);
    btnRedOutput = new QPushButton;
    btnRedOutput->setIcon(icon1);
    btnRedOutput->setFixedSize(icon1.size());
    labelRedInputPort = new QLabel("Input port");
    initComboBoxInput(comboBoxRedInputPort);
    btnRedInputPort = new QPushButton;
    btnRedInputPort->setIcon(icon1);
    btnRedInputPort->setFixedSize(icon1.size());

    grpBoxMarkOutput = new QGroupBox("Mark output");
    labelMarkOutput = new QLabel("Output");
    initComboBoxOutput(comboBoxMarkOutput);
    btnMarkOutput = new QPushButton;
    btnMarkOutput->setIcon(icon1);
    btnMarkOutput->setFixedSize(icon1.size());


    grpBoxMarkEnd = new QGroupBox("Mark end output IO");
    labelMarkEnd = new QLabel("Output");
    initComboBoxOutput(comboBoxMarkEnd);
    btnMarkEnd = new QPushButton;
    btnMarkEnd->setIcon(icon1);
    btnMarkEnd->setFixedSize(icon1.size());
    labelPulse = new QLabel("Pulse");
    lineEditPulse = new QLineEdit("1");
    lineEditPulse->setFixedWidth(120);
    labelPulsems = new QLabel("ms");

    grpBoxStart = new QGroupBox("Start Mark port");
    labelStartInputPort = new QLabel("Input port");
    initComboBoxInput(comboBoxStartInputPort);
    btnStartInputPort = new QPushButton;
    btnStartInputPort->setIcon(icon2);
    btnStartInputPort->setFixedSize(icon2.size());
    checkBoxStart = new QCheckBox("Start signal pulse mode");

    labelFilter = new QLabel("Filter time ms");
    lineEditFilter = new QLineEdit("50");
    lineEditFilter->setFixedWidth(120);


    //设置布局
    //1. 设置grpBoxStop的布局
    layoutStopBottom = new QGridLayout;
    layoutStopBottom->addWidget(labelStopOutputPort,0,0);
    layoutStopBottom->addWidget(comboBoxStopOutputPort,0,1);
    layoutStopBottom->addWidget(btnStop1,0,2);
    layoutStopBottom->addWidget(labelPulseWidth,1,0);
    layoutStopBottom->addWidget(lineEditPulseWidth,1,1);
    layoutStopBottom->addWidget(labelMs);
    layoutStop = new QVBoxLayout;
    layoutStop->addWidget(labelPromptMessageWhen);
    layoutStop->addWidget(checkBox0);
    layoutStop->addWidget(checkBox1);
    layoutStop->addWidget(checkBox2);
    layoutStop->addLayout(layoutStopBottom);
    grpBoxStop->setLayout(layoutStop);
    //2. 设置grpBoxDoor的布局
    layoutDoor = new QGridLayout;
    layoutDoor->addWidget(labelInputPort,0,0);
    layoutDoor->addWidget(comboBoxInputPort,0,1);
    layoutDoor->addWidget(btnDoor1,0,2);
    layoutDoor->addWidget(checkBoxEnableMarkPauseMode,1,0);
    layoutDoor->addWidget(comboBoxEnableMarkPauseMode,2,1);
    layoutDoor->addWidget(btnDoor2,2,2);
    grpBoxDoor->setLayout(layoutDoor);
    //3. 设置grpBoxLaserReady的布局
    layoutLaserReady = new QGridLayout;
    layoutLaserReady->addWidget(labelLaserOutputPort,0,0);
    layoutLaserReady->addWidget(comboBoxLaserOutputPort,0,1);
    layoutLaserReady->addWidget(btnLaserReady1,0,2);
    layoutLaserReady->addWidget(labelLaserInputPort,1,0);
    layoutLaserReady->addWidget(comboBoxLaserInputPort,1,1);
    layoutLaserReady->addWidget(btnLaserReady2,1,2);
    grpBoxLaserReady->setLayout(layoutLaserReady);
    //4. 设置grpBoxLaserPower的布局
    layoutLaserPower = new QHBoxLayout;
    layoutLaserPower->addWidget(labelPort);
    layoutLaserPower->addWidget(comboBoxPort);
    layoutLaserPower->addWidget(btnLaserPower);
    grpBoxLaserPower->setLayout(layoutLaserPower);
    //5. 设置grpBoxRed的布局
    layoutRed = new QGridLayout;
    layoutRed->addWidget(labelOutput,0,0);
    layoutRed->addWidget(comboBoxOutput,0,1);
    layoutRed->addWidget(btnRedOutput,0,2);
    layoutRed->addWidget(labelRedInputPort,1,0);
    layoutRed->addWidget(comboBoxRedInputPort,1,1);
    layoutRed->addWidget(btnRedInputPort,1,2);
    grpBoxRed->setLayout(layoutRed);
    //6. 设置grpBoxMarkOutput的布局
    layoutMarkOutput = new QHBoxLayout;
    layoutMarkOutput->addWidget(labelMarkOutput);
    layoutMarkOutput->addWidget(comboBoxMarkOutput);
    layoutMarkOutput->addWidget(btnMarkOutput);
    grpBoxMarkOutput->setLayout(layoutMarkOutput);
    //7. 设置grpBoxMarkEnd的布局
    layoutMarkEnd = new QGridLayout;
    layoutMarkEnd->addWidget(labelMarkEnd,0,0);
    layoutMarkEnd->addWidget(comboBoxMarkEnd,0,1);
    layoutMarkEnd->addWidget(btnMarkEnd,0,2);
    layoutMarkEnd->addWidget(labelPulse,1,0);
    layoutMarkEnd->addWidget(lineEditPulse,1,1);
    layoutMarkEnd->addWidget(labelPulsems,1,2);
    grpBoxMarkEnd->setLayout(layoutMarkEnd);
    //8. 设置grpBoxStart的布局
    layoutStart = new QGridLayout;
    layoutStart->addWidget(labelStartInputPort,0,0);
    layoutStart->addWidget(comboBoxStartInputPort,0,1);
    layoutStart->addWidget(btnStartInputPort,0,2);
    layoutStart->addWidget(checkBoxStart,1,0,1,2);
    grpBoxStart->setLayout(layoutStart);
    //9. 设置底部布局
    layoutBottom = new QHBoxLayout;
    layoutBottom->addWidget(labelFilter);
    layoutBottom->addWidget(lineEditFilter);

    //10. 设置整体布局
    this->layoutLeft = new QVBoxLayout;
    this->layoutRight = new QVBoxLayout;
    this->layout = new QGridLayout;
    layoutLeft->addWidget(grpBoxStop);
    layoutLeft->addWidget(grpBoxDoor);
    layoutLeft->addWidget(grpBoxLaserReady);
    layoutRight->addWidget(grpBoxLaserPower);
    layoutRight->addWidget(grpBoxRed);
    layoutRight->addWidget(grpBoxMarkOutput);
    layoutRight->addWidget(grpBoxMarkEnd);
    layoutRight->addWidget(grpBoxStart);
    layout->addLayout(layoutLeft,0,0);
    layout->addLayout(layoutRight,0,1);
    layout->addLayout(layoutBottom,1,1);
    this->setLayout(layout);
}

void ConfigTabWidgetPort::initComboBoxOutput(QComboBox * & output)
{
        output = new QComboBox;
        output->setFixedWidth(120);
        output->addItem("NULL");
        output->addItem("0");
        output->addItem("1");
}

void ConfigTabWidgetPort::initComboBoxInput(QComboBox * & input)
{
        input = new QComboBox;
        input->setFixedWidth(120);
        input->addItem("NULL");
        input->addItem("0");
        input->addItem("1");
        input->addItem("2");
}
