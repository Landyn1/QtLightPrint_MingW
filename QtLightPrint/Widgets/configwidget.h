#ifndef CONFIGWIDGET_H
#define CONFIGWIDGET_H

#include <QWidget>
#include "configtabwidget.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

class ConfigWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ConfigWidget(QWidget *parent = nullptr);

    ConfigTabWidget * tabWidget;
    QPushButton* btnOk;
    QPushButton* btnCancel;
    QHBoxLayout* layoutBottom;
    QVBoxLayout* layout;

    void initUI();

    void SlotCancel();

signals:

};

#endif // CONFIGWIDGET_H
