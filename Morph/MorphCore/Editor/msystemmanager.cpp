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

#include "mainwindow.h"

// TODO: Include all other sub-systems to manage them

// Total number of lines in one dimension will be (GRID_LINE_NUM * 2 + 1)
#define GRID_LINE_NUM 3

// Units of space between lines
#define GRID_LINE_SPACE 80

using namespace Morph;

const QPoint     MSystemManager::invalidMousePoint(-1, -1);
const Ogre::Real MSystemManager::turboModifier(10);

MSystemManager* MSystemManager::smInstance = NULL;

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
    mainEnt(0),
    mainEntAnim(0),
    mainNode(0),
    mainSubEnt(0),
    oldPos(invalidMousePoint),

    mFloorGrid(0),
    mCircle(0)
{
    lightDiffuseColor.setAsRGBA(qRgba(0, 0, 0, 1));
    lightSpecularColor.setAsRGBA(qRgba(0, 0, 0, 1));
    ambientLightColor.setAsRGBA(qRgba(0, 0, 0, 1));

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
    if(mainEnt != NULL && mainNode != NULL)
    {
        switch(e->key())
        {
        case Qt::Key_W:
        case Qt::Key_Up:
            rotX = -0.1;
            mainNode->pitch(Radian(rotX));
            repaint();
            break;
        case Qt::Key_S:
        case Qt::Key_Down:
            rotX = 0.1;
            mainNode->pitch(Radian(rotX));
            repaint();
            break;
        case Qt::Key_A:
        case Qt::Key_Left:
            rotY = -0.1;
            mainNode->yaw(Radian(rotY));
            repaint();
            break;
        case Qt::Key_D:
        case Qt::Key_Right:
            rotY = 0.1;
            mainNode->yaw(Radian(rotY));
            repaint();
            break;
        case Qt::Key_R:
            mCurrCamera->setPosition(0, 50, 0);
            repaint();
            break;
        }
    }
}

void MSystemManager::keyReleaseEvent(QKeyEvent* e)
{
    if(mainEnt != NULL && mainNode != NULL)
    {
        switch(e->key()){
            case Qt::Key_W:
            case Qt::Key_Up:
                rotX = 0.0;
                mainNode->pitch(Radian(rotX));
                repaint();
                break;
            case Qt::Key_S:
            case Qt::Key_Down:
                rotX = 0.0;
                mainNode->pitch(Radian(rotX));
                repaint();
                break;
            case Qt::Key_A:
            case Qt::Key_Left:
                rotY = 0.0;
                mainNode->yaw(Radian(rotY));
                repaint();
                break;
            case Qt::Key_D:
            case Qt::Key_Right:
                rotY = 0.0;
                mainNode->yaw(Radian(rotY));
                repaint();
                break;
        }
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
    if(mouseMiddleBtn || mouseLeftPressed)
    {
        QPoint currentPos = e->pos();

        if(mousePos.x() < currentPos.x())
            mDirection.x = 1;
        else if(mousePos.x() > currentPos.x())
            mDirection.x = -1;
        else
            mDirection.x = 0;

        if(mousePos.y() < currentPos.y())
            mDirection.y = -1;
        else if(mousePos.y() > currentPos.y())
            mDirection.y = 1;
        else
            mDirection.y = 0;

        update();
        mousePos = currentPos;
        mDirection = Vector3::ZERO;
    }
    if(mouseRightPressed)
    {
        QPoint currentPos = e->pos();

        if(mousePos.x() < currentPos.x())
            angleX = -0.01;
        else if(mousePos.x() > currentPos.x())
            angleX = 0.01;
        else
            angleX = 0.00;

        if(mousePos.y() < currentPos.y())
            angleY = -0.01;
        else if(mousePos.y() > currentPos.y())
            angleY = 0.01;
        else
            angleY = 0.00;

        update();
        mousePos = currentPos;
        angleX = 0.00;
        angleY = 0.00;
    }
    //if(mouseLeftPressed){
    //	QPoint currentPos = e->pos();

    //	if(mousePos.x() < currentPos.x())
    //		mDirection.x = -0.01;
    //	else if(mousePos.x() > currentPos.x())
    //		mDirection.x = 0.01;
    //	else
    //		mDirection.x = 0;
    //
    //	update();
    //	mousePos = currentPos;
    //	mDirection = Vector3::ZERO;
    //}
    //if(mouseRightPressed){
    //       QPoint currentPos = e->pos();

    //	if(mousePos.x() < currentPos.x())
    //		mDirection.x = -0.01;
    //	else if(mousePos.x() > currentPos.x())
    //		mDirection.x = 0.01;
    //	else
    //		mDirection.x = 0;

    //	if(mousePos.y() < currentPos.y())
    //		mDirection.y = -0.01;
    //	else if(mousePos.y() > currentPos.y())
    //		mDirection.y = 0.01;
    //	else
    //		mDirection.y = 0;

    //	mousePos = currentPos;
 //       update();
    //	mDirection = Vector3::ZERO;
    //}
}

void MSystemManager::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
        mouseLeftPressed = true;
    if(e->button() == Qt::RightButton)
    {
        mouseRightPressed = true;
        mousePos = e->pos();
    }
    if(e->button() == Qt::MidButton)
        mouseMiddleBtn = true;
}

