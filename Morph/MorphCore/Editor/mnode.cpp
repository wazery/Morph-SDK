//TODO: Add the licence

#include "mnode.h"
#include "mnodemanager.h"

using namespace Morph;

MNode::MNode()
{
}

MNode::~MNode()
{
}

bool MNode::addChildNode(const MString &nodeName, MNodePtr &nodePtr)
{
    MNodePtr ptr;
    if (!findChildNode(nodeName, ptr))
    {
        mNodeChildren[nodeName] = nodePtr;
        MString parentStr;
        if (!mParentNodeChainName.isEmpty())
        {
            parentStr = this->mParentNodeChainName + "." + this->mName;
        }
        else
            parentStr = this->mName;
    }
    else
        return false;

    return true;
}

bool MNode::removeChildNode(const MString &nodeName)
{
    MNodePtrList::iterator it;
    it = mNodeChildren.find(nodeName);
    if (it != mNodeChildren.end())
    {
        Morph::MNodeManager::getSingleton().notifyRemoveNode(this->mParentNodeChainName + "." + this->mName, nodeName);
        it->second->release();
        mNodeChildren.erase(it);
    }
    else
        return false;

    return true;
}

bool MNode::deleteChildNodeByID(const MString &nodeID)
{
    if (mNodeChildren.size() > 0)
    {
        MNodePtrList::iterator it;
        for (it = mNodeChildren.begin(); it != mNodeChildren.end();)
        {
            if (it->second->getNodeID() == nodeID)
            {
                it->second->release();
                mNodeChildren.erase(it++);
            }
            else
                ++it;
        }
        for (it = mNodeChildren.begin(); it != mNodeChildren.end(); it++)
        {
            it->second->deleteChildNodeByID(nodeID);
        }
    }
}

bool MNode::findChildNode(const MString &nodeName, MNodePtr &nodePtr)
{
    MNodePtrList::iterator it;
    it = mNodeChildren.find(nodeName);
    if(it != mNodeChildren.end())
        nodePtr = it->second;

    else
        return false;

    return true;
}

bool MNode::release()
{
    if (mNodeChildren.size() > 0)
    {
        for (MNodePtrList::iterator it = mNodeChildren.begin(); it!= mNodeChildren.end(); it++)
        {
            it->second->release();
        }
    }

    return true;
}

void MNode::_notifyAttributeChanged(const MString &attrName)
{
    //FIXME: need to implement the MAttrObj class.
    //Morph::MNodeManager::getSingleton().notifyAttributeChanged(mParentNodeChainName, mName, attrName, *getAttribute(attrName));
}
