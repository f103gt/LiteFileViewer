#ifndef CSVVIEWER_H
#define CSVVIEWER_H

#include "fileviewer.h"

class CsvViewer: public FileViewer
{
public:
    CsvViewer(CsvViewer const&) = delete;
    void operator=(CsvViewer const&) = delete;
    QWidget* view(const QString& fileName) override;
    static CsvViewer& getInstance();
private:
    CsvViewer();
};

#endif // CSVVIEWER_H
