#include "MApplication.h"
#include "MButtonEventEmitter.h"

using namespace Ogre;
//-------------------------------------------------------------------------------------
MApplication::MApplication(const std::string& SceneFilePath):
    BaseApplication(SceneFilePath),
    mCount(0),
    mCurrentObject(0),
    mGrabbedObject(0),
    bLMouseDown(false),
    bRMouseDown(false),
    mRotateSpeed(0.1f),
    bRobotMode(true),
    mMouseOver(false),
    mObjectGrabbed(false)
{
}
//-------------------------------------------------------------------------------------
MApplication::~MApplication(void)
{
    mSceneMgr->destroyQuery(mRayScnQuery);
}

MButtonWidget* MApplication::getMButtonWidget(const std::string &widgetName){
    MButtonCanvasObject* canvasObject = new MButtonCanvasObject(widgetName);
    MButtonWidget* widgetPtr = new MButtonWidget(canvasObject);
    return widgetPtr;
}

MCheckButtonWidget* MApplication::getMCheckButtonWidget(const std::string &widgetName){
    MButtonCanvasObject* canvasObject = new MButtonCanvasObject(widgetName);
    MCheckButtonWidget* widgetPtr = new MCheckButtonWidget(canvasObject);
    return widgetPtr;
}

MVSliderWidget* MApplication::getMVSliderWidget(const std::string &widgetName){
    MButtonCanvasObject* canvasObject = new MButtonCanvasObject(widgetName);
    MVSliderWidget* widgetPtr = new MVSliderWidget(canvasObject);
    return widgetPtr;
}


//-------------------------------------------------------------------------------------
void MApplication::createScene(void)
{
    BaseApplication::createScene();
    mRenderer = &CEGUI::OgreRenderer::bootstrapSystem();

    CEGUI::SchemeManager::getSingleton().create((CEGUI::utf8*)"TaharezLook.scheme");
    CEGUI::MouseCursor::getSingleton().setImage("TaharezLook", "MouseArrow");
}

void MApplication::chooseSceneManager(void)
{
}

void MApplication::createFrameListener(void)
{
    //we still want to create the frame listener from the base app
    BaseApplication::createFrameListener();

    //but we also want to set up our raySceneQuery after everything has been initialized
    mRayScnQuery = mSceneMgr->createRayQuery(Ogre::Ray());
}

bool MApplication::frameRenderingQueued(const Ogre::FrameEvent& arg)
{
    //we want to run everything in the previous frameRenderingQueued call
    //but we also want to do something afterwards, so lets  start off with this
    if(!BaseApplication::frameRenderingQueued(arg))
    {
        return false;
    }

    /*
    This next big chunk basically sends a raycast straight down from the camera's position
    It then checks to see if it is under world geometry and if it is we move the camera back up
    */
    Ogre::Vector3 camPos = mCamera->getPosition();
    Ogre::Ray cameraRay(Ogre::Vector3(camPos.x, 5000.0f, camPos.z), Ogre::Vector3::NEGATIVE_UNIT_Y);

    mRayScnQuery->setRay(cameraRay);

    /*
    here we tell it not to sort the raycast results	world geometry would be
    at the end of the list so sorting would be bad in this case since we are iterating through everything
    */
    mRayScnQuery->setSortByDistance(false);
    Ogre::RaySceneQueryResult& result = mRayScnQuery->execute();
    Ogre::RaySceneQueryResult::iterator iter = result.begin();

    for(iter; iter != result.end(); iter++)
    {
        if(iter->worldFragment)
        {
            //gets the results, fixes camera height and breaks the loop
            Ogre::Real terrainHeight = iter->worldFragment->singleIntersection.y;

            if((terrainHeight + 10.0f) > camPos.y)
            {
                mCamera->setPosition(camPos.x, terrainHeight + 10.0f, camPos.z);
            }
            break;
        }
    }

    return true;
}

