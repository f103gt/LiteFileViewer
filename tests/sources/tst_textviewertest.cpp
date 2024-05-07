#include "./headers/tst_textviewertest.h"
void TxtViewerTest::testSupportsToolbar() {
    TxtViewer viewer;
    QVERIFY(viewer.supportsToolbar());
}

void TxtViewerTest::testSupportsPagination() {
    TxtViewer viewer;
    QVERIFY(!viewer.supportsPagination());
}

void TxtViewerTest::testZoomIn() {
    TxtViewer viewer;
    QWidget widget;
    QTextEdit textEdit(&widget);
    textEdit.setFontPointSize(10);
    viewer.zoomIn(&widget, 1.2);
    QCOMPARE(textEdit.font().pointSizeF(), 12.0);
}

void TxtViewerTest::testZoomOut() {
    TxtViewer viewer;
    QWidget widget;
    QTextEdit textEdit(&widget);
    textEdit.setFontPointSize(12);
    viewer.zoomOut(&widget, 1.2);
    QCOMPARE(textEdit.font().pointSizeF(), 10.0);
}

void TxtViewerTest::testSupportsSearch() {
    TxtViewer viewer;
    QVERIFY(viewer.supportsSearch());
}

void TxtViewerTest::testOpen() {
    TxtViewer viewer;
    QTemporaryFile tempFile;
    if (tempFile.open()) {
        QTextStream out(&tempFile);
        out << "test data";
        tempFile.close();

        viewer.open(tempFile.fileName());

        QWidget* widget = viewer.display(QVariant());
        QVERIFY(widget != nullptr);
        QTextEdit* textEdit = qobject_cast<QTextEdit*>(widget);
        QVERIFY(textEdit != nullptr);
        QCOMPARE(textEdit->toPlainText(), QString("test data"));
    }
}


void TxtViewerTest::testDisplay() {
    TxtViewer viewer;
    QWidget* widget = viewer.display(QVariant::fromValue(QString("test")));
    QVERIFY(widget != nullptr);
    QTextEdit* textEdit = qobject_cast<QTextEdit*>(widget);
    QVERIFY(textEdit != nullptr);
    QCOMPARE(textEdit->toPlainText(), QString("test"));
}
