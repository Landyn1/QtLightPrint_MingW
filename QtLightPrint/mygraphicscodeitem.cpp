#include "mygraphicscodeitem.h"
#include"mainWindow.h"
#include"ZXingWriter.h"
#include"thirdcurve.h"
MyGraphicsCodeItem::MyGraphicsCodeItem():QGraphicsPathItem()
{

}

MyGraphicsCodeItem::~MyGraphicsCodeItem(){

}

QRectF MyGraphicsCodeItem::getRect()
{
    double x,y,w,h;
    x = this->path().boundingRect().x();
    y = this->path().boundingRect().y();
    w = this->path().boundingRect().width();
    h = this->path().boundingRect().height();
    return QRectF(x,y-h,w,h);
}


bool MyGraphicsCodeItem::selectEvent(QPointF p)
{
    if(isSelected())
        return true;
    if(this->path().boundingRect().contains(p))
    {
        setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
        this->setSelected(true);
        return true;
    }
    this->setFlags(NULL);
    this->setSelected(false);
    return false;
}

void MyGraphicsCodeItem::setPathByStr(QString str,QString codeType)
{
    vector<dPoint> vdPoint;
    double dpiX = QApplication::primaryScreen()->physicalDotsPerInchX();
    double  t = (dpiX * 10) / 254; //1mm=tpx
    vdPoint = Border(20*t, 20*t, str.toStdString(), codeType.toStdString());
    QPainterPath path;
    for (vector<dPoint>::iterator it = vdPoint.begin(); it != vdPoint.end(); it++)
    {
        if(!(*it).flag)
        {
            path.moveTo(QPointF((*it).x,(*it).y));
        }
        else
        {
            path.lineTo(QPointF((*it).x,(*it).y));
        }
    }
    this->setPath(path);
    noBrushPath = path;
}

void MyGraphicsCodeItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
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
    //painter->setBrush(Qt::blue);
    painter->setPen(pen);
    painter->scale(1,-1);

    painter->drawPath(this->path());

}
QPainterPath MyGraphicsCodeItem::ViewPath()
{
    QPainterPath p;
    QPainterPath path = this->path();
    for (int i = 0; i < path.elementCount(); i++)
    {
        QPainterPath::Element element = path.elementAt(i);
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

QRectF MyGraphicsCodeItem::boundingRect() const
{
    double x,y,w,h;
    x = this->path().boundingRect().x();
    y = this->path().boundingRect().y();
    w = this->path().boundingRect().width();
    h = this->path().boundingRect().height();
    return QRectF(x,y-h,w,h);
}
bool MyGraphicsCodeItem::set_brush(double jiaodu,int midu)
{
    QPainterPath path2;
    double k = tan(jiaodu*M_PI/180);//斜率
    double w = this->path().boundingRect().width();
    double h = this->path().boundingRect().height();
    QList<QPointF> jiaodians;
    path2 = noBrushPath;
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
                ThirdCurve curve(lp1,c1,c2,lp2);
                curves.append(curve);
                kc ++;
            }
        }
    }
    double m = double(h)/double(w);
    k = -k;
    if(int(jiaodu)%90 != 0 ||  ((int(jiaodu)%180 == 0)&&(int(jiaodu)%90 != 0)))
    {
        if(k>0&&k<=m)
        {
            double t = h + k*w; //y=kx+t
            double pert = t/(midu);
            for(double ii=-k*w-1;ii<h+1;ii += pert)
            {
                jiaodians.clear();
                QPointF p1(w,(w*k)+(ii));
                QPointF p2(0,(ii));
                if( ii > (h)- (w*k))
                {
                    p1 = QPointF(((h)-(ii))/k,h);
                }
                else if( ii < 0)
                {
                    p2 = QPointF((-(ii))/k,0);
                }

                QLineF l(p1,p2);
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
                for(int i = 0;i<jiaodians.length()-1;i++)
                {
                    if(jiaodu != 0)
                    {
                        if(path2.contains((jiaodians[i]+QPointF(0.1,0.1))) && path2.contains((jiaodians[i+1]-QPointF(0.1,0.1))) )
                        {
                            path2.moveTo(jiaodians[i]);
                            path2.lineTo(jiaodians[i+1]);
                        }
                    }
                    else
                    {
                        if(path2.contains((jiaodians[i]+QPointF(0.1,0))) && path2.contains((jiaodians[i+1]-QPointF(0.1,0))) )
                        {
                            path2.moveTo(jiaodians[i]);
                            path2.lineTo(jiaodians[i+1]);
                        }
                    }
                }
            }

        }
        else if( k>m )
        {
            double t = h + w*k; //y=kx+t
            double pert = t/double(midu);
            for(double ii=-k*w-1;ii<h+1;ii= ii + pert)
            {
                jiaodians.clear();
                QPointF p1(((h)-(ii))/k,h);
                QPointF p2((-(ii))/k,0);

                if(ii <= (h)- (w*k))
                {

                    p1 = QPointF(w,(w*k)+(ii));
                    //qDebug()<<mapToScene(p1)<<mapToScene(p2)<<pert*i<<endl;
                }
                else if( ii > 0)
                {
                    p2 = QPointF(0,(ii));
                }
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
                for(int i = 0;i<jiaodians.length()-1;i++)
                {
                    if(path2.contains((jiaodians[i]+QPointF(0.1,0.1))) && path2.contains((jiaodians[i+1]-QPointF(0.1,0.1))) )
                    {
                        path2.moveTo(jiaodians[i]);
                        path2.lineTo(jiaodians[i+1]);
                    }
                }
            }

        }
        else if( k<-m)
        {

            double t = -(w*k) + (h); //y=kx+t
            double pert = t/double(midu);
            for(int ii=0;ii<=midu;ii++)
            {
                jiaodians.clear();
                QPointF p1(((h)-(pert*ii))/k,h);
                QPointF p2((-(pert*ii))/k,0);
                if(pert * ii < h)
                {
                    p1 = QPointF(0,(pert*ii));
                }
                else if( pert * ii > (-w*k))
                {
                    p2 = QPointF(w,(w*k)+(pert*ii));
                }
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
                for(int i = 0;i<jiaodians.length()-1;i++)
                {
                    if(path2.contains((jiaodians[i]+QPointF(0.1,-0.1))) && path2.contains((jiaodians[i+1]-QPointF(0.1,-0.1))) )
                    {
                        path2.moveTo(jiaodians[i]);
                        path2.lineTo(jiaodians[i+1]);
                    }
                }
            }
        }
        else if( k>=-m && k<0)
        {

            double t = -(w*k) + (h); //y=kx+t
            double pert = t/double(midu);
            for(int ii=0;ii<=midu;ii++)
            {
                jiaodians.clear();
                QPointF p1(w,(w*k)+(pert*ii));
                QPointF p2(0,(pert*ii));
                if(pert * ii > h)
                {
                    p2 = QPointF(((h)-(pert*ii))/k,h);
                }
                else if( pert * ii < (-w*k))
                {
                    p1 = QPointF((-(pert*ii))/k,0);
                }
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
                for(int i = 0;i<jiaodians.length()-1;i++)
                {
                    if(path2.contains((jiaodians[i]+QPointF(0.1,-0.1))) && path2.contains((jiaodians[i+1]-QPointF(0.1,-0.1))) )
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
            double t = h + k*w; //y=kx+t
            double pert = t/(midu);
            for(double ii=-k*w-1;ii<h+1;ii += pert)
            {
                jiaodians.clear();
                QPointF p1(w,(ii));
                QPointF p2(0,(ii));
                QLineF l(p1,p2);
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
                for(int i = 0;i<jiaodians.length()-1;i++)
                {
                        if(path2.contains((jiaodians[i]+QPointF(0.1,0))) && path2.contains((jiaodians[i+1]-QPointF(0.1,0))) )
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
            for(int ii=0;ii<=midu;ii++)
            {
                jiaodians.clear();
                QPointF p1(pert*ii,h);
                QPointF p2(pert*ii,0);
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
                for(int i = 0;i<jiaodians.length()-1;i++)
                {
                    if(path2.contains((jiaodians[i]+QPointF(0,0.1))) && path2.contains((jiaodians[i+1]-QPointF(0,0.1))) )
                    {
                        path2.moveTo(jiaodians[i]);
                        path2.lineTo(jiaodians[i+1]);
                    }
                }
            }
        }

    }
    this->setPath(path2);
    update();
}
void MyGraphicsCodeItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{

}
void MyGraphicsCodeItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{

}
void MyGraphicsCodeItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}
