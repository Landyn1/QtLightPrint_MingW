#include "mygraphicstextitem.h"
#include<qdebug.h>
#include"mainWindow.h"
#include <QPen>
#include <QPainter>
#include <QPainterPath>
#include <QPainterPathStroker>
#include <QStyle>
#include <QStyleOptionGraphicsItem>
#include<QKeyEvent>
#include<thirdcurve.h>
MyGraphicsTextItem::MyGraphicsTextItem(QGraphicsTextItem *p,QString str):QGraphicsRectItem()
{

    this->str = str;
}


void MyGraphicsTextItem::setStr(QString str,QFont font)
{

    this->str = str;
    this->font = font;
    setDefault_Path();
    makePath_fill_Rect();
    set_brush(jiaodu,midu);
    update();
}
void MyGraphicsTextItem::setRectF()
{
    QFontMetrics fm(this->font);
    rectf = fm.boundingRect(str);
}
void MyGraphicsTextItem::set_brush(double jiaodu, int midu)
{
    brushpath.clear();
    this->jiaodu = jiaodu;
    this->midu = midu;
    if(midu == 0)
        return;
    QPainterPath path2;
    double k = tan(jiaodu*M_PI/180);//斜率
    int w = path.boundingRect().width()+10;
    int h = path.boundingRect().height()+10;
    QList<QPointF> jiaodians;
    path2 = this->path;
    QList<QLineF> lins;
    QList<ThirdCurve> curves;
    QPointF lp1,lp2,c1,c2;
    int kl = 0;
    int kc = 0;
    for (int i = 0; i < path2.elementCount(); i++)
    {
        QPainterPath::Element element = path2.elementAt(i);
        QPointF po = element;
        if (element.isMoveTo())
        {
            lp1 = po;
            kl = 0;
        }
        else if (element.isLineTo())
        {
            if(kl == 0)
            {
                lp2 = po;
                lins.append(QLineF(lp1,lp2));
                kl++;
            }
            else
            {
                lp1 = lp2;
                lp2 = po;
                lins.append(QLineF(lp1,lp2));
            }
        }
        else if(element.isCurveTo())
        {
            if(kl != 0)
                lp1 = lp2;
            c1 = po;
            kc++;
        }
        else
        {
            if(kc%3==1)
            {
                c2 = po;
                kc++;
            }
            else if(kc%3 == 2)
            {
                lp2 = po;
                //curve lp1,c1,c2,lp2
                ThirdCurve curve(lp1,c1,c2,lp2);
                curves.append(curve);
                kc ++;
                lp1 = lp2;
            }
        }
    }
    double dpiX = QApplication::primaryScreen()->physicalDotsPerInchX();
    double mint = (dpiX*10)/254;; //1mm = tpx;
    mint = mint*0.02; //0.02mm = tpx;
    double m = double(h)/double(w);
    if(int(jiaodu)%90 != 0 ||  ((int(jiaodu)%180 == 0)&&(int(jiaodu)%90 != 0)))
    {
        if(k>0&&k<=m)
        {
            double t = (w/2*k) + (h/2); //y=kx+t
            double pert = t/(midu/2);
            pert = fmax(pert,mint);
            midu = 2*t/pert+2;
            for(int ii=-midu/2;ii<=midu/2;ii++)
            {
                jiaodians.clear();
                QPointF p1(w/2,(w/2*k)+(pert*ii));
                QPointF p2(-w/2,(-w/2*k)+(pert*ii));
                if(pert * ii >= (h/2)- (w/2*k))
                {
                    p1 = QPointF(((h/2)-(pert*ii))/k,h/2);
                }
                else if( pert * ii <= -(h/2)+(w/2*k))
                {
                    p2 = QPointF(((-h/2)-(pert*ii))/k,-h/2);
                }
                p1.setY(-p1.y());
                p2.setY(-p2.y());
                QLineF l(p1,p2);
                for(int i=0;i<curves.length();i++)
                {
                    QList<QPointF> cjiaodians = curves[i].jiaodian(l);
                    for(int j = 0;j<cjiaodians.length();j++)
                    {
                        if(cjiaodians[j]!=QPointF(-20000,-20000) )
                        {
                             jiaodians.append(cjiaodians[j]);
                        }
                    }
                }
                for(int i=0;i<lins.length();i++)
                {
                    QPointF intersectionPoint;
                    auto type = l.intersects(lins[i],&intersectionPoint);
                    if(type == QLineF::BoundedIntersection)
                    {
                        jiaodians.append(intersectionPoint);
                    }
                }
                for(int i = 1;i<jiaodians.length();i++)
                {
                    for(int j=0;j<jiaodians.length()-i;j++)
                    {
                        if(jiaodians[j].x()>jiaodians[j+1].x())
                        {
                            QPointF tm = jiaodians[j];
                            jiaodians[j] = jiaodians[j+1];
                            jiaodians[j+1] = tm;
                        }
                    }
                }
                for(int i = 0;i<jiaodians.length()-1;i= i+2)
                {
                    if(jiaodians.length()%2 == 0)
                    {
                            path2.moveTo(jiaodians[i]);
                            path2.lineTo(jiaodians[i+1]);
                    }
                }
            }

        }
        else if( k>m )
        {
            double t = (w/2*k) + (h/2); //y=kx+t
            double pert = t/(midu/2);
            pert = fmax(pert,mint);
            midu = 2*t/pert+2;
            for(int ii=-midu/2;ii<midu/2;ii++)
            {
                jiaodians.clear();
                QPointF p1(((h/2)-(pert*ii))/k,h/2);
                QPointF p2(((-h/2)-(pert*ii))/k,-h/2);
                if(pert * ii < (h/2)- (w/2*k))
                {
                    p1 = QPointF(w/2,(w/2*k)+(pert*ii));
                }
                else if( pert * ii > -(h/2)+(w/2*k))
                {
                    p2 = QPointF(-w/2,(-w/2*k)+(pert*ii));
                }
                p1.setY(-p1.y());
                p2.setY(-p2.y());
                QLineF l(p1,p2);
                for(int i=0;i<curves.length();i++)
                {
                    QList<QPointF> cjiaodians = curves[i].jiaodian(l);
                    for(int j = 0;j<cjiaodians.length();j++)
                    {
                        if(cjiaodians[j]!=QPointF(-20000,-20000) )
                        {
                             jiaodians.append(cjiaodians[j]);
                        }
                    }
                }
                for(int i=0;i<lins.length();i++)
                {
                    QPointF intersectionPoint;
                    auto type = l.intersects(lins[i],&intersectionPoint);
                    if(type == QLineF::BoundedIntersection)
                    {
                        jiaodians.append(intersectionPoint);
                    }
                }
                for(int i = 1;i<jiaodians.length();i++)
                {
                    for(int j=0;j<jiaodians.length()-i;j++)
                    {
                        if(jiaodians[j].x()>jiaodians[j+1].x())
                        {
                            QPointF tm = jiaodians[j];
                            jiaodians[j] = jiaodians[j+1];
                            jiaodians[j+1] = tm;
                        }
                    }
                }
                for(int i = 0;i<jiaodians.length()-1;i= i+2)
                {
                    if(jiaodians.length()%2 == 0)
                    {
                            path2.moveTo(jiaodians[i]);
                            path2.lineTo(jiaodians[i+1]);
                    }
                }
            }

        }
        else if( k<-m)
        {

            double t = -(w/2*k) + (h/2); //y=kx+t
            double pert = t/(midu/2);
            pert = fmax(pert,mint);
            midu = 2*t/pert+2;
            for(int ii=-midu/2;ii<midu/2;ii++)
            {
                jiaodians.clear();
                QPointF p1(((h/2)-(pert*ii))/k,h/2);
                QPointF p2(((-h/2)-(pert*ii))/k,-h/2);
                if(pert * ii < (h/2)+(w/2*k))
                {
                    p1 = QPointF(-w/2,(-w/2*k)+(pert*ii));
                }
                else if( pert * ii > -(h/2)+(-w/2*k))
                {
                    p2 = QPointF(w/2,(w/2*k)+(pert*ii));
                }
                p1.setY(-p1.y());
                p2.setY(-p2.y());
                QLineF l(p1,p2);
                for(int i=0;i<curves.length();i++)
                {
                    QList<QPointF> cjiaodians = curves[i].jiaodian(l);
                    for(int j = 0;j<cjiaodians.length();j++)
                    {
                        if(cjiaodians[j]!=QPointF(-20000,-20000) )
                        {
                             jiaodians.append(cjiaodians[j]);
                        }
                    }
                }
                for(int i=0;i<lins.length();i++)
                {
                    QPointF intersectionPoint;
                    auto type = l.intersects(lins[i],&intersectionPoint);
                    if(type == QLineF::BoundedIntersection)
                    {
                        jiaodians.append(intersectionPoint);
                    }
                }
                for(int i = 1;i<jiaodians.length();i++)
                {
                    for(int j=0;j<jiaodians.length()-i;j++)
                    {
                        if(jiaodians[j].x()>jiaodians[j+1].x())
                        {
                            QPointF tm = jiaodians[j];
                            jiaodians[j] = jiaodians[j+1];
                            jiaodians[j+1] = tm;
                        }
                    }
                }
                for(int i = 0;i<jiaodians.length()-1;i= i+2)
                {
                    if(jiaodians.length()%2 == 0)
                    {
                            path2.moveTo(jiaodians[i]);
                            path2.lineTo(jiaodians[i+1]);
                    }
                }
            }
        }
        else if( k>=-m && k<0)
        {

            double t = -(w/2*k) + (h/2); //y=kx+t
            double pert = t/(midu/2);
            pert = fmax(pert,mint);
            midu = 2*t/pert+2;
            for(int ii=-midu/2;ii<midu/2;ii++)
            {
                jiaodians.clear();
                QPointF p1(w/2,(w/2*k)+(pert*ii));
                QPointF p2(-w/2,(-w/2*k)+(pert*ii));
                if(pert * ii > (h/2)+(w/2*k))
                {
                    p2 = QPointF(((h/2)-(pert*ii))/k,h/2);
                }
                else if( pert * ii < -(h/2)-(w/2*k))
                {
                    p1 = QPointF(((-h/2)-(pert*ii))/k,-h/2);
                }
                p1.setY(-p1.y());
                p2.setY(-p2.y());
                QLineF l(p1,p2);
                for(int i=0;i<curves.length();i++)
                {
                    QList<QPointF> cjiaodians = curves[i].jiaodian(l);
                    for(int j = 0;j<cjiaodians.length();j++)
                    {
                        if(cjiaodians[j]!=QPointF(-20000,-20000) )
                        {
                             jiaodians.append(cjiaodians[j]);
                        }
                    }
                }
                for(int i=0;i<lins.length();i++)
                {
                    QPointF intersectionPoint;
                    auto type = l.intersects(lins[i],&intersectionPoint);
                    if(type == QLineF::BoundedIntersection)
                    {
                        jiaodians.append(intersectionPoint);
                    }
                }
                for(int i = 1;i<jiaodians.length();i++)
                {
                    for(int j=0;j<jiaodians.length()-i;j++)
                    {
                        if(jiaodians[j].x()>jiaodians[j+1].x())
                        {
                            QPointF tm = jiaodians[j];
                            jiaodians[j] = jiaodians[j+1];
                            jiaodians[j+1] = tm;
                        }
                    }
                }
                for(int i = 0;i<jiaodians.length()-1;i= i+2)
                {
                    if(jiaodians.length()%2 == 0)
                    {
                            path2.moveTo(jiaodians[i]);
                            path2.lineTo(jiaodians[i+1]);
                    }
                }
            }
        }

    }
    else
    {

        if(int(jiaodu)%180 == 0)
        {
            double t = (w/2*k) + (h/2); //y=kx+t
            double pert = t/(midu/2);
            pert = fmax(pert,mint);
            midu = 2*t/pert+2;
            for(int ii=-midu/2;ii<midu/2;ii++)
            {
                jiaodians.clear();
                QPointF p1(-w/2,pert*ii);
                QPointF p2(w/2,pert*ii);
                p1.setY(-p1.y());
                p2.setY(-p2.y());
                QLineF l(p1,p2);
                for(int i=0;i<curves.length();i++)
                {
                    QList<QPointF> cjiaodians = curves[i].jiaodian(l);
                    for(int j = 0;j<cjiaodians.length();j++)
                    {
                        if(cjiaodians[j]!=QPointF(-20000,-20000) )
                        {
                             jiaodians.append(cjiaodians[j]);
                        }
                    }
                }
                for(int i=0;i<lins.length();i++)
                {
                    QPointF intersectionPoint;
                    auto type = l.intersects(lins[i],&intersectionPoint);
                    if(type == QLineF::BoundedIntersection)
                    {
                        jiaodians.append(intersectionPoint);
                    }
                }
                for(int i = 1;i<jiaodians.length();i++)
                {
                    for(int j=0;j<jiaodians.length()-i;j++)
                    {
                        if(jiaodians[j].x()>jiaodians[j+1].x())
                        {
                            QPointF tm = jiaodians[j];
                            jiaodians[j] = jiaodians[j+1];
                            jiaodians[j+1] = tm;
                        }
                    }
                }
                for(int i = 0;i<jiaodians.length()-1;i= i+2)
                {
                    if(jiaodians.length()%2 == 0)
                    {
                            path2.moveTo(jiaodians[i]);
                            path2.lineTo(jiaodians[i+1]);
                    }
                }
            }
        }

        else
        {
            double pert = w/double(midu);
            pert = fmax(pert,mint);
            midu = 2*w/pert+2;
            for(int ii=-midu/2;ii<midu/2;ii++)
            {
                jiaodians.clear();
                QPointF p1(pert*ii,h/2);
                QPointF p2(pert*ii,-h/2);
                p1.setY(-p1.y());
                p2.setY(-p2.y());
                QLineF l(p1,p2);
                for(int i=0;i<curves.length();i++)
                {
                    QList<QPointF> cjiaodians = curves[i].jiaodian(l);
                    for(int j = 0;j<cjiaodians.length();j++)
                    {
                        if(cjiaodians[j]!=QPointF(-20000,-20000) )
                        {
                             jiaodians.append(cjiaodians[j]);
                        }
                    }
                }
                for(int i=0;i<lins.length();i++)
                {
                    QPointF intersectionPoint;
                    auto type = l.intersects(lins[i],&intersectionPoint);
                    if(type == QLineF::BoundedIntersection)
                    {
                        jiaodians.append(intersectionPoint);
                    }
                }

                for(int i = 1;i<jiaodians.length();i++)
                {
                    for(int j=0;j<jiaodians.length()-i;j++)
                    {
                        if(jiaodians[j].y()>jiaodians[j+1].y())
                        {
                            QPointF tm = jiaodians[j];
                            jiaodians[j] = jiaodians[j+1];
                            jiaodians[j+1] = tm;
                        }
                    }
                }
                for(int i = 0;i<jiaodians.length()-1;i= i+2)
                {
                    if(jiaodians.length()%2 == 0)
                    {
                            path2.moveTo(jiaodians[i]);
                            path2.lineTo(jiaodians[i+1]);
                    }
                }
            }
        }

    }
    brushpath = path2;
    update();
}

