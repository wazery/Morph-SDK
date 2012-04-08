/* ============================================================
 *
 * This file is a part of Morph project
 *
 * Date        : 2011-10-26
 * @file msystemmanager.cpp
 * @brief A manager which is responsible for creating the basic things
 * that Ogre needs to start, in another word it bootstraps Ogre.
 *
 * Copyright (C) 2011-2012 by @author Islam Wazery <wazery at ubuntu dot com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation;
 * either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * ============================================================ */

#include <QX11Info>

#include "MSystemManager.h"
#include "MLogManager.h"
#include "mOgreEntityViewer/mogrelogproxy.h"

// TODO: Include all other sub-systems to manage them

// Total number of lines in one dimension will be (GRID_LINE_NUM * 2 + 1)
#define GRID_LINE_NUM 3

// Units of space between lines
#define GRID_LINE_SPACE 80

using namespace Morph;

const QPoint     MSystemManager::invalidMousePoint(-1, -1);
const Ogre::Real MSystemManager::turboModifier(10);

MSystemManager::MSystemManager(QWidget *parent)
    : QWidget(parent),
      mRoot(0),
    mRenderWindow(0),
    mWindowWidth(0),
    mWindowHeight(0),
    mSceneManager(0),
    mMainCamera(0),
    mCurrCamera(0),
    mViewport(0),
    oldPos(invalidMousePoint),

    mFloorGrid(0),
    mCircle(0)
{
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_InputMethodEnabled);
    setMinimumSize(240, 240);
    setFocusPolicy(Qt::ClickFocus);
}

MSystemManager::~MSystemManager()
{
    if (mRenderWindow)
    {
        mRenderWindow->removeAllViewports();
    }

    if (mRoot)
    {
        mRoot->detachRenderTarget(mRenderWindow);

        if (mSceneManager)
        {
            mRoot->destroySceneManager(mSceneManager);
        }
    }

    //shutDown();
    delete mRoot;
}

//void MSystemManager::setBackgroundColor(QColor c)
//{
//    if(ogreViewport)
//    {
//        Ogre::ColourValue ogreColour;
//        ogreColour.setAsARGB(c.rgba());
//        ogreViewport->setBackgroundColour(ogreColour);
//    }
//}

QPaintEngine* MSystemManager::paintEngine() const
{
    // I don't want another paint engine to get in the way for my Ogre based paint engine.
    // So this return nothing.
    return NULL;
}

void MSystemManager::paintEvent(QPaintEvent *e)
{
    if(!mRoot)
    {
        initialise();
    }

    mRoot->_fireFrameStarted();
    mRenderWindow->update(true);
    mRoot->_fireFrameEnded();

    e->accept();
}

void MSystemManager::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);

    if(e->isAccepted())
    {
        const QSize &newSize = e->size();
        if(mRenderWindow)
        {
            mRenderWindow->resize(newSize.width(), newSize.height());
            mRenderWindow->windowMovedOrResized();
        }
        if(mCurrCamera)
        {
            Ogre::Real aspectRatio = Ogre::Real(newSize.width()) / Ogre::Real(newSize.height());
            mCurrCamera->setAspectRatio(aspectRatio);
        }
    }
}

void MSystemManager::keyPressEvent(QKeyEvent *e)
{
    static QMap<int, Ogre::Vector3> keyCoordModificationMapping;
    static bool mappingInitialised = false;

    if(!mappingInitialised)
    {
        // ToDo: Enhance the navigation.
        keyCoordModificationMapping[Qt::Key_W] 		  = Ogre::Vector3( 0, 0,-5);
        keyCoordModificationMapping[Qt::Key_S] 		  = Ogre::Vector3( 0, 0, 5);
        keyCoordModificationMapping[Qt::Key_A] 		  = Ogre::Vector3(-5, 0, 0);
        keyCoordModificationMapping[Qt::Key_D] 		  = Ogre::Vector3( 5, 0, 0);
        keyCoordModificationMapping[Qt::Key_PageUp]   = Ogre::Vector3( 0, 5, 0);
        keyCoordModificationMapping[Qt::Key_PageDown] = Ogre::Vector3( 0,-5, 0);

        mappingInitialised = true;
    }

    QMap<int, Ogre::Vector3>::iterator keyPressed =
            keyCoordModificationMapping.find(e->key());
    if(keyPressed != keyCoordModificationMapping.end() && mCurrCamera)
    {
        const Ogre::Vector3 &actualCamPos = mCurrCamera->getPosition();
        setCameraPosition(actualCamPos + keyPressed.value());

        e->accept();
    }
    else
    {
        e->ignore();
    }
}

