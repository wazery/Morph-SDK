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

// TODO: Include all other sub-systems to manage them

// Total number of lines in one dimension will be (GRID_LINE_NUM * 2 + 1)
#define GRID_LINE_NUM 3

// Units of space between lines
#define GRID_LINE_SPACE 80

using namespace Morph;

MSystemManager* MSystemManager::smInstance = NULL;

MSystemManager::MSystemManager()
{
    mRoot = 0;
    mRenderWindow = 0;
    mWindowWidth  = 0;
    mWindowHeight = 0;
    mSceneManager = 0;
    mMainCamera   = 0;
    mCurrCamera   = 0;
    mViewport     = 0;

    mFloorGrid    = 0;
    mCircle       = 0;
    mIsInitialised = false;
}

MSystemManager::~MSystemManager(void)
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

    shutDown();
}

bool MSystemManager::initialise(String windowName, int width, int height, NameValuePairList *params, Root *pRoot)
{
    if (pRoot)
        mRoot = pRoot;
    else
    {
        mRoot = OGRE_NEW Ogre::Root("plugins.cfg", "ogre.cfg", "Ogre.log");
        Ogre::RenderSystem* renderSystem = mRoot->getRenderSystemByName("OpenGL Rendering Subsystem");
        renderSystem->setConfigOption("Full Screen", "No");
        mRoot->setRenderSystem(renderSystem);

        // Initialize the system, but don't create a render window.
        mRoot->initialise(false);

        mSceneManager = mRoot->createSceneManager(Ogre::ST_GENERIC);

        if (params)
            mRoot->createRenderWindow("Ogre rendering window", width, height, params);
        else
        {
            Ogre::NameValuePairList viewConfig;
            Ogre::String widgetHandle;
#ifdef Q_WS_WIN
            widgetHandle = Ogre::StringConverter::toString((size_t)((HWND)winId()));
#else
            QX11Info xInfo = QX11Info();
            widgetHandle = Ogre::StringConverter::toString((unsigned long)(xInfo.display())) + ":"
                    + Ogre::StringConverter::toString((unsigned int)(xInfo.screen())) + ":"
                    + Ogre::StringConverter::toString((unsigned long)(parentWidget()->winId())) + ":";
#endif
            viewConfig["externalWindowHandle"] = widgetHandle;
            mRenderWindow = mRoot->createRenderWindow("Ogre rendering window", width, height, &viewConfig);
        }
    }

    addResourceLocations();
    initResources();

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

void MSystemManager::resizeWindow(int width, int height)
{
    if (mIsInitialised && mRenderWindow)
    {
        mRenderWindow->windowMovedOrResized();

        if (height !=0 && mMainCamera != 0)
            mMainCamera->setAspectRatio(Ogre::Real(width) / Ogre::Real(height));

        mMainCamera->yaw(Ogre::Radian(0));
        mWindowWidth = width;
        mWindowHeight = height;
    }
}

bool MSystemManager::initOgreCore(String windowName, int width, int height, Ogre::NameValuePairList *params)
{
    // TODO: logging into the MLogManager
    mRenderWindow = mRoot->createRenderWindow(windowName, width, height, false, params);

    mMainCamera = mSceneManager->createCamera("Main Camera");
    mMainCamera->setPosition(0, 0, 80);
    mMainCamera->lookAt(0, 0, -300);
    mMainCamera->setNearClipDistance(5);
    //mMainCamera->setDebugDisplayEnabled(enabled); TODO: add the debug overlay

    // Create one viewport to the entire window
    mViewport = mRenderWindow->addViewport(mMainCamera);
    mViewport->setBackgroundColour(Ogre::ColourValue(0.19, 0.19, 0.19));
    mMainCamera->setAspectRatio(Ogre::Real(width) / Ogre::Real(height));
    mCurrCamera = mMainCamera;

    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

    // Setup animation default
    Ogre::Animation::setDefaultInterpolationMode(Ogre::Animation::IM_LINEAR);
    Ogre::Animation::setDefaultRotationInterpolationMode(Ogre::Animation::RIM_LINEAR);

    createScene();
    createGrid();

    return mIsInitialised;
    /** @return mIsInitialised */
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

void MSystemManager::setBackgroundColour(QColor c)
{
    if (mViewport)
    {
        Ogre::ColourValue colour;
        colour.setAsARGB(c.rgba());
        mViewport->setBackgroundColour(colour);
    }
}

void MSystemManager::setCameraPosition(const Ogre::Vector3 &pos)
{
    if (mCurrCamera)
    {
        mCurrCamera->setPosition(pos);
        mCurrCamera->lookAt(0, 50, 0);

        // FIXME: Not sure about it, needs testing!
        doRender();
    }
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

// TODO: Parameterize this function if needed.
void MSystemManager::addResourceLocations()
{
    ConfigFile cf;
    cf.load("resources.cfg");

    // Go through all sections & settings in the file
    ConfigFile::SectionIterator seci = cf.getSectionIterator();

    String secName, typeName, archName;
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        ConfigFile::SettingsMultiMap *settings = seci.getNext();
        ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
            ResourceGroupManager::getSingleton().addResourceLocation(
                        archName, typeName, secName);
        }
    }
}

void MSystemManager::initResources()
{
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
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

MSystemManager* MSystemManager::getSingletonPtr()
{
    if (smInstance == NULL)
        smInstance = new MSystemManager();

    return smInstance;
    /** @return smInstance */
}

MSystemManager &MSystemManager::getSingleton()
{
    if (smInstance == NULL)
        smInstance = new MSystemManager();

    return *smInstance;
    /** @return *smInstance */
}

void MSystemManager::releaseSingleton()
{
    if (smInstance)
    {
        delete smInstance;
        smInstance = NULL;
    }
}
