#include "saveScene.h"
#include "qdebug.h"

using namespace Ogre;
void saveAsDotScene(const QString& path, QFile& file, Ogre::SceneManager* sceneManager)
{
    Ogre::MeshSerializer* mMeshSerializer = new Ogre::MeshSerializer();
    Ogre::MaterialSerializer* mMaterialSerializer = new Ogre::MaterialSerializer();

    int idCounter = 3;
    if (!file.open(QIODevice::WriteOnly))
    {
        /* show wrror message if not able to open file */
        QMessageBox::warning(0, "Read only", "The file is in read only mode");
    }
    else
    {
        Ogre::SceneManager::MovableObjectIterator iterator = sceneManager->getMovableObjectIterator("Entity");
        QXmlStreamWriter* xmlWriter = new QXmlStreamWriter();
        xmlWriter->setAutoFormatting(true);
        xmlWriter->setDevice(&file);
        xmlWriter->writeStartElement("scene");
        xmlWriter->writeAttribute("formatVersion","");

        xmlWriter->writeStartElement("nodes");
        while(iterator.hasMoreElements())
        {
            Ogre::Entity* e = static_cast<Ogre::Entity*>(iterator.getNext());
            Ogre::Any any = e->getParentNode()->getUserAny();
            Ogre::String widgetType("");
            if(!any.isEmpty()){
                widgetType = any_cast<Ogre::String>(any);
            }
            Ogre::String tmp(widgetType + ":" + e->getParentNode()->getName());
            QString nodeName(tmp.c_str());
            xmlWriter->writeStartElement("node");
            xmlWriter->writeAttribute("name", nodeName);
            xmlWriter->writeAttribute("id", QString::number(idCounter++));


            xmlWriter->writeStartElement("position");
            xmlWriter->writeAttribute("x", QString::number(e->getParentNode()->getPosition().x));
            xmlWriter->writeAttribute("y", QString::number(e->getParentNode()->getPosition().y));
            xmlWriter->writeAttribute("z", QString::number(e->getParentNode()->getPosition().z));
            xmlWriter->writeEndElement();

            xmlWriter->writeStartElement("scale");
            xmlWriter->writeAttribute("x", QString::number(e->getParentNode()->getScale().x));
            xmlWriter->writeAttribute("y", QString::number(e->getParentNode()->getScale().y));
            xmlWriter->writeAttribute("z", QString::number(e->getParentNode()->getScale().z));
            xmlWriter->writeEndElement();

            xmlWriter->writeStartElement("entity");
            xmlWriter->writeAttribute("name", nodeName);
            xmlWriter->writeAttribute("meshFile", nodeName.toLower() + QString(".mesh") );
            xmlWriter->writeAttribute("static", QString("false"));
            xmlWriter->writeEndElement();

            const Mesh* mesh = e->getMesh().getPointer();


            mMeshSerializer->exportMesh(mesh,String(path.toStdString() +
                                                    nodeName.toLower().toStdString() +
                                                    ".mesh" ));


            std::cout << "numeber" <<  mesh->getNumSubMeshes() << std::endl;


            for(int i = 0; i < e->getNumSubEntities(); i++){


                Ogre::Material *mat = static_cast<Ogre::Material*>
                        (Ogre::MaterialManager::getSingletonPtr()->getByName(e->getSubEntity(i)->getMaterialName()).getPointer());

                //e->getMesh().get()->getSubMesh()
                if(mat->getTechnique(0)->getPass(0)->getNumTextureUnitStates() !=0){
                Ogre::String str = mat->getTechnique(0)->getPass(0)->getTextureUnitState(0)->getTextureName();

            Ogre::MaterialPtr mMatPtr =e->getSubEntity(i)->getMaterial()    ;

            mMaterialSerializer->exportMaterial(mMatPtr ,
                                                String(path.toStdString() +
                                                       nodeName.toLower().toStdString() +
                                                       QString::number(i).toStdString() + ".material" ));
            Ogre::TexturePtr* mTexPtr = new Ogre::TexturePtr(Ogre::TextureManager::getSingletonPtr()->getByName(str));
            Ogre::Texture* mTex = mTexPtr->getPointer();
            Ogre::PixelFormat pxf = mTex->getFormat();
            Ogre::Image mImage;
            mTex->convertToImage(mImage);
            std::cout << str << std::endl;
            mImage.save(String(path.toStdString() +
                                 str));
                }
}
            //material file merge

            for(int i = 0; i < e->getNumSubEntities(); i++){
                Ogre::Material *mat = static_cast<Ogre::Material*>
                        (Ogre::MaterialManager::getSingletonPtr()->getByName(e->getSubEntity(i)->getMaterialName()).getPointer());


                QString mMatFilePath = QString((path.toStdString() +
                                               nodeName.toLower().toStdString() +
                                                ".material").c_str()) ;


                 QFile mFile(mMatFilePath);
                 if (!mFile.open(QIODevice::Append))
                 {
                     /* show wrror message if not able to open file */
                     QMessageBox::warning(0, "Read only", "The file is in read only mode");
                 }
                 else{
                     QTextStream out(&mFile);

                     QString mTempMatPath = QString((path + nodeName.toLower() + QString::number(i) + ".material"));

                     QFile mTempMatFile(mTempMatPath);
                     mTempMatFile.open(QIODevice::ReadOnly);

                     QTextStream src(&mTempMatFile);

                     mFile.write(src.readAll().toStdString().c_str());
                     mTempMatFile.remove();

                 }



            }


            xmlWriter->writeEndElement();


        }

        xmlWriter->writeEndElement();
        xmlWriter->writeEndDocument();
        delete xmlWriter;
    }

    delete mMeshSerializer;
    delete mMaterialSerializer;
}
