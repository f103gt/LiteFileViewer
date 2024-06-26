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
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QtWidgets/QSplitter>
#include <QList>
#include <QtWidgets/QStackedLayout>
#include <QFileDialog>
#include <QStackedWidget>
#include <array>


QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionClose;
    QAction *actionRecentFiles;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *centerLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *widget;
    QGridLayout *gridLayout;
    QListWidget *listWidget;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuRecentFiles;
    QSplitter* splitter;
    QLabel* welcomeLabel;
    QStackedWidget* stackedWidget;


    static const int MaxRecentFiles = 10;
    std::array<QAction *, MaxRecentFiles> recentFileActs;


    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);

        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");

        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName("actionOpen");
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName("actionClose");
        actionRecentFiles = new QAction(MainWindow);
        actionRecentFiles->setObjectName("actionRecentFiles");

        welcomeLabel = new QLabel("Ctrl+O Open new file\nCtrl+W Close current file\nCtrl+ (Ctrl=) Zoom In\nCtrl- Zoom Out");
        welcomeLabel->setObjectName("welcomeLabel");
        welcomeLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(welcomeLabel);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");

        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->addWidget(welcomeLabel);
        stackedWidget->addWidget(tabWidget);

        centerLayout = new QVBoxLayout();
        centerLayout->addWidget(stackedWidget);

        verticalLayout->addLayout(centerLayout);

        MainWindow->setCentralWidget(centralwidget);

        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        MainWindow->setMenuBar(menubar);

        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));

        menuRecentFiles = new QMenu(menuFile);
        menuRecentFiles->setObjectName("menuRecentFiles");
        menuRecentFiles->setTitle(QCoreApplication::translate("MainWindow", "Recent Files", nullptr));
        for (int i = 0; i < MaxRecentFiles; ++i) {
            recentFileActs[i] = new QAction(MainWindow);
            recentFileActs[i]->setVisible(false);
            menuRecentFiles->addAction(recentFileActs[i]);
        }

        menuFile->addAction(actionOpen);
        menuFile->addAction(actionClose);
        menuFile->addSeparator();
        menuFile->addMenu(menuRecentFiles);

        menubar->addMenu(menuFile);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    }



    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
#if QT_CONFIG(shortcut)
        actionOpen->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        actionClose->setText(QCoreApplication::translate("MainWindow", "Close", nullptr));
#if QT_CONFIG(shortcut)
        actionClose->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+W", nullptr));
#endif // QT_CONFIG(shortcut)
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "Home", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

