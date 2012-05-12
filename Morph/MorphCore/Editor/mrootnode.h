#ifndef MROOTNODE_H
#define MROOTNODE_H

#include "mnode.h"
#include "mattribute.h"
#include "msystemmanager.h"

namespace Morph
{
    class MRootNode : public MNode
    {
    public:
        MRootNode(const MString &nodeName);
        ~MRootNode(void);

        virtual bool initialise();
        virtual bool release();

        static MString nodeID;

        //every MNode instance have to implement this create fun, use to create the class itself
        static MNodePtr creator(const MString &nodeName = "");

    protected:
        virtual void _modifiy(const MAttribute &attr);

        static int instanceCount;
    };
}

#endif // MROOTNODE_H
