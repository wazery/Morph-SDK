#ifndef MBUTTONWIDGET_H
#define MBUTTONWIDGET_H
#include <QObject>
#include <OGRE/OgreEntity.h>
#include <string>
#include <vector>
#include <QMap>
#include "MEvent.h"

class MButtonWidget : public QObject
{
    Q_OBJECT
public:
    explicit MButtonWidget(QObject *parent = 0);
    class MCanvasObject
    {
	public:
        MCanvasObject(const Ogre::Entity &entity);
	protected:
        const std::string& name() const;
    private:
        std::string         mName;
        friend class        MButtonWidget;
	};

    MButtonWidget(const MCanvasObject *canvasObject, QObject *parent = 0);
    ~MButtonWidget();
    void Clicked();
protected:
    const MCanvasObject                     *mCanvasObject;
    static QMap<std::string, MButtonWidget*> sWidgetsDataBase;
    friend class MButtonEvents;

signals:
    void clicked();

public slots:
    void print();
};

#endif // BUTTON_H
