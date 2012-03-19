/* ============================================================
 *
 * This file is a part of Morph project
 *
 * Date        : 2011-10-26
 * @file mnodemanager.h
 * @brief A manager which is responsible for all the details about nodes
 * and managing them and their attributes.
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

#ifndef MNODEMANAGER_H
#define MNODEMANAGER_H

#include <OGRE/Ogre.h>

#include "mnode.h"

class MSelectListener
{};

class MAttributeListener
{};

class MNodeTreeListener
{};

class MNodeManager
{
public:
    MNodeManager();
    ~MNodeManager();

    /** Registers new node to the register list.
      @param nodeID Ogre::String Identifier of the node.
      @param creatorFun MNodeCreatorFun The creator fun.
      @returns true if the node registered correctly.
    */
    virtual bool registerNode(const Ogre::String &nodeID, MNodeCreatorFun creatorFun);

    /** De-registers the node from the register list.
      @param nodeID Ogre::String Identifier of the node.
    */
    virtual bool deregisterNode(const Ogre::String &nodeID);

    /** Select a given node and insert it to the selected node list.
      @remarks For a given chain name this function splits the name and try to find every node,
               if the node itself and its parents are all found, it inserts the node poiner to the selected node list.
      @param nodeChainName Ogre::String The full name of the node and its parents, e.x. "grandparent.parent.child".
      @returns true if the node found and selected.
    */
    virtual bool selectNode(const Ogre::String &nodeChainName);

    /** It asks if the node is selected, if yes it returns true.
      @param nodeChainName Ogre::String
      @return true of the node is selcted.
    */
    bool isNodeSelected(const Ogre::String &nodeChainName);

    /** Searchs for a node using its chain name.
      @remarks This function takes the chain name ant of this chain name contain some '.' char,
               it will split the string into parent and child name, such as "john.sam.lily",
               then it will first find "john", and then at john's children nodes
               find "sam", and then at sam's children fild "lily". If all of
               them have been found,and then return lily node pointer.
      @param nodeChainName Ogre::String the chain name of a particular node.
      @param distinationNodePtr MNodePtr pointer of the distination node.
      @param parentNodePtr MNodePtr pointer of the parent node.
      @return true if it finds the node successfully.
    */
    virtual bool findNodeByChainName(const Ogre::String &nodeChainName, MNodePtr distinationNodePtr, MNodePtr parentNodePtr);

    /** Gets the selected node list */
    MNodePtrList &getSelectedNodeList(){};

    /** Register a select listener.
      @param listener MSelectListener* A pointer to a select listener class.
      @return void
    */
    void addSelectListener(MSelectListener* listener);

    /** De-register a select listener
      @param listener MSelectListener* A pointer to a select listener class.
      @return void
    */
    void removeSelectListener(MSelectListener* listener);

    /** Register an attribute listener.
      @param listener MAttributeListener*
      @return void
    */
    void addAttributeListener(MAttributeListener* listener);

    /** De-register an attribute listener.
      @param listener MAttributeListener*
      @return void
    */
    void removeAttributeListener(MAttributeListener* listener);

    /** Register a node tree listener.
      @param listener MNodeTreeListener*
      @return void
    */
    void addNodeTreeListener(MNodeTreeListener* listener);

    /** De-register a node tree listener.
      @param listener MNodeTreeListener*
      @return void
    */
    void removeNodeTreeListener(MNodeTreeListener* listener);

    /**
      @param
      @return
    */
    void initialise();

    /**
      @remarks
      @param
      @return
    */
    virtual MNodePtr createNode();

    /**
      @remarks
      @param
      @return
    */
    virtual deleteNode();

    virtual void notifyAttributeChanged();
    virtual void notifyAddNode();
    virtual void notifyRemoveNode();

    static MNodeManager* smInstance;

    /** Get the class address pointer */
    static MNodeManager* getSingletonPtr();
    /** Get the class instance */
    static MNodeManager &getSingleton();
    /** Delete the class instance */
    static void releaseSingleton();

protected:

    bool mIsInitialised;

    MNodeRegList mNodeRegList;
    MNodePtr mRootNodePtr;
    MNodePtrList mSelectedNodeList;

    MNodePtrList::iterator mSelectedNodeListIterator;

    std::vector<MSelectListener*> mSelectListenerList;
    std::vector<MAttributeListener*> mAttributeListenerList;
    std::vector<MNodeTreeListener*> mNodeTreeListenerList;

};

#endif // MNODEMANAGER_H
