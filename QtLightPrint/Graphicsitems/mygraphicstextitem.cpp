#include "GraphicsItems/mygraphicstextitem.h"
#include<qdebug.h>
#include"mainWindow.h"
#include <QPen>
#include <QPainter>
#include <QPainterPath>
#include <QPainterPathStroker>
#include <QStyle>
#include <QStyleOptionGraphicsItem>
#include<QKeyEvent>
MyGraphicsTextItem::MyGraphicsTextItem(QGraphicsTextItem *p,QString str):QGraphicsRectItem()
{
    setFlags(NULL);
    setSelected(false);
    this->str = str;
}


void MyGraphicsTextItem::setStr(QString str,QFont font)
{

    this->str = str;
    this->font = font;
    setDefault_Path();
    makePath_fill_Rect();
    set_brush(angle,space);
    update();
}

QRectF MyGraphicsTextItem::getRect()
{
    double x,y,w,h;
    x = rect().x()+pos().x();
    y = rect().y()+pos().y();
    w = rect().width();
    h = rect().height();
    return QRectF(x,y,w,h);
}
void MyGraphicsTextItem::setRectF()
{
    QFontMetrics fm(this->font);
    rectf = fm.boundingRect(str);
}
void MyGraphicsTextItem::setLinsAndCurves(QPainterPath path2, QList<QLineF> &lins,QList<ThirdCurve> &curves)
{
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
}

void MyGraphicsTextItem::setBrushpath(QList<QLineF> lins, QList<ThirdCurve> curves , QLineF l, QList<QPointF> intersections, QPainterPath &path2, int k)
{

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

        for(int i=0;i<curves.length();i++)
        {
            QList<QPointF> cintersections = curves[i].intersection(l);
            for(int j = 0;j<cintersections.length();j++)
            {
                if(cintersections[j]!=QPointF(-20000,-20000) )
                {
                     intersections.append(cintersections[j]);
                }
            }
        }
        for(int i=0;i<lins.length();i++)
        {
            QPointF intersectionPoint;
            auto type = l.intersects(lins[i],&intersectionPoint);
            if(type == QLineF::BoundedIntersection)
            {
                intersections.append(intersectionPoint);
            }
        }
        if(k==0)
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
        }
        for(int i = 0;i<intersections.length()-1;i= i+2)
        {
            if(intersections.length()%2 == 0)
            {
                    path2.moveTo(intersections[i]);
                    path2.lineTo(intersections[i+1]);
            }
        }
}
void MyGraphicsTextItem::set_brush(double angle, double space)
{
    brushpath.clear();
    this->angle = angle;
    double dpiX = QApplication::primaryScreen()->physicalDotsPerInchX();
    double  temp = (dpiX * 10) / 254; //1mm = tpx
    double maxh = fmax(this->getRect().width(),this->getRect().height());
    double linenum = (maxh/temp) / space;
    this->space = space;
    if(space == 0)
    {
        update();
        return;
    }
    QPainterPath path2;
    double k = tan(angle*M_PI/180);//斜率
    int w = path.boundingRect().width()+10;
    int h = path.boundingRect().height()+10;
    QList<QPointF> intersections;
    QList<QLineF> lins;
    QList<ThirdCurve> curves;
    setLinsAndCurves(this->path,lins,curves);

    double mint = (dpiX*10)/254;; //1mm = tpx;
    mint = mint*0.02; //0.02mm = tpx;
    double m = double(h)/double(w);
    if(int(angle)%90 != 0 ||  ((int(angle)%180 == 0)&&(int(angle)%90 != 0)))
    {
        if(k>0&&k<=m)
        {
            double t = (w/2*k) + (h/2); //y=kx+t
            double pert = t/(linenum/2);
            pert = fmax(pert,mint);
            linenum = 2*t/pert+2;
            for(int ii=-linenum/2;ii<=linenum/2;ii++)
            {
                intersections.clear();
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
                setBrushpath(lins,curves,l,intersections,path2);
            }

        }
        else if( k>m )
        {
            double t = (w/2*k) + (h/2); //y=kx+t
            double pert = t/(linenum/2);
            pert = fmax(pert,mint);
            linenum = 2*t/pert+2;
            for(int ii=-linenum/2;ii<linenum/2;ii++)
            {
                intersections.clear();
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
                setBrushpath(lins,curves,l,intersections,path2);
            }

        }
        else if( k<-m)
        {

            double t = -(w/2*k) + (h/2); //y=kx+t
            double pert = t/(linenum/2);
            pert = fmax(pert,mint);
            linenum = 2*t/pert+2;
            for(int ii=-linenum/2;ii<linenum/2;ii++)
            {
                intersections.clear();
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
                setBrushpath(lins,curves,l,intersections,path2);
            }
        }
        else if( k>=-m && k<0)
        {

            double t = -(w/2*k) + (h/2); //y=kx+t
            double pert = t/(linenum/2);
            pert = fmax(pert,mint);
            linenum = 2*t/pert+2;
            for(int ii=-linenum/2;ii<linenum/2;ii++)
            {
                intersections.clear();
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
                setBrushpath(lins,curves,l,intersections,path2);
            }
        }

    }
    else
    {

        if(int(angle)%180 == 0)
        {
            double t = (w/2*k) + (h/2); //y=kx+t
            double pert = t/(linenum/2);
            pert = fmax(pert,mint);
            linenum = 2*t/pert+2;
            for(int ii=-linenum/2;ii<linenum/2;ii++)
            {
                intersections.clear();
                QPointF p1(-w/2,pert*ii);
                QPointF p2(w/2,pert*ii);
                p1.setY(-p1.y());
                p2.setY(-p2.y());
                QLineF l(p1,p2);
                setBrushpath(lins,curves,l,intersections,path2);
            }
        }

        else
        {
            double pert = w/double(linenum);
            pert = fmax(pert,mint);
            linenum = 2*w/pert+2;
            for(int ii=-linenum/2;ii<linenum/2;ii++)
            {
                intersections.clear();
                QPointF p1(pert*ii,h/2);
                QPointF p2(pert*ii,-h/2);
                p1.setY(-p1.y());
                p2.setY(-p2.y());
                QLineF l(p1,p2);
                setBrushpath(lins,curves,l,intersections,path2,1);
            }
        }

    }
    brushpath = path2;
    update();
}

