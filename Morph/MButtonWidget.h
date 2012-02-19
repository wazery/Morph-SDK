#ifndef MBUTTONWIDGET_H
#define MBUTTONWIDGET_H
#include <sigc++/sigc++.h>
#include <OGRE/OgreEntity.h>
#include <string>
#include <vector>
#include <QMap>
#include "MEvent.h"

class MButtonWidget
{
public:
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

    MButtonWidget(const MCanvasObject *canvasObject);
    ~MButtonWidget();
    sigc::signal<void>& Clicked();
protected:
    const MCanvasObject                     *mCanvasObject;
    static QMap<std::string, MButtonWidget*> mWidgetsDataBase;
    sigc::signal<void>                       mClicked;
    friend class MButtonEvents;
};

#endif // BUTTON_H
