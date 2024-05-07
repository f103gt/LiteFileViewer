#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include "fileviewer.h"
#include <QObject>
#include <QGraphicsView>

/*!
\\class ImageBasedViewer
\\brief The ImageBasedViewer class is an abstract class for viewers that display image-based content.

This class provides the basic functionalities for zooming in and out of images. It is designed to be
subclassed by viewers that handle image-based file formats.

\\sa FileViewer
*/

class ImageBasedViewer : public FileViewer {
public:
    virtual ~ImageBasedViewer() {}
    virtual void zoomIn(QWidget *currentTab, double factor) override;
    virtual void zoomOut(QWidget *currentTab, double factor) override;
};

/*!
\\class ImageViewer
\\brief The ImageViewer class provides a viewer for image files.

As a subclass of ImageBasedViewer, it inherits the zooming functionalities. This class is specifically
tailored for image file formats such as JPG and PNG. It supports a toolbar for better user experience
but does not support pagination.

\\sa ImageBasedViewer
*/

class ImageViewer: public ImageBasedViewer
{
    Q_OBJECT
public:
    ImageViewer() = default;
    ~ImageViewer() = default;
    /*!
    \\brief Checks if the viewer supports a toolbar.
    \\return true since the viewer supports a toolbar.
    */
    bool supportsToolbar() const override;
    /*!
    \\brief Checks if the viewer supports pagination.
    \\return false since the viewer does not support pagination.
    */
    bool supportsPagination() const override;
public slots:
    /*!
    \\brief Opens an image file with the given fileName.

    This method attempts to open an image file with the given fileName. If successful,
    it emits the fileOpened signal with the file's pixmap, name, and suffix.

    \\param fileName The name of the file to open.
    */
    void open(const QString& fileName) override;
    /*!
    \\brief Displays the image data in a widget.
    \\param data The data to display.
    \\return The widget displaying the data.
    */
    QWidget* display(QVariant data) override;
};

#endif // IMAGEVIEWER_H