void MSystemManager::moveEvent(QMoveEvent *e)
{
    QWidget::moveEvent(e);

    if(e->isAccepted() && mRenderWindow)
    {
        mRenderWindow->windowMovedOrResized();
        update();
    }
}

void MSystemManager::mouseDoubleClickEvent(QMouseEvent *e)
{
    if(e->buttons().testFlag(Qt::LeftButton))
    {
        Ogre::Real x = e->pos().x() / (float)width();
        Ogre::Real y = e->pos().y() / (float)height();

        Ogre::Ray ray = mCurrCamera->getCameraToViewportRay(x, y);
        Ogre::RaySceneQuery *query = mSceneManager->createRayQuery(ray);
        Ogre::RaySceneQueryResult &queryResult = query->execute();
        Ogre::RaySceneQueryResult::iterator queryResultIterator = queryResult.begin();

        if(queryResultIterator != queryResult.end())
        {
            if(queryResultIterator->movable)
            {
                // when the object is double clicked..
                // replace the last line with whatever you want
                selectedNode = queryResultIterator->movable->getParentSceneNode();

                //button_object_clicked(selectedNode->getAttachedObject(0)->getName() );

                selectedNode->showBoundingBox(true);
            }
        }
        else
        {
            if (selectedNode)
            {
                // when you double click on any other object..
                selectedNode->showBoundingBox(false);
                selectedNode = 0;
            }
        }
        mSceneManager->destroyQuery(query);
        update();
        e->accept();
    }
    else
    {
        e->ignore();
    }
}

void MSystemManager::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons().testFlag(Qt::LeftButton) && oldPos != invalidMousePoint)
    {
        const QPoint &pos = e->pos();
        Ogre::Real deltaX = pos.x() - oldPos.x();
        Ogre::Real deltaY = pos.y() - oldPos.y();

        if(e->modifiers().testFlag(Qt::ControlModifier))
        {
            deltaX *= turboModifier;
            deltaY *= turboModifier;
        }

        Ogre::Vector3 camTranslation(deltaX, deltaY, 0);
        const Ogre::Vector3 &actualCamPos = mCurrCamera->getPosition();
        setCameraPosition(actualCamPos + camTranslation);

        oldPos = pos;
        e->accept();
    }
    else
    {
        e->ignore();
    }
}

void MSystemManager::mousePressEvent(QMouseEvent *e)
{
    if(e->buttons().testFlag(Qt::LeftButton))
    {
        oldPos = e->pos();
        e->accept();
    }
    else
    {
        e->ignore();
    }
}

void MSystemManager::mouseReleaseEvent(QMouseEvent *e)
{
    if(!e->buttons().testFlag(Qt::LeftButton))
    {
        oldPos = QPoint(invalidMousePoint);
        e->accept();
    }
    else
    {
        e->ignore();
    }
}

void MSystemManager::wheelEvent(QWheelEvent *e)
{
    Ogre::Vector3 zTranslation(0,0, -e->delta() / 10);

    if(e->modifiers().testFlag(Qt::ControlModifier))
    {
        zTranslation.z *= turboModifier;
    }

    const Ogre::Vector3 &actualCamPos = mCurrCamera->getPosition();
    setCameraPosition(actualCamPos + zTranslation);

    e->accept();
}

