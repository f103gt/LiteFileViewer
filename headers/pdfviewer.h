#ifndef PDFVIEWER_H
#define PDFVIEWER_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QList>
#include "imageviewer.h"
#include <QObject>

/*!
\\class PdfViewer
\\brief The PdfViewer class provides a viewer for PDF files.

PdfViewer inherits from ImageBasedViewer abstract class.
This class provides a viewer for PDF file format. It supports pagination and
a toolbar for a better user experience. It also allows navigating to a specific
page using the goToPage method.

\\sa ImageBasedViewer
*/

class PdfViewer: public ImageBasedViewer
{
    Q_OBJECT
    const int PAGE_SERAPARATOR = 10;
public:
    /*!
    \\brief Default constructor.
    */
    PdfViewer() = default;
    /*!
    \\brief Checks if the viewer supports a toolbar.
    \\return true since the viewer supports a toolbar.
    */
    bool supportsToolbar() const override;
    /*!
    \\brief Checks if the viewer supports pagination.
    \\return true since the viewer supports pagination.
    */
    bool supportsPagination() const override;
    /*!
    \\brief Navigates to a specific page in the PDF.
    \\param widget The widget displaying the PDF.
    \\param page The page number to navigate to.
    */
    void goToPage(QWidget *widget,int page) override;
public slots:
    /*!
    \\brief Opens a PDF file with the given fileName.

    This method attempts to open a PDF file with the given fileName. If successful,
    it emits the fileOpened signal with the file's content, name, and suffix.

    \\param fileName The name of the file to open.
    */
    void open(const QString& fileName) override;

    /*!
    \\brief Displays the PDF data in a widget.
    \\param data The data to display.
    \\return The widget displaying the data.
    */
    QWidget* display(QVariant data) override;
};

#endif // PDFVIEWER_H
