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

void MyGraphicsLineItem::setLinsAndCurves(QPainterPath path2, QList<QLineF> &lins)
{
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
}

void MyGraphicsLineItem::setBrushpath(QList<QLineF> lins, QLineF l, QList<QPointF> intersections, QPainterPath &path2, int k)
{

    //延长l以确保不会丢失交点
    QPointF p1,p2;
    QPointF pp1,pp2;
    p1 = l.p1();
    p2 = l.p2();
    l.setLength(-2);
    pp1 = l.p2();
    l.setP1(p1);
    l.setP2(p2);
    l.setLength(l.length()+2);
    pp2 = l.p2();
    l.setP1(pp1);
    l.setP2(pp2);



    for(int i=0;i<lins.length();i++)
    {
        QPointF intersectionPoint;
        auto type = l.intersects(lins[i],&intersectionPoint);
        if(type == QLineF::BoundedIntersection)
        {
            intersections.append(intersectionPoint);
        }
    }
    if(k == 0)
    {
        for(int i = 1;i<intersections.length();i++)
        {
            for(int j=0;j<intersections.length()-i;j++)
            {
                if(intersections[j].x()>intersections[j+1].x())
                {
                    QPointF tm = intersections[j];
                    intersections[j] = intersections[j+1];
                    intersections[j+1] = tm;
                }
            }
        }
        for(int i=0;i<intersections.length()-1;i++)
        {
            double x1,y1;
            x1 = (intersections[i].x()+intersections[i+1].x())/2;
            y1 = (intersections[i].y()+intersections[i+1].y())/2;
            if(path().contains((QPointF(x1,y1))))
            {
                     path2.moveTo(intersections[i]);
                     path2.lineTo(intersections[i+1]);
            }
        }

    }
    else if( k == 1)
    {
        for(int i = 1;i<intersections.length();i++)
        {
            for(int j=0;j<intersections.length()-i;j++)
            {
                if(intersections[j].x()>intersections[j+1].x())
                {
                    QPointF tm = intersections[j];
                    intersections[j] = intersections[j+1];
                    intersections[j+1] = tm;
                }
            }
        }
        for(int i=0;i<intersections.length()-1;i++)
        {
            if(path().contains((intersections[i]+QPointF(1,0))) && path().contains((intersections[i+1]-QPointF(1,0))))
            {
                     path2.moveTo(intersections[i]);
                     path2.lineTo(intersections[i+1]);
            }
        }
    }
    else
    {
        for(int i = 1;i<intersections.length();i++)
        {
            for(int j=0;j<intersections.length()-i;j++)
            {
                if(intersections[j].y()>intersections[j+1].y())
                {
                    QPointF tm = intersections[j];
                    intersections[j] = intersections[j+1];
                    intersections[j+1] = tm;
                }
            }
        }

        for(int i=0;i<intersections.length()-1;i++)
        {
            double x1,y1;
            x1 = (intersections[i].x()+intersections[i+1].x())/2;
            y1 = (intersections[i].y()+intersections[i+1].y())/2;
            if(path().contains((QPointF(x1,y1))))
            {
                     path2.moveTo(intersections[i]);
                     path2.lineTo(intersections[i+1]);
            }
        }
    }
}

bool MyGraphicsLineItem::set_brush(double angle,int linenum)
{
    brushPath.clear();
    this->angle = angle;
    this->linenum = linenum;
    if(linenum == 0)
        return true;
    QPainterPath path2;
    double k = tan(angle*M_PI/180);//斜率
    double w = this->path().boundingRect().width();
    double h = this->path().boundingRect().height();
    QList<QPointF> intersections;
    QList<QLineF> lins;
    setLinsAndCurves(this->path(),lins);
    double m = double(h)/double(w);
    double offsetx = path().boundingRect().x();
    double offsety = path().boundingRect().y();
    QPointF offset(offsetx,offsety);
    if(int(angle)%90 != 0 ||  ((int(angle)%180 == 0)&&(int(angle)%90 != 0)))
    {
        if(k>0&&k<=m)
        {
            double t = h + k*w; //y=kx+t
            double pert = t/(linenum);
            for(double ii=-k*w-1;ii<h+1;ii += pert)
            {
                intersections.clear();
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
                setBrushpath(lins,l,intersections,path2);
            }

        }
        else if( k>m )
        {
            double t = h + w*k; //y=kx+t
            double pert = t/double(linenum);
            for(double ii=-k*w-1;ii<h+1;ii= ii + pert)
            {
                intersections.clear();
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
                setBrushpath(lins,l,intersections,path2);
            }

        }
        else if( k<-m)
        {

            double t = -(w*k) + (h); //y=kx+t
            double pert = t/double(linenum);
            for(int ii=0;ii<=linenum;ii++)
            {
                intersections.clear();
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
                setBrushpath(lins,l,intersections,path2);
            }
        }
        else if( k>=-m && k<0)
        {

            double t = -(w*k) + (h); //y=kx+t
            double pert = t/double(linenum);
            for(int ii=0;ii<=linenum;ii++)
            {
                intersections.clear();
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

                setBrushpath(lins,l,intersections,path2);
            }
        }

    }
    else
    {

        if(int(angle)%180 == 0)
        {
            double t = h + k*w; //y=kx+t
            double pert = t/(linenum);
            for(double ii=-k*w-1;ii<h+1;ii += pert)
            {
                intersections.clear();
                QPointF p1(w,(ii));
                QPointF p2(0,(ii));
                QLineF l(p1+offset,p2+offset);
                setBrushpath(lins,l,intersections,path2,1);
            }
        }

        else
        {
            double pert = w/double(linenum);
            for(int ii=0;ii<=linenum;ii++)
            {
                intersections.clear();
                QPointF p1(pert*ii,h);
                QPointF p2(pert*ii,0);
                QLineF l(p1+offset,p2+offset);

                setBrushpath(lins,l,intersections,path2,2);
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
    //+painter->setBrush(Qt::blue);
    painter->setPen(pen);
    painter->drawPath(this->path());
    painter->drawPath(brushPath);
}

QRect MyGraphicsLineItem::getRect()
{
    int x,y,w,h;
    QPoint leftbuttom(10000,10000),righttop(-10000,-10000);

    QPainterPath path = this->path();

    for (int i = 0; i < path.elementCount() ;i++)
    {
        QPointF p1 = path.elementAt(i);
        if(leftbuttom.x()>p1.toPoint().x())
        {
            leftbuttom.setX( p1.toPoint().x());
        }
        if(leftbuttom.y()>p1.toPoint().y())
        {
            leftbuttom.setY(p1.toPoint().y());
        }
        if(righttop.x()<p1.toPoint().x())
        {
            righttop.setX(p1.toPoint().x());
        }
        if(righttop.y()<p1.toPoint().y())
        {
            righttop.setY(p1.toPoint().y());
        }
    }
    QPoint pos = this->pos().toPoint();
    x = leftbuttom.x()+pos.x();
    y = leftbuttom.y()+pos.y();
    w = righttop.x()-leftbuttom.x();
    h = righttop.y()-leftbuttom.y();
    return QRect(x,y,w,h);
}

bool MyGraphicsLineItem::selectEvent(QPointF p,int k)
{
    if(k == 1)
    {
        setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
        setSelected(true);
        return true;
    }
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
