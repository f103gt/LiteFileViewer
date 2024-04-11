#include "txtviewer.h"

QWidget *TxtViewer::view(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return nullptr;

    QTextStream in(&file);
    QString fileContent = in.readAll();

    QTextEdit *textEdit = new QTextEdit;
    textEdit->setPlainText(fileContent);

    return textEdit;
}
