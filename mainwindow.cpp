#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSharedPointer>
#include <QKeyEvent>
#include "txtviewer.h"
#include "pdfviewer.h"
#include "csvviewer.h"
#include "imageviewer.h"
#include <QDebug>
#include <QShortcut>
#include <QThread>
#include <QLineEdit>
#include <QSettings>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    viewers["txt"] = new TxtViewer;
    viewers["pdf"] = new PdfViewer;
    viewers["csv"] = &CsvViewer::getInstance();
    viewers["jpg"] = new ImageViewer;
    viewers["png"] = new ImageViewer;

    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::onOpenButtonClicked);

    connect(ui->actionClose, &QAction::triggered, this, &MainWindow::closeCurrentTab);

    connect(ui->tabWidget, &QTabWidget::currentChanged, this, [=]() {
        checkTabCount();
    });

    // Initialize recent file actions and connect them to openRecentFile
    for (int i = 0; i < MaxRecentFiles; ++i) {
        recentFileActs[i] = ui->recentFileActs[i];
        connect(recentFileActs[i], &QAction::triggered, this, &MainWindow::openRecentFile);
    }

    // Load the recent files and update the actions
    updateRecentFileActions();

    ui->stackedWidget->setCurrentWidget(ui->welcomeLabel);

}

void MainWindow::openRecentFile()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (action)
    {
        QString fileName = action->data().toString();
        // Load the file and set it as the current file
        loadFile(fileName);
        setCurrentFile(fileName);
    }
}

void MainWindow::loadFile(const QString &fileName)
{
    QFileInfo fileInfo(fileName);
    QString fileExtension = fileInfo.suffix().toLower();
    if (viewers.contains(fileExtension)) {
        QThread* thread = new QThread;
        FileViewer* viewer = viewers[fileExtension];
        viewer->moveToThread(thread);
        disconnect(viewer, &FileViewer::fileOpened, this, nullptr);

        connect(viewer, &FileViewer::fileOpened, this, [this](const QVariant &data,const QString &title, const QString &fileExtension) {
            this->addTab(data, title, fileExtension);
        });

        connect(thread, &QThread::finished, viewer, &QObject::deleteLater);
        thread->start();
        QMetaObject::invokeMethod(viewer, "open", Q_ARG(QString, fileName));
    }
}


void MainWindow::updateRecentFileActions()
{
    QSettings settings("YourCompany", "YourApp");
    QStringList files = settings.value("recentFileList").toStringList();

    int numRecentFiles = qMin(files.size(), (int)MaxRecentFiles);

    for (int i = 0; i < numRecentFiles; ++i) {
        QString text = tr("&%1").arg(files[i]); // Include the full file path
        recentFileActs[i]->setText(text);
        recentFileActs[i]->setData(files[i]);
        recentFileActs[i]->setVisible(true);
    }
    for (int j = numRecentFiles; j < MaxRecentFiles; ++j)
        recentFileActs[j]->setVisible(false);
}


void MainWindow::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    setWindowModified(false);

    QString shownName = curFile;
    if (curFile.isEmpty())
        shownName = "untitled.txt";
    setWindowFilePath(shownName);

    QSettings settings("YourCompany", "YourApp");
    QStringList files = settings.value("recentFileList").toStringList();
    files.removeAll(fileName); // If the file is already in the list, it is removed
    files.prepend(fileName); // The file is added to the beginning of the list
    while (files.size() > MaxRecentFiles) // If the list is too big, the last file is removed
        files.removeLast();

    settings.setValue("recentFileList", files);

    foreach (QWidget *widget, QApplication::topLevelWidgets()) {
        MainWindow *mainWin = qobject_cast<MainWindow *>(widget);
        if (mainWin)
            mainWin->updateRecentFileActions();
    }
}


void MainWindow::checkTabCount() const
{
    if (ui->tabWidget->count() == 0)
        ui->stackedWidget->setCurrentWidget(ui->welcomeLabel);
    else
        ui->stackedWidget->setCurrentWidget(ui->tabWidget);
}


