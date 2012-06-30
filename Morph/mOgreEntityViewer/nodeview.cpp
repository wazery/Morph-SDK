#include "nodeview.h"

using namespace Morph;

NodeView::NodeView(QWidget* parent)
{
    QStringList headerLabels;
    headerLabels.append(QString("Object Name"));

    setColumnCount(1);
    setHeaderLabels(headerLabels);
    //connect(this, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(changeSelection(QTreeWidgetItem*, int)));

    //mSelectedItem = NULL;
    //mOgreRoot =  NULL;
}

NodeView::~NodeView()
{
}

void NodeView::setSystemManager(MSystemManager* manager)
{
    mManger = manager;

    if(initTree())
        MLogManager::getSingleton().logOutput("Canvas objects tree successfully created", M_EDITOR_MESSAGE);
    else
        MLogManager::getSingleton().logOutput("Canvas objects tree are not successfully created!", M_ERROR);
}

bool NodeView::initTree()
{
    if(!mManger->isVisible())
        return false;

    this->clear();
    mNodeList.clear();

    QTreeWidgetItem* rootNodeItem = new QTreeWidgetItem(this);
    rootNodeItem->setFont(0, QFont("ubuntu", -1, 3, true));
    rootNodeItem->setData(0, Qt::DecorationRole, QIcon("settings.png"));
    rootNodeItem->setText(0, "Root");

    for (Ogre::SceneManager::MovableObjectIterator i = mManger->getSceneManager()->getMovableObjectIterator("Entity"); i.hasMoreElements();)
    {
        Ogre::Entity* ent = static_cast<Ogre::Entity*>(i.getNext());
        QTreeWidgetItem* NodeItem = new QTreeWidgetItem(rootNodeItem);
        QString name(ent->getName().c_str());
        QStringList list = name.split(".");
        NodeItem->setText(0, list.at(0));
        mNodeList.append(NodeItem);
    }

    return true;
//    objectCreated(root, root->);
//    for (MNodePtrList::iterator it = root->getChildNodesList().begin(); it != root->getChildNodesList().end(); it++)
//    {
//        if(it != NULL)
//            populateTree(*it);
//        else
//            break;
//    }

//    const MNodePtr rootNode = MNodeManager::getSingleton().getRootNodePtr();

//    if(!rootNode)
//        return false;

//    this->clear();
//    //mOgreRoot = NULL;
//    populateTree(rootNode);
//    qDebug() << "init tree";
}

void NodeView::updateTreeSelection(QString name)
{
    QTreeWidgetItem* item = findItem(name);
    item->setSelected(true);
    MLogManager::getSingleton().logOutput("Object: " + item->text(0) + " has been selected!", M_EDITOR_MESSAGE);
}

QTreeWidgetItem* NodeView::findItem(QString name)
{
    foreach(QTreeWidgetItem* item, mNodeList)
    {
        QStringList list = name.split(".");
        if (item->text(0) == list.at(0))
            return item;
        else
        {
            QTreeWidgetItem* item = new QTreeWidgetItem();
            return item;
        }
    }
}

void NodeView::populateTree(const MNodePtr obj)
{
//    if (!obj->showInObjectTree())
////        return;
//    QTreeWidgetItem* newItem;
//    //if (parent == 0)
//    //    return;

//    QTreeWidgetItem* parentItem = findItem(0, obj->getParent());
//    if (parentItem)
//        newItem = new QTreeWidgetItem(parentItem);
//    else
//        newItem = new QTreeWidgetItem(this);

//    if (parentItem)
//        setItemExpanded(parentItem, true);

//    newItem->setText(0, obj->getName());
//    qDebug() << "tree name: " << obj->getName();

    //TODO:pupulateChilds

    //newItem->setData(0, Qt::UserRole, QVariant(obj));
    //newItem->setData(0, Qt::DecorationRole, QVariant(QIcon("./gui/core/metamethod.png")));
}

bool NodeView::updateNodeTree()
{
    //FIXME: There is a big problem in this if statement, the return value is always incorrect.
    //if(!MSystemManager::getSingleton().isInitialised())
        //return false;

    //const MNodePtr rootNode = MNodeManager::getSingleton().getRootNodePtr();
    //qDebug() << "2: " << rootNode->getName();

//    if(!rootNode)
//        return false;
    //m_hAppRoot = m_wndNodeTree.InsertItem(_T("world"), 0, 0);
    //m_wndNodeTree.SetItemState(m_hAppRoot, TVIS_BOLD, TVIS_BOLD);

//    clear();
//    createNodeItem(rootNode);

    //m_wndNodeTree.Expand(m_hAppRoot, TVE_EXPAND);
    // TODO: replace this function as it is deprecated.
    //setItemSelected(mSelectedItem, true);
    //m_wndNodeTree.Expand(m_hSelectedItem,TVE_EXPAND);

    return true;
}

