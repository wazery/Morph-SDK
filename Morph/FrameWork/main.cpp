#include <iostream>
#include "MCheckButtonWidget.h".h"
#include "MApplication.h"


using namespace std;

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        MApplication app;

        MButtonCanvasObject coObject("Unnamed_3");
        MCheckButtonWidget btn(&coObject);
        QObject::connect(&btn, SIGNAL(clicked()), &btn, SLOT(printClicked()));
        QObject::connect(&btn, SIGNAL(enter()), &btn, SLOT(printEnter()));
        QObject::connect(&btn, SIGNAL(leave()), &btn, SLOT(printLeave()));
        QObject::connect(&btn, SIGNAL(toggled(bool)), &btn, SLOT(printToggled(bool)));


        try {
            app.exec();
        } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif

