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
signals:
    void clicked();

public slots:
    void print();
};

#endif // BUTTON_H
