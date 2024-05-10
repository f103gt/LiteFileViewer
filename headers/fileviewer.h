#ifndef FILEVIEWER_H
#define FILEVIEWER_H

#include <QWidget>
#include <QObject>
#include <QToolBar>
#include <QLabel>
#include <QScopedPointer>
#include "zoomcommand.h"

/*!
 \\class FileViewer
\\brief The FileViewer class provides an abstract base class for file viewers.

FileViewer is an abstract base class that defines the interface for file viewers in the Lite File Viewer application.
It uses the Template Method design pattern where the `zoom` method is the template method and the `zoomIn` and `zoomOut`
methods are the primitive operations.

\\sa ZoomInCommand, ZoomOutCommand
*/

class FileViewer : public QObject {
    Q_OBJECT
public:
    /*!
    \\brief A constant that defines the zoom factor.
    */
    static constexpr double ZOOM_FACTOR = 1.25;
    /*!
    \\brief Destructor.
    */
    virtual ~FileViewer(){};
    /*!
    \\brief Checks if the viewer supports a toolbar.
    \\return true if the viewer supports a toolbar, false otherwise.
    */
    virtual bool supportsToolbar() const = 0;
    /*!
    \\brief Checks if the viewer supports pagination.
    \\return true if the viewer supports pagination, false otherwise.
    */
    virtual bool supportsPagination() const = 0;
    /*!
    \\brief Navigates to a specific page in the file.
    \\param widget The widget displaying the file.
    \\param page The page number to navigate to.
    */
    virtual void goToPage(QWidget *widget,int page);
    /*!
    \\brief Zooms in on the file.
    \\param currentTab The current tab displaying the file.
    \\param factor The zoom factor.
    */
    virtual void zoomIn(QWidget *currentTab,double factor) = 0;
    /*!
    \\brief Zooms out on the file.
    \\param currentTab The current tab displaying the file.
    \\param
*/
    virtual void zoomOut(QWidget *currentTab,double factor) = 0;
    /*!
    \\brief Checks if the viewer supports search.
    \\return true if the viewer supports search, false otherwise.
    */
    virtual bool supportsSearch();
    /*!
    \\brief Creates a toolbar for the viewer.
    \\return A pointer to the created QToolBar.
    */
    virtual QToolBar* createToolbar();
protected:
    QScopedPointer<ZoomInCommand> zoomInCommand;
    QScopedPointer<ZoomOutCommand> zoomOutCommand;
    /*!
    \\brief Constructor.
    */
    FileViewer();
    /*!
    \\brief Zooms in or out on the file.
    \\param currentTab The current tab displaying the file.
    \\param command The command to execute (ZoomInCommand or ZoomOutCommand).
    \\param factor The zoom factor.
    */
    void zoom(QWidget *currentTab, ZoomCommand* command,double factor);
public slots:
    /*!
    \\brief Opens a file with the given fileName.
    \\param fileName The name of the file to open.
    */
    virtual void open(const QString& fileName) = 0;
    /*!
    \\brief Displays the file data in a widget.
    \\param data The data to display.
    \\return The widget displaying the data.
    */
    virtual QWidget* display(QVariant data) = 0;
signals:
    void fileOpened(QVariant data, const QString& title,const QString& fileExtension);
    void zoomInRequested(double factor);
    void zoomOutRequested(double factor);
    void pageChanged(int currentPage, int totalPages);
};

#endif // FILEVIEWER_H