bool MApplication::mouseMoved(const OIS::MouseEvent& arg)
{
    //updates CEGUI with mouse movement
    CEGUI::System::getSingleton().injectMouseMove(arg.state.X.rel, arg.state.Y.rel);
    CEGUI::Point mousePos = CEGUI::MouseCursor::getSingleton().getPosition();

    //then send a raycast straight out from the camera at the mouse's position
    Ogre::Ray mouseRay = mCamera->getCameraToViewportRay(mousePos.d_x/float(arg.state.width), mousePos.d_y/float(arg.state.height));
    mRayScnQuery->setRay(mouseRay);
    mRayScnQuery->setSortByDistance(true);
    //   mRayScnQuery->setQueryMask(bRobotMode ? ROBOT_MASK : NINJA_MASK);	//will return objects with the query mask in the results
    static bool WasOver(false);
    static std::string ObjectLastOn;
    //std::cout << WasOver << std::endl;
    /*
    This next chunk finds the results of the raycast
    If the mouse is pointing at world geometry we spawn a robot at that position
    */
    Ogre::RaySceneQueryResult& result = mRayScnQuery->execute();
    Ogre::RaySceneQueryResult::iterator iter = result.begin();
    if(mObjectGrabbed){
        MButtonEventEmitter::getSingleton().emitGrab( mGrabbedObject->getName());
        std::cout << -(arg.state.Y.rel) << std::endl;
    }

    if(result.size() == 0){mMouseOver = false;}
    if(!mMouseOver){
        if(WasOver){
            MButtonEventEmitter::getSingleton().emitLeave(mCurrentObject->getName());
            WasOver = false;
        }
        for(iter; iter != result.end(); iter++)
        {
            //if you clicked on a robot or ninja it becomes selected
            if(iter->movable && iter->movable->getName().substr(0, 5) != "tile[" )
            {
                mMouseOver = true;
                mCurrentObject = iter->movable->getParentSceneNode();
                MButtonEventEmitter::getSingleton().emitEnter(mCurrentObject->getName());
                WasOver = true;
                ObjectLastOn = mCurrentObject->getName();


                break;
            }

        }

    }


    return true;
}

bool MApplication::mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id)
{
    if(id == OIS::MB_Left)
    {
        //show that the current object has been deselected by removing the bounding box visual
        if(mCurrentObject)
        {

            //    mCurrentObject->showBoundingBox(false);
        }

        //find the current mouse position
        CEGUI::Point mousePos = CEGUI::MouseCursor::getSingleton().getPosition();

        //then send a raycast straight out from the camera at the mouse's position
        Ogre::Ray mouseRay = mCamera->getCameraToViewportRay(mousePos.d_x/float(arg.state.width), mousePos.d_y/float(arg.state.height));
        mRayScnQuery->setRay(mouseRay);
        mRayScnQuery->setSortByDistance(true);
        //mRayScnQuery->setQueryMask(bRobotMode ? ROBOT_MASK : NINJA_MASK);	//will return objects with the query mask in the results

        /*
        This next chunk finds the results of the raycast
        If the mouse is pointing at world geometry we spawn a robot at that position
        */
        Ogre::RaySceneQueryResult& result = mRayScnQuery->execute();
        Ogre::RaySceneQueryResult::iterator iter = result.begin();

        for(iter; iter != result.end(); iter++)
        {
            //if you clicked on a robot or ninja it becomes selected
            if(iter->movable && iter->movable->getName().substr(0, 5) != "tile[")
            {
                mCurrentObject = iter->movable->getParentSceneNode();
                MButtonEventEmitter::getSingleton().emitClicked(mCurrentObject->getName());
                mObjectGrabbed = true;
                mGrabbedObject = iter->movable->getParentSceneNode();
                break;
            }
        }

    }
    return true;
}

bool MApplication::mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id)
{
    mObjectGrabbed = false;
    mGrabbedObject = 0;

    if(id  == OIS::MB_Left)
    {
        bLMouseDown = false;
    }
    else if(id == OIS::MB_Right)	//when the right mouse is released we then unhide the cursor
    {
        CEGUI::MouseCursor::getSingleton().show();
        bRMouseDown = false;
    }

    return true;
}

bool MApplication::keyPressed(const OIS::KeyEvent& arg)
{
    //check and see if the spacebar was hit, and this will switch which mesh is spawned
    if (arg.key == OIS::KC_ESCAPE)
    {
        mShutDown = true;
    }
    //then we return the base app keyPressed function so that we get all of the functionality
    //and the return value in one line
    return true;//BaseApplication::keyPressed(arg);
}


