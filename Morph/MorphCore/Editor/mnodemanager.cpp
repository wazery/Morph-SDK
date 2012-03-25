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

#include "MNode.h"
#include "MLogManager.h"

using namespace Morph;

MNodeManager::MNodeManager()
{
    mIsInitialised = false;
}

MNodeManager::~MNodeManager()
{
    if (smInstance)
    {
        delete smInstance;
        smInstance = NULL;
    }
}

bool MNodeManager::registerNode(const MString &nodeID, MNodeCreatorFun creatorFun)
{
    // Check if the node id exist
    if (!creatorFun)
    {
        MString errorString = "ERROR: The function creator is NULL for this node(" + nodeID + ")";
        MLogManager::getSingletonPtr()->logOutput(errorString);
        return false;
    }
    else
        mNormalNodeRegList[nodeID] = creatorFun;

    return true;
}

bool MNodeManager::deregisterNode(const MString &nodeID)
{
    // Check if the node id exist
    // FIXME: selectNode();
    if (mNormalNodeRegList.find(nodeID) != mNormalNodeRegList.end())
    {
        mNormalNodeRegList.erase(mNormalNodeRegList.find(nodeID));

        if (mRootNodePtr && nodeID == mRootNodePtr->getNodeID())
        {
            mRootNodePtr->release();
        }
        // Free all nodes created by this nodeID.
        else if(mRootNodePtr)
        {
            mRootNodePtr->deleteChildNodeByID(nodeID);
            notifyRemoveNode("", mRootNodePtr->getName());
        }
    }
    else
    {
        MString errorString = "WARN: The node name (" + nodeID + ") that you want to de-register doesn't exist!";
        MLogManager::getSingleton().logOutput(errorString);
        return false;
    }
    // FIXME: selectNode("");
    return true;
}

bool MNodeManager::selectNode(const MString &nodeChainName)
{
}

bool MNodeManager::isNodeSelected(const MString &nodeChainName)
{
}

bool MNodeManager::findNodeByChainName(const MString &nodeChainName, MNodePtr distinationNodePtr, MNodePtr parentNodePtr)
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

MNodePtr MNodeManager::createNode(const MString &nodeID, const MString &nodeName)
{
}

void MNodeManager::deleteNode(const MString &nodeChainName)
{
}

void MNodeManager::notifyAttributeChanged(const MString &parentNodeChainName, const MString &nodename, const MString &attrName, const MAttribute &attr)
{
}

void MNodeManager::notifyAddNode(const MString &parentNodeChinName, const MString &nodeName)
{
}

void MNodeManager::notifyRemoveNode(const MString &parentNodeChinName, const MString &nodeName)
{
}

MNodeManager* MNodeManager::getSingletonPtr()
{
    if (smInstance == NULL)
    {
        smInstance = new MNodeManager;
    }

    return smInstance;
}

MNodeManager &MNodeManager::getSingleton()
{
    if (smInstance == NULL)
    {
        smInstance = new MNodeManager;
    }

    return *smInstance;
}

void MNodeManager::releaseSingleton()
{
    if (smInstance)
    {
        delete smInstance;
        smInstance = NULL;
    }
}
