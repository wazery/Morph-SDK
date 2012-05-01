#ifndef Settingsdialog_H
#define Settingsdialog_H

#include <QDialog>
#include <QColorDialog>
#include <QSettings>

namespace Ui
{
class Settingsdialog;
}

class Settingsdialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit Settingsdialog(QWidget *parent = 0, bool isCanvasVisible = false);
    ~Settingsdialog();

public slots:
    void gridDivisionsChanged(int size);
    void gridColorChanged();
    void gridPrespectiveSizeChanged(int size);
    void gridRenderLayerChanged(int index);
    
signals:
   void signalGridDivisionsChanged(int size);
   void signalGridPrespectiveSizeChanged(int size);
   void signalGridColorChanged(QColor color);
   void signalGridRenderLayerChanged(int index);

private:
    Ui::Settingsdialog *ui;

    QSettings *mSettings;
    QString mSettingsFile;
};

#endif // Settingsdialog_H
