#include "txtviewer.h"
#include <QFileInfo>

void TxtViewer::zoomIn(QWidget *currentTab, double factor)
{
    QTextEdit* textEdit =  currentTab->findChild<QTextEdit*>();
    if(textEdit){
        QFont font = textEdit->font();
        font.setPointSizeF(font.pointSizeF() * factor);
        textEdit->setFont(font);
    }else{
        qDebug() << "Failed to find QTextEdit in current tab";
    }
}

void TxtViewer::zoomOut(QWidget *currentTab, double factor)
{
    QTextEdit* textEdit =  currentTab->findChild<QTextEdit*>();
    if(textEdit){
        QFont font = textEdit->font();
        font.setPointSizeF(font.pointSizeF() / factor);
        textEdit->setFont(font);
    }else{
        qDebug() << "Failed to find QTextEdit in current tab";
    }
}

void TxtViewer::open(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    QString fileContent = in.readAll();

    QFileInfo fileInfo(fileName);
    emit fileOpened(QVariant::fromValue(fileContent), fileInfo.fileName(), fileInfo.suffix().toLower());
}

QWidget* TxtViewer::display(QVariant data)
{
    QString fileContent = data.value<QString>();
    QTextEdit *textEdit = new QTextEdit;
    textEdit->setPlainText(fileContent);
    return textEdit;
}
