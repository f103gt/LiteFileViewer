#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QtWidgets/QSplitter>
#include <QList>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QStackedLayout>
#include <QFileDialog>


QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionClose;
    QAction *actionRead;
    QAction *actionConvert;
    QAction *actionCompress;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *widget;
    QGridLayout *gridLayout;
    QListWidget *listWidget;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;
    QToolBar *toolBar;
    QSplitter* splitter;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName("actionOpen");
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName("actionSave");
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName("actionClose");
        actionRead = new QAction(MainWindow);
        actionRead->setObjectName("actionRead");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/image/read-file.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRead->setIcon(icon);
        actionRead->setMenuRole(QAction::NoRole);
        actionConvert = new QAction(MainWindow);
        actionConvert->setObjectName("actionConvert");

        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/image/file-converter.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionConvert->setIcon(icon1);
        actionConvert->setMenuRole(QAction::NoRole);
        actionConvert->setShortcutVisibleInContextMenu(false);
        actionCompress = new QAction(MainWindow);
        actionCompress->setObjectName("actionCompress");

        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/image/compress-file.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCompress->setIcon(icon2);
        actionCompress->setMenuRole(QAction::NoRole);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setAutoFillBackground(true);
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        tabWidget = new QTabWidget(centralwidget);



        tab = new QWidget();
        tab->setObjectName("tab");

        QGridLayout *gridLayout = new QGridLayout(tab);
        gridLayout->setObjectName("gridLayout");


        // Create a new QWidget to hold the label and list widget
        QWidget *listWidgetContainer = new QWidget();
        QVBoxLayout *listLayout = new QVBoxLayout();

        QLabel *listLabel = new QLabel("Recent Files");
        QListWidget *listWidget = new QListWidget();
        listWidget->setObjectName("listWidget");
        listWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

        listLayout->addWidget(listLabel);
        listLayout->addWidget(listWidget);
        listWidgetContainer->setLayout(listLayout);

        QWidget *buttonWidget = new QWidget();
        QVBoxLayout *buttonLayout = new QVBoxLayout();


        QPushButton* openButton = new QPushButton("Open");
        openButton->setFixedSize(200, 25);
        openButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        //buttonLayout->addStretch();
        buttonLayout->addWidget(openButton, 0, Qt::AlignCenter); // Align the button to the center
        buttonLayout->addStretch();
        buttonWidget->setLayout(buttonLayout);

        QObject::connect(openButton, SIGNAL(clicked()), MainWindow, SLOT(on_openButton_clicked()));


        // Add list widget container and button to the grid layout
        gridLayout->addWidget(listWidgetContainer, 0, 0); // Add list widget container to the first column
        gridLayout->addWidget(buttonWidget, 0, 1); // Add button to the second column

        // Set the stretch factors for the columns
        gridLayout->setColumnStretch(0, 1); // First column takes up 1/5 of the width
        gridLayout->setColumnStretch(1, 4);


        tabWidget->addTab(tab, QString("Home"));

        verticalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName("toolBar");
        toolBar->setBaseSize(QSize(0, 0));
        toolBar->setAllowedAreas(Qt::LeftToolBarArea);
        toolBar->setIconSize(QSize(40, 50));
        toolBar->setFloatable(false);
        MainWindow->addToolBar(Qt::LeftToolBarArea, toolBar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionClose);
        toolBar->addAction(actionRead);
        toolBar->addAction(actionConvert);
        toolBar->addAction(actionCompress);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
#if QT_CONFIG(shortcut)
        actionOpen->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSave->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
#if QT_CONFIG(shortcut)
        actionSave->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionClose->setText(QCoreApplication::translate("MainWindow", "Close", nullptr));
#if QT_CONFIG(shortcut)
        actionClose->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+W", nullptr));
#endif // QT_CONFIG(shortcut)
        actionRead->setText(QCoreApplication::translate("MainWindow", "Read", nullptr));
        actionConvert->setText(QCoreApplication::translate("MainWindow", "Convert", nullptr));
        actionCompress->setText(QCoreApplication::translate("MainWindow", "Compress", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "Home", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H


//TODO REMOVE ACTION COMPRESS
