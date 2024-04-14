#include "imageviewer.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QFileInfo>


void ImageViewer::zoomIn(QWidget *currentTab, double factor)
{
    QGraphicsView* view = currentTab->findChild<QGraphicsView*>();
    if (view) {
        view->scale(factor, factor);
    } else {
        qDebug() << "Failed to find QGraphicsView in current tab";
    }
}

void ImageViewer::zoomOut(QWidget *currentTab, double factor)
{
    QGraphicsView* view = currentTab->findChild<QGraphicsView*>();
    if (view) {
        view->scale(1/factor, 1/factor);
    } else {
        qDebug() << "Failed to find QGraphicsView in current tab";
    }
}

void ImageViewer::open(const QString &fileName)
{
    QPixmap pixmap(fileName);

    QFileInfo fileInfo(fileName);
    emit fileOpened(QVariant::fromValue(pixmap),
                    fileInfo.fileName(),
                    fileInfo.suffix().toLower());
}

QWidget* ImageViewer::display(QVariant data)
{
    QPixmap pixmap = data.value<QPixmap>();
    QGraphicsView *view = new QGraphicsView;
    QGraphicsScene *scene = new QGraphicsScene;
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pixmap);

    scene->addItem(item);
    view->setScene(scene);

    scene->setSceneRect(pixmap.rect());
    item->setPos(scene->sceneRect().center() - item->boundingRect().center());

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    view->setAlignment(Qt::AlignCenter);
    view->setMinimumSize(1, 1);

    view->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);

    return view;
}
