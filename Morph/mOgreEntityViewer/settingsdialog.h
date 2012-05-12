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
    void clicked();
    void gridDivisionsChanged(int size);
    void gridColorChanged();
    void gridPrespectiveSizeChanged(int size);
    void gridRenderLayerChanged(int index);
    void gridRenderScaleChanged(bool value);
    
signals:
   void signalGridDivisionsChanged(int size);
   void signalGridPrespectiveSizeChanged(int size);
   void signalGridColorChanged(QColor color);
   void signalGridRenderLayerChanged(int index);
   void signalGridRenderScaleChanged(bool value);

private:
    Ui::Settingsdialog *ui;

    QSettings *mSettings;
    QString mSettingsFile;

    int mDivisions;
    QColor mColor;
    int mSize;
    int mIndex;
    bool mValue;
};

#endif // Settingsdialog_H
