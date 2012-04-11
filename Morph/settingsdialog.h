#ifndef Settingsdialog_H
#define Settingsdialog_H

#include <QDialog>

namespace Ui
{
class Settingsdialog;
}

class Settingsdialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit Settingsdialog(QWidget *parent = 0);
    ~Settingsdialog();
    
private:
    Ui::Settingsdialog *ui;
};

#endif // Settingsdialog_H
