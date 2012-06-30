#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include <QFileDialog>

Settingsdialog::Settingsdialog(QWidget *parent, bool isCanvasVisible) :
    QDialog(parent),
    ui(new Ui::Settingsdialog)
{
    ui->setupUi(this);

    mSettingsFile = QApplication::applicationDirPath() + "editorSettings";
    mSettings = new QSettings(mSettingsFile, QSettings::NativeFormat);

    ui->resoursesPath->setText(mSettings->value("Editor/resourcesPath").toString());
    ui->configPath->setText(mSettings->value("Editor/configurationPath").toString());
    ui->pluginsPath->setText(mSettings->value("Editor/pluginsPath").toString());
    ui->ogreLogPath->setText(mSettings->value("Editor/ogreLogPath").toString());
    ui->morphLogPath->setText(mSettings->value("Editor/morphLogPath").toString());

    connect(ui->browseBtn, SIGNAL(clicked()), this, SLOT(browseDialog()));
    connect(ui->confBtn, SIGNAL(clicked()), this, SLOT(confDialog()));
    connect(ui->pluginsBtn, SIGNAL(clicked()), this, SLOT(pluginsDialog()));
    connect(ui->ogreBtn, SIGNAL(clicked()), this, SLOT(ogreLogDialog()));
    connect(ui->morphBtn, SIGNAL(clicked()), this, SLOT(morphLogDialog()));

    connect(ui->resoursesPath, SIGNAL(textChanged(QString)), this, SLOT(setResourcesPath(QString)));
    connect(ui->configPath, SIGNAL(textChanged(QString)), this, SLOT(setConfigPath(QString)));
    connect(ui->pluginsPath, SIGNAL(textChanged(QString)), this, SLOT(setPluginsPath(QString)));
    connect(ui->ogreLogPath, SIGNAL(textChanged(QString)), this, SLOT(setOgreLogPath(QString)));
    connect(ui->morphLogPath, SIGNAL(textChanged(QString)), this, SLOT(setMorphLogPath(QString)));
    connect(ui->buttonsBox->button(QDialogButtonBox::Ok), SIGNAL(clicked()), this, SLOT(clicked()));

    if(isCanvasVisible)
    {
        ui->renderLayer->addItem("Back");
        ui->renderLayer->addItem("Front");

        mSize = mSettings->value("Grid/gridPrespectiveSize").toInt();
        ui->mPerspSize->setValue(mSize);

        mDivisions = mSettings->value("Grid/gridDivisions").toInt();
        ui->mGridSpacingMenu->setValue(mDivisions);

        mIndex = mSettings->value("Grid/gridRenderLayer").toInt();
        ui->renderLayer->setCurrentIndex(mIndex);

        mValue = mSettings->value("Grid/gridRenderScale").toBool();
        ui->renderScale->setChecked(mValue);

        mColor = mSettings->value("Grid/gridColor").toString();

        connect(ui->modify, SIGNAL(clicked()), this, SLOT(gridColorChanged()));
        connect(ui->mGridSpacingMenu, SIGNAL(valueChanged(int)), this, SLOT(gridDivisionsChanged(int)));
        connect(ui->mPerspSize, SIGNAL(valueChanged(int)), this, SLOT(gridPrespectiveSizeChanged(int)));
        connect(ui->renderLayer, SIGNAL(currentIndexChanged(int)), this, SLOT(gridRenderLayerChanged(int)));
        connect(ui->renderScale, SIGNAL(clicked(bool)), this, SLOT(gridRenderScaleChanged(bool)));
    }
    else
    {
        ui->notVisible->setText("You can not change this settings unless you open the canvas");
        //ui->buttonsBox->setEnabled(false);
    }
}

Settingsdialog::~Settingsdialog()
{
    delete ui;
}

void Settingsdialog::browseDialog()
{
    QString file = QFileDialog::getOpenFileName(this, "Please set the resource path");
    ui->resoursesPath->setText(file);
}

void Settingsdialog::confDialog()
{
    QString file = QFileDialog::getOpenFileName(this, "Please set the configuration path");
    ui->configPath->setText(file);
}

void Settingsdialog::pluginsDialog()
{
    QString file = QFileDialog::getOpenFileName(this, "Please set the plugins path");
    ui->pluginsPath->setText(file);
}

void Settingsdialog::ogreLogDialog()
{
    QString file = QFileDialog::getOpenFileName(this, "Please set the Ogre log path");
    ui->ogreLogPath->setText(file);
}

void Settingsdialog::morphLogDialog()
{
    QString file = QFileDialog::getOpenFileName(this, "Please set the Morph Editor log path");
    ui->morphLogPath->setText(file);
}

void Settingsdialog::setResourcesPath(QString string)
{
   // Q_UNUSED(string)
    mSettings->setValue("Editor/resourcesPath", string);
}

void Settingsdialog::setConfigPath(QString string)
{
    Q_UNUSED(string)
    mSettings->setValue("Editor/configurationPath", ui->configPath->text());
}

void Settingsdialog::setPluginsPath(QString string)
{
    Q_UNUSED(string)
    mSettings->setValue("Editor/pluginsPath", ui->pluginsPath->text());
}

void Settingsdialog::setOgreLogPath(QString string)
{
    Q_UNUSED(string)
    mSettings->setValue("Editor/ogreLogPath", ui->ogreLogPath->text());
}

void Settingsdialog::setMorphLogPath(QString string)
{
    Q_UNUSED(string)
    mSettings->setValue("Editor/morphLogPath", ui->morphLogPath->text());
}

void Settingsdialog::clicked()
{
    emit signalGridDivisionsChanged(mDivisions);
    emit signalGridColorChanged(mColor);
    emit signalGridPrespectiveSizeChanged(mSize);
    emit signalGridRenderLayerChanged(mIndex);
    emit signalGridRenderScaleChanged(mValue);
}

void Settingsdialog::gridDivisionsChanged(int size)
{
    mSettings->setValue("Grid/gridDivisions", size);
    mDivisions = size;
}

void Settingsdialog::gridColorChanged()
{
    QColor color = QColorDialog::getColor(QColor(mSettings->value("gridColor").toString()));
    mSettings->setValue("Grid/gridColor", color.name());
    mColor = color;
}

void Settingsdialog::gridPrespectiveSizeChanged(int size)
{
    mSettings->setValue("Grid/gridPrespectiveSize", size);
    mSize = size;
}

void Settingsdialog::gridRenderLayerChanged(int index)
{
    mSettings->setValue("Grid/gridRenderLayer", index);
    mIndex = index;
}

void Settingsdialog::gridRenderScaleChanged(bool value)
{
    mSettings->setValue("Grid/gridRenderScale", value);
    mValue = value;
}
