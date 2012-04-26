#ifndef MCHECKBUTTONWIDGET_H
#define MCHECKBUTTONWIDGET_H
#include <QObject>
#include <string>
#include <QMap>
#include "MButtonCanvasObject.h"
#include "MButtonEventEmitter.h"

class MCheckButtonWidget : public QObject
{
    Q_OBJECT
public:
    explicit MCheckButtonWidget(QObject *parent = 0);
    MCheckButtonWidget(const MButtonCanvasObject *canvasObject, QObject *parent = 0);
    ~MCheckButtonWidget();
    void setActive(bool isActive = true);
    bool getActive() const;
protected:
    const MButtonCanvasObject                  *mCanvasObject;
    static QMap<std::string, MCheckButtonWidget*>    smWidgetsDataBase;
    friend class MButtonEventEmitter;
    bool mActive;
private:
    void Clicked();
    void Enter();
    void Leave();
signals:
    void clicked();
    void toggled(bool isActive);
    void enter();
    void leave();

public slots:
    void printClicked();
    void printToggled(bool isActive);
    void printEnter();
    void printLeave();
};

#endif // MCHECKBUTTONWIDGET_H
