#include "qlptfilehandle.h"
#include"qfiledialog.h"
#include<qmessagebox.h>
#include<qfiledialog.h>
#include"qbuffer.h"
#include"GraphicsItems/mylabel.h"
qlptfileHandle::qlptfileHandle()
{

}
template<typename T> void qlptfileHandle::saveItems(QGraphicsItem* node, ItemFileClass *&iff,int type)
{
    T *item = qgraphicsitem_cast<T *>(node);
    iff->name = item->name;
    iff->angle = item->angle;
    iff->space = item->space;
    iff->rec = item->rect();
    iff->id = item->data(0).toInt();
    iff->pos = item->pos();
    iff->type = type;
}

void qlptfileHandle::createnewfile(mainWindow *mw,QWidget *th,QString filename)
{
    QWidget *widgetfile = new QWidget();

    //widgetfile->setParent(ui.scrollArea_3);
    QHBoxLayout *lay = new QHBoxLayout();
    QPushButton *close_file =new QPushButton("×");
    myLabel *label_file= new myLabel(mw->filenum);
    label_file->setText(filename);
    lay->addWidget(label_file);
    lay->addWidget(close_file);
    lay->setMargin(0);
    label_file->adjustSize();
    QSize file1_size = label_file->size();
    int file1_w = file1_size.width();
    //label_file->resize(file1_w,30);
    label_file->setMinimumSize(QSize(file1_w,30));
    label_file->setMaximumSize(QSize(file1_w,30));

    close_file->setMinimumSize(QSize(20,20));
    close_file->setMaximumSize(QSize(20,20));
    widgetfile->setStyleSheet("QWidget{background-color:rgb(255,255,255);}");
    close_file->setStyleSheet("QPushButton{background-color:rgb(240,240,240)}");
    widgetfile->setMinimumSize(QSize(file1_w+20,30));
    widgetfile->setMaximumSize(QSize(file1_w+20,30));
    widgetfile->setLayout(lay);
    mw->m_file->setAlignment(Qt::AlignLeft);
    mw->m_file->setMargin(0);
    mw->m_file->addWidget(widgetfile);
    mw->files->setLayout(mw->m_file);
    mw->ui.scrollArea_3->setWidget(mw->files);
    mw->filenum++;
    mw->fileid++;
    MyGraphicsScene *scene1 = new MyGraphicsScene();
    MyGraphicsView *view1 = new MyGraphicsView();
    //添加
    mw->connect(view1, &MyGraphicsView::addItem,mw->ui.itemtable, [=](int row,QGraphicsItem * item) {
        mw->additem(row,item);
    });
    mw->scenes.append(scene1);
    mw->views.append(view1);
    mw->isfirst.append(true);
    mw->connect(label_file,&myLabel::clicked,[=](int id){
       mw-> scene = mw->scenes[id];
        mw->view = mw->views[id];
        mw->view->setScene(mw->scene);
        mw->view->setStatusBarPtr(mw->ui.statusBar);
        while(mw->ui.itemtable->rowCount()>0)
        {
           mw->ui.itemtable->removeRow(0);
        }
        //ui.itemtable->removeRow(0);

        QList<QGraphicsItem*> visibleItems;
        QList<QGraphicsItem*> items = mw->scene->items();
        for(int i=0;i<items.length();i++)
        {
            if(items[i]->data(0).toInt()>0)
            {
                visibleItems.append(items[i]);
            }
        }
        int l = visibleItems.length();
        QGraphicsItem *temp;
        for(int i=0;i<l-1;i++)
        {
            for(int j=0;j<l-i-1;j++)
            {
                if(visibleItems[j]->data(0).toInt()>visibleItems[j+1]->data(0).toInt())
                {
                    temp = visibleItems[j];
                    visibleItems[j] = visibleItems[j+1];
                    visibleItems[j+1] = temp;
                }
            }
        }
        for(int i=0;i<l;i++)
        {
            emit mw->view->addItem(i,visibleItems[i]);
        }
        if(mw->isfirst[id])
        {
            mw->view->setMouseTracking(true);
            mw->view->preProcessItem();
            mw->scene->setBackgroundBrush(Qt::white);
            mw->scene->setSceneRect(-10000, -10000, 20000, 20000);
            mw->view->setAlignment(Qt::AlignCenter);
            mw->view->scale(1, -1);
            mw->view->topkedu->setPos(0, mw->view->mapToScene(0, 0).y() );
            mw->view->leftkedu->setPos(mw->view->mapToScene(0, 0).x(),0);
            mw->scene->update();
            mw->initConnect();
            mw->isfirst[id]=false;
        }
        mw->ui.dock4->setWidget(mw->view);
        mw->view->centerOn(QPointF(0, 0));
        for(int i=0;i<mw->m_file->count();i++)
        {
            QLayoutItem* item = mw->m_file->itemAt(i);
            QWidget* widget = item->widget();
            widget->setStyleSheet("QWidget{background-color:rgb(190,190,190);}");
            QPushButton *btn = widget->findChild<QPushButton *>();
            btn->setStyleSheet("QPushButton{background-color:rgb(180,180,180)}");
        }

        widgetfile->setStyleSheet("QWidget{background-color:rgb(255,255,255);}");
        close_file->setStyleSheet("QPushButton{background-color:rgb(240,240,240)}");

    });
    emit label_file->clicked(label_file->id);

    mw->connect(close_file,&QPushButton::clicked,th,[=](){

        //lay->removeWidget(label_file);
        //lay->removeWidget(close_file);
        if(mw->m_file->count() == 1)
        {
            mw->ui.dock4->setWidget(NULL);
        }
        for(int i=0;i<mw->m_file->count();i++)
        {
            QLayoutItem* item = mw->m_file->itemAt(i);
            QWidget* widget = item->widget();
            myLabel *l = widget->findChild<myLabel *>();
            if(l->id==label_file->id-1)
            {
                emit l->clicked(l->id);
            }
            if(l->id>label_file->id)
            {
                l->id = l->id-1;
            }
        }

        widgetfile->setParent(NULL);
        mw->m_file->removeWidget(widgetfile);
        delete widgetfile;

        mw->isfirst[mw->filenum-1] = true;
        mw->files->setLayout(mw->m_file);
        mw->ui.scrollArea_3->setWidget(mw->files);

        mw->filenum--;

        mw->scenes.removeOne(scene1);
        mw->views.removeOne(view1);

    });
}

