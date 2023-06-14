#include "itemscalehandle.h"
#include<QLabel>
#include<qstatusbar.h>
ItemScaleHandle::ItemScaleHandle(MyGraphicsView * view)
{
    this->view = view;
}


void ItemScaleHandle::changeScale(qreal currentscale,int wheelDeltaValue)
{
    int ccc = currentscale * 100 + 0.5;
    currentscale = qreal(ccc) / 100;
    QString str;
    int t = 1;

    if (currentscale > 1)
    {
        QString str = QString::number(currentscale);
        t = str.toInt() ;
        if (t == 0)
            t = 1;
    }

    int danwei = t / 10;
    if (wheelDeltaValue > 0)
    {
        if (currentscale >= 0.9 && currentscale*100 < 195)
        {
            view->scale(1 / currentscale, 1 / currentscale);
            view->scale(currentscale + 0.2, currentscale + 0.2);
        }

        if (t == 2)
        {

            view->scale(1 / currentscale, 1 / currentscale);
            view->scale(currentscale + 2, currentscale + 2);
        }

        if (t == 4)
        {

            view->scale(1 / currentscale, 1 / currentscale);
            view->scale(currentscale + 1, currentscale + 1);
        }

        if (t == 5)
        {

            view->scale(1 / currentscale, 1 / currentscale);
            view->scale(currentscale + 3, currentscale + 3);
        }

        if ( t == 8 )
        {
            view->scale(1 / currentscale, 1 / currentscale);
            view->scale(currentscale + 2, currentscale + 2);
        }

        if (t % 10 == 0)
        {
            if (currentscale == 2000)
                return;
            int x = t,num = 0;
            while (1)
            {
                x = x / 10;
                num++;
                if (x < 10)
                {
                    break;
                }

            }

            if (x == 1)
            {
                view->scale(1 / currentscale, 1 / currentscale);
                view->scale(currentscale + 1*pow(10, num), currentscale + 1* pow(10, num));
            }
            if (x == 2)
            {
                view->scale(1 / currentscale, 1 / currentscale);
                view->scale(currentscale + 2 * pow(10, num), currentscale + 2 * pow(10, num));
            }
            if (x == 4)
            {
                view->scale(1 / currentscale, 1 / currentscale);
                view->scale(currentscale + 1 * pow(10, num), currentscale + 1 * pow(10, num));
            }
            if (x == 5)
            {
                view->scale(1 / currentscale, 1 / currentscale);
                view->scale(currentscale + 3 * pow(10, num), currentscale + 3 * pow(10, num));
            }
            if (x == 8)
            {
                view->scale(1 / currentscale, 1 / currentscale);
                view->scale(currentscale + 2 * pow(10, num), currentscale + 2 * pow(10, num));
            }
        }


        if (currentscale < 1)
        {
            double x = currentscale;
            int num = 0;
            while (1)
            {
                x = x * 10;
                num--;
                if (x > 1)
                {
                    break;
                }

            }
            if (x == 10)
            {
                if (currentscale != 2000)
                {
                    view->scale(1 / currentscale, 1 / currentscale);
                    view->scale(currentscale + 1 * pow(10, num + 1), currentscale + 1 * pow(10, num + 1));

                }
                else
                {
                    view->scale(1 / currentscale, 1 / currentscale);
                    view->scale(currentscale - 1 * pow(10, num), currentscale - 1 * pow(10, num));
                }
            }
            if (x == 2)
            {
                view->scale(1 / currentscale, 1 / currentscale);
                view->scale(currentscale + 2 * pow(10, num), currentscale + 2 * pow(10, num));
            }
            if (x == 4)
            {
                view->scale(1 / currentscale, 1 / currentscale);
                view->scale(currentscale + 1 * pow(10, num), currentscale + 1 * pow(10, num));
            }
            if (x == 5)
            {
                view->scale(1 / currentscale, 1 / currentscale);
                view->scale(currentscale + 3 * pow(10, num), currentscale + 3 * pow(10, num));
            }
            if (x == 8)
            {
                view->scale(1 / currentscale, 1 / currentscale);
                view->scale(currentscale + 2 * pow(10, num), currentscale + 2 * pow(10, num));
            }
        }


    }

    // 向下滚动，缩小
    else
    {
        if (currentscale >= 1 && currentscale * 100 < 195)
        {
            view->scale(1 / currentscale, 1 / currentscale);
            view->scale(currentscale - 0.2, currentscale - 0.2);
        }

        if (t == 2)
        {

            view->scale(1 / currentscale, 1 / currentscale);
            view->scale(currentscale - 0.2, currentscale - 0.2);
        }

        if (t == 4)
        {

            view->scale(1 / currentscale, 1 / currentscale);
            view->scale(currentscale - 2, currentscale - 2);
        }

        if (t == 5)
        {

            view->scale(1 / currentscale, 1 / currentscale);
            view->scale(currentscale - 1, currentscale - 1);
        }

        if (t == 8)
        {
            view->scale(1 / currentscale, 1 / currentscale);
            view->scale(currentscale - 3, currentscale - 3);
        }

        if (t % 10 == 0)
        {
            int x = t, num = 0;
            while (1)
            {
                x = x / 10;
                num++;
                if (x < 10)
                {
                    break;
                }

            }

            if (x == 1)
            {
                if (currentscale != 2000)
                {
                    view->scale(1 / currentscale, 1 / currentscale);
                    view->scale(currentscale - 2 * pow(10, num - 1), currentscale - 2 * pow(10, num-1));

                }
                else
                {
                    view->scale(1 / currentscale, 1 / currentscale);
                    view->scale(currentscale - 1 * pow(10, num), currentscale - 1 * pow(10, num));
                }
            }
            if (x == 2)
            {
                view->scale(1 / currentscale, 1 / currentscale);
                view->scale(currentscale - 1 * pow(10, num), currentscale - 1 * pow(10, num));
            }
            if (x == 4)
            {
                view->scale(1 / currentscale, 1 / currentscale);
                view->scale(currentscale - 2 * pow(10, num), currentscale - 2 * pow(10, num));
            }
            if (x == 5)
            {
                view->scale(1 / currentscale, 1 / currentscale);
                view->scale(currentscale - 1 * pow(10, num), currentscale - 1 * pow(10, num));
            }
            if (x == 8)
            {
                view->scale(1 / currentscale, 1 / currentscale);
                view->scale(currentscale - 3 * pow(10, num), currentscale - 3 * pow(10, num));
            }
        }


        if (currentscale < 1)
        {
            double x = currentscale;
            int num = 0;
            if (x == 0.1)
                return;
            while (1)
            {
                x = x * 10;
                num--;
                if (x > 1)
                {
                    break;
                }

            }
            if (x == 10)
            {
                if (currentscale != 2000)
                {
                    view->scale(1 / currentscale, 1 / currentscale);
                    view->scale(currentscale - 2 * pow(10, num), currentscale - 2 * pow(10, num ));

                }
                else
                {
                    view->scale(1 / currentscale, 1 / currentscale);
                    view->scale(currentscale - 1 * pow(10, num), currentscale - 1 * pow(10, num));
                }
            }
            if (x == 2)
            {
                view->scale(1 / currentscale, 1 / currentscale);
                view->scale(currentscale - 1 * pow(10, num), currentscale - 1 * pow(10, num));
            }
            if (x == 4)
            {
                view->scale(1 / currentscale, 1 / currentscale);
                view->scale(currentscale - 2 * pow(10, num), currentscale - 2 * pow(10, num));
            }
            if (x == 5)
            {
                view->scale(1 / currentscale, 1 / currentscale);
                view->scale(currentscale - 1 * pow(10, num), currentscale - 1 * pow(10, num));
            }
            if (x == 8)
            {
                view->scale(1 / currentscale, 1 / currentscale);
                view->scale(currentscale - 3 * pow(10, num), currentscale - 3 * pow(10, num));
            }

        }

    }


    emit view->ScaleChanged(view->matrix().m11());
    QString scaleLabelText;
    if(view->lan == 0)
        scaleLabelText.sprintf("缩放倍数：%.2f", view->matrix().m11());
    else
    {
        scaleLabelText.sprintf("scale：%.2f", view->matrix().m11());
    }
    view->_scaleLabel->setText(scaleLabelText);
    view->_statusBarPtr->update();
    view->leftkedu->update();
    view->topkedu->update();
    //scene()->update();
}
