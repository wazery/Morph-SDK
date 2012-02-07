#include "button.h"
#include "ogrecanvas.h"
#include <QX11Info>
#include <iostream>

const QPoint     OgreCanvas::invalidMousePoint(-1, -1);
const Ogre::Real OgreCanvas::turboModifier(10);

OgreCanvas::OgreCanvas(QWidget *parent)
    :QWidget(parent),
      ogreRoot(0),
      ogreSceneManager(0),
      ogreRenderWindow(0),
      ogreViewport(0),
      ogreCamera(0),
      oldPos(invalidMousePoint),
      selectedNode(0)
{
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_PaintOnScreen);
	setAttribute(Qt::WA_InputMethodEnabled);
    setMinimumSize(240, 240);
    setFocusPolicy(Qt::ClickFocus);
}

OgreCanvas::~OgreCanvas()
{
    if(ogreRenderWindow)
    {
        ogreRenderWindow->removeAllViewports();
    }

    if(ogreRoot)
    {
        ogreRoot->detachRenderTarget(ogreRenderWindow);

        if(ogreSceneManager)
        {
            ogreRoot->destroySceneManager(ogreSceneManager);
        }
    }

    delete ogreRoot;
}

void OgreCanvas::setBackgroundColor(QColor c)
{
    if(ogreViewport)
    {
        Ogre::ColourValue ogreColour;
        ogreColour.setAsARGB(c.rgba());
        ogreViewport->setBackgroundColour(ogreColour);
    }
}

void OgreCanvas::setCameraPosition(const Ogre::Vector3 &pos)
{
    ogreCamera->setPosition(pos);
    ogreCamera->lookAt(0, 50, 0);
    update();
    emit cameraPositionChanged(pos);
}

void OgreCanvas::keyPressEvent(QKeyEvent *e)
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
    if(keyPressed != keyCoordModificationMapping.end() && ogreCamera)
    {
        const Ogre::Vector3 &actualCamPos = ogreCamera->getPosition();
        setCameraPosition(actualCamPos + keyPressed.value());

        e->accept();
    }
    else
    {
        e->ignore();
    }
}

void OgreCanvas::mouseDoubleClickEvent(QMouseEvent *e)
{
    if(e->buttons().testFlag(Qt::LeftButton))
    {
        Ogre::Real x = e->pos().x() / (float)width();
        Ogre::Real y = e->pos().y() / (float)height();

        Ogre::Ray ray = ogreCamera->getCameraToViewportRay(x, y);
        Ogre::RaySceneQuery *query = ogreSceneManager->createRayQuery(ray);
        Ogre::RaySceneQueryResult &queryResult = query->execute();
        Ogre::RaySceneQueryResult::iterator queryResultIterator = queryResult.begin();

        if(queryResultIterator != queryResult.end())
        {
            if(queryResultIterator->movable)
            {
				// when the object is double clicked..
				// replace the last line with whatever you want
                selectedNode = queryResultIterator->movable->getParentSceneNode();

               object_clicked(selectedNode->getAttachedObject(0)->getName() );

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

        ogreSceneManager->destroyQuery(query);

        update();
        e->accept();
    }
    else
    {
        e->ignore();
    }
}

void OgreCanvas::mouseMoveEvent(QMouseEvent *e)
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
        const Ogre::Vector3 &actualCamPos = ogreCamera->getPosition();
        setCameraPosition(actualCamPos + camTranslation);

        oldPos = pos;
        e->accept();
    }
    else
    {
        e->ignore();
    }
}

void OgreCanvas::mousePressEvent(QMouseEvent *e)
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

void OgreCanvas::mouseReleaseEvent(QMouseEvent *e)
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

void OgreCanvas::moveEvent(QMoveEvent *e)
{
    QWidget::moveEvent(e);

    if(e->isAccepted() && ogreRenderWindow)
    {
        ogreRenderWindow->windowMovedOrResized();
        update();
    }
}

QPaintEngine* OgreCanvas::paintEngine() const
{
    // I don't want another paint engine to get in the way for my Ogre based paint engine.
    // So this return nothing.
    return NULL;
}

void OgreCanvas::paintEvent(QPaintEvent *e)
{
	if(!ogreRoot)
	{
		initOgreSystem();
	}
    ogreRoot->_fireFrameStarted();
    ogreRenderWindow->update(true);
    ogreRoot->_fireFrameEnded();

    e->accept();
}

void OgreCanvas::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);

    if(e->isAccepted())
    {
        const QSize &newSize = e->size();
        if(ogreRenderWindow)
        {
            ogreRenderWindow->resize(newSize.width(), newSize.height());
            ogreRenderWindow->windowMovedOrResized();
        }
        if(ogreCamera)
        {
            Ogre::Real aspectRatio = Ogre::Real(newSize.width()) / Ogre::Real(newSize.height());
            ogreCamera->setAspectRatio(aspectRatio);
        }
    }
}

