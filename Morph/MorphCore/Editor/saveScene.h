#ifndef SAVESCENE_H
#define SAVESCENE_H

#include "OGRE/Ogre.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QXmlStreamWriter>

void saveAsDotScene(const QString& path, QFile& file, Ogre::SceneManager* sceneManager);

#endif // SAVESCENE_H
