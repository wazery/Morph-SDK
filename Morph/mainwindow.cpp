#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

using namespace Morph;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mSettingsFile = QApplication::applicationDirPath() + "editorSettings";
    mSettings = new QSettings(mSettingsFile, QSettings::NativeFormat);

    // Pointers to the editor subsystems.
    systemManager = ui->widget;
    lightWin = new LightWindow(this);

    loadSettings();

    envProperties = new EnvProperties(this);
    QTabWidget *propertiesTab = ui->tabWidget_3;
    propertiesTab->addTab(envProperties, QIcon("settings.png"), ("Environment"));
    // TODO: Create the object properties tab
    //propertiesTab->addTab(objProperties, QIcon("settings.png"), ("Object Properties"));
    //propertiesTab->setMaximumSize(243, 450);

    ui->listWidget->addItem(new QListWidgetItem(QIcon("settings.png"), "Toggle Button"));
    ui->listWidget->addItem(new QListWidgetItem(QIcon("check.png"), "Check Button"));
    ui->listWidget->addItem(new QListWidgetItem(QIcon("calculator.png"), "Radio Button"));

    MLogManager::getSingleton().addListener(ui->textBrowser);
    MLogManager::getSingleton().addListener(ui->textBrowser_2);

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(changeIndexofCanvas()));

    // TODO: add listeners for the subsystems.
    //MNodeManager::getSingleton().addSelectListener(&m_wndProperties);
    //MNodeManager::getSingleton().addAttributeListener(&m_wndProperties);
    //MCommandManager::getSingleton().addCommandListener(this);

    // Connect actions to slots.
    connect(ui->actionFakeError, SIGNAL(triggered()), this, SLOT(fakeSlot()));
    connect(ui->actionAbout_Morph, SIGNAL(triggered()), this, SLOT(openAboutDialog()));

    connect(ui->actionConfigure_Editor, SIGNAL(triggered()), this, SLOT(openSettingsDialog()));
    connect(ui->actionAdd_Ogre_Mesh, SIGNAL(triggered()), this, SLOT(addObj()));
    connect(ui->actionSet_Background_Color, SIGNAL(triggered()), this, SLOT(setBackgroundColor()));
    connect(ui->action_Add_Light, SIGNAL(triggered()), this, SLOT(addLight()));

    // FIXME: A hack on signls and slots, bad way.
    //connect(ui->actionRemoveMesh, SIGNAL(triggered()), this, SLOT(emitRemoveObj()));
    //connect(this, SIGNAL(signalRemoveObject(QString)), this, SLOT(removeObj(QString)));

    // Environment Properties
    connect(envProperties->fogTypeCombo, SIGNAL(activated(int)), this, SLOT(setFog(int)));
    connect(envProperties->fogColorBtn, SIGNAL(clicked()), this, SLOT(setFogColor()));
    connect(envProperties->shadowTypeCombo, SIGNAL(activated(int)), this, SLOT(setShadow(int)));
    connect(envProperties->backgroundColorBtn, SIGNAL(clicked()), this, SLOT(setBackgroundColor()));
    connect(envProperties->ambientLightColorBtn, SIGNAL(clicked()), this, SLOT(setAmbientLight()));
    connect(envProperties->modifyAction, SIGNAL(triggered()), this, SLOT(modifyLight()));
    connect(envProperties->removeAction, SIGNAL(triggered()), this, SLOT(deleteLight()));

    connect(lightWin->diffuseColorLightBtn, SIGNAL(clicked()), this, SLOT(setDiffuseLightColor()));
    connect(lightWin->specularColorLightBtn, SIGNAL(clicked()), this, SLOT(setSpecularLightColor()));
    connect(lightWin->okBtn, SIGNAL(clicked()), this, SLOT(createNewLight()));

    connect(ui->grid, SIGNAL(clicked()), this, SLOT(gridChanged()));
    connect(ui->zoomSlider, SIGNAL(valueChanged(int)), ui->zommSpinBox, SLOT(setValue(int)));
    connect(ui->zommSpinBox, SIGNAL(valueChanged(int)), ui->zoomSlider, SLOT(setValue(int)));

    // --------------------------------------
    //            Initialise Engine
    // --------------------------------------
    connect(systemManager, SIGNAL(initialised()), this, SLOT(addNodeListener()));
    connect(systemManager, SIGNAL(initialised()), this, SLOT(initialisePlugins()));

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
    qDebug() << "2) widget initialised";
    MNodeManager::getSingleton().addNodeTreeListener(ui->treeView);
}

void MainWindow::initialisePlugins()
{
    MNodeManager::getSingleton().registerNode(MRootNode::nodeID, MRootNode::creator);

    // firstly create the root.
    MNodePtr rootNodePtr = MNodeManager::getSingleton().createNode(MRootNode::nodeID, MRootNode::nodeID);
    if(!rootNodePtr)
    {
        MLogManager::getSingleton().logOutput("Error failed in initilaizePlugin(), setting the root node", M_ERROR);
        return;
    }
    MNodeManager::getSingleton().setRootNodePtr(rootNodePtr);
    MNodeManager::getSingleton().notifyAddNode("World.", rootNodePtr->getName());

    // Enable Canvas Buttons
    ui->grid->setEnabled(true);
    ui->zommSpinBox->setEnabled(true);
    ui->zoomSlider->setEnabled(true);
    ui->oneView->setEnabled(true);
    ui->fourViews->setEnabled(true);
    ui->wireframe->setEnabled(true);
    ui->points->setEnabled(true);
    ui->polygons->setEnabled(true);

    // Init Grid.
//    for(int i = 0; i < systemManager->mGridList.count(); i++)
//    {
//        systemManager->mGridList[i]->setEnabled(ui->grid->isChecked());
//    }
//    Ogre::ColourValue ogreColor;
//    ogreColor.setAsARGB(QColor(mSettings->value("gridColor").toString()).rgba());
//    systemManager->mGrid->setColour(ogreColor);
//    systemManager->mGrid->setPerspectiveSize(mSettings->value("gridPrespectiveSize").toInt());
//    if(mSettings->value("gridRenderLayer").toInt() == 0)
//        systemManager->mGrid->setRenderLayer(ViewportGrid::RL_BEHIND);
//    else
//        systemManager->mGrid->setRenderLayer(ViewportGrid::RL_INFRONT);
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
    ui->polygons->setEnabled(false);
}

