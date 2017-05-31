#-------------------------------------------------
#
# Project created by QtCreator 2017-05-16T14:48:12
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HEUIndoorLocation
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    titlewidget.cpp \
    tool_button.cpp \
    push_button.cpp \
    main_widget.cpp \
    util.cpp \
    contentwidget.cpp \
    warningwidget.cpp \
    basestation/basestationdao.cpp \
    basestation/basemodel.cpp \
    basestation/jizhan.cpp \
    basestation/jzwidget.cpp \
    attence/kqwidget.cpp \
    camera/bqwidget.cpp \
    label/truebqwidget.cpp \
    Maps/mapwidget.cpp \
    Maps/paintarea.cpp \
    Maps/ellipse.cpp \
    Maps/polygon.cpp \
    Maps/shape.cpp \
    Maps/line.cpp \
    Maps/rect.cpp \
    Maps/pen.cpp \
    Maps/mapdraw.cpp

HEADERS  += mainwindow.h \
    titlewidget.h \
    tool_button.h \
    push_button.h \
    main_widget.h \
    util.h \
    contentwidget.h \
    warningwidget.h \
    basestation/basestationdao.h \
    basestation/basemodel.h \
    basestation/jizhan.h \
    basestation/jzwidget.h \
    attence/kqwidget.h \
    camera/bqwidget.h \
    label/truebqwidget.h \
    Maps/mapwidget.h \
    Maps/paintarea.h \
    Maps/ellipse.h \
    Maps/polygon.h \
    Maps/shape.h \
    Maps/type.h \
    Maps/line.h \
    Maps/rect.h \
    Maps/pen.h \
    Maps/mapdraw.h

FORMS    += mainwindow.ui \
    titlewidget.ui \
    main_widget.ui \
    contentwidget.ui \
   # jzwidget.ui \
   # bqwidget.ui \
   # kqwidget.ui \
   # truebqwidget.ui \
    basestation/jzwidget.ui \
    attence/kqwidget.ui \
    camera/bqwidget.ui \
    label/truebqwidget.ui \
    Maps/mapwidget.ui \
    Maps/mapdraw.ui

RESOURCES += \
    image.qrc
