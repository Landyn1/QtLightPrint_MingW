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
    QPointF pos;
    int layer;
    int type;
    int id;
    QRectF rec;
    QPainterPath path;
    int bian_num;
    QString text;
    QFont font;
    QPixmap pixmap;
    QString pixAdr;



};


