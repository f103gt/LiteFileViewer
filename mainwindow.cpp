#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSharedPointer>
#include <QKeyEvent>
#include "txtviewer.h"
#include "pdfviewer.h"
#include "csvviewer.h"
#include "imageviewer.h"
#include <QDebug>

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
        // Get the file extension
        QFileInfo fileInfo(fileName);
        QString fileExtension = fileInfo.suffix().toLower();
        // Check if we have a viewer for this file type
        if (viewers.contains(fileExtension)) {
            // Use the viewer to create a widget for this file
            QWidget *widget = viewers[fileExtension]->view(fileName);
            if (widget != nullptr) {
                // Create a new tab
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
        // Get the QGraphicsView of the currently active tab
        QGraphicsView *view = getCurrentTabGraphicsView();
        if(view) {
            if(event->key() == Qt::Key_Plus) {
                // Zoom in
                view->scale(1.2, 1.2);
            } else if(event->key() == Qt::Key_Minus) {
                // Zoom out
                view->scale(1/1.2, 1/1.2);
            }
        }
    }
}



QGraphicsView* MainWindow::getCurrentTabGraphicsView() const{
    // Get the currently active tab
    QWidget *currentTab = ui->tabWidget->currentWidget();
    if (!currentTab) {
        return nullptr;
    }

    // Find the QGraphicsView in the current tab
    QGraphicsView *view = currentTab->findChild<QGraphicsView *>();
    return view;
}



