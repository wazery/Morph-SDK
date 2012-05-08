#ifndef MOGRECANVAS_H
#define MOGRECANVAS_H

#include <QWidget>
#include <QPaintEngine>
#include <QPaintEvent>
#include <QResizeEvent>

#include <OGRE/Ogre.h>

#include "mlogmanager.h"
#include "mOgreEntityViewer/viewgrid.h"

using namespace Ogre;

// Similar to QOgreRenderWindow
class MOgreCanvas : public QWidget
{
    Q_OBJECT
public:
    enum CameraPositions
    {
        CP_FRONT = 0x0,
        CP_BACK = 0x1,
        CP_LEFT = 0x2,
        CP_RIGHT = 0x3,
        CP_TOP = 0x4,
        CP_BOTTOM = 0x5,
        CP_FREE = 0x6
    };
    MOgreCanvas(QString windowName, Ogre::SceneManager* sceneMgr, Ogre::ProjectionType projectionType, CameraPositions cameraPositions, Ogre::ColourValue backgorundColor, QWidget *parent = 0);
    ~MOgreCanvas();

    void setPolygonMode(Ogre::PolygonMode pm);
    Ogre::PolygonMode getPolygonMode();

    void setViewMode(CameraPositions cp);
    CameraPositions getViewMode() { return mCameraPositions; }

    void setProjectionType(Ogre::ProjectionType pt);
    Ogre::ProjectionType getProjectionType() { return mProjectionType;}

    void setBackgroundColor(Ogre::ColourValue color) { mVp->setBackgroundColour(color); }
    Ogre::ColourValue getBackgroundColor() { return mVp->getBackgroundColour(); }

    Ogre::Viewport* getViewport() { return mVp; }

    Ogre::Camera* getCamera() { return mCamera; }

    bool isInitialised() { return mIsInitialised; }

    bool hasGrid;

private:
    QString mWindowName;
    Ogre::SceneManager* mSceneMgr;
    Ogre::RenderWindow* mRenderWindow;
    Ogre::Camera *mCamera;
    Ogre::ColourValue mBackgroundColor;
    Ogre::SceneNode *mCameraPivotNode;
    bool mIsInitialised;
    Ogre::Viewport* mVp;
    Ogre::Vector2 mousePressStartPoint;
    Ogre::Vector2 mousePressEndPoint;

    void init();
    void createOrbitalCamera();

    CameraPositions mCameraPositions;
    Ogre::ProjectionType mProjectionType;

protected:
    virtual QPaintEngine* paintEngine() const { return 0; } // Turn off Qts paint engine for the Ogre widget.
    virtual void paintEvent(QPaintEvent *e);
    virtual void resizeEvent(QResizeEvent *e);
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void keyReleaseEvent(QKeyEvent* e);
    //virtual void moveEvent(QMoveEvent *e);
    virtual void mouseDoubleClickEvent(QMouseEvent *e);
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseReleaseEvent(QMouseEvent *e);
    virtual void wheelEvent(QWheelEvent *e);
    //virtual void dragEnterEvent(QDragEnterEvent* e);
    //virtual void dropEvent(QDropEvent* e);

signals:
    void keyPress(QKeyEvent* e);
    void keyRelease(QKeyEvent* e);
    void mousePress(QMouseEvent* e);
    void mouseRelease(QMouseEvent* e);
    void mouseMove(QMouseEvent* e);
    void wheel(QWheelEvent* e);
    void mouseDoubleClick(QMouseEvent* e);
    void initialised();
};
#endif // MOGRECANVAS_H
