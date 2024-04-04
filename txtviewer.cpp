#include "txtviewer.h"

QWidget *TxtViewer::view(const QString &fileName)
{
    // Open the file
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return nullptr;

    // Read the text file content
    QTextStream in(&file);
    QString fileContent = in.readAll();

    // Display the text file content
    QTextEdit *textEdit = new QTextEdit;
    textEdit->setPlainText(fileContent);

    return textEdit;
}
