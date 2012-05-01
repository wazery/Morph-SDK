/* ============================================================
 *
 * This file is a part of Morph project
 *
 * Date        : 2011-10-26
 * @file ObjPropertiesView.h
 * @brief The editor view for object properties.
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

#ifndef OBJPROPERTIESVIEW_H
#define OBJPROPERTIESVIEW_H

#include <QtGui>
#include <OGRE/Ogre.h>
#include "../MorphCore/Editor/MType.h"
#include "../MorphCore/Editor/mnode.h"
#include "../MorphCore/Editor/mattribute.h"

class ObjPropertiesView : public QWidget
{
    Q_OBJECT
public:
    explicit ObjPropertiesView(QWidget *parent = 0);
    ~ObjPropertiesView();

    QComboBox* listAnimCombo;
    QComboBox* renderDetailCombo;


private:
    QLabel* label;

protected:
    void initPropertyList();

    /** Will be fired when the selected node changed */
    virtual void selectChanged(const std::map<Morph::MString, Morph::MNodePtr> &selectedNodelist);

    /** Will be fired when the attribute changed */
    virtual void attributeChanged(const Morph::MString &parentNodeChainName, const Morph::MString &nodeName, const Morph::MString &attrName, const Morph::MAttribute &attr);
    
    Morph::MString mSelectedNodeName;
    Morph::MNode *mSelectedNodePtr;

signals:
    
public slots:
    
};
#endif // OBJPROPERTIESVIEW_H
