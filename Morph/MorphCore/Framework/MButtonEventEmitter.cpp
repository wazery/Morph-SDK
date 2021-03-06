#include "MButtonEventEmitter.h"
#include "MButtonWidget.h"
#include "MCheckButtonWidget.h"
#include "MVSliderWidget.h"
#include <cstddef>
#include <QtGlobal>

MButtonEventEmitter* MButtonEventEmitter::smInstance = NULL;

MButtonEventEmitter::MButtonEventEmitter(){
}

MButtonEventEmitter& MButtonEventEmitter::getSingleton(){
    if (smInstance == NULL)
            smInstance = new MButtonEventEmitter();

        return *smInstance;
}

MButtonEventEmitter* MButtonEventEmitter::getSingletonPtr(){
    if (smInstance = NULL)
        smInstance = new MButtonEventEmitter();

    return smInstance;
}

void MButtonEventEmitter::releaseSingleton(){
    if (smInstance)
    {
        delete smInstance;
        smInstance = NULL;
    }
}

void MButtonEventEmitter::emitClicked(const std::string &entityName){
    std::cout << entityName << std::endl;
    if(MButtonWidget::smWidgetsDataBase.contains(entityName)){
    MButtonWidget::smWidgetsDataBase[entityName]->Clicked();
    }

    if(MCheckButtonWidget::smWidgetsDataBase.contains(entityName)){
    MCheckButtonWidget::smWidgetsDataBase[entityName]->Clicked();
    }

    if(MVSliderWidget::smWidgetsDataBase.contains(entityName)){
    MVSliderWidget::smWidgetsDataBase[entityName]->Clicked();
    }
}

void MButtonEventEmitter::emitEnter(const std::string &entityName){
    if(MButtonWidget::smWidgetsDataBase.contains(entityName)){
    MButtonWidget::smWidgetsDataBase[entityName]->Enter();
    }

    if(MCheckButtonWidget::smWidgetsDataBase.contains(entityName)){
    MCheckButtonWidget::smWidgetsDataBase[entityName]->Enter();
    }

    if(MVSliderWidget::smWidgetsDataBase.contains(entityName)){
    MVSliderWidget::smWidgetsDataBase[entityName]->Enter();
    }
}

void MButtonEventEmitter::emitLeave(const std::string &entityName){
    if(MButtonWidget::smWidgetsDataBase.contains(entityName)){
    MButtonWidget::smWidgetsDataBase[entityName]->Leave();
    }

    if(MCheckButtonWidget::smWidgetsDataBase.contains(entityName)){
    MCheckButtonWidget::smWidgetsDataBase[entityName]->Leave();
    }

    if(MVSliderWidget::smWidgetsDataBase.contains(entityName)){
    MVSliderWidget::smWidgetsDataBase[entityName]->Enter();
    }
}

void MButtonEventEmitter::emitGrab(const std::string &entityName){

    if(MVSliderWidget::smWidgetsDataBase.contains(entityName)){
    MVSliderWidget::smWidgetsDataBase[entityName]->Grabbed();
    }
}


MButtonEventEmitter::~MButtonEventEmitter(){

}

MButtonEventEmitter::MButtonEventEmitter(MButtonEventEmitter const&){

}

MButtonEventEmitter& MButtonEventEmitter::operator=(MButtonEventEmitter const&){

}
