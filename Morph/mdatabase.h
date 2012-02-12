#ifndef MDATABASE_H
#define MDATABASE_H
#include <string>
#include <vector>

template<typename WIDGET>
class MDataBase
{
public:
    MDataBase();
    void addWidget(WIDGET& inWidget);
    WIDGET& getWidgetAt(int i) const;
    int findWidget(const std::string& inName);
    void removeWidget(const std::string& inName);
protected:
    std::vector<WIDGET*> mWidgetDB;
};


template<typename WIDGET>
MDataBase<WIDGET>::MDataBase()
{
}

template<typename WIDGET>
void MDataBase<WIDGET>::addWidget(WIDGET& inWidget){
    mWidgetDB.push_back(&inWidget);
}

template<typename WIDGET>
WIDGET& MDataBase<WIDGET>::getWidgetAt(int i) const{
    return *(mWidgetDB.at(i));
}

template<typename WIDGET>
int MDataBase<WIDGET>::findWidget(const std::string& inName){
    int i = 0;
    for(typename std::vector<WIDGET*>::const_iterator it = mWidgetDB.begin(); it != mWidgetDB.end();++it, i++  ){
             if( ( (*it)->getCanvasObject().getName() ) == inName )
                 return i;

         }

        return -1;
}

template<typename WIDGET>
void MDataBase<WIDGET>::removeWidget(const std::string& inName){
    int ind = findWidget(inName);
    mWidgetDB.erase( mWidgetDB.begin() + ind);
}


#endif // MDATABASE_H
