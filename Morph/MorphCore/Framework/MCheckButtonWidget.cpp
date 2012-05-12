#include "MCheckButtonWidget.h"
#include <string>
#include <iostream>

QMap<std::string, MCheckButtonWidget*> MCheckButtonWidget::smWidgetsDataBase;

MCheckButtonWidget::MCheckButtonWidget(QObject *parent) :
    QObject(parent){

}

MCheckButtonWidget::MCheckButtonWidget(const MButtonCanvasObject *canvasObject, QObject *parent) :
    QObject(parent), mCanvasObject(canvasObject), mActive(false){
    smWidgetsDataBase.insert(mCanvasObject->name(), this);
    std::cout << "Button init" << std::endl;
}

MCheckButtonWidget::~MCheckButtonWidget(){
    smWidgetsDataBase.remove( mCanvasObject->name() );
}

void MCheckButtonWidget::setActive(bool isActive){
    mActive = isActive;
}

bool MCheckButtonWidget::getActive() const{
    return mActive;
}


void MCheckButtonWidget::Clicked(){
    emit clicked();
    setActive(!getActive());
    emit toggled(getActive());
}


void MCheckButtonWidget::Enter(){
    emit enter();
}

void MCheckButtonWidget::Leave(){
    emit leave();
}


void MCheckButtonWidget::printClicked(){
    std::cout << "------------object clicked-------------" << std::endl;
}

void MCheckButtonWidget::printEnter(){
    std::cout << "------------object Entered-------------" << std::endl;
}

void MCheckButtonWidget::printLeave(){
    std::cout << "------------object Leaved-------------" << std::endl;
}

void MCheckButtonWidget::printToggled(bool isActive){
    std::cout << "Object State is " << (isActive? "activated": "notActivated") << std::endl;
}
