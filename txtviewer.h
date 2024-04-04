#ifndef TXTVIEWER_H
#define TXTVIEWER_H

#include <QWidget>
#include "fileviewer.h"
#include <QTextEdit>
#include <QIODevice>
#include <QFile>

class TxtViewer : public FileViewer {
public:
    TxtViewer() = default;
    QWidget* view(const QString& fileName) override;
};

#endif // TXTVIEWER_H
