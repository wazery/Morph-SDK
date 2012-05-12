#ifndef MVSLIDERWIDGERT_H
#define MVSLIDERWIDGERT_H
#include <QObject>
#include <string>
#include <QMap>
#include "MButtonCanvasObject.h"
#include "MButtonEventEmitter.h"

class MVSliderWidget : public QObject
{
    Q_OBJECT
public:
    explicit MVSliderWidget(QObject *parent = 0);
    MVSliderWidget(const MButtonCanvasObject *canvasObject, QObject *parent = 0);
    ~MVSliderWidget();
protected:
    const MButtonCanvasObject                  *mCanvasObject;
    static QMap<std::string, MVSliderWidget*>    smWidgetsDataBase;
    friend class MButtonEventEmitter;
private:
    void Clicked();
    void Enter();
    void Leave();
    void Grabbed();
signals:
    void clicked();
    void enter();
    void leave();
    void grabbed();

public slots:
    void printClicked();
    void printEnter();
    void printLeave();
    void printGrabbed();
};

#endif // MVSLIDERWIDGERT_H
