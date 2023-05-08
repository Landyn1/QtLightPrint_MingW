#include "mainWindow.h"
#include <QApplication>
#include<qtranslator.h>
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication a(argc, argv);
    QString runPath = QCoreApplication::applicationDirPath();
    qDebug()<<runPath<<endl;
    static QTranslator *qtTranslator = new QTranslator;
    if(qtTranslator->load(runPath+"/lang_zh_CN.qm")){
        a.installTranslator(qtTranslator);
    }
    mainWindow w;
    w.resize(1500,800);
    w.show();
    
    return a.exec();
	return 0;
}
