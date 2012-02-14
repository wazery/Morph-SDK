#include "MEvent.h"

void ButtonEventEmitter::objectClicked(std::string inObjName){
    int test = MButtonWidget::mWidgetsDataBase.findWidgetIndex(inObjName);
    if( test != -1){
        MButtonWidget::mWidgetsDataBase.widgetAt(test).mClicked();
    }

}

