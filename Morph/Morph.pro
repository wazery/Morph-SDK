#-------------------------------------------------
#
# Project created by QtCreator 2011-10-26T21:48:08
#
#-------------------------------------------------

QT       += core gui
QT		 += opengl

TARGET = Morph
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ogrecanvas.cpp \
    MEvent.cpp \
    MButtonWidget.cpp

HEADERS += mainwindow.h \
        splashscreen.h \
    ogrecanvas.h \
    MWidget.h \
    MEvent.h \
    MButtonWidget.h \
    MWidgetDataBase.h

FORMS    += mainwindow.ui

#unix {
    # You may need to change this include directory
    INCLUDEPATH += /usr/include/OGRE
    CONFIG += link_pkgconfig
    PKGCONFIG += OGRE


    INCLUDEPATH += /usr/include/sigc++-2.0
    CONFIG += link_pkgconfig
    PKGCONFIG += sigc++-2.0
#}

#win32 {
#    # You may need to change this include directory
#    OGREHOME = D:\ogrehead\sdk
#    LIBS += -LC:\boost\boost_1_40\lib
#    Release:LIBS += -L$$OGREHOME\lib\release
#    Debug:LIBS += -L$$OGREHOME\lib\debug
#    INCLUDEPATH += $$OGREHOME\include\OGRE
#    INCLUDEPATH += C:\boost\boost_1_40
#}

CONFIG(debug, debug|release) {
    TARGET = $$join(TARGET,,,d)
    #LIBS *= -lOgreMain_d
}
CONFIG(release, debug|release):LIBS *= -lOgreMain

RESOURCES += \
    icons.qrc
