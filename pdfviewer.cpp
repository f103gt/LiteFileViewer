#include "pdfviewer.h"
#include <QPdfDocument>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QFileInfo>
#include <QPainter>
#include <QDebug>
#include <QLabel>
#include <QVBoxLayout>
#include <QScrollBar>
#include <QLineEdit>

bool PdfViewer::supportsToolbar() const
{
    return true;
}

bool PdfViewer::supportsPagination() const
{
    return true;
}

void PdfViewer::zoomIn(QWidget *currentTab, double factor)
{
    QGraphicsView* view = currentTab->findChild<QGraphicsView*>();
    if (view) {
        view->scale(factor, factor);
        zoom(currentTab,zoomInCommand.get(),factor);
    } else {
        qDebug() << "Failed to find QGraphicsView in current tab";
    }
}


void PdfViewer::zoomOut(QWidget *currentTab, double factor)
{
    QGraphicsView* view = currentTab->findChild<QGraphicsView*>();
    if (view) {
        view->scale(1/factor, 1/factor);
        zoom(currentTab,zoomOutCommand.get(),factor);
    } else {
        qDebug() << "Failed to find QGraphicsView in current tab";
    }
}


void PdfViewer::goToPage(QWidget *widget, int page)
{
    auto view = widget->property("view").value<QGraphicsView*>();
    auto pixmaps = widget->property("pixmaps").value<QList<QPixmap>>();
    int yOffset = 0;
    for (int i = 0; i < page - 1 && i < pixmaps.size(); ++i) {
        yOffset += pixmaps[i].height() + 10;
    }

    // Set the scrollbar's value to this offset
    view->verticalScrollBar()->setValue(yOffset);
    emit pageChanged(page, pixmaps.size());
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
    //return view;

    QWidget *widget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(widget);
    layout->addWidget(view);
    widget->setProperty("view", QVariant::fromValue(view));
    widget->setProperty("pixmaps", data);

    connect(view->verticalScrollBar(), &QScrollBar::valueChanged, this,[this, view, pixmaps](){
        int scrollPos = view->verticalScrollBar()->value();

        int yOffset = 0;
        int currentPage = 0;
        for (int i = 0; i < pixmaps.size(); ++i) {
            if (scrollPos < yOffset + pixmaps[i].height() / 2) {
                currentPage = i + 1;
                break;
            }
            yOffset += pixmaps[i].height() + 10;
        }

        emit pageChanged(currentPage, pixmaps.size());
    });

    return widget;
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
