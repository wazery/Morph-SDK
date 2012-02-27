#ifndef OGRE_CANVAS_H
#define OGRE_CANVAS_H

#include <QtGui>
#include <Ogre.h>


class OgreCanvas : public QWidget
{
    Q_OBJECT

public:
    OgreCanvas(QWidget *parent = 0);
    ~OgreCanvas();

    // Override QWidget::paintEngine to return NULL
    QPaintEngine* paintEngine() const; // Turn off QTs paint engine for the Ogre widget.

public slots:
    void setBackgroundColor(QColor c);
    void setCameraPosition(const Ogre::Vector3 &pos);

signals:
    void cameraPositionChanged(const Ogre::Vector3 &pos);

protected:
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void moveEvent(QMoveEvent *e);
    virtual void mouseDoubleClickEvent(QMouseEvent *e);
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseReleaseEvent(QMouseEvent *e);
    virtual void paintEvent(QPaintEvent *e);
    virtual void resizeEvent(QResizeEvent *e);
    virtual void wheelEvent(QWheelEvent *e);

private:
    void initOgreSystem();
	void setupNLoadResources();
	void createScene();
    void createGridObjects();

private:
    static const Ogre::Real turboModifier;
    static const QPoint invalidMousePoint;

private:
    Ogre::Root          *ogreRoot;
    Ogre::SceneManager  *ogreSceneManager;
    Ogre::RenderWindow  *ogreRenderWindow;
    Ogre::Viewport      *ogreViewport;
    Ogre::Camera        *ogreCamera;
    Ogre::ManualObject  *mFloorGrid;
    Ogre::ManualObject  *mCircle;

    QPoint oldPos;
    Ogre::SceneNode *selectedNode;
};

#endif // OGRE_CANVAS_H
