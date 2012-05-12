#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QSplashScreen>
#include <iostream>

void myMessageOutput(QtMsgType type, const char *msg)
{
    //in this function, you can write the message to any stream!
    switch (type)
    {
    case QtDebugMsg:
        fprintf(stderr, "Debug: %s\n", msg);
        break;
    case QtWarningMsg:
        fprintf(stderr, "Warning: %s\n", msg);
        break;
    case QtCriticalMsg:
        fprintf(stderr, "Critical: %s\n", msg);
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal: %s\n", msg);
       abort();
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("Morph");
    QCoreApplication::setOrganizationDomain("https://github.com/Zeology/Morph-SDK");
    QCoreApplication::setApplicationName("Morph SDK");

    qInstallMsgHandler(myMessageOutput); //install : set the callback

    QApplication a(argc, argv);

    //QPixmap img("Splash22.jpg");

//    QSplashScreen splash(img);
//    splash.show();
//    splash.showMessage("Initialising Engine..", Qt::AlignBottom, Qt::white);
//    sleep(5);
//    splash.showMessage("Starting...", Qt::AlignBottom, Qt::white);
//    sleep(1);

	MainWindow w;

    //splash.finish(&w);
	w.show();

    return a.exec();
}
