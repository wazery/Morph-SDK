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

// FIXME: Use Ogre singleton implementation untill
// implementing one for the editor core
//#include <OgreSingleton.h>
#include <OGRE/Ogre.h>

//#include "MSingleton.h" // FIXME: Implement this header file.

using namespace Ogre;

namespace Morph
{
    /** @class*/
    class MSystemManager : public QWidget
    {
        Q_OBJECT

    public:
        /** Default constructor */
        MSystemManager(QWidget *parent = 0);

        /** Finaliser */
        ~MSystemManager();

        // Override QWidget::paintEngine to return NULL
        QPaintEngine* paintEngine() const; // Turn off QTs paint engine for the Ogre widget.

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

        /** Access the MainCamera */
        Ogre::Camera* getMainCamera(void) const    { /** @return mMainCamera */ return(mMainCamera); }

        /** Access the CurrentCamera */
        Ogre::Camera* getCurrCamera(void) const    { /** @return mCurrCamera */ return(mCurrCamera); }

        /** Access the mIsInitialised */
        bool isInitialised(void) const    { /** @return mIsInitialised */ return(mIsInitialised);}

        /** Access the RenderWindow */
        Ogre::RenderWindow* getRenderWindow() const    { /** @return mRenderWindow */ return(mRenderWindow);}

        /** Access the WindowWidth */
        int getWindowWidth(void) const    { /** @return mWindowWidth */ return(mWindowWidth); }

        /** Access the WindowHeight */
        int getWindowHeight(void) const    { /** @return mWindowHeight */ return(mWindowHeight); }

    public slots:
        /** Sets the viewport background */
        //void setBackgroundColour(QColor c);
        /** Sets the current camera position */
        void setCameraPosition(const Ogre::Vector3 &pos);

    signals:
        void cameraPositionChanged(const Ogre::Vector3 &pos);

    protected:
        virtual void paintEvent(QPaintEvent *e);
        virtual void resizeEvent(QResizeEvent *e);
        virtual void keyPressEvent(QKeyEvent *e);
        virtual void moveEvent(QMoveEvent *e);
        virtual void mouseDoubleClickEvent(QMouseEvent *e);
        virtual void mouseMoveEvent(QMouseEvent *e);
        virtual void mousePressEvent(QMouseEvent *e);
        virtual void mouseReleaseEvent(QMouseEvent *e);
        virtual void wheelEvent(QWheelEvent *e);

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
        bool initOgreCore(Ogre::Real width, Ogre::Real height);

        /** Shut Down Ogre System */
        void shutDown();

        /** Creates the entire scene
            @remarks
                It can be overriden, as it is a pure virtual.
        */
        void createScene();

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

        // TODO: check if this function is logical
        void addViewport(Ogre::Camera camera);

        /** Create the grid for the canvas */
        void createGrid();

    public:
        //static MSystemManager* smInstance;

//        /** Get the class address pointer */
//        static MSystemManager* getSingletonPtr();

//        static MSystemManager &getSingleton();

//        static void releaseSingleton();

    private:
        static const Ogre::Real turboModifier;
        static const QPoint invalidMousePoint;

    protected:
        Ogre::Root          *mRoot;
        Ogre::SceneManager  *mSceneManager;
        Ogre::RenderWindow  *mRenderWindow;
        Ogre::Viewport      *mViewport;
        Ogre::Overlay       *mDebugOverlay; // TODO: change its name

        Ogre::ManualObject  *mFloorGrid;
        Ogre::ManualObject  *mCircle;

        Ogre::Camera        *mMainCamera;
        Ogre::Camera        *mCurrCamera;

        QPoint oldPos;
        Ogre::SceneNode *selectedNode;

        bool		mIsInitialised;
        int			mWindowWidth;
        int			mWindowHeight;
    };

    //MSystemManager* MSystemManager::smInstance = NULL;
}
#endif // MSYSTEMMANAGER_H
