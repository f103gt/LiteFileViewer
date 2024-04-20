#ifndef PDFVIEWER_H
#define PDFVIEWER_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QList>
#include "imageviewer.h"
#include <QObject>

class PdfViewer: public ImageBasedViewer
{
    Q_OBJECT
    const int PAGE_SERAPARATOR = 10;
public:
    PdfViewer() = default;
    bool supportsToolbar() const override;
    bool supportsPagination() const override;
    void goToPage(QWidget *widget,int page) override;
public slots:
    void open(const QString& fileName) override;
    QWidget* display(QVariant data) override;
};

#endif // PDFVIEWER_H
