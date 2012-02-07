#ifndef BUTTON_H
#define BUTTON_H
#include <sigc++/sigc++.h>
#include "database.h"
#include <OGRE/OgreEntity.h>
#include <string>
#include <vector>


void object_clicked(std::string inObjName);

class Button
{
public:
	class CanvasObject{
	public:
		CanvasObject(const Ogre::Entity& inEntity){
			mName = inEntity.getName();
		}
		std::string getName(){
			return mName;
		}
	protected:
		std::string mName;
	};
	friend void object_clicked(std::string inObjName);

    Button(CanvasObject& inCO) : mCO(inCO){
		mDB.Insert(*this);
	}
	CanvasObject mCO;
	sigc::signal<void> mClicked;
	static DataBase mDB;
};



#endif // BUTTON_H
