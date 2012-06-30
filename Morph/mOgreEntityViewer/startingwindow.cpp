#include <QDesktopServices>
#include <QUrl>
#include "startingwindow.h"
#include "ui_startingwindow.h"

StartingWindow::StartingWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartingWindow),
    mSettingsFile(""),
    mSettings(NULL)
{
    ui->setupUi(this);

    mSettingsFile = QApplication::applicationDirPath() + "editorSettings";
    mSettings = new QSettings(mSettingsFile, QSettings::NativeFormat);

    ui->textEdit->setFont(QFont("ubuntu"));
    ui->showAgain->setChecked(mSettings->value("StartingWindow/startingWindow").toBool());

    connect(ui->showAgain, SIGNAL(clicked(bool)), this, SLOT(setShowAgain(bool)));
    connect(ui->toolButton, SIGNAL(clicked()), this, SLOT(openEditorGuide()));
}

StartingWindow::~StartingWindow()
{
    delete ui;
}

void StartingWindow::setShowAgain(bool value)
{
    mSettings->setValue("StartingWindow/startingWindow", value);
}

void StartingWindow::openEditorGuide()
{
    QUrl url;
    url.setUrl("file:///home/wazery/source-codes/Morph-SDK/Desktop/Turn%20Off%20the%20Lights%20-%20Chrome%20Extension.htm");
    QDesktopServices::openUrl(url);
}
