#-------------------------------------------------
#
# Project created by QtCreator 2015-02-04T10:31:35
#
#-------------------------------------------------

QT       += core gui serialport multimedia concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HumanMeasureSystem
TEMPLATE = app

DEFINES += NOMINMAX
#DEFINES += NOMINMAX is for include <QDateTime>

SOURCES += main.cpp\
        mainwindow.cpp \
    mpu_9150.cpp \
    mpu_lpms.cpp

HEADERS  += mainwindow.h \
    mpu_9150.h \
    mpu_lpms.h

FORMS    += mainwindow.ui

INCLUDEPATH += $$quote(D:\LIB\Qwt-6.1.2\include)\
               $$quote(D:\LIB\OpenMAT-1.3.4\include)


Release : LIBS +=   $$quote(D:\LIB\Qwt-6.1.2\lib\qwt.lib)\
                    $$quote(D:\LIB\OpenMAT-1.3.4\lib\x86\LpSensor.lib)

Debug : LIBS +=   $$quote(D:\LIB\OpenMAT-1.3.4\lib\x86\LpSensorD.lib)
