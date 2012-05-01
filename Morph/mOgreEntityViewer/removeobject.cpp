#include "removeobject.h"
#include "ui_removeobject.h"

RemoveObject::RemoveObject(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RemoveObject)
{
    ui->setupUi(this);
}

RemoveObject::~RemoveObject()
{
    delete ui;
}

QString getMeshName(QWidget *parent, const QString &caption)
{
//    ui->setupUi(this);
//    ui
}
