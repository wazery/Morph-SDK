#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "MorphCore/Editor/saveScene.h"
#include "MorphCore/Editor/OgreMax/OgreMaxScene.hpp"

#include <QMessageBox>

using namespace Morph;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mSettingsFile = QApplication::applicationDirPath() + "editorSettings";
    mSettings = new QSettings(mSettingsFile, QSettings::NativeFormat);

    if (!mSettings->value("StartingWindow/startingWindow").toBool())
    {
        startingWindow = new StartingWindow(this);
        startingWindow->show();
    }

    //if(mSettings->value("Editor/firstTime").toBool())

    // Pointers to the editor subsystems.
    systemManager = ui->widget;
    lightWin = new LightWindow(this);

    matWin = new MatWindow(this);

    loadSettings();

    // Disable actions
    ui->actionNew->setEnabled(false);
    ui->actionOpen_Ogre_Scene->setEnabled(false);
    ui->actionAdd_Ogre_Mesh->setEnabled(false);
    ui->actionCopy->setEnabled(false);
    ui->actionCut->setEnabled(false);
    ui->action_Remove_Selected->setEnabled(false);
    ui->actionSave->setEnabled(false);
    ui->actionSave_as->setEnabled(false);
    ui->menuMaterial->setEnabled(false);
    ui->menuObjects->setEnabled(false);
    ui->menuSelection->setEnabled(false);
    //ui->menuSettings->setEnabled(false);
    ui->menuView->setEnabled(false);
    ui->menuTools->setEnabled(false);
    ui->menuWindows->setEnabled(false);

    envProperties = new EnvProperties(this);
    propertiesTab = ui->tabWidget_3;
    propertiesTab->addTab(envProperties, QIcon("settings.png"), ("Environment"));

    objProperties = new ObjProperties(this);
    propertiesTab->addTab(objProperties, QIcon("settings.png"), ("Object"));
    propertiesTab->setEnabled(false);

    ui->listWidget->addItem(new QListWidgetItem(QIcon("settings.png"), "3D Button"));
    ui->listWidget->addItem(new QListWidgetItem(QIcon("check.png"), "3D Slider"));
    ui->listWidget->addItem(new QListWidgetItem(QIcon("calculator.png"), "3D Toggle Button"));

    MLogManager::getSingleton().addListener(ui->textBrowser);
    MLogManager::getSingleton().addListener(ui->textBrowser_2);

    ui->engineProgress->setVisible(false);
    ui->label->setVisible(false);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(startEngineLoading()));
    connect(ui->engineProgress, SIGNAL(valueChanged(int)), this, SLOT(changeIndexofCanvas(int)));

    // TODO: add listeners for the subsystems.
    //MNodeManager::getSingleton().addSelectListener(&m_wndProperties);
    //MNodeManager::getSingleton().addAttributeListener(&m_wndProperties);
    //MCommandManager::getSingleton().addCommandListener(this);

    //  Connect actions to slots.
    // --------------------------------------
    connect(ui->actionAbout_Morph, SIGNAL(triggered()), this, SLOT(openAboutDialog()));
    connect(ui->action_Quick_Start_Guide, SIGNAL(triggered()), this, SLOT(openQuickStart()));

    connect(ui->actionConfigure_Editor, SIGNAL(triggered()), this, SLOT(openSettingsDialog()));
    connect(ui->actionAdd_Ogre_Mesh, SIGNAL(triggered()), this, SLOT(addObj()));
    connect(ui->actionSet_Background_Color, SIGNAL(triggered()), this, SLOT(setBackgroundColor()));
    connect(ui->action_Add_Light, SIGNAL(triggered()), this, SLOT(addLight()));

    connect(ui->actionSet_Script_Path, SIGNAL(triggered()), this, SLOT(setScriptPath()));
    connect(ui->actionSet_Texture, SIGNAL(triggered()), this, SLOT(setTexturePath()));

    connect(ui->actionRemoveMesh, SIGNAL(triggered()), this, SLOT(showRemoveObj()));
    connect(ui->action_Remove_Selected, SIGNAL(triggered()), this, SLOT(removeSelected()));

    connect(ui->actionSave_as, SIGNAL(triggered()), this, SLOT(saveAs()));
    connect(ui->actionOpen_Ogre_Scene, SIGNAL(triggered()), this, SLOT(openScene()));
    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(newScene()));

    connect(ui->actionAboutQt, SIGNAL(triggered()), this, SLOT(aboutQt()));
    connect(ui->actionRestore_Default, SIGNAL(triggered()), this, SLOT(restoreDefault()));

    connect(ui->actionSelect, SIGNAL(triggered()), this, SLOT(selectObject()));
    connect(ui->actionMove, SIGNAL(triggered()), this, SLOT(moveObject()));
    connect(ui->actionRotate, SIGNAL(triggered()), this, SLOT(rotateObject()));
    connect(ui->actionNavigation, SIGNAL(triggered()), this, SLOT(translateObject()));
    //connect(ui->actionFull_Screen, SIGNAL(triggered()), this, SLOT(fullScreen()));

    //  Environment Properties
    // --------------------------------------
    connect(envProperties->fogTypeCombo, SIGNAL(activated(int)), this, SLOT(setFog(int)));
    connect(envProperties->fogColorBtn, SIGNAL(clicked()), this, SLOT(setFogColor()));
    connect(envProperties->shadowTypeCombo, SIGNAL(activated(int)), this, SLOT(setShadow(int)));
    connect(envProperties->backgroundColorBtn, SIGNAL(clicked()), this, SLOT(setBackgroundColor()));
    connect(envProperties->ambientLightColorBtn, SIGNAL(clicked()), this, SLOT(setAmbientLight()));
    connect(envProperties->modifyAction, SIGNAL(triggered()), this, SLOT(modifyLight()));
    connect(envProperties->removeAction, SIGNAL(triggered()), this, SLOT(deleteLight()));
    connect(envProperties->renderDetailCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(setRenderDetail(int)));

    //  Object Properties
    // --------------------------------------
    connect(systemManager, SIGNAL(selectedNodeChanged(bool)), this, SLOT(getObjName(bool)));
    connect(systemManager, SIGNAL(selectedNodeChanged(bool)), this, SLOT(enableObjProperties(bool)));
    connect(systemManager, SIGNAL(selectedNodeChanged(bool)), this, SLOT(setPostions(bool)));
    connect(systemManager, SIGNAL(selectedNodeChanged(bool)), this, SLOT(setScales(bool)));
    connect(systemManager, SIGNAL(selectedNodeChanged(bool)), this, SLOT(updateTreeSelection(bool)));

    connect(objProperties->boundBoxCheckBox, SIGNAL(clicked(bool)), this, SLOT(setObjBoundingBoxes(bool)));
    connect(systemManager, SIGNAL(selectedNodeChanged(bool)), objProperties->boundBoxCheckBox, SLOT(setChecked(bool)));

    connect(objProperties->dispSkeletonCheckBox, SIGNAL(clicked(bool)), this, SLOT(setobjSkeleton(bool)));

    connect(objProperties, SIGNAL(signalPosXChanged(int)), this, SLOT(setObjectPosX(int)));
    connect(objProperties, SIGNAL(signalPosYChanged(int)), this, SLOT(setObjectPosY(int)));
    connect(objProperties, SIGNAL(signalPosZChanged(int)), this, SLOT(setObjectPosZ(int)));

    connect(objProperties, SIGNAL(signalRotXChanged(int)), this, SLOT(setObjectRotX(int)));
    connect(objProperties, SIGNAL(signalRotYChanged(int)), this, SLOT(setObjectRotY(int)));
    connect(objProperties, SIGNAL(signalRotZChanged(int)), this, SLOT(setObjectRotZ(int)));

    connect(objProperties, SIGNAL(signalScaleXChanged(int)), this, SLOT(setObjectScaleX(int)));
    connect(objProperties, SIGNAL(signalScaleYChanged(int)), this, SLOT(setObjectScaleY(int)));
    connect(objProperties, SIGNAL(signalScaleZChanged(int)), this, SLOT(setObjectScaleZ(int)));

    connect(objProperties->viewMatBtn, SIGNAL(clicked()), this, SLOT(setMaterial()));
    connect(matWin, SIGNAL(msgBoxClicked()), this, SLOT(updateMaterial()));

    connect(objProperties->listAnimCombo, SIGNAL(activated(QString)), this, SLOT(setAnimation(QString)));
    connect(objProperties->loopCheckBox, SIGNAL(stateChanged(int)), this, SLOT(setAnimLoop(int)));
    connect(objProperties->playCheckBox, SIGNAL(stateChanged(int)), this, SLOT(setAnimEnabled(int)));

    // Light Win Properties
    // --------------------------------------
    connect(lightWin->diffuseColorLightBtn, SIGNAL(clicked()), this, SLOT(setDiffuseLightColor()));
    connect(lightWin->specularColorLightBtn, SIGNAL(clicked()), this, SLOT(setSpecularLightColor()));
    connect(lightWin->okBtn, SIGNAL(clicked()), this, SLOT(createNewLight()));

    connect(ui->grid, SIGNAL(clicked(bool)), this, SLOT(gridChanged(bool)));
    connect(ui->zoomSlider, SIGNAL(valueChanged(int)), ui->zommSpinBox, SLOT(setValue(int)));
    connect(ui->zommSpinBox, SIGNAL(valueChanged(int)), ui->zoomSlider, SLOT(setValue(int)));

    //  Initialise Engine
    // --------------------------------------
    connect(systemManager, SIGNAL(initialised()), this, SLOT(addNodeListener()));
    connect(systemManager, SIGNAL(initialised()), this, SLOT(initialisePlugins()));

    connect(ui->zoomSlider, SIGNAL(sliderMoved(int)), this, SLOT(zoomValueChanged(int)));

    connect(ui->fourViews, SIGNAL(clicked()), this, SLOT(setFourViewPorts()));
    connect(ui->oneView, SIGNAL(clicked()), this, SLOT(setOneViewPort()));
    connect(ui->wireframe, SIGNAL(clicked()), this, SLOT(setViewPortToWireframe()));
    connect(ui->points, SIGNAL(clicked()), this, SLOT(setViewPortToPoints()));
    connect(ui->polygons, SIGNAL(clicked()), this, SLOT(setViewPortToPolygons()));

    //Init to white the diffuse and specular colors (NOTE: the initialisation takes effect on the "LightWindow")
    diffuseLightColor.setRgba(qRgba(255, 255, 255, 255));
    specularLightColor.setRgba(qRgba(255, 255, 255, 255));
    //listName.push_back("Main Light");//This is our first light created by hand in LightWindow, so we've to put in the "blacklist" of names
}

