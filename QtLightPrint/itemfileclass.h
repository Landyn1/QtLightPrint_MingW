#include <QObject>
#include<qrect.h>
#include<qpainterpath.h>
#include<qfont.h>
#include<qdebug.h>
#include<qpixmap.h>
class ItemFileClass
{
public:
    ItemFileClass();
    QString name;
    QPointF pos= QPointF(0,0);
    int layer=0;
    int type=0;
    int id=0;
    QRectF rec=QRectF(0,0,0,0);
    QPainterPath path = QPainterPath();
    int bian_num = 0;
    QString text;
    QFont font = QFont();
    QString pix = QString();
    QString pixAdr;
    friend QDataStream& operator >>(QDataStream &in,ItemFileClass &t);
    friend QDataStream& operator <<(QDataStream &out,ItemFileClass &t);
    friend QDebug operator <<(QDebug& q,ItemFileClass&t);


};


