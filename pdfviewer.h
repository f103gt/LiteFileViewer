#ifndef PDFVIEWER_H
#define PDFVIEWER_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QList>
#include "fileviewer.h"
#include <QObject>

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
    Q_OBJECT
public:
    PdfViewer() = default;
public slots:
   void open(const QString& fileName) override;
    QWidget* display(QVariant data) override;
};

#endif // PDFVIEWER_H
