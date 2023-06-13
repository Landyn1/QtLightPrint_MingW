#include "pltfilehandle.h"

pltFileHandle::pltFileHandle()
{

}


QPainterPath pltFileHandle::readPLT(QString filename)
{
    QFile file(filename);
    bool isok = file.open(QIODevice::ReadOnly); //只读模式打开
    QPainterPath path;
    if(isok == true)
    {
            int k=0;
            QByteArray array;
            array = file.read(file.size());
            QString all = QString(array).toUtf8().data();
            QStringList sts = all.split(";");
            for(QString st:sts)
            {
                if(st.contains("PU"))
                {
                    QRegExp Separator = QRegExp(" |,");
                    QStringList lists = st.split(Separator);
                    k=0;
                    if(lists.length()<2)
                    {
                        continue;
                    }
                    QString x1,y1;
                    for(int i=0;i<lists[0].length();i++)
                    {
                        if((lists[0][i]>=48 && lists[0][i]<=57) || lists[0][i]=='-')
                        {
                            x1.append(lists[0][i]);
                        }
                    }
                    for(int i=0;i<lists[1].length();i++)
                    {
                        if((lists[1][i]>=48 && lists[1][i]<=57) || lists[1][i]=='-')
                        {
                            y1.append(lists[1][i]);
                        }
                    }
                    double x,y;
                    x = x1.toDouble()/10;
                    y = y1.toDouble()/10;
                    path.moveTo(x,y);
                }
                else if(st.contains("PD"))
                {
                    QRegExp Separator = QRegExp(" |,");
                    QStringList lists = st.split(Separator);
                    k=1;
                    if(lists.length()<2)
                    {

                        continue;
                    }
                    QString x1,y1;
                    for(int i=0;i<lists[0].length();i++)
                    {
                        if((lists[0][i]>=48 && lists[0][i]<=57) || lists[0][i]=='-')
                        {
                            x1.append(lists[0][i]);
                        }
                    }
                    for(int i=0;i<lists[1].length();i++)
                    {
                        if((lists[1][i]>=48 && lists[1][i]<=57) || lists[1][i]=='-')
                        {
                            y1.append(lists[1][i]);
                        }
                    }

                    double x,y;

                    x = x1.toDouble()/10;
                    y = y1.toDouble()/10;
                    path.lineTo(x,y);
                }
                else if(st.contains("PA"))
                {

                    QRegExp Separator = QRegExp(" |,");
                    QStringList lists = st.split(Separator);
                    if(lists.length()<2)
                    {
                        continue;
                    }
                    QString x1,y1;
                    for(int i=0;i<lists[0].length();i++)
                    {
                        if((lists[0][i]>=48 && lists[0][i]<=57) || lists[0][i]=='-')
                        {
                            x1.append(lists[0][i]);
                        }
                    }
                    for(int i=0;i<lists[1].length();i++)
                    {
                        if((lists[1][i]>=48 && lists[1][i]<=57) || lists[1][i]=='-')
                        {
                            y1.append(lists[1][i]);
                        }
                    }

                    double x,y;

                    x = x1.toDouble()/10;
                    y = y1.toDouble()/10;
                    if(k == 0)
                    {
                        path.moveTo(x,y);
                    }
                    else
                    {
                        path.lineTo(x,y);
                    }
                }
            }
      return path;
     }
}
