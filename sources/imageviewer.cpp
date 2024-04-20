#include "../headers/imageviewer.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QFileInfo>


bool ImageViewer::supportsToolbar() const
{
    return true;
}

bool ImageViewer::supportsPagination() const
{
    return false;
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
    if (!data.canConvert<QPixmap>()) {
        throw std::runtime_error("Failed to convert data to QPixmap");
    }

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
