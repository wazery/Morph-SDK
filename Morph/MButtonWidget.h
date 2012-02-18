#ifndef MBUTTONWIDGET_H
#define MBUTTONWIDGET_H
#include <sigc++/sigc++.h>
#include <OGRE/OgreEntity.h>
#include <string>
#include <vector>
#include <QMap>
//#include "MWidgetDataBase.h"
#include "MEvent.h"

class MButtonWidget
{
public:
	class CanvasObject{
	public:
        CanvasObject(const Ogre::Entity& inEntity);
	protected:
        const std::string& name() const;
    private:
		std::string mName;
        friend class MButtonWidget;
	};

    MButtonWidget(const CanvasObject& inCO);
    ~MButtonWidget();
    //const std::string& canvasObjectName() const;
    sigc::signal<void>& Clicked();
protected:
    CanvasObject mCanvasObject;
    static QMap<std::string, MButtonWidget*> mWidgetsDataBase;
    sigc::signal<void> mClicked;
    friend class ButtonEventEmitter;
};

#endif // BUTTON_H
