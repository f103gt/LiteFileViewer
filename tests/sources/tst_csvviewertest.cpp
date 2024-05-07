#include "./headers/tst_csvviewertest.h"
#include <QTableWidget>


void TestCsvViewer::testOpen() {
    CsvViewer& viewer = CsvViewer::getInstance();
    viewer.open("test.csv");
    QVERIFY(QFile::exists("test.csv"));
}

void TestCsvViewer::testDisplay() {
    CsvViewer& viewer = CsvViewer::getInstance();

    QVariantList rows;
    QStringList headers = {"header1", "header2", "header3"};
    rows.append(headers);
    QStringList row1 = {"data1", "data2", "data3"};
    rows.append(row1);

    QWidget* widget = viewer.display(QVariant::fromValue(rows));

    QTableWidget* tableWidget = qobject_cast<QTableWidget*>(widget);
    QVERIFY(tableWidget != nullptr);
    QCOMPARE(tableWidget->rowCount(), 1);
    QCOMPARE(tableWidget->columnCount(), 3);
    QCOMPARE(tableWidget->horizontalHeaderItem(0)->text(), "header1");
    QCOMPARE(tableWidget->horizontalHeaderItem(1)->text(), "header2");
    QCOMPARE(tableWidget->horizontalHeaderItem(2)->text(), "header3");
    QCOMPARE(tableWidget->item(0, 0)->text(), "data1");
    QCOMPARE(tableWidget->item(0, 1)->text(), "data2");
    QCOMPARE(tableWidget->item(0, 2)->text(), "data3");
}

void TestCsvViewer::testSupportsToolbar() {
    CsvViewer& viewer = CsvViewer::getInstance();
    QVERIFY(viewer.supportsToolbar() == true);
}

void TestCsvViewer::testSupportsPagination() {
    CsvViewer& viewer = CsvViewer::getInstance();
    QVERIFY(viewer.supportsPagination() == false);
}

void TestCsvViewer::testZoomIn() {
    CsvViewer& viewer = CsvViewer::getInstance();
    QTableWidget* tableWidget = new QTableWidget;
    QFont initialFont = tableWidget->font();
    viewer.zoomIn(tableWidget, 1.2);
    QFont zoomedFont = tableWidget->font();
    QVERIFY(zoomedFont.pointSizeF() > initialFont.pointSizeF());
}

void TestCsvViewer::testZoomOut() {
    CsvViewer& viewer = CsvViewer::getInstance();
    QTableWidget* tableWidget = new QTableWidget;
    QFont initialFont = tableWidget->font();
    viewer.zoomOut(tableWidget, 1.2);
    QFont zoomedFont = tableWidget->font();
    QVERIFY(zoomedFont.pointSizeF() < initialFont.pointSizeF());
}