MainWindow::~MainWindow()
{
    saveSettings();
    delete ui;
}

void MainWindow::addNodeListener()
{
    if(systemManager->isInitialised())
        ui->treeView->setSystemManager(systemManager);
    //MNodeManager::getSingleton().addNodeTreeListener(ui->treeView);
}

void MainWindow::initialisePlugins()
{
    //MNodeManager::getSingleton().registerNode(MRootNode::nodeID, MRootNode::creator);

    // firstly create the root.
    //MNodePtr rootNodePtr = MNodeManager::getSingleton().createNode(MRootNode::nodeID, MRootNode::nodeID);
//    if(!rootNodePtr)
//    {
//        MLogManager::getSingleton().logOutput("Error failed in initilaizePlugin(), setting the root node", M_ERROR);
//        return;
//    }
    //MNodeManager::getSingleton().setRootNodePtr(rootNodePtr);
    //MNodeManager::getSingleton().notifyAddNode("World.", rootNodePtr->getName());

    // Init Object Properties
    objProperties->boundBoxCheckBox->setEnabled(false);
    objProperties->dispSkeletonCheckBox->setEnabled(false);
    objProperties->lodSlider->setEnabled(false);

    // Enable Canvas Buttons
    ui->grid->setEnabled(true);
    ui->zommSpinBox->setEnabled(true);
    ui->zoomSlider->setEnabled(true);
    ui->onetoOne->setEnabled(true);
    ui->oneView->setEnabled(true);
    ui->fourViews->setEnabled(true);
    ui->wireframe->setEnabled(true);
    ui->points->setEnabled(true);
    ui->actionNew->setEnabled(true);
    ui->actionOpen->setEnabled(true);
    ui->actionOpen_Ogre_Scene->setEnabled(true);
    ui->actionAdd_Ogre_Mesh->setEnabled(true);
    ui->actionSave->setEnabled(true);
    ui->actionCopy->setEnabled(true);
    ui->actionCut->setEnabled(true);
    ui->action_Remove_Selected->setEnabled(true);
    ui->actionSave_as->setEnabled(true);
    ui->menuMaterial->setEnabled(true);
    ui->menuObjects->setEnabled(true);
    ui->menuSelection->setEnabled(true);
    //ui->menuSettings->setEnabled(true);
    ui->menuView->setEnabled(true);
    ui->menuTools->setEnabled(true);
    ui->menuWindows->setEnabled(true);
}

void MainWindow::zoomValueChanged(int value)
{
    systemManager->changeZoomValue(Ogre::Vector3(0, 0, value));
}

void MainWindow::setFourViewPorts()
{
    if(systemManager->isVisible())
    {
        systemManager->setViewNum(4);
        ui->oneView->setEnabled(true);
        ui->fourViews->setEnabled(false);
        //ui->fourViews->setIcon(); //TODO: Insert a grayish disabled four views icon
    }
}

void MainWindow::setOneViewPort()
{
    if(systemManager->isVisible())
    {
        systemManager->setViewNum(1);
        ui->fourViews->setEnabled(true);
        ui->oneView->setEnabled(false);
        //ui->oneView->setIcon(); //TODO: Insert a grayish disabled one view icon
    }
}

void MainWindow::setViewPortToWireframe()
{
    //Re-Enable other view options
    ui->points->setEnabled(true);
    ui->polygons->setEnabled(true);

    QList<MOgreCanvas*> renderWidnowList = systemManager->getOgreWindows();
    for(int i = 0; i < renderWidnowList.count(); i++)
    {
        renderWidnowList[i]->setPolygonMode(Ogre::PM_WIREFRAME);
        renderWidnowList[i]->update();
    }
    MLogManager::getSingleton().logOutput("Set Viewport mode to Wireframe", M_EDITOR_MESSAGE);
    ui->wireframe->setEnabled(false);
}

void MainWindow::setViewPortToPoints()
{
    //Re-Enable other view options
    ui->wireframe->setEnabled(true);
    ui->polygons->setEnabled(true);

    QList<MOgreCanvas*> renderWidnowList = systemManager->getOgreWindows();
    for(int i = 0; i < renderWidnowList.count(); i++)
    {
        renderWidnowList[i]->setPolygonMode(Ogre::PM_POINTS);
        renderWidnowList[i]->update();
    }
    MLogManager::getSingleton().logOutput("Set Viewport mode to Points", M_EDITOR_MESSAGE);
    ui->points->setEnabled(false);
}

void MainWindow::setViewPortToPolygons()
{
    //Re-Enable other view options
    ui->wireframe->setEnabled(true);
    ui->points->setEnabled(true);

    QList<MOgreCanvas*> renderWidnowList = systemManager->getOgreWindows();
    for(int i = 0; i < renderWidnowList.count(); i++)
    {
        renderWidnowList[i]->setPolygonMode(Ogre::PM_SOLID);
        renderWidnowList[i]->update();
    }
    MLogManager::getSingleton().logOutput("Set Viewport mode to Polygons", M_EDITOR_MESSAGE);
}

