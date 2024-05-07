#ifndef TXTVIEWER_H
#define TXTVIEWER_H

#include <QWidget>
#include "fileviewer.h"
#include <QTextEdit>
#include <QIODevice>
#include <QFile>
#include "highlightstrategy.h"

/*!
\\class TxtViewer
\\brief The TxtViewer class provides a viewer for text files.

As all the *Viewer classes, it inherits from FileViewer ablstract classs.
This class provides a viewer for the following file formats - SLQ,JSON,HTML,XML,TXT.
It supports zooming in and out,and can highlight syntax in the text file using a
specified HighlightStrategy. It DOES NOT support pagination !
Also except of the key board short cut navidation,
provides as well Tool Bar for better user experience.

\\sa FileViewer, HighlightStrategy
*/


class TxtViewer : public FileViewer {
    Q_OBJECT
    QScopedPointer<HighlightStrategy> highlightStrategy_;
public:
    /*!
    \\brief Default constructor.
    */
    TxtViewer() = default;
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
    /*!
    \\brief Zooms in the text in the current tab.
    \\param currentTab The current tab.
    \\param factor The zoom factor.
    */
    void zoomIn(QWidget *currentTab,double factor) override;
    /*!
    \\brief Zooms out the text in the current tab.
    \\param currentTab The current tab.
    \\param factor The zoom factor.
    */
    void zoomOut(QWidget *currentTab,double factor) override;
    /*!
    \\brief Checks if the viewer supports search.
    \\return true since the viewer supports search.
    */
    bool supportsSearch() override;
    /*!
    \\brief Sets the highlight strategy.
    \\param strategy The highlight strategy.
    */
    void setHighlightStrategy(HighlightStrategy* strategy){ highlightStrategy_.reset(strategy);}
public slots:
    /*!
\\brief Opens a file with the given fileName.

This method attempts to open a file with the given fileName. If successful,
it emits the fileOpened signal with the file's content, name, and suffix.

\\param fileName The name of the file to open.
*/
    void open(const QString& fileName) override;

    /*!
    \\brief Displays the data in a widget.
    \\param data The data to display.
    \\return The widget displaying the data.
    */
    QWidget* display(QVariant data) override;

};

#endif // TXTVIEWER_H
