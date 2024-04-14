#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QMap>
#include <QLabel>
#include "fileviewer.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QString curFile;
    static const int MaxRecentFiles = 10;
    QAction *recentFileActs[MaxRecentFiles];
    void setCurrentFile(const QString &fileName);
    void loadFile(const QString &fileName);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void keyPressEvent(QKeyEvent *event);

    void updateRecentFileActions();


public slots:

    void onOpenButtonClicked();
    void closeCurrentTab();
    void addTab(QVariant data, const QString& title,const QString& fileExtension);
    void openRecentFile();


private:
    Ui::MainWindow *ui;
    QMap<QString, FileViewer*> viewers;
    double zoomLevel = 1.0;
    QGraphicsView*getCurrentTabGraphicsView() const;
    QLabel* getCurrentTabLabel() const;
    void checkTabCount() const;

};
#endif // MAINWINDOW_H