void MainWindow::loadSettings()
{
    // Set background color to the last saved setting.
    QColor color(mSettings->value("Canvas/canvasBackgroundColor").toString());
    if (color.isValid())
    {
        systemManager->setBackgroundColor(color);
    }

    //Set grid checkbox
    ui->grid->setChecked(mSettings->value("Grid/grid").toBool());
}

// TODO: I don't know why the save settings not called in the ~MainWindow()
void MainWindow::saveSettings()
{
    // Set the previous viewport option.
    if(ui->wireframe->isEnabled())
        mSettings->setValue("Canvas/canvasViewportCurrentOption", 0);

    else if(ui->points->isEnabled())
        mSettings->setValue("Canvas/canvasViewportCurrentOption", 1);

    if(ui->polygons->isEnabled())
        mSettings->setValue("Canvas/canvasViewportCurrentOption", 2);
}

void MainWindow::openAboutDialog()
{
    aboutdialog = new AboutDialog();
    aboutdialog->show();
}

void MainWindow::openQuickStart()
{
    startingWindow = new StartingWindow();
    startingWindow->show();
}

void MainWindow::openSettingsDialog()
{
    if(systemManager->isVisible())
        settingsdialog = new Settingsdialog(this, true);
    else
        settingsdialog = new Settingsdialog(this, false);
    connect(settingsdialog, SIGNAL(signalGridDivisionsChanged(int)), this, SLOT(gridDivisionsChanged(int)));
    connect(settingsdialog, SIGNAL(signalGridColorChanged(QColor)), this, SLOT(gridColorChanged(QColor)));
    connect(settingsdialog, SIGNAL(signalGridPrespectiveSizeChanged(int)), this, SLOT(gridPrespectiveSizeChanged(int)));
    connect(settingsdialog, SIGNAL(signalGridRenderLayerChanged(int)), this, SLOT(gridRenderLayerChanged(int)));
    connect(settingsdialog, SIGNAL(signalGridRenderScaleChanged(bool)), this, SLOT(gridRenderScaleChanged(bool)));
    settingsdialog->show();
}

static QTimer* timer = new QTimer();
void MainWindow::startEngineLoading()
{
    if(mSettings->value("Editor/resourcesPath").toString().isEmpty() || mSettings->value("Editor/configurationPath").toString().isEmpty() || mSettings->value("Editor/pluginsPath").toString().isEmpty() || mSettings->value("Editor/ogreLogPath").toString().isEmpty() || mSettings->value("Editor/morphLogPath").toString().isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setText("This is the first time you start Morph Editor, wellcome and can you please set Ogre settings?");
        msgBox.setIcon(QMessageBox::Question);
        QPushButton* yesButton = msgBox.addButton(tr("OK"), QMessageBox::ActionRole);
        QPushButton* noButton = msgBox.addButton(tr("Cancel"), QMessageBox::ActionRole);
        msgBox.exec();

        if (msgBox.clickedButton() == yesButton)
        {
            ui->actionConfigure_Editor->trigger();
        }
        else if (msgBox.clickedButton() == noButton)
        {
            msgBox.close();
        }
    }

    ui->engineProgress->setVisible(true);
    ui->label->setVisible(true);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateProgress()));
    timer->start(10);
}

void MainWindow::updateProgress()
{
    static int progress = 0;
    ui->engineProgress->setValue(++progress);
}

void MainWindow::changeIndexofCanvas(int value)
{
    if (isActiveWindow())
    {
        if(value == 100)
        {
            ui->tabWidget->setCurrentIndex(1);
            ui->rendered->show();
            propertiesTab->setEnabled(true);
            setOneViewPort();
            ui->engineProgress->setVisible(false);
            ui->label->setVisible(false);
            ui->pushButton->setVisible(false);
            //ui->treeView->preInit();
        }
    }
    else
    {
        ui->engineProgress->hide();
        ui->label->hide();
        timer->stop();
        disconnect(timer, SIGNAL(timeout()), this, SLOT(updateProgress()));
        QMessageBox::warning(this, "Window must be focused!", "In order to start loading the canvas, the Morph editor must get focused!");
    }
}

void MainWindow::aboutQt()
{
    QApplication::aboutQt();
}

void MainWindow::restoreDefault()
{
    mSettings->setValue("Grid/gridPrespectiveSize", 130);
    mSettings->setValue("Grid/gridDivisions", 3);
    mSettings->setValue("Grid/gridColor", "#000000");
    mSettings->setValue("Grid/grid", true);
    mSettings->setValue("Grid/gridRenderLayer", 0);
    mSettings->setValue("Canvas/canvasBackgroundColor", "#181818");
    mSettings->setValue("StartingWindow/startingWindow", "false");

    QMessageBox::information(this, "Morph Editor Needs Restart", "In order the changes to take effect, you must restart Morph Editor!");
}

void MainWindow::selectObject()
{
    ui->actionNavigation->setEnabled(true);
    ui->actionRotate->setEnabled(true);
    ui->actionMove->setEnabled(true);
    ui->actionSelect->setEnabled(false);
    systemManager->setCursor(Qt::CrossCursor);
    systemManager->setSelectEnabled(true);
}

void MainWindow::moveObject()
{
    ui->actionSelect->setEnabled(true);
    ui->actionNavigation->setEnabled(true);
    ui->actionRotate->setEnabled(true);
    ui->actionMove->setEnabled(false);
    systemManager->setSelectEnabled(false);
    systemManager->setCursor(Qt::ClosedHandCursor);
    systemManager->setMoveEnabled(true);
}

void MainWindow::translateObject()
{
    systemManager->setMoveEnabled(false);
    ui->actionSelect->setEnabled(true);
    ui->actionMove->setEnabled(true);
    ui->actionNavigation->setEnabled(false);
    systemManager->setCursor(Qt::ArrowCursor);
}

void MainWindow::fullScreen()
{
//    if(!isFullScreen())
//        this->fullScreen();
//    else
//        setWindowState(Qt::WindowMaximized);
}

void MainWindow::rotateObject()
{
//    ui->actionSelect->setEnabled(true);
//    ui->actionMove->setEnabled(true);
//    ui->actionNavigation->setEnabled(true);
//    ui->actionRotate->setEnabled(false);
//    systemManager->setCursor(Qt::SizeFDiagCursor);
}

void MainWindow::gridColorChanged(QColor color)
{
    Ogre::ColourValue ogreColor;
    ogreColor.setAsARGB(color.rgba());

    if(!systemManager->mGridList.isEmpty())
    {
        for(int i = 0; i < systemManager->mGridList.count(); i++)
        {
            systemManager->mGridList[i]->setColour(ogreColor);
            mSettings->setValue("Grid/gridColor", color.name());
        }
    }
}

void MainWindow::gridDivisionsChanged(int value)
{
    if(!systemManager->mGridList.isEmpty())
    {
        for(int i = 0; i < systemManager->mGridList.count(); i++)
        {
            systemManager->mGridList[i]->setDivision(value);
        }
    }
}

void MainWindow::gridPrespectiveSizeChanged(int size)
{
    if(!systemManager->mGridList.isEmpty())
    {
        for(int i = 0; i < systemManager->mGridList.count(); i++)
        {
            systemManager->mGridList[i]->setPerspectiveSize(size);
        }
    }
}

void MainWindow::gridRenderLayerChanged(int index)
{
    if(!systemManager->mGridList.isEmpty())
    {
        for(int i = 0; i < systemManager->mGridList.count(); i++)
        {
            if(index == 0)
                systemManager->mGridList[i]->setRenderLayer(ViewportGrid::RL_BEHIND);
            else
                systemManager->mGridList[i]->setRenderLayer(ViewportGrid::RL_INFRONT);
        }
    }
}

