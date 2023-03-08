#include "MyKedu.h"
#include <QPen>
#include <QPainter>
#include <QPainterPath>
#include <QPainterPathStroker>
#include <QStyle>
#include <QStyleOptionGraphicsItem>
#include"mainWindow.h"
#include"qdebug.h"
MyKedu::MyKedu(QGraphicsRectItem *parent)
	: QGraphicsRectItem(parent)
{
	
}

MyKedu::~MyKedu()
{
	
}

void MyKedu::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QRect rect(-5000,0,10000,20);
    auto height = rect.height() ;
    auto width = rect.width() ;
    
    painter->setRenderHint(QPainter::Antialiasing);
    painter->fillRect(rect, backgroundColor);
    
    double dpiX = QApplication::primaryScreen()->physicalDotsPerInchX();

    double dpiY = QApplication::primaryScreen()->physicalDotsPerInchY();
    auto  t = (dpiX * 10) / 254;
    t = t * scale;

    double x1 = offset*scale;
    double width1 = viewWidth ;

    qDebug() << width1 << endl;

    painter->scale(1, -1);
    painter->translate(0, 0);
    painter->save();
    QPen pen;
    pen.setColor(textAndLineColor);
    pen.setWidth(1);
    painter->setPen(pen);
    painter->setFont(font);
    auto  tt = (dpiY * 10) / 254;
    auto shortLine_y = height * 0.75;
    auto longLine_y = height * 0.5;
    auto middleLine_y = height * 0.625;
    auto halfHeight = height / 2;
    int temp1 = 0;
    double x2 = 0;
    //painter->scale(1 / scale, 1 / scale);
    if (x1 >= 0)
    {
        for (double i = 0; i < x1; i += t /scale)
        {
            temp1++;
            x2 = i;
        }
    }
    else
    {
        for (double i = 0; i > x1; i -= t/scale )
        {
            temp1--;
            x2 = i;
        }
    }
    
    int temp=temp1 ;
    if (temp1 > 0)
    {
        temp = temp1 - 1;
    }
    else
    {
        temp = temp1 + 1;
    }
    qDebug() << temp << x2 << "ddd" << endl;
   // int i = x2 * 1000 + 0.5;
   // int x = t / scale * 1000 + 0.5;
    if (scale >= 1.9 || scale <1)
    {
        for (double i = x2; i <= x2 + width1; i += t / scale)
        {
            if (temp % 5 == 0 && temp % 10 != 0)
            {
                painter->drawLine(QPointF(i, middleLine_y), QPointF(i, height));
            }

            else if (temp % 10 == 0 && temp % 5 == 0)//画长线
            {
                painter->drawLine(QPointF(i, longLine_y), QPointF(i, height));

                if (temp == 0)
                {
                    painter->drawText(QRectF(i - 50, 0, 100, halfHeight), Qt::AlignCenter | Qt::TextWordWrap, QString::number((0)));
                }
                else
                    painter->drawText(QRectF(i - 50, 0, 100, halfHeight), Qt::AlignCenter | Qt::TextWordWrap, QString::number((i / t)));
            }

            else
            {
                painter->drawLine(QPointF(i, shortLine_y), QPointF(i, height));
            }
            if (i == 0)
            {
                qDebug() << "" << endl;
            }
            ++temp;
        }
    }
    else
    {
        temp = 0;
        for (double i = 0; i < 5100; i += t)
        {
            if (temp % 5 == 0 && temp % 10 != 0)
            {
                painter->drawLine(QPointF(i, middleLine_y), QPointF(i, height));
            }

            else if (temp % 10 == 0 && temp % 5 == 0)//画长线
            {
                painter->drawLine(QPointF(i, longLine_y), QPointF(i, height));

                painter->drawText(QRectF(i - 50, 0, 100, halfHeight), Qt::AlignCenter | Qt::TextWordWrap, QString::number((i / t) ));
            }

            else
            {
                painter->drawLine(QPointF(i, shortLine_y), QPointF(i, height));
            }
            ++temp;
        }
        temp = 0;
        for (double i = 0; i > -5100; i -= t)
        {
            if (temp % 5 == 0 && temp % 10 != 0)
            {
                painter->drawLine(QPointF(i, middleLine_y), QPointF(i, height));
            }
            else if (temp % 10 == 0 && temp % 5 == 0)//画长线
            {
                painter->drawLine(QPointF(i, longLine_y), QPointF(i, height));
                painter->drawText(QRectF(i - 50, 0, 100, halfHeight), Qt::AlignCenter | Qt::TextWordWrap, QString::number((i / t)));
            }
            else
            {
                painter->drawLine(QPointF(i, shortLine_y), QPointF(i, height));
            }
            ++temp;
        }
    }


    
    
    painter->eraseRect(QRectF(offset*scale, 0, 20, 19.9));
    painter->drawLine(QPointF(x2, 20), QPointF(x2+width1 , 20));
}
