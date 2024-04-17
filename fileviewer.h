#ifndef FILEVIEWER_H
#define FILEVIEWER_H

#include <QWidget>
#include <QObject>
#include <QToolBar>
#include <QLabel>
#include <QScopedPointer>
#include <zoomcommand.h>

class FileViewer : public QObject {
    Q_OBJECT
public:
    virtual ~FileViewer(){};
    virtual bool supportsToolbar() const = 0;
    virtual bool supportsPagination() const = 0;
    virtual void goToPage(QWidget *widget,int page) {}
    virtual void zoomIn(QWidget *currentTab,double factor) = 0;
    virtual void zoomOut(QWidget *currentTab,double factor) = 0;

    //TODO DO I NEED TO USE HERE CONST OR NOT?
    virtual QToolBar* createToolbar(){
        if(!supportsToolbar()){return nullptr;}
        QToolBar *toolbar = new QToolBar();
        toolbar->setMovable(true);

        QAction *zoomInAction = toolbar->addAction("+");
        QLabel *zoomLabel = new QLabel("Zoom: 100%");
        zoomLabel->setObjectName("zoomLabel");
        toolbar->addWidget(zoomLabel);
        QAction *zoomOutAction = toolbar->addAction("-");

        // Connect the actions to the zoomIn and zoomOut methods
        connect(zoomInAction, &QAction::triggered,this, [this]() {
            emit zoomInRequested(1.2);
        });
        connect(zoomOutAction, &QAction::triggered, this,[this]() {
            emit zoomOutRequested(1.2);
        });
        QLabel *pageLabel = new QLabel();
        toolbar->addWidget(pageLabel);

        return toolbar;
    }
protected:
    QScopedPointer<ZoomInCommand> zoomInCommand;
    QScopedPointer<ZoomOutCommand> zoomOutCommand;
    FileViewer()
        : zoomInCommand(new ZoomInCommand())
        , zoomOutCommand(new ZoomOutCommand())
    {}

    void zoom(QWidget *currentTab, ZoomCommand* command,double factor) {
        // Common code
        double zoomLevel = currentTab->property("zoomLevel").toDouble();
        zoomLevel = command->calculateZoomLevel(zoomLevel, factor);
        currentTab->setProperty("zoomLevel", zoomLevel);
        QToolBar *toolbar = currentTab->findChild<QToolBar*>();

        if (toolbar) {
            QLabel *zoomLabel = toolbar->findChild<QLabel*>("zoomLabel");
            if (zoomLabel) {
                zoomLabel->setText(QString("Zoom: %1%").arg(qRound(zoomLevel * 100)));
            }
        }
    }
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
