#include "MButtonWidget.h"
#include <string>
#include <iostream>

QMap<std::string, MButtonWidget*> MButtonWidget::mWidgetsDataBase;

MButtonWidget::MCanvasObject::MCanvasObject(const Ogre::Entity& entity){
    mName = entity.getName();
}

const std::string& MButtonWidget::MCanvasObject::name() const{
    return mName;
}

MButtonWidget::MButtonWidget(const MCanvasObject* canvasObject) : mCanvasObject(canvasObject){
    mWidgetsDataBase.insert(mCanvasObject->name(), this);
}

MButtonWidget::~MButtonWidget(){
    mWidgetsDataBase.remove( mCanvasObject->name() );
}


sigc::signal<void>& MButtonWidget::Clicked(){
    return mClicked;
}

