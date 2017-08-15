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
