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

#ifndef MSYSTEMMANAGER_H
#define MSYSTEMMANAGER_H

#include <QtGui>

#include <OGRE/Ogre.h>

#include "mogrecanvas.h"

#include "mOgreEntityViewer/viewgrid.h"

//#include "MSingleton.h" // FIXME: Implement this header file.

using namespace Ogre;

namespace Ui {
    class MSystemManager;
}

namespace Morph
{
    /** @class*/
    class MSystemManager : public QWidget, public Ogre::FrameListener
    {
        Q_OBJECT

    public:
        /** Default constructor */
        MSystemManager(QWidget *parent = 0);

        /** Finaliser */
        ~MSystemManager();

        // Override QWidget::paintEngine to return NULL
        QPaintEngine* paintEngine() const { return NULL; } // Turn off QTs paint engine for the Ogre widget.

        /** Initialise Ogre System
            @remarks
                Create a render window. This window should be the current
                ChildView window using the externalWindowHandle value pair option.
            @param windowName QString identifying the name of the parent window.
            @param width int containing the width of the Ogre Canvas.
            @param height int containing the height of the Ogre Canvas.
            @param params NameValuePairList Name / value parameter pair (first = name, second = value).
            @param pRoot Root pointer to the Ogre root.
        */
        bool initialise();

        /** Rendring the canvas */
        void doRender();

        /** Access the Root */
        Ogre::Root* getRoot(void) const    { /** @return mRoot */ return(mRoot); }

        /** Access the SceneManager */
        Ogre::SceneManager* getSceneManager(void) const    { /** @return mSceneManager */ return(mSceneManager); }

        /** Access the mIsInitialised */
        bool isInitialised(void) const    { /** @return mIsInitialised */ return(mIsInitialised);}

        /** Access the RenderWindow */
        Ogre::RenderWindow* getRenderWindow() const    { /** @return mRenderWindow */ return(mRenderWindow);}

        /** Access the WindowWidth */
        int getWindowWidth(void) const    { /** @return mWindowWidth */ return(mWindowWidth); }

        /** Access the WindowHeight */
        int getWindowHeight(void) const    { /** @return mWindowHeight */ return(mWindowHeight); }

        void setBackgroundColor(QColor);

        /** Access the background color */
        QColor getBackgroundColor() const { return QColor(mBackgroundColor.getAsRGBA()); }

        /** Access the canvas windows */
        QList<MOgreCanvas*> getOgreWindows() { return mRenderWindowList; }

        void update();
        void updateAnim();

        void setBoundingBoxes(int value);
        void setSkeleton(int value);

        void setShadow(int fogType);
        void setAmbientLight(QColor color);
        QColor getAmbientLight();
        void setDiffuseColor(QColor color);
        QColor getDiffuseColor();
        void setSpecularColor(QColor color);
        QColor getSpecularColor();

        void updateMaterial();

        void createPointLight(String name, String xPos, String yPos, String zPos, String diffuse, String specular);
        void createDirectionalLight(String name, String xDir, String yDir, String zDir, String diffuse, String specular);
        void createSpotlight(String name, String xPos, String yPos, String zPos, String xDir, String yDir, String zDir, String diffuse, String specular);

        void updatePointLight(String oldName, String name, String xPos, String yPos, String zPos, String diffuse, String specular);
        void updateDirectionalLight(String oldName, String name, String xDir, String yDir, String zDir, String diffuse, String specular);
        void updateSpotlight(String oldName, String name, String xPos, String yPos, String zPos, String xDir, String yDir, String zDir, String diffuse, String specular);
        void deleteLight(String name);

        void addObject(Ogre::String name);
        void removeObject(Ogre::String name);

        //Entity
        Ogre::SceneNode* mainNode;
        Ogre::Entity*    mainEnt;
        Ogre::SubEntity* mainSubEnt;

    public slots:
        /** Sets the number of active viewports */
        void setViewNum(int num);

    signals:
        void initialised();

    public slots:
        void keyPress(QKeyEvent* e);
        void keyRelease(QKeyEvent* e);
        void mousePress(QMouseEvent* e);
        void mouseRelease(QMouseEvent* e);
        void mouseMove(QMouseEvent* e);
        void mouseDoubleClick(QMouseEvent *e);
        void wheel(QWheelEvent * e);

    protected:
        virtual void showEvent(QShowEvent *e);
        void moveEvent(QMoveEvent *e);
        void paintEvent(QPaintEvent *e);
        void resizeEvent(QResizeEvent *e);
        void dragEnterEvent(QDragEnterEvent* e);
        void dropEvent(QDropEvent* e);

    protected:
         /** Initialise Ogre Core
            @remarks
                Create a render window. This window should be the current
                childView window using the externalWindowHandle value pair option.
            @param windowName Ogre::String identifying the name of the parent window.
            @param width int containing the width of the Ogre Canvas.
            @param height int containing the height of the Ogre Canvas.
            @param params NameValuePairList Name / value parameter pair (first = name, second = value).
        */
        bool initOgreCore();

        /** Shut Down Ogre System */
        void shutDown();

        /** Creates the entire scene
            @remarks
                It can be overriden, as it is a pure virtual.
        */
        void createScene();
        void createLight();

        /** Destroys the entire scene */
        void destroyScene();

        // FIXME: This function has no implementation. May be later implemented for the loading
        // resources progress bar in the editor view
        //void createResourceListener();
        void createFrameListener();

        /** Setup paths to all resources */
        void addResourceLocations();

        /** Setup the resources for Ogre */
        void initResources();

        void updateStats(void);

        // FrameListener overrides
        virtual bool frameStarted(const FrameEvent& evt);
        virtual bool frameEnded(const FrameEvent& evt);

        /** Create the grid for the canvas */
        void createGrid();

    public:
        static MSystemManager* smInstance;
        QList<ViewportGrid*> mGridList;
        QList<MOgreCanvas*> mRenderWindowList;
        Ogre::Viewport* mOgreViewport;

        /** Get the class address pointer */
        static MSystemManager* getSingletonPtr();

        static MSystemManager &getSingleton();

        static void releaseSingleton();

    private:
        Ui::MSystemManager* ui;
        //static const Ogre::Real turboModifier;
        static const QPoint invalidMousePoint;

        QVBoxLayout *mVerticalLayout;
        Ogre::ColourValue mBackgroundColor;

    protected:
        Ogre::Root          *mRoot;
        Ogre::SceneManager  *mSceneManager;
        Ogre::RenderWindow  *mRenderWindow;

        Ogre::Overlay       *mDebugOverlay; // TODO: change its name

        Ogre::AnimationState* mainEntAnim;

        QPoint oldPos;
        Ogre::SceneNode *selectedNode;

        //Deplacement
        Ogre::Vector3 mDirection;
        Ogre::Real mRotate;
        Ogre::Real mMove;
        bool isMoving;
        QPoint mousePressPos;
        QPoint mousePos;
        float angleX, angleY;
        float rotX, rotY;

        //Light
        Ogre::Light* mainLight;
        Ogre::ColourValue lightDiffuseColor;
        Ogre::ColourValue lightSpecularColor;
        Ogre::ColourValue ambientLightColor;
        QColor ambientOldColor;
        QColor diffuseOldColor;
        QColor specularOldColor;

        bool mouseLeftPressed;
        bool mouseRightPressed;
        bool mouseMiddleBtn;
        bool isLoopOn;
        bool isAnimEnabled;

        bool mIsInitialised;
        int	 mWindowWidth;
        int	 mWindowHeight;
    };
}
#endif // MSYSTEMMANAGER_H
