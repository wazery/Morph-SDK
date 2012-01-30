#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPixmap img("Splash22.jpg");

	//@ToDo: Implementing the splash screen with QML.
    QSplashScreen splash(img);
    splash.show();
	splash.showMessage("Application is now loading", Qt::AlignBottom, Qt::white);
	sleep(5);
	splash.showMessage("Starting...", Qt::AlignBottom, Qt::white);
	sleep(1);

	MainWindow w;

	splash.finish(&w);
	w.show();
    //OgreWidget* ogreWidget = new OgreWidget(&w); // the ogre canvas

    return a.exec();
}