void MSystemManager::mouseReleaseEvent(QMouseEvent *e)
{
    Q_UNUSED(e);
    mouseLeftPressed = false;
    mouseRightPressed = false;
    mouseMiddleBtn = false;
}

void MSystemManager::wheelEvent(QWheelEvent *e)
{
    mDirection.z = -e->delta()/12;
    update();
    mDirection.z = 0;
}

void MSystemManager::update()
{
    if(mRenderWindow != NULL)
    {
        mRoot->_fireFrameStarted();
        mRenderWindow->update();

        mCurrCamera->moveRelative(mDirection);
        mCurrCamera->yaw(Radian(angleX));
        mCurrCamera->pitch(Radian(angleY));

        updateStats();
        mRoot->_fireFrameEnded();
    }
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
    MLogManager::getSingleton().logOutput("Main camera created", M_EDITOR_MESSAGE);
    mMainCamera->setPosition(0, 0, 80);
    mMainCamera->lookAt(0, 0, -300);
    mMainCamera->setNearClipDistance(5);
    //mMainCamera->setDebugDisplayEnabled(enabled); TODO: add the debug overlay

    // Create one viewport to the entire window
    mViewport = mRenderWindow->addViewport(mMainCamera);
    MLogManager::getSingleton().logOutput("Added viewport", M_EDITOR_MESSAGE);
    mViewport->setBackgroundColour(Ogre::ColourValue(0.117647059, 0.117647059, 0.117647059));
    mMainCamera->setAspectRatio(Ogre::Real(width) / Ogre::Real(height));
    mCurrCamera = mMainCamera;

    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

    // Setup animation default
    Ogre::Animation::setDefaultInterpolationMode(Ogre::Animation::IM_LINEAR);
    Ogre::Animation::setDefaultRotationInterpolationMode(Ogre::Animation::RIM_LINEAR);

    addResourceLocations();
    initResources();
    MLogManager::getSingleton().logOutput("Initialised all resources", M_EDITOR_MESSAGE);
    createScene();
    MLogManager::getSingleton().logOutput("Scene created", M_EDITOR_MESSAGE);
    createGrid();
    MLogManager::getSingleton().logOutput("Grid is set to: ON", M_EDITOR_MESSAGE);
    createLight();
    MLogManager::getSingleton().logOutput("Added light", M_EDITOR_MESSAGE);

    //FIXME: Implement it for the debug overlay
    //createFrameListener();

    return mIsInitialised;
    /** @return mIsInitialised */
}

// TODO: Parameterize this function if needed.
void MSystemManager::addResourceLocations()
{
    // Load resource paths from config file
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
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
            // OS X does not set the working directory relative to the app,
            // In order to make things portable on OS X we need to provide
            // the loading with it's own bundle path location
            ResourceGroupManager::getSingleton().addResourceLocation(
                String(macBundlePath() + "/" + archName), typeName, secName);
#else
            ResourceGroupManager::getSingleton().addResourceLocation(
                archName, typeName, secName);
#endif
        }
    }
}

