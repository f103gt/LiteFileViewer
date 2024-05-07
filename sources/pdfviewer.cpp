#include "../headers/pdfviewer.h"
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
#include <QScopedPointer>
#include <QLineEdit>

bool PdfViewer::supportsToolbar() const
{
    return true;
}

bool PdfViewer::supportsPagination() const
{
    return true;
}

void PdfViewer::goToPage(QWidget *widget, int page)
{
    auto view = widget->property("view").value<QGraphicsView*>();
    auto pixmaps = widget->property("pixmaps").value<QList<QPixmap>>();
    if (page < 1 || page > pixmaps.size()) {
        throw std::out_of_range("Page number is out of range");
    }

    int totalHeight = 0;
    for (int i = 0; i < page - 1; ++i) {
        if (pixmaps[i].isNull()) {
            throw std::runtime_error("Invalid pixmap at index " + std::to_string(i));
        }
        totalHeight += pixmaps[i].height() + PAGE_SERAPARATOR;
    }

    double scaleFactor = view->transform().m11();
    if (scaleFactor <= 0) {
        throw std::runtime_error("Invalid scale factor: " + std::to_string(scaleFactor));
    }
    int position = static_cast<int>(totalHeight * scaleFactor);

    view->verticalScrollBar()->setValue(position);
    emit pageChanged(page, pixmaps.size());
}


//TOOD REPLACE WITH Q SCOPED POINTER
void PdfViewer::open(const QString &fileName)
{
    QFileInfo fileInfo(fileName);
    if (!fileInfo.exists() || !fileInfo.isFile()) {
        throw std::runtime_error(("File " + fileName.toStdString() + " does not exist or is not a valid file").c_str());}
    QScopedPointer<QPdfDocument> pdfDocument(new QPdfDocument);
    if (pdfDocument->load(fileName) != QPdfDocument::Error::None) {
        throw std::runtime_error(("Failed to load PDF document " + fileName.toStdString()).c_str());
    }

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
    if (!data.canConvert<QList<QPixmap>>()) {
        throw std::runtime_error("Invalid data type provided to PdfViewer::display");
    }

    QList<QPixmap> pixmaps = data.value<QList<QPixmap>>();

    if (pixmaps.isEmpty()) {
        throw std::runtime_error( "Empty list of pixmaps");
    }

    auto scene = new QGraphicsScene;
    if (!scene ) {
        throw std::runtime_error("Failed to create QGraphicsScene");
    }
    auto view = new QGraphicsView(scene);

    if (!view) {
        throw std::runtime_error("Failed to create QGraphicsView");
    }


    int yOffset = 0;

    for (const QPixmap &pixmap : pixmaps) {
        if (pixmap.isNull()) {
            throw std::runtime_error("Invalid QPixmap found in the list");
        }
        auto item = new QGraphicsPixmapItem(pixmap);
        if (!item) {
            throw std::runtime_error("Failed to create QGraphicsPixmapItem");
        }
        item->setPos(0, yOffset);

        scene->addItem(item);

        yOffset += pixmap.height() + PAGE_SERAPARATOR;
    }


    QWidget *widget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(widget);
    layout->addWidget(view);
    widget->setProperty("view", QVariant::fromValue(view));
    widget->setProperty("pixmaps", data);

    connect(view->verticalScrollBar(), &QScrollBar::valueChanged, this, [this, view, pixmaps]() {
        double scaleFactor = view->transform().m11();
        int scrollPos = view->verticalScrollBar()->value();

        int yOffset = 0;
        int currentPage = 0;
        for (int i = 0; i < pixmaps.size(); ++i) {
            int pixmapHeight = static_cast<int>(pixmaps[i].height() * scaleFactor);
            int actualYOffset = static_cast<int>(yOffset * scaleFactor);
            if (scrollPos < actualYOffset + pixmapHeight) {
                currentPage = i + 1;
                break;
            }
            yOffset += pixmaps[i].height() + PAGE_SERAPARATOR;
        }
        emit pageChanged(currentPage, pixmaps.size());
    });


    return widget;
}

