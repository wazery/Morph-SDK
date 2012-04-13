#ifndef ENVPROPERTIES_H
#define ENVPROPERTIES_H

#include <QtGui>

class EnvProperties : public QWidget
{
    Q_OBJECT

public:
    EnvProperties(QWidget *parent = 0);
    ~EnvProperties();

    QPushButton* fogColorBtn;
    QPushButton* backgroundColorBtn;
    QPushButton* ambientLightColorBtn;
    QComboBox* fogTypeCombo;
    QComboBox* shadowTypeCombo;
    QTreeWidget* lightsTree;
    QAction* modifyAction;
    QAction* removeAction;

private:
    QLabel* fogType;
    QLabel* fogColor;
    QLabel* shadowType;
    QLabel* backgroundColor;
    QLabel* ambientLight;

    QGroupBox* groupFog;
    QGroupBox* groupShadow;
    QGroupBox* groupBackground;
    QGroupBox* groupLights;

    QGridLayout* gridFogLayout;
    QGridLayout* gridShadowLayout;
    QGridLayout* gridBackgroundLayout;
    QGridLayout* gridAmbientLightLayout;
    QGridLayout* gridLightsLayout;

    QVBoxLayout* regroupLayout;

    QTreeWidgetItem* mainLight;
    QTreeWidgetItem* lightType;

    QColorDialog* winColor;
    QGridLayout* mainLayout;
};

#endif // ENVPROPERTIES_H
