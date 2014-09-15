TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

QMAKE_CXXFLAGS += -std=c++1y

INCLUDEPATH += $${PWD}/../../

include(deployment.pri)
qtcAddDeployment()

