#include "FileHandel/itemfileclass.h"

ItemFileClass::ItemFileClass()
{
    name = QString();

    text = QString();

    pixAdr = QString();


}
QDebug operator <<(QDebug &debug,ItemFileClass&t)
{
    debug<<t.name<<t.layer<<t.type<<t.id<<t.rec<<t.path<<t.bian_num<<t.text<<t.font<<t.pixAdr<<t.pos<<t.pix<<t.codetype<<t.angle<<t.space;
    return debug;
}

QDataStream& operator >>(QDataStream &in, ItemFileClass&t)
{
    in>>t.name>>t.layer>>t.type>>t.id>>t.rec>>t.path>>t.bian_num>>t.text>>t.font>>t.pixAdr>>t.pos>>t.pix>>t.codetype>>t.angle>>t.space;
    return in;
}

QDataStream& operator <<(QDataStream &out, ItemFileClass&t)
{
    out<<t.name<<t.layer<<t.type<<t.id<<t.rec<<t.path<<t.bian_num<<t.text<<t.font<<t.pixAdr<<t.pos<<t.pix<<t.codetype<<t.angle<<t.space;
    return out;
}

void ItemFileClass::setPathByText()
{
    QString text = this->text;
    QPainterPath p;
    QStringList strlist = text.split(";");
    for(int i=0;i<strlist.length()-1;i++)
    {
        QStringList positionList = strlist[i].split(" ");
        double x =  positionList[1].toDouble();
        double y = positionList[2].toDouble();
        if(positionList[0] == "move")
        {
            p.moveTo(x,y);
        }
        else
        {
            p.lineTo(x,y);
        }
    }
    this->path = p;
}
