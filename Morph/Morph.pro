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
<<<<<<< HEAD
<<<<<<< HEAD
    ogrecanvas.cpp \
    MButtonWidget.cpp \
    to-do.cpp \
    MButtonEventEmitter.cpp \
    MButtonCanvasObject.cpp

HEADERS += mainwindow.h \
        splashscreen.h \
    ogrecanvas.h \
    MButtonWidget.h \
    MButtonEventEmitter.h \
    MButtonCanvasObject.h
=======
    button.cpp \
    MEvent.cpp \
=======
>>>>>>> 8ee92ded2f5b2c4d72e2464b3af91d236b0bc48d
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
    mOgreEntityViewer/envproperties.cpp \
    mOgreEntityViewer/settingsdialog.cpp \
    mOgreEntityViewer/lightwindow.cpp \
    MorphCore/Editor/mcommandmanager.cpp \
    MorphCore/Editor/micommand.cpp \
    mOgreEntityViewer/nodeview.cpp \
    MorphCore/Editor/mrootnode.cpp \
    mOgreEntityViewer/aboutdialog.cpp \
    mOgreEntityViewer/viewgrid.cpp \
    mOgreEntityViewer/removeobject.cpp \
    #mOgreEntityViewer/textrenderer.cpp
    MorphCore/Editor/mogrecanvas.cpp \
    MorphCore/Editor/loadingbar.cpp \
    mOgreEntityViewer/objproperties.cpp \
    mOgreEntityViewer/startingwindow.cpp \
    mOgreEntityViewer/matwindow.cpp

HEADERS += mainwindow.h \
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
<<<<<<< HEAD
    MorphCore/Editor/MNodeManager.h
>>>>>>> 4f3226e29c7690b0d08e1f81b3023f10ef0beee7
=======
    MorphCore/Editor/MNodeManager.h \
    MorphCore/Editor/mattrobject.h \
    mOgreEntityViewer/objpropertiesview.h \
    mOgreEntityViewer/envproperties.h \
    mOgreEntityViewer/settingsdialog.h \
    mOgreEntityViewer/lightwindow.h \
    MorphCore/Editor/mcommandmanager.h \
    MorphCore/Editor/micommand.h \
    mOgreEntityViewer/nodeview.h \
    MorphCore/Editor/mrootnode.h \
    mOgreEntityViewer/aboutdialog.h \
    mOgreEntityViewer/viewgrid.h \
    mOgreEntityViewer/removeobject.h \
    #mOgreEntityViewer/textrenderer.h
    MorphCore/Editor/mogrecanvas.h \
    MorphCore/Editor/loadingbar.h \
    mOgreEntityViewer/objproperties.h \
    mOgreEntityViewer/startingwindow.h \
    mOgreEntityViewer/matwindow.h
>>>>>>> 8ee92ded2f5b2c4d72e2464b3af91d236b0bc48d

FORMS    += mainwindow.ui \
    mOgreEntityViewer/settingsdialog.ui \
    mOgreEntityViewer/aboutdialog.ui \
    mOgreEntityViewer/removeobject.ui \
    mOgreEntityViewer/startingwindow.ui

#unix
#{
    # You may need to change this include directory
    INCLUDEPATH += /usr/include/OGRE
    CONFIG += link_pkgconfig
    PKGCONFIG += OGRE
<<<<<<< HEAD
=======

#    INCLUDEPATH += /usr/include/sigc++-2.0
    CONFIG += link_pkgconfig
#    PKGCONFIG += sigc++-2.0
>>>>>>> 8ee92ded2f5b2c4d72e2464b3af91d236b0bc48d
#}

#win32
#{
#    # You may need to change this include directory
#    OGREHOME = D:\ogrehead\sdk
#    LIBS += -LC:\boost\boost_1_40\lib
#    Release:LIBS += -L$$OGREHOME\lib\release
#    Debug:LIBS += -L$$OGREHOME\lib\debug
#    INCLUDEPATH += $$OGREHOME\include\OGRE
#    INCLUDEPATH += C:\boost\boost_1_40
#}

CONFIG(debug, debug|release)
{
    TARGET = $$join(TARGET,,,)
    #LIBS *= -lOgreMain_d
}

CONFIG(release, debug|release):LIBS *= -lOgreMain

RESOURCES += \
    icons.qrc
