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
    std::cout << "Button init" << std::endl;
}

MButtonWidget::~MButtonWidget(){
    smWidgetsDataBase.remove( mCanvasObject->name() );
}


void MButtonWidget::Clicked(){
     emit clicked();
}

void MButtonWidget::Pressed(){
     emit pressed();
}

void MButtonWidget::Released(){
     emit released();
}

void MButtonWidget::Enter(){
     emit enter();
}

void MButtonWidget::Leave(){
    emit leave();
}

void MButtonWidget::printClicked(){
    std::cout << "------------object clicked-------------" << std::endl;
}

void MButtonWidget::printEnter(){
    std::cout << "------------object Entered-------------" << std::endl;
}

void MButtonWidget::printLeave(){
    std::cout << "------------object Leaved-------------" << std::endl;
}