void MSystemManager::initResources()
{
    Ogre::ResourceGroupManager *rgm = Ogre::ResourceGroupManager::getSingletonPtr();
    rgm->addResourceLocation("meshes/SdkTrays.zip", "Zip", "Bootstrap");
    rgm->addResourceLocation("meshes", "FileSystem", "General");
    rgm->addResourceLocation("meshes/ogrehead.mesh", "FileSystem", "General");
    rgm->addResourceLocation("meshes/jaiqua.mesh", "FileSystem", "General");
    ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void MSystemManager::createScene()
{
    mSceneManager->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
    Ogre::Light* lightSource = mSceneManager->createLight("Main Light Source");
    lightSource->setPosition(Ogre::Vector3(20, 80, 50));

    addObject("jaiqua.mesh");
}

void MSystemManager::createLight()
{
    mSceneManager->setAmbientLight(ColourValue(1, 1, 1));
    ambientOldColor = QColor(Qt::white);
    mainLight = mSceneManager->createLight("Main Light");
    mainLight->setPosition(0, 100, -500);
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
        MLogManager::getSingletonPtr()->logOutput("Couldn't create the grid!", M_ERROR);
    }
}

void MSystemManager::setCameraPosition(const Ogre::Vector3 &pos)
{
    mCurrCamera->setPosition(pos);
    mCurrCamera->lookAt(0, 50, 0);
    update();
    emit cameraPositionChanged(pos);
}

void MSystemManager::setBoundingBoxes(int value)
{
    if(value)
        mainNode->showBoundingBox(true);
    else
        mainNode->showBoundingBox(false);
}

void MSystemManager::setSkeleton(int value)
{
    if(value)
        mainEnt->setDisplaySkeleton(true);
    else
        mainEnt->setDisplaySkeleton(false);
}

void MSystemManager::setBackgroundColor(QColor color)
{
    Ogre::ColourValue ogreColor;
    ogreColor.setAsARGB(color.rgba());
    mViewport->setBackgroundColour(ogreColor);
}

void MSystemManager::setShadow(int fogType)
{
    if(fogType == 0)
        mSceneManager->setShadowTechnique(SHADOWTYPE_NONE);
    else if(fogType == 1)
        mSceneManager->setShadowTechnique(SHADOWTYPE_STENCIL_MODULATIVE);
    else if(fogType == 2)
        mSceneManager->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE);
    else if(fogType == 3)
        mSceneManager->setShadowTechnique(SHADOWTYPE_TEXTURE_MODULATIVE);
}

void MSystemManager::setAmbientLight(QColor color)
{
    mSceneManager->setAmbientLight(ColourValue(color.redF(), color.greenF(), color.blueF(), color.alphaF()));
    ambientOldColor = color;
}

QColor MSystemManager::getAmbientLight()
{
    return ambientOldColor;
}

void MSystemManager::setDiffuseColor(QColor color)
{
    diffuseOldColor = color;
}

QColor MSystemManager::getDiffuseColor()
{
    return diffuseOldColor;
}

void MSystemManager::setSpecularColor(QColor color)
{
    specularOldColor = color;
}

QColor MSystemManager::getSpecularColor()
{
    return specularOldColor;
}

void MSystemManager::updateMaterial()
{
    for(unsigned int i=0; i<mainEnt->getNumSubEntities(); ++i)
    {
        mainSubEnt = mainEnt->getSubEntity(i);
        mainSubEnt->getMaterial()->reload();
    }
}

void MSystemManager::createPointLight(String name, String xPos, String yPos, String zPos, String diffuse, String specular)
{
    Light* newLight = mSceneManager->createLight(name);
    newLight->setPosition(StringConverter::parseReal(xPos), StringConverter::parseReal(yPos), StringConverter::parseReal(zPos));

    QColor diffuseColor(diffuse.c_str());
    QColor specularColor(specular.c_str());
    lightDiffuseColor.setAsRGBA(diffuseColor.rgba());
    lightSpecularColor.setAsRGBA(specularColor.rgba());
    diffuseOldColor = diffuseColor;
    specularOldColor = specularColor;
    newLight->setDiffuseColour(diffuseColor.redF(), diffuseColor.greenF(), diffuseColor.blueF());
    newLight->setSpecularColour(specularColor.redF(), specularColor.greenF(), specularColor.blueF());
}

