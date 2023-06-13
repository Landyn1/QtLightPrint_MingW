#ifndef ADVANCEDWIDGET_H
#define ADVANCEDWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>
#include <QCheckBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

class AdvancedWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AdvancedWidget(QWidget *parent = nullptr);

    QGroupBox* grpBoxAdvanced;
    QGroupBox* grpBox1;
    QGroupBox* grpBox2;
    QGroupBox* grpBoxJump;
    QGroupBox* grpBox3;
    QGroupBox* grpBox4;

    QLabel * labelCurrentPen;
    QLabel * labelConfig;
    QCheckBox* checkBoxOpen;
    QLabel * labelColor;
    //Number of processing (pieces)
    QLabel* labelNumber;
    QLabel* labelSpeed;
    QLabel* labelPower;
    QLabel* labelCurrent;
    QLabel* labelFrequency;
    QLabel* labelMOPA;
    QLabel* labelQ;
    QLabel* labelOpening;
    QLabel* labelOff;
    QLabel* labelEnd;
    QLabel* labelCorner;
    QLabel* labelMark;
    QLabel* labelInter;

    QLineEdit* lineEditCurrentPen;
    QLineEdit* lineEditConfig;
    QPushButton * btnColor;
    QFrame* frameColor;
    QLineEdit* lineEditNumber;
    QLineEdit* lineEditSpeed;
    QLineEdit* lineEditPower;
    QLineEdit* lineEditCurrent;
    QLineEdit* lineEditFrequency;
    QLineEdit* lineEditMOPA;
    QLineEdit* lineEditQ;
    QLineEdit* lineEditOpening;
    QLineEdit* lineEditOff;
    QLineEdit* lineEditEnd;
    QLineEdit* lineEditCorner;
    QLineEdit* lineEditMark;
    QLineEdit* lineEditInter;

    QLabel* labelJumpSpeed;
    QLabel* labelJumpPosition;
    QLabel* labelJumpDistance;
    QLineEdit* lineEditJumpSpeed;
    QLineEdit* lineEditJumpPosition;
    QLineEdit* lineEditJumpDistance;
    QLabel* labelJumpMms;
    QLabel* labelJumpUs;
    QLabel* labelJumpUsmm;

    QLabel* labelMinimum;
    QLabel* labelMaximum1;
    QLabel* labelMaximum2;
    QLineEdit* lineEditMin;
    QLineEdit* lineEditMax1;
    QLineEdit* lineEditMax2;
    QLabel* labelMinUs;
    QLabel* labelMaxUs;
    QLabel* labelMaxMm;

    QCheckBox* checkBoxVector;
    QLabel* labelNumberOf;
    QLineEdit* lineEditNumberOf;

    QLabel* labelOpeningLag;
    QLineEdit* lineEditOpeningLag;
    QLabel* labelOpeningLagUs;

    QLabel* labelDotting;
    QLineEdit* lineEditDotting;
    QLabel* labelDottingMs;

    QCheckBox* checkBoxJitter;
    QLabel* labelRound;
    QLineEdit* lineEditRound;
    QLabel* labelRoundMm;
    QLabel* labelSpacing;
    QLineEdit* lineEditSpacing;
    QLabel* labelSpacingMm;

    QPushButton* btnReset;
    QPushButton* btnSet;
    QPushButton* btnOk;
    QPushButton* btnCancel;

    //布局
    QGridLayout* layoutLeft;
    QGridLayout* layoutGrpBox2;
    QGridLayout* layoutJump;
    QGridLayout* layoutGrpBox3;
    QGridLayout* layoutGrpBox4;
    QVBoxLayout* layoutCentre;
    QHBoxLayout* layoutOpening;
    QHBoxLayout* layoutDotting;
    QVBoxLayout* layoutRight;
    QHBoxLayout* layoutBottom;
    QHBoxLayout* layoutTop;
    QVBoxLayout* layout;

    void initUI();


    //槽函数
    void ShowColor();
    void ResetSlot();
    void SetSlot();
    void OkSlot();
    void CancelSlot();


signals:

};

#endif // ADVANCEDWIDGET_H