bool MSystemManager::initialise()
{      
        mRoot = OGRE_NEW Ogre::Root();

        // Logging Ogre messages to the editors logging listeners.
        MOgreLogProxy* log = new MOgreLogProxy();
        Ogre::LogManager::getSingleton().getDefaultLog()->addListener(log);

        Ogre::RenderSystem* renderSystem = mRoot->getRenderSystemByName("OpenGL Rendering Subsystem");
        mRoot->setRenderSystem(renderSystem);
        mRoot->getRenderSystem()->setConfigOption("Full Screen", "No");


        // Initialize the system, but don't create a render window.
        mRoot->initialise(false);

        mSceneManager = mRoot->createSceneManager(Ogre::ST_GENERIC);

        Ogre::NameValuePairList viewConfig;
        Ogre::String widgetHandle;

    #ifdef Q_WS_WIN
        widgetHandle = Ogre::StringConverter::toString((size_t)((HWND)winId()));
    #else
        //QWidget *q_parent = dynamic_cast <QWidget *> (parent());
        QX11Info xInfo = x11Info();

        widgetHandle =
                widgetHandle = Ogre::StringConverter::toString((unsigned long)(xInfo.display())) + ":"
                + Ogre::StringConverter::toString((unsigned int)(xInfo.screen())) + ":"
                + Ogre::StringConverter::toString((unsigned long)(parentWidget()->winId())) + ":";
    #endif
        viewConfig["externalWindowHandle"] = widgetHandle;
        mRenderWindow = mRoot->createRenderWindow("Ogre rendering window",
                                                        width(), height(), false, &viewConfig);
        initOgreCore(width(), height());

    if (!mRoot)
        return false;

    /** @return bool */
    return true;
}

void MSystemManager::shutDown()
{
    mRoot->destroyAllRenderQueueInvocationSequences();
    mRoot->destroySceneManager(mSceneManager);
    OGRE_DELETE mRoot;
    mRoot = 0;
}

bool MSystemManager::initOgreCore(Ogre::Real width, Ogre::Real height)
{
    mMainCamera = mSceneManager->createCamera("Main Camera");
    MLogManager::getSingleton().logOutput("Main camera created", M_WARN);
    mMainCamera->setPosition(0, 0, 80);
    mMainCamera->lookAt(0, 0, -300);
    mMainCamera->setNearClipDistance(5);
    //mMainCamera->setDebugDisplayEnabled(enabled); TODO: add the debug overlay

    // Create one viewport to the entire window
    mViewport = mRenderWindow->addViewport(mMainCamera);
    MLogManager::getSingleton().logOutput("Added viewport", M_WARN);
    mViewport->setBackgroundColour(Ogre::ColourValue(0.117647059, 0.117647059, 0.117647059));
    mMainCamera->setAspectRatio(Ogre::Real(width) / Ogre::Real(height));
    mCurrCamera = mMainCamera;

    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

    // Setup animation default
    Ogre::Animation::setDefaultInterpolationMode(Ogre::Animation::IM_LINEAR);
    Ogre::Animation::setDefaultRotationInterpolationMode(Ogre::Animation::RIM_LINEAR);

    initResources();
    MLogManager::getSingleton().logOutput("Initialised all resources", M_WARN);
    createScene();
    MLogManager::getSingleton().logOutput("Scene created", M_WARN);
    createGrid();

    return mIsInitialised;
    /** @return mIsInitialised */
}

// TODO: Parameterize this function if needed.
void MSystemManager::addResourceLocations()
{
//    ConfigFile cf;
//    cf.load("resources.cfg");

//    // Go through all sections & settings in the file
//    ConfigFile::SectionIterator seci = cf.getSectionIterator();

//    String secName, typeName, archName;
//    while (seci.hasMoreElements())
//    {
//        secName = seci.peekNextKey();
//        ConfigFile::SettingsMultiMap *settings = seci.getNext();
//        ConfigFile::SettingsMultiMap::iterator i;
//        for (i = settings->begin(); i != settings->end(); ++i)
//        {
//            typeName = i->first;
//            archName = i->second;
//            ResourceGroupManager::getSingleton().addResourceLocation(
//                        archName, typeName, secName);
//        }
//    }
}

