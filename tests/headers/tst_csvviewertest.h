#ifndef TST_CSVVIEWERTEST_H
#define TST_CSVVIEWERTEST_H
#include <QtTest>
#include "../file-reader/headers/csvviewer.h"

class TestCsvViewer : public QObject
{
    Q_OBJECT

private slots:
    void testOpen();
    void testDisplay();
    void testSupportsToolbar();
    void testSupportsPagination();
    void testZoomIn();
    void testZoomOut();
};
#endif // TST_CSVVIEWERTEST_H
