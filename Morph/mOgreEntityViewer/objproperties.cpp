/* ============================================================
 *
 * This file is a part of Morph project
 *
 * Date        : 2011-10-26
 * @file objproperties.cpp
 * @brief Object properties tab.
 *
 * Copyright (C) 2011-2012 by @author Islam Wazery <wazery at ubuntu dot com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation;
 * either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * ============================================================ */

#include "objproperties.h"

ObjProperties::ObjProperties(QWidget *parent) : QWidget(parent)
{
    groupObjName = new QGroupBox("Object");
    groupObjName->setMaximumHeight(60);

    name = new QLabel("Name : ");
    nameText = new QTextEdit();
    nameText->setToolTip("Object name cannot be changed!");
    nameText->setFixedHeight(28);
    nameText->setAcceptRichText(false);
    nameText->setReadOnly(true);
    nameText->setMaximumHeight(28);

    gridNameLayout = new QGridLayout;

    gridNameLayout->addWidget(name, 1, 0);
    gridNameLayout->addWidget(nameText, 1, 1);
    groupObjName->setLayout(gridNameLayout);
    ////////////////////////////////////////////

    //POSITION OPTIONS
    groupPos = new QGroupBox("Position Options");
    groupPos->setMaximumHeight(150);

    posX = new QLabel("X: ");
    posXText = new QSpinBox();
    posXText->setFixedHeight(28);
    posXText->setFixedWidth(60);

    posY = new QLabel("Y: ");
    posYText = new QSpinBox();
    posYText->setFixedHeight(28);
    posYText->setFixedWidth(60);

    posZ = new QLabel("Z: ");
    posZText = new QSpinBox();
    posZText->setFixedHeight(28);
    posZText->setFixedWidth(60);

    gridPosLayout = new QGridLayout;

    gridPosLayout->addWidget(posX, 0, 0);
    gridPosLayout->addWidget(posXText, 0, 1);

    gridPosLayout->addWidget(posY, 0, 2);
    gridPosLayout->addWidget(posYText, 0, 3);

    gridPosLayout->addWidget(posZ, 0, 4);
    gridPosLayout->addWidget(posZText, 0, 5);
    groupPos->setLayout(gridPosLayout);
    ////////////////////////////////////////////

    //ROTATION OPTIONS
    groupRot = new QGroupBox("Rotation Options");
    groupRot->setMaximumHeight(150);

    rotX = new QLabel("X: ");
    rotXText = new QSpinBox();
    rotXText->setFixedHeight(28);
    rotXText->setFixedWidth(60);

    rotY = new QLabel("Y: ");
    rotYText = new QSpinBox();
    rotYText->setFixedHeight(28);
    rotYText->setFixedWidth(60);

    rotZ = new QLabel("Z: ");
    rotZText = new QSpinBox();
    rotZText->setFixedHeight(28);
    rotZText->setFixedWidth(60);

    gridRotLayout = new QGridLayout;

    gridRotLayout->addWidget(rotX, 0, 0);
    gridRotLayout->addWidget(rotXText, 0, 1);

    gridRotLayout->addWidget(rotY, 0, 2);
    gridRotLayout->addWidget(rotYText, 0, 3);

    gridRotLayout->addWidget(rotZ, 0, 4);
    gridRotLayout->addWidget(rotZText, 0, 5);
    groupRot->setLayout(gridRotLayout);
    ////////////////////////////////////////////

    //SCALE OPTIONS
    groupScale = new QGroupBox("Scale Options");
    groupScale->setMaximumHeight(150);

    scaleX = new QLabel("X: ");
    scaleXText = new QSpinBox();
    scaleXText->setFixedHeight(28);
    scaleXText->setFixedWidth(60);

    scaleY = new QLabel("Y: ");
    scaleYText = new QSpinBox();
    scaleYText->setFixedHeight(28);
    scaleYText->setFixedWidth(60);

    scaleZ = new QLabel("Z: ");
    scaleZText = new QSpinBox();
    scaleZText->setFixedHeight(28);
    scaleZText->setFixedWidth(60);

    gridScaleLayout = new QGridLayout;

    gridScaleLayout->addWidget(scaleX, 0, 0);
    gridScaleLayout->addWidget(scaleXText, 0, 1);

    gridScaleLayout->addWidget(scaleY, 0, 2);
    gridScaleLayout->addWidget(scaleYText, 0, 3);

    gridScaleLayout->addWidget(scaleZ, 0, 4);
    gridScaleLayout->addWidget(scaleZText, 0, 5);
    groupScale->setLayout(gridScaleLayout);
    ////////////////////////////////////////////

    //DISPLAY OPTIONS
    groupDisp = new QGroupBox("Display Options");

    lod = new QLabel("LOD : ");
    lodSlider = new QSlider(Qt::Horizontal);
    lodSlider->setSliderPosition(lodSlider->maximum()/2);
    lodSlider->setRange(0, 5);

    boundingBox = new QLabel(tr("Bounding Boxes : "));
    boundBoxCheckBox = new QCheckBox;

    dispSkeleton = new QLabel(tr("Skeleton : "));
    dispSkeletonCheckBox = new QCheckBox;

    gridDispLayout = new QGridLayout;

    gridDispLayout->addWidget(boundingBox, 1, 0);
    gridDispLayout->addWidget(boundBoxCheckBox, 1, 1);

    gridDispLayout->addWidget(dispSkeleton, 2, 0);
    gridDispLayout->addWidget(dispSkeletonCheckBox, 2, 1);

    gridDispLayout->addWidget(lod, 3, 0);
    gridDispLayout->addWidget(lodSlider, 3, 1);
    groupDisp->setLayout(gridDispLayout);
    ////////////////////////////////////////////

    //MATERIALS
    groupMat = new QGroupBox("Materials Options");
    groupMat->setMaximumHeight(100);

    viewMat = new QLabel(tr("View/Change : "));
    viewMatBtn = new QPushButton(tr("Modify"));

    gridMatLayout = new QGridLayout;
    gridMatLayout->addWidget(viewMat, 0, 0);
    gridMatLayout->addWidget(viewMatBtn, 0, 1);

    groupMat->setLayout(gridMatLayout);
    ////////////////////////////////////////////

    //ANIMATION
    groupAnim = new QGroupBox("Animation Options");

    listAnim = new QLabel(tr("Select Animation : "));
    listAnimCombo = new QComboBox;

    loop = new QLabel(tr("Set Loop : "));
    loopCheckBox = new QCheckBox;

    playAnim = new QLabel(tr("Play Anim : "));
    playCheckBox = new QCheckBox;

    gridAnimLayout = new QGridLayout;
    gridAnimLayout->addWidget(listAnim, 0, 0);
    gridAnimLayout->addWidget(listAnimCombo, 0, 1);

    gridAnimLayout->addWidget(loop, 1, 0);
    gridAnimLayout->addWidget(loopCheckBox, 1, 1);

    gridAnimLayout->addWidget(playAnim, 2, 0);
    gridAnimLayout->addWidget(playCheckBox, 2, 1);

    groupAnim->setLayout(gridAnimLayout);
    ////////////////////////////////////////////

    regroupLayout = new QVBoxLayout;
    regroupLayout->addWidget(groupObjName);
    regroupLayout->addWidget(groupPos);
    regroupLayout->addWidget(groupRot);
    regroupLayout->addWidget(groupScale);
    regroupLayout->addWidget(groupDisp);
    regroupLayout->addWidget(groupMat);
    regroupLayout->addWidget(groupAnim);
    regroupLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));
    setLayout(regroupLayout);

    connect(posXText, SIGNAL(valueChanged(int)), this, SLOT(setObjectPosX(int)));
    connect(posYText, SIGNAL(valueChanged(int)), this, SLOT(setObjectPosY(int)));
    connect(posZText, SIGNAL(valueChanged(int)), this, SLOT(setObjectPosZ(int)));

    connect(rotXText, SIGNAL(valueChanged(int)), this, SLOT(setObjectRotX(int)));
    connect(rotYText, SIGNAL(valueChanged(int)), this, SLOT(setObjectRotY(int)));
    connect(rotZText, SIGNAL(valueChanged(int)), this, SLOT(setObjectRotZ(int)));

    connect(scaleXText, SIGNAL(valueChanged(int)), this, SLOT(setObjectScaleX(int)));
    connect(scaleYText, SIGNAL(valueChanged(int)), this, SLOT(setObjectScaleY(int)));
    connect(scaleZText, SIGNAL(valueChanged(int)), this, SLOT(setObjectScaleZ(int)));
}