void qlptfileHandle::createnewfile(mainWindow *mw,QWidget *th)
{
    QWidget *widgetfile = new QWidget();

    //widgetfile->setParent(ui.scrollArea_3);
    QHBoxLayout *lay = new QHBoxLayout();
    QPushButton *close_file =new QPushButton("×");
    myLabel *label_file= new myLabel(mw->filenum);
    label_file->setText(("file")+QString::number(mw->fileid+1));
    lay->addWidget(label_file);
    lay->addWidget(close_file);
    lay->setMargin(0);
    label_file->adjustSize();
    QSize file1_size = label_file->size();
    int file1_w = file1_size.width();
    //label_file->resize(file1_w,30);
    label_file->setMinimumSize(QSize(file1_w,30));
    label_file->setMaximumSize(QSize(file1_w,30));

    close_file->setMinimumSize(QSize(20,20));
    close_file->setMaximumSize(QSize(20,20));
    widgetfile->setStyleSheet("QWidget{background-color:rgb(255,255,255);}");
    close_file->setStyleSheet("QPushButton{background-color:rgb(240,240,240)}");
    widgetfile->setMinimumSize(QSize(file1_w+20,30));
    widgetfile->setMaximumSize(QSize(file1_w+20,30));
    widgetfile->setLayout(lay);
    mw->m_file->setAlignment(Qt::AlignLeft);
    mw->m_file->setMargin(0);
    mw->m_file->addWidget(widgetfile);
    mw->files->setLayout(mw->m_file);
    mw->ui.scrollArea_3->setWidget(mw->files);
    mw->filenum++;
    mw->fileid++;
    MyGraphicsScene *scene1 = new MyGraphicsScene();
    MyGraphicsView *view1 = new MyGraphicsView();
    //添加
    mw->connect(view1, &MyGraphicsView::addItem,mw->ui.itemtable, [=](int row,QGraphicsItem * item) {
        mw->additem(row,item);
    });
    mw->scenes.append(scene1);
    mw->views.append(view1);
    mw->isfirst.append(true);
    mw->connect(label_file,&myLabel::clicked,[=](int id){
       mw-> scene = mw->scenes[id];
        mw->view = mw->views[id];
        mw->view->setScene(mw->scene);
        mw->view->setStatusBarPtr(mw->ui.statusBar);
        while(mw->ui.itemtable->rowCount()>0)
        {
           mw->ui.itemtable->removeRow(0);
        }
        //ui.itemtable->removeRow(0);

        QList<QGraphicsItem*> visibleItems;
        QList<QGraphicsItem*> items = mw->scene->items();
        for(int i=0;i<items.length();i++)
        {
            if(items[i]->data(0).toInt()>0)
            {
                visibleItems.append(items[i]);
            }
        }
        int l = visibleItems.length();
        QGraphicsItem *temp;
        for(int i=0;i<l-1;i++)
        {
            for(int j=0;j<l-i-1;j++)
            {
                if(visibleItems[j]->data(0).toInt()>visibleItems[j+1]->data(0).toInt())
                {
                    temp = visibleItems[j];
                    visibleItems[j] = visibleItems[j+1];
                    visibleItems[j+1] = temp;
                }
            }
        }
        for(int i=0;i<l;i++)
        {
            emit mw->view->addItem(i,visibleItems[i]);
        }
        if(mw->isfirst[id])
        {
            mw->view->setMouseTracking(true);
            mw->view->preProcessItem();
            mw->scene->setBackgroundBrush(Qt::white);
            mw->scene->setSceneRect(-10000, -10000, 20000, 20000);
            mw->view->setAlignment(Qt::AlignCenter);
            mw->view->scale(1, -1);
            mw->view->topkedu->setPos(0, mw->view->mapToScene(0, 0).y() );
            mw->view->leftkedu->setPos(mw->view->mapToScene(0, 0).x(),0);
            mw->scene->update();
            mw->initConnect();
            mw->isfirst[id]=false;
        }
        mw->ui.dock4->setWidget(mw->view);
        mw->view->centerOn(QPointF(0, 0));
        for(int i=0;i<mw->m_file->count();i++)
        {
            QLayoutItem* item = mw->m_file->itemAt(i);
            QWidget* widget = item->widget();
            widget->setStyleSheet("QWidget{background-color:rgb(190,190,190);}");
            QPushButton *btn = widget->findChild<QPushButton *>();
            btn->setStyleSheet("QPushButton{background-color:rgb(180,180,180)}");
        }

        widgetfile->setStyleSheet("QWidget{background-color:rgb(255,255,255);}");
        close_file->setStyleSheet("QPushButton{background-color:rgb(240,240,240)}");

    });
    emit label_file->clicked(label_file->id);

    mw->connect(close_file,&QPushButton::clicked,th,[=](){

        //lay->removeWidget(label_file);
        //lay->removeWidget(close_file);
        if(mw->m_file->count() == 1)
        {
            mw->ui.dock4->setWidget(NULL);
        }
        for(int i=0;i<mw->m_file->count();i++)
        {
            QLayoutItem* item = mw->m_file->itemAt(i);
            QWidget* widget = item->widget();
            myLabel *l = widget->findChild<myLabel *>();
            if(l->id==label_file->id-1)
            {
                emit l->clicked(l->id);
            }
            if(l->id>label_file->id)
            {
                l->id = l->id-1;
            }
        }

        widgetfile->setParent(NULL);
        mw->m_file->removeWidget(widgetfile);
        delete widgetfile;

        mw->isfirst[mw->filenum-1] = true;
        mw->files->setLayout(mw->m_file);
        mw->ui.scrollArea_3->setWidget(mw->files);

        mw->filenum--;

        mw->scenes.removeOne(scene1);
        mw->views.removeOne(view1);

    });
}