// Creates tree widget items for the node and its childs.
void NodeView::createNodeItem(const MNodePtr &nodePtr)
{
//    QTreeWidgetItem* currNodeItem = new QTreeWidgetItem(this);
//    if(nodePtr->getName() == "World")
//    {
//        currNodeItem->setFont(0, QFont("ubuntu", -1, 3, true));
//        currNodeItem->setData(0, Qt::DecorationRole, QIcon("settings.png"));
//    }
//    currNodeItem->setText(0, nodePtr->getName());

//    //if(MNodeManager::getSingleton().getFirstSelectedNode() == nodePtr)
//        mSelectedItem = currNodeItem;

//    if(!mOgreRoot)
//        mOgreRoot = currNodeItem;

//    const MNodePtrList childNodeList = nodePtr->getChildNodesList();
//    if(childNodeList.size() > 0)
//    {
//        for(MNodePtrList::const_iterator it = childNodeList.begin(); it!=childNodeList.end(); it++)
//        {
//            createNodeItem(it->second);
//        }
//    }
}

void NodeView::setSelectedObject(MNodePtr obj)
{
//    selectionModel()->clear();
//    if (obj)
//    {
//        QTreeWidgetItem* selectedItem = findItem(0, obj);
//        // setItemExpanded(selectedItem->parent(), true);
//        setItemSelected(selectedItem, true);
//        mSelectedObject = obj;
//    }
//    else
//    {
//        mSelectedObject = 0;
//    }
}

//void NodeView::objectNameChanged(MNodePtr obj)
//{
//    if (!obj->showInObjectTree())
//        return;

//    QTreeWidgetItem* found = findItem(0, obj);
//    if (found)
//        found->setText(0, obj->getName().c_str());
//}

//void NodeView::objectVisibilityChanged(MNodePtr obj, bool visible)
//{
//    if (!obj->showInObjectTree())
//        return;

//    QTreeWidgetItem* found = findItem(0, obj);
//    if (found)
//        if (!visible)
//            found->setTextColor(0, QColor(150, 150, 150));
//        else
//            found->setTextColor(0, QColor(0, 0, 0));
//}

void NodeView::changeSelection(QTreeWidgetItem* item, int column)
{
//    if (item == 0)
//        return;

//    mSelectedObject = reinterpret_cast<MNodePtr>(item->data(0, Qt::UserRole).toUInt());
//    selectionChanged(mSelectedObject);
}

//void NodeView::objectDestructionStarted(MNodePtr obj, MNodePtr parent)
//{
//    if (!obj->showInObjectTree())
//        return;

//    if (parent == 0)
//        return;

//    QTreeWidgetItem* found = findItem(0, obj);
//    if (found)
//        if (found->parent())
//            delete found->parent()->takeChild(found->parent()->indexOfChild(found));
//        else
//            delete takeTopLevelItem(indexOfTopLevelItem(found));
//}

// This function
QTreeWidgetItem* NodeView::FindorCreateNodeItem(const MString &nodeChainName)
{
    QVector<string> namesList = MAttribute::tokenize(nodeChainName.toUtf8().constData(), ".", true, false, "");

    QTreeWidgetItem* currNode;

    for(size_t i = 0; i < namesList.size(); i++)
    {
        MString nodeName = namesList[i].c_str();

        if(i == 0)
        {
            // if the first node is not the root return
            if(nodeName != mOgreRoot->text(0))
            {
                return NULL;
            }
            else
            {
                currNode = mOgreRoot;
            }
        }
        else
        {
            QTreeWidgetItemIterator it(this);
            while (*it) {
                if ((*it)->text(0) == currNode->text(0))
                {
                    QTreeWidgetItem*  nextItem;
                    QTreeWidgetItem*  childItem = currNode->child(0);

                    while(childItem != NULL)
                    {
                        if(nodeName == childItem->text(0))
                        {
                            currNode = childItem;
                            break;
                        }
                        nextItem   = childItem->child(0);
                        childItem  = nextItem;
                    }
                    if(currNode != childItem)
                        return false;
                }
                else
                    return NULL;
                ++it;
            }
        }
    }
    return currNode;
}

void NodeView::addNode(const MString &parentNodeChainName, const MString &nodeName)
{
    qDebug() << "5) addNode";
    updateNodeTree();
    QTreeWidgetItem* parentItem = FindorCreateNodeItem(parentNodeChainName);
    if(parentItem)
    {
        QTreeWidgetItem* createdItem = new QTreeWidgetItem(parentItem);
        createdItem->setText(0, nodeName);
        qDebug() << "created item text: " << createdItem->text(0);

//TODO: createdItem->setData(0, Qt::DecorationRole, QIcon("settings.png"));
//    if(createdItem)
//    {
//        mSelectedItem = createdItem;
//        setItemSelected(mSelectedItem, true);
//    }
}
//MNodePtr dstNodePtr, parentNodePtr;
//MNodeManager::getSingleton().findNodeByChainName(parentNodeChainName + (".") + nodeName, dstNodePtr, parentNodePtr);
////qDebug() << dstNodePtr->getName();
//if(dstNodePtr)
//{
//    const MNodePtrList nodePtrList = dstNodePtr->getChildNodesList();
//    if(nodePtrList.size()>0)
//    {
//        for(MNodePtrList::const_iterator it = nodePtrList.begin(); it != nodePtrList.end(); it++)
//            addNode((it->second)->getParentNodeChainName(), (it->second)->getName());
//    }
//}
}

void NodeView::removeNode(const MString &parentNodeChainName, const MString &nodeName)
{
}
