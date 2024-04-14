#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QWidget>
#include <QToolBar>
#include <QLabel>

class TabWidget: public QWidget
{
    Q_OBJECT

    QToolBar *toolbar;
    QLabel *zoomLabel;
    QLabel *pageLabel;
public:
    TabWidget() = default;
    TabWidget(QWidget *parent = nullptr);

    // Methods to update the zoom level and page count
    void setZoomLevel(double zoom);
    void setPageCount(int currentPage, int totalPages);
};

#endif // TABWIDGET_H