QPainterPath MyGraphicsTextItem::ViewPath()
{
    QPainterPath p;
    QPainterPath path = this->path;

    QPainterPath path2 = brushpath;
    int k=0;
    QPointF p0,c1,c2,p3;
    for (int i = 0; i < path.elementCount(); i++)
    {
        QPainterPath::Element element = path.elementAt(i);
        QPointF po = element;
        QPointF po2 = mapToScene(po);
        if (element.isMoveTo())
        {
            p.moveTo(mapToScene(po));
            p0 = po2;
        }
        else if (element.isLineTo())
        {
            p.lineTo(mapToScene(po));
            p0 = po2;
        }
        else if(element.isCurveTo())
        {

            c1 = po2;
            k++;
            //path2.cubicTo(po2);
        }
        else
        {
            if(k%3 == 1)
            {
                c2 = po2;
                k++;
            }
            else if(k%3 == 2)
            {
                p3 = po2;
                QList<QPointF> list;
                for(int i=0;i<=5;i++)
                {
                    double temp = 0.2*i;
                    double tx = f(temp,p0.x(),c1.x(),c2.x(),p3.x());
                    double ty = f(temp,p0.y(),c1.y(),c2.y(),p3.y());
                    list.append(QPointF(tx,ty));
                }
                double s = 0;
                for(int i=0;i<5;i++)
                {
                    double x1,x2,y1,y2;
                    x1 = list[i].x();
                    y1 = list[i].y();
                    x2 = list[i+1].x();
                    y2 = list[i+1].y();
                    double m = (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
                    m = sqrt(m);
                    s += m;
                }
                double dpiX = QApplication::primaryScreen()->physicalDotsPerInchX();
                double  t = (dpiX * 10) / 254;   //1mm = t px
                double s_mm = s/t;
                int num = s_mm / 0.1 ; //每隔0.1毫米一个单位;

                for(int i=1;i<=num;i++)
                {
                    double temp = (double(1)/double(num))*i;
                    double tx = f(temp,p0.x(),c1.x(),c2.x(),p3.x());
                    double ty = f(temp,p0.y(),c1.y(),c2.y(),p3.y());
                    p.lineTo(tx,ty);
                }
                k++;
                p0=po2;
            }

        }
    }

    for (int i = 0; i < path2.elementCount(); i++)
    {
        QPainterPath::Element element = path2.elementAt(i);
        QPointF po = element;
        if (element.isMoveTo())
        {
            p.moveTo(mapToScene(po));
        }
        else if (element.isLineTo())
        {
            p.lineTo(mapToScene(po));
        }
    }
    return p;
}

void MyGraphicsTextItem::setDefault_Path()
{
    path.clear();
    path.addText(0,0, font, str);
}

void MyGraphicsTextItem::makePath_fill_Rect()
{
    QPainterPath path = this->path;
    QRectF rect = path.boundingRect();

    QRectF tarRect = this->rect();
    qreal scaleX = tarRect.width() / rect.width();
    qreal scaleY = tarRect.height() / rect.height();



    QTransform trans;
    trans.scale(scaleX, scaleY);
    QPainterPath tmp_path = trans.map(path);

    QPointF delta = tarRect.center() - tmp_path.boundingRect().center();
    tmp_path.translate(delta.x(), delta.y());
    this->setPath(tmp_path);
}
void MyGraphicsTextItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QPen pen;   // 定义一个画笔，设置画笔颜色和宽度
    //pen.setColor(QColor(0, 160, 230));
    QList<QGraphicsView*> list = scene()->views();
    QGraphicsView* view = list.first();
    double s = view->matrix().m11();
    pen.setWidthF(1/s);
    if(data(0).toInt() == -1)
    {
        pen.setColor(Qt::blue);
    }
    painter->setPen(pen);
    //painter->setBrush(Qt::blue);
    painter->scale(1,-1);
   // painter->drawRect(rect());
    painter->drawPath(path);
    painter->drawPath(brushpath);
}
MyGraphicsTextItem::~MyGraphicsTextItem()
{

}

bool MyGraphicsTextItem::selectEvent(QPointF p)
{

    if(isSelected())
        return true;
    if(rect().contains(p))
    {
        setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
        this->setSelected(true);
        return true;
    }
    this->setFlags(NULL);
    this->setSelected(false);
    return false;
}

void MyGraphicsTextItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{

}
void MyGraphicsTextItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{

}
void MyGraphicsTextItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}
