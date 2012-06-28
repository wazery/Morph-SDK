#ifndef NODEVIEW_H
#define NODEVIEW_H

#include <QTreeWidget>
#include "MorphCore/Editor/msystemmanager.h"
#include "MorphCore/Editor/mnode.h"
#include "MorphCore/Editor/mnodemanager.h"

using namespace Morph;

class NodeView : public QTreeWidget, public MNodeTreeListener
{
    //Q_OBJECT

    MNodePtr mSelectedObject;
    bool initTree();

public:
    NodeView(QWidget* parent = 0);
    ~NodeView();

    MNodePtr getSelectedObject() { return mSelectedObject; }

//    void objectMoved(MNodePtr parent, MNodePtr child, MNodePtr old_parent);
    void populateTree(const MNodePtr obj);
    bool updateNodeTree(void);
    void createNodeItem(const MNodePtr &nodePtr);
//    void objectDestructionStarted(MNodePtr obj, MNodePtr parent);
//    void objectNameChanged(MNodePtr obj);
//    void objectVisibilityChanged(MNodePtr obj, bool visible);

    QTreeWidgetItem* findItem(QString name);
    QTreeWidgetItem *FindorCreateNodeItem(const MString &nodeChainName);

    void setSystemManager(MSystemManager* manager);

    void updateTreeSelection(QString name);

    // Overriden functions from the MNodeTreeListener.
    virtual void addNode(const MString &parentNodeChainName, const MString &nodeName);
    virtual void removeNode(const MString &parentNodeChainName, const MString &nodeName);

protected:
    MSystemManager* mManger;
    QTreeView mNodeTree;
    QTreeWidgetItem* mOgreRoot;
    QTreeWidgetItem* mSelectedItem;
    QList<QTreeWidgetItem*> mNodeList;

protected slots:
    void changeSelection(QTreeWidgetItem*, int);
signals:
    void selectionChanged(MNodePtr obj);
public slots:
    void setSelectedObject(MNodePtr obj);
};

#endif // NODEVIEW_H
