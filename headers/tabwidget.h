#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QWidget>
#include <QToolBar>
#include <QLabel>

/*!
\\class TabWidget
\\brief The TabWidget class provides a widget with a toolbar and labels to display zoom level and page count.

This class is designed to be used as a part of an application that requires displaying and manipulating document views.
It includes a toolbar for actions and labels to show the current zoom level and page count.

\\sa QWidget, QToolBar, QLabel
*/

class TabWidget: public QWidget
{
    Q_OBJECT

    /*!< Toolbar containing actions related to the tab. */
    QToolBar *toolbar;
    /*!< Label displaying the current zoom level. */
    QLabel *zoomLabel;
     /*!< Label displaying the current page and total pages. */
    QLabel *pageLabel;

public:
    /*!
    \\brief Default constructor.
    */
    TabWidget() = default;

    /*!
    \\brief Constructor with parent widget.
    \\param parent The parent widget.
    */
    TabWidget(QWidget *parent = nullptr);

    /*!
    \\brief Sets the zoom level in the zoom label.
    \\param zoom The new zoom level to display.
    */
    void setZoomLevel(double zoom);

    /*!
    \\brief Sets the page count in the page label.
    \\param currentPage The current page number.
    \\param totalPages The total number of pages.
    */
    void setPageCount(int currentPage, int totalPages);
};

#endif // TABWIDGET_H
