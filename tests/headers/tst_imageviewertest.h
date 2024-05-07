#ifndef TST_IMAGEVIEWERTEST_H
#define TST_IMAGEVIEWERTEST_H

#include "../file-reader/headers/imageviewer.h"

class ImageViewerTest : public QObject
{
    Q_OBJECT
    std::unique_ptr<ImageViewer> viewer;
    const QString fileName = "/path/to/your/image/file.jpg";
public:
    ImageViewerTest();
    ~ImageViewerTest() = default;

private slots:
    void testOpen();
    void testDisplay();
};


#endif // TST_IMAGEVIEWERTEST_H
