QT       += core gui

QT += pdf

QT += testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    sources/csvviewer.cpp \
    sources/fileviewer.cpp \
    sources/highlightstrategy.cpp \
    sources/imageviewer.cpp \
    sources/main.cpp \
    sources/mainwindow.cpp \
    sources/pdfviewer.cpp \
    sources/tabwidget.cpp \
    sources/txtviewer.cpp \
    sources/viewerfactory.cpp \
    sources/zoomcommand.cpp

HEADERS += \
    headers/csvviewer.h \
    headers/fileviewer.h \
    headers/highlightstrategy.h \
    headers/imageviewer.h \
    headers/mainwindow.h \
    headers/pdfviewer.h \
    headers/tabwidget.h \
    headers/txtviewer.h \
    headers/ui_mainwindow.h \
    headers/viewerfactory.h \
    headers/zoomcommand.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc \
    resources.qrc

DISTFILES += \
    .gitignore \
    README.md \
    config.qdocconf
