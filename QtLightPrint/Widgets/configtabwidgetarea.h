#ifndef CONFIGTABWIDGETAREA_H
#define CONFIGTABWIDGETAREA_H

#include <QWidget>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QCheckBox>
#include <QPushButton>
#include <QRadioButton>

class ConfigTabWidgetArea : public QWidget
{
    Q_OBJECT
public:
    explicit ConfigTabWidgetArea(QWidget *parent = nullptr);

    QGroupBox* grpBoxExterior;
    QGroupBox* grpBoxReverse;
    QGroupBox* grpBoxX;
    QGroupBox* grpBoxY;
    QGroupBox* grpBoxGo;
    QGroupBox* grpBoxPassWord;

    //给grpBoxExterior添加控件
    QLabel* labelAreaSize;
    QLineEdit* lineEditAreaSize;
    QLineEdit* lineEditMaxLine;
    QLabel* labelMaxLine;
    QLabel* labelmm1;
    QLabel* labelmm2;
    QLabel* labelmm3;
    QLabel* labelmm4;
    QLabel* labelOffsetX;
    QLabel* labelOffsetY;
    QLabel* labelAngle;
    QLineEdit* lineEditOffsetX;
    QLineEdit* lineEditOffsetY;
    QLineEdit* lineEditAngle;
    QLabel* labelPoint;

    QCheckBox* checkBoxUseCalibrationFile;
    QLineEdit* lineEdit;
    QPushButton* btnUse;

    QCheckBox* checkBoxXYInterchange;
    QCheckBox* checkBoxXreverse;
    QCheckBox* checkBoxYreverse;

    QLabel* labelXProperty;
    QLineEdit* lineEditXProperty;
    QPushButton* propertyXBtn;
    QLabel* labelX1;
    QLabel* labelX2;
    QLabel* labelX3;
    QLineEdit* lineEditX1;
    QLineEdit* lineEditX2;
    QLineEdit* lineEditX3;

    QLabel* labelYProperty;
    QLineEdit* lineEditYProperty;
    QPushButton* propertyYBtn;
    QLabel* labelY1;
    QLabel* labelY2;
    QLabel* labelY3;
    QLineEdit* lineEditY1;
    QLineEdit* lineEditY2;
    QLineEdit* lineEditY3;

    QCheckBox* checkBoxEqualProportionMethod;;
    QLabel* labelProportional;
    QLineEdit* lineEditProportional;
    QPushButton* btnSetX;
    QPushButton* btnSetY;

    QCheckBox* checkBoxUseConfigurationFile;
    QLineEdit* lineEditConfigFileLocation;
    QPushButton* btnConfigFileLocation;
    QPushButton* btnSaveConfigAs;

    QRadioButton* radioBtnDoNotMove;
    QRadioButton* radioBtnGalvanicCenter;
    QRadioButton* radioBtnTopLeftCornerOfTheProject;
    QRadioButton* radioBtnObjectUpperRightCorner;
    QRadioButton* radioBtnObjectBottomRightCorner;
    QRadioButton* radioBtnLowerLeftCornerOfTheProject;
    QRadioButton* radioBtnSpecifiedLocation;
    QLabel* labelX;
    QLabel* labelY;
    QLineEdit* lineEditX;
    QLineEdit* lineEditY;

    QPushButton *btnCalculateRecommendValues;

    QPushButton* btnPassword;

    //布局
    //控件布局
    QGridLayout* gridLayoutExterior;
    QHBoxLayout* layoutUse;
    QHBoxLayout* layoutReverse;
    QGridLayout* layoutX;
    QGridLayout* layoutY;
    QHBoxLayout* layoutProportional;
    QGridLayout* layoutUseConfigurationFile;
    QVBoxLayout* layoutGo;
    QHBoxLayout* layoutGoX;   //对grpBoxX中的X所在行采用水平布局
    QHBoxLayout* layoutGoY;
    QHBoxLayout* layoutPassword;

    //grpBoxX,grpBoxY采用水平布局，左侧采用垂直布局，右侧采用垂直布局，整体采用水平布局
    QHBoxLayout* layoutXY;
    QVBoxLayout* layoutLeft;
    QVBoxLayout* layoutRight;
    QHBoxLayout* layout;

    void initUI();

    void btnUseSlot();
    void proportyXBtnSlot();
    void proportyYBtnSlot();
    void btnConfigFileLocationSlot();
    void btnSaveConfigAsSlot();
    void btnCalculateRecommendValuesSlot();
    void btnPasswordSlot();

signals:

};

#endif // CONFIGTABWIDGETAREA_H
