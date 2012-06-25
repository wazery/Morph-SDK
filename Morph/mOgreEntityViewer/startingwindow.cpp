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
}

StartingWindow::~StartingWindow()
{
    delete ui;
}

void StartingWindow::setShowAgain(bool value)
{
    mSettings->setValue("StartingWindow/startingWindow", value);
}
