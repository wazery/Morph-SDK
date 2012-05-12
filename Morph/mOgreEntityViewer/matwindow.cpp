#include "matwindow.h".h"

MatWindow::MatWindow(QWidget *parent)
         : QWidget(parent)
{
    setWindowTitle(tr("View/Change Material"));
    setWindowFlags(Qt::Dialog);
    setMinimumSize(QSize(400, 500));
    setMaximumSize(QSize(400, 500));

    treeMat = new QTreeWidget(this);
    treeMat->setHeaderLabels(QStringList("Sub Entities"));
    treeMat->setMinimumSize(150, 150);
    connect(treeMat, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(processMat(QTreeWidgetItem*)));

    textureLbl = new QLabel("Texture Preview");
    textureLbl->setPixmap(tr("settings.png"));
    textureLbl->setMinimumSize(150, 150);

    matText = new QTextEdit;
    matText->setMinimumSize(300, 200);
    connect(matText, SIGNAL(textChanged()), this, SLOT(updateTexture()));

    //Textures
    viewTexture = new QGroupBox(tr("View Texture"));

    treeTextureLayout = new QHBoxLayout;
    treeTextureLayout->addWidget(treeMat);
    treeTextureLayout->addWidget(textureLbl);

    viewTexture->setLayout(treeTextureLayout);
    //////////

    //Material
    viewMat = new QGroupBox(tr("View Material"));

    matLayout = new QVBoxLayout;
    matLayout->addWidget(matText);

    viewMat->setLayout(matLayout);
    ////////////

    //Btn
    groupBtn = new QGroupBox;
    groupBtn->setFlat(true);

    okBtn = new QPushButton(tr("&Ok"));
    okBtn->setMaximumSize(QSize(75, 25));
    connect(okBtn, SIGNAL(clicked()), this, SLOT(saveMat()));
    cancelBtn = new QPushButton(tr("&Cancel"));
    cancelBtn->setMaximumSize(QSize(75, 25));
    connect(cancelBtn, SIGNAL(clicked()), this, SLOT(close()));

    btnLayout = new QGridLayout;

    btnLayout->addWidget(okBtn, 0, 1);
    btnLayout->addWidget(cancelBtn, 0, 2);
    btnLayout->setAlignment(okBtn, Qt::AlignRight & Qt::AlignBottom);
    btnLayout->setAlignment(cancelBtn, Qt::AlignRight & Qt::AlignBottom);

    groupBtn->setLayout(btnLayout);
    ///////////

    gridLayout = new QVBoxLayout;
    gridLayout->addWidget(viewTexture);
    gridLayout->addWidget(viewMat);
    gridLayout->addWidget(groupBtn);
    setLayout(gridLayout);

    scriptPath += QDir::currentPath()+"/media/materials/scripts/";
    texturePath += QDir::currentPath()+"/media/materials/textures/";
    posMat = -1;
    nextMat = -1;
    strAllMat = "";
}

MatWindow::~MatWindow()
{

}

void MatWindow::setScriptPath(QString path)
{
    scriptPath = path;
    scriptPath += "/";
}

void MatWindow::setTexturePath(QString path)
{
    texturePath = path;
    texturePath += "/";
}

void MatWindow::setTexture(Ogre::Entity* ent)
{
    //Remove old materials
    for(int i=0; i<=treeMat->topLevelItemCount(); ++i){
        QTreeWidgetItem* item = treeMat->topLevelItem(i);
        delete item;
        item = treeMat->takeTopLevelItem(i);
        delete item;
        item = 0;
    }
    QTreeWidgetItem* item = treeMat->takeTopLevelItem(0);
    delete item;
    item = 0;

    //add new materials
    for(unsigned int i=0; i<ent->getNumSubEntities(); ++i){
        QTreeWidgetItem* item = new QTreeWidgetItem(treeMat);
        item->setText(0, ent->getSubEntity(i)->getMaterialName().c_str());
    }
    treeMat->setCurrentItem(treeMat->topLevelItem(0));
    QTreeWidgetItem* currentItem = treeMat->currentItem();

    processMat(currentItem);
}

