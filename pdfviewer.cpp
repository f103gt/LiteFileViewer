#include "pdfviewer.h"
#include <QPdfDocument>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPainter>


QWidget *PdfViewer::view(const QString &fileName)
{
    auto pdfDocument = new QPdfDocument;
    pdfDocument->load(fileName);

    auto scene = new QGraphicsScene;
    auto view = new QGraphicsView(scene);
    DecoratedScene decoratedScene(scene);

    int yOffset = 0;
    CompositeItem compositeItem;
    for (int i = 0; i < pdfDocument->pageCount(); ++i) {
        QSize imageSize(2400, 3393);
        QImage image = pdfDocument->render(i, imageSize);

        QImage imageWithWhiteBg(imageSize, QImage::Format_ARGB32);
        imageWithWhiteBg.fill(Qt::white);
        QPainter painter(&imageWithWhiteBg);
        painter.drawImage(0, 0, image);
        painter.end();

        QPixmap pixmap = QPixmap::fromImage(imageWithWhiteBg);
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
