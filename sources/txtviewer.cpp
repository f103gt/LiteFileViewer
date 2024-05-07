#include "../headers/txtviewer.h"
#include <QFileInfo>
#include <QLabel>

bool TxtViewer::supportsToolbar() const
{
    return true;
}

bool TxtViewer::supportsPagination() const
{
    return false;
}
bool TxtViewer::supportsSearch(){return true;}

void TxtViewer::zoomIn(QWidget *currentTab, double factor)
{
    QTextEdit* textEdit =  currentTab->findChild<QTextEdit*>();
    if(textEdit){
        QFont font = textEdit->font();
        font.setPointSizeF(font.pointSizeF() * factor);
        textEdit->setFont(font);
        zoom(currentTab,zoomInCommand.get(),factor);
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
        zoom(currentTab,zoomOutCommand.get(),factor);
    }else{
        qDebug() << "Failed to find QTextEdit in current tab";
    }
}

void TxtViewer::open(const QString &fileName)
{
    QFileInfo fileInfo(fileName);
    QString fileExtension = fileInfo.suffix();

    if (fileExtension == "sql") {
        setHighlightStrategy(new SqlHighlightStrategy);
    } else if (fileExtension == "json") {
        setHighlightStrategy(new JsonHighlightStrategy);
    } else if(fileExtension =="html"||
               fileExtension == "xml"){
        setHighlightStrategy(new XmlHtmlHighlightStrategy());
    }else{
        setHighlightStrategy(new DefaultHighlightStrategy);
    }
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    QString fileContent = in.readAll();

    emit fileOpened(QVariant::fromValue(fileContent), fileInfo.fileName(), fileInfo.suffix().toLower());
}

QWidget* TxtViewer::display(QVariant data)
{
    QString fileContent = data.value<QString>();
    QTextEdit *textEdit = new QTextEdit;
    textEdit->setPlainText(fileContent);
    if (highlightStrategy_) {
        highlightStrategy_->createHighlighter(textEdit->document());
    }
    return textEdit;
}
