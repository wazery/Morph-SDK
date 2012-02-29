#include "MEvent.h"

void MButtonEvents::emitObjectClickedEvent(const std::string &objectName){
    if( MButtonWidget::sWidgetsDataBase.contains(objectName) ){
        MButtonWidget::sWidgetsDataBase[objectName]->Clicked();
    }
}
