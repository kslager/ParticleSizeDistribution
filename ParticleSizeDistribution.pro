QT += core gui charts widgets

TARGET = PSD
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

HEADERS += \
    mainwindow.h \
    soil.h

FORMS +=

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    soil.cpp
