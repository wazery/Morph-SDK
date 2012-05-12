#include "MVSliderWidget.h"
#include <string>
#include <iostream>

QMap<std::string, MVSliderWidget*> MVSliderWidget::smWidgetsDataBase;

MVSliderWidget::MVSliderWidget(QObject *parent) :
    QObject(parent){

}

MVSliderWidget::MVSliderWidget(const MButtonCanvasObject *canvasObject, QObject *parent) :
    QObject(parent), mCanvasObject(canvasObject){
    smWidgetsDataBase.insert(mCanvasObject->name(), this);
}

MVSliderWidget::~MVSliderWidget(){
    smWidgetsDataBase.remove( mCanvasObject->name() );
}


void MVSliderWidget::Clicked(){
     emit clicked();
}

void MVSliderWidget::Enter(){
     emit enter();
}

void MVSliderWidget::Leave(){
    emit leave();
}

void MVSliderWidget::Grabbed(){
    emit grabbed();
}

void MVSliderWidget::printClicked(){
    std::cout << "------------object clicked-------------" << std::endl;
}

void MVSliderWidget::printEnter(){
    std::cout << "------------object Entered-------------" << std::endl;
}

void MVSliderWidget::printLeave(){
    std::cout << "------------object Leaved-------------" << std::endl;
}

void MVSliderWidget::printGrabbed(){
    std::cout << "------------object Grabbed-------------" << std::endl;
}
