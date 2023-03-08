#include "mainWindow.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainWindow w;
    w.show();
    
    //test_main();
    return a.exec();
	return 0;
}
