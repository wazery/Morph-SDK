#ifndef MWIDGETDATABASE_H
#define MWIDGETDATABASE_H
#include <string>
#include <vector>

template<typename WIDGET>
class MWidgetDataBase
{
public:
    MWidgetDataBase();
    void addWidget(WIDGET& inWidget);
    WIDGET& widgetAt(int i) const;
    int findWidgetIndex(const std::string& inName);
    void removeWidgetByName(const std::string& inName);
protected:
    std::vector<WIDGET*> mWidgetDB;
};


template<typename WIDGET>
MWidgetDataBase<WIDGET>::MWidgetDataBase()
{
}

template<typename WIDGET>
void MWidgetDataBase<WIDGET>::addWidget(WIDGET& inWidget){
    mWidgetDB.push_back(&inWidget);
}

template<typename WIDGET>
WIDGET& MWidgetDataBase<WIDGET>::widgetAt(int i) const{
    return *(mWidgetDB.at(i));
}

template<typename WIDGET>
int MWidgetDataBase<WIDGET>::findWidgetIndex(const std::string& inName){
    int i = 0;
    for(typename std::vector<WIDGET*>::const_iterator it = mWidgetDB.begin(); it != mWidgetDB.end();++it, i++  ){
             if( ( (*it)->canvasObjectName() ) == inName )
                 return i;

         }

        return -1;
}

template<typename WIDGET>
void MWidgetDataBase<WIDGET>::removeWidgetByName(const std::string& inName){
    int ind = findWidgetIndex(inName);
    mWidgetDB.erase( mWidgetDB.begin() + ind);
}


#endif // MDATABASE_H