void MSystemManager::createDirectionalLight(String name, String xDir, String yDir, String zDir, String diffuse, String specular)
{
    Light* newLight = mSceneManager->createLight(name);
    newLight->setDirection(StringConverter::parseReal(xDir), StringConverter::parseReal(yDir), StringConverter::parseReal(zDir));

    QColor diffuseColor(diffuse.c_str());
    QColor specularColor(specular.c_str());
    lightDiffuseColor.setAsRGBA(diffuseColor.rgba());
    lightSpecularColor.setAsRGBA(specularColor.rgba());
    diffuseOldColor = diffuseColor;
    specularOldColor = specularColor;
    newLight->setDiffuseColour(diffuseColor.redF(), diffuseColor.greenF(), diffuseColor.blueF());
    newLight->setSpecularColour(specularColor.redF(), specularColor.greenF(), specularColor.blueF());
}

void MSystemManager::createSpotlight(String name, String xPos, String yPos, String zPos, String xDir, String yDir, String zDir, String diffuse, String specular)
{
    Light* newLight = mSceneManager->createLight(name);
    newLight->setPosition(StringConverter::parseReal(xPos), StringConverter::parseReal(yPos), StringConverter::parseReal(zPos));
    newLight->setDirection(StringConverter::parseReal(xDir), StringConverter::parseReal(yDir), StringConverter::parseReal(zDir));

    QColor diffuseColor(diffuse.c_str());
    QColor specularColor(specular.c_str());
    lightDiffuseColor.setAsRGBA(diffuseColor.rgba());
    lightSpecularColor.setAsRGBA(specularColor.rgba());
    diffuseOldColor = diffuseColor;
    specularOldColor = specularColor;
    newLight->setDiffuseColour(diffuseColor.redF(), diffuseColor.greenF(), diffuseColor.blueF());
    newLight->setSpecularColour(specularColor.redF(), specularColor.greenF(), specularColor.blueF());
}

void MSystemManager::updatePointLight(String oldName, String name, String xPos, String yPos, String zPos, String diffuse, String specular)
{
    Light* newLight = NULL;
    if(oldName != "none"){//name has changed
        mSceneManager->destroyLight(oldName);
        newLight = mSceneManager->createLight(name);
    }
    else
        newLight = mSceneManager->getLight(name);

    newLight->setPosition(StringConverter::parseReal(xPos), StringConverter::parseReal(yPos), StringConverter::parseReal(zPos));

    QColor diffuseColor(diffuse.c_str());
    QColor specularColor(specular.c_str());
    lightDiffuseColor.setAsRGBA(diffuseColor.rgba());
    lightSpecularColor.setAsRGBA(specularColor.rgba());
    diffuseOldColor = diffuseColor;
    specularOldColor = specularColor;
    newLight->setDiffuseColour(diffuseColor.redF(), diffuseColor.greenF(), diffuseColor.blueF());
    newLight->setSpecularColour(specularColor.redF(), specularColor.greenF(), specularColor.blueF());
}

void MSystemManager::updateDirectionalLight(String oldName, String name, String xDir, String yDir, String zDir, String diffuse, String specular)
{
    Light* newLight = NULL;
    if(oldName != "none"){//name has changed
        mSceneManager->destroyLight(oldName);
        newLight = mSceneManager->createLight(name);
    }
    else
        newLight = mSceneManager->getLight(name);

    newLight->setDirection(StringConverter::parseReal(xDir), StringConverter::parseReal(yDir), StringConverter::parseReal(zDir));

    QColor diffuseColor(diffuse.c_str());
    QColor specularColor(specular.c_str());
    lightDiffuseColor.setAsRGBA(diffuseColor.rgba());
    lightSpecularColor.setAsRGBA(specularColor.rgba());
    diffuseOldColor = diffuseColor;
    specularOldColor = specularColor;
    newLight->setDiffuseColour(diffuseColor.redF(), diffuseColor.greenF(), diffuseColor.blueF());
    newLight->setSpecularColour(specularColor.redF(), specularColor.greenF(), specularColor.blueF());
}

