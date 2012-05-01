#include "mrootnode.h"

using namespace Morph;

MString MRootNode::nodeID = ("World");
int MRootNode::instanceCount = 0;

MRootNode::MRootNode(const MString &nodeName)
{
    MRootNode::instanceCount++;
    mID = MRootNode::nodeID;
    if(nodeName == (""))
        mName = nodeID;
    else mName = nodeName;
}

MRootNode::~MRootNode(void)
{
}

/** Every MNode instance have to implement this create fun, use to create the class itself.
    @param name nodeName	Name of the node.
    @returns node           shared_ptr pointer
*/
MNodePtr MRootNode::creator(const MString &nodeName)
{
    MNodePtr ptr;
    if(MRootNode::instanceCount>0)
    {
        MLogManager::getSingleton().logOutput(("Root proxy node have been exist, Root node just can be one instance "), M_ERROR);
        //FIXME: this line fails return ptr;
    }
    ptr.reset(new MRootNode(nodeName));
    return ptr;
}

/** Releases this object.
    @returns	true if it succeeds, false if it fails.
*/
bool MRootNode::release()
{
    return(true);
}

/** initialises this object.
    @returns	true if it succeeds, false if it fails.
*/
bool MRootNode::initialise()
{
    // root name
    MAttribute attrName(("name"), mName, ("This is all the Morph proxy node entry."));
    attrName.setReadOnly(true);
    //FIXME: mAttributeList[("name")] = attrName;

    return(false);
}

void MRootNode::_modifiy(const MAttribute &attr)
{
}