ObjProperties::~ObjProperties()
{

}

void ObjProperties::updateListAnim(Ogre::AnimationStateSet* anims)
{
    if(anims != 0)
    {
        Ogre::AnimationStateIterator animNames = anims->getAnimationStateIterator();
        while(animNames.hasMoreElements())
        {
            listAnimCombo->addItem(animNames.getNext()->getAnimationName().c_str());
        }
        loopCheckBox->setEnabled(true);
        playCheckBox->setEnabled(true);
    }
    else
    {
        loopCheckBox->setEnabled(false);
        playCheckBox->setEnabled(false);
    }
}

void ObjProperties::setObjectPosX(int value)
{
    emit signalPosXChanged(value);
}

void ObjProperties::setObjectPosY(int value)
{
    emit signalPosYChanged(value);
}

void ObjProperties::setObjectPosZ(int value)
{
    emit signalPosZChanged(value);
}

// --------------------------------
void ObjProperties::setObjectRotX(int value)
{
    emit signalRotXChanged(value);
}

void ObjProperties::setObjectRotY(int value)
{
    emit signalRotYChanged(value);
}

void ObjProperties::setObjectRotZ(int value)
{
    emit signalRotZChanged(value);
}

// --------------------------------
void ObjProperties::setObjectScaleX(int value)
{
    emit signalScaleXChanged(value);
}

void ObjProperties::setObjectScaleY(int value)
{
    emit signalScaleYChanged(value);
}

void ObjProperties::setObjectScaleZ(int value)
{
    emit signalScaleZChanged(value);
}
