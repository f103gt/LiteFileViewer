#include <QtTest>
#include <QAbstractTextDocumentLayout>
#include "../file-reader/headers/highlightstrategy.h"

class HighlightStrategyTest : public QObject {
    Q_OBJECT

private slots:
    // HtmlXmlHighlighter Tests
    void testHtmlXmlHighlighter_data();
    void testHtmlXmlHighlighter();

    // SqlHighlighter Tests
    void testSqlHighlighter_data();
    void testSqlHighlighter();

    // JsonHighlighter Tests
    void testJsonHighlighter_data();
    void testJsonHighlighter();
};
