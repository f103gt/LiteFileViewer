#ifndef CSVVIEWER_H
#define CSVVIEWER_H

#include "fileviewer.h"

class CsvViewer: public FileViewer
{
    Q_OBJECT

    CsvViewer() = default;
public:
    CsvViewer(CsvViewer const&) = delete;
    void operator=(CsvViewer const&) = delete;
    static CsvViewer& getInstance();
    bool supportsToolbar() const override;
    bool supportsPagination() const override;
    void zoomIn(QWidget *currentTab,double factor) override;
    void zoomOut(QWidget *currentTab,double factor) override;
public slots:
    void open(const QString& fileName) override;
    QWidget* display(QVariant data) override;
};

#endif // CSVVIEWER_H