void OgreCanvas::wheelEvent(QWheelEvent *e)
{
    Ogre::Vector3 zTranslation(0,0, -e->delta() / 10);

    if(e->modifiers().testFlag(Qt::ControlModifier))
    {
        zTranslation.z *= turboModifier;
    }

    const Ogre::Vector3 &actualCamPos = ogreCamera->getPosition();
    setCameraPosition(actualCamPos + zTranslation);

    e->accept();
}

void OgreCanvas::initOgreSystem()
{
    ogreRoot = new Ogre::Root();
    //ogreRoot->showConfigDialog();
	Ogre::RenderSystem *renderSystem = ogreRoot->getRenderSystemByName("OpenGL Rendering Subsystem");
	ogreRoot->setRenderSystem(renderSystem);
	ogreRoot->getRenderSystem()->setConfigOption( "Full Screen", "No" );

    ogreRoot->initialise(false);

    ogreSceneManager = ogreRoot->createSceneManager(Ogre::ST_GENERIC);

    Ogre::NameValuePairList viewConfig;
    Ogre::String widgetHandle;
#ifdef Q_WS_WIN
    widgetHandle = Ogre::StringConverter::toString((size_t)((HWND)winId()));
#else
    QWidget *q_parent = dynamic_cast <QWidget *> (parent());
    QX11Info xInfo = x11Info();

    widgetHandle =
	        widgetHandle = Ogre::StringConverter::toString((unsigned long)(xInfo.display())) + ":"
	        + Ogre::StringConverter::toString((unsigned int)(xInfo.screen())) + ":"
	        + Ogre::StringConverter::toString((unsigned long)(parentWidget()->winId())) + ":";
#endif
    viewConfig["externalWindowHandle"] = widgetHandle;
    ogreRenderWindow = ogreRoot->createRenderWindow("Ogre rendering window",
                                                    width(), height(), false, &viewConfig);


    ogreCamera = ogreSceneManager->createCamera("myCamera");
    Ogre::Vector3 camPos(0, 0, 80);
    ogreCamera->setPosition(camPos);
    ogreCamera->lookAt(0, 0, -300);
	ogreCamera->setNearClipDistance(5);
    emit cameraPositionChanged(camPos);

    ogreViewport = ogreRenderWindow->addViewport(ogreCamera);
    ogreViewport->setBackgroundColour(Ogre::ColourValue(0.19, 0.19, 0.19));
    ogreCamera->setAspectRatio(Ogre::Real(ogreViewport->getActualWidth()) / Ogre::Real(ogreViewport->getActualHeight()));
    //-------------------------------------------------------------------------------------
    // Set default mipmap level (NB some APIs ignore this)
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

    setupNLoadResources();

    // FIXME: pass the object you want to it here..
	createScene();
}

void OgreCanvas::setupNLoadResources()
{
    Ogre::ResourceGroupManager *rgm = Ogre::ResourceGroupManager::getSingletonPtr();
    rgm->addResourceLocation("meshes/SdkTrays.zip", "Zip", "Bootstrap");
    rgm->addResourceLocation("meshes", "FileSystem", "General");
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void print(void){
    std::cout << "------------object clicked-------------" << std::endl;
}


void OgreCanvas::createScene()
{
	// This function usage is in line 303!

    ogreSceneManager->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
    // Create a light
    Ogre::Light* l = ogreSceneManager->createLight("MainLight");
    l->setPosition(20, 80, 50);

	// Replace this line with the object --> object = ogreSceneManager->createEntity("Head", "ogrehead.mesh");
	// and don't forgot to attach the object in the last line.
    Ogre::Entity* ogreHead = ogreSceneManager->createEntity("Head", "ogrehead.mesh");

    Button::CanvasObject obj(*ogreHead);
    Button n(obj);
    n.mClicked.connect(sigc::ptr_fun(print));

    Ogre::SceneNode* headNode = ogreSceneManager->getRootSceneNode()->createChildSceneNode();
    headNode->attachObject(ogreHead);
}

// Just testing the LogManager .. not yet fully implemented!
// ToDo: make a seperate sub-system for logging and output.
//Ogre::Log OgreCanvas::createLogManager()
//{
//    Ogre::LogManager* logmgr = new Ogre::LogManager;
//    Ogre::Log *log = Ogre::LogManager::getSingleton().createLog("mylog.log", true, true, false);
////    Ogre::Root *root = new Ogre::Root("", "");
//    return logmgr->getLog();
//}
