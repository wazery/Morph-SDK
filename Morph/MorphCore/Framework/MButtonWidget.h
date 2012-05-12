#ifndef MBUTTONWIDGET_H
#define MBUTTONWIDGET_H
#include <QObject>
#include <string>
#include <QMap>
#include "MButtonCanvasObject.h"
#include "MButtonEventEmitter.h"

class MButtonWidget : public QObject
{
    Q_OBJECT
public:
    explicit MButtonWidget(QObject *parent = 0);
    MButtonWidget(const MButtonCanvasObject *canvasObject, QObject *parent = 0);
    ~MButtonWidget();
protected:
    const MButtonCanvasObject                  *mCanvasObject;
    static QMap<std::string, MButtonWidget*>    smWidgetsDataBase;
    friend class MButtonEventEmitter;
private:
    void Clicked();
    void Pressed();
    void Released();
    void Enter();
    void Leave();
signals:
    void clicked();
    void pressed();
    void released();
    void enter();
    void leave();

public slots:
    void printClicked();
    void printEnter();
    void printLeave();
};

#endif // BUTTON_H
