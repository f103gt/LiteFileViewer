#ifndef TXTVIEWER_H
#define TXTVIEWER_H

#include <QWidget>
#include "fileviewer.h"
#include <QTextEdit>
#include <QIODevice>
#include <QFile>

class TxtViewer : public FileViewer {
    Q_OBJECT
public:
    TxtViewer() = default;
    void zoomIn(QWidget *currentTab,double factor) override;
    void zoomOut(QWidget *currentTab,double factor) override;
public slots:
    void open(const QString& fileName) override;
    QWidget* display(QVariant data) override;

};

#endif // TXTVIEWER_H