void MSystemManager::initResources()
{
    Ogre::ResourceGroupManager *rgm = Ogre::ResourceGroupManager::getSingletonPtr();
    rgm->addResourceLocation("meshes/SdkTrays.zip", "Zip", "Bootstrap");
    rgm->addResourceLocation("meshes", "FileSystem", "General");
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void MSystemManager::createScene()
{
    mSceneManager->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
    Ogre::Light* lightSource = mSceneManager->createLight("Main Light Source");
    lightSource->setPosition(Ogre::Vector3(20, 80, 50));

    Ogre::Entity* ogrehead = mSceneManager->createEntity("Ogre Head", "ogrehead.mesh");
    mSceneManager->getRootSceneNode()->createChildSceneNode("ogreHead")->attachObject(ogrehead);

    // TODO: logging the complete of initialisation.
}

void MSystemManager::destroyScene()
{
    if (mSceneManager)
    {
        mSceneManager->destroyAllLights();
        mSceneManager->destroyAllEntities();;
    }
}

void MSystemManager::doRender()
{
    if (!mIsInitialised || !mRenderWindow)
        return;

    mRoot->renderOneFrame();
}

void MSystemManager::createGrid()
{
    try
    {
        mFloorGrid = mSceneManager->createManualObject("editingFloorGrid");
        mFloorGrid->begin("editingFloorGridLines", RenderOperation::OT_LINE_LIST);

        for (int x=(-GRID_LINE_NUM * GRID_LINE_SPACE); x <= GRID_LINE_NUM * GRID_LINE_SPACE; x += GRID_LINE_SPACE)
        {
            mFloorGrid->position(Vector3(x, 0, -GRID_LINE_NUM * GRID_LINE_SPACE));
            mFloorGrid->position(Vector3(x, 0, GRID_LINE_NUM * GRID_LINE_SPACE));
        }

        for (int z = -GRID_LINE_NUM * GRID_LINE_SPACE; z <= GRID_LINE_NUM * GRID_LINE_SPACE; z += GRID_LINE_SPACE)
        {
            mFloorGrid->position(Vector3(-GRID_LINE_NUM * GRID_LINE_SPACE, 0, z));
            mFloorGrid->position(Vector3(GRID_LINE_NUM * GRID_LINE_SPACE, 0, z));
        }

        mFloorGrid->end();
        mFloorGrid->setCastShadows(false);
        mFloorGrid->setQueryFlags(0);

        mSceneManager->getRootSceneNode()->createChildSceneNode("floorGrid")->attachObject(mFloorGrid);


        mCircle = mSceneManager->createManualObject("circle");
        mCircle->begin("circle_line", RenderOperation::OT_LINE_STRIP);

        const int segs = 200;
        const float delta = (float)(2 * Ogre::Math::PI / segs);

        for (int i = 0; i < segs; ++i)
            mCircle->position((float)Ogre::Math::Sin(i * delta), 0, (float)Ogre::Math::Cos(i * delta));

        // TODO: make 3 colored dimensions arrows
        mCircle->colour(Ogre::Real(1), Ogre::Real(0), Ogre::Real(0));

        mCircle->end();
        SceneNode * centerNode = mSceneManager->getRootSceneNode()->createChildSceneNode("centerCircle");
        centerNode->attachObject(mCircle);
    }
    catch (Ogre::Exception& e)
    {
        // TODO: Logging to the LogManager
    }
}

void MSystemManager::setCameraPosition(const Ogre::Vector3 &pos)
{
    mCurrCamera->setPosition(pos);
    mCurrCamera->lookAt(0, 50, 0);
    update();
    emit cameraPositionChanged(pos);
}

void MSystemManager::addViewport(Ogre::Camera camera)
{
    if (mRenderWindow)
        mRenderWindow->addViewport(&camera);
}

/*void MSystemManager::createResourceListener()
{
    Ogre::ResourceGroupListener::resourceGroupLoadStarted()
}*/

void MSystemManager::createFrameListener()
{
}

void MSystemManager::updateStats(void)
{
    //mRenderWindow->updateStats();
}

bool MSystemManager::frameStarted(const FrameEvent& evt)
{
    if (mRenderWindow->isClosed())
        return false;

    // TODO: MManipToolsManager::getSingleton().updateFrame(evt.timeSinceLastFrame);
    return true;
    /** @return bool */
}

bool MSystemManager::frameEnded(const FrameEvent& evt)
{
    updateStats();

    /** @return bool */
    return true;
}

//MSystemManager* MSystemManager::getSingletonPtr()
//{
//    if (smInstance == NULL)
//        smInstance = new MSystemManager();

//    return smInstance;
//    /** @return smInstance */
//}

//MSystemManager &MSystemManager::getSingleton()
//{
//    if (smInstance == NULL)
//        smInstance = new MSystemManager();

//    return *smInstance;
//    /** @return *smInstance */
//}

//void MSystemManager::releaseSingleton()
//{
//    if (smInstance)
//    {
//        delete smInstance;
//        smInstance = NULL;
//    }
//}