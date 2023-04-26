#include "mygraphicscodeitem.h"
#include"mainWindow.h"
#include"ZXingWriter.h"
#include"thirdcurve.h"
MyGraphicsCodeItem::MyGraphicsCodeItem():QGraphicsRectItem()
{

}

MyGraphicsCodeItem::~MyGraphicsCodeItem(){

}


bool MyGraphicsCodeItem::selectEvent(QPointF p)
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

void MyGraphicsCodeItem::makePath_fill_Rect()
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
    this->path.clear();
    this->path = (tmp_path);
}

void MyGraphicsCodeItem::setPathByStr(QString str,QString codeType)
{

    this->text = str;
    this->codetype = codeType;
    vector<dPoint> vdPoint;
    double dpiX = QApplication::primaryScreen()->physicalDotsPerInchX();
    double  t = (dpiX * 10) / 254; //1mm=tpx
    vdPoint = Border(20*t, 20*t, str.toStdString(), codeType.toStdString());
    double w = 20*t,h = 20*t;
    QPainterPath path;
    this->path.clear();
    for (vector<dPoint>::iterator it = vdPoint.begin(); it != vdPoint.end(); it++)
    {
        if(!(*it).flag)
        {
            path.moveTo(QPointF((*it).x-(w/2),(*it).y-(h/2)));
        }
        else
        {
            path.lineTo(QPointF((*it).x-(w/2),(*it).y-(h/2)));
        }
    }
    set_brush(this->jiaodu,this->midu);
    this->path = path;
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
    painter->drawPath(brushPath);
    painter->drawPath(this->path);

}
QPainterPath MyGraphicsCodeItem::ViewPath()
{
    QPainterPath p;
    QPainterPath path = this->path;
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
    QPainterPath path2 = brushPath;
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

QRectF MyGraphicsCodeItem::boundingRect() const
{
//    double x,y,w,h;
//    x = this->path().boundingRect().x();
//    y = this->path().boundingRect().y();
//    w = this->path().boundingRect().width();
//    h = this->path().boundingRect().height();
//    return QRectF(x,y-h,w,h);

      return rect();
}
bool MyGraphicsCodeItem::set_brush(double jiaodu, int midu)
{
    this->jiaodu = jiaodu;
    this->midu = midu;
    brushPath.clear();
    if(midu == 0)
    {
        update();
        return true;
    }
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

    brushPath = path2;
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
