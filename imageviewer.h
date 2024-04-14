#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include "fileviewer.h"
#include <QObject>

class ImageViewer: public FileViewer
{
    Q_OBJECT
public:
    ImageViewer() = default;
    ~ImageViewer() = default;
    bool supportsToolbar() const override;
    bool supportsPagination() const override;
    void zoomIn(QWidget *currentTab,double factor) override;
    void zoomOut(QWidget *currentTab,double factor) override;
    QToolBar* createToolbar() override;
public slots:
    void open(const QString& fileName) override;
    QWidget* display(QVariant data) override;
};

#endif // IMAGEVIEWER_H
