#include "GraphicsItems/MyleftKedu.h"
#include <QPen>
#include <QPainter>
#include <QPainterPath>
#include <QPainterPathStroker>
#include <QStyle>
#include <QStyleOptionGraphicsItem>
#include"mainWindow.h"
#include"qdebug.h"
MyleftKedu::MyleftKedu(QGraphicsRectItem* parent)
	: QGraphicsRectItem (parent)
{}

MyleftKedu::~MyleftKedu()
{}

void MyleftKedu::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    QRect rect(0, -10000, 20, 20000);
    auto height = rect.height();
    auto width = rect.width();

    painter->setRenderHint(QPainter::Antialiasing);
    painter->fillRect(rect, backgroundColor);

    double dpiY = QApplication::primaryScreen()->physicalDotsPerInchY();

    //绘制刻度
    //painter->save();

    QPen pen;
    pen.setColor(textAndLineColor);
    pen.setWidth(1);
    painter->setPen(pen);
    painter->setFont(font);
    auto shortLineWidth = width * 0.25;
    auto longLineWidth = width * 0.6;
    auto middleLineWidth = width * 0.45;
    auto harfWidth = width / 2;
    double  tt = (dpiY * 10) / 254;
    if(scale >= 1999)
        tt = tt * scale * 2;
    else
        tt = tt * scale;
    double x1 ;

    double height1;

    x1 = offset*scale;
    height1 = viewHeight;
    painter->scale(1, -1);
    painter->translate(0, 0);
    int temp1 = 0;
    double x2 = 0;
    //painter->scale(1 / scale, 1 / scale);
    if (x1 >= 0)
    {
        for (double i = 0; i < x1; i += tt / scale)
        {
            temp1++;
            x2 = i;
        }
    }
    else
    {
        for (double i = 0; i > x1; i -= tt / scale)
        {
            temp1--;
            x2 = i;
        }
    }
    int temp = temp1;
    if (temp1 > 0)
    {
        temp = temp1 - 1;
    }
    else
    {
        temp = temp1 + 1;
    }

    if (scale >= 1.9 || scale < 1)
    {
        for (double i = x2; i >= x2 - height1; i -= tt/scale )
        {
            if (temp % 10 != 0 && temp % 5 == 0)//画长线
            {
                painter->drawLine(QPointF(longLineWidth, -i), QPointF(width, -i));
            }
            else if (temp % 5 == 0 && temp % 10 == 0)
            {

                painter->drawLine(QPointF(middleLineWidth, -i), QPointF(width, -i));
                painter->rotate(90);

                if (temp == 0)
                {
                    painter->drawText(QRectF(-i - 50, -10, 100, harfWidth), Qt::AlignCenter | Qt::TextWordWrap, QString::number(0));
                }
                else
                {
                    double num = double(i)/tt;
                    if(scale == 2000)
                    {
                        num = num*2;
                    }
                        painter->drawText(QRectF(-i - 50, -10, 100, harfWidth), Qt::AlignCenter | Qt::TextWordWrap, QString::number(num));
                }
                painter->rotate(270);
            }
            else
            {
                painter->drawLine(QPointF(width - shortLineWidth, -i), QPointF(width, -i));
            }
            temp--;
        }
    }
    else
    {
        temp = 0;
        for (double i = 0; i < 10100 * scale; i += tt )
        {
            if (temp % 10 != 0 && temp % 5 == 0)//画长线
            {
                painter->drawLine(QPointF(longLineWidth, i), QPointF(width, i));
            }
            else if (temp % 5 == 0 && temp % 10 == 0)
            {

                painter->drawLine(QPointF(middleLineWidth, i), QPointF(width, i));
                painter->rotate(90);
                painter->drawText(QRectF(i - 50, -10, 100, harfWidth), Qt::AlignCenter | Qt::TextWordWrap, QString::number(-((i) / tt)));
                painter->rotate(270);
            }
            else
            {
                painter->drawLine(QPointF(width - shortLineWidth, i), QPointF(width, i));
            }
            temp++;
        }
        temp = 0;
        for (double i = 0; i > -10100 * scale; i -= tt)
        {
            if (temp % 10 != 0 && temp % 5 == 0)//画长线
            {
                //painter.drawLine(QPointF(width-middleLineWidth,i),QPointF(width,i));

                painter->drawLine(QPointF(longLineWidth, i), QPointF(width, i));

            }
            else if (temp % 5 == 0 && temp % 10 == 0)
            {



                painter->drawLine(QPointF(middleLineWidth, i), QPointF(width, i));

                //painter.rotate(90);
                // painter.translate(width*0.3, i-50);
                painter->rotate(90);
                //painter->scale(scale, scale);
                //painter.drawText(-10,0,QString::number(i-70));
                painter->drawText(QRectF((i - 50), -10, 100, 10), Qt::AlignCenter | Qt::TextWordWrap, QString::number(-((i) / tt)));
                // painter.resetMatrix();
                //painter->scale(1/scale, 1/scale);
                painter->rotate(270);

            }
            else
            {
                painter->drawLine(QPointF(width - shortLineWidth, i), QPointF(width, i));
            }
            temp++;
        }
    }



    

   //painter->eraseRect(QRectF(0, -offset*scale, 20, 19.9));
  
   painter->drawLine(QPointF(20 , -10000*scale), QPointF(20 , 10000*scale));
   //painter->setPen(Qt::transparent);
   //painter->setBrush(slidingLineColor);
   //painter->drawRect(0, -slidingLinePos, 20, 3);
}


