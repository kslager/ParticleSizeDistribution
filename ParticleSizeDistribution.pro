QT += core gui charts widgets

TARGET = PSD
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

HEADERS += \
    mainwindow.h \
    soil.h \
    psdview.h \
    psdwidget.h \
    soilmodel.h

FORMS +=

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    psdview.cpp \
    psdwidget.cpp \
    soilmodel.cpp

INCLUDEPATH += ../boost_1_64_0/
QMAKE_CXXFLAGS += -std=c++11
