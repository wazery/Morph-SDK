#include "button.h"
#include <string>

DataBase Button::mDB;

void object_clicked(std::string inObjName)
{

    int test = Button::mDB.Found(inObjName);
    if( test != -1)
	{
        Button::mDB.mDB.at(test).mClicked();
	}

}
