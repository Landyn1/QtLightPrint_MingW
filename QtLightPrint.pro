# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Tools.
# ------------------------------------------------------
QT += core gui widgets \
    quick
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
    mygraphicscurvelineitem.h \
    mygraphicslineitem.h \
    mygraphicspolygonitem.h \
    mygraphicstextitem.h
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
    mygraphicscurvelineitem.cpp \
    mygraphicslineitem.cpp \
    mygraphicspolygonitem.cpp \
    mygraphicstextitem.cpp
FORMS += ./mainWindow.ui
RESOURCES += mainWindow.qrc
LIBS += -LD:\QtCode\QtLightPrint_mingw\QtLightPrint\debug\ -lCUDrvE