void MainWindow::loadSettings()
{
    // Set background color to the last saved setting.
    QColor color(mSettings->value("Canvas Background Color").toString());
    if (color.isValid())
    {
        // FIXME, need to set the viewport color with the saved settings color.
        systemManager->setBackgroundColor(color);
    }

    //TODO: check if the grid is enabled if(systemManager->mGridList)
    //Set grid checkbox
    ui->grid->setChecked(mSettings->value("grid").toBool());
}

void MainWindow::saveSettings()
{
}

void MainWindow::fakeSlot()
{
    MLogManager::getSingleton().logOutput("Fake Error!", M_ERROR, true);
}

void MainWindow::openAboutDialog()
{
    aboutdialog = new AboutDialog();
    aboutdialog->show();
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
    settingsdialog->show();
}

void MainWindow::changeIndexofCanvas()
{
    ui->tabWidget->setCurrentIndex(1);
    setOneViewPort();
}

void MainWindow::gridColorChanged(QColor color)
{
    Ogre::ColourValue ogreColor;
    ogreColor.setAsARGB(color.rgba());
    //systemManager->mGrid->setColour(ogreColor);
}

void MainWindow::gridDivisionsChanged(int value)
{
    //systemManager->mGrid->setDivision(value);
}

void MainWindow::gridPrespectiveSizeChanged(int size)
{
    //systemManager->mGrid->setPerspectiveSize(size);
}

void MainWindow::gridRenderLayerChanged(int index)
{
//    if(index == 0)
//        systemManager->mGrid->setRenderLayer(ViewportGrid::RL_BEHIND);
//    else
//        systemManager->mGrid->setRenderLayer(ViewportGrid::RL_INFRONT);
}

void MainWindow::addObj()
{
    if(systemManager->isVisible())
    {
        QString meshName = QFileDialog::getOpenFileName(this, "Add a model", QDir::currentPath() + "/Media/models", "Mesh (*.mesh)");
        loadObj(meshName);
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
//		objProperties->renderDetailCombo->setCurrentIndex(0);
//		objProperties->boundBoxCheckBox->setChecked(false);
//		objProperties->dispSkeletonCheckBox->setChecked(false);
//		objProperties->lodSlider->setSliderPosition(objProperties->lodSlider->maximum()/2);
//		objProperties->listAnimCombo->clear();
//		objProperties->updateListAnim(systemManager->mainEnt->getAllAnimationStates());

//		if(objProperties->listAnimCombo->itemText(0) != "") { // The mesh has animations
//			systemManager->setAnimationState(objProperties->listAnimCombo->itemText(0).toStdString());
//			objProperties->playCheckBox->setChecked(false);
//			objProperties->loopCheckBox->setChecked(false);
//			MLogManager::getSingleton().logOutput("Has Animations : YES", M_EDITOR_MESSAGE);
//		}
//		else
//			MLogManager::getSingleton().logOutput("Has Animations : NO", M_EDITOR_MESSAGE);

//		MLogManager::getSingleton().logOutput("=========================", M_EDITOR_MESSAGE); // End of the log
    }
}

// TODO:
void MainWindow::removeObj(const QString &meshName)
{
    RemoveObject* removeObject = new RemoveObject();
    removeObject->show();
//    systemManager->removeObject();
}

void MainWindow::setBackgroundColor()
{
    if(systemManager->isVisible())
    {
        QColor color = QColorDialog::getColor(systemManager->getBackgroundColor(), this);

        if(color.isValid())
        {
            systemManager->setBackgroundColor(color);
            MLogManager::getSingleton().logOutput("Background Color : " + color.name(), M_EDITOR_MESSAGE);
        }

        mSettings->setValue("canvasBackgroundColor", color.name());
        mSettings->sync();
    }
    else
        QMessageBox::warning(this, "You must open the canvas first!", "You are trying to make an action that couldn't be done without launching the canvas first!");
}

void MainWindow::gridChanged()
{
    mSettings->setValue("grid", ui->grid->isChecked());
    mSettings->sync();

    //systemManager->mGrid->setEnabled(ui->grid->isChecked());
    if(ui->grid->isChecked())
        MLogManager::getSingleton().logOutput("Grid set to on", M_EDITOR_MESSAGE);
    else
        MLogManager::getSingleton().logOutput("Grid set to off", M_EDITOR_MESSAGE);

    systemManager->update();
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
//        QString ambientColor = envProperties->lightsTree->currentItem()->child(3)->text(0);
//        ambientColor = ambientColor.remove()
    }
}

void MainWindow::setFog(int)
{
}

void MainWindow::setFogColor()
{
}

void MainWindow::setShadow()
{
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

