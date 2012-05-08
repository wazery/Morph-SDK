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

    void showEvent(QShowEvent *);

    QString getMeshName() { return mMeshName; }

public slots:
    void setText();
    void Clicked();

signals:
    void clicked();
    
private:
    Ui::RemoveObject *ui;
    QString mMeshName;
    bool initialized;
};

#endif // REMOVEOBJECT_H
