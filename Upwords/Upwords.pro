TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += main.cpp \
    funzioniDizionario.cpp \
    funzioniStampa.cpp \
    funzioniControllo.cpp \
    funzioniGioco.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    funzioniDizionario.h \
    funzioniStampa.h \
    costanti.h \
    funzioniControllo.h \
    funzioniGioco.h

