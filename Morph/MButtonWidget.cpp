#include "MButtonWidget.h"
#include <string>
#include <iostream>

MWidgetDataBase<MButtonWidget> MButtonWidget::mWidgetsDataBase;

MButtonWidget::CanvasObject::CanvasObject(const Ogre::Entity& inEntity){
    mName = inEntity.getName();
}

const std::string& MButtonWidget::CanvasObject::name() const{
    return mName;
}

MButtonWidget::MButtonWidget(const CanvasObject& inCO) : mCanvasObject(inCO){
    mWidgetsDataBase.addWidget(*this);
}

MButtonWidget::~MButtonWidget(){
    mWidgetsDataBase.removeWidgetByName(mCanvasObject.name());
}

const std::string& MButtonWidget::canvasObjectName() const{
    return mCanvasObject.name();
}

sigc::signal<void>& MButtonWidget::Clicked(){
    return mClicked;
}

