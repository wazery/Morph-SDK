#include "MButtonCanvasObject.h"


MButtonCanvasObject::MButtonCanvasObject(const Ogre::Entity &entity){
    mName = entity.getName();
}

const std::string& MButtonCanvasObject::name() const{
    return mName;
}


