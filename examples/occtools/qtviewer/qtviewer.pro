include(../../../qmake/compiler_config.pri)

TEMPLATE = app
TARGET   = qtviewer

CONFIG += console

QT += gui
isEqual(QT_MAJOR_VERSION, 5): QT += widgets

FOUGTOOLS_SRCDIR = ../../../src
INCLUDEPATH += $$FOUGTOOLS_SRCDIR

HEADERS += \
    $$FOUGTOOLS_SRCDIR/occtools/qt_view.h \
    qt_view_controller.h

SOURCES += \
    $$FOUGTOOLS_SRCDIR/occtools/qt_view.cpp \
    main.cpp \
    qt_view_controller.cpp

# CASCADE_ROOT must be defined when invoking qmake (eg. qmake CASCADE_ROOT=/opt/lib/occ/build)
include(../../../src/occtools/occ.pri)

LIBS += -lTKernel -lTKMath -lTKBRep -lTKService -lTKV3d
