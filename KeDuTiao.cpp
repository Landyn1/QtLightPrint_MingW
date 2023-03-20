#include "KeDuTiao.h"
#include<qpainter.h>
#include<qgraphicsview.h>
KeDuTiao::KeDuTiao(QGraphicsItem*parent)
	: QGraphicsItem(parent)
{
	
}

KeDuTiao::~KeDuTiao()
{

}

void KeDuTiao::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    auto Hheight = 20;
    auto Hwidth = 10000;

    
    painter->setRenderHint(QPainter::Antialiasing);
    //painter.fillRect(rect, backgroundColor);

   // orientation == Qt::Horizontal ?  : painter.translate(0, 0 - offset);

    painter->translate(0 - offset, 0);
    //绘制刻度
    painter->save();
    auto length = 10000 + offset;
    painter->setPen(QPen(textAndLineColor, 1));
    painter->setFont(font);
    auto shortLine_y = Hheight * 0.75;
    auto longLine_y = Hheight * 0.5;
    auto middleLine_y = Hheight * 0.625;
    auto halfHeight = Hheight / 2;
    int temp = 0;
    for (int i = 0; i < length; i += 10)
    {
        if (temp % 10 == 0)//画长线
        {
            painter->drawLine(QPointF(i, middleLine_y), QPointF(i, Hheight));
        }
        else if (temp % 5 == 0)
        {
            painter->drawLine(QPointF(i, longLine_y), QPointF(i, Hheight));
            painter->drawText(QRectF(i - 50, 0, 100, halfHeight), Qt::AlignCenter | Qt::TextWordWrap, QString::number(i));
        }
        else
        {
            painter->drawLine(QPointF(i, shortLine_y), QPointF(i, Hheight));
        }
        ++temp;
    }

}
QRectF KeDuTiao::boundingRect() const
{
    return _centerRect;
}

