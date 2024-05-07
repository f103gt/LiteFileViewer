#ifndef CSVVIEWER_H
#define CSVVIEWER_H

#include "fileviewer.h"

/*!
 \\class CsvViewer
 \\brief The CsvViewer class provides a concrete implementation of the FileViewer for CSV files.

 CsvViewer is a singleton class that inherits from the FileViewer abstract base class. It provides the functionality to open and display CSV files in a QTableWidget. It also supports zooming in and out of the displayed CSV file.

 \\sa FileViewer
*/

class CsvViewer: public FileViewer
{
    Q_OBJECT

    /*!
     \\brief Private constructor for the singleton class.
    */
    CsvViewer() = default;
public:
    /*!
     \\brief Delete the copy constructor.
    */
    CsvViewer(CsvViewer const&) = delete;
    /*!
     \\brief Delete the assignment operator.
    */
    void operator=(CsvViewer const&) = delete;
    /*!
     \\brief Get the singleton instance.
     \\return A reference to the singleton instance.
    */
    static CsvViewer& getInstance();
    /*!
     \\brief Check if the viewer supports a toolbar.
     \\return true if the viewer supports a toolbar, false otherwise.
    */
    bool supportsToolbar() const override;
    /*!
     \\brief Check if the viewer supports pagination.
     \\return true if the viewer supports pagination, false otherwise.
    */
    bool supportsPagination() const override;
    /*!
     \\brief Zoom in on the displayed CSV file.
     \\param currentTab The current tab displaying the file.
     \\param factor The zoom factor.
    */
    void zoomIn(QWidget *currentTab,double factor) override;
    /*!
     \\brief Zoom out on the displayed CSV file.
     \\param currentTab The current tab displaying the file.
     \\param factor The zoom factor.
    */
    void zoomOut(QWidget *currentTab,double factor) override;
public slots:
    /*!
     \\brief Open a CSV file.
     \\param fileName The name of the file to open.
    */
    void open(const QString& fileName) override;
    /*!
     \\brief Display the CSV file data in a QTableWidget.
     \\param data The data to display.
     \\return The widget displaying the data.
    */
    QWidget* display(QVariant data) override;
};

#endif // CSVVIEWER_H
