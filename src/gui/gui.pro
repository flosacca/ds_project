QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gui
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++14

INCLUDEPATH += \
    .. \
    ../lib

HEADERS += \
    mainwindow.h

SOURCES += \
    ../doc.cc \
    ../dom.cc \
    ../extractor.cc \
    file.cc \
    ../splitter.cc \
    mainwindow.cc \
    main.cc

FORMS += \
    mainwindow.ui