void MainWindow::gridRenderScaleChanged(bool value)
{
    if(!systemManager->mGridList.isEmpty())
    {
        for(int i = 0; i < systemManager->mGridList.count(); i++)
        {
            systemManager->mGridList[i]->setRenderScale(value);
        }
    }
}

void MainWindow::addObj()
{
    if(systemManager->isVisible())
    {
        QString meshName = QFileDialog::getOpenFileName(this, "Add a model", QDir::currentPath() + "/Media/models", "Mesh (*.mesh)");
        loadObj(meshName);
        ui->treeView->setSystemManager(systemManager);
    }
    else
        QMessageBox::warning(this, "You must open the canvas first!", "You are trying to make an action that couldn't be done without launching the canvas first!");
}

void MainWindow::loadObj(const QString &meshName)
{
    if(!meshName.isNull())
    {
        systemManager->addObject(meshName.toStdString()); // Create the new one
        MLogManager::getSingleton().logOutput("Added object: " + meshName, M_EDITOR_MESSAGE);

        if(systemManager->mainEnt->hasSkeleton())
            MLogManager::getSingleton().logOutput("Has Skeleton : YES", M_EDITOR_MESSAGE);
        else
            MLogManager::getSingleton().logOutput("Has Skeleton : NO", M_EDITOR_MESSAGE);

        // Update object properties
        objProperties->boundBoxCheckBox->setChecked(false);
        objProperties->dispSkeletonCheckBox->setChecked(false);
        objProperties->lodSlider->setSliderPosition(objProperties->lodSlider->maximum()/2);
        objProperties->listAnimCombo->clear();
        objProperties->updateListAnim(systemManager->mainEnt->getAllAnimationStates());

        if(objProperties->listAnimCombo->itemText(0) != "")
        {
            // The mesh has animations
            systemManager->setAnimationState(objProperties->listAnimCombo->itemText(0).toStdString());
            objProperties->playCheckBox->setChecked(false);
            objProperties->loopCheckBox->setChecked(false);
            MLogManager::getSingleton().logOutput("Has Animations : YES", M_EDITOR_MESSAGE);
        }
        else
            MLogManager::getSingleton().logOutput("Has Animations : NO", M_EDITOR_MESSAGE);

        MLogManager::getSingleton().logOutput("=========================", M_EDITOR_MESSAGE); // End of the log
    }
}

void MainWindow::showRemoveObj()
{
    RemoveObject* removeObject = new RemoveObject(this);
    removeObject->show();
}

void MainWindow::commitRemoveObj()
{
    RemoveObject* removeObject = qobject_cast<RemoveObject*>(QObject::sender());
    systemManager->removeObject(removeObject->getMeshName().toUtf8().constData());

    ui->treeView->setSystemManager(systemManager);
}

void MainWindow::removeSelected()
{
    if(systemManager->getSelectedNode())
        systemManager->removeObject(systemManager->getSelectedNode()->getName());

    ui->treeView->setSystemManager(systemManager);
}

void MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),"",tr("DotScene (*.scene)"));
    Ogre::String basename, path;
    Ogre::StringUtil::splitFilename(fileName.toStdString(), basename, path);
    QFile file(fileName);
    saveAsDotScene(QString(path.c_str()), file, systemManager->getSceneManager());
}

void MainWindow::openScene()
{
    if(systemManager->isVisible())
    {
        QMessageBox msgBox;
        msgBox.setText("Do you want to save current scene?");
        msgBox.setIcon(QMessageBox::Question);
        QPushButton* yesButton = msgBox.addButton(tr("Yes"), QMessageBox::ActionRole);
        QPushButton* noButton = msgBox.addButton(tr("No"), QMessageBox::ActionRole);
        msgBox.exec();

        if (msgBox.clickedButton() == yesButton)
        {
            ui->actionSave_as->trigger();
        }
        else if (msgBox.clickedButton() == noButton)
        {
            msgBox.close();
        }

        QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"",tr("DotScene (*.scene)"));

        if(fileName.isEmpty())
            return;

        for (Ogre::SceneManager::MovableObjectIterator i = systemManager->getSceneManager()->getMovableObjectIterator("Entity"); i.hasMoreElements();)
        {
            Ogre::Entity* ent = static_cast<Ogre::Entity*>(i.getNext());
            systemManager->getSceneManager()->destroyEntity(ent->getName());
        }

        Ogre::String basename, path;
        Ogre::StringUtil::splitFilename(fileName.toStdString(), basename, path);
        std::string mDirPath(path.begin(),path.end() -1);
        ResourceGroupManager::getSingleton().addResourceLocation(path, "FileSystem","General",true);
        Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();


        OgreMax::OgreMaxScene* loader = new OgreMax::OgreMaxScene();
        loader->Load( fileName.toStdString(), systemManager->getRenderWindow(), 0 , systemManager->getSceneManager());

        ui->treeView->setSystemManager(systemManager);
        //            loader->Load(mSceneFilePath, mWindow, 0, mSceneMgr, mNode);
    }
    else
    {
        QMessageBox::warning(this, "You must open the canvas first!", "You are trying to make an action that couldn't be done without launching the canvas first!");
    }
}

void MainWindow::newScene()
{
    QMessageBox msgBox;
    msgBox.setText("Do you want to save current scene?");
    msgBox.setIcon(QMessageBox::Question);
    QPushButton* yesButton = msgBox.addButton(tr("Yes"), QMessageBox::ActionRole);
    QPushButton* noButton = msgBox.addButton(tr("No"), QMessageBox::ActionRole);
    msgBox.exec();

    if (msgBox.clickedButton() == yesButton)
    {
        ui->actionSave_as->trigger();
    }
    else if (msgBox.clickedButton() == noButton)
    {
        msgBox.close();
    }

    for (Ogre::SceneManager::MovableObjectIterator i = systemManager->getSceneManager()->getMovableObjectIterator("Entity"); i.hasMoreElements();)
    {
        Ogre::Entity* ent = static_cast<Ogre::Entity*>(i.getNext());
        systemManager->getSceneManager()->destroyEntity(ent->getName());
    }

    ui->treeView->setSystemManager(systemManager);
    systemManager->update();
}

void MainWindow::setBackgroundColor()
{
    if(systemManager->isVisible())
    {
        QColor color = QColorDialog::getColor(QColor(mSettings->value("Canvas/canvasBackgroundColor").toString()), this);

        if(color.isValid())
        {
            systemManager->setBackgroundColor(color);
            MLogManager::getSingleton().logOutput("Background Color : " + color.name(), M_EDITOR_MESSAGE);
        }

        mSettings->setValue("Canvas/canvasBackgroundColor", color.name());
        mSettings->sync();
    }
    else
        QMessageBox::warning(this, "You must open the canvas first!", "You are trying to make an action that couldn't be done without launching the canvas first!");
}

void MainWindow::gridChanged(bool value)
{
    mSettings->setValue("Grid/grid", ui->grid->isChecked());
    mSettings->sync();

    if(ui->grid->isChecked())
        MLogManager::getSingleton().logOutput("Grid set to on", M_EDITOR_MESSAGE);
    else
        MLogManager::getSingleton().logOutput("Grid set to off", M_EDITOR_MESSAGE);

    systemManager->gridChanged(value);
}

void MainWindow::addLight()
{
    if(systemManager->isVisible())
    {
        //Clean properties
        lightWin->nameLightEdit->setText("");
        lightWin->XEditPos->setText("0.0");
        lightWin->YEditPos->setText("0.0");
        lightWin->ZEditPos->setText("0.0");
        lightWin->XEditDir->setText("0.0");
        lightWin->YEditDir->setText("0.0");
        lightWin->ZEditDir->setText("0.0");
        diffuseLightColor.setRgba(qRgba(255, 255, 255, 255));
        specularLightColor.setRgba(qRgba(255, 255, 255, 255));
        lightWin->typeLightCombo->setCurrentIndex(0);
        lightWin->newTypeLight("Point");//update the layout to fit with the Point light (you can only edit the position and not the direction)

        lightWin->setWindowTitle("Create Light");
        lightWin->move(width()/2, height()/2);
        lightWin->show();
    }
    else
        QMessageBox::warning(this, "You must open the canvas first!", "You are trying to make an action that couldn't be done without launching the canvas first!");
}

