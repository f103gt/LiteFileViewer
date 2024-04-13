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
public slots:
    void open(const QString& fileName) override;
    QWidget* display(QVariant data) override;
};

#endif // IMAGEVIEWER_H
