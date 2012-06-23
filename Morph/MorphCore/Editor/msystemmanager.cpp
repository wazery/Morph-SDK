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

#include "msystemmanager.h"
#include "ui_msystemmanager.h"

#include "MLogManager.h"
#include "MNodeManager.h"
#include "mOgreEntityViewer/mogrelogproxy.h"
//#include "mOgreEntityViewer/textrenderer.h"

#include "mainwindow.h"

// TODO: Include all other sub-systems to manage them

using namespace Morph;

const QPoint     MSystemManager::invalidMousePoint(-1, -1);
//const Ogre::Real MSystemManager::turboModifier(10);

MSystemManager* MSystemManager::smInstance = NULL;

MSystemManager::MSystemManager(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::MSystemManager),
      mRoot(0),
    mRenderWindow(0),
    mWindowWidth(0),
    mWindowHeight(0),
    mSceneManager(0),
    selectedNode(NULL),
    mainEnt(0),
    mainEntAnim(0),
    mainNode(0),
    mainSubEnt(0),
    oldPos(invalidMousePoint)
{
    fogColor.setAsRGBA(qRgba(0, 0, 0, 1));
    mBackgroundColor.setAsARGB(QColor(30, 30, 30, 1).rgba());

    lightDiffuseColor.setAsRGBA(qRgba(0, 0, 0, 1));
    lightSpecularColor.setAsRGBA(qRgba(0, 0, 0, 1));
    ambientLightColor.setAsRGBA(qRgba(0, 0, 0, 1));

    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_InputMethodEnabled);
    setMinimumSize(240, 240);
    setFocusPolicy(Qt::WheelFocus);

    mRenderWindow = NULL;

    ui->setupUi(this);

    mVerticalLayout = new QVBoxLayout(this);
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

    Ogre::Root::getSingleton().removeFrameListener(this);

    for(int i = 0;i< mRenderWindowList.count() ;i++)
    {
        delete mRenderWindowList.takeAt(i);
    }

    delete ui;

    delete mRoot;
}

void MSystemManager::showEvent(QShowEvent *evt)
{
    if(!mRenderWindow)
    {
        initialise();
    }

    QWidget::showEvent(evt);
}

void MSystemManager::paintEvent(QPaintEvent *e)
{
//    if(!mRoot)
//    {
//        initialise();
//    }

//    mRoot->_fireFrameStarted();
//    mRenderWindow->update(true);
//    //TextRenderer::g;
//    mRoot->_fireFrameEnded();

//    e->accept();
}

void MSystemManager::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);

//    if(e->isAccepted())
//    {
//        const QSize &newSize = e->size();
//        if(mRenderWindow)
//        {
//            mRenderWindow->resize(newSize.width(), newSize.height());
//            mRenderWindow->windowMovedOrResized();
//        }
//        if(mCurrCamera)
//        {
//            Ogre::Real aspectRatio = Ogre::Real(newSize.width()) / Ogre::Real(newSize.height());
//            mCurrCamera->setAspectRatio(aspectRatio);
//        }
//    }
}

void MSystemManager::keyPress(QKeyEvent* e)
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
        }
    }
}

void MSystemManager::keyRelease(QKeyEvent* e)
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

void MSystemManager::mouseDoubleClick(QMouseEvent *e)
{
    if(e->buttons().testFlag(Qt::LeftButton))
    {
        Ogre::Real x = e->pos().x() / (float)width();
        Ogre::Real y = e->pos().y() / (float)height();
        Ogre::Ray ray;

        // Reset selected node.
        selectedNode = NULL;

        for(int i = 0; i < mRenderWindowList.count(); i++)
        {
            ray = mRenderWindowList[i]->getCamera()->getCameraToViewportRay(x, y);

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
                    if(selectedNode->getShowBoundingBox())
                        emit selectedNodeChanged(true);
                    else
                        emit selectedNodeChanged(false);
                    //button_object_clicked(selectedNode->getAttachedObject(0)->getName() );
                }
            }
            else
            {
                // when you double click on any other object..
                emit selectedNodeChanged(false);
                selectedNode = 0;
            }
            mSceneManager->destroyQuery(query);
            update();
            e->accept();
        }
    }
    else
    {
        e->ignore();
    }
}

