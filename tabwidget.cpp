#include "tabwidget.h"

#include <QVBoxLayout>

TabWidget::TabWidget(QWidget *parent)
    : QWidget(parent), toolbar(new QToolBar(this)), zoomLabel(new QLabel("Zoom: 100%")), pageLabel(new QLabel("Page: 1/1")) {
    // Setup the toolbar
    toolbar->addWidget(zoomLabel);
    toolbar->addWidget(pageLabel);

    // Layout to organize the toolbar and the content view
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(toolbar);
    // Add your content view to the layout
    // layout->addWidget(contentView);

    setLayout(layout);
}

void TabWidget::setZoomLevel(double zoom)
{
    zoomLabel->setText(QString("Zoom: %1%").arg(zoom * 100));
}

void TabWidget::setPageCount(int currentPage, int totalPages)
{
    pageLabel->setText(QString("Page: %1/%2").arg(currentPage).arg(totalPages));
}
