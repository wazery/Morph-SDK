#ifndef LIGHTWINDOW_H
#define LIGHTWINDOW_H

#include <QWidget>
#include <QtGui>

class LightWindow : public QWidget
{
    Q_OBJECT

public:
    LightWindow(QWidget *parent = 0);

    QPushButton* diffuseColorLightBtn;
    QPushButton* specularColorLightBtn;
    QPushButton* okBtn;

    QLineEdit* nameLightEdit;
    QLineEdit* XEditPos;
    QLineEdit* YEditPos;
    QLineEdit* ZEditPos;
    QLineEdit* XEditDir;
    QLineEdit* YEditDir;
    QLineEdit* ZEditDir;

    QComboBox* typeLightCombo;

public slots:
    void newTypeLight(QString);

private:
    void addLightDesign();
    void setNameDesign();
    void setColorDesign();
    void setTypeDesign();
    void setPosDesign();

    QPushButton *cancelBtn;

    QGroupBox* groupLight;
    QGroupBox* groupPos;
    QGroupBox* groupBtn;
    QGroupBox* groupDir;

    QLabel* nameLight;
    QLabel* diffuseColorLight;
    QLabel* specularColorLight;
    QLabel* typeLight;
    QLabel* XPos;
    QLabel* YPos;
    QLabel* ZPos;
    QLabel* XDir;
    QLabel* YDir;
    QLabel* ZDir;

    QGridLayout* mainPropertieslayout;
    QGridLayout* posLayout;
    QGridLayout* dirLayout;
    QGridLayout* btnLayout;
    QGridLayout* lightLayout;
};

#endif // LIGHTWINDOW_H
