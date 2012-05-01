#ifndef MATTROBJECT_H
#define MATTROBJECT_H

#include "MType.h"
#include "mattribute.h"

using namespace std;

namespace Morph
{
    class MAttrObject
    {
    public:
        MAttrObject();
        ~MAttrObject();

        bool isAttrExist(MString name) const
        {
            if (mAttributeList.find(name) == mAttributeList.end())
                return false;
            else
                return true;
        }

        bool addAttribute(const MString &attrName, const MAttribute &attr);

        virtual bool setAttribute(const MString &name, const MAttribute &attr, bool modify = true);

        virtual bool setAttribute(const MString &attrName, const boost::any &anyValue, bool modify = true);

        virtual bool setAttributeByString(const MString &attrName, const MString &valueString, bool modify = true);

        const MAttribute* getAttribute(const MString &name);

        const MAttribute* getFirstAttr();

        bool hasMoreAttr() const;

        const MAttribute* getNextAttr();

        unsigned int getAttributeCount() const { return mAttributeList.size(); }

    protected:
        virtual void _modify(const MAttribute &attr) {}
        //FIXME:
        //virtual void _notifyAttributeChanged(const MString &attrName);

    private:
        MAttributeList mAttributeList;
        MAttributeList::Iterator mAttributeListIterator;
    };
}
#endif // MATTROBJECT_H
