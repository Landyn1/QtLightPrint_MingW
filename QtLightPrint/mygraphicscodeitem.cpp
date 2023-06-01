#include "mygraphicscodeitem.h"
#include"mainWindow.h"
#include"ZXingWriter.h"
#include"thirdcurve.h"
MyGraphicsCodeItem::MyGraphicsCodeItem():QGraphicsRectItem()
{

}

MyGraphicsCodeItem::~MyGraphicsCodeItem(){

}
void MyGraphicsCodeItem::rotateY()
{
    double rooty = getRect().y()+(getRect().height()/2);
    rooty = rooty-pos().y();
    QPainterPath p;
    QPainterPath path = this->path;
    for (int i = 0; i < path.elementCount(); i++)
    {
        QPainterPath::Element element = path.elementAt(i);
        QPointF po = element;
        int x1,y1;
        x1 = po.x();
        y1 = rooty*2-po.y();
        if (element.isMoveTo())
        {
            p.moveTo(QPointF(x1,y1));
        }
        else if (element.isLineTo())
        {
            p.lineTo(QPointF(x1,y1));
        }
    }
    this->path = p;
}

void MyGraphicsCodeItem::rotateX()
{
    double rootx = getRect().x()+(getRect().width()/2);
    rootx = rootx-pos().x();
    QPainterPath p;
    QPainterPath path = this->path;
    for (int i = 0; i < path.elementCount(); i++)
    {
        QPainterPath::Element element = path.elementAt(i);
        QPointF po = element;
        int x1,y1;
        x1 = rootx*2-po.x();
        y1 = po.y();
        if (element.isMoveTo())
        {
            p.moveTo(QPointF(x1,y1));
        }
        else if (element.isLineTo())
        {
            p.lineTo(QPointF(x1,y1));
        }
    }
    this->path = p;
}


bool MyGraphicsCodeItem::selectEvent(QPointF p,int k)
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


//将path 充满 rect
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
QRect MyGraphicsCodeItem::getRect()
{
    int x,y,w,h;
    x = rect().x()+pos().x();
    y = rect().y()+pos().y();
    w = rect().width();
    h = rect().height();
    return QRect(x,y,w,h);
}

//根据codetype 和 str 获取code的path 这里后续还需要填写各个codetype的限制
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
    set_brush(this->angle,this->space);
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
    if(data(0).toInt() > 0)
    {
            painter->drawPath(brushPath);
    }
    painter->drawPath(this->path);

}
QPainterPath MyGraphicsCodeItem::ViewPath(int k)
{
    QPainterPath p;
    QPainterPath path = this->path;
    for (int i = 0; i < path.elementCount(); i++)
    {
        QPainterPath::Element element = path.elementAt(i);
        QPointF po = element;
        po.setY(-po.y());
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
    if(k == 0)
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
bool MyGraphicsCodeItem::set_brush(double angle, double space)
{
    this->angle = angle;
    double dpiX = QApplication::primaryScreen()->physicalDotsPerInchX();
    double  temp = (dpiX * 10) / 254; //1mm = tpx
    double maxh = fmax(this->getRect().width(),this->getRect().height());
    double linenum = (maxh/temp) / space;
    this->space = space;
    brushPath.clear();
    if(space == 0)
    {
        update();
        return true;
    }
    QPainterPath path2;
    double k = tan(angle*M_PI/180);//斜率
    int w = path.boundingRect().width()+10;
    int h = path.boundingRect().height()+10;
    QList<QPointF> intersections;
    QList<QLineF> lins;
    setLinsAndCurves(this->path,lins);
    double mint = (dpiX*10)/254;; //1mm = tpx;
    mint = mint*0.02; //0.02mm = tpx; 最小的线间距0.02mm
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
                setBrushpath(lins,l,intersections,path2);
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
                setBrushpath(lins,l,intersections,path2);           }
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
                setBrushpath(lins,l,intersections,path2);
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
                setBrushpath(lins,l,intersections,path2);
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
                setBrushpath(lins,l,intersections,path2);
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
                setBrushpath(lins,l,intersections,path2,1);
            }
        }

    }
    brushPath = path2;
    update();
}

void MyGraphicsCodeItem::setLinsAndCurves(QPainterPath path2,QList<QLineF> &lins)
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
                //curves.append(curve);
                kc ++;
                lp1 = lp2;
            }
        }
    }
}

void MyGraphicsCodeItem::setBrushpath(QList<QLineF> lins,QLineF l,QList<QPointF> intersections,QPainterPath &path2,int k)
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
void MyGraphicsCodeItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{

}
void MyGraphicsCodeItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{

}
void MyGraphicsCodeItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}