QPainterPath MyGraphicsTextItem::ViewPath(int kk)
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
        po.setY(-po.y());
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

    if(kk == 0)
    {
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
    }
    return p;
}


void MyGraphicsTextItem::rotateY()
{
    double rooty = getRect().y()+(getRect().height()/2);
    rooty = rooty-pos().y();
    QPainterPath p;
    QPainterPath path = this->path;

    QPointF lp1,lp2,c1,c2;
    int kl = 0;
    int kc = 0;
    for (int i = 0; i < path.elementCount(); i++)
    {
        QPainterPath::Element element = path.elementAt(i);
        QPointF po = element;
        int x1,y1;
        x1 = po.x();
        y1 = rooty*2-po.y();
        po.setX(x1);
        po.setY(y1);
        if (element.isMoveTo())
        {
            lp1 = po;
            kl = 0;
            p.moveTo(po);
        }
        else if (element.isLineTo())
        {
            if(kl == 0)
            {
                lp2 = po;
                p.lineTo(po);
                kl++;
            }
            else
            {
                lp1 = lp2;
                lp2 = po;
                p.lineTo(po);
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
                p.cubicTo(c1,c2,lp2);
                kc ++;
                lp1 = lp2;
            }
        }
    }
    this->setPath(p);
}

void MyGraphicsTextItem::rotateX()
{
    double rootx = getRect().x()+(getRect().width()/2);
    rootx = rootx-pos().x();
    QPainterPath p;
    QPainterPath path = this->path;

    QPointF lp1,lp2,c1,c2;
    int kl = 0;
    int kc = 0;
    for (int i = 0; i < path.elementCount(); i++)
    {
        QPainterPath::Element element = path.elementAt(i);
        QPointF po = element;
        int x1,y1;
        x1 = rootx*2-po.x();
        y1 = po.y();
        po.setX(x1);
        po.setY(y1);
        if (element.isMoveTo())
        {
            lp1 = po;
            kl = 0;
            p.moveTo(po);
        }
        else if (element.isLineTo())
        {
            if(kl == 0)
            {
                lp2 = po;
                p.lineTo(po);
                kl++;
            }
            else
            {
                lp1 = lp2;
                lp2 = po;
                p.lineTo(po);
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
                p.cubicTo(c1,c2,lp2);
                kc ++;
                lp1 = lp2;
            }
        }
    }
    this->setPath(p);
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
    if(data(15).toInt() == 1)
    {
        double w = rect().width()/2;
        double h = rect().height()/2;
        QPointF p1;
        p1.setX((w-10)/s);
        p1.setY((h+10)/s);
        QPixmap pix;
        pix.load(":/res/lock.png");
        painter->scale(1,-1);
        painter->drawPixmap(QRectF(p1.x()-w,p1.y()-h-20/s,20/s,20/s),pix,pix.rect());
        painter->scale(1,-1);
    }
    painter->scale(1,-1);
   // painter->drawRect(rect());
    painter->drawPath(path);
    if(data(0).toInt() > 0)
    {
            painter->drawPath(brushpath);
    }
}
MyGraphicsTextItem::~MyGraphicsTextItem()
{

}

bool MyGraphicsTextItem::selectEvent(QPointF p,int k)
{
    if(k == 1)
    {
        setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
        setSelected(true);
        return true;
    }
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
