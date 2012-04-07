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

#include "MNodeManager.h"

using namespace Morph;

MNodeManager* MNodeManager::smInstance = NULL;

MNodeManager::MNodeManager()
{
    mIsInitialised = false;
}

MNodeManager::~MNodeManager()
{
//    if (smInstance)
//    {
//        delete smInstance;
//        smInstance = NULL;
//    }
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
        MLogManager::getSingleton().logOutput(errorString, M_WARN);
        return false;
    }

    selectNode("", M_SELECT_CLEAR);
    return true;
}

bool MNodeManager::selectNode(const MString &nodeChainName, eSelectMode mode)
{
}

bool MNodeManager::isNodeSelected(const MString &nodeChainName)
{
    MNodePtrList::iterator it = mSelectedNodeList.find(nodeChainName);
    if (it != mSelectedNodeList.end())
    {
        return true;
    }

    return false;
}

bool MNodeManager::findNodeByChainName(const MString &nodeChainName, MNodePtr distinationNodePtr, MNodePtr parentNodePtr)
{
    if(!mIsInitialised)
        return false;

//    vector<MString> namesList = nodeChainName.split(".");

//    MNodePtr nodePtr;
//    MNodePtr parentPtr;

//    for (size_t i = 0; i < namesList.size(); i++)
//    {
//        if (i == 0)
//        {
//            if (namesList[i] != getroo)
//            {

//            }
//        }
//    }
}

void MNodeManager::addSelectListener(MSelectListener* listener)
{
    if (!mIsInitialised)
        return;

    // Return if it is existed.
    if(find(mSelectListenerList.begin(), mSelectListenerList.end(), listener) != mSelectListenerList.end())
        return;

    if(listener)
        mSelectListenerList.push_back(listener);
}

void MNodeManager::removeSelectListener(MSelectListener* listener)
{
    if (listener)
        mSelectListenerList.erase(find(mSelectListenerList.begin(), mSelectListenerList.end(), listener));
}

void MNodeManager::addAttributeListener(MAttributeListener* listener)
{
    if(!mIsInitialised)
        return;

    // Return if it is existed.
    if(find(mAttributeListenerList.begin(), mAttributeListenerList.end(), listener) != mAttributeListenerList.end())
        return;

    if(listener)
        mAttributeListenerList.push_back(listener);
}

void MNodeManager::removeAttributeListener(MAttributeListener* listener)
{
    if(listener)
        mAttributeListenerList.erase(find(mAttributeListenerList.begin(), mAttributeListenerList.end(), listener));
}

void MNodeManager::addNodeTreeListener(MNodeTreeListener* listener)
{
    if(!mIsInitialised)
        return;

    // Return if it is existed.
    if(find(mNodeTreeListenerList.begin(), mNodeTreeListenerList.end(), listener) != mNodeTreeListenerList.end())
        return;

    if (listener)
    {
        mNodeTreeListenerList.push_back(listener);
    }
}

void MNodeManager::removeNodeTreeListener(MNodeTreeListener* listener)
{
    if(listener)
        mNodeTreeListenerList.erase(find(mNodeTreeListenerList.begin(), mNodeTreeListenerList.end(), listener));
}

void MNodeManager::initialise()
{
    mIsInitialised = true;
}

MNodePtr MNodeManager::createNode(const MString &nodeID, const MString &nodeName)
{
}

void MNodeManager::deleteNode(const MString &nodeChainName)
{
}

void MNodeManager::notifyAttributeChanged(const MString &parentNodeChainName, const MString &nodeName, const MString &attrName, const MAttribute &attr)
{
    std::vector<MAttributeListener*>::iterator it;
    for (it = mAttributeListenerList.begin(); it != mAttributeListenerList.end(); ++it)
    {
        assert(*it);
        (*it)->attributeChanged(parentNodeChainName, nodeName, attrName, attr);
    }
}

void MNodeManager::notifyAddNode(const MString &parentNodeChinName, const MString &nodeName)
{
    std::vector<MNodeTreeListener*>::iterator it;
    for (it = mNodeTreeListenerList.begin(); it != mNodeTreeListenerList.end(); ++it)
    {
        assert(*it);
        (*it)->addNode(parentNodeChinName, nodeName);
    }
}

void MNodeManager::notifyRemoveNode(const MString &parentNodeChinName, const MString &nodeName)
{
    std::vector<MNodeTreeListener*>::iterator it;
    for (it = mNodeTreeListenerList.begin(); it != mNodeTreeListenerList.end(); ++it)
    {
        assert(*it);
        (*it)->removeNode(parentNodeChinName, nodeName);
    }
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
