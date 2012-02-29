#include "MButtonWidget.h"
#include <string>
#include <iostream>

QMap<std::string, MButtonWidget*> MButtonWidget::sWidgetsDataBase;

MButtonWidget::MButtonWidget(QObject *parent) :
    QObject(parent){

}

MButtonWidget::MCanvasObject::MCanvasObject(const Ogre::Entity &entity){
    mName = entity.getName();
}

const std::string& MButtonWidget::MCanvasObject::name() const{
    return mName;
}

MButtonWidget::MButtonWidget(const MCanvasObject *canvasObject, QObject *parent) :
    QObject(parent), mCanvasObject(canvasObject){
    sWidgetsDataBase.insert(mCanvasObject->name(), this);
}

MButtonWidget::~MButtonWidget(){
    sWidgetsDataBase.remove( mCanvasObject->name() );
}


void MButtonWidget::Clicked(){
     emit clicked();
}

void MButtonWidget::print(){
    std::cout << "------------object clicked-------------" << std::endl;
}

