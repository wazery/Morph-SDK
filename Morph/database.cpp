#include "database.h"
#include "button.h"

using namespace std;

void DataBase::Insert(Button& inButton){
	mDB.push_back(inButton);
}

 int  DataBase::Found(std::string inName){
	 int i = 0;

     for(vector<Button>::iterator it = mDB.begin(); it != mDB.end(); it++, i++  ){
		 if(it->mCO.getName() == inName )
			 return i;
     }
	return -1;
}
