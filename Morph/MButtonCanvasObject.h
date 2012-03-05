#ifndef MBUTTONCANVASOBJECT_H
#define MBUTTONCANVASOBJECT_H
#include <OGRE/OgreEntity.h>
#include <string>

class MButtonCanvasObject
{
public:
    MButtonCanvasObject(const Ogre::Entity &entity);
protected:
    const std::string& name() const;
private:
    std::string         mName;
    friend class        MButtonWidget;
};

#endif // MBUTTONCANVASOBJECT_H
