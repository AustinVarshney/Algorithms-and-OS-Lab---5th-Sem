QT += core gui widgets

CONFIG += c++11

TARGET = SchedulerSimulator
TEMPLATE = app

SOURCES += \
    main.cpp \
    schedulerwindow.cpp \
    schedulingcore.cpp

HEADERS += \
    schedulerwindow.h \
    schedulingcore.h