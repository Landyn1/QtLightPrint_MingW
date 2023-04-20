# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Tools.
# ------------------------------------------------------
QT += core gui widgets \
    quick
QT += xml
TEMPLATE = app
TARGET = QtLightPrint
DESTDIR = ../QtLightPrint/debug
CONFIG += debug
LIBS += -L"."
DEPENDPATH += .
MOC_DIR += .
OBJECTS_DIR += debug
UI_DIR += .
RCC_DIR += .
HEADERS += ./CUDrvE.h \
    ./ItemAdjust.h \
    ./MyGraphicsCircleItem.h \
    ./MyGraphicsEllipseItem.h \
    ./MyGraphicsRecItem.h \
    ./PrintParams.h \
    ./MyKedu.h \
    ./MyMianArea.h \
    ./MygraphicsLinePre.h \
    ./MyleftKedu.h \
    ./MyGraphicsScene.h \
    ./MyGraphicsView.h \
    ./mainWindow.h \
    CUDrvE.h \
    CUDrvE_global.h \
    ZXingWriter.h \
    advancedwidget.h \
    bottomdockwidget.h \
    configtabwidget.h \
    configtabwidgetarea.h \
    configtabwidgetlasercontrol.h \
    configtabwidgetother.h \
    configtabwidgetport.h \
    configtabwidgetred.h \
    configwidget.h \
    dialogcalculaterecommendvalues.h \
    dialogcalculationratio.h \
    dialogpasswordsetting.h \
    itemfileclass.h \
    mygraphicscodeitem.h \
    mygraphicscurvelineitem.h \
    mygraphicsheplbrushrectitem.h \
    mygraphicslineitem.h \
    mygraphicspixmapitem.h \
    mygraphicspolygonitem.h \
    mygraphicstextitem.h \
    mylabel.h \
    widgetco2.h \
    widgetfiber.h \
    widgetuv.h \
    widgetyag.h
SOURCES += ./ItemAdjust.cpp \
    ./MyGraphicsCircleItem.cpp \
    ./MyGraphicsEllipseItem.cpp \
    ./MyGraphicsRecItem.cpp \
    ./MyGraphicsScene.cpp \
    ./MyGraphicsView.cpp \
    ./MyKedu.cpp \
    ./MyMianArea.cpp \
    ./MygraphicsLinePre.cpp \
    ./MyleftKedu.cpp \
    ./main.cpp \
    ./mainWindow.cpp \
    ./PrintParams.cpp \
    advancedwidget.cpp \
    bottomdockwidget.cpp \
    configtabwidget.cpp \
    configtabwidgetarea.cpp \
    configtabwidgetlasercontrol.cpp \
    configtabwidgetother.cpp \
    configtabwidgetport.cpp \
    configtabwidgetred.cpp \
    configwidget.cpp \
    dialogcalculaterecommendvalues.cpp \
    dialogcalculationratio.cpp \
    dialogpasswordsetting.cpp \
    itemfileclass.cpp \
    mygraphicscodeitem.cpp \
    mygraphicscurvelineitem.cpp \
    mygraphicsheplbrushrectitem.cpp \
    mygraphicslineitem.cpp \
    mygraphicspixmapitem.cpp \
    mygraphicspolygonitem.cpp \
    mygraphicstextitem.cpp \
    mylabel.cpp \
    widgetco2.cpp \
    widgetfiber.cpp \
    widgetuv.cpp \
    widgetyag.cpp
FORMS += ./mainWindow.ui
RESOURCES += mainWindow.qrc \
    mainWindow.qrc

DISTFILES += \
    .editorconfig \
    .gitattributes \
    .qmake.stash \
    QtLightPrint.pri \
    QtLightPrint.pro.user \
    cpp.hint


LIBS += -L$$PWD/libs/ -lCUDrvE libZXingWriter