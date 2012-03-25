#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "MorphCore/Editor/MLogManager.h"

using namespace Morph;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->listWidget->addItem(new QListWidgetItem(QIcon("settings.png"), "Toggle Button"));
    ui->listWidget->addItem(new QListWidgetItem(QIcon("check.png"), "Check Button"));
    ui->listWidget->addItem(new QListWidgetItem(QIcon("calculator.png"), "Radio Button"));

    MLogManager::getSingleton().addListener(ui->textBrowser);

    connect(ui->actionFakeError, SIGNAL(triggered()), this, SLOT(fakeSlot()));
    connect(ui->actionAbout_Morph, SIGNAL(triggered()), this, SLOT(about()));
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

MainWindow::~MainWindow()
{
    delete ui;
}
