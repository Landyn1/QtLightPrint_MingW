#ifndef WIDGETFIBER_H
#define WIDGETFIBER_H

#include <QWidget>
#include <QGroupBox>
#include <QCheckBox>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QGridLayout>
#include <QHBoxLayout>

class WidgetFiber : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetFiber(QWidget *parent = nullptr);

    QGroupBox* grpBoxPWM;
    QLabel* labelMax;
    QLineEdit* lineEditMax;
    QLabel* labelMaxKhz;
    QLabel* labelMin;
    QLineEdit* lineEditMin;
    QLabel* labelMinKhz;
    QPushButton* btnPowerMapping;

    QCheckBox* checkBoxDoes;
    QCheckBox* checkBoxLight;
    QLabel* labelTurn;
    QLineEdit* lineEditTurn;
    QLabel* labelMs;

    QGroupBox* grpBoxFiber;
    QLabel* labelTypes;
    QComboBox* comboBoxTypes;

    QPushButton* btnTest;

    //设置布局
    QGridLayout* layoutPWM;
    QHBoxLayout* layoutFiber;
    QGridLayout* layoutRight;
    QHBoxLayout* layoutTop;
    QVBoxLayout* layout;

    void initUI();

signals:

};

#endif // WIDGETFIBER_H
