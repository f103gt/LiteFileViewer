#include <QtTest>
#include <QSignalSpy>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QScrollBar>
#include <QLayout>
#include "./headers/tst_pdfviewertest.h"

PdfViewerTest::PdfViewerTest() {
    pdfViewer = std::make_unique<PdfViewer>();
}

PdfViewerTest::~PdfViewerTest() {}

void PdfViewerTest::testOpenValidPdf() {
    QString validPdfFile = "D:/Downloads/Git manual.pdf";
    QSignalSpy fileOpenedSpy(pdfViewer.get(), SIGNAL(fileOpened(QVariant, QString, QString)));

    pdfViewer->open(validPdfFile);

    QVERIFY(fileOpenedSpy.count() == 1);
    QList<QVariant> arguments = fileOpenedSpy.takeFirst();
    QCOMPARE(arguments.at(1).toString(), QFileInfo(validPdfFile).fileName());
}



void PdfViewerTest::testDisplay(){
    QString validPdfFile = "D:/Downloads/Git manual.pdf";

    QSignalSpy fileOpenedSpy(pdfViewer.get(), SIGNAL(fileOpened(QVariant, QString, QString)));
    pdfViewer->open(validPdfFile);

    QVERIFY(fileOpenedSpy.count() == 1);

    QVariant data = fileOpenedSpy.takeFirst().at(0);

    QWidget* widget = pdfViewer->display(data);

    QVERIFY(widget != nullptr);
    auto view = widget->property("view").value<QGraphicsView*>();
    QVERIFY(view != nullptr);
}


void PdfViewerTest::testZoomIn_Success()
{
    PdfViewer viewer;
    QWidget currentTab;

    QVBoxLayout* layout = new QVBoxLayout;
    currentTab.setLayout(layout);

    QGraphicsView* view = new QGraphicsView(&currentTab);
    currentTab.layout()->addWidget(view);

    viewer.zoomIn(&currentTab, 1.5);
    QCOMPARE(view->transform().m11(), 1.5);
}



void PdfViewerTest::testZoomIn_ThrowsError()
{
    PdfViewer viewer;
    QWidget currentTab;

    try {
        viewer.zoomIn(&currentTab, 1.5);
        QFAIL("Expected std::runtime_error");
    } catch (const std::runtime_error& err) {
        QCOMPARE(err.what(), "Failed to find QGraphicsView in current tab");
    } catch (...) {
        QFAIL("Expected std::runtime_error");
    }
}


void PdfViewerTest::testZoomOut_Success()
{
    PdfViewer viewer;
    QWidget currentTab;

    QGraphicsView* view = new QGraphicsView;
    currentTab.setProperty("view", QVariant::fromValue(view));

    viewer.zoomOut(&currentTab, 1.5);
    QCOMPARE(view->transform().m11(), 1 / 1.5);

    delete view;
}

void PdfViewerTest::testGoToPage_Success()
{
    PdfViewer viewer;
    QWidget currentTab;

    QGraphicsView* view = new QGraphicsView(&currentTab);
    currentTab.setProperty("view", QVariant::fromValue(view));

    QList<QPixmap> pixmaps;
    pixmaps.append(QPixmap(100, 100));

    currentTab.setProperty("pixmaps", QVariant::fromValue(pixmaps));

    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    view->verticalScrollBar()->setRange(0, 1000);

    viewer.goToPage(&currentTab, 1);

    QCOMPARE(view->verticalScrollBar()->value(), 0);
}


void PdfViewerTest::testGoToPage_ThrowsError_PageOutOfRange()
{
    PdfViewer viewer;
    QWidget currentTab;

    QPointer<QGraphicsView> view = new QGraphicsView(&currentTab);

    currentTab.setProperty("view", QVariant::fromValue(view));

    QList<QPixmap> pixmaps;
    pixmaps.append(QPixmap(100, 100));
    currentTab.setProperty("pixmaps", QVariant::fromValue(pixmaps));

    try {
        viewer.goToPage(&currentTab, 2);
        QFAIL("Expected std::out_of_range");
    } catch (const std::out_of_range& err) {
        QCOMPARE(err.what(), "Page number is out of range");
    } catch (...) {
        QFAIL("Expected std::out_of_range");
    }
    delete view;
}

void PdfViewerTest::testGoToPage_ThrowsError_InvalidPixmap()
{
    PdfViewer viewer;
    QWidget currentTab;

    QPointer<QGraphicsView> view = new QGraphicsView(&currentTab);

    currentTab.setProperty("view", QVariant::fromValue(view));
    QList<QPixmap> pixmaps;
    pixmaps.append(QPixmap());
    currentTab.setProperty("pixmaps", QVariant::fromValue(pixmaps));

    try {
        viewer.goToPage(&currentTab, 1);
        QFAIL("Expected std::runtime_error");
    } catch (const std::runtime_error& err) {
        QCOMPARE(err.what(), "Invalid pixmap at index 0");
    } catch (...) {
        QFAIL("Expected std::runtime_error");
    }
}

void PdfViewerTest::testGoToPage_ThrowsError_InvalidScaleFactor()
{
    PdfViewer viewer;
    QWidget currentTab;

    QGraphicsView* view = new QGraphicsView(&currentTab);
    currentTab.setProperty("view", QVariant::fromValue(view));

    QList<QPixmap> pixmaps;
    pixmaps.append(QPixmap(100, 100));
    currentTab.setProperty("pixmaps", QVariant::fromValue(pixmaps));

    view->setTransform(QTransform());

    try {
        viewer.goToPage(&currentTab, 1);
        QFAIL("Expected std::runtime_error");
    } catch (const std::runtime_error& err) {
        QCOMPARE(err.what(), "Invalid scale factor: 0");
    } catch (...) {
        QFAIL("Expected std::runtime_error");
    }
}


//#include "tst_pdfviewertest.moc"
