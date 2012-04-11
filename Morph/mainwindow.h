#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "settingsdialog.h"
#include "Ogre.h"

#include "MorphCore/Editor/msystemmanager.h"

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

public slots:
    void about();
    void openSettingsdialog();
    void addObj();
    void loadObj(const QString &meshName);
    void fakeSlot();

private:
    Ui::MainWindow *ui;
    Settingsdialog *settingsdialog;
    MSystemManager *systemManager;
};

#endif // MAINWINDOW_H
