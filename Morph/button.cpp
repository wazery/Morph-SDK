#include "button.h"
#include <string>
#include <iostream>

MDataBase<Button> Button::mDB;

Button::CanvasObject::CanvasObject(const Ogre::Entity& inEntity){
    mName = inEntity.getName();
}

const std::string& Button::CanvasObject::getName() const{
    return mName;
}

Button::Button(const CanvasObject& inCO) : mCO(inCO){
    mDB.addWidget(*this);
}

Button::~Button(){
    mDB.removeWidget(mCO.getName());
}

const Button::CanvasObject& Button::getCanvasObject() const{
    return mCO;
}

sigc::signal<void>& Button::Clicked(){
    return mClicked;
}

