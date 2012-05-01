#pragma once

#include <wchar.h>
#include <map>
#include <string>
#include <fstream>
#include <QVector>

#include <QString>
#include <QStringList>

using namespace std;

//FIXME: used to export to dll libs
//#define MORPH_API

typedef unsigned int UINT;

namespace Morph
{
    typedef QStringList MStringList;
    typedef QString MString;

    enum eSelectMode
    {
        M_SELECT_REPLACE,
        M_SELECT_ADD,
        M_SELECT_SUBTRACT,
        M_SELECT_CLEAR
    };
}

//#ifndef DEFAULT_MAX_UNDO_ITEM_NUM
//#define DEFAULT_MAX_UNDO_ITEM_NUM 1000
