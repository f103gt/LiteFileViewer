#ifndef FILEVIEWER_H
#define FILEVIEWER_H

#include <QWidget>
#include <QObject>
#include <QToolBar>
#include <QLabel>
#include <QScopedPointer>
#include "zoomcommand.h"

class FileViewer : public QObject {
    Q_OBJECT
public:
    static constexpr double ZOOM_FACTOR = 1.25;
    virtual ~FileViewer(){};
    virtual bool supportsToolbar() const = 0;
    virtual bool supportsPagination() const = 0;
    virtual void goToPage(QWidget *widget,int page) {
        Q_UNUSED(widget)
        Q_UNUSED(page)
    }
    virtual void zoomIn(QWidget *currentTab,double factor) = 0;
    virtual void zoomOut(QWidget *currentTab,double factor) = 0;

    virtual QToolBar* createToolbar(){
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
protected:
    QScopedPointer<ZoomInCommand> zoomInCommand;
    QScopedPointer<ZoomOutCommand> zoomOutCommand;
    FileViewer()
        : zoomInCommand(new ZoomInCommand())
        , zoomOutCommand(new ZoomOutCommand())
    {}

    void zoom(QWidget *currentTab, ZoomCommand* command,double factor) {
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
public slots:
    virtual void open(const QString& fileName) = 0;
    virtual QWidget* display(QVariant data) = 0;
signals:
    void fileOpened(QVariant data, const QString& title,const QString& fileExtension);
    void zoomInRequested(double factor);
    void zoomOutRequested(double factor);
    void pageChanged(int currentPage, int totalPages);
};

#endif // FILEVIEWER_H
