#include <QtTest>
#include "./headers/tst_imageviewertest.h"

ImageViewerTest::ImageViewerTest()
{
    viewer = std::make_unique<ImageViewer>();
}

void ImageViewerTest::testOpen()
{
    viewer->open(fileName);
}

void ImageViewerTest::testDisplay()
{
    QPixmap pixmap(100, 100);
    QVariant data = QVariant::fromValue(pixmap);
    QWidget* widget = viewer->display(data);
    QVERIFY(widget != nullptr);

    QVariant invalidData = QVariant::fromValue(QString("invalid"));
    try {
        viewer->display(invalidData);
        QFAIL("Expected std::runtime_error for invalid data");
    } catch (std::runtime_error& e) {
        QCOMPARE(e.what(), "Failed to convert data to QPixmap");
    } catch (...) {
        QFAIL("Unexpected exception type");
    }
}

