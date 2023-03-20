#include "mygraphicstextitem.h"
#include<qdebug.h>
MyGraphicsTextItem::MyGraphicsTextItem(QGraphicsTextItem *p,QString str):QGraphicsTextItem()
{

    this->setPlainText(str);

    QFont font("微软雅黑",36);
    //font.setStretch(50);//字体拉伸

    this->setFont(font);
    QFontMetrics fm(font);

    //setRotation(-90);
    //setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    QTransform t(1,0,0,0,-1,0,0,0,1);
    setTransform(t);

    qDebug()<<fm.boundingRect(str)<<endl;;
}

MyGraphicsTextItem::~MyGraphicsTextItem()
{

}
