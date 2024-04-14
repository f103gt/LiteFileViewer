#ifndef FILEVIEWER_H
#define FILEVIEWER_H

#include <QWidget>
#include <QObject>
#include <QToolBar>

class FileViewer : public QObject {
    Q_OBJECT
public:
    virtual ~FileViewer() {}
    virtual bool supportsToolbar() const = 0;
    virtual bool supportsPagination() const = 0;
    virtual void zoomIn(QWidget *currentTab,double factor) = 0;
    virtual void zoomOut(QWidget *currentTab,double factor) =0;
    virtual void goToPage(QWidget *widget,int page) {}
    //TODO DO I NEED TO USE HERE CONST OR NOT?
    virtual QToolBar* createToolbar() = 0;
public slots:
    virtual void open(const QString& fileName) = 0;
    virtual QWidget* display(QVariant data) = 0;
signals:
    void fileOpened(QVariant data, const QString& title,const QString& fileExtension);
    void zoomInRequested(double factor);
    void zoomOutRequested(double factor);
    void pageChanged(int currentPage, int totalPages);
};

#endif // FILEVIEWER_H
