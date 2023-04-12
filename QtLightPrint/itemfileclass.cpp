#include "itemfileclass.h"

ItemFileClass::ItemFileClass()
{
    name = QString();

    text = QString();

    pixAdr = QString();


}
QDebug operator <<(QDebug &debug,ItemFileClass&t)
{
    debug<<t.name<<t.layer<<t.type<<t.id<<t.rec<<t.path<<t.bian_num<<t.text<<t.font<<t.pixAdr<<t.pos<<t.pix;
    return debug;
}

QDataStream& operator >>(QDataStream &in, ItemFileClass&t)
{
    in>>t.name>>t.layer>>t.type>>t.id>>t.rec>>t.path>>t.bian_num>>t.text>>t.font>>t.pixAdr>>t.pos>>t.pix;
    return in;
}

QDataStream& operator <<(QDataStream &out, ItemFileClass&t)
{
    out<<t.name<<t.layer<<t.type<<t.id<<t.rec<<t.path<<t.bian_num<<t.text<<t.font<<t.pixAdr<<t.pos<<t.pix;
    return out;
}
