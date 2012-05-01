#include "settingsdialog.h"
#include "ui_settingsdialog.h"

Settingsdialog::Settingsdialog(QWidget *parent, bool isCanvasVisible) :
    QDialog(parent),
    ui(new Ui::Settingsdialog)
{
    ui->setupUi(this);

    mSettingsFile = QApplication::applicationDirPath() + "editorSettings";
    mSettings = new QSettings(mSettingsFile, QSettings::NativeFormat);

    if(isCanvasVisible)
    {
        ui->mPerspSize->setValue(mSettings->value("gridPrespectiveSize").toInt());
        ui->mGridSpacingMenu->setValue(mSettings->value("gridDivisions").toInt());
        ui->renderLayer->addItem("Back");
        ui->renderLayer->addItem("In front");
        ui->renderLayer->setCurrentIndex(mSettings->value("gridRenderLayer").toInt());

        connect(ui->modify, SIGNAL(clicked()), this, SLOT(gridColorChanged()));
        connect(ui->mGridSpacingMenu, SIGNAL(valueChanged(int)), this, SLOT(gridDivisionsChanged(int)));
        connect(ui->mPerspSize, SIGNAL(valueChanged(int)), this, SLOT(gridPrespectiveSizeChanged(int)));
        connect(ui->renderLayer, SIGNAL(currentIndexChanged(int)), this, SLOT(gridRenderLayerChanged(int)));

    }
    else
    {
        ui->notVisible->setText("You can not change this settings unless you open the canvas");
        ui->cancel->setEnabled(false);
    }
}

Settingsdialog::~Settingsdialog()
{
    delete ui;
}

void Settingsdialog::gridDivisionsChanged(int size)
{
    mSettings->setValue("gridDivisions", size);
    emit signalGridDivisionsChanged(size);
}

void Settingsdialog::gridColorChanged()
{
    QColor color = QColorDialog::getColor(QColor(mSettings->value("gridColor").toString()));
    mSettings->setValue("gridColor", color.name());
    emit signalGridColorChanged(color);
}

void Settingsdialog::gridPrespectiveSizeChanged(int size)
{
    mSettings->setValue("gridPrespectiveSize", size);
    emit signalGridPrespectiveSizeChanged(size);
}

void Settingsdialog::gridRenderLayerChanged(int index)
{
    mSettings->setValue("gridRenderLayer", index);
    emit signalGridRenderLayerChanged(index);
}
