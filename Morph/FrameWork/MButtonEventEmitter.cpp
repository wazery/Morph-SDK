#include "MButtonEventEmitter.h"
#include "MButtonWidget.h"
#include "MCheckButtonWidget.h"
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
    if(MButtonWidget::smWidgetsDataBase.contains(entityName)){
    MButtonWidget::smWidgetsDataBase[entityName]->Clicked();
    }

    if(MCheckButtonWidget::smWidgetsDataBase.contains(entityName)){
    MCheckButtonWidget::smWidgetsDataBase[entityName]->Clicked();
    }
}

void MButtonEventEmitter::emitEnter(const std::string &entityName){
    if(MButtonWidget::smWidgetsDataBase.contains(entityName)){
    MButtonWidget::smWidgetsDataBase[entityName]->Enter();
    }

    if(MCheckButtonWidget::smWidgetsDataBase.contains(entityName)){
    MCheckButtonWidget::smWidgetsDataBase[entityName]->Enter();
    }
}

void MButtonEventEmitter::emitLeave(const std::string &entityName){
    if(MButtonWidget::smWidgetsDataBase.contains(entityName)){
    MButtonWidget::smWidgetsDataBase[entityName]->Leave();
    }

    if(MCheckButtonWidget::smWidgetsDataBase.contains(entityName)){
    MCheckButtonWidget::smWidgetsDataBase[entityName]->Leave();
    }
}

MButtonEventEmitter::~MButtonEventEmitter(){

}

MButtonEventEmitter::MButtonEventEmitter(MButtonEventEmitter const&){

}

MButtonEventEmitter& MButtonEventEmitter::operator=(MButtonEventEmitter const&){

}
