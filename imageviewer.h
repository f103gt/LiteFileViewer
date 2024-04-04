#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include "fileviewer.h"

class ImageViewer: public FileViewer
{
public:
    ImageViewer();
    QWidget* view(const QString& fileName) override;
};

#endif // IMAGEVIEWER_H
