#ifndef CONFIGTABWIDGETPORT_H
#define CONFIGTABWIDGETPORT_H

#include <QWidget>
#include <QGroupBox>
#include <QLabel>
#include <QCheckBox>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>

class ConfigTabWidgetPort : public QWidget
{
    Q_OBJECT
public:
    explicit ConfigTabWidgetPort(QWidget *parent = nullptr);

    void initUI();
    void initComboBoxOutput(QComboBox * &);
    void initComboBoxInput(QComboBox * &);

    QGroupBox* grpBoxStop;
    QLabel* labelPromptMessageWhen;
    QCheckBox* checkBox0;
    QCheckBox* checkBox1;
    QCheckBox* checkBox2;
    QLabel* labelStopOutputPort;
    QComboBox* comboBoxStopOutputPort;
    QPushButton* btnStop1;
    QLabel* labelPulseWidth;
    QLineEdit* lineEditPulseWidth;
    QLabel* labelMs;

    QGroupBox* grpBoxDoor;
    QLabel* labelInputPort;
    QComboBox* comboBoxInputPort;
    QPushButton* btnDoor1;
    QCheckBox* checkBoxEnableMarkPauseMode;
    QComboBox* comboBoxEnableMarkPauseMode;
    QPushButton* btnDoor2;

    QGroupBox* grpBoxLaserReady;
    QLabel* labelLaserOutputPort;
    QComboBox* comboBoxLaserOutputPort;
    QPushButton* btnLaserReady1;
    QLabel* labelLaserInputPort;
    QComboBox* comboBoxLaserInputPort;
    QPushButton* btnLaserReady2;

    QGroupBox* grpBoxLaserPower;
    QLabel* labelPort;
    QComboBox* comboBoxPort;
    QPushButton* btnLaserPower;

    QGroupBox* grpBoxRed;
    QLabel* labelOutput;
    QComboBox* comboBoxOutput;
    QPushButton* btnRedOutput;
    QLabel* labelRedInputPort;
    QComboBox* comboBoxRedInputPort;
    QPushButton* btnRedInputPort;

    QGroupBox* grpBoxMarkOutput;
    QLabel* labelMarkOutput;
    QComboBox* comboBoxMarkOutput;
    QPushButton* btnMarkOutput;

    QGroupBox* grpBoxMarkEnd;
    QLabel* labelMarkEnd;
    QComboBox* comboBoxMarkEnd;
    QPushButton* btnMarkEnd;
    QLabel* labelPulse;
    QLineEdit* lineEditPulse;
    QLabel* labelPulsems;

    QGroupBox* grpBoxStart;
    QLabel* labelStartInputPort;
    QComboBox* comboBoxStartInputPort;
    QPushButton* btnStartInputPort;
    QCheckBox* checkBoxStart;

    QLabel* labelFilter;
    QLineEdit* lineEditFilter;


    //布局
    QGridLayout * layoutStopBottom;     //grpBoxStop底部布局
    QVBoxLayout * layoutStop;           //grpBoxStop整体布局
    QGridLayout * layoutDoor;
    QGridLayout * layoutLaserReady;
    QHBoxLayout * layoutLaserPower;
    QGridLayout * layoutRed;
    QHBoxLayout * layoutMarkOutput;
    QGridLayout * layoutMarkEnd;
    QGridLayout * layoutStart;

    //整体布局
    QVBoxLayout * layoutLeft;
    QVBoxLayout * layoutRight;
    QHBoxLayout * layoutBottom;
    QGridLayout * layout;



signals:

};

#endif // CONFIGTABWIDGETPORT_H
