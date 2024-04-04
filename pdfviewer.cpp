#include "pdfviewer.h"
#include <QPdfDocument>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>


QWidget *PdfViewer::view(const QString &fileName)
{
    // Load the PDF document
    auto pdfDocument = new QPdfDocument;
    pdfDocument->load(fileName);

    // Create a QGraphicsScene and QGraphicsView
    auto scene = new QGraphicsScene;
    auto view = new QGraphicsView(scene);
    DecoratedScene decoratedScene(scene);

    // Render each page of the PDF as an image and add it to the scene
    int yOffset = 0;
    CompositeItem compositeItem;
    for (int i = 0; i < pdfDocument->pageCount(); ++i) {
        QSize imageSize = view->size()*3;  // Set the desired image size
        QImage image = pdfDocument->render(i, imageSize);
        QPixmap pixmap = QPixmap::fromImage(image);

        // Add the pixmap to the scene at the correct position
        auto item = new QGraphicsPixmapItem(pixmap);
        item->setPos(0, yOffset);
        compositeItem.add(item);

        // Update the yOffset for the next page
        yOffset += pixmap.height() + 10;
    }
    compositeItem.drawItems(&decoratedScene);
    return view;
}

DecoratedScene::DecoratedScene(QGraphicsScene *scene) :scene(scene){}

void DecoratedScene::addItem(QGraphicsPixmapItem *item)
{
    scene->addItem(item);
}

void CompositeItem::add(QGraphicsPixmapItem *item)
{
    items.append(item);
}

void CompositeItem::drawItems(DecoratedScene *scene)
{
    for (auto item : items) {
        scene->addItem(item);
    }
}
