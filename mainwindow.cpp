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


    ui->stackedWidget->setCurrentWidget(ui->welcomeLabel);

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
        QVBoxLayout *layout = new QVBoxLayout(newTab);
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
            // Adjusting the lambda function to match the signal signature
            connect(viewer, &FileViewer::fileOpened, this, [this](const QVariant &data,const QString &title, const QString &fileExtension) {
                this->addTab(data, title, fileExtension);
            });

            connect(thread, &QThread::finished, viewer, &QObject::deleteLater);
            thread->start();
            QMetaObject::invokeMethod(viewer, "open", Q_ARG(QString, fileName));
        }
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
            ui->zoomLabel->setVisible(true);
            ui->zoomLabel->setText(QString("Zoom: %1%").arg(zoomLevel * 100));
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



