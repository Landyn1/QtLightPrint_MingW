#ifndef DIALOGCALCULATIONRATIO_H
#define DIALOGCALCULATIONRATIO_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>

class DialogCalculationRatio : public QDialog
{
    Q_OBJECT
public:
    DialogCalculationRatio();

    QLabel* labelTarget;
    QLabel* labelActual;
    QLineEdit* lineEditTarget;
    QLineEdit* lineEditActual;
    QPushButton* btnOk;
    QPushButton* btnCancel;

    QGridLayout* layout;

    void initUI();

    void btnOkSlot();
    void btnCancelSlot();
};

#endif // DIALOGCALCULATIONRATIO_H