void MatWindow::processMat(QTreeWidgetItem* currentItem)
{
    if(!currentItem)
        return;

    return;

    //clean old values
    strAllMat = "";
    matText->clear();
    textureLbl->setPixmap(QPixmap(""));
    textureLbl->setText("Texture Unavailable");

    //We'll seek for the material to include it in matText.
    QDir dir(scriptPath);
    QStringList listFiles(dir.entryList(QStringList() << "*.material", QDir::Files));

    for(int i = 0; i < listFiles.size(); i++)
    {
        QFile file(dir.path() + QDir::separator() + listFiles.at(i));
        if(file.open(QIODevice::ReadOnly))
        {
            QTextStream script(&file);
            //Search our mat
            QString strMat = script.readAll();
            QString nameMat("material "+currentItem->text(0));
            posMat = strMat.indexOf(nameMat);
            if(posMat != -1)
            {
                matText->setPlainText(strMat);//insert all the text and keep it in strAllMat
                strAllMat = matText->toPlainText();
                matText->clear();//clear it so the user don't see anything

                //Process: we cut the beginning of the string. Then we cut all others material
                //So we only have the material wich interest us
                strMat.remove(0, posMat);//we cut the firt part of the string
                nextMat = strMat.indexOf("material ", 8);//search the next material at pos 8 because we want the next material (not the first one)
                if(nextMat != -1)
                    strMat.remove(nextMat, strMat.size());//we cut from this next material to the end so we only have the material we want

                //Processing strMat
                for(int i=0; i<strMat.size(); ++i)
                {
                    if(strMat.at(i) == '\t')
                        strMat.replace(i, 1, "          ");
                }
                matText->setPlainText(strMat);
                QFont f("Arial", 8);
                matText->setFont(f);

                //Now we're looking for the texture
                int posText = strMat.indexOf("texture ");
                if(posText != -1)
                {
                    QString textureName;
                    for(int i=posText+8; i<strMat.size(); ++i)
                    {
                        textureName += strMat.at(i);
                    }
                    textureName.truncate(textureName.indexOf('.'));
                    QPixmap img;
                    if(img.load(texturePath+textureName))
                    {
                        img = img.scaled(150, 150);
                        textureLbl->setText(textureName);
                        textureLbl->setPixmap(img);
                    }
                    else
                    {
                        textureLbl->setText("Image Unavailable");
                    }
                }
                matFile.setFileName(file.fileName());//Finally we keep matFile in memory so that we can open the file later --> saveMat()
            }
        }
        file.close();
    }
}

void MatWindow::saveMat()
{
    if(!QMessageBox::question(this, tr("Overwrite File?"), tr("Do you want to overwrite the material <i>%1</i> with the new one?").arg(treeMat->currentItem()->text(0)), tr("&Yes"), tr("&No"))){
        QFile filename(matFile.fileName());
        if(!filename.open(QFile::WriteOnly | QFile::Text | QFile::Truncate ))
            QMessageBox::warning(this, tr("Morph Editor"), tr("Cannot write file %1:\n%2.") .arg(matFile.fileName()) .arg(filename.errorString()));
        else{
            QTextStream script(&filename);
            QApplication::setOverrideCursor(Qt::WaitCursor);

            QString nameMat("material "+treeMat->currentItem()->text(0));
            int posToReplace = strAllMat.indexOf(nameMat);
            if(posToReplace != -1){
                int nextPosToReplace = strAllMat.indexOf("material ", posToReplace+8);
                if(nextPosToReplace != -1){
                    strAllMat.replace(posToReplace, nextPosToReplace - posToReplace, matText->toPlainText());
                    script << strAllMat;
                }
                else{
                    strAllMat.replace(posToReplace, strAllMat.size() - posToReplace, matText->toPlainText());
                    script << strAllMat;
                }
                emit(msgBoxClicked());
            }
            else
                QMessageBox::warning(this, "Problem", "There was a problem when saving...");

            QApplication::restoreOverrideCursor();
            close();
        }
    }
}

QString MatWindow::checkMat(QString str)
{
    QStringList listStr = str.split('.');
    if(listStr.at(1) == "material")
        return listStr.at(0);
    else
        return "";
}

void MatWindow::updateTexture()
{
    return;
    QString allTxt = matText->toPlainText();
    int posText = allTxt.indexOf("texture ");
    if(posText != -1){
        QString textureName;
        for(int i=posText+8; i<allTxt.size(); ++i){
            textureName += allTxt.at(i);
        }
        textureName.truncate(textureName.indexOf('.'));
        QPixmap img;
        std::cout << QString(texturePath+textureName).toLocal8Bit().data() << std::endl;
        if(img.load(texturePath+textureName)){
            img = img.scaled(150, 150);
            textureLbl->setText(textureName);
            textureLbl->setPixmap(img);
        }
        else
            textureLbl->setText("Image Unavailable");
    }
}
