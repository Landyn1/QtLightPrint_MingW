#ifndef CONFIGTABWIDGETOTHER_H
#define CONFIGTABWIDGETOTHER_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QGridLayout>

class ConfigTabWidgetOther : public QWidget
{
    Q_OBJECT
public:
    explicit ConfigTabWidgetOther(QWidget *parent = nullptr);

    void initUI();

    QLabel* labelStartMarkDelay;
    QLineEdit* lineEditStartMarkDelay;
    QLabel *labelStartMarkDelayms;

    QLabel* labelEndMarkDelay;
    QLineEdit* lineEditEndMarkDelay;
    QLabel* labelEndMarkDelayms;

    QLabel* labelMaxSpeed;
    QLineEdit* lineEditMaxSpeed;
    QLabel* labelMaxSpeedmms;

    QLabel* labelMinSpeed;
    QLineEdit* lineEditMinSpeed;
    QLabel* labelMinSpeedmms;

    QCheckBox* checkBoxShowStartMarkDialog;

    QCheckBox* checkBoxProhibit;

    QLabel* labelTotalProcessing;
    QLabel* labelTotalProcessingNum;
    QLabel* labelms;

    QLabel* labelTotalNumberOf;
    QLabel* labelTotalNumberOfNum;

    QCheckBox* checkBoxSingleFileMode;

    QCheckBox* checkBoxContinuousMakingOfMovingShapes;

    QCheckBox* checkBoxPowerFailureAutomaticProtectionFile;

    QGridLayout * layout;

signals:

};

#endif // CONFIGTABWIDGETOTHER_H
