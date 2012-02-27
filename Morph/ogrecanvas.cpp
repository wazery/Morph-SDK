#include "button.h"
#include "MEvent.h"
#include "ogrecanvas.h"
#include <QX11Info>
#include <iostream>
#include "MorphCore/Editor/MLogManager.h"
#include "mOgreEntityViewer/mogrelogproxy.h"

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

//Total number of lines in one dimension will be FLOOR_LINE_NUM*2 + 1
#define FLOOR_LINE_NUM 3
//Units of space between lines
#define FLOOR_LINE_SPACE 80

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

				button_object_clicked(selectedNode->getAttachedObject(0)->getName() );

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

    MOgreLogProxy* log = new MOgreLogProxy();
    Ogre::LogManager::getSingleton().getDefaultLog()->addListener(log);

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
    //QWidget *q_parent = dynamic_cast <QWidget *> (parent());
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
    ogreViewport->setBackgroundColour(Ogre::ColourValue(0.117647059, 0.117647059, 0.117647059));
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

void print(void)
{
    MLogManager::getSingleton().logOutput("------------object clicked-------------");
}


void OgreCanvas::createScene()
{
    ogreSceneManager->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
    // Create a light
    Ogre::Light* l = ogreSceneManager->createLight("MainLight");
    l->setPosition(20, 80, 50);

	// Replace this line with the object --> object = ogreSceneManager->createEntity("Head", "ogrehead.mesh");
	// and don't forgot to attach the object in the last line.
	// Create a skydome
	//ogreSceneManager->setSkyDome(true, "Examples/CloudySky", 5, 8);

	this->createGridObjects();

	Ogre::Entity* ogreheadEntity = ogreSceneManager->createEntity("ogreHead", "ogrehead.mesh");
	ogreSceneManager->getRootSceneNode()->createChildSceneNode("ogreHead")->attachObject(ogreheadEntity);

    static Button::CanvasObject obj(*ogreheadEntity);
    static Button n(obj);
    n.Clicked().connect(sigc::ptr_fun(print));
}

void OgreCanvas::createGridObjects()
{
        mFloorGrid = ogreSceneManager->createManualObject("editingFloorGrid");
		mFloorGrid->begin("editingFloorGridLines", Ogre::RenderOperation::OT_LINE_LIST);

        for (int x=(-FLOOR_LINE_NUM * FLOOR_LINE_SPACE); x <= FLOOR_LINE_NUM * FLOOR_LINE_SPACE; x += FLOOR_LINE_SPACE)
        {
            mFloorGrid->position(Ogre::Vector3(x, 0, -FLOOR_LINE_NUM * FLOOR_LINE_SPACE));
            mFloorGrid->position(Ogre::Vector3(x, 0, FLOOR_LINE_NUM * FLOOR_LINE_SPACE));
        }

        for (int z = -FLOOR_LINE_NUM * FLOOR_LINE_SPACE; z <= FLOOR_LINE_NUM * FLOOR_LINE_SPACE; z += FLOOR_LINE_SPACE)
        {
            mFloorGrid->position(Ogre::Vector3(-FLOOR_LINE_NUM * FLOOR_LINE_SPACE, 0, z));
            mFloorGrid->position(Ogre::Vector3(FLOOR_LINE_NUM * FLOOR_LINE_SPACE, 0, z));
        }
        mFloorGrid->colour(Ogre::ColourValue::Black);

        mFloorGrid->end();
		mFloorGrid->setCastShadows(false);
        mFloorGrid->setQueryFlags(0);

		ogreSceneManager->getRootSceneNode()->createChildSceneNode("floorGrid")->attachObject(mFloorGrid);

        mCircle = ogreSceneManager->createManualObject("circle");
		mCircle->begin("circle_line", Ogre::RenderOperation::OT_LINE_STRIP);

        const int segs = 200;
		const float delta = (float)(2 * Ogre::Math::PI / segs);

        for (int i = 0; i < segs; ++i)
			mCircle->position((float)Ogre::Math::Sin(i * delta), 0, (float)Ogre::Math::Cos(i * delta));

        mCircle->end();
		Ogre::SceneNode * centerNode = ogreSceneManager->getRootSceneNode()->createChildSceneNode("centerCircle");
		centerNode->attachObject(mCircle);

		//this->mCurrCamera->setAutoTracking(true,centerNode);
		//this->mCurrCamera->setFixedYawAxis(true);
}
