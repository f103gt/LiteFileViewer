#include <QtTest>
#include "./headers/tst_pdfviewertest.h"
#include "./headers/tst_imageviewertest.h"
#include "./headers/tst_highlightstrategytest.h"
#include "./headers/tst_textviewertest.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    int status = 0;

    {
        ImageViewerTest tc;
        status += QTest::qExec(&tc, argc, argv);
    }

    // {
    //     PdfViewerTest tc;
    //     status += QTest::qExec(&tc, argc, argv);
    // }

    {
        HighlightStrategyTest tc;
        status += QTest::qExec(&tc, argc, argv);
    }

    {
        TxtViewerTest tc;
        status += QTest::qExec(&tc, argc, argv);
    }

    return status;
}
