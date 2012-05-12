#include "mogrecanvas.h"

#ifdef Q_OS_UNIX
    #include <QX11Info>
#endif

using namespace Morph;
MOgreCanvas::MOgreCanvas(QString windowName, Ogre::SceneManager* sceneMgr, Ogre::ProjectionType projectionType, CameraPositions cameraPositions, Ogre::ColourValue backgorundColor, QWidget *parent) :
    QWidget(parent),
    mWindowName(windowName),
    mSceneMgr(sceneMgr),
    mRenderWindow(NULL),
    mCamera(NULL),
    hasGrid(false),
    mBackgroundColor(backgorundColor),
    mIsInitialised(false),
    mVp(NULL)
{
    mProjectionType = projectionType;
    mCameraPositions = cameraPositions;

    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_PaintOnScreen);
    //setAttribute(Qt::WA_NoBackground);

    setObjectName(windowName);

    setFocusPolicy(Qt::WheelFocus);
}

MOgreCanvas::~MOgreCanvas()
{
    if(mRenderWindow)
    {
        //mSceneMgr->destroyManualObject(mVp->getTarget()->getName() + "::" + StringConverter::toString(mVp->getZOrder()) + "::ViewportGrid");
        //mSceneMgr->destroySceneNode();
        mRenderWindow->removeAllViewports();
        mSceneMgr->destroyCamera(mCamera);
        mCamera = 0;
        mVp = 0;
        Ogre::Root::getSingleton().detachRenderTarget(mRenderWindow);
        mRenderWindow = 0;
        this->destroy();
    }
}

void MOgreCanvas::setPolygonMode(Ogre::PolygonMode pm)
{
    if(mCamera)
        mCamera->setPolygonMode(pm);
}

Ogre::PolygonMode MOgreCanvas::getPolygonMode()
{
    return mCamera->getPolygonMode();
}

void MOgreCanvas::setViewMode(CameraPositions cp)
{
    mCameraPivotNode->resetOrientation();

    switch(cp)
    {
        case CP_FRONT:
        {
            break;
        }
        case CP_BACK:
        {
            mCameraPivotNode->yaw(Ogre::Degree(180),Ogre::Node::TS_WORLD);
            break;
        }
        case CP_LEFT:
        {
            mCameraPivotNode->yaw(Ogre::Degree(90),Ogre::Node::TS_WORLD);
            break;
        }
        case CP_RIGHT:
        {
            mCameraPivotNode->yaw(Ogre::Degree(-90),Ogre::Node::TS_WORLD);
            break;
        }
        case CP_TOP:
        {
            mCameraPivotNode->pitch(Ogre::Degree(-90),Ogre::Node::TS_WORLD);
            break;
        }
        case CP_BOTTOM:
        {
            mCameraPivotNode->pitch(Ogre::Degree(90),Ogre::Node::TS_WORLD);
            break;
        }
        case CP_FREE:
        {
            mCameraPivotNode->yaw(Ogre::Degree(45),Ogre::Node::TS_WORLD);
            mCameraPivotNode->pitch(Ogre::Degree(-30),Ogre::Node::TS_LOCAL);
            break;
        }
    }

    mCameraPositions = cp;
}

void MOgreCanvas::setProjectionType(Ogre::ProjectionType pt)
{
    if(mCamera)
        mCamera->setProjectionType(pt);
}

void MOgreCanvas::paintEvent(QPaintEvent* e)
{
    QWidget::paintEvent(e);

    if(!mRenderWindow)
        init();

    Ogre:;Root::getSingleton().renderOneFrame();
}

void MOgreCanvas::init()
{
    Ogre::NameValuePairList viewConfig;
    Ogre::String widgetHandle;

#ifdef Q_OS_WIN
    widgetHandle = Ogre::StringConverter::toString((size_t)((HWND)winId()));
#else
    QX11Info info = x11Info();
    widgetHandle  = Ogre::StringConverter::toString((unsigned long)(info.display()));
    widgetHandle += ":";
    widgetHandle += Ogre::StringConverter::toString((unsigned int)(info.screen()));
    widgetHandle += ":";
    widgetHandle += Ogre::StringConverter::toString((unsigned long)(winId()));
#endif
    viewConfig["parentWindowHandle"] = widgetHandle;
    mRenderWindow = Ogre::Root::getSingleton().createRenderWindow(mWindowName.toStdString(), width(), height(), false, &viewConfig);

    mRenderWindow->setActive(true);

    mRenderWindow->resize(width(), height());
    mRenderWindow->setVisible(true);

    createOrbitalCamera();

    mVp = mRenderWindow->addViewport(mCamera);

    //float cr = ((1.0-0.0)*((float)rand()/RAND_MAX))+0.0;
    //float cg = ((1.0-0.0)*((float)rand()/RAND_MAX))+0.0;
    //float cb = ((1.0-0.0)*((float)rand()/RAND_MAX))+0.0;

    mVp->setBackgroundColour(mBackgroundColor);
    mIsInitialised = true;
    emit initialised();
}

void MOgreCanvas::createOrbitalCamera()
{
    mCamera = mSceneMgr->createCamera("#Camera_"+mRenderWindow->getName());
    MLogManager::getSingleton().logOutput(QString("Camera created with name: ") + QString(mCamera->getName().c_str()), M_EDITOR_MESSAGE);
    mCamera->setProjectionType(mProjectionType);
    mCamera->setNearClipDistance(0.1);
    mCamera->setAspectRatio(Ogre::Real(width()) / Ogre::Real(height()));

    if (Ogre::Root::getSingletonPtr()->getRenderSystem()->getCapabilities()->hasCapability(Ogre::RSC_INFINITE_FAR_PLANE))
        mCamera->setFarClipDistance(0);
    else
        mCamera->setFarClipDistance(20000.0);

    mCameraPivotNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();

    if(mProjectionType == Ogre::PT_PERSPECTIVE)
        mCamera->setPosition(40,70,160); //500
    else
        mCamera->setPosition(40,70,160); //10000

    mCamera->lookAt(mCameraPivotNode->getPosition());
    mCameraPivotNode->attachObject(mCamera);

    setViewMode(mCameraPositions);
}

void MOgreCanvas::resizeEvent(QResizeEvent* e)
{
    if(e->isAccepted())
    {
        if (mRenderWindow)
        {
            mCamera->setAspectRatio((float)e->size().width()/(float)e->size().height());
            mRenderWindow->resize(e->size().width(), e->size().height());
            mRenderWindow->windowMovedOrResized();
        }
    }

    QWidget::resizeEvent(e);
}

void MOgreCanvas::keyPressEvent(QKeyEvent* e)
{
    emit keyPress(e);
}

void MOgreCanvas::keyReleaseEvent(QKeyEvent* e)
{
    emit keyRelease(e);
}

void MOgreCanvas::mousePressEvent(QMouseEvent* e)
{
    emit mousePress(e);
}

void MOgreCanvas::mouseReleaseEvent(QMouseEvent* e)
{
    emit mouseRelease(e);
}

void MOgreCanvas::mouseMoveEvent(QMouseEvent* e)
{
    emit mouseMove(e);
}

void MOgreCanvas::wheelEvent(QWheelEvent * e)
{
    emit wheel(e);
}
void MOgreCanvas::mouseDoubleClickEvent(QMouseEvent *e)
{
    emit mouseDoubleClick(e);
}