//Note: Only modify the LightWin attributes, not the tree. See createLight to see how we're updating the tree with the modifed values
void MainWindow::modifyLight()
{
    QTreeWidgetItem* treeWidgetItem = envProperties->lightsTree->currentItem(); //get the light
    treeWidgetItem = envProperties->lightsTree->topLevelItem(envProperties->lightsTree->indexOfTopLevelItem(envProperties->lightsTree->currentItem()));

    if(treeWidgetItem != NULL)
    {
        //in case the user didn't click on an item of the tree
        QString nameLight = treeWidgetItem->text(0); //Name of the light
        lightWin->nameLightEdit->setText(nameLight);//Update name's light of the Light Window

        QString typeLight = treeWidgetItem->child(0)->text(0); //type of the light
        typeLight = typeLight.remove(0, 7);//update the string because if we don't, it'll be like this : "Type : Point" --> so we're removing "Type : "

        QString diffuseColor = treeWidgetItem->child(1)->text(0); //diffuse color
        diffuseColor = diffuseColor.remove(0, 16);
        diffuseLightColor.setNamedColor(diffuseColor);

        QString specularColor = treeWidgetItem->child(2)->text(0); //specular color
        specularColor = specularColor.remove(0, 17);
        diffuseLightColor.setNamedColor(specularColor);

        QTreeWidgetItem* posDirItem = treeWidgetItem->child(3);

        if(posDirItem->text(0) == "Position" && treeWidgetItem->childCount() == 4)
        {
            //So it must be the Point light type (because the spotlight type has not only the positions parameters but also the direction --> so childcount = 5)
            QString xPos = posDirItem->child(0)->text(0);
            xPos = xPos.remove(0, 8);
            lightWin->XEditPos->setText(xPos);

            QString yPos = posDirItem->child(1)->text(0);
            yPos = yPos.remove(0, 8);
            lightWin->YEditPos->setText(yPos);

            QString zPos = posDirItem->child(2)->text(0);
            zPos = zPos.remove(0, 8);
            lightWin->ZEditPos->setText(zPos);

            lightWin->typeLightCombo->setCurrentIndex(0);//Set the ComboBox to "Point"
            lightWin->newTypeLight("Point");//update the layout to fit with the Directional light properties
        }
        else if(posDirItem->text(0) == "Direction")
        {
            //It's obviously the Directionnal light type
            QString xDir = posDirItem->child(0)->text(0);
            xDir = xDir.remove(0, 8);
            lightWin->XEditDir->setText(xDir);

            QString yDir = posDirItem->child(1)->text(0);
            yDir = yDir.remove(0, 8);
            lightWin->YEditDir->setText(yDir);

            QString zDir = posDirItem->child(2)->text(0);
            zDir = zDir.remove(0, 8);
            lightWin->ZEditDir->setText(zDir);

            lightWin->typeLightCombo->setCurrentIndex(1);//Set the ComboBox to "Directional"
            lightWin->newTypeLight("Directional");//update the layout to fit with the Directional light properties
        }
        else if(treeWidgetItem->childCount() == 5)
        {
            //it's the spotlight type
            QString xPos = posDirItem->child(0)->text(0);
            xPos = xPos.remove(0, 8);
            lightWin->XEditPos->setText(xPos);

            QString yPos = posDirItem->child(1)->text(0);
            yPos = yPos.remove(0, 8);
            lightWin->YEditPos->setText(yPos);

            QString zPos = posDirItem->child(2)->text(0);
            zPos = zPos.remove(0, 8);
            lightWin->ZEditPos->setText(zPos);


            QTreeWidgetItem* dirItem = treeWidgetItem->child(4);

            QString xDir = dirItem->child(0)->text(0);
            xDir = xDir.remove(0, 8);
            lightWin->XEditDir->setText(xDir);

            QString yDir = dirItem->child(1)->text(0);
            yDir = yDir.remove(0, 8);
            lightWin->YEditDir->setText(yDir);

            QString zDir = dirItem->child(2)->text(0);
            zDir = zDir.remove(0, 8);
            lightWin->ZEditDir->setText(zDir);

            lightWin->typeLightCombo->setCurrentIndex(2);//Set the ComboBox to "Spotlight"
            lightWin->newTypeLight("Spotlight");//update the layout to fit with the Spotlight light properties
        }
        lightWin->move(width()/2, height()/2);
        lightWin->setWindowTitle("Modifiy : " + nameLight);
        lightWin->show();
    }
}

void MainWindow::deleteLight()
{
    QTreeWidgetItem* treeWidgetItem = envProperties->lightsTree->currentItem();
    int posToRemove = envProperties->lightsTree->indexOfTopLevelItem(treeWidgetItem);
    QString name = envProperties->lightsTree->currentItem()->text(0);

    if(posToRemove != 1)
    {
        envProperties->lightsTree->takeTopLevelItem(posToRemove);
        listName.removeAt(posToRemove);//update our list of names
        systemManager->deleteLight(name.toStdString());
    }
    else
        QMessageBox::warning(this, "Cannot delete light", "Sorry, but you cannot delete this light at this position of the tree (-->Bug)");
}

void MainWindow::getObjName(bool value)
{
    Q_UNUSED(value)

    if(systemManager->getSelectedNode())
    {
        QString name(systemManager->getSelectedNode()->getName().c_str());
        QStringList list = name.split(".");
        objProperties->nameText->setText(list.at(0));
    }
    else
        objProperties->nameText->setText("");
}

void MainWindow::setScriptPath()
{
    QString scriptPathName = QFileDialog::getExistingDirectory(this, tr("Select Directory"), QDir::currentPath()+"/media/materials/scripts/");
    if(!scriptPathName.isEmpty())
        matWin->setScriptPath(scriptPathName);
}

void MainWindow::setTexturePath()
{
    QString texturePathName = QFileDialog::getExistingDirectory(this, tr("Select Directory"), QDir::currentPath()+"/media/materials/textures/");
    if(!texturePathName.isEmpty())
        matWin->setTexturePath(texturePathName);
}

void MainWindow::setRenderDetail(int index)
{
    if(index == 0)
        setViewPortToWireframe();
    else if(index == 1)
        setViewPortToPoints();
    else if(index == 2)
        setViewPortToPolygons();
}

void MainWindow::setObjBoundingBoxes(bool value)
{
    if(systemManager->getSelectedNode() != NULL)
    {
        systemManager->getSelectedNode()->showBoundingBox(value);
        systemManager->update();
    }
    //objProperties->boundBoxCheckBox->setEnabled(false);
}

void MainWindow::setobjSkeleton(bool value)
{
    //if(systemManager->getSelectedNode())
    //    systemManager->getSceneManager()->getEntity(systemManager->getSelectedNode()->getName())->setDisplaySkeleton(value);
}

void MainWindow::setObjectPosX(int value)
{
    if(systemManager->getSelectedNode() != NULL)
    {
        Ogre::Vector3 vector = systemManager->getSelectedNode()->getPosition();
        systemManager->getSelectedNode()->setPosition(Ogre::Real(value), vector.y, vector.z);
        systemManager->update();
    }
}

void MainWindow::setObjectPosY(int value)
{
    if(systemManager->getSelectedNode() != NULL)
    {
        Ogre::Vector3 vector = systemManager->getSelectedNode()->getPosition();
        systemManager->getSelectedNode()->setPosition(vector.x, Ogre::Real(value), vector.z);
        systemManager->update();
    }
}

