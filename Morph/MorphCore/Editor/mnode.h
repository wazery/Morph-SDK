/* ============================================================
 *
 * This file is a part of Morph project
 *
 * Date        : 2011-10-26
 * @file mnodemanager.cpp
 * @brief The Node class which is has all of the attributes for a simple node
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

#ifndef MNODE_H
#define MNODE_H

#include <Ogre.h>

#include "boost/shared_ptr.hpp"

#include "MType.h"
#include "mattribute.h"
#include "mattrobject.h"

#include <QMap>

using namespace std;

namespace Morph
{

    class MNode;

    typedef boost::shared_ptr<MNode> MNodePtr;

    typedef MNodePtr (*MNodeCreatorFun)(const MString &nodeName);

    typedef std::map<MString, MNodePtr> MNodePtrList;

    class MNode : public MAttrObject
    {

    public:

        MNode();
        ~MNode();

        /** A pure virtual function to be overriden with all the attributes that connect with
        the ogre node*/
        virtual bool initialise() = 0;

        /** Needed to be called before destroying the node instance*/
        virtual bool release() = 0;

        void setNodeID(const MString &nodeID) {mID = nodeID;}
        MString getNodeID() const {return mID;}

        void setName(MString nodeName) {mName = nodeName;}
        MString getName() const {return mName;}

        MNodePtr getParent() const {return mNodeParent;}

        virtual bool addChildNode(const MString &nodeName, MNodePtr &nodePtr);
        virtual bool removeChildNode(const MString &nodeName);

        virtual bool findChildNode(const MString &nodeName, MNodePtr &nodePtr);
        virtual bool deleteChildNodeByID(const MString &nodeID);

        // FIXME:
        const MNodePtrList &getChildNodesList() const {return mNodeChildren;}

        // Access the ParentNodeChainName
        const MString &getParentNodeChainName(void) const { return (mParentNodeChainName); }
        void setParentNodeChainName(const MString &parentNodeChainName)	{ mParentNodeChainName = parentNodeChainName; }

    protected:

        /// Pointer to parent node
        MNodePtr mNodeParent;

        MString mParentNodeChainName;

        // TODO: Implement the MAttribute class
        /** When the user use the setAttribute function to change attribute value, this function
        will be called to fix the Ogre node value. */
        virtual void _modifiy(const MAttribute &attr) = 0;

        MString mName;
        MString mID;

        // the id name in this list that the node could be add to child node list,esle refuse.
        // if the this filter list is empty,that mean all kinds of node are accepted .
        std::vector<MString> mChildNodeIDFiltList;

        virtual void _notifyAttributeChanged(const MString& attrName);

    private:

        MNodePtrList mNodeChildren;
    };
}
#endif // MNODE_H