void MainWindow::addTab(QVariant data, const QString &title,const QString& fileExension)
{
    QFileInfo fileInfo(title);
    QString fileExtension = fileInfo.suffix().toLower();
    QWidget *widget = viewers[fileExension]->display(data);
    if (widget != nullptr) {
        QWidget *newTab = new QWidget();
        newTab->setProperty("zoomLevel", 1.0);
        QVBoxLayout *layout = new QVBoxLayout(newTab);
        if (viewers[fileExension]->supportsToolbar()) {
            QToolBar *toolbar = viewers[fileExension]->createToolbar();
            if(toolbar){
                layout->addWidget(toolbar);
                connect(viewers[fileExension], &FileViewer::zoomInRequested,this, [this, newTab, fileExtension](double factor) {
                    viewers[fileExtension]->zoomIn(newTab, factor);
                });
                connect(viewers[fileExension], &FileViewer::zoomOutRequested,this, [this, newTab, fileExtension](double factor) {
                    viewers[fileExtension]->zoomOut(newTab, factor);
                });
                if(viewers[fileExension]->supportsPagination()){
                    QLabel *pageLabel = new QLabel();
                    toolbar->addWidget(pageLabel);
                    QLineEdit *pageLineEdit = new QLineEdit();
                    toolbar->addWidget(pageLineEdit);
                    connect(viewers[fileExtension], &FileViewer::pageChanged, this,[pageLabel](int currentPage, int totalPages) {
                        pageLabel->setText(QString("%1/%2").arg(currentPage).arg(totalPages));
                    });
                    connect(pageLineEdit, &QLineEdit::returnPressed, this,[this, pageLineEdit,widget, fileExtension](){
                        int page = pageLineEdit->text().split('/')[0].toInt();
                        auto pixmaps = widget->property("pixmaps").value<QList<QPixmap>>();
                        if (page >= 1 && page <= pixmaps.size()) {
                            viewers[fileExtension]->goToPage(widget,page);
                        } else {
                            //TODO HANDLE PROPERLY
                            qDebug()<<"INVALID PAGE NUMBER\n";
                        }
                    });


                }
            }

        }
        layout->addWidget(widget);

        newTab->setProperty("fileExtension", fileExtension);
        ui->tabWidget->addTab(newTab, title);
    }
}


void MainWindow::onOpenButtonClicked() {
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"), "/home",
                                                    tr("All Files (*)"));
    if (!fileName.isEmpty()) {
        QFileInfo fileInfo(fileName);
        QString fileExtension = fileInfo.suffix().toLower();
        if (viewers.contains(fileExtension)) {
            QThread* thread = new QThread;
            FileViewer* viewer = viewers[fileExtension];
            viewer->moveToThread(thread);
            disconnect(viewer, &FileViewer::fileOpened, this, nullptr);

            connect(viewer, &FileViewer::fileOpened, this, [this](const QVariant &data,const QString &title, const QString &fileExtension) {
                this->addTab(data, title, fileExtension);
            });

            connect(thread, &QThread::finished, viewer, &QObject::deleteLater);
            thread->start();
            QMetaObject::invokeMethod(viewer, "open", Q_ARG(QString, fileName));
        }
        setCurrentFile(fileName);
    }
}


void MainWindow::closeCurrentTab() {
    int currentIndex = ui->tabWidget->currentIndex();
    ui->tabWidget->removeTab(currentIndex);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//TODDO MAYBE REPLACE WITH SHORTCUT
void MainWindow::keyPressEvent(QKeyEvent *event){
    if(event->modifiers() & Qt::ControlModifier) {
        QWidget *view = ui->tabWidget->currentWidget();

        if(view) {
            QString fileExtension = view->property("fileExtension").toString();
            if(event->key() == Qt::Key_Plus || event->key()==Qt::Key_Equal) {
                viewers[fileExtension]->zoomIn(view,1.2);
            } else if(event->key() == Qt::Key_Minus) {
                viewers[fileExtension]->zoomOut(view,1.2);
            }
        }
    }
}


QGraphicsView* MainWindow::getCurrentTabGraphicsView() const{
    QWidget *currentTab = ui->tabWidget->currentWidget();
    if (!currentTab) {
        return nullptr;
    }
    QGraphicsView *view = currentTab->findChild<QGraphicsView *>();
    return view;
}



