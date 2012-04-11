#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "settingsdialog.h"
#include "Ogre.h"

#include "MorphCore/Editor/msystemmanager.h"
#include "MorphCore/Editor/mlogmanager.h"
#include "lightwindow.h"
#include "envproperties.h"

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
    void about();
    void openSettingsdialog();
    void addObj();
    void loadObj(const QString &meshName);
    void setBackgroundColor();
    void addLight();
    void modifyLight();
    void deleteLight();
    void createNewLight();
    void setDiffuseLightColor();
    void setSpecularLightColor();
    void fakeSlot();

private:
    Ui::MainWindow *ui;
    QSettings *settings;
    QString mSettingsFile;
    Settingsdialog *settingsdialog;
    MSystemManager *systemManager;
    MLogManager    *logManager; // FIXME
    LightWindow    *lightWin;

    EnvProperties* envProperties;//Class EnvProperties.h

    QColor diffuseLightColor;
    QColor specularLightColor;

    QList<QString> listName;
};

#endif // MAINWINDOW_H
