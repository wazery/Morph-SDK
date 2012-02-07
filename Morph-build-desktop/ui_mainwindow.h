/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Wed Feb 8 01:38:22 2012
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDockWidget>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QTextBrowser>
#include <QtGui/QToolBar>
#include <QtGui/QTreeView>
#include <QtGui/QWidget>
#include "ogrecanvas.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionQuit;
    QAction *actionNew;
    QAction *actionSave_as;
    QAction *actionSelect;
    QAction *actionMove;
    QAction *actionTranslate;
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *actionCut;
    QAction *actionDelete;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionFull_Screen;
    QAction *actionShow_3D_Canvas;
    QAction *actionWidgets;
    QAction *actionScene_Explorer;
    QAction *actionCanvas;
    QAction *actionLogging;
    QAction *actionAbout_Morph;
    QAction *actionRotate;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuSelection;
    QMenu *menuObjects;
    QMenu *menuView;
    QMenu *menuTools;
    QMenu *menuWindows;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QToolBar *toolBar;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QGridLayout *gridLayout_2;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_4;
    OgreCanvas *widget;
    QSlider *horizontalSlider;
    QSpinBox *spinBox;
    QWidget *tab_2;
    QGridLayout *gridLayout_6;
    QGridLayout *gridLayout_5;
    QPushButton *pushButton;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_2;
    QDockWidget *dockWidget_2;
    QWidget *dockWidgetContents_2;
    QGridLayout *gridLayout;
    QTextBrowser *textBrowser;
    QDockWidget *dockWidget_3;
    QWidget *dockWidgetContents_3;
    QGridLayout *gridLayout_3;
    QTreeView *treeView;
    QDockWidget *dockWidget_4;
    QWidget *dockWidgetContents_4;
    QGridLayout *gridLayout_7;
    QListWidget *listWidget;
    QDockWidget *dockWidget_5;
    QWidget *dockWidgetContents_5;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1073, 777);
        MainWindow->setMinimumSize(QSize(500, 0));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/toolbar/icons/qtOgitor.svg"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setStyleSheet(QString::fromUtf8("background:rgb(30, 30, 30)"));
        MainWindow->setDocumentMode(false);
        MainWindow->setTabShape(QTabWidget::Rounded);
        MainWindow->setDockOptions(QMainWindow::AllowNestedDocks|QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/toolbar/icons/folder32.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon1);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/toolbar/icons/upload32.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon2);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/toolbar/icons/block32.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionQuit->setIcon(icon3);
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/toolbar/icons/ogscene2.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew->setIcon(icon4);
        actionSave_as = new QAction(MainWindow);
        actionSave_as->setObjectName(QString::fromUtf8("actionSave_as"));
        actionSave_as->setIcon(icon2);
        actionSelect = new QAction(MainWindow);
        actionSelect->setObjectName(QString::fromUtf8("actionSelect"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/toolbar/icons/arrow32.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSelect->setIcon(icon5);
        actionMove = new QAction(MainWindow);
        actionMove->setObjectName(QString::fromUtf8("actionMove"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/toolbar/icons/move.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionMove->setIcon(icon6);
        actionTranslate = new QAction(MainWindow);
        actionTranslate->setObjectName(QString::fromUtf8("actionTranslate"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/toolbar/icons/translate.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionTranslate->setIcon(icon7);
        actionCopy = new QAction(MainWindow);
        actionCopy->setObjectName(QString::fromUtf8("actionCopy"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/toolbar/icons/linedpaper32.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCopy->setIcon(icon8);
        actionPaste = new QAction(MainWindow);
        actionPaste->setObjectName(QString::fromUtf8("actionPaste"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/toolbar/icons/paste.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionPaste->setIcon(icon9);
        actionCut = new QAction(MainWindow);
        actionCut->setObjectName(QString::fromUtf8("actionCut"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/toolbar/icons/scissors32.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCut->setIcon(icon10);
        actionDelete = new QAction(MainWindow);
        actionDelete->setObjectName(QString::fromUtf8("actionDelete"));
        actionUndo = new QAction(MainWindow);
        actionUndo->setObjectName(QString::fromUtf8("actionUndo"));
        actionRedo = new QAction(MainWindow);
        actionRedo->setObjectName(QString::fromUtf8("actionRedo"));
        actionFull_Screen = new QAction(MainWindow);
        actionFull_Screen->setObjectName(QString::fromUtf8("actionFull_Screen"));
        actionShow_3D_Canvas = new QAction(MainWindow);
        actionShow_3D_Canvas->setObjectName(QString::fromUtf8("actionShow_3D_Canvas"));
        actionWidgets = new QAction(MainWindow);
        actionWidgets->setObjectName(QString::fromUtf8("actionWidgets"));
        actionScene_Explorer = new QAction(MainWindow);
        actionScene_Explorer->setObjectName(QString::fromUtf8("actionScene_Explorer"));
        actionCanvas = new QAction(MainWindow);
        actionCanvas->setObjectName(QString::fromUtf8("actionCanvas"));
        actionLogging = new QAction(MainWindow);
        actionLogging->setObjectName(QString::fromUtf8("actionLogging"));
        actionAbout_Morph = new QAction(MainWindow);
        actionAbout_Morph->setObjectName(QString::fromUtf8("actionAbout_Morph"));
        actionRotate = new QAction(MainWindow);
        actionRotate->setObjectName(QString::fromUtf8("actionRotate"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/toolbar/icons/leftturnarrow32.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRotate->setIcon(icon11);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1073, 25));
        menuBar->setStyleSheet(QString::fromUtf8(""));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        menuSelection = new QMenu(menuBar);
        menuSelection->setObjectName(QString::fromUtf8("menuSelection"));
        menuObjects = new QMenu(menuBar);
        menuObjects->setObjectName(QString::fromUtf8("menuObjects"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QString::fromUtf8("menuTools"));
        menuWindows = new QMenu(menuBar);
        menuWindows->setObjectName(QString::fromUtf8("menuWindows"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QFont font;
        font.setStyleStrategy(QFont::PreferAntialias);
        mainToolBar->setFont(font);
        mainToolBar->setStyleSheet(QString::fromUtf8(""));
        mainToolBar->setMovable(true);
        mainToolBar->setAllowedAreas(Qt::AllToolBarAreas);
        mainToolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        toolBar->setAutoFillBackground(false);
        toolBar->setStyleSheet(QString::fromUtf8(""));
        MainWindow->addToolBar(Qt::LeftToolBarArea, toolBar);
        dockWidget = new QDockWidget(MainWindow);
        dockWidget->setObjectName(QString::fromUtf8("dockWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(dockWidget->sizePolicy().hasHeightForWidth());
        dockWidget->setSizePolicy(sizePolicy);
        dockWidget->setMinimumSize(QSize(800, 500));
        dockWidget->setLayoutDirection(Qt::LeftToRight);
        dockWidget->setFeatures(QDockWidget::AllDockWidgetFeatures);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        gridLayout_2 = new QGridLayout(dockWidgetContents);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        tabWidget = new QTabWidget(dockWidgetContents);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setStyleSheet(QString::fromUtf8(""));
        tabWidget->setTabPosition(QTabWidget::East);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setElideMode(Qt::ElideNone);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout_4 = new QGridLayout(tab);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        widget = new OgreCanvas(tab);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalSlider = new QSlider(widget);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(540, 390, 160, 29));
        horizontalSlider->setOrientation(Qt::Horizontal);
        spinBox = new QSpinBox(widget);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setGeometry(QRect(480, 390, 59, 27));

        gridLayout_4->addWidget(widget, 0, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        gridLayout_6 = new QGridLayout(tab_2);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setSpacing(6);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        pushButton = new QPushButton(tab_2);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setAutoDefault(false);
        pushButton->setDefault(false);
        pushButton->setFlat(false);

        gridLayout_5->addWidget(pushButton, 0, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_5->addItem(verticalSpacer, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer, 0, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_2, 0, 0, 1, 1);


        gridLayout_6->addLayout(gridLayout_5, 1, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_6->addItem(verticalSpacer_2, 0, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());

        gridLayout_2->addWidget(tabWidget, 0, 0, 1, 1);

        dockWidget->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget);
        dockWidget_2 = new QDockWidget(MainWindow);
        dockWidget_2->setObjectName(QString::fromUtf8("dockWidget_2"));
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QString::fromUtf8("dockWidgetContents_2"));
        gridLayout = new QGridLayout(dockWidgetContents_2);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        textBrowser = new QTextBrowser(dockWidgetContents_2);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textBrowser->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textBrowser->setSource(QUrl("file:///home/enopia/source-codes/Morph/Morph-build-desktop/logging.html"));

        gridLayout->addWidget(textBrowser, 0, 0, 1, 1);

        dockWidget_2->setWidget(dockWidgetContents_2);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget_2);
        dockWidget_3 = new QDockWidget(MainWindow);
        dockWidget_3->setObjectName(QString::fromUtf8("dockWidget_3"));
        sizePolicy.setHeightForWidth(dockWidget_3->sizePolicy().hasHeightForWidth());
        dockWidget_3->setSizePolicy(sizePolicy);
        dockWidgetContents_3 = new QWidget();
        dockWidgetContents_3->setObjectName(QString::fromUtf8("dockWidgetContents_3"));
        gridLayout_3 = new QGridLayout(dockWidgetContents_3);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        treeView = new QTreeView(dockWidgetContents_3);
        treeView->setObjectName(QString::fromUtf8("treeView"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(treeView->sizePolicy().hasHeightForWidth());
        treeView->setSizePolicy(sizePolicy1);
        treeView->setAnimated(true);

        gridLayout_3->addWidget(treeView, 0, 0, 1, 1);

        dockWidget_3->setWidget(dockWidgetContents_3);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockWidget_3);
        dockWidget_4 = new QDockWidget(MainWindow);
        dockWidget_4->setObjectName(QString::fromUtf8("dockWidget_4"));
        dockWidgetContents_4 = new QWidget();
        dockWidgetContents_4->setObjectName(QString::fromUtf8("dockWidgetContents_4"));
        gridLayout_7 = new QGridLayout(dockWidgetContents_4);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        listWidget = new QListWidget(dockWidgetContents_4);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        gridLayout_7->addWidget(listWidget, 0, 0, 1, 1);

        dockWidget_4->setWidget(dockWidgetContents_4);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockWidget_4);
        dockWidget_5 = new QDockWidget(MainWindow);
        dockWidget_5->setObjectName(QString::fromUtf8("dockWidget_5"));
        dockWidgetContents_5 = new QWidget();
        dockWidgetContents_5->setObjectName(QString::fromUtf8("dockWidgetContents_5"));
        dockWidget_5->setWidget(dockWidgetContents_5);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockWidget_5);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuSelection->menuAction());
        menuBar->addAction(menuObjects->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuWindows->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSave_as);
        menuFile->addAction(actionQuit);
        menuEdit->addAction(actionUndo);
        menuEdit->addAction(actionRedo);
        menuEdit->addSeparator();
        menuEdit->addAction(actionCut);
        menuEdit->addAction(actionCopy);
        menuEdit->addAction(actionPaste);
        menuEdit->addAction(actionDelete);
        menuEdit->addSeparator();
        menuTools->addAction(actionSelect);
        menuTools->addAction(actionMove);
        menuTools->addAction(actionTranslate);
        menuWindows->addAction(actionCanvas);
        menuWindows->addAction(actionFull_Screen);
        menuWindows->addAction(actionLogging);
        menuWindows->addAction(actionScene_Explorer);
        menuWindows->addAction(actionWidgets);
        menuHelp->addAction(actionAbout_Morph);
        mainToolBar->addAction(actionNew);
        mainToolBar->addAction(actionOpen);
        mainToolBar->addAction(actionSave);
        mainToolBar->addAction(actionSave_as);
        mainToolBar->addAction(actionQuit);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionCut);
        toolBar->addAction(actionSelect);
        toolBar->addAction(actionMove);
        toolBar->addAction(actionTranslate);
        toolBar->addAction(actionRotate);

        retranslateUi(MainWindow);
        QObject::connect(actionQuit, SIGNAL(activated()), MainWindow, SLOT(close()));
        QObject::connect(actionFull_Screen, SIGNAL(activated()), MainWindow, SLOT(showFullScreen()));
        QObject::connect(actionWidgets, SIGNAL(activated()), dockWidget_4, SLOT(show()));
        QObject::connect(actionScene_Explorer, SIGNAL(activated()), dockWidget_3, SLOT(show()));
        QObject::connect(actionLogging, SIGNAL(activated()), dockWidget_2, SLOT(show()));
        QObject::connect(actionCanvas, SIGNAL(activated()), dockWidget, SLOT(show()));

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Morph Editor", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("MainWindow", "&Open", 0, QApplication::UnicodeUTF8));
        actionOpen->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        actionSave->setText(QApplication::translate("MainWindow", "&Save", 0, QApplication::UnicodeUTF8));
        actionQuit->setText(QApplication::translate("MainWindow", "&Quit", 0, QApplication::UnicodeUTF8));
        actionNew->setText(QApplication::translate("MainWindow", "&New", 0, QApplication::UnicodeUTF8));
        actionNew->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", 0, QApplication::UnicodeUTF8));
        actionSave_as->setText(QApplication::translate("MainWindow", "Save &As", 0, QApplication::UnicodeUTF8));
        actionSave_as->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+S", 0, QApplication::UnicodeUTF8));
        actionSelect->setText(QApplication::translate("MainWindow", "&Select", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionSelect->setToolTip(QApplication::translate("MainWindow", "Select Objects", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionMove->setText(QApplication::translate("MainWindow", "&Move", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionMove->setToolTip(QApplication::translate("MainWindow", "Move", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionTranslate->setText(QApplication::translate("MainWindow", "&Translate", 0, QApplication::UnicodeUTF8));
        actionCopy->setText(QApplication::translate("MainWindow", "&Copy", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionCopy->setToolTip(QApplication::translate("MainWindow", "Copy Selected Item", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionCopy->setShortcut(QApplication::translate("MainWindow", "Ctrl+C", 0, QApplication::UnicodeUTF8));
        actionPaste->setText(QApplication::translate("MainWindow", "&Paste", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionPaste->setToolTip(QApplication::translate("MainWindow", "Paste Selected Item", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionPaste->setShortcut(QApplication::translate("MainWindow", "Ctrl+V", 0, QApplication::UnicodeUTF8));
        actionCut->setText(QApplication::translate("MainWindow", "&Cut", 0, QApplication::UnicodeUTF8));
        actionCut->setShortcut(QApplication::translate("MainWindow", "Ctrl+X", 0, QApplication::UnicodeUTF8));
        actionDelete->setText(QApplication::translate("MainWindow", "&Delete", 0, QApplication::UnicodeUTF8));
        actionDelete->setShortcut(QApplication::translate("MainWindow", "Del", 0, QApplication::UnicodeUTF8));
        actionUndo->setText(QApplication::translate("MainWindow", "&Undo", 0, QApplication::UnicodeUTF8));
        actionUndo->setShortcut(QApplication::translate("MainWindow", "Ctrl+Z", 0, QApplication::UnicodeUTF8));
        actionRedo->setText(QApplication::translate("MainWindow", "&Redo", 0, QApplication::UnicodeUTF8));
        actionRedo->setShortcut(QApplication::translate("MainWindow", "Ctrl+Y", 0, QApplication::UnicodeUTF8));
        actionFull_Screen->setText(QApplication::translate("MainWindow", "&Full Screen", 0, QApplication::UnicodeUTF8));
        actionFull_Screen->setShortcut(QApplication::translate("MainWindow", "F11", 0, QApplication::UnicodeUTF8));
        actionShow_3D_Canvas->setText(QApplication::translate("MainWindow", "&Show 3D Canvas", 0, QApplication::UnicodeUTF8));
        actionWidgets->setText(QApplication::translate("MainWindow", "Widgets", 0, QApplication::UnicodeUTF8));
        actionScene_Explorer->setText(QApplication::translate("MainWindow", "Scene Explorer", 0, QApplication::UnicodeUTF8));
        actionCanvas->setText(QApplication::translate("MainWindow", "Canvas", 0, QApplication::UnicodeUTF8));
        actionLogging->setText(QApplication::translate("MainWindow", "Logging", 0, QApplication::UnicodeUTF8));
        actionAbout_Morph->setText(QApplication::translate("MainWindow", "About Morph", 0, QApplication::UnicodeUTF8));
        actionRotate->setText(QApplication::translate("MainWindow", "Rotate", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "&File", 0, QApplication::UnicodeUTF8));
        menuEdit->setTitle(QApplication::translate("MainWindow", "&Edit", 0, QApplication::UnicodeUTF8));
        menuSelection->setTitle(QApplication::translate("MainWindow", "Selection", 0, QApplication::UnicodeUTF8));
        menuObjects->setTitle(QApplication::translate("MainWindow", "Objects", 0, QApplication::UnicodeUTF8));
        menuView->setTitle(QApplication::translate("MainWindow", "View", 0, QApplication::UnicodeUTF8));
        menuTools->setTitle(QApplication::translate("MainWindow", "&Tools", 0, QApplication::UnicodeUTF8));
        menuWindows->setTitle(QApplication::translate("MainWindow", "&Windows", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        dockWidget->setWhatsThis(QApplication::translate("MainWindow", "The Ogre canvas which views the 3D objects in two ways, the first is the rendered and the second is the wireframe view", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        dockWidget->setWindowTitle(QApplication::translate("MainWindow", "Canvas", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_ACCESSIBILITY
        tabWidget->setAccessibleName(QApplication::translate("MainWindow", "tab", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_ACCESSIBILITY
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Rendered", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_ACCESSIBILITY
        pushButton->setAccessibleName(QApplication::translate("MainWindow", "Start", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_ACCESSIBILITY
        pushButton->setText(QApplication::translate("MainWindow", "Start Ogre", 0, QApplication::UnicodeUTF8));
        pushButton->setShortcut(QApplication::translate("MainWindow", "Ctrl+Return", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Wireframe", 0, QApplication::UnicodeUTF8));
        dockWidget_2->setWindowTitle(QApplication::translate("MainWindow", "Logging", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        textBrowser->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_ACCESSIBILITY
        textBrowser->setAccessibleName(QApplication::translate("MainWindow", "logging", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_ACCESSIBILITY
        textBrowser->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><title>Accelerated C++ Errata</title><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" color:#ff0000;\">Please note</span> that because of corrections, page numbers may sometimes differ slightly from one printing to another. So, for example, if you have a copy of the first printing, and you are looking for a correction first noticed in the fourth printing, you may find it on the page before or after the one cited. </p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Thanks to Walter\302\240E.\302\240Brown, Don\302\240C"
                        "aldwell, Paolo\302\240Carlini, Neil\302\240Cerutti, Harry\302\240Chung, David\302\240Clark, Anton\302\240Doblmaier, Debatosh\302\240Debnath, Steven\302\240van\302\240Dijk, Hans\302\240Dulimarta, Daniel\302\240Faber, Attila\302\240Feher, Adam\302\240Foster, Kevin\302\240Goodsell, Seyed\302\240H.\302\240Haeri, Gregory\302\240Haley, Mogens\302\240Hansen, Philip\302\240Hibbs, Anto\302\240Jurkovic, John\302\240Linderman, Greg\302\240McClure, Miguel\302\240Mart\303\255nez de\302\240la\302\240Torre, Bernd\302\240Mohr, Wo-Yip\302\240Ng, Nicole\302\240McAllister, Brian\302\240McNamara, Frank\302\240Mittelbach, Ron\302\240Natalie, John\302\240Potter, Peter\302\240N.\302\240Roth, Andreas\302\240Scherer, William\302\240Simon, Marc\302\240Souaille, Randy\302\240Sherman, Ralf\302\240Taner, Antoine\302\240Trux, Alex\302\240Tuzlukov, Abraham\302\240Walfish, Conrad\302\240Weisert, and Han\302\240Xu for pointing\302\240them\302\240out! </p>\n"
"<p style=\" margin-top:16px; margin-bottom:12px; margin-left:0px; margin-right:0px; "
                        "-qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:x-large; font-weight:600;\">Technical errors in the fifth printing</span> </p>\n"
"<ul style=\"margin-top: 0px; margin-bottom: 0px; margin-left: 0px; margin-right: 0px; -qt-list-indent: 1;\"><li style=\" margin-top:12px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Pages 32 and 307: The precedence table should say that the assignment and conditional operators have the same precedence and are right-associative. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 173: In the second line from the end of the page, <span style=\" font-family:'Courier New,courier';\">*beg</span> should be <span style=\" font-family:'Courier New,courier';\">*begin</span> (twice). </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 179: The text should say t"
                        "hat it is possible for <span style=\" font-family:'Courier New,courier';\">argc</span>to be zero. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Pages 191-192, 314: The types that containers are required to provide include <span style=\" font-family:'Courier New,courier';\">difference_type</span> </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 223: In the fourth line of the first complete paragraph, <span style=\" font-family:'Courier New,courier';\">iostream</span> should be <span style=\" font-family:'Courier New,courier';\">istream</span>. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 224: In the fifth line after the second program example, <span style=\" font-family:'Courier New,courier';\">string</span> should be <span style=\" font-family:'Cour"
                        "ier New,courier';\">Str</span>. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 304: The text incorrectly states that <span style=\" font-family:'Courier New,courier';\">float</span> is promoted to <span style=\" font-family:'Courier New,courier';\">double</span> as part of the standard arithmetic conversions. </li></ul>\n"
"<p style=\" margin-top:16px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:x-large; font-weight:600;\">Clarifications in the fifth printing</span> </p>\n"
"<ul style=\"margin-top: 0px; margin-bottom: 0px; margin-left: 0px; margin-right: 0px; -qt-list-indent: 1;\"><li style=\" margin-top:12px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 24: The discussion at the bottom of the page should say explicitly that treating a <span style=\" font-family:'Courier New,courier';\">bool</sp"
                        "an> value as a number yields <span style=\" font-family:'Courier New,courier';\">1</span> if the <span style=\" font-family:'Courier New,courier';\">bool</span> is <span style=\" font-family:'Courier New,courier';\">true</span> and<span style=\" font-family:'Courier New,courier';\">0</span> if the <span style=\" font-family:'Courier New,courier';\">bool</span> is <span style=\" font-family:'Courier New,courier';\">false</span>. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 216: In the code example at the bottom of the page, the call to <span style=\" font-family:'Courier New,courier';\">s.data.push_back</span> is not the only compile error, because it is not the only reference to <span style=\" font-family:'Courier New,courier';\">s.data</span>; there is another reference near the beginning of the example. </li></ul>\n"
"<p style=\" margin-top:16px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent"
                        ":0; text-indent:0px;\"><span style=\" font-size:x-large; font-weight:600;\">Typographical details in the fifth printing</span> </p>\n"
"<ul style=\"margin-top: 0px; margin-bottom: 0px; margin-left: 0px; margin-right: 0px; -qt-list-indent: 1;\"><li style=\" margin-top:12px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 57: In the fourth paragraph, the first sentence should end with ``end-of-file'' instead of ``end-of file.'' </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 111: In the last full paragraph, the variable named <span style=\" font-family:'Courier New,courier';\">didn't</span> should be <span style=\" font-family:'Courier New,courier';\">didnt</span>. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 128: Near the bottom of the page, the sentence that refers to ``the data stru"
                        "cture that <span style=\" font-family:'Courier New,courier';\">split</span> returns'' should instead be referring to <span style=\" font-family:'Courier New,courier';\">xref</span>. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 154: There is a comma missing in the argument list of the call to <span style=\" font-family:'Courier New,courier';\">copy</span> in the last line of exercise 8-6. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 219: The constructor of class <span style=\" font-family:'Courier New,courier';\">Str</span> should have parameters named <span style=\" font-family:'Courier New,courier';\">b</span> and <span style=\" font-family:'Courier New,courier';\">e</span>, rather than <span style=\" font-family:'Courier New,courier';\">i</span> and <span style=\" font-family:'Courier New,courier';\">j</span>, to match the ver"
                        "sion on page 212. </li></ul>\n"
"<p style=\" margin-top:16px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:x-large; font-weight:600;\">Technical errors in the fourth printing</span> </p>\n"
"<ul style=\"margin-top: 0px; margin-bottom: 0px; margin-left: 0px; margin-right: 0px; -qt-list-indent: 1;\"><li style=\" margin-top:12px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 34: In exercise 2-10, the comparison <span style=\" font-family:'Courier New,courier';\">k</span> <span style=\" font-family:'Courier New,courier';\">!=</span> <span style=\" font-family:'Courier New,courier';\">n</span> should be <span style=\" font-family:'Courier New,courier';\">k</span> <span style=\" font-family:'Courier New,courier';\">!=</span> <span style=\" font-family:'Courier New,courier';\">10</span>. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-inde"
                        "nt:0; text-indent:0px;\">Page 70: The invariant near the bottom of the page should refer to <span style=\" font-family:'Courier New,courier';\">maxlen</span> rather than <span style=\" font-family:'Courier New,courier';\">max</span>. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 174: In the third line from the bottom, <span style=\" font-family:'Courier New,courier';\">coord</span> <span style=\" font-family:'Courier New,courier';\">+</span> <span style=\" font-family:'Courier New,courier';\">1</span> should be <span style=\" font-family:'Courier New,courier';\">coords</span> <span style=\" font-family:'Courier New,courier';\">+</span> <span style=\" font-family:'Courier New,courier';\">1</span>. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 183: In the comment in the code example near the bottom of the page, <span style=\" font-fa"
                        "mily:'Courier New,courier';\">p</span> should be <span style=\" font-family:'Courier New,courier';\">*p</span>. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 190: In the last code example on the page, <span style=\" font-family:'Courier New,courier';\">size_type</span> should be <span style=\" font-family:'Courier New,courier';\">std::size_t</span>. Note that the similar example on page 193 is correct as it stands, because <span style=\" font-family:'Courier New,courier';\">size_type</span> has now been defined. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 239: The call to <span style=\" font-family:'Courier New,courier';\">students[i].grade()</span> is dynamically bound, not statically bound. However, because the type of <span style=\" font-family:'Courier New,courier';\">students[i]</span> is known during compilation, the effect"
                        " is the same as that of static binding. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 264: The first code example should call <span style=\" font-family:'Courier New,courier';\">s1.read(cin)</span> rather than <span style=\" font-family:'Courier New,courier';\">read(cin,</span> <span style=\" font-family:'Courier New,courier';\">s1)</span>, and similarly for <span style=\" font-family:'Courier New,courier';\">s2</span>. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Pages 265-266: The text sometimes mentions the standard <span style=\" font-family:'Courier New,courier';\">vector</span> class when it should refer to the <span style=\" font-family:'Courier New,courier';\">Vec</span> class that we are defining. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\""
                        ">Page 280: The last code example has a spurious semicolon at the end. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 281: The first complete paragraph should note that <span style=\" font-family:'Courier New,courier';\">Pic</span> must also be a friend. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 304: The list of conversions is missing an entry, just before the last one. It should say: ``Otherwise, if either operand is <span style=\" font-family:'Courier New,courier';\">unsigned</span> <span style=\" font-family:'Courier New,courier';\">int</span>, the result is <span style=\" font-family:'Courier New,courier';\">unsigned</span> <span style=\" font-family:'Courier New,courier';\">int</span>.'' It also needs to mention the integral promotions. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:12px; margin-left:0px; margin-right:"
                        "0px; -qt-block-indent:0; text-indent:0px;\">Page 307: The description of compound assignment should say <span style=\" font-family:'Courier New,courier';\">x</span> <span style=\" font-style:italic;\">op</span><span style=\" font-family:'Courier New,courier';\">=</span> <span style=\" font-family:'Courier New,courier';\">y</span> instead of <span style=\" font-family:'Courier New,courier';\">x</span> <span style=\" font-style:italic;\">op</span><span style=\" font-family:'Courier New,courier';\">=</span> <span style=\" font-family:'Courier New,courier';\">x</span> </li></ul>\n"
"<p style=\" margin-top:16px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:x-large; font-weight:600;\">Typographical details in the fourth printing</span> </p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:1; text-indent:0px;\">The code examples are not consistent about whether to put a space after <span s"
                        "tyle=\" font-family:'Courier New,courier';\">template</span>; that is, whether to say <span style=\" font-family:'Courier New,courier';\">template&lt;class T&gt; class Vec { /* ... */ };</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:1; text-indent:0px;\">or <span style=\" font-family:'Courier New,courier';\">template &lt;class T&gt; class Vec { /* ... */ };</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:1; text-indent:0px;\">Fortunately, it's correct either way. </p>\n"
"<p style=\" margin-top:16px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:x-large; font-weight:600;\">Clarifications in the fourth printing</span> </p>\n"
"<ul style=\"margin-top: 0px; margin-bottom: 0px; margin-left: 0px; margin-right: 0px; -qt-list-indent: 1;\"><li style=\" margin-top:12px; margin-bottom:0px; margin-left:0px; margin-rig"
                        "ht:0px; -qt-block-indent:0; text-indent:0px;\">Pages 32 and 307: The description of compound assignments in the table should enumerate the operators explicitly. The description of <span style=\" font-family:'Courier New,courier';\">%</span> should say that the operands must be integers. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 100: In exercise 5-9, it's not clear whether a word containing mixed-case letters is uppercase or lowercase. The exercise should be to write all the words in the input that do not contain any uppercase letters, followed by all the words that contain one or more uppercase letters. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 179: The program at the bottom of the page can be made easier to understand by writing <span style=\" font-family:'Courier New,courier';\">argv[1]</span> as a special case, and then "
                        "printing a space <span style=\" font-style:italic;\">before</span> each subsequent argument, if any. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Pages 260 and 263: The initializations of <span style=\" font-family:'Courier New,courier';\">p</span> and <span style=\" font-family:'Courier New,courier';\">refptr</span> are clearer if they appear in the same order as the definitions of the data members themselves. </li></ul>\n"
"<p style=\" margin-top:16px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:x-large; font-weight:600;\">Technical errors in the third printing</span> </p>\n"
"<ul style=\"margin-top: 0px; margin-bottom: 0px; margin-left: 0px; margin-right: 0px; -qt-list-indent: 1;\"><li style=\" margin-top:12px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 47: The invariant in the comment on the "
                        "third line of the page should say that <span style=\" font-family:'Courier New,courier';\">homework</span> contains all the homework grades read so far, rather than all the grades. Similarly for the invariant in the comment near the bottom of page 70. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 100: In exercise 5-6, <span style=\" font-family:'Courier New,courier';\">v</span> should be <span style=\" font-family:'Courier New,courier';\">students</span> throughout. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 136: In the first complete paragraph on the page, the third sentence should refer to ``the body'' rather than ``the <span style=\" font-family:'Courier New,courier';\">push_back</span>.'' </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Pages "
                        "167, 238, 241, 248, and 258: <span style=\" font-family:'Courier New,courier';\">students.name.size()</span> should be <span style=\" font-family:'Courier New,courier';\">students.name().size()</span> instead. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 186: <span style=\" font-family:'Courier New,courier';\">&lt;ifstream&gt;</span> should be <span style=\" font-family:'Courier New,courier';\">&lt;fstream&gt;</span> </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 191: Containers need to define <span style=\" font-family:'Courier New,courier';\">reference</span> and <span style=\" font-family:'Courier New,courier';\">const_reference</span> as well as <span style=\" font-family:'Courier New,courier';\">value_type</span>. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; t"
                        "ext-indent:0px;\">Page 203: In the last paragraph before the code example, <span style=\" font-family:'Courier New,courier';\">size</span> and <span style=\" font-family:'Courier New,courier';\">end</span> need to know about the new member as well. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 206: The comments in the code example should reflect that the definitions of <span style=\" font-family:'Courier New,courier';\">size</span> and <span style=\" font-family:'Courier New,courier';\">end</span> are changed. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 209: The last sentence of the second paragraph swaps the descriptions of <span style=\" font-family:'Courier New,courier';\">limit</span> and <span style=\" font-family:'Courier New,courier';\">avail</span>. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px"
                        "; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 213: On the third line of the first code example, the comment should refer to <span style=\" font-family:'Courier New,courier';\">d2</span> instead of <span style=\" font-family:'Courier New,courier';\">d</span>. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 222: The declaration of <span style=\" font-family:'Courier New,courier';\">operator</span> <span style=\" font-family:'Courier New,courier';\">double</span> in the first code example should have a <span style=\" font-family:'Courier New,courier';\">const</span> immediately before the semicolon. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Pages 258 and 259: In the example that spans those pages, <span style=\" font-family:'Courier New,courier';\">runtime_error</span> should be <span style=\" font-family:'Courier New,c"
                        "ourier';\">std::runtime_error</span>. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Pages 261 and 263: The definition of <span style=\" font-family:'Courier New,courier';\">refptr</span> should mention <span style=\" font-family:'Courier New,courier';\">std::size_t</span> rather than <span style=\" font-family:'Courier New,courier';\">size_t</span>. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 264: In the last example before the start of section 14.4, <span style=\" font-family:'Courier New,courier';\">run_time_error</span> should be <span style=\" font-family:'Courier New,courier';\">runtime_error</span>. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Pages 271, 273, and 276: Class <span style=\" font-family:'Courier New,courier';\">Pic_base</span> sh"
                        "ould have an empty virtual destructor. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 277: In the sentence before the last code example, <span style=\" font-family:'Courier New,courier';\">vector&lt;char&gt;</span> should be <span style=\" font-family:'Courier New,courier';\">vector&lt;string&gt;</span>. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 281: The second code example should refer to <span style=\" font-family:'Courier New,courier';\">std::max</span> rather than just <span style=\" font-family:'Courier New,courier';\">max</span>. </li></ul>\n"
"<p style=\" margin-top:16px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:x-large; font-weight:600;\">Clarifications in the third printing</span> </p>\n"
"<ul style=\"margin-top: 0px; margin-bottom: 0px; marg"
                        "in-left: 0px; margin-right: 0px; -qt-list-indent: 1;\"><li style=\" margin-top:12px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 28: It should be explicit that we are talking about the values that <span style=\" font-family:'Courier New,courier';\">r</span> takes on in the loop bodies, not what value it might have after the loop completes. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 73: Exercise 4-6 should ask the reader to rewrite the <span style=\" font-family:'Courier New,courier';\">read</span> and <span style=\" font-family:'Courier New,courier';\">grade</span> functions as well as the <span style=\" font-family:'Courier New,courier';\">Student_info</span> structure. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 154: The <span style=\" font-family:'Courier New,courier';\""
                        ">xref</span> function doesn't return a <span style=\" font-family:'Courier New,courier';\">vector&lt;string&gt;</span>, so exercise 8-5 should describe the current behavior as ``placing their entire output in a data structure.'' </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 165: The discussion at the bottom of the page should say explicitly that initialization takes place in the order of declaration, not in the order of the member-initializer list. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 184: The discussion of off-the-end pointers in the third paragraph of 10.6.2 should refer to the earlier discussion on page 149. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 190: The comments in the first example should make it clear that the definitio"
                        "ns use the cited constructors, rather than defining them. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 191: In section 11.2.3, paragraph 2, the first sentence refers to ``the type of the objects that the container stores.'' It is clearer to refer to ``the type of each object that the container stores.'' </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 258: In order to use the <span style=\" font-family:'Courier New,courier';\">Handle</span> class, it is necessary to change the Core class to allow <span style=\" font-family:'Courier New,courier';\">Handle&lt;core&gt;</span> to use the <span style=\" font-family:'Courier New,courier';\">clone</span> member, either by making <span style=\" font-family:'Courier New,courier';\">Handle&lt;core&gt;</span> a friend of <span style=\" font-family:'Courier New,courier';\">Core</span> or by maki"
                        "ng the <span style=\" font-family:'Courier New,courier';\">clone</span> member <span style=\" font-family:'Courier New,courier';\">public</span>. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 306: The description of operators that guarantee order of evaluation should include the comma operator (correctly described at the bottom of the table on page 307). </li></ul>\n"
"<p style=\" margin-top:16px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:x-large; font-weight:600;\">Typographical details in the third printing</span> </p>\n"
"<ul style=\"margin-top: 0px; margin-bottom: 0px; margin-left: 0px; margin-right: 0px; -qt-list-indent: 1;\"><li style=\" margin-top:12px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 128: In the penultimate comment in the code example, ``lines numbers'' should be ``line n"
                        "umbers.'' </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 164: The last line of the fourth paragraph has an extra word ``a'' in it. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 192: In the last line of the page, ``It the operator...'' should be ``If the operator...'' </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 247: There should not be a space between ``<span style=\" font-family:'Courier New,courier';\">friend</span>'' and ``ship'' at the end of the first complete paragraph. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Pages 292 and 294: The chapter title at the top of the page is missing a question mark. </li>\n"
"<li style=\" margin-top:0px; margin-botto"
                        "m:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 296: In the paragraph beginning ``C++ inherits its'' near the middle of the page, there is a missing word ``by'' after ``followed'' in the third line. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 297: The first line of the definition of <span style=\" font-style:italic;\">type-specifier</span> should end with an ``or'' (|) symbol. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 303: The word ``is'' appears twice in a row in section A.2.3, paragraph 2, line 1. </li></ul>\n"
"<p style=\" margin-top:16px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:x-large; font-weight:600;\">Technical errors in the second printing</span> </p>\n"
"<ul style=\"margin-top: 0px; margin-bottom: 0p"
                        "x; margin-left: 0px; margin-right: 0px; -qt-list-indent: 1;\"><li style=\" margin-top:12px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 22, first paragraph, last line: ``true'' should be ``false'' </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 32, near the end of the table: <span style=\" font-family:'Courier New,courier';\">x</span> <span style=\" font-style:italic;\">op</span><span style=\" font-family:'Courier New,courier';\">=</span> <span style=\" font-family:'Courier New,courier';\">x</span> should be <span style=\" font-family:'Courier New,courier';\">x</span> <span style=\" font-style:italic;\">op</span><span style=\" font-family:'Courier New,courier';\">=</span> <span style=\" font-family:'Courier New,courier';\">y</span>. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 33"
                        ": The equivalence between <span style=\" font-family:'Courier New,courier';\">for</span> and <span style=\" font-family:'Courier New,courier';\">while</span> statements is not exact if the <span style=\" font-style:italic;\">statement</span> is or contains a <span style=\" font-family:'Courier New,courier';\">continue</span> statement. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 34: In the description <span style=\" font-family:'Courier New,courier';\">if (</span><span style=\" font-style:italic;\">&lt;condition&gt;</span><span style=\" font-family:'Courier New,courier';\">) </span><span style=\" font-style:italic;\">statement</span><span style=\" font-family:'Courier New,courier';\">; else </span><span style=\" font-style:italic;\">statement2</span></li>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:1; text-indent:0px;\">there should be no semicolon, because the"
                        " <span style=\" font-style:italic;\">statement</span> will usually have one of its own. </p>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 48, just before 3.3: The execution time of <span style=\" font-family:'Courier New,courier';\">sort</span> is guaranteed in the average case, but it is possible for it to run more slowly with pathological input. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 64: The 11th line from the bottom is missing some characters: <span style=\" font-family:'Courier New,courier';\">&lt;&lt; string(maxlen + 1 - students[i].name.size(), '</span></li>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:1; text-indent:0px;\">should be <span style=\" font-family:'Courier New,courier';\">&lt;&lt; string(maxlen + 1 - students[i].name.size(), ' ');</span> </p>\n"
"<li sty"
                        "le=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 70, 7 lines from the bottom: <span style=\" font-family:'Courier New,courier';\">vs</span> should be <span style=\" font-family:'Courier New,courier';\">students</span> in the comment on that line. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 97: <span style=\" font-family:'Courier New,courier';\">erase</span> returns an iterator referring to the position immediately after the erasure. <span style=\" font-family:'Courier New,courier';\">c[n]</span> refers to a container element, not necessarily a character. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 116, two paragraphs before the beginning of section 6.3: The first reference to <span style=\" font-family:'Courier New,courier';\">v</span> in that paragraph shou"
                        "ld refer to <span style=\" font-family:'Courier New,courier';\">s.homework</span> instead, as should the reference to <span style=\" font-family:'Courier New,courier';\">v</span> in the comment in the code example. The last two references to should refer to <span style=\" font-family:'Courier New,courier';\">nonzero</span> instead. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 120: The last code example should call <span style=\" font-family:'Courier New,courier';\">students.erase</span>, not <span style=\" font-family:'Courier New,courier';\">v.erase</span>. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 135: In the last line of the first paragraph of section 7.4.4, <span style=\" font-family:'Courier New,courier';\">&lt;</span> should be <span style=\" font-family:'Courier New,courier';\">&lt;=</span>. </li>\n"
"<li style=\" margi"
                        "n-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 190, last line on the page: <span style=\" font-family:'Courier New,courier';\">vector</span> should be <span style=\" font-family:'Courier New,courier';\">Vec</span>. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 204, code example: The second parameter for <span style=\" font-family:'Courier New,courier';\">construct</span> should be <span style=\" font-family:'Courier New,courier';\">const</span> <span style=\" font-family:'Courier New,courier';\">T&amp;</span>, not <span style=\" font-family:'Courier New,courier';\">T</span>. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 205, the declarations of <span style=\" font-family:'Courier New,courier';\">uninitialized_copy</span> and <span style=\" font-family:'Courier New,courie"
                        "r';\">uninitialized_fill</span> should be <span style=\" font-family:'Courier New,courier';\">template&lt;class In, class Out&gt; Out uninitialized_copy(In, In, Out); <br />template&lt;class Out, class T&gt; void uninitialized_fill(Out, Out, const T&amp;); </span></li>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:1; text-indent:0px;\">where <span style=\" font-family:'Courier New,courier';\">In</span> is an input-iterator type and <span style=\" font-family:'Courier New,courier';\">Out</span> is a forward-iterator type. </p>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 213, just after the last code example: The second sentence should say ``The first statement defines <span style=\" font-family:'Courier New,courier';\">t</span>...'' instead of referring to <span style=\" font-family:'Courier New,courier';\">s</span>. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:"
                        "0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 257, two lines before the beginning of section 14.1.2: <span style=\" font-family:'Courier New,courier';\">student.grade()</span> should be <span style=\" font-family:'Courier New,courier';\">(*student).grade()</span>. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 283, last example: The <span style=\" font-family:'Courier New,courier';\">width</span> function should call <span style=\" font-family:'Courier New,courier';\">std::max</span> explicitly instead of plain <span style=\" font-family:'Courier New,courier';\">max</span>. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 284, last example: The <span style=\" font-family:'Courier New,courier';\">height</span> function should call <span style=\" font-family:'Courier New,courier';\">std::max</span> e"
                        "xplicitly instead of plain <span style=\" font-family:'Courier New,courier';\">max</span>. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 330, the index entry for <span style=\" font-family:'Courier New,courier';\">http://www.accu.org</span> should refer to page 294 (where the URL actually appears) rather than page 293 (where the section begins that contains the URL). </li>\n"
"<li style=\" margin-top:0px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 307: Near the bottom of the table, <span style=\" font-family:'Courier New,courier';\">x</span> <span style=\" font-style:italic;\">op</span><span style=\" font-family:'Courier New,courier';\">=</span> <span style=\" font-family:'Courier New,courier';\">x</span> should be <span style=\" font-family:'Courier New,courier';\">x</span> <span style=\" font-style:italic;\">op</span><span style=\" font-family:'Courier New,courier"
                        "';\">=</span> <span style=\" font-family:'Courier New,courier';\">y</span> </li></ul>\n"
"<p style=\" margin-top:16px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:x-large; font-weight:600;\">Clarifications in the second printing</span> </p>\n"
"<ul style=\"margin-top: 0px; margin-bottom: 0px; margin-left: 0px; margin-right: 0px; -qt-list-indent: 1;\"><li style=\" margin-top:12px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 44 uses the term ``(one past)'' without explaining it. The idea is that if <span style=\" font-family:'Courier New,courier';\">c</span> is a container, <span style=\" font-family:'Courier New,courier';\">c.end()</span> does not refer to the last element, but rather to the imaginary location where the element after the last one would be if it existed. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; tex"
                        "t-indent:0px;\">Page 76, last paragraph before section 5.1.1: The text should make it clear that assigning a new value to <span style=\" font-family:'Courier New,courier';\">students</span> overwrites the previous contents. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 103, immediately after the first example: ``third argument is an iterator'' is clearer if replaced by ``third parameter is required to be an iterator''. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 107, just after the last example: It is clearer to say that <span style=\" font-family:'Courier New,courier';\">static</span> local variables are ``constructed'' than that they are ``created,'' because the storage that the variable occupies is supposed to be allocated when the program begins execution. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:"
                        "0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 135: The explanation of <span style=\" font-family:'Courier New,courier';\">nrand</span> could be clearer. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 142: The second paragraph of section 8.1.2 could be clearer. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 151: The description of <span style=\" font-family:'Courier New,courier';\">ostream_iterator</span> does not make it clear that the second argument must have type <span style=\" font-family:'Courier New,courier';\">const</span> <span style=\" font-family:'Courier New,courier';\">char*</span>. In particular, it cannot be a <span style=\" font-family:'Courier New,courier';\">string</span> or a character literal. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block"
                        "-indent:0; text-indent:0px;\">Page 154: In exercise 8-2, <span style=\" font-family:'Courier New,courier';\">equal(b,</span> <span style=\" font-family:'Courier New,courier';\">e,</span> <span style=\" font-family:'Courier New,courier';\">d)</span> would be clearer as <span style=\" font-family:'Courier New,courier';\">equal(b,</span> <span style=\" font-family:'Courier New,courier';\">e,</span> <span style=\" font-family:'Courier New,courier';\">b2)</span>. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 195, just before the last code example: It should be clearer that we are referring to the copy constructor, as opposed to other constructors. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 201, second paragraph of section 11.3.5: The second sentence should be clearer. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:12px; margin-"
                        "left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 202, last line before the example: the word ``copy'' is ambiguous. </li></ul>\n"
"<p style=\" margin-top:16px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:x-large; font-weight:600;\">Typographical details in the second printing</span> </p>\n"
"<ul style=\"margin-top: 0px; margin-bottom: 0px; margin-left: 0px; margin-right: 0px; -qt-list-indent: 1;\"><li style=\" margin-top:12px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">In various places, <span style=\" font-family:'Courier New,courier';\">container&lt;T&gt;</span> should really appear as <span style=\" font-style:italic;\">container</span><span style=\" font-family:'Courier New,courier';\">&lt;T&gt;</span> because there is no standard type named <span style=\" font-family:'Courier New,courier';\">container</span>; instead, <span style=\" font-style:italic;\">contai"
                        "ner</span> refers to the name of any standard-library container class. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 11: The second-to-last paragraph in the section just before 1.2 should have ``Our'' instead of ``Out'' as its first word. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 21: In the line just before the code example, ``what know'' should be ``what we know''. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 45, second paragraph before the diagram, ``average of value'' in the last line of that paragraph should be ``average value''. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 51: In the seventh line from the bottom, the word ``same'' appears twi"
                        "ce in succession. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 66: In the fourth line from the bottom, the word ``about'' appears twice in a row. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 104: It is useful for the first paragraph to include a reference back to page 88. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 139: In the penultimate line, ``constrains'' should be ``constrain.'' </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 152: The penultimate comment in the first code example is in the wrong font. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 250, thre"
                        "e lines before the last code example: ``(<span style=\" font-family:'Courier New,courier';\">publicly</span>)'' should be ``(<span style=\" font-family:'Courier New,courier';\">public</span>ly)''. </li></ul>\n"
"<p style=\" margin-top:16px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:x-large; font-weight:600;\">Technical errors in the first printing</span> </p>\n"
"<ul style=\"margin-top: 0px; margin-bottom: 0px; margin-left: 0px; margin-right: 0px; -qt-list-indent: 1;\"><li style=\" margin-top:12px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">The calls to <span style=\" font-family:'Courier New,courier';\">setw</span>, such as the one near the bottom of page 64, do not work as advertised. The implementations that we used do not implement <span style=\" font-family:'Courier New,courier';\">setw</span> properly for <span style=\" font-family:'Courier New,courier';\">string</span>s, as we n"
                        "oted in exercise 4-9 (page 74), so we did not discover the problem during testing. </li>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:1; text-indent:0px;\">The most straightforward solution is to replace </p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:2; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">cout &lt;&lt; setw(maxlen+1) &lt;&lt; students[i].name; </span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:1; text-indent:0px;\">by <span style=\" font-family:'Courier New,courier';\">cout &lt;&lt; students[i].name &lt;&lt; string(maxlen+1 - students[i].name.size(), ' '); </span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:1; text-indent:0px;\">thereby obviating exercise 4.9 entirely. Alternatively, one could write <span style=\" font-family:'Couri"
                        "er New,courier';\">cout &lt;&lt; setw(maxlen+1) &lt;&lt; setiosflags(ios_base::left) &lt;&lt; students[i].name &lt;&lt; resetiosflags(ios_base::left); </span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:1; text-indent:0px;\">which would cause <span style=\" font-family:'Courier New,courier';\">cout</span> to left-justify (i.e. pad on the right) while writing <span style=\" font-family:'Courier New,courier';\">students[i].name</span>. </p>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 32: The definition of <span style=\" font-family:'Courier New,courier';\">%</span> in the table should say <span style=\" font-family:'Courier New,courier';\">x - ((x / y) * y)</span> instead of <span style=\" font-family:'Courier New,courier';\">x - ((x - y) * y)</span>. Ditto for the table on page 307. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-"
                        "right:0px; -qt-block-indent:0; text-indent:0px;\">Page 35: The using-directive for <span style=\" font-family:'Courier New,courier';\">std::precision</span> shouldn't be there. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 36: The program might divide by zero if the student enters no grades. Discussing this eventuality in the main text would be a diversion, so we've added a new exercise. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 46: The using-directive for <span style=\" font-family:'Courier New,courier';\">std::precision</span> shouldn't be there. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 47: The line near the middle of the page reading <span style=\" font-family:'Courier New,courier';\">: median = homework[mid];</span></li>\n"
"<p s"
                        "tyle=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:1; text-indent:0px;\">should be <span style=\" font-family:'Courier New,courier';\">: homework[mid];</span> </p>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 54: The phrase ``reference to <span style=\" font-family:'Courier New,courier';\">const</span> <span style=\" font-family:'Courier New,courier';\">double</span>'' near the bottom of the page should be ``reference to <span style=\" font-family:'Courier New,courier';\">vector</span> of <span style=\" font-family:'Courier New,courier';\">const</span> <span style=\" font-family:'Courier New,courier';\">double</span>.'' </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 60: In the program example, the subexpression <span style=\" font-family:'Courier New,courier';\">grade(students[i])</span> should"
                        " be <span style=\" font-family:'Courier New,courier';\">grade(midterm,</span> <span style=\" font-family:'Courier New,courier';\">final,</span> <span style=\" font-family:'Courier New,courier';\">homework)</span>. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 73: The description of the <span style=\" font-family:'Courier New,courier';\">width</span> member function should say that the output is padded on the left, not on the right. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 80: In the first code example on the page, <span style=\" font-family:'Courier New,courier';\">vector&lt;Student::info&gt;</span> should be <span style=\" font-family:'Courier New,courier';\">vector&lt;Student_info&gt;</span>. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Pa"
                        "ge 95: The comments in the program on this page have &quot;left-hand&quot; and &quot;right-hand&quot; reversed. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 97: The definition <span style=\" font-family:'Courier New,courier';\">container&lt;T&gt;</span> <span style=\" font-family:'Courier New,courier';\">c();</span> should be <span style=\" font-family:'Courier New,courier';\">container&lt;T&gt;</span> <span style=\" font-family:'Courier New,courier';\">c;</span> </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 108: The test for <span style=\" font-family:'Courier New,courier';\">i</span> + <span style=\" font-family:'Courier New,courier';\">sep.size()</span> <span style=\" font-family:'Courier New,courier';\">!=</span> <span style=\" font-family:'Courier New,courier';\">e</span> in the inner <span style=\" font-family:'Courier New,c"
                        "ourier';\">if</span> is redundant, as is the test <span style=\" font-family:'Courier New,courier';\">if</span> <span style=\" font-family:'Courier New,courier';\">(i</span> <span style=\" font-family:'Courier New,courier';\">!=</span> <span style=\" font-family:'Courier New,courier';\">e)</span> near the end of the program. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 115: In the last line of section 6.2.3, <span style=\" font-family:'Courier New,courier';\">median_grade</span> should be <span style=\" font-family:'Courier New,courier';\">grade_aux</span>. The <span style=\" font-family:'Courier New,courier';\">average_analysis</span> function does not take into account the possibility that a student did no homework at all. We're going to leave that possibility as an exercise. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 121: Th"
                        "e description of <span style=\" font-family:'Courier New,courier';\">accumulate</span> is wrong. The function copies <span style=\" font-family:'Courier New,courier';\">t</span>, adds each element in the range <span style=\" font-family:'Courier New,courier';\">[b,</span> <span style=\" font-family:'Courier New,courier';\">e)</span> to the copy of <span style=\" font-family:'Courier New,courier';\">t</span>, and returns a copy of the modified copy of <span style=\" font-family:'Courier New,courier';\">t</span> as its result. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 147: In the first paragraph in 8.2.4, it isn't really true that forward iterators prevent us from looking at an element again. What they do is to prevent us from moving an iterator to the immediately preceding element. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 1"
                        "50: In the first sentence of section 8.3, the phrase &quot;separate categories from output iterators&quot; should be &quot;separate categories from forward iterators.&quot; </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 163: In the last paragraph, the claim that users don't need to know how <span style=\" font-family:'Courier New,courier';\">Student_info</span> is implemented isn't quite accurate: They don't need to know in order to write code that uses it, but they do need to know some of the details in order to be able to prepare input files for the program. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 176: The <span style=\" font-family:'Courier New,courier';\">month_lengths</span> array should be defined as <span style=\" font-family:'Courier New,courier';\">const int month_lengths[] = { /* ... */ }; </span></li>\n"
"<li style="
                        "\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 178: The <span style=\" font-family:'Courier New,courier';\">letters</span> array should be defined as <br /><span style=\" font-family:'Courier New,courier';\">static const char* const letters[] = { /* ... */ }; </span><br />because there is no intent ever to change its elements. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 195: The call to <span style=\" font-family:'Courier New,courier';\">split(words)</span> in the last line of the first code example should be <span style=\" font-family:'Courier New,courier';\">split(line)</span>. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 199: The name <span style=\" font-family:'Courier New,courier';\">blanks</span> should be <span style=\" font-family:'Courier New,courier'"
                        ";\">spaces</span>. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 200: The two references to <span style=\" font-family:'Courier New,courier';\">words</span> in the first complete paragraph (the second of which is in a code example) should refer to <span style=\" font-family:'Courier New,courier';\">line</span>. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 220: In the last example on the page, the variables <span style=\" font-family:'Courier New,courier';\">temp</span> and <span style=\" font-family:'Courier New,courier';\">s</span> should be <span style=\" font-family:'Courier New,courier';\">temp1</span> and <span style=\" font-family:'Courier New,courier';\">greeting</span>, respectively. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 221:"
                        " In the second paragraph of section 12.4, we should be talking about <span style=\" font-family:'Courier New,courier';\">Vec</span>, not <span style=\" font-family:'Courier New,courier';\">vector</span>. Moreover, in the hypothetical case, <span style=\" font-family:'Courier New,courier';\">p</span> would contain 42 empty rows, not 42 rows of single null characters. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 249: Just before the last example, the phrase &quot;version of <span style=\" font-family:'Courier New,courier';\">final</span> in <span style=\" font-family:'Courier New,courier';\">Core</span>&quot; should be &quot;version of <span style=\" font-family:'Courier New,courier';\">regrade</span> in <span style=\" font-family:'Courier New,courier';\">Core</span>.&quot; </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 250: Near the"
                        " end of the third line, <span style=\" font-family:'Courier New,courier';\">final</span> should be <span style=\" font-family:'Courier New,courier';\">regrade</span>. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 264: In the first example, the last comment should say &quot;<span style=\" font-style:italic;\">changes only </span><span style=\" font-family:'Courier New,courier';\">s2</span><span style=\" font-style:italic;\"> and not </span><span style=\" font-family:'Courier New,courier';\">s1</span>&quot; instead of &quot;<span style=\" font-style:italic;\">changes only </span><span style=\" font-family:'Courier New,courier';\">s1</span><span style=\" font-style:italic;\"> and not </span><span style=\" font-family:'Courier New,courier';\">s2</span>.&quot; In the following example, the call <span style=\" font-family:'Courier New,courier';\">make_unique();</span> should be <span style=\" font-family:'Courier New,courier';"
                        "\">cp.make_unique();</span> Page 281: in the last line before section 15.2.2, <span style=\" font-family:'Courier New,courier';\">operator&gt;&gt;</span> should be <span style=\" font-family:'Courier New,courier';\">operator&lt;&lt;</span>. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 282: In the last example, the last two parameters should be named <span style=\" font-family:'Courier New,courier';\">beg</span> and <span style=\" font-family:'Courier New,courier';\">end</span>, respectively. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 287: In the discussion near the bottom of the page, <span style=\" font-family:'Courier New,courier';\">protected</span> allows access to the base-class part of any object of the appropriate derived class, not just the base-class part of the current object. What it does not allow is access to membe"
                        "rs of freestanding base-class objects. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 292: Just before the sample output, the text describes the grade histogram as containing asterisks, when it actually contains <span style=\" font-family:'Courier New,courier';\">=</span> symbols. </li></ul>\n"
"<p style=\" margin-top:16px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:x-large; font-weight:600;\">Clarifications in the first printing</span> </p>\n"
"<ul style=\"margin-top: 0px; margin-bottom: 0px; margin-left: 0px; margin-right: 0px; -qt-list-indent: 1;\"><li style=\" margin-top:12px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 28: The description of the <span style=\" font-family:'Courier New,courier';\">for</span> statement should make it clear that the <span style=\" font-style:italic;\">init-s"
                        "tatement</span> is required to be either a definition or an expression statement. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 191: In the first complete paragraph, the two uses of <span style=\" font-family:'Courier New,courier';\">size_t</span> are easier to understand if they refer to <span style=\" font-family:'Courier New,courier';\">size_type</span> instead, to match the code. The two names refer to the same type, so the uses are technically correct, but it's easier to understand if they're changed. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 193: The discussion of the <span style=\" font-family:'Courier New,courier';\">size</span> function at the bottom of the page makes it appear that the type of the difference between two pointers is more important than it really is. The real point is that although the value of <span s"
                        "tyle=\" font-family:'Courier New,courier';\">limit</span> <span style=\" font-family:'Courier New,courier';\">-</span> <span style=\" font-family:'Courier New,courier';\">data</span> has type <span style=\" font-family:'Courier New,courier';\">ptrdiff_t</span>, returning that value from <span style=\" font-family:'Courier New,courier';\">size</span> converts it to <span style=\" font-family:'Courier New,courier';\">size</span>'s return type. </li></ul>\n"
"<p style=\" margin-top:16px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:x-large; font-weight:600;\">Typographical details in the first printing</span> </p>\n"
"<ul style=\"margin-top: 0px; margin-bottom: 0px; margin-left: 0px; margin-right: 0px; -qt-list-indent: 1;\"><li style=\" margin-top:12px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">If a page has any <span style=\" font-family:'Courier New,courier';\">constant-width</span> text "
                        "in the heading at the top of the page (which can happen only for odd-numbered pages), the page number is very slightly smaller than it should be. The affected page numbers are 3, 85, 87, 89, 91, 93, 95, 103, 105, 107, 109, 163, 179, 189, 191, 193, 215, 217, 219, 233, and 235. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page xii: &quot;language&quot; should be &quot;language&quot; near the end of the third paragraph. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 24: Shortly before 2.4.1.2, change &quot;such the ones&quot; to &quot;such as the ones.&quot; </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 30: Change <span style=\" font-family:'Courier New,courier';\">string::size_type</span> to <span style=\" font-family:'Courier New,courier';\">int</s"
                        "pan> in the two <span style=\" font-family:'Courier New,courier';\">for</span> statements at the bottom of the page. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 34: The program in exercise 2-10 should have a <span style=\" font-family:'Courier New,courier';\">return 0;</span> statement at the end. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 45: Near the bottom, change &quot;it should easy&quot; to &quot;it should be easy.&quot; </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 72: The comments in the last example on the page have their beginning slashes in italic font rather than constant-width font. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 158: Th"
                        "e word &quot;have&quot; appears twice in a row in the first paragraph after the numbered list near the top of the page. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 162: The word &quot;the&quot; appears twice in a row in the first complete paragraph on this page. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 164: The word &quot;be&quot; appears twice in a row in paragraph 5, line 3. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 167: In the second line of the paragraph beginning &quot;<span style=\" font-weight:600;\">Protection labels</span>,&quot; &quot;accessible&quot; should be &quot;accessible.&quot; </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 17"
                        "8: In the second complete paragraph from the end of the page, &quot;determine the its type&quot; should be &quot;determine its type.&quot; </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 199: Immediately before the example, &quot;in of an expression&quot; should be &quot;in an expression.&quot; In the last complete paragraph, the word &quot;the&quot; appears twice in a row. </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 203: On the first line of the page, &quot;such this one&quot; should be &quot;such as this one.&quot; </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 224: Near the middle of the page, &quot;does not to prevent&quot; should be &quot;does not prevent.&quot; </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; ma"
                        "rgin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 253: Near the end of the second paragraph, &quot;use the a single&quot; should be &quot;use a single.&quot; </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 260: In the first line of the first complete paragraph, &quot;we would like be able&quot; should be &quot;we would like to be able.&quot; </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 262: In the second paragraph from the end, ``such <span style=\" font-family:'Courier New,courier';\">Student_info</span>'' should be ``such as <span style=\" font-family:'Courier New,courier';\">Student_info</span>.'' </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 283: In the first complete paragraph, &quot;an ordinary member functions&quot; should be "
                        "&quot;an ordinary member function.&quot; </li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 289: In the fourth line, &quot;parameter, type&quot; should be &quot;parameter type.&quot; </li>\n"
"<li style=\" margin-top:0px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Page 307: The table extends beyond the nominal right margin. </li></ul>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><a href=\"109.htm\"><img src=\"images/Prev1.gif\" /></a><a href=\"109.htm\"><span style=\" text-decoration: underline; color:#0000ff;\"> </span></a></p></body></html>", 0, QApplication::UnicodeUTF8));
        dockWidget_3->setWindowTitle(QApplication::translate("MainWindow", "Scene Explorer", 0, QApplication::UnicodeUTF8));
        dockWidget_4->setWindowTitle(QApplication::translate("MainWindow", "Widgets", 0, QApplication::UnicodeUTF8));
        dockWidget_5->setWindowTitle(QApplication::translate("MainWindow", "Properties", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
