#-------------------------------------------------
#
# Project created by QtCreator 2011-10-24T22:07:38
#
#-------------------------------------------------

QT       += core gui
QT		 += opengl
#QT       -= gui

    INCLUDEPATH += /usr/include/OGRE
    CONFIG += link_pkgconfig
    PKGCONFIG += OGRE


    INCLUDEPATH += /usr/include/OIS
    CONFIG += link_pkgconfig
    PKGCONFIG += OIS

    INCLUDEPATH += /usr/include/sigc++-2.0
    CONFIG += link_pkgconfig
    PKGCONFIG += sigc++-2.0


TARGET = cppex
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app





CONFIG(debug, debug|release) {
    TARGET = $$join(TARGET,,,d)
    #LIBS *= -lOgreMain_d
}
CONFIG(release, debug|release):LIBS *= -lOgreMain
CONFIG(release, debug|release):LIBS *= -lCEGUIOgreRenderer
CONFIG(release, debug|release):LIBS *= -lCEGUIBase
CONFIG(release, debug|release):LIBS *= -lOIS

SOURCES += main.cpp \
    MButtonCanvasObject.cpp \
    MButtonEventEmitter.cpp \
    MButtonWidget.cpp \
    BaseApplication.cpp \
    MApplication.cpp \
    MCheckButtonWidget.cpp \
    tinystr.cpp \
    tinyxml.cpp \
    tinyxmlerror.cpp \
    tinyxmlparser.cpp \
    DotSceneLoader.cpp

HEADERS += \
    MApplication.h \
    MButtonCanvasObject.h \
    MButtonEventEmitter.h \
    MButtonWidget.h \
    BaseApplication.h \
    MApplication.h \
    MCheckButtonWidget.h \
    tinystr.h \
    tinyxml.h \
    DotSceneLoader.h








