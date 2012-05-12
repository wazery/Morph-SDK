#ifndef MATWINDOW_H
#define MATWINDOW_H

#include <QWidget>
#include <QtGui>
#include <Ogre.h>

class MatWindow : public QWidget
{
    Q_OBJECT

public:
    MatWindow(QWidget *parent = 0);
    ~MatWindow();

    void setTexture(Ogre::Entity*);
    void setScriptPath(QString);
    void setTexturePath(QString);

signals:
    void msgBoxClicked();

private slots:
    void processMat(QTreeWidgetItem*);
    void saveMat();
    void updateTexture();

private:
    QString checkMat(QString str);//Check if the file is a '.material'

    QLabel* textureLbl;

    QTreeWidget* treeMat;
    QTextEdit* matText;
    QPushButton* okBtn;
    QPushButton* cancelBtn;

    QGroupBox* viewTexture;
    QGroupBox* viewMat;
    QGroupBox* groupBtn;

    QHBoxLayout* treeTextureLayout;

    QGridLayout* btnLayout;

    QVBoxLayout* matLayout;
    QVBoxLayout* gridLayout;

    QString scriptPath;
    QString texturePath;

    QFile matFile;
    QString strAllMat;
    int posMat, nextMat;
};

#endif // MATWINDOW_H
