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
    //DISPLAY OPTION
    groupDisp = new QGroupBox("Display Options");

    renderDetail = new QLabel(tr("Render Detail :"));
    renderDetailCombo = new QComboBox;
    renderDetailCombo->addItem(tr("Solid"));
    renderDetailCombo->addItem(tr("Wireframe"));
    renderDetailCombo->addItem(tr("Points"));

    lod = new QLabel("LOD : ");
    lodSlider = new QSlider(Qt::Horizontal);
    lodSlider->setSliderPosition(lodSlider->maximum()/2);
    lodSlider->setRange(0, 5);

    boundingBox = new QLabel(tr("Bounding Boxes : "));
    boundBoxCheckBox = new QCheckBox;

    dispSkeleton = new QLabel(tr("Skeleton : "));
    dispSkeletonCheckBox = new QCheckBox;

    gridDispLayout = new QGridLayout;
    gridDispLayout->addWidget(renderDetail, 0, 0);
    gridDispLayout->addWidget(renderDetailCombo, 0, 1);

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
    regroupLayout->addWidget(groupDisp);
    regroupLayout->addWidget(groupMat);
    regroupLayout->addWidget(groupAnim);
    regroupLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));
    setLayout(regroupLayout);
}

ObjProperties::~ObjProperties()
{

}

void ObjProperties::updateListAnim(Ogre::AnimationStateSet* anims)
{
    if(anims != 0){
        Ogre::AnimationStateIterator animNames = anims->getAnimationStateIterator();
        while(animNames.hasMoreElements()){
            listAnimCombo->addItem(animNames.getNext()->getAnimationName().c_str());
        }
        loopCheckBox->setEnabled(true);
        playCheckBox->setEnabled(true);
    }
    else{
        loopCheckBox->setEnabled(false);
        playCheckBox->setEnabled(false);

    }
}
