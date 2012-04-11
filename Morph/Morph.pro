#-------------------------------------------------
#
# Project created by QtCreator 2011-10-26T21:48:08
#
#-------------------------------------------------

QT       += core gui
QT       += opengl

TARGET = Morph
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    button.cpp \
    MEvent.cpp \
    MorphCore/Editor/msystemmanager.cpp \
    #MorphCore/Editor/msingleton.cpp
    MorphCore/Editor/mlogmanager.cpp \
    mOgreEntityViewer/logview.cpp \
    mOgreEntityViewer/mogrelogproxy.cpp \
    MorphCore/Editor/mnodemanager.cpp \
    MorphCore/Editor/mnode.cpp \
    MorphCore/Editor/mattribute.cpp \
    MorphCore/Editor/mattrobject.cpp \
    mOgreEntityViewer/objpropertiesview.cpp \
    settingsdialog.cpp

HEADERS += mainwindow.h \
    button.h \
    mdatabase.h \
    MWidget.h \
    MEvent.h \
    MorphCore/Editor/msystemmanager.h \
    #MorphCore/Editor/msingleton.h // FIXME: implement it.
    MorphCore/Editor/mlogmanager.h \
    mOgreEntityViewer/logview.h \
    mOgreEntityViewer/mogrelogproxy.h \
    MorphCore/Editor/mnodemanager.h \
    MorphCore/Editor/mnode.h \
    MorphCore/Editor/MNode.h \
    MorphCore/Editor/MType.h \
    MorphCore/Editor/mattribute.h \
    MorphCore/Editor/MNodeManager.h \
    MorphCore/Editor/mattrobject.h \
    mOgreEntityViewer/objpropertiesview.h \
    settingsdialog.h

FORMS    += mainwindow.ui \
    settingsdialog.ui

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
