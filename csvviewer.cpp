#include "csvviewer.h"
#include <QTableWidget>
#include <QFile>
#include <QFileInfo>

//TODO ADD MORE DESIGN PATTERNS

void CsvViewer::open(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    QStringList headers = in.readLine().split(',');

    QVariantList rows;
    rows.append(headers);

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(',');
        rows.append(fields);
    }

    QFileInfo fileInfo(fileName);
    emit fileOpened(QVariant::fromValue(rows),
                    fileInfo.fileName(),
                    fileInfo.suffix().toLower());
}

QWidget* CsvViewer::display(QVariant data)
{
    QVariantList rows = data.toList();
    QStringList headers = rows.takeFirst().toStringList();

    QTableWidget *tableWidget = new QTableWidget;
    tableWidget->setColumnCount(headers.size());
    tableWidget->setHorizontalHeaderLabels(headers);

    for (const QVariant &rowVariant : rows) {
        QStringList fields = rowVariant.toStringList();
        int row = tableWidget->rowCount();
        tableWidget->insertRow(row);

        for (int i = 0; i < fields.size(); ++i) {
            QTableWidgetItem *item = new QTableWidgetItem(fields[i]);
            tableWidget->setItem(row, i, item);
        }
    }

    tableWidget->resizeColumnsToContents();
    return tableWidget;
}


CsvViewer &CsvViewer::getInstance()
{
    static CsvViewer instance;
    return instance;
}

bool CsvViewer::supportsToolbar() const
{
    return true;
}

bool CsvViewer::supportsPagination() const
{
    return false;
}

void CsvViewer::zoomIn(QWidget *currentTab,double factor)
{
    QTableWidget* tableWidget =  currentTab->findChild<QTableWidget*>();
    if(tableWidget){
        QFont font = tableWidget->font();
        font.setPointSizeF(font.pointSizeF() * factor);
        tableWidget->setFont(font);
        tableWidget->resizeColumnsToContents();
    }else {
        qDebug() << "Failed to find QGraphicsView in current tab";
    }
}

void CsvViewer::zoomOut(QWidget *currentTab,double factor)
{
    QTableWidget* tableWidget =  currentTab->findChild<QTableWidget*>();
    if(tableWidget){
        QFont font = tableWidget->font();
        font.setPointSizeF(font.pointSizeF() / factor);
        tableWidget->setFont(font);
        tableWidget->resizeColumnsToContents();
    }else{
        qDebug() << "Failed to find QTableWidget in current tab";
    }

}

QToolBar *CsvViewer::createToolbar()
{
    return nullptr;
}
