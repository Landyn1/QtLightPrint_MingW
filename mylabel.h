#ifndef MYLABEL_H
#define MYLABEL_H

#include <QObject>
#include<QLabel>
#include<QMouseEvent>
class myLabel : public QLabel
{
    Q_OBJECT
public:
    myLabel(int k);
    void mouseReleaseEvent(QMouseEvent* event) override;
    int id; // 在widget中的id
signals:
    void clicked(int k);
};

#endif // MYLABEL_H
