#include "MEvent.h"

void ButtonEventEmitter::objectClicked(std::string inObjName){
    if( MButtonWidget::mWidgetsDataBase.contains(inObjName) ){
        MButtonWidget::mWidgetsDataBase[inObjName]->mClicked();
    }
//    int test = MButtonWidget::mWidgetsDataBase.findWidgetIndex(inObjName);
//    if( test != -1){
//        MButtonWidget::mWidgetsDataBase.widgetAt(test).mClicked();
//    }

}