void qlptfileHandle::openfile(mainWindow *mw,QWidget* th)
{
    QFileDialog dialog(th);
    QStringList fileNames;
    QStringList types;
    types.append("TEXT (*.qlpt))");
    types.append("ALL (*.*))");
    dialog.setNameFilters(types);
    if (dialog.exec()) {
        fileNames = dialog.selectedFiles();
        QString fileName = fileNames[0];
        QFile file(fileName);
        QStringList name = fileName.split('/');
        QStringList types = fileName.split('.');
        QString type = types[types.length()-1];
        mw->creatnewfile(name[name.length()-1]);
        if(type == "plt")
        {
            MyGraphicsLineItem *item = new MyGraphicsLineItem();
            item->setPath(mw->pltfilehanler->readPLT(fileName));
            item->name = ("群组")+QString::number(mw->view->row+1);
            item->setPos(0,0);
            item->setVisible(true);
            mw->scene->addItem(item);
            mw->view->row++;
            item->setData(0,mw->view->item_id);
            mw->view->item_id++;
            emit mw->view->addItem(mw->view->row-1,item);
            return;
        }

        if (!file.open (QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(th, ("Error"), ("Selected file is not  correct."));
        }
        else {
            QDataStream in(&file);
            QList<QGraphicsItem *> items;
            while (!in.atEnd())
            {
                ItemFileClass t;
                in>>t;

                if(t.type == 1)
                {
                    MyGraphicsRecItem *item = new MyGraphicsRecItem();
                    item->setPos(t.pos);
                    item->setRect(t.rec);
                    item->name = t.name;
                    item->setData(0,t.id);
                    item->angle = t.angle;
                    item->space = t.space;
                    item->set_brush(item->angle,item->space);
                    mw->scene->addItem(item);
                    item->setVisible(true);
                    mw->scene->update();
                    items.append(item);
                    //emit mw->view->addItem(mw->view->row,item);
                    mw->view->row++;
                    if(mw->view->item_id<t.id)
                        mw->view->item_id = t.id;
                }
                else if(t.type == 2)
                {
                    MyGraphicsEllipseItem* item = new MyGraphicsEllipseItem();
                    item->setPos(t.pos);
                    item->setRect(t.rec);
                    item->name = t.name;
                    item->setData(0,t.id);
                    item->angle = t.angle;
                    item->space = t.space;
                    item->set_brush(item->angle,item->space);
                    mw->scene->addItem(item);
                    item->setVisible(true);
                    mw->scene->update();
                    items.append(item);
                    //emit mw->view->addItem(mw->view->row,item);
                    mw->view->row++;
                    if(mw->view->item_id<t.id)
                        mw->view->item_id = t.id;
                }
                else if(t.type == 3)
                {
                    MyGraphicsCircleItem *item = new MyGraphicsCircleItem();
                    item->setPos(t.pos);
                    item->setRect(t.rec);
                    item->name = t.name;
                    item->setData(0,t.id);
                    item->angle = t.angle;
                    item->space = t.space;
                    item->set_brush(item->angle,item->space);
                    mw->scene->addItem(item);
                    item->setVisible(true);
                    mw->scene->update();
                    items.append(item);
                    //emit mw->view->addItem(mw->view->row,item);
                    mw->view->row++;
                    if(mw->view->item_id<t.id)
                        mw->view->item_id = t.id;
                }
                else if(t.type == 4)
                {
                    MyGraphicsLineItem *item = new MyGraphicsLineItem();
                    if(t.text != "")
                    {
                        t.setPathByText();
                    }
                    item->setPath(t.path);
                    item->setVisible(true);
                    item->setData(0, t.id);
                    item->setPos( t.pos);
                    item->name=t.name;
                    item->angle = t.angle;
                    item->space = t.space;
                    item->set_brush(item->angle,item->space);
                    mw->scene->addItem(item);
                    items.append(item);
                    //emit mw->view->addItem(mw->view->row,item);
                    mw->view->row++;
                    if(mw->view->item_id<t.id)
                        mw->view->item_id = t.id;
                }
                else if(t.type == 5)
                {
                    MyGraphicsPolygonItem *item = new MyGraphicsPolygonItem();
                    item->setPath(t.path);
                    item->setRect(t.rec);
                    item->setVisible(true);
                    item->setData(0, t.id);
                    item->setPos( t.pos);
                    item->angle = t.angle;
                    item->space = t.space;
                    item->set_brush(item->angle,item->space);
                    item->name=t.name;
                    mw->scene->addItem(item);
                    items.append(item);
                    //emit mw->view->addItem(mw->view->row,item);
                    mw->view->row++;
                    if(mw->view->item_id<t.id)
                        mw->view->item_id = t.id;
                }
                else if(t.type == 6)
                {
                    MyGraphicsTextItem *item = new MyGraphicsTextItem();
                    item->name = t.name;
                    item->setRect(t.rec);
                    item->setVisible(true);
                    item->setData(0, t.id);
                    item->setPos( t.pos);
                    item->path = t.path;
                    item->setStr(t.text,t.font);
                    item->angle = t.angle;
                    item->space = t.space;
                    item->set_brush(item->angle,item->space);
                    mw->scene->addItem(item);
                    items.append(item);
                    //emit mw->view->addItem(mw->view->row,item);
                    mw->view->row++;
                    if(mw->view->item_id<t.id)
                        mw->view->item_id = t.id;
                }
                else if(t.type == 7)
                {
                    MyGraphicsCurveLineItem * item = new MyGraphicsCurveLineItem();
                    item->name = t.name;
                    item->setVisible(true);
                    item->setData(0, t.id);
                    item->setPos( t.pos);
                    item->setPath(t.path);
                    mw->scene->addItem(item);
                    items.append(item);
                    //emit mw->view->addItem(mw->view->row,item);
                    mw->view->row++;
                    if(mw->view->item_id<t.id)
                        mw->view->item_id = t.id;
                }

                else if(t.type == 8)
                {
                    QPixmap pix;
                    pix.loadFromData(QByteArray::fromBase64(t.pix.toLocal8Bit()));

                    MyGraphicsPixMapItem *item = new MyGraphicsPixMapItem();
                    item->name = t.name;
                    item->setVisible(true);
                    item->setData(0, t.id);
                    item->setPos( t.pos);
                    item->setRectF(t.rec.toRect());
                    item->setPixmap(pix);
                    mw->scene->addItem(item);
                    items.append(item);
                    //emit mw->view->addItem(mw->view->row,item);
                    mw->view->row++;
                    if(mw->view->item_id<t.id)
                        mw->view->item_id = t.id;
                }
                else if(t.type == 9)
                {

                    MyGraphicsCodeItem *item = new MyGraphicsCodeItem();
                    //item->setPathByStr(t.text,t.codetype);
                    item->text = t.text;
                    item->codetype = t.codetype;
                    item->path = (t.path);
                    item->angle = t.angle;
                    item->space = t.space;
                    item->setRect(t.rec);
                    item->set_brush(item->angle,item->space);
                    item->setVisible(true);
                    item->setData(0, t.id);
                    item->setPos( t.pos);
                    item->name=t.name;
                    mw->scene->addItem(item);
                    items.append(item);
                    //emit mw->view->addItem(mw->view->row,item);
                    mw->view->row++;
                    if(mw->view->item_id<t.id)
                        mw->view->item_id = t.id;
                }
            }
            mw->view->item_id++;
            int l = items.length();
            QGraphicsItem *temp;
            for(int i=0;i<l-1;i++)
            {
                for(int j=0;j<l-i-1;j++)
                {
                    if(items[j]->data(0).toInt()>items[j+1]->data(0).toInt())
                    {
                        temp = items[j];
                        items[j] = items[j+1];
                        items[j+1] = temp;
                    }
                }
            }
            for(int i=0;i<l;i++)
            {
                emit mw->view->addItem(i,items[i]);
            }

        }
        file.close ();
    }

}




void qlptfileHandle::savefile(QList<QGraphicsItem*> items,QWidget *mw)
{

        QString fileName = QFileDialog::getSaveFileName(mw,
            ("保存"),
            "",
            ("TEXT Files (*.qlpt)"));
        if(fileName.isNull())
        {
            return;
        }
        QFile file(fileName);
        if (!file.open(QFileDevice::WriteOnly | QFileDevice::Truncate))
        {
            QMessageBox::warning(mw, ("Error"), ("打开文件错误!"));
        }

        //下附各个图元
        QDataStream out(&file);
        for(QGraphicsItem * node:items)
        {
            if(node->data(0).toInt()>0)
            {
                ItemFileClass *iff = new ItemFileClass();
                if(node->type() == 1 )
                {
                    saveItems<MyGraphicsRecItem>(node,iff,1);
                }
                else if(node->type() == 2)
                {
                    saveItems<MyGraphicsEllipseItem>(node,iff,2);
                }
                else if(node->type() == 3)
                {
                    saveItems<MyGraphicsCircleItem>(node,iff,3);
                }
                else if(node->type() ==  4)
                {
                    saveItems<MyGraphicsLineItem>(node,iff,4);
                    MyGraphicsLineItem *item = qgraphicsitem_cast<MyGraphicsLineItem *>(node);
                    QString path_str;
                    if(item->path().elementCount()>20)
                    {
                        int num = 0;
                        while(num < item->path().elementCount())
                        {
                            QPainterPath::Element element = item->path().elementAt(num);
                            QPointF po = element;
                            if (element.isMoveTo())
                            {
                                QString po_str = "move "+QString::number(po.x())+" "+QString::number(po.y())+";";
                                path_str += po_str;
                            }
                            else
                            {
                                QString po_str = "line "+QString::number(po.x())+" "+QString::number(po.y())+";";
                                path_str += po_str;
                            }
                            num++;
                        }
                        iff->text = path_str;
                    }
                    else
                    {
                        iff->path = item->path();
                    }
                }
                else if(node->type() == 5)
                {
                    saveItems<MyGraphicsPolygonItem>(node,iff,5);
                    MyGraphicsPolygonItem *item = qgraphicsitem_cast<MyGraphicsPolygonItem *>(node);
                    iff->path = item->path;
                    iff->bian_num = item->num;
                }
                else if(node->type() == 6)
                {
                    saveItems<MyGraphicsTextItem>(node,iff,6);
                    MyGraphicsTextItem *item = qgraphicsitem_cast<MyGraphicsTextItem *>(node);
                    iff->path = item->path;
                    iff->font = item->font;
                    iff->text = item->str;
                }
                else if(node->type() == 7)
                {
                    saveItems<MyGraphicsCurveLineItem>(node,iff,7);
                    MyGraphicsCurveLineItem *item = qgraphicsitem_cast<MyGraphicsCurveLineItem *>(node);
                    iff->path = item->path();
                }
                else if(node->type() == 8)
                {
                    MyGraphicsPixMapItem *item = qgraphicsitem_cast<MyGraphicsPixMapItem *>(node);
                    iff->name = item->name;
                    iff->id = item->data(0).toInt();
                    iff->rec = item->rectf;
                    iff->pos = item->pos();
                    iff->pixAdr = item->filename;
                    iff->type =item->type();
                    QImage img = item->pixmap().toImage();
                    QByteArray ba;
                    QBuffer buf(&ba);
                    img.save(&buf, "png");
                    iff->pix = ba.toBase64();
                }
                else if(node->type() == 9)
                {
                    saveItems<MyGraphicsCodeItem>(node,iff,9);
                    MyGraphicsCodeItem *item = qgraphicsitem_cast<MyGraphicsCodeItem *>(node);
                    iff->path = item->path;
                    iff->text = item->text;
                    iff->codetype = item->codetype;
                }
                out<<*iff;
            }
        }
        file.close();
}
