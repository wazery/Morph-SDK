#include "MButtonWidget.h"
#include <string>
#include <iostream>

QMap<std::string, MButtonWidget*> MButtonWidget::smWidgetsDataBase;

MButtonWidget::MButtonWidget(QObject *parent) :
    QObject(parent){

}

MButtonWidget::MButtonWidget(const MButtonCanvasObject *canvasObject, QObject *parent) :
    QObject(parent), mCanvasObject(canvasObject){
    smWidgetsDataBase.insert(mCanvasObject->name(), this);
}

MButtonWidget::~MButtonWidget(){
    smWidgetsDataBase.remove( mCanvasObject->name() );
}


void MButtonWidget::Clicked(){
     emit clicked();
}

void MButtonWidget::print(){
    std::cout << "------------object clicked-------------" << std::endl;
}

