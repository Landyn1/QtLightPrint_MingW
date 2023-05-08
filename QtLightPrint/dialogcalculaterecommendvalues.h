#ifndef DIALOGCALCULATERECOMMENDVALUES_H
#define DIALOGCALCULATERECOMMENDVALUES_H

#include <QDialog>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>

class DialogCalculateRecommendValues : public QDialog
{
    Q_OBJECT
public:
    DialogCalculateRecommendValues();

    QGroupBox* grpBoxTheoretical;
    QLabel* labelX;
    QLabel* labelY;
    QLineEdit* lineEditX;
    QLineEdit* lineEditY;

    QGroupBox* grpBoxMeasured;
    QLabel* labelA;
    QLabel* labelX1;
    QLabel* labelX2;
    QLabel* labelX3;
    QLabel* labelY1;
    QLabel* labelY2;
    QLabel* labelY3;
    QLineEdit* lineEditA;
    QLineEdit* lineEditX1;
    QLineEdit* lineEditX2;
    QLineEdit* lineEditX3;
    QLineEdit* lineEditY1;
    QLineEdit* lineEditY2;
    QLineEdit* lineEditY3;

    QPushButton* btnCalculate;
    QPushButton* btnSure;

    QGroupBox* grpBoxX;
    QLabel* labelProportyX;
    QLabel* labelXPic1;
    QLabel* labelXPic2;
    QLabel* labelXPic3;
    QLineEdit* lineEditProportyX;
    QLineEdit* lineEditXPic1;
    QLineEdit* lineEditXPic2;
    QLineEdit* lineEditXPic3;

    QGroupBox* grpBoxY;
    QLabel* labelProportyY;
    QLabel* labelYPic1;
    QLabel* labelYPic2;
    QLabel* labelYPic3;
    QLineEdit* lineEditProportyY;
    QLineEdit* lineEditYPic1;
    QLineEdit* lineEditYPic2;
    QLineEdit* lineEditYPic3;

    QLabel* labelPic;

    QHBoxLayout* layoutGrpBoxTheoretical;
    QGridLayout* layoutGrpBoxMeasured;
    QGridLayout* layoutGrpBoxX;
    QGridLayout* layoutGrpBoxY;

    //整体布局：上侧采用网格布局，下侧采用水平布局，整体采用垂直布局
    QGridLayout* layoutTop;
    QHBoxLayout* layoutBottom;
    QVBoxLayout* layout;

    void initUI();

    void btnCalculateSlot();
    void btnSureSlot();
};

#endif // DIALOGCALCULATERECOMMENDVALUES_H