void MSystemManager::updateSpotlight(String oldName, String name, String xPos, String yPos, String zPos, String xDir, String yDir, String zDir, String diffuse, String specular)
{
    Light* newLight = NULL;
    if(oldName != "none"){//name has changed
        mSceneManager->destroyLight(oldName);
        newLight = mSceneManager->createLight(name);
    }
    else
        newLight = mSceneManager->getLight(name);

    newLight->setPosition(StringConverter::parseReal(xPos), StringConverter::parseReal(yPos), StringConverter::parseReal(zPos));
    newLight->setDirection(StringConverter::parseReal(xDir), StringConverter::parseReal(yDir), StringConverter::parseReal(zDir));

    QColor diffuseColor(diffuse.c_str());
    QColor specularColor(specular.c_str());
    lightDiffuseColor.setAsRGBA(diffuseColor.rgba());
    lightSpecularColor.setAsRGBA(specularColor.rgba());
    diffuseOldColor = diffuseColor;
    specularOldColor = specularColor;
    newLight->setDiffuseColour(diffuseColor.redF(), diffuseColor.greenF(), diffuseColor.blueF());
    newLight->setSpecularColour(specularColor.redF(), specularColor.greenF(), specularColor.blueF());
}

void MSystemManager::deleteLight(String name)
{
    mSceneManager->destroyLight(name);
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
//   mDebugOverlay = OverlayManager::getSingleton().getByName("Core/DebugOverlay");
//   mDebugOverlay->show();

   //mRoot->getSingletonPtr()->addFrameListener(this);
}

void MSystemManager::updateStats(void)
{
    //mRenderWindow->updateStats();
}

bool MSystemManager::frameStarted(const FrameEvent& e)
{
    if (mRenderWindow->isClosed())
        return false;

    // TODO: MManipToolsManager::getSingleton().updateFrame(e.timeSinceLastFrame);
    return true;
    /** @return bool */
}

bool MSystemManager::frameEnded(const FrameEvent& e)
{
    updateStats();

    /** @return bool */
    return true;
}

void MSystemManager::dragEnterEvent(QDragEnterEvent* e)
{
#if defined(Q_WS_WIN)
    if(e->mimeData()->hasUrls())
    {
        QRegExp fileMatcher("^/([A-Z]:/.*\\.mesh)$");
        if( fileMatcher.exactMatch(e->mimeData()->urls().first().path()) )
            e->acceptProposedAction();
    }
#else
    QRegExp fileMatcher("^file://(/.*\\.mesh)$");
    if( fileMatcher.exactMatch(e->mimeData()->text()) )
        e->acceptProposedAction();
#endif
}

void MSystemManager::dropEvent(QDropEvent* e)
{
#if defined(Q_WS_WIN)
    QRegExp fileMatcher("^/([A-Z]:/.*\\.mesh)$");
    if( fileMatcher.exactMatch(e->mimeData()->urls().first().path()) )
    {
        QString meshName = fileMatcher.cap(1);
        meshName.replace("/", "\\");
#else
    QRegExp fileMatcher("^file://(/.*\\.mesh)$");
    if( fileMatcher.exactMatch(e->mimeData()->text()) )
    {
        QString name = fileMatcher.cap(1);
#endif
        //FIXME:
        addObject(name.toStdString());
        e->acceptProposedAction();
    }
}

void MSystemManager::addObject(Ogre::String name)
{
    Ogre::ResourceGroupManager *rgm = Ogre::ResourceGroupManager::getSingletonPtr();
    rgm->addResourceLocation(name, "FileSystem", "General");

    //Update the name
    String meshName = name;
    meshName.substr(meshName.size()-5, 5);

    //Remove old object
    if(mainEnt != NULL)
    {
        mSceneManager->destroyEntity(mainEnt);
        mainEntAnim = 0;
    }
    if(mainNode != NULL)
        mSceneManager->destroySceneNode(mainNode->getName());

    //Add New Object
    mainEnt = mSceneManager->createEntity(meshName, name);
    mainNode = mSceneManager->getRootSceneNode()->createChildSceneNode(meshName+"node");
    mainNode->attachObject(mainEnt);
    mainNode->setPosition(Vector3(0, 0, 0));

    //Update the camera's pos to fit whith the object size
    mCurrCamera->setPosition(mainNode->getPosition().x, mainNode->getPosition().y, mainNode->getPosition().z - 200);
    mCurrCamera->lookAt(mainNode->getPosition());
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
