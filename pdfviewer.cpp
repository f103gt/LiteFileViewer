#include "pdfviewer.h"
#include <QPdfDocument>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QFileInfo>
#include <QPainter>
#include <QDebug>


void PdfViewer::zoomIn(QWidget *currentTab, double factor)
{
    QGraphicsView* view = currentTab->findChild<QGraphicsView*>();
    if (view) {
        view->scale(factor, factor);
    } else {
        qDebug() << "Failed to find QGraphicsView in current tab";
    }
}


void PdfViewer::zoomOut(QWidget *currentTab, double factor)
{
    QGraphicsView* view = currentTab->findChild<QGraphicsView*>();
    if (view) {
        view->scale(1/factor, 1/factor);
    } else {
        qDebug() << "Failed to find QGraphicsView in current tab";
    }
}

void PdfViewer::open(const QString &fileName)
{
    QFileInfo fileInfo(fileName);
    auto pdfDocument = new QPdfDocument;
    pdfDocument->load(fileName);

    QList<QPixmap> pixmaps;
    for (int i = 0; i < pdfDocument->pageCount(); ++i) {
        QSize imageSize(2400, 3393);
        QImage image = pdfDocument->render(i, imageSize);

        QImage imageWithWhiteBg(imageSize, QImage::Format_ARGB32);
        imageWithWhiteBg.fill(Qt::white);
        QPainter painter(&imageWithWhiteBg);
        painter.drawImage(0, 0, image);
        painter.end();

        QPixmap pixmap = QPixmap::fromImage(imageWithWhiteBg);
        pixmaps.append(pixmap);
    }
    emit fileOpened(QVariant::fromValue(pixmaps), fileInfo.fileName(),fileInfo.suffix().toLower());
}



QWidget* PdfViewer::display(QVariant data)
{
    QList<QPixmap> pixmaps = data.value<QList<QPixmap>>();
    auto scene = new QGraphicsScene;
    auto view = new QGraphicsView(scene);
    DecoratedScene decoratedScene(scene);

    int yOffset = 0;
    CompositeItem compositeItem;
    for (const QPixmap &pixmap : pixmaps) {
        auto item = new QGraphicsPixmapItem(pixmap);
        item->setPos(0, yOffset);

        scene->addItem(item);

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
