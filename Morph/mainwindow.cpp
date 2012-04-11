#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "MorphCore/Editor/MLogManager.h"
#include <QMessageBox>

using namespace Morph;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Pointer to the MSystemManager.
    systemManager = ui->widget;

    ui->listWidget->addItem(new QListWidgetItem(QIcon("settings.png"), "Toggle Button"));
    ui->listWidget->addItem(new QListWidgetItem(QIcon("check.png"), "Check Button"));
    ui->listWidget->addItem(new QListWidgetItem(QIcon("calculator.png"), "Radio Button"));

    MLogManager::getSingleton().addListener(ui->textBrowser);
    MLogManager::getSingleton().addListener(ui->textBrowser_2);

    // Connect actions to slots.
    connect(ui->actionFakeError, SIGNAL(triggered()), this, SLOT(fakeSlot()));
    connect(ui->actionAbout_Morph, SIGNAL(triggered()), this, SLOT(about()));
    connect(ui->actionConfigure_Editor, SIGNAL(triggered()), this, SLOT(openSettingsdialog()));
    connect(ui->actionAdd_Ogre_Mesh, SIGNAL(triggered()), this, SLOT(addObj()));
    connect(ui->actionSet_Background_Color, SIGNAL(triggered()), this, SLOT(setBackgroundColor()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fakeSlot()
{
    MLogManager::getSingleton().logOutput("Fake Error!", M_ERROR, true);
}

void MainWindow::about()
{
    QString ogreVersion = QString::number(OGRE_VERSION_MAJOR) + "." + QString::number(OGRE_VERSION_MINOR) + "." + QString::number(OGRE_VERSION_PATCH);
    QMessageBox::about(this, tr("About Morph SDK"),
                       tr("Morph SDK %1\n").arg("1.0") +
                       tr("Copyright (C) 2012 Zeology\n\n") +
                       tr("Licensed under the LGPL\n") +
                       tr("Using Ogre %1 and Qt %2\n\n").arg(ogreVersion).arg(qVersion()) +
                       tr("Developers:\n") +
                       tr("ISlam Wazery <wazery@ubuntu.com>\n") +
                       tr("Mohammed Yosry <mohammedyosry3000@gmail.com>") +
                       tr("Ibrahim Hamdy <mohammedyosry3000@gmail.com>") +
                       tr("Ahmed Adel    <mohammedyosry3000@gmail.com>"));
}

void MainWindow::openSettingsdialog()
{
    settingsdialog = new Settingsdialog();
    settingsdialog->show();
}

void MainWindow::addObj()
{
    QString meshName = QFileDialog::getOpenFileName(this, "Add a model", QDir::currentPath() + "/Media/models", "Mesh (*.mesh)");
    loadObj(meshName);
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
//		objProperties->updateListAnim(ogreView->mainEnt->getAllAnimationStates());

//		if(objProperties->listAnimCombo->itemText(0) != "") { // The mesh has animations
//			ogreView->setAnimationState(objProperties->listAnimCombo->itemText(0).toStdString());
//			objProperties->playCheckBox->setChecked(false);
//			objProperties->loopCheckBox->setChecked(false);
//			showmeshLog->insertPlainText("Has Animations : YES \n");
//		}
//		else
//			showmeshLog->insertPlainText("Has Animations : NO \n");

//		showmeshLog->insertPlainText("========================= \n"); // End of the log
    }
}

void MainWindow::setBackgroundColor()
{
    QColor color = QColorDialog::getColor(systemManager->getBackgroundColor(), this);

    if(color.isValid())
    {
        systemManager->setBackgroundColor(color);
        MLogManager::getSingleton().logOutput("Background Color : " + color.name() + '\n');
    }
}


