#include "removeobject.h"
#include "ui_removeobject.h"
#include <QPushButton>

RemoveObject::RemoveObject(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RemoveObject)
{
    ui->setupUi(this);
    connect(ui->textEdit, SIGNAL(textChanged()), this, SLOT(setText()));
    connect(ui->buttonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked()), this, SLOT(Clicked()));
    connect(this, SIGNAL(clicked()), parent, SLOT(commitRemoveObj()));
}

void RemoveObject::showEvent(QShowEvent *)
{
    if(!initialized)
    {
        initialized = true;
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
}

RemoveObject::~RemoveObject()
{
    delete ui;
}

void RemoveObject::Clicked()
{
    emit clicked();
}

void RemoveObject::setText()
{
    mMeshName = ui->textEdit->toPlainText();
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
}
