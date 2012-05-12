#ifndef STARTINGWINDOW_H
#define STARTINGWINDOW_H

#include <QDialog>
#include <QSettings>

namespace Ui {
class StartingWindow;
}

class StartingWindow : public QDialog
{
    Q_OBJECT
    
public:
    explicit StartingWindow(QWidget *parent = 0);
    ~StartingWindow();

public slots:
    void setShowAgain(bool value);
    
private:
    Ui::StartingWindow *ui;
    QSettings *mSettings;
    QString mSettingsFile;
};

#endif // STARTINGWINDOW_H
