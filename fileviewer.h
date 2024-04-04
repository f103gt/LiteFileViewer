#ifndef FILEVIEWER_H
#define FILEVIEWER_H
#include <QWidget>

class FileViewer {
public:
    virtual ~FileViewer() {}
    virtual QWidget* view(const QString& fileName) = 0;
};


#endif // FILEVIEWER_H
