#include <iostream>
#include "MApplication.h"
#include "MVSliderWidget.h"

using namespace std;

int main(int argc, char *argv[])
{
    // Create application object
    MApplication app("/meshes/MyScene.scene");

    MVSliderWidget* btn = MApplication::getMVSliderWidget("OgreHead");


    //        MButtonCanvasObject coObject("Unnamed_3");
    //        MCheckButtonWidget btn(&coObject);
//            QObject::connect(btn, SIGNAL(clicked()), btn, SLOT(printClicked()));
//            QObject::connect(btn, SIGNAL(enter()), btn, SLOT(printEnter()));
//            QObject::connect(btn, SIGNAL(leave()), btn, SLOT(printLeave()));
//            QObject::connect(&btn, SIGNAL(toggled(bool)), &btn, SLOT(printToggled(bool)));
   // QObject::connect(btn, SIGNAL(grabbed()), btn, SLOT(printGrabbed()));

    try {
        app.exec();
    }catch (Ogre::Exception& e){

        std::cerr << "An exception has occured: " <<
                     e.getFullDescription().c_str() << std::endl;
    }

    return 0;
}