void MainWindow::setObjectPosZ(int value)
{
    if(systemManager->getSelectedNode() != NULL)
    {
        Ogre::Vector3 vector = systemManager->getSelectedNode()->getPosition();
        systemManager->getSelectedNode()->setPosition(vector.x, vector.y, Ogre::Real(value));
        systemManager->update();
    }
}

// -----------------------------------------
void MainWindow::setObjectRotX(int value)
{
    Quaternion q(Degree(10), Vector3::UNIT_X);
    systemManager->getSelectedNode()->rotate(q);
    systemManager->update();
}

void MainWindow::setObjectRotY(int value)
{
    Quaternion q(Degree(10), Vector3::UNIT_Y);
    systemManager->getSelectedNode()->rotate(q);
    systemManager->update();
}

void MainWindow::setObjectRotZ(int value)
{
    Quaternion q(Degree(10), Vector3::UNIT_Z);
    systemManager->getSelectedNode()->rotate(q);
    systemManager->update();
}

// -----------------------------------------
void MainWindow::setObjectScaleX(int value)
{
    if(systemManager->getSelectedNode() != NULL)
    {
        Ogre::Vector3 vector = systemManager->getSelectedNode()->getScale();

        if(Ogre::Real(value) == vector.x)
            return;

        systemManager->getSelectedNode()->scale(Ogre::Real(value), vector.y, vector.z);
        systemManager->update();
    }
}

void MainWindow::setObjectScaleY(int value)
{
    if(systemManager->getSelectedNode() != NULL)
    {
        Ogre::Vector3 vector = systemManager->getSelectedNode()->getScale();

        if(Ogre::Real(value) == vector.y)
            return;

        systemManager->getSelectedNode()->scale(vector.x, Ogre::Real(value), vector.z);
        systemManager->update();
    }
}

void MainWindow::setObjectScaleZ(int value)
{
    if(systemManager->getSelectedNode() != NULL)
    {
        Ogre::Vector3 vector = systemManager->getSelectedNode()->getScale();

        if(Ogre::Real(value) == vector.z)
            return;

        systemManager->getSelectedNode()->scale(vector.x, vector.y, Ogre::Real(value));
        systemManager->update();
    }
}

void MainWindow::setMaterial()
{
    matWin->move(width()/2, height()/2);
    matWin->setTexture(systemManager->getMainEntity());
    matWin->show();
}

void MainWindow::updateMaterial()
{
    systemManager->updateMaterial();
    MLogManager::getSingleton().logOutput("Please restart the application so that the new material can take effect");
    QMessageBox::information(this, "Material Update", "Please restart the application so that the new material can take effect");
}

void MainWindow::setAnimation(QString name)
{
    systemManager->setAnimationState(name.toStdString());
}
void MainWindow::setAnimLoop(int enable)
{
    systemManager->setAnimLoop(enable);
}
void MainWindow::setAnimEnabled(int enable)
{
    systemManager->setAnimEnabled(enable);
}

void MainWindow::enableObjProperties(bool value)
{
    Q_UNUSED(value)

    objProperties->boundBoxCheckBox->setEnabled(true);
    objProperties->dispSkeletonCheckBox->setEnabled(true);
    objProperties->lodSlider->setEnabled(true);
}

void MainWindow::setPostions(bool value)
{
    Q_UNUSED(value)

    if(systemManager->getSelectedNode())
    {
        Ogre::Vector3 vector = systemManager->getSelectedNode()->getPosition();
        objProperties->posXText->setValue(int(vector.x));
        objProperties->posYText->setValue(int(vector.y));
        objProperties->posZText->setValue(int(vector.z));
    }
    else
    {
        objProperties->posXText->setValue(0);
        objProperties->posYText->setValue(0);
        objProperties->posZText->setValue(0);
    }
}

void MainWindow::setScales(bool value)
{
    Q_UNUSED(value)

    if(systemManager->getSelectedNode())
    {
        Ogre::Vector3 vector = systemManager->getSelectedNode()->getScale();
        objProperties->scaleXText->setValue(int(vector.x));
        objProperties->scaleYText->setValue(int(vector.y));
        objProperties->scaleZText->setValue(int(vector.z));
    }
    else
    {
        objProperties->posXText->setValue(0);
        objProperties->posYText->setValue(0);
        objProperties->posZText->setValue(0);
    }
}

void MainWindow::updateTreeSelection(bool value)
{
    if(systemManager->getSelectedNode())
    {
        QString name(systemManager->getSelectedNode()->getName().c_str());
        ui->treeView->updateTreeSelection(name);
    }
}

void MainWindow::setDiffuseLightColor()
{
    //In case we're updating a light
    if(lightWin->windowTitle() != "Create Light")
    {
        QString diffuseColor = envProperties->lightsTree->currentItem()->child(1)->text(0);
        diffuseColor = diffuseColor.remove(0, 16);

        diffuseLightColor = QColorDialog::getColor(QColor(diffuseColor), this);
    }
    else
        diffuseLightColor = QColorDialog::getColor(Qt::white, this);
}

void MainWindow::setSpecularLightColor()
{
    //In case we're updating a light
    if(lightWin->windowTitle() != "Create Light")
    {
        QString specularColor = envProperties->lightsTree->currentItem()->child(2)->text(0);
        specularColor = specularColor.remove(0, 17);

        specularLightColor = QColorDialog::getColor(QColor(specularColor), this);
    }
    else
        specularLightColor = QColorDialog::getColor(Qt::white, this);
}

void MainWindow::setAmbientLight()
{
    if (lightWin->windowTitle() != "Create Light")
    {
        //QString ambientColor = envProperties->lightsTree->currentItem()->child(3)->text(0);
        //ambientColor = ambientColor.remove()
    }
}

void MainWindow::setFog(int fogType)
{
    systemManager->setFog(fogType);
    systemManager->update();
}

void MainWindow::setFogColor()
{
    QColor color = QColorDialog::getColor(systemManager->getFogColor(), this);
    if(color.isValid())
    {
        systemManager->setFogColor(color);
        MLogManager::getSingleton().logOutput("Fog Color : " + color.name(), M_EDITOR_MESSAGE);
    }
    systemManager->update();
}

void MainWindow::setShadow(int fogType)
{
    if(fogType == 0)
        systemManager->getSceneManager()->setShadowTechnique(SHADOWTYPE_NONE);
    else if(fogType == 1)
        systemManager->getSceneManager()->setShadowTechnique(SHADOWTYPE_STENCIL_MODULATIVE);
    else if(fogType == 2)
        systemManager->getSceneManager()->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE);
    else if(fogType == 3)
        systemManager->getSceneManager()->setShadowTechnique(SHADOWTYPE_TEXTURE_MODULATIVE);

    systemManager->update();
}

void MainWindow::createNewLight()
{
    //Recover properties
    QString nameLight = lightWin->nameLightEdit->text();
    QString xPos = lightWin->XEditPos->text();
    QString yPos = lightWin->YEditPos->text();
    QString zPos = lightWin->ZEditPos->text();
    QString xDir = lightWin->XEditDir->text();
    QString yDir = lightWin->YEditDir->text();
    QString zDir = lightWin->ZEditDir->text();
    QString typeLight = lightWin->typeLightCombo->currentText();

    if(nameLight != "")
    {
        //we have to get a name (for Ogre)
        if(!listName.contains(nameLight) && lightWin->windowTitle() == "Create Light")
        {
            //we don't want to have twice the same name (Ogre doesn't like that ;)
            listName.push_back(nameLight);
            //New Light
            QTreeWidgetItem* newLight = new QTreeWidgetItem(envProperties->lightsTree);
            newLight->setText(0, nameLight);
            //Light Type
            QTreeWidgetItem* newTypeLight = new QTreeWidgetItem(newLight);
            newTypeLight->setText(0, "Type : " + typeLight);
            //Light Color
            QTreeWidgetItem* newDiffuseLightColor = new QTreeWidgetItem(newLight);
            newDiffuseLightColor->setText(0, "Diffuse Color : " + diffuseLightColor.name());
            //systemManager->setDiffuseColor(diffuseLightColor);
            QTreeWidgetItem* newSpecularLightColor = new QTreeWidgetItem(newLight);
            newSpecularLightColor->setText(0, "Specular Color : " + specularLightColor.name());
            //systemManager->setSpecularColor(specularLightColor);

            //Because Point light, Spotlight and Directional light don't have the same properties, we filtrate
            if(typeLight == "Point")
            {
                //Light Pos
                QTreeWidgetItem* posLight = new QTreeWidgetItem(newLight);
                posLight->setText(0, "Position");
                //Light Pos X
                QTreeWidgetItem* posXLight = new QTreeWidgetItem(posLight);
                posXLight->setText(0, "X Pos : " + xPos);
                //Light Pos Y
                QTreeWidgetItem* posYLight = new QTreeWidgetItem(posLight);
                posYLight->setText(0, "Y Pos : " + yPos);
                //Light Pos Z
                QTreeWidgetItem* posZLight = new QTreeWidgetItem(posLight);
                posZLight->setText(0, "Z Pos : " + zPos);

                systemManager->createPointLight(nameLight.toStdString(), xPos.toStdString(), yPos.toStdString(), zPos.toStdString(), diffuseLightColor.name().toStdString(), specularLightColor.name().toStdString());

                MLogManager::getSingleton().logOutput("==========Light===========", M_EDITOR_MESSAGE);
                MLogManager::getSingleton().logOutput("Point Light Created : " + nameLight , M_EDITOR_MESSAGE);
                MLogManager::getSingleton().logOutput("At Position : " + xPos + ", " + yPos + ", " + zPos , M_EDITOR_MESSAGE);
                MLogManager::getSingleton().logOutput("Diffuse Color : " + diffuseLightColor.name() , M_EDITOR_MESSAGE);
                MLogManager::getSingleton().logOutput("Specular Color : " + specularLightColor.name() , M_EDITOR_MESSAGE);
                MLogManager::getSingleton().logOutput("==========================", M_EDITOR_MESSAGE);
            }
            else if(typeLight == "Spotlight")
            {
                //Light Pos
                QTreeWidgetItem* posLight = new QTreeWidgetItem(newLight);
                posLight->setText(0, "Position");
                //Light Pos X
                QTreeWidgetItem* posXLight = new QTreeWidgetItem(posLight);
                posXLight->setText(0, "X Pos : " + xPos);
                //Light Pos Y
                QTreeWidgetItem* posYLight = new QTreeWidgetItem(posLight);
                posYLight->setText(0, "Y Pos : " + yPos);
                //Light Pos Z
                QTreeWidgetItem* posZLight = new QTreeWidgetItem(posLight);
                posZLight->setText(0, "Z Pos : " + zPos);

                //Light Dir
                QTreeWidgetItem* dirLight = new QTreeWidgetItem(newLight);
                dirLight->setText(0, "Direction");
                //Light Dir X
                QTreeWidgetItem* dirXLight = new QTreeWidgetItem(dirLight);
                dirXLight->setText(0, "X Dir : " + xDir);
                //Light Dir Y
                QTreeWidgetItem* dirYLight = new QTreeWidgetItem(dirLight);
                dirYLight->setText(0, "Y Dir : " + yDir);
                //Light Dir Z
                QTreeWidgetItem* dirZLight = new QTreeWidgetItem(dirLight);
                dirZLight->setText(0, "Z Dir : " + zDir);

                systemManager->createSpotlight(nameLight.toStdString(), xPos.toStdString(), yPos.toStdString(), zPos.toStdString(), xDir.toStdString(), yDir.toStdString(), zDir.toStdString(), diffuseLightColor.name().toStdString(), specularLightColor.name().toStdString());

                MLogManager::getSingleton().logOutput("==========Light===========", M_EDITOR_MESSAGE);
                MLogManager::getSingleton().logOutput("Spotlight Created : " + nameLight , M_EDITOR_MESSAGE);
                MLogManager::getSingleton().logOutput("At Position : " + xPos + ", " + yPos + ", " + zPos , M_EDITOR_MESSAGE);
                MLogManager::getSingleton().logOutput("Direction : " + xDir + ", " + yDir + ", " + zDir , M_EDITOR_MESSAGE);
                MLogManager::getSingleton().logOutput("Diffuse Color : " + diffuseLightColor.name() , M_EDITOR_MESSAGE);
                MLogManager::getSingleton().logOutput("Specular Color : " + specularLightColor.name() , M_EDITOR_MESSAGE);
                MLogManager::getSingleton().logOutput("==========================", M_EDITOR_MESSAGE);
            }
            else if(typeLight == "Directional")
            {
                //Light Dir
                QTreeWidgetItem* dirLight = new QTreeWidgetItem(newLight);
                dirLight->setText(0, "Direction");
                //Light Dir X
                QTreeWidgetItem* dirXLight = new QTreeWidgetItem(dirLight);
                dirXLight->setText(0, "X Dir : " + xDir);
                //Light Dir Y
                QTreeWidgetItem* dirYLight = new QTreeWidgetItem(dirLight);
                dirYLight->setText(0, "Y Dir : " + yDir);
                //Light Dir Z
                QTreeWidgetItem* dirZLight = new QTreeWidgetItem(dirLight);
                dirZLight->setText(0, "Z Dir : " + zDir);

                systemManager->createDirectionalLight(nameLight.toStdString(), xDir.toStdString(), yDir.toStdString(), zDir.toStdString(), diffuseLightColor.name().toStdString(), specularLightColor.name().toStdString());
                MLogManager::getSingleton().logOutput("==========Light===========", M_EDITOR_MESSAGE);
                MLogManager::getSingleton().logOutput("Directional Light Created : " + nameLight , M_EDITOR_MESSAGE);
                MLogManager::getSingleton().logOutput("Direction : " + xDir + ", " + yDir + ", " + zDir , M_EDITOR_MESSAGE);
                MLogManager::getSingleton().logOutput("Diffuse Color : " + diffuseLightColor.name() , M_EDITOR_MESSAGE);
                MLogManager::getSingleton().logOutput("Specular Color : " + specularLightColor.name() , M_EDITOR_MESSAGE);
                MLogManager::getSingleton().logOutput("==========================", M_EDITOR_MESSAGE);
            }

            lightWin->close();

            //Clean properties
            lightWin->nameLightEdit->setText("");
            lightWin->XEditPos->setText("0.0");
            lightWin->YEditPos->setText("0.0");
            lightWin->ZEditPos->setText("0.0");
            lightWin->XEditDir->setText("0.0");
            lightWin->YEditDir->setText("0.0");
            lightWin->ZEditDir->setText("0.0");
            diffuseLightColor.setRgba(qRgba(255, 255, 255, 255));
            specularLightColor.setRgba(qRgba(255, 255, 255, 255));
            lightWin->typeLightCombo->setCurrentIndex(0);
            lightWin->newTypeLight("Point");//update the layout to fit with the Point light (you can only edit the position and not the direction)
        }
        else if(lightWin->windowTitle() != "Create Light")
        {
            //We are updating a light
            QString oldName = "none";
            if(nameLight != envProperties->lightsTree->currentItem()->text(0))
            {
                //the name has changed so we removed the name which don't exist anymore ant update listName with the new name
                oldName = envProperties->lightsTree->currentItem()->text(0);
                listName.removeAt(envProperties->lightsTree->indexOfTopLevelItem(envProperties->lightsTree->currentItem()));
                listName.push_back(nameLight);
            }

            QTreeWidgetItem* treeWidgetItem = envProperties->lightsTree->currentItem(); //get the light

            treeWidgetItem->setText(0, nameLight); //Name of the light
            treeWidgetItem->child(0)->setText(0, "Type : " + typeLight); //type of the light
            treeWidgetItem->child(1)->setText(0, "Diffuse Color : " + diffuseLightColor.name()); //diffuse color
            treeWidgetItem->child(2)->setText(0, "Specular Color : " + specularLightColor.name()); //specular color
            systemManager->setDiffuseColor(diffuseLightColor);
            systemManager->setSpecularColor(specularLightColor);

            QTreeWidgetItem* posDirItem = treeWidgetItem->child(3);
            if(typeLight == "Point"){
                posDirItem->setText(0, "Position");

                posDirItem->child(0)->setText(0, "X Pos : " + xPos);
                posDirItem->child(1)->setText(0, "Y Pos : " + yPos);
                posDirItem->child(2)->setText(0, "Z Pos : " + zPos);

                QTreeWidgetItem* dirItem = treeWidgetItem->child(4);
                if(dirItem != NULL)//Means that it was a Spotlight before. So we're removing the Direction properties
                    treeWidgetItem->takeChild(4);

                systemManager->updatePointLight(oldName.toStdString(), nameLight.toStdString(), xPos.toStdString(), yPos.toStdString(), zPos.toStdString(), diffuseLightColor.name().toStdString(), specularLightColor.name().toStdString());
                MLogManager::getSingleton().logOutput("==========Light===========", M_EDITOR_MESSAGE);
                MLogManager::getSingleton().logOutput("Point Light Updated :", M_EDITOR_MESSAGE);
                MLogManager::getSingleton().logOutput("Old Name : " + oldName , M_EDITOR_MESSAGE);
                MLogManager::getSingleton().logOutput("New Name : " + nameLight , M_EDITOR_MESSAGE);
                MLogManager::getSingleton().logOutput("At Position : " + xPos + ", " + yPos + ", " + zPos , M_EDITOR_MESSAGE);
                MLogManager::getSingleton().logOutput("Diffuse Color : " + diffuseLightColor.name() , M_EDITOR_MESSAGE);
                MLogManager::getSingleton().logOutput("Specular Color : " + specularLightColor.name() , M_EDITOR_MESSAGE);
                MLogManager::getSingleton().logOutput("==========================", M_EDITOR_MESSAGE);
            }
            else if(typeLight == "Directional")
            {
                posDirItem->setText(0, "Direction");

                posDirItem->child(0)->setText(0, "X Dir : " + xDir);
                posDirItem->child(1)->setText(0, "Y Dir : " + yDir);
                posDirItem->child(2)->setText(0, "Z Dir : " + zDir);

                QTreeWidgetItem* dirItem = treeWidgetItem->child(4);
                if(dirItem != NULL)//Means that it was a Spotlight before. So we're removing the Direction properties (we don't want twice direction properties)
                    treeWidgetItem->takeChild(4);

                systemManager->updateDirectionalLight(oldName.toStdString(), nameLight.toStdString(), xDir.toStdString(), yDir.toStdString(), zDir.toStdString(), diffuseLightColor.name().toStdString(), specularLightColor.name().toStdString());
                MLogManager::getSingleton().logOutput("==========Light===========", M_EDITOR_MESSAGE);
                MLogManager::getSingleton().logOutput("Directional Light Updated :", M_EDITOR_MESSAGE);
                MLogManager::getSingleton().logOutput("Old Name : " + oldName , M_EDITOR_MESSAGE);
                MLogManager::getSingleton().logOutput("New Name : " + nameLight , M_EDITOR_MESSAGE);
                MLogManager::getSingleton().logOutput("Direction : " + xDir + ", " + yDir + ", " + zDir , M_EDITOR_MESSAGE);
                MLogManager::getSingleton().logOutput("Diffuse Color : " + diffuseLightColor.name() , M_EDITOR_MESSAGE);
                MLogManager::getSingleton().logOutput("Specular Color : " + specularLightColor.name() , M_EDITOR_MESSAGE);
                MLogManager::getSingleton().logOutput("==========================", M_EDITOR_MESSAGE);
            }
            else if(typeLight == "Spotlight")
            {
                posDirItem->setText(0, "Position");

                posDirItem->child(0)->setText(0, "X Pos : " + xPos);
                posDirItem->child(1)->setText(0, "Y Pos : " + yPos);
                posDirItem->child(2)->setText(0, "Z Pos : " + zPos);

                QTreeWidgetItem* dirItem = treeWidgetItem->child(4);
                if(dirItem != NULL){
                    dirItem->setText(0, "Direction");

                    dirItem->child(0)->setText(0, "X Dir : " + xDir);
                    dirItem->child(1)->setText(0, "Y Dir : " + yDir);
                    dirItem->child(2)->setText(0, "Z Dir : " + zDir);

                    systemManager->updateSpotlight(oldName.toStdString(), nameLight.toStdString(), xPos.toStdString(), yPos.toStdString(), zPos.toStdString(), xDir.toStdString(), yDir.toStdString(), zDir.toStdString(), diffuseLightColor.name().toStdString(), specularLightColor.name().toStdString());
                    MLogManager::getSingleton().logOutput("==========Light===========", M_EDITOR_MESSAGE);
                    MLogManager::getSingleton().logOutput("Spotlight Light Updated :", M_EDITOR_MESSAGE);
                    MLogManager::getSingleton().logOutput("Old Name : " + oldName , M_EDITOR_MESSAGE);
                    MLogManager::getSingleton().logOutput("New Name : " + nameLight , M_EDITOR_MESSAGE);
                    MLogManager::getSingleton().logOutput("At Position : " + xPos + ", " + yPos + ", " + zPos , M_EDITOR_MESSAGE);
                    MLogManager::getSingleton().logOutput("Direction : " + xDir + ", " + yDir + ", " + zDir , M_EDITOR_MESSAGE);
                    MLogManager::getSingleton().logOutput("Diffuse Color : " + diffuseLightColor.name() , M_EDITOR_MESSAGE);
                    MLogManager::getSingleton().logOutput("Specular Color : " + specularLightColor.name() , M_EDITOR_MESSAGE);
                    MLogManager::getSingleton().logOutput("==========================", M_EDITOR_MESSAGE);
                }
                else{//The Direction tree doesn't exist
                    //Light Dir
                    QTreeWidgetItem* dirLight = new QTreeWidgetItem(treeWidgetItem);
                    dirLight->setText(0, "Direction");
                    //Light Dir X
                    QTreeWidgetItem* dirXLight = new QTreeWidgetItem(dirLight);
                    dirXLight->setText(0, "X Dir : " + xDir);
                    //Light Dir Y
                    QTreeWidgetItem* dirYLight = new QTreeWidgetItem(dirLight);
                    dirYLight->setText(0, "Y Dir : " + yDir);
                    //Light Dir Z
                    QTreeWidgetItem* dirZLight = new QTreeWidgetItem(dirLight);
                    dirZLight->setText(0, "Z Dir : " + zDir);
                }
            }

            lightWin->close();

            //Clean properties
            lightWin->nameLightEdit->setText("");
            lightWin->XEditPos->setText("0.0");
            lightWin->YEditPos->setText("0.0");
            lightWin->ZEditPos->setText("0.0");
            lightWin->XEditDir->setText("0.0");
            lightWin->YEditDir->setText("0.0");
            lightWin->ZEditDir->setText("0.0");
            diffuseLightColor.setRgba(qRgba(255, 255, 255, 255));
            specularLightColor.setRgba(qRgba(255, 255, 255, 255));
            lightWin->typeLightCombo->setCurrentIndex(0);
            lightWin->newTypeLight("Point");//update the layout to fit with the Point light (you can only edit the position and not the direction)
        }
        else
            QMessageBox::warning(this, "Change Light's Name", "Cannot set twice the same name to two different lights");
    }
    else
        QMessageBox::warning(this, "Light's Name Required", "Please set a name to the light");
}

