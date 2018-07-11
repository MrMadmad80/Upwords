TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += main.cpp \
    mieFunzioni.cpp \
    funzioniDizionario.cpp \
    funzioniStampa.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    mieFunzioni.h \
    funzioniDizionario.h \
    funzioniStampa.h \
    costanti.h

