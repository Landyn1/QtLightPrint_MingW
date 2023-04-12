#ifndef DIALOGPASSWORDSETTING_H
#define DIALOGPASSWORDSETTING_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>

class DialogPasswordSetting : public QDialog
{
public:
    DialogPasswordSetting();

    QLabel* labelPassword;
    QLineEdit* lineEditPassword1;
    QLineEdit* lineEditPassword2;
    QPushButton* btnOk;
    QPushButton* btnCancel;
    QPushButton* btnDelete;

    QGridLayout* layout;

    void initUI();

    void btnOkSlot();
    void btnCancelSlot();
    void btnDeleteSlot();
};

#endif // DIALOGPASSWORDSETTING_H