void MSystemManager::mouseMove(QMouseEvent* e)
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
}

void MSystemManager::mousePress(QMouseEvent* e)
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

void MSystemManager::mouseRelease(QMouseEvent* e)
{
    Q_UNUSED(e);
    mouseLeftPressed = false;
    mouseRightPressed = false;
    mouseMiddleBtn = false;
}

void MSystemManager::wheel(QWheelEvent * e)
{
    mDirection.z = -e->delta()/12;
    update();
    mDirection.z = 0;
}

void MSystemManager::update()
{
    if(mRenderWindow != NULL)
    {
        for(int i = 0; i < mRenderWindowList.count(); i++)
        {
            if(mRenderWindowList[i]->getCamera())
            {
                mRenderWindowList[i]->getCamera()->moveRelative(mDirection);
                mRenderWindowList[i]->getCamera()->yaw(Radian(angleX));
                mRenderWindowList[i]->getCamera()->pitch(Radian(angleY));
            }
            if(mRenderWindowList[i]->isInitialised() && !mRenderWindowList[i]->hasGrid)
                createGrid(mRenderWindowList[i], i);
            mRenderWindowList[i]->repaint();
        }
        //updateStats();
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

#ifdef Q_OS_WIN
    widgetHandle = Ogre::StringConverter::toString((size_t)((HWND)winId()));
#else
    QX11Info info = x11Info();
    widgetHandle  = Ogre::StringConverter::toString((unsigned long)(info.display()));
    widgetHandle += ":";
    widgetHandle += Ogre::StringConverter::toString((unsigned int)(info.screen()));
    widgetHandle += ":";
    widgetHandle += Ogre::StringConverter::toString((unsigned long)(parentWidget()->winId()));
#endif
    viewConfig["parentWindowHandle"] = widgetHandle;
    mRenderWindow = mRoot->createRenderWindow("ViewHIDDEN", 1, 1, false, &viewConfig);
    mIsInitialised = true;
    initOgreCore();

    Ogre::Root::getSingleton().addFrameListener(this);

    MNodeManager::getSingleton().initialise();
    emit initialised();

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

bool MSystemManager::initOgreCore()
{
    // Setup animation default
    Ogre::Animation::setDefaultInterpolationMode(Ogre::Animation::IM_LINEAR);
    Ogre::Animation::setDefaultRotationInterpolationMode(Ogre::Animation::RIM_LINEAR);

    addResourceLocations();
    initResources();
    MLogManager::getSingleton().logOutput("Initialised all resources", M_EDITOR_MESSAGE);
    createScene();
    MLogManager::getSingleton().logOutput("Scene created", M_EDITOR_MESSAGE);
    //createLight();
    //MLogManager::getSingleton().logOutput("Added light", M_EDITOR_MESSAGE);

    TextureManager::getSingleton().setDefaultNumMipmaps(5);
    MaterialManager::getSingleton().setDefaultTextureFiltering(Ogre::TFO_ANISOTROPIC);
    MaterialManager::getSingleton().setDefaultAnisotropy(2);

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
            ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
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
    Ogre::Light* lightSource = mSceneManager->createLight("Main Light Source");
    lightSource->setPosition(Ogre::Vector3(20, 80, 50));

    addObject("ogrehead.mesh");
}

void MSystemManager::createLight()
{
    mSceneManager->setAmbientLight(ColourValue(1, 0, 0));
    mSceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
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

void MSystemManager::createGrid(MOgreCanvas* renderWindowList, int index)
{
    mGridList.append(new ViewportGrid(mSceneManager, renderWindowList->getViewport()));

    QString settingsFile = QApplication::applicationDirPath() + "editorSettings";
    QSettings* settings = new QSettings(settingsFile, QSettings::NativeFormat);

    Ogre::ColourValue ogreColor;
    ogreColor.setAsARGB(QColor(settings->value("Grid/gridColor").toString()).rgba());
    mGridList[index]->setColour(ogreColor);
    mGridList[index]->setPerspectiveSize(settings->value("Grid/gridPrespectiveSize").toInt());

    if(settings->value("Grid/gridRenderLayer").toInt() == 0)
        mGridList[index]->setRenderLayer(ViewportGrid::RL_BEHIND);
    else
        mGridList[index]->setRenderLayer(ViewportGrid::RL_INFRONT);

    renderWindowList->hasGrid = true;
    mGridList[index]->setEnabled(settings->value("Grid/grid").toBool());
    mGridList[index]->setDivision(30);
}

void MSystemManager::gridChanged(bool value)
{
    for(int i = 0; i < mGridList.count(); i++)
    {
        mGridList[i]->setEnabled(value);
    }
    update();
}

void MSystemManager::changeZoomValue(Ogre::Vector3 pos)
{
    Ogre::Vector3 vector;
    for(int i = 0; i < mRenderWindowList.count(); i++)
    {
        vector = mRenderWindowList[i]->getCamera()->getPosition();
        mRenderWindowList[i]->getCamera()->setPosition(vector.x, vector.y, pos.z);
        mRenderWindowList[i]->update();
    }
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
    mBackgroundColor = ogreColor;
    for(int i = 0; i < mRenderWindowList.count(); i++)
    {
        mRenderWindowList[i]->getViewport()->setBackgroundColour(ogreColor);
        mRenderWindowList[i]->repaint();
    }
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
    mSceneManager->setAmbientLight(Ogre::ColourValue(color.redF(), color.greenF(), color.blueF(), color.alphaF()));
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

void MSystemManager::setFog(int fogType)
{
    switch(fogType)
    {
        case 0:
            mSceneManager->setFog(FOG_NONE);
            break;
        case 1:
            mSceneManager->setFog(FOG_LINEAR, fogColor, 0.0, 50, 500);
            break;
        case 2:
            mSceneManager->setFog(FOG_EXP, fogColor, 0.005);
            break;
        case 3:
            mSceneManager->setFog(FOG_EXP2, fogColor, 0.003);
            break;
    }
}

void MSystemManager::setFogColor(QColor color)
{
    fogOldColor = color;
    fogColor.setAsARGB(color.rgba());
    if(mSceneManager->getFogMode() == FOG_LINEAR)
        mSceneManager->setFog(FOG_LINEAR, fogColor, mSceneManager->getFogDensity(), mSceneManager->getFogStart(), mSceneManager->getFogEnd());
    else if(mSceneManager->getFogMode() == FOG_EXP)
        mSceneManager->setFog(FOG_EXP, fogColor, mSceneManager->getFogDensity());
    else if(mSceneManager->getFogMode() == FOG_EXP2)
        mSceneManager->setFog(FOG_EXP2, fogColor, mSceneManager->getFogDensity());
}

QColor MSystemManager::getFogColor()
{
    return fogOldColor;
}

Ogre::Entity* MSystemManager::getMainEntity()
{
    return mainEnt;
}

void MSystemManager::updateMaterial()
{
    for(unsigned int i=0; i<mainEnt->getNumSubEntities(); ++i)
    {
        mainSubEnt = mainEnt->getSubEntity(i);
        mainSubEnt->getMaterial()->reload();
    }
}

void MSystemManager::setAnimationState(Ogre::String name)
{
    if(mainEntAnim != NULL){
        mainEntAnim->setLoop(false);
        mainEntAnim->setEnabled(false);
    }
    mainEntAnim = mainEnt->getAnimationState(name);
    mainEntAnim->setLoop(false);
    if(isLoopOn)
        mainEntAnim->setLoop(true);
    if(isAnimEnabled)
        mainEntAnim->setEnabled(true);
}

void MSystemManager::setAnimLoop(bool enable)
{
    mainEntAnim->setLoop(enable);
    isLoopOn = enable;
}

void MSystemManager::setAnimEnabled(bool enable)
{
    mainEntAnim->setEnabled(enable);
    isAnimEnabled = enable;
}

void MSystemManager::createPointLight(Ogre::String name, String xPos, String yPos, String zPos, String diffuse, String specular)
{
    Light* newLight = mSceneManager->createLight(name);
    newLight->setPosition(Ogre::StringConverter::parseReal(xPos), StringConverter::parseReal(yPos), StringConverter::parseReal(zPos));

    QColor diffuseColor(diffuse.c_str());
    QColor specularColor(specular.c_str());
    lightDiffuseColor.setAsRGBA(diffuseColor.rgba());
    lightSpecularColor.setAsRGBA(specularColor.rgba());
    diffuseOldColor = diffuseColor;
    specularOldColor = specularColor;
    newLight->setDiffuseColour(diffuseColor.redF(), diffuseColor.greenF(), diffuseColor.blueF());
    newLight->setSpecularColour(specularColor.redF(), specularColor.greenF(), specularColor.blueF());
}

void MSystemManager::createDirectionalLight(Ogre::String name, String xDir, String yDir, String zDir, String diffuse, String specular)
{
    Light* newLight = mSceneManager->createLight(name);
    newLight->setDirection(Ogre::StringConverter::parseReal(xDir), StringConverter::parseReal(yDir), StringConverter::parseReal(zDir));

    QColor diffuseColor(diffuse.c_str());
    QColor specularColor(specular.c_str());
    lightDiffuseColor.setAsRGBA(diffuseColor.rgba());
    lightSpecularColor.setAsRGBA(specularColor.rgba());
    diffuseOldColor = diffuseColor;
    specularOldColor = specularColor;
    newLight->setDiffuseColour(diffuseColor.redF(), diffuseColor.greenF(), diffuseColor.blueF());
    newLight->setSpecularColour(specularColor.redF(), specularColor.greenF(), specularColor.blueF());
}

void MSystemManager::createSpotlight(Ogre::String name, String xPos, String yPos, String zPos, String xDir, String yDir, String zDir, String diffuse, String specular)
{
    Light* newLight = mSceneManager->createLight(name);
    newLight->setPosition(Ogre::StringConverter::parseReal(xPos), StringConverter::parseReal(yPos), StringConverter::parseReal(zPos));
    newLight->setDirection(Ogre::StringConverter::parseReal(xDir), StringConverter::parseReal(yDir), StringConverter::parseReal(zDir));

    QColor diffuseColor(diffuse.c_str());
    QColor specularColor(specular.c_str());
    lightDiffuseColor.setAsRGBA(diffuseColor.rgba());
    lightSpecularColor.setAsRGBA(specularColor.rgba());
    diffuseOldColor = diffuseColor;
    specularOldColor = specularColor;
    newLight->setDiffuseColour(diffuseColor.redF(), diffuseColor.greenF(), diffuseColor.blueF());
    newLight->setSpecularColour(specularColor.redF(), specularColor.greenF(), specularColor.blueF());
}

void MSystemManager::updatePointLight(Ogre::String oldName, String name, String xPos, String yPos, String zPos, String diffuse, String specular)
{
    Light* newLight = NULL;
    if(oldName != "none"){//name has changed
        mSceneManager->destroyLight(oldName);
        newLight = mSceneManager->createLight(name);
    }
    else
        newLight = mSceneManager->getLight(name);

    newLight->setPosition(Ogre::StringConverter::parseReal(xPos), StringConverter::parseReal(yPos), StringConverter::parseReal(zPos));

    QColor diffuseColor(diffuse.c_str());
    QColor specularColor(specular.c_str());
    lightDiffuseColor.setAsRGBA(diffuseColor.rgba());
    lightSpecularColor.setAsRGBA(specularColor.rgba());
    diffuseOldColor = diffuseColor;
    specularOldColor = specularColor;
    newLight->setDiffuseColour(diffuseColor.redF(), diffuseColor.greenF(), diffuseColor.blueF());
    newLight->setSpecularColour(specularColor.redF(), specularColor.greenF(), specularColor.blueF());
}

void MSystemManager::updateDirectionalLight(Ogre::String oldName, String name, String xDir, String yDir, String zDir, String diffuse, String specular)
{
    Light* newLight = NULL;
    if(oldName != "none"){//name has changed
        mSceneManager->destroyLight(oldName);
        newLight = mSceneManager->createLight(name);
    }
    else
        newLight = mSceneManager->getLight(name);

    newLight->setDirection(Ogre::StringConverter::parseReal(xDir), StringConverter::parseReal(yDir), StringConverter::parseReal(zDir));

    QColor diffuseColor(diffuse.c_str());
    QColor specularColor(specular.c_str());
    lightDiffuseColor.setAsRGBA(diffuseColor.rgba());
    lightSpecularColor.setAsRGBA(specularColor.rgba());
    diffuseOldColor = diffuseColor;
    specularOldColor = specularColor;
    newLight->setDiffuseColour(diffuseColor.redF(), diffuseColor.greenF(), diffuseColor.blueF());
    newLight->setSpecularColour(specularColor.redF(), specularColor.greenF(), specularColor.blueF());
}

void MSystemManager::updateSpotlight(Ogre::String oldName, String name, String xPos, String yPos, String zPos, String xDir, String yDir, String zDir, String diffuse, String specular)
{
    Light* newLight = NULL;
    if(oldName != "none"){//name has changed
        mSceneManager->destroyLight(oldName);
        newLight = mSceneManager->createLight(name);
    }
    else
        newLight = mSceneManager->getLight(name);

    newLight->setPosition(Ogre::StringConverter::parseReal(xPos), StringConverter::parseReal(yPos), StringConverter::parseReal(zPos));
    newLight->setDirection(Ogre::StringConverter::parseReal(xDir), StringConverter::parseReal(yDir), StringConverter::parseReal(zDir));

    QColor diffuseColor(diffuse.c_str());
    QColor specularColor(specular.c_str());
    lightDiffuseColor.setAsRGBA(diffuseColor.rgba());
    lightSpecularColor.setAsRGBA(specularColor.rgba());
    diffuseOldColor = diffuseColor;
    specularOldColor = specularColor;
    newLight->setDiffuseColour(diffuseColor.redF(), diffuseColor.greenF(), diffuseColor.blueF());
    newLight->setSpecularColour(specularColor.redF(), specularColor.greenF(), specularColor.blueF());
}

void MSystemManager::deleteLight(Ogre::String name)
{
    mSceneManager->destroyLight(name);
}

void MSystemManager::setViewNum(int num)
{
    for(int i = 0;i<mRenderWindowList.count();i++)
    {
        delete mGridList.takeAt(i);
        delete mRenderWindowList.takeAt(i);
        i--;
    }

    for(int i = 0; i<mVerticalLayout->count();i++)
    {
        delete mVerticalLayout->takeAt(i);
        i--;
    }

     if(num == 1)
     {
         QSplitter *Splitter = new QSplitter(this);
         Splitter->setStyleSheet("QSplitter  { border-color: rgb(77, 77, 77); color: rgb(0, 255, 0);  height: 1px; background-color: rgb(45, 45, 45); }");
         Splitter->setOrientation(Qt::Vertical);
         mVerticalLayout->addWidget(Splitter);

         MOgreCanvas *orw = new MOgreCanvas(QString("View0"), mSceneManager, Ogre::PT_PERSPECTIVE, MOgreCanvas::CP_FREE, mBackgroundColor, Splitter);
         mRenderWindowList.append(orw);
         Splitter->addWidget(orw);
     }

    if(num == 4)
    {
        QSplitter *Splitter = new QSplitter(this);
        Splitter->setStyleSheet("QSplitter  { border-color: rgb(77, 77, 77); color: blue;  height: 1px; background-color: rgb(45, 45, 45); }");
        Splitter->setOrientation(Qt::Vertical);

        QSplitter *Splitter2 = new QSplitter(Splitter);
        Splitter2->setStyleSheet("QSplitter  { border-color: rgb(77, 77, 77); color: blue;  height: 1px; background-color: rgb(45, 45, 45); }");
        Splitter2->setOrientation(Qt::Horizontal);
        Splitter->addWidget(Splitter2);

        QSplitter *Splitter3 = new QSplitter(Splitter);
        Splitter3->setStyleSheet("QSplitter  { border-color: redrgb(77, 77, 77); color: blue;  height: 1px; background-color: rgb(45, 45, 45); }");
        Splitter3->setOrientation(Qt::Horizontal);
        Splitter->addWidget(Splitter3);

        mVerticalLayout->addWidget(Splitter);

        MOgreCanvas *orw = new MOgreCanvas(QString("View1"), mSceneManager, Ogre::PT_ORTHOGRAPHIC, MOgreCanvas::CP_FRONT, mBackgroundColor, Splitter2);
        mRenderWindowList.append(orw);
        Splitter2->addWidget(orw);

        orw = new MOgreCanvas(QString("View2"), mSceneManager, Ogre::PT_ORTHOGRAPHIC, MOgreCanvas::CP_LEFT, mBackgroundColor, Splitter2);
        mRenderWindowList.append(orw);
        Splitter2->addWidget(orw);

        orw = new MOgreCanvas(QString("View3"), mSceneManager, Ogre::PT_ORTHOGRAPHIC, MOgreCanvas::CP_TOP, mBackgroundColor, Splitter3);
        mRenderWindowList.append(orw);
        Splitter3->addWidget(orw);

        orw = new MOgreCanvas(QString("View4"), mSceneManager, Ogre::PT_PERSPECTIVE, MOgreCanvas::CP_FREE, mBackgroundColor, Splitter3);
        mRenderWindowList.append(orw);
        Splitter3->addWidget(orw);
    }

    for(int i = 0;i<mRenderWindowList.count();i++)
    {
        connect(mRenderWindowList[i],SIGNAL(keyPress(QKeyEvent*)),this,SLOT(keyPress(QKeyEvent*)));
        connect(mRenderWindowList[i],SIGNAL(keyRelease(QKeyEvent*)),this,SLOT(keyRelease(QKeyEvent*)));
        connect(mRenderWindowList[i],SIGNAL(mousePress(QMouseEvent*)),this,SLOT(mousePress(QMouseEvent*)));
        connect(mRenderWindowList[i],SIGNAL(mouseRelease(QMouseEvent*)),this,SLOT(mouseRelease(QMouseEvent*)));
        connect(mRenderWindowList[i],SIGNAL(mouseMove(QMouseEvent*)),this,SLOT(mouseMove(QMouseEvent*)));
        connect(mRenderWindowList[i],SIGNAL(wheel(QWheelEvent*)),this,SLOT(wheel(QWheelEvent*)));
        connect(mRenderWindowList[i],SIGNAL(mouseDoubleClick(QMouseEvent*)),this,SLOT(mouseDoubleClick(QMouseEvent*)));
        connect(mRenderWindowList[i],SIGNAL(initialised()),this,SLOT(update()));
    }
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
    else
        QMessageBox::warning(parentWidget(), "You can't add files with this type", "Please add file of type .mesh");
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
        addObject(name.toStdString());
        e->acceptProposedAction();
    }
}

void MSystemManager::addObject(Ogre::String name)
{
    Ogre::ResourceGroupManager *rgm = Ogre::ResourceGroupManager::getSingletonPtr();
    rgm->addResourceLocation(name, "FileSystem", "General");

    //FIXME: Re implement the naming mechanism.
    Ogre::String basename, path;
    Ogre::StringUtil::splitFilename(name, basename, path);
    String meshName = basename;
    meshName.substr(meshName.size()-5, 5);

    //Remove old object
    //if(mainEnt != NULL)
    //{
    //    mSceneManager->destroyEntity(mainEnt);
    //    mainEntAnim = 0;
    //}
    //if(mainNode != NULL)
    //    mSceneManager->destroySceneNode(mainNode->getName());

    //Add New Object
    mainEnt = mSceneManager->createEntity(meshName, name);
    mainNode = mSceneManager->getRootSceneNode()->createChildSceneNode(meshName+"node");

    MString parentChainName = "World." + MString(meshName.c_str());
    MString nodeName = MString(meshName.c_str()) + "node";

    //MString parentChainName = "World." + MString("sometext");
    //MString nodeName = MString("lklkl") + "node";

    MNodeManager::getSingleton().notifyAddNode(parentChainName, nodeName);

    mainNode->attachObject(mainEnt);
    mainNode->setPosition(Vector3(0, 0, 0));
    update();

    //Update the camera's pos to fit whith the object size
    //mCurrCamera->setPosition(mainNode->getPosition().x, mainNode->getPosition().y, mainNode->getPosition().z - 200);
    //mCurrCamera->lookAt(mainNode->getPosition());
}

void MSystemManager::removeObject(Ogre::String name)
{
    if(mSceneManager)
    {
        mSceneManager->destroyEntity(name);
        mSceneManager->destroySceneNode(name);
    }
    update();
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
