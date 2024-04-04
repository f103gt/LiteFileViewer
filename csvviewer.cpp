#include "csvviewer.h"
#include <QTableWidget>
#include <QFile>

//TODO ADD MORE DESIGN PATTERNS

CsvViewer::CsvViewer() {}

QWidget *CsvViewer::view(const QString &fileName)
{
    // Open the CSV file
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return nullptr;

    QTextStream in(&file);
    QString headerLine = in.readLine(); // Read the first line for headers
    QStringList headers = headerLine.split(',');

    // Create a QTableWidget
    QTableWidget *tableWidget = new QTableWidget;
    tableWidget->setColumnCount(headers.size()); // Set the number of columns
    tableWidget->setHorizontalHeaderLabels(headers); // Set the headers

    // Read the CSV file and populate the table
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(',');

        int row = tableWidget->rowCount();
        tableWidget->insertRow(row);

        for (int i = 0; i < fields.size(); ++i) {
            QTableWidgetItem *item = new QTableWidgetItem(fields[i]);
            tableWidget->setItem(row, i, item);
        }
    }

    tableWidget->resizeColumnsToContents(); // Optional: Resize columns to fit content
    return tableWidget;
}

CsvViewer &CsvViewer::getInstance()
{
    static CsvViewer instance;
    return instance;
}
