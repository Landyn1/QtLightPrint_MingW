#include "mygraphicslineitem.h"
#include<MyGraphicsView.h>
MyGraphicsLineItem::MyGraphicsLineItem(QGraphicsPathItem *parent) : QGraphicsPathItem(parent)
{

}

MyGraphicsLineItem::~MyGraphicsLineItem()
{

}
QPainterPath MyGraphicsLineItem::ViewPath()
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


    path.clear();
    path = brushPath;
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


bool MyGraphicsLineItem::set_brush(double jiaodu,int midu)
{
    brushPath.clear();
    this->jiaodu = jiaodu;
    this->midu = midu;
    if(midu == 0)
        return true;
    QPainterPath path2;
    double k = tan(jiaodu*M_PI/180);//斜率
    double w = this->path().boundingRect().width();
    double h = this->path().boundingRect().height();
    QList<QPointF> jiaodians;
    path2 = this->path();
    QList<QLineF> lins;
    QPointF lp1,lp2;
    int kl = 0;
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
    }
    double m = double(h)/double(w);
    double offsetx = path().boundingRect().x();
    double offsety = path().boundingRect().y();
    QPointF offset(offsetx,offsety);
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

                QLineF l(p1+offset,p2+offset);
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
                double tmpt = l.p1().y()-(k*l.p1().x());

                for(int i=0;i<jiaodians.length()-1;i++)
                {
                    QLineF ll(jiaodians[i],jiaodians[i+1]);

                    if(path().contains((QPointF(jiaodians[i].x()+(ll.length()/3),k*(jiaodians[i].x()+(ll.length()/3))+tmpt))) && path().contains((QPointF(jiaodians[i+1].x()-(ll.length()/3),k*(jiaodians[i+1].x()-(ll.length()/3))+tmpt))))
                    {
                             path2.moveTo(jiaodians[i]);
                             path2.lineTo(jiaodians[i+1]);
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
                QLineF l(p1+offset,p2+offset);
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
                double tmpt = l.p1().y()-(k*l.p1().x());
                for(int i=0;i<jiaodians.length()-1;i++)
                {
                    QLineF ll(jiaodians[i],jiaodians[i+1]);

                    if(path().contains((QPointF(jiaodians[i].x()+(ll.length()/3),k*(jiaodians[i].x()+(ll.length()/3))+tmpt))) && path().contains((QPointF(jiaodians[i+1].x()-(ll.length()/3),k*(jiaodians[i+1].x()-(ll.length()/3))+tmpt))))
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
                QLineF l(p1+offset,p2+offset);
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
                double tmpt = l.p1().y()-(k*l.p1().x());
                for(int i=0;i<jiaodians.length()-1;i++)
                {
                    QLineF ll(jiaodians[i],jiaodians[i+1]);
                    double xx1 = jiaodians[i].x()+abs(ll.length()*(cos(jiaodu))/100);
                    double xx2 = jiaodians[i+1].x()-abs(ll.length()*(cos(jiaodu))/100);
                    if(path().contains((QPointF(xx1,k*xx1+tmpt))) && path().contains((QPointF(xx2,k*xx2+tmpt))))
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
                QLineF l(p1+offset,p2+offset);

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
//                for(int i = 0;i<jiaodians.length()-1;i= i+2)
//                {
//                    if(jiaodians.length()%2 == 0)
//                    {
//                            path2.moveTo(jiaodians[i]);
//                            path2.lineTo(jiaodians[i+1]);
//                    }
//                }
                double tmpt = l.p1().y()-(k*l.p1().x());
                for(int i=0;i<jiaodians.length()-1;i++)
                {
                    QLineF ll(jiaodians[i],jiaodians[i+1]);

                    if(path().contains((QPointF(jiaodians[i].x()+(ll.length()/3),k*(jiaodians[i].x()+(ll.length()/3))+tmpt))) && path().contains((QPointF(jiaodians[i+1].x()-(ll.length()/3),k*(jiaodians[i+1].x()-(ll.length()/3))+tmpt))))
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

                QLineF l(p1+offset,p2+offset);
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
                // qDebug()<<jiaodians<<lins;
//                for(int i = 0;i<jiaodians.length()-1;i= i+2)
//                {
//                    if(jiaodians.length()%2 == 0)
//                    {
//                            path2.moveTo(jiaodians[i]);
//                            path2.lineTo(jiaodians[i+1]);
//                    }
//                }
                for(int i=0;i<jiaodians.length()-1;i++)
                {
                    if(path().contains((jiaodians[i]+QPointF(1,0))) && path().contains((jiaodians[i+1]-QPointF(1,0))))
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
                QLineF l(p1+offset,p2+offset);
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

                for(int i=0;i<jiaodians.length()-1;i++)
                {
                    if(path().contains((jiaodians[i]+QPointF(0,1))) && path().contains((jiaodians[i+1]-QPointF(0,1))))
                    {
                             path2.moveTo(jiaodians[i]);
                             path2.lineTo(jiaodians[i+1]);
                    }
                }
//                for(int i = 0;i<jiaodians.length()-1;i= i+2)
//                {
//                    if(jiaodians.length()%2 == 0)
//                    {
//                            path2.moveTo(jiaodians[i]);
//                            path2.lineTo(jiaodians[i+1]);
//                    }
//                }
            }
        }

    }
    brushPath = path2;
    update();
}


bool MyGraphicsLineItem::readPLT(QString filename)
{
    QFile file(filename);
    bool isok = file.open(QIODevice::ReadOnly); //只读模式打开
    QPainterPath path;
    qDebug()<<filename<<endl;
    if(isok == true)
    {
        //读文件
              //一行一行的读

            while(file.atEnd() == false)
            {
                QByteArray array;
                array = file.readLine();
                QString st = QString(array).toUtf8().data();
                if(st.contains("PU"))
                {
                    QStringList lists = st.split(" ");
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
                    QStringList lists = st.split(" ");
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
            }
            qDebug()<<path<<endl;
            this->setPath(path);
     }
}
void MyGraphicsLineItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
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
    painter->drawPath(this->path());
    painter->drawPath(brushPath);
}

QRect MyGraphicsLineItem::getRect()
{
    int x,y,w,h;
    QPoint zuoxia(10000,10000),youshang(-10000,-10000);

    QPainterPath path = this->path();

    for (int i = 0; i < path.elementCount() ;i++)
    {
        QPointF p1 = path.elementAt(i);
        if(zuoxia.x()>p1.toPoint().x())
        {
            zuoxia.setX( p1.toPoint().x());
        }
        if(zuoxia.y()>p1.toPoint().y())
        {
            zuoxia.setY(p1.toPoint().y());
        }
        if(youshang.x()<p1.toPoint().x())
        {
            youshang.setX(p1.toPoint().x());
        }
        if(youshang.y()<p1.toPoint().y())
        {
            youshang.setY(p1.toPoint().y());
        }
    }
    QPoint pos = this->pos().toPoint();
    x = zuoxia.x()+pos.x();
    y = zuoxia.y()+pos.y();
    w = youshang.x()-zuoxia.x();
    h = youshang.y()-zuoxia.y();
    return QRect(x,y,w,h);
}

bool MyGraphicsLineItem::selectEvent(QPointF p)
{
    if(isSelected())
        return true;
    QPainterPath path = this->path();

    for (int i = 0; i < path.elementCount() - 1; i++)
    {
        QPointF p1 = path.elementAt(i);
        QPointF p2 = path.elementAt(i+1);
        QLine l(p1.toPoint(),p2.toPoint());
        if(isOnLine(l,p.toPoint()))
        {

            this->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
            this->setSelected(true);
            return true;
        }
    }
    this->setFlags(NULL);
    this->setSelected(false);
    return false;

}

bool MyGraphicsLineItem::isOnLine(QLine l , QPoint p)
{
    qreal ab = (l.x1() -l.x2())*(l.x1()-l.x2()) + (l.y1()-l.y2())*(l.y1()-l.y2());
    ab = sqrt(ab);
    qreal ac = (l.x1()-p.x())*(l.x1()-p.x()) + (l.y1()-p.y())*(l.y1()-p.y());
    ac = sqrt(ac);
    qreal bc = (l.x2()-p.x())*(l.x2()-p.x()) + (l.y2()-p.y())*(l.y2()-p.y());
    bc = sqrt(bc);
    qreal x = ac+bc-ab;
    if(x<0.1&&x>-0.1)
    {
        return true;
    }
    return false;
}

void MyGraphicsLineItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{

}
void MyGraphicsLineItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{

}
void MyGraphicsLineItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}
