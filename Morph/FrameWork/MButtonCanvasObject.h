#ifndef MBUTTONCANVASOBJECT_H
#define MBUTTONCANVASOBJECT_H
#include <OGRE/OgreEntity.h>
#include <string>

class MButtonCanvasObject
{
public:
    MButtonCanvasObject(const std::string &entityName);
protected:
    const std::string& name() const;
private:
    std::string         mName;
    friend class        MButtonWidget;
    friend class        MCheckButtonWidget;
};

#endif // MBUTTONCANVASOBJECT_H
