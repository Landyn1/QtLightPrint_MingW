#include "GraphicsItems/mylabel.h"

myLabel::myLabel(int k) : QLabel()
{
    id = k;
}

void myLabel::mouseReleaseEvent(QMouseEvent* event)
{
    if (event != nullptr && event->button() == Qt::LeftButton)
    {
        emit clicked(id);	//emit signal
    }
}
