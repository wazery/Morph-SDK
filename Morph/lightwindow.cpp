#include "lightwindow.h"

LightWindow::LightWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle(tr("New Light"));
    setWindowFlags(Qt::Dialog);
    setMinimumSize(QSize(211, 313));
    setMaximumSize(QSize(211, 418));

    //Light Main Properties (name, color, type)
    groupLight = new QGroupBox(tr("Light Properties"));

    nameLight = new QLabel(tr("Name :"));
    nameLightEdit = new QLineEdit;

    diffuseColorLight = new QLabel(tr("Diffuse Color :"));
    diffuseColorLightBtn = new QPushButton(tr("Modify"));

    specularColorLight = new QLabel(tr("Specular Color :"));
    specularColorLightBtn = new QPushButton(tr("Modify"));

    typeLight = new QLabel(tr("Type :"));
    typeLightCombo = new QComboBox;
    typeLightCombo->addItem(tr("Point"));
    typeLightCombo->addItem(tr("Directional"));
    typeLightCombo->addItem(tr("Spotlight"));
    connect(typeLightCombo, SIGNAL(activated(QString)), this, SLOT(newTypeLight(QString)));

    mainPropertieslayout = new QGridLayout;

    mainPropertieslayout->addWidget(nameLight, 0, 0);
    mainPropertieslayout->addWidget(nameLightEdit, 0, 1);

    mainPropertieslayout->addWidget(diffuseColorLight, 1, 0);
    mainPropertieslayout->addWidget(diffuseColorLightBtn, 1, 1);
    mainPropertieslayout->addWidget(specularColorLight, 2, 0);
    mainPropertieslayout->addWidget(specularColorLightBtn, 2, 1);

    mainPropertieslayout->addWidget(typeLight, 3, 0);
    mainPropertieslayout->addWidget(typeLightCombo, 3, 1);

    groupLight->setLayout(mainPropertieslayout);

    /////////////////////////////////////////////////////////////

    //Light Position
    groupPos = new QGroupBox(tr("Light Position (optional)"));

    XPos = new QLabel(tr("X Position :"));
    XEditPos = new QLineEdit(tr("0.0"));

    YPos = new QLabel(tr("Y Position :"));
    YEditPos = new QLineEdit(tr("0.0"));

    ZPos = new QLabel(tr("Z Position :"));
    ZEditPos = new QLineEdit(tr("0.0"));

    posLayout = new QGridLayout;

    posLayout->addWidget(XPos, 0, 0);
    posLayout->addWidget(XEditPos, 0, 1);

    posLayout->addWidget(YPos, 1, 0);
    posLayout->addWidget(YEditPos, 1, 1);

    posLayout->addWidget(ZPos, 2, 0);
    posLayout->addWidget(ZEditPos, 2, 1);

    groupPos->setLayout(posLayout);

    /////////////////////////////////////////////////////////////

    //Light Direction
    groupDir = new QGroupBox(tr("Light Direction (optional)"));

    XDir = new QLabel(tr("X Direction :"));
    XEditDir = new QLineEdit(tr("0.0"));

    YDir = new QLabel(tr("Y Direction :"));
    YEditDir = new QLineEdit(tr("0.0"));

    ZDir = new QLabel(tr("Z Direction :"));
    ZEditDir = new QLineEdit(tr("0.0"));

    dirLayout = new QGridLayout;

    dirLayout->addWidget(XDir, 0, 0);
    dirLayout->addWidget(XEditDir, 0, 1);

    dirLayout->addWidget(YDir, 1, 0);
    dirLayout->addWidget(YEditDir, 1, 1);

    dirLayout->addWidget(ZDir, 2, 0);
    dirLayout->addWidget(ZEditDir, 2, 1);

    groupDir->setLayout(dirLayout);

    /////////////////////////////////////////////////////////////

    //Buttons
    groupBtn = new QGroupBox;
    groupBtn->setFlat(true);

    okBtn = new QPushButton(tr("&Ok"));
    cancelBtn = new QPushButton(tr("&Cancel"));
    connect(cancelBtn, SIGNAL(clicked()), this, SLOT(close()));

    btnLayout = new QGridLayout;

    btnLayout->addWidget(okBtn, 0, 0);
    btnLayout->addWidget(cancelBtn, 0, 1);

    groupBtn->setLayout(btnLayout);
    /////////////////////////////////////////////////////////////

    lightLayout = new QGridLayout;

    lightLayout->addWidget(groupLight, 0, 0);
    lightLayout->addWidget(groupPos, 1, 0);
    lightLayout->addWidget(groupBtn, 2, 0);

    setLayout(lightLayout);
}

void LightWindow::newTypeLight(QString type)
{
    if(type == "Point"){
        resize(211, 313);
        //Hide Direction Properties
        groupDir->hide();
        lightLayout->removeWidget(groupDir);
        //Show Position Properties
        lightLayout->addWidget(groupPos, 1, 0);
        if(groupPos->isHidden())
            groupPos->show();
    }
    else if(type == "Directional"){
        resize(211, 313);
        //Hide Position Properties
        groupPos->hide();
        lightLayout->removeWidget(groupPos);
        //Show Directions Properties
        lightLayout->addWidget(groupDir, 1, 0);
        lightLayout->addWidget(groupBtn, 2, 0);
        if(groupDir->isHidden())
            groupDir->show();
    }
    else if(type == "Spotlight"){
        resize(211, 418);
        //Show Position Properties
        lightLayout->addWidget(groupPos, 1, 0);
        if(groupPos->isHidden())
            groupPos->show();
        //Show Directions Properties
        lightLayout->addWidget(groupDir, 2, 0);
        lightLayout->addWidget(groupBtn, 3, 0);
        if(groupDir->isHidden())
            groupDir->show();
    }
}

