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

void MainWindow::closeCurrentTab() {
    int currentIndex = ui->tabWidget->currentIndex();
    ui->tabWidget->removeTab(currentIndex);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onOpenButtonClicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"), "/home",
                                                    tr("All Files (*)"));
    if (!fileName.isEmpty()) {
        QFileInfo fileInfo(fileName);
        QString fileExtension = fileInfo.suffix().toLower();
        if (viewers.contains(fileExtension)) {
            QWidget *widget = viewers[fileExtension]->view(fileName);
            if (widget != nullptr) {
                QWidget *newTab = new QWidget();
                QVBoxLayout *layout = new QVBoxLayout(newTab);
                layout->addWidget(widget);

                ui->tabWidget->addTab(newTab, fileInfo.fileName());
            }
        }
    }
}


void MainWindow::keyPressEvent(QKeyEvent *event){
    if(event->modifiers() & Qt::ControlModifier) {
        QGraphicsView *view = getCurrentTabGraphicsView();
        if(view) {
            if(event->key() == Qt::Key_Plus || event->key()==Qt::Key_Equal) {
                view->scale(1.2, 1.2);
            } else if(event->key() == Qt::Key_Minus) {
                view->scale(1/1.2, 1/1.2);
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



