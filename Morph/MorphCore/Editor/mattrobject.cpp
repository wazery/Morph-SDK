#include "mattrobject.h"

using namespace Morph;

MAttrObject::MAttrObject()
{
}

MAttrObject::~MAttrObject()
{
    mAttributeList.clear();
}

bool MAttrObject::addAttribute(const MString &attrName, const MAttribute &attr)
{
    if (isAttrExist(attrName))
    {
        MLogManager::getSingleton().logOutput("Error: Couldn't add attribute: " + attrName + ", it actually exists!", M_ERROR, false);
        return false;
    }
    if (attr.getName() != attrName)
    {
        MLogManager::getSingleton().logOutput("Error: Couldn't add attribute: " + attrName + ", it might take a different name!", M_ERROR, false);
        return false;
    }

    mAttributeList[attrName] = attr;
    return false;
}

bool MAttrObject::setAttribute(const MString &name, const MAttribute &attr, bool modify)
{
    if (!isAttrExist(name))
    {
        MLogManager::getSingleton().logOutput("Error: Attribute: " + name + "not found!", M_ERROR, false);
        return false;
    }
    if (mAttributeList[name].getType() != attr.getType())
    {
        MLogManager::getSingleton().logOutput("Setting attribute can not be done because value type not match!", M_ERROR, false);
        return false;
    }

    mAttributeList[name] = attr;
    if (modify)
        _modify(mAttributeList[name]);

    //this->_notifyAttributeChanged(name);
    return true;
}

bool MAttrObject::setAttribute(const MString &attrName, const boost::any &anyValue, bool modify)
{
    if(!isAttrExist(attrName))
    {
        MLogManager::getSingleton().logOutput("Error: Attribute: " + attrName + "not found!", M_ERROR, false);
        return false;
    }

    if(!mAttributeList[attrName].setValue(anyValue))
        return false;

    if(modify)
        _modify(mAttributeList[attrName]);
    //_notifyAttributeChanged(attrName);
    return true;
}

bool MAttrObject::setAttributeByString(const MString &attrName, const MString &valueString, bool modify)
{
    if (!isAttrExist(attrName))
    {
        MLogManager::getSingleton().logOutput("Error: Attribute: " + attrName + "not found!", M_ERROR, false);
        return false;
    }
    if (!mAttributeList[attrName].setValueByString(valueString))
        return false;

    if(modify)
        _modify(mAttributeList[attrName]);
   // _notifyAttributeChanged(attrName);
    return true;
}

const MAttribute* MAttrObject::getAttribute(const MString &name)
{
    if(mAttributeList.find(name) != mAttributeList.end())
        return &mAttributeList[name];

    return NULL;
}

const MAttribute* MAttrObject::getFirstAttr()
{
    mAttributeListIterator = mAttributeList.begin();

    if (mAttributeListIterator == mAttributeList.end())
        return NULL;

    //return &mAttributeListIterator->second;
}

bool MAttrObject::hasMoreAttr() const
{
    if(mAttributeListIterator == mAttributeList.end())
        return false;

    return true;
}

const MAttribute* MAttrObject::getNextAttr()
{
    if(mAttributeListIterator == mAttributeList.end())
        return NULL;

    //const MAttribute* m = &mAttributeListIterator->second;
    mAttributeListIterator++;
    //return m;
}

//void _notifyAttributeChanged(const MString &attrName)
//{
//}
