#ifndef BUTTON_H
#define BUTTON_H
#include <sigc++/sigc++.h>
#include <OGRE/OgreEntity.h>
#include <string>
#include <vector>
#include "mdatabase.h"
#include "MEvent.h"



class Button
{
public:
	class CanvasObject{
	public:
        CanvasObject(const Ogre::Entity& inEntity);
        const std::string& getName() const;
	protected:
		std::string mName;
	};

    Button(const CanvasObject& inCO);
    ~Button();
    const CanvasObject& getCanvasObject() const;
    sigc::signal<void>& Clicked();
protected:
    CanvasObject mCO;
    sigc::signal<void> mClicked;
    static MDataBase<Button> mDB;
    friend void button_object_clicked(std::string inObjName);
};

#endif // BUTTON_H
