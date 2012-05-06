#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "mOgreEntityViewer/settingsdialog.h"
#include "mOgreEntityViewer/aboutdialog.h"
#include "mOgreEntityViewer/removeobject.h"
#include "Ogre.h"

#include "MorphCore/Editor/msystemmanager.h"
#include "MorphCore/Editor/mlogmanager.h"
#include "mOgreEntityViewer/lightwindow.h"
#include "mOgreEntityViewer/envproperties.h"

using namespace Morph;
namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void loadSettings();
    void saveSettings();

public slots:
    void openAboutDialog();

    // Settings dialog slots.
    void openSettingsDialog();
    void changeIndexofCanvas();

    void setFourViewPorts();
    void setOneViewPort();
    void setViewPortToWireframe();
    void setViewPortToPoints();
    void setViewPortToPolygons();

    void gridDivisionsChanged(int value);
    void gridPrespectiveSizeChanged(int size);
    void gridRenderLayerChanged(int index);
    void gridColorChanged(QColor color);

    void addObj();
    void loadObj(const QString &meshName);
    void removeObj(const QString &meshName);

    void setBackgroundColor();
    void gridChanged();

    void addLight();
    void modifyLight();
    void deleteLight();
    void createNewLight();
    void setDiffuseLightColor();
    void setSpecularLightColor();
    void setAmbientLight();

    void setFog(int);
    void setFogColor();

    void setShadow();
    void fakeSlot();

    void addNodeListener();
    void initialisePlugins();

private:
    Ui::MainWindow *ui;
    QSettings *mSettings;
    QString mSettingsFile;

    Settingsdialog *settingsdialog;
    AboutDialog    *aboutdialog;

    MSystemManager *systemManager;
    MLogManager    *logManager; // FIXME
    LightWindow    *lightWin;

    EnvProperties* envProperties;//Class EnvProperties.h

    QColor diffuseLightColor;
    QColor specularLightColor;

    QList<QString> listName;
};

#endif // MAINWINDOW_H
