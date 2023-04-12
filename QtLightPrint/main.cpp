#include "mainWindow.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    mainWindow w;
    w.resize(1500,800);
    w.show();
    
    //test_main();
    return a.exec();
	return 0;
}
