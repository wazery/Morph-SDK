#include "MEvent.h"

void MButtonEvents::emitObjectClickedEvent(std::string &objectName){
    if( MButtonWidget::mWidgetsDataBase.contains(objectName) ){
        MButtonWidget::mWidgetsDataBase[objectName]->mClicked();
    }
}
