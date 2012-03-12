#include "MButtonEventEmitter.h"
#include "MButtonWidget.h"
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
    Q_ASSERT(MButtonWidget::smWidgetsDataBase.contains(entityName));
    MButtonWidget::smWidgetsDataBase[entityName]->Clicked();
}

void MButtonEventEmitter::emitPressed(const std::string &entityName){
    Q_ASSERT(MButtonWidget::smWidgetsDataBase.contains(entityName));
    MButtonWidget::smWidgetsDataBase[entityName]->Pressed();
}

void MButtonEventEmitter::emitReleased(const std::string &entityName){
    Q_ASSERT(MButtonWidget::smWidgetsDataBase.contains(entityName));
    MButtonWidget::smWidgetsDataBase[entityName]->Released();
}

void MButtonEventEmitter::emitEnter(const std::string &entityName){
    Q_ASSERT(MButtonWidget::smWidgetsDataBase.contains(entityName));
    MButtonWidget::smWidgetsDataBase[entityName]->Enter();
}

void MButtonEventEmitter::emitLeave(const std::string &entityName){
    Q_ASSERT(MButtonWidget::smWidgetsDataBase.contains(entityName));
    MButtonWidget::smWidgetsDataBase[entityName]->Leave();
}

MButtonEventEmitter::~MButtonEventEmitter(){

}

MButtonEventEmitter::MButtonEventEmitter(MButtonEventEmitter const&){

}

MButtonEventEmitter& MButtonEventEmitter::operator=(MButtonEventEmitter const&){

}
