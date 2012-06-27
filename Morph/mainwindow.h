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
#include "mOgreEntityViewer/matwindow.h"
#include "mOgreEntityViewer/envproperties.h"
#include "mOgreEntityViewer/objproperties.h"
#include "mOgreEntityViewer/startingwindow.h"

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
    void openQuickStart();

    // Settings dialog slots.
    void openSettingsDialog();
    void changeIndexofCanvas(int value);
    void startEngineLoading();
    void updateProgress();

    void setFourViewPorts();
    void setOneViewPort();
    void setViewPortToWireframe();
    void setViewPortToPoints();
    void setViewPortToPolygons();

    void gridDivisionsChanged(int value);
    void gridPrespectiveSizeChanged(int size);
    void gridRenderLayerChanged(int index);
    void gridColorChanged(QColor color);
    void gridRenderScaleChanged(bool value);

    void addObj();
    void loadObj(const QString &meshName);
    void showRemoveObj();
    void commitRemoveObj();
    void removeSelected();
    void saveAs();
    void openScene();

    void setBackgroundColor();
    void gridChanged(bool value);

    void addLight();
    void modifyLight();
    void deleteLight();
    void createNewLight();
    void setDiffuseLightColor();
    void setSpecularLightColor();
    void setAmbientLight();

    void setScriptPath();
    void setTexturePath();

    void getObjName(bool value);
    void setRenderDetail(int index);
    void setObjBoundingBoxes(bool value);
    void enableObjProperties(bool value);
    void setPostions(bool value);
    void setScales(bool value);
    void setobjSkeleton(bool value);

    void setObjectPosX(int value);
    void setObjectPosY(int value);
    void setObjectPosZ(int value);

    void setObjectRotX(int value);
    void setObjectRotY(int value);
    void setObjectRotZ(int value);

    void setObjectScaleX(int value);
    void setObjectScaleY(int value);
    void setObjectScaleZ(int value);

    void setMaterial();
    void updateMaterial();
    void setAnimation(QString name);
    void setAnimLoop(int enable);
    void setAnimEnabled(int enable);

    void setFog(int fogType);
    void setFogColor();

    void setShadow(int fogType);

    void addNodeListener();
    void initialisePlugins();

    void zoomValueChanged(int value);

    void aboutQt();
    void restoreDefault();

    void selectObject();
    void moveObject();
    void translateObject();
    void rotateObject();

private:
    Ui::MainWindow *ui;
    QSettings *mSettings;
    QString mSettingsFile;

    Settingsdialog *settingsdialog;
    AboutDialog    *aboutdialog;

    QTabWidget     *propertiesTab;

    MSystemManager *systemManager;
    MLogManager    *logManager;
    LightWindow    *lightWin;
    MatWindow      *matWin;
    StartingWindow *startingWindow;

    EnvProperties* envProperties;//Class EnvProperties.h
    ObjProperties* objProperties;

    QColor diffuseLightColor;
    QColor specularLightColor;

    QList<QString> listName;
};

#endif // MAINWINDOW_H
