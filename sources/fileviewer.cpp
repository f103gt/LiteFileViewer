#include "../headers/fileviewer.h"

void FileViewer::goToPage(QWidget *widget,int page) {
    Q_UNUSED(widget)
    Q_UNUSED(page)
}

bool FileViewer::supportsSearch(){return false;}

FileViewer::FileViewer()
    : zoomInCommand(new ZoomInCommand())
    , zoomOutCommand(new ZoomOutCommand())
{}

void  FileViewer::zoom(QWidget *currentTab, ZoomCommand* command,double factor) {
    double zoomLevel = currentTab->property("zoomLevel").toDouble();
    zoomLevel = command->calculateZoomLevel(zoomLevel, factor);
    currentTab->setProperty("zoomLevel", zoomLevel);
    QToolBar *toolbar = currentTab->findChild<QToolBar*>();

    if (!toolbar) {
        throw std::runtime_error("Failed to find QToolBar in current tab");
    }

    QLabel *zoomLabel = toolbar->findChild<QLabel*>("zoomLabel");
    if (!zoomLabel) {
        throw std::runtime_error("Failed to find zoom label in toolbar");
    }

    zoomLabel->setText(QString("Zoom: %1%").arg(qRound(zoomLevel * 100)));

}

QToolBar*  FileViewer::createToolbar(){
    if(!supportsToolbar()){return nullptr;}
    auto toolbar = std::make_unique<QToolBar>();
    toolbar->setMovable(true);

    QAction *zoomInAction = toolbar->addAction("+");
    if (!zoomInAction) {
        throw std::runtime_error("Failed to create zoom in action.");
    }

    QLabel *zoomLabel = new QLabel("Zoom: 100%");
    if (!zoomInAction) {
        throw std::runtime_error("Failed to create zoom in action.");
    }

    zoomLabel->setObjectName("zoomLabel");

    toolbar->addWidget(zoomLabel);

    QAction *zoomOutAction = toolbar->addAction("-");
    if (!zoomOutAction) {
        throw std::runtime_error("Failed to create zoom out action.");
    }

    connect(zoomInAction, &QAction::triggered,this, [this]() {
        emit zoomInRequested(ZOOM_FACTOR);
    });
    connect(zoomOutAction, &QAction::triggered, this,[this]() {
        emit zoomOutRequested(ZOOM_FACTOR);
    });
    QLabel *pageLabel = new QLabel();
    if (!pageLabel) {
        throw std::runtime_error("Failed to create page label.");
    }

    toolbar->addWidget(pageLabel);

    return toolbar.release();
}
