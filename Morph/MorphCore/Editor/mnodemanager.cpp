/* ============================================================
 *
 * This file is a part of Morph project
 *
 * Date        : 2011-10-26
 * @file mnodemanager.cpp
 * @brief A manager which is responsible for all the details about nodes
 * and managing them.
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

#include "mnodemanager.h"

MNodeManager::MNodeManager()
{
    mIsInitialised = false;
}

MNodeManager::~MNodeManager()
{
    if (mInstance)
    {
        delete mInstance;
        mInstance = NULL;
    }
}

virtual bool MNodeManager::registerNode(const Ogre::String &nodeID, MNodeCreatorFun creatorFun)
{
}

virtual bool MNodeManager::deregisterNode(const Ogre::String &nodeID)
{
}

virtual bool MNodeManager::selectNode(const Ogre::String &nodeChainName)
{
}

bool MNodeManager::isNodeSelected(const Ogre::String &nodeChainName)
{
}

virtual bool MNodeManager::findNodeByChainName(const Ogre::String &nodeChainName, MNodePtr distinationNodePtr, MNodePtr parentNodePtr)
{
}

void MNodeManager::addSelectListener(MSelectListener* listener)
{
}

void MNodeManager::removeSelectListener(MSelectListener* listener)
{
}

void MNodeManager::addAttributeListener(MAttributeListener* listener)
{
}

void MNodeManager::removeAttributeListener(MAttributeListener* listener)
{
}

void MNodeManager::addNodeTreeListener(MNodeTreeListener* listener)
{
}

void MNodeManager::removeNodeTreeListener(MNodeTreeListener* listener)
{
}

void MNodeManager::initialise()
{
}

virtual MNodePtr MNodeManager::createNode()
{
}

virtual MNodeManager::deleteNode()
{
}

virtual void MNodeManager::notifyAttributeChanged()
{
}

virtual void MNodeManager::notifyAddNode()
{
}

virtual void MNodeManager::notifyRemoveNode()
{
}

static MNodeManager* MNodeManager::getSingletonPtr()
{
    if (smInstance == NULL)
    {
        mInstance = new MNodeManager*;
    }

    return smInstance;
}

static MNodeManager* &MNodeManager::getSingleton()
{
    if (smInstance == NULL)
    {
        smInstance = new MNodeManager;
    }

    return *smInstance;
}

static void MNodeManager::releaseSingleton()
{
    if (smInstance)
    {
        delete smInstance;
       smIntance = NULL;
    }
}
