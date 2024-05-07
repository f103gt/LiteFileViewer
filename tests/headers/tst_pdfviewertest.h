#ifndef TST_PDFVIEWERTEST_H
#define TST_PDFVIEWERTEST_H


#include "../file-reader/headers/pdfviewer.h"

class PdfViewerTest : public QObject
{
    Q_OBJECT
    std::unique_ptr<PdfViewer> pdfViewer;
public:
    PdfViewerTest();
    ~PdfViewerTest();

private slots:
    void testOpenValidPdf();
    void testDisplay();
    void testZoomIn_Success();
    void testZoomIn_ThrowsError();
    void testZoomOut_Success();
    void testGoToPage_Success();
    void testGoToPage_ThrowsError_PageOutOfRange();
    void testGoToPage_ThrowsError_InvalidPixmap();
    void testGoToPage_ThrowsError_InvalidScaleFactor();
};

#endif // TST_PDFVIEWERTEST_H
