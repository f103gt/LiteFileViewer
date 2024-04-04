#ifndef PDFVIEWER_H
#define PDFVIEWER_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QList>
#include "fileviewer.h"

class DecoratedScene: public QGraphicsScene{
    QGraphicsScene* scene;
public:
    explicit DecoratedScene(QGraphicsScene* scene);
    void addItem(QGraphicsPixmapItem* item);
};


class CompositeItem: public QGraphicsPixmapItem{
    QList<QGraphicsPixmapItem*> items;
public:
    void add(QGraphicsPixmapItem* item);
    void drawItems(DecoratedScene* scene);
};

class PdfViewer: public FileViewer
{
public:
    PdfViewer() = default;
    QWidget* view(const QString& fileName) override;
};

#endif // PDFVIEWER_H
