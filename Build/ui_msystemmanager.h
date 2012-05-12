/********************************************************************************
** Form generated from reading UI file 'MSystemManager.ui'
**
** Created: Fri Jul 15 23:51:46 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MSYSTEMMANAGER_H
#define UI_MSYSTEMMANAGER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MSystemManager
{
public:

    void setupUi(QWidget *MSystemManager)
    {
        if (MSystemManager->objectName().isEmpty())
            MSystemManager->setObjectName(QString::fromUtf8("MSystemManager"));
        MSystemManager->resize(400, 300);

        retranslateUi(MSystemManager);

        QMetaObject::connectSlotsByName(MSystemManager);
    } // setupUi

    void retranslateUi(QWidget *MSystemManager)
    {
        MSystemManager->setWindowTitle(QApplication::translate("MSystemManager", "MSystemManager", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MSystemManager: public Ui_MSystemManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QOGREWIDGET_H
