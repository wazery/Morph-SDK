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
        connect(ui->buttonsBox->button(QDialogButtonBox::Ok), SIGNAL(clicked()), this, SLOT(clicked()));
    }
    else
    {
        ui->notVisible->setText("You can not change this settings unless you open the canvas");
        ui->buttonsBox->setEnabled(false);
    }
}

Settingsdialog::~Settingsdialog()
{
    delete ui;
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
