#ifndef REMOVEOBJECT_H
#define REMOVEOBJECT_H

#include <QDialog>

namespace Ui {
class RemoveObject;
}

class RemoveObject : public QDialog
{
    Q_OBJECT
    
public:
    explicit RemoveObject(QWidget *parent = 0);
    ~RemoveObject();

    QString getMeshName(QWidget *parent = 0, const QString &caption = QString());
    
private:
    Ui::RemoveObject *ui;
};

#endif // REMOVEOBJECT_H
