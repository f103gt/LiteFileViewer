#include "imageviewer.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

ImageViewer::ImageViewer() {}

QWidget *ImageViewer::view(const QString &fileName)
{
    // Create a QGraphicsView
    QGraphicsView *view = new QGraphicsView;

    // Create a QGraphicsScene
    QGraphicsScene *scene = new QGraphicsScene;

    // Load the JPG file into a QPixmap
    QPixmap pixmap(fileName);

    // Create a QGraphicsPixmapItem with the QPixmap
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pixmap);

    // Add the QGraphicsPixmapItem to the scene
    scene->addItem(item);

    // Set the scene to the QGraphicsView
    view->setScene(scene);

    // Set the scene's sceneRect to the size of the pixmap
    scene->setSceneRect(pixmap.rect());

    // Align the QGraphicsPixmapItem to center
    item->setPos(scene->sceneRect().center() - item->boundingRect().center());

    // Disable scrollbars
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Set the alignment to center
    view->setAlignment(Qt::AlignCenter);

    // Remove fixed size to allow resizing
    // view->setFixedSize(pixmap.size());

    // Set a minimum size for the view
    view->setMinimumSize(1, 1);

    // Update the view to fit the scene's content
    view->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);

    return view;
}

