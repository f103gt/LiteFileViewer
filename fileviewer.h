#ifndef FILEVIEWER_H
#define FILEVIEWER_H
#include <QWidget>
#include <QObject>

class FileViewer : public QObject {
    Q_OBJECT
public:
    virtual ~FileViewer() {}
public slots:
    virtual void open(const QString& fileName) = 0;
    virtual QWidget* display(QVariant data) = 0;
signals:
    void fileOpened(QVariant data, const QString& title,const QString& fileExtension);
};

#endif // FILEVIEWER_H
