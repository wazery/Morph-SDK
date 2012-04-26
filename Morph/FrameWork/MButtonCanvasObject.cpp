#include "MButtonCanvasObject.h"


MButtonCanvasObject::MButtonCanvasObject(const std::string &entityName){
    mName = entityName;
}

const std::string& MButtonCanvasObject::name() const{
    return mName;
}


