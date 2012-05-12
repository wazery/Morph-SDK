#include "objpropertiesview.h"

ObjPropertiesView::ObjPropertiesView(QWidget *parent) :
    QWidget(parent)
{
}

ObjPropertiesView::~ObjPropertiesView()
{
}

void ObjPropertiesView::initPropertyList()
{
}

void ObjPropertiesView::selectChanged(const std::map<Morph::MString, Morph::MNodePtr> &selectedNodelist)
{
}

void ObjPropertiesView::attributeChanged(const Morph::MString &parentNodeChainName, const Morph::MString &nodeName, const Morph::MString &attrName, const Morph::MAttribute &attr)
{
}
