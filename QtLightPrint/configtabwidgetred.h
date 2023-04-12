#ifndef CONFIGTABWIDGETRED_H
#define CONFIGTABWIDGETRED_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QComboBox>
#include <QGroupBox>
#include <QGridLayout>
#include <QVBoxLayout>

class ConfigTabWidgetRed : public QWidget
{
    Q_OBJECT
public:
    explicit ConfigTabWidgetRed(QWidget *parent = nullptr);

    void initUI();

    QGroupBox * groupBox;

    QLabel* labelRedLightStyle;
    QComboBox * comBox;

    QLabel* labelRedLight;
    QLineEdit* lineEditRedLight;
    QLabel* labelMms;

    QLabel* labelOffsetX;
    QLineEdit* lineEditOffsetX;
    QLabel* labelMm1;

    QLabel* labelOffsetY;
    QLineEdit* lineEditOffsetY;
    QLabel* labelMm2;

    QLabel* labelSizeRatioX;
    QLineEdit* lineEditSizeRatioX;

    QLabel* labelSizeRatioY;
    QLineEdit* lineEditSizeRatioY;

    QLabel* labelTime;

    QCheckBox* checkBoxLaser;
    QCheckBox* checkBoxEnable;

    QPushButton* btnRedPreview;

    QGridLayout* layoutGrpBox;
    QVBoxLayout* layoutRight;
    QGridLayout* layout;

    void btnRedPreviewSlot();

signals:

};

#endif // CONFIGTABWIDGETRED_H
