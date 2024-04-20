#include "../headers/xmlhtmlviewer.h"
#include <QFileInfo>

void HtmlXmlHighlighter::addRule(QRegularExpression pattern, QColor color, int weight) {
    HighlightingRule rule;
    QTextCharFormat format;
    format.setForeground(color);
    format.setFontWeight(weight);
    rule.pattern = pattern;
    rule.format = format;
    highlightingRules.append(rule);
}

HtmlXmlHighlighter::HtmlXmlHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent) {
    addRule(QRegularExpression("<\\/?.*?>"), Qt::darkBlue, QFont::Bold);
    addRule(QRegularExpression("\\b[A-Za-z0-9-_:]+(?=\\=)"), Qt::red, QFont::Bold);
    addRule(QRegularExpression("\"[^\"]*\"|'[^']*'"), Qt::green, QFont::Bold);
    addRule(QRegularExpression("<!--[^>]*-->"), Qt::lightGray, QFont::NoFontMerging);
}

void HtmlXmlHighlighter::highlightBlock(const QString &text) {
    for (const HighlightingRule &rule : std::as_const(highlightingRules)) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
}

void HtmlXmlViewer::open(const QString& fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    QString fileContent = in.readAll();

    QFileInfo fileInfo(fileName);
    emit fileOpened(QVariant::fromValue(fileContent), fileInfo.fileName(), fileInfo.suffix().toLower());
}


QWidget* HtmlXmlViewer::display(QVariant data) {
    qDebug()<<"displaying\n";
    QWidget* widget = viewer_->display(data);
    QTextEdit *textEdit = qobject_cast<QTextEdit *>(widget);
    if (textEdit) {
        new HtmlXmlHighlighter(textEdit->document());
    }
    return widget;
}
