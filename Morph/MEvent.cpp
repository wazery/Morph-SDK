#include "MWidget.h"

void button_object_clicked(std::string inObjName){
    int test = Button::mDB.findWidget(inObjName);
    if( test != -1){
        Button::mDB.getWidgetAt(test).mClicked();
    }

}

