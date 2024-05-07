#ifndef TST_TEXTVIEWERTEST_H
#define TST_TEXTVIEWERTEST_H
#include <QtTest>
#include "../file-reader/headers/txtviewer.h"

class TxtViewerTest : public QObject {
    Q_OBJECT

private slots:
    void testSupportsToolbar();
    void testSupportsPagination();
    void testZoomIn();
    void testZoomOut();
    void testSupportsSearch();
    void testOpen();
    void testDisplay();
};
#endif // TST_TEXTVIEWERTEST_H
