QT += testlib
QT -= gui
QT += widgets

QT += pdf

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_pdfviewertest.cpp \
    sources/main.cpp \
    sources/tst_csvviewertest.cpp \
    sources/tst_highlightstrategytest.cpp \
    sources/tst_imageviewertest.cpp \
    sources/tst_textviewertest.cpp
SOURCES += $$files(D:/Qt/projects/file-reader/sources/*.cpp)
SOURCES -= $$files(D:/Qt/projects/file-reader/sources/main.cpp)
HEADERS += $$files(D:/Qt/projects/file-reader/headers/*.h) \
    headers/tst_csvviewertest.h \
    headers/tst_highlightstrategytest.h \
    headers/tst_imageviewertest.h \
    headers/tst_pdfviewertest.h \
    headers/tst_textviewertest.h
