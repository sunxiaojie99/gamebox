#-------------------------------------------------
#
# Project created by QtCreator 2012-08-12T17:12:30
#
#-------------------------------------------------

QT       += core gui

TARGET = scoff_snake
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    game.cpp \
    ball.cpp \
    brick.cpp \
    dynamicbrick.cpp \
    mywidget.cpp \
    double2.cpp

HEADERS  += widget.h \
    game.h \
    ball.h \
    brick.h \
    dynamicbrick.h \
    mywidget.h \
    double2.h


FORMS    += widget.ui \
    game.ui \
    mywidget.ui \
    basicmain.ui \
    double2.ui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

RESOURCES += \
    myresource.qrc
RC_ICONS=myico.ico
QT += core gui multimedia


