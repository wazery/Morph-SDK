#ifndef MAPPLICATION_H
#define MAPPLICATION_H

#include "BaseApplication.h"

#include <CEGUI/CEGUISystem.h>
#include <CEGUI/CEGUISchemeManager.h>
#include <CEGUI/RendererModules/Ogre/CEGUIOgreRenderer.h>
#include <MButtonWidget.h>
#include <MCheckButtonWidget.h>
#include <MVSliderWidget.h>

class MApplication : public BaseApplication
{
public:
    MApplication(const std::string& SceneFilePath);
    virtual ~MApplication(void);

    static MButtonWidget* getMButtonWidget(const std::string& widgetName);
    static MCheckButtonWidget* getMCheckButtonWidget(const std::string& widgetName);
    static MVSliderWidget* getMVSliderWidget(const std::string& widgetName);

protected:
    virtual void createScene(void);

    virtual void chooseSceneManager(void);
    virtual void createFrameListener(void);

    virtual bool frameRenderingQueued(const Ogre::FrameEvent& arg);

    virtual bool mouseMoved(const OIS::MouseEvent& arg);
    virtual bool mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id);
    virtual bool mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id);
    virtual bool keyPressed(const OIS::KeyEvent& arg);

    Ogre::SceneNode *mCurrentObject;	//pointer to our currently selected object
    Ogre::RaySceneQuery* mRayScnQuery;	//pointer to our ray scene query
    CEGUI::Renderer* mGUIRenderer;		//our CEGUI renderer

    bool bLMouseDown, bRMouseDown;	//true if mouse buttons are held down
    int mCount;						//number of objects created
    float mRotateSpeed;				//the rotation speed for the camera
    bool mMouseOver;
    bool mObjectGrabbed;
    Ogre::SceneNode *mGrabbedObject;
    bool bRobotMode;				//if true we place robots in the world

    CEGUI::OgreRenderer* mRenderer;
};

#endif // INTERMEDIATETUTORIAL3_H
