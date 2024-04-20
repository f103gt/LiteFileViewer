#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include "fileviewer.h"
#include <QObject>
#include <QGraphicsView>

//COMPOSITE
class ImageBasedViewer : public FileViewer {
public:
    virtual ~ImageBasedViewer() {}
    virtual void zoomIn(QWidget *currentTab, double factor) override {
        QGraphicsView* view = currentTab->findChild<QGraphicsView*>();
        if (!view) {
            throw std::runtime_error("Failed to find QGraphicsView in current tab");
        }
        view->scale(factor, factor);
        zoom(currentTab,zoomInCommand.get(),factor);

    }
    virtual void zoomOut(QWidget *currentTab, double factor) override {
        QGraphicsView* view = currentTab->findChild<QGraphicsView*>();
        if (!view) {
            throw std::runtime_error("Failed to find QGraphicsView in current tab");
        }
        view->scale(1/factor, 1/factor);
        zoom(currentTab,zoomOutCommand.get(),factor);
    }
};

class ImageViewer: public ImageBasedViewer
{
    Q_OBJECT
public:
    ImageViewer() = default;
    ~ImageViewer() = default;
    bool supportsToolbar() const override;
    bool supportsPagination() const override;
    // void zoomIn(QWidget *currentTab,double factor) override;
    // void zoomOut(QWidget *currentTab,double factor) override;
public slots:
    void open(const QString& fileName) override;
    QWidget* display(QVariant data) override;
};

#endif // IMAGEVIEWER_H
