#include "MButtonEventEmitter.h"
#include "MButtonWidget.h"
#include <cstddef>
#include <cassert>

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
    assert(MButtonWidget::smWidgetsDataBase.contains(entityName));
    MButtonWidget::smWidgetsDataBase[entityName]->Clicked();
}


MButtonEventEmitter::~MButtonEventEmitter(){

}

MButtonEventEmitter::MButtonEventEmitter(MButtonEventEmitter const&){

}

MButtonEventEmitter& MButtonEventEmitter::operator=(MButtonEventEmitter const&){

}
