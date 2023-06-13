#include "GraphicsItems/MyKedu.h"
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
    QRect rect(-10000,0,20000,20);
    auto height = rect.height() ;
    auto width = rect.width() ;
    
    painter->setRenderHint(QPainter::Antialiasing);
    painter->fillRect(rect, backgroundColor);
    
    double dpiX = QApplication::primaryScreen()->physicalDotsPerInchX();

    double dpiY = QApplication::primaryScreen()->physicalDotsPerInchY();
    auto  t = (dpiX * 10) / 254;
    if(scale >= 1999)
        t = t * scale*2;
    else
        t = t * scale;
    double x1 = offset*scale;
    double width1 = viewWidth ;

    //qDebug() << width1 << endl;

    painter->scale(1, -1);
    painter->translate(0, 0);
   // painter->save();
    QPen pen;
    pen.setColor(textAndLineColor);
    pen.setWidth(1);
    painter->setPen(pen);
    painter->setFont(font);
    auto shortLine_y = height * 0.75;
    auto longLine_y = height * 0.5;
    auto middleLine_y = height * 0.625;
    auto halfHeight = height / 2;
    int temp1 = 0;
    double x2 = 0;

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
                {
                    double num = double(i)/t;
                    if(scale == 2000)
                    {
                        num = num*2;
                    }
                    painter->drawText(QRectF(i - 50, 0, 100, halfHeight), Qt::AlignCenter | Qt::TextWordWrap, QString::number(num));
                }


            }

            else
            {
                painter->drawLine(QPointF(i, shortLine_y), QPointF(i, height));
            }
            ++temp;
        }
    }
    else
    {
        temp = 0;
        for (double i = 0; i < 10100; i += t)
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
        for (double i = 0; i > -10100; i -= t)
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

    painter->eraseRect(QRectF(offset*scale, 0, 20, 20));
    
    painter->drawLine(QPointF(x2, 20), QPointF(x2+width1 , 20));

}
