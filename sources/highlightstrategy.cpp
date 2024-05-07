#include "./headers/highlightstrategy.h"
#include <utility>

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
void SqlHighlighter::addRule(const QStringList &patterns, const QColor &color)
{
    QTextCharFormat format;
    format.setForeground(color);
    format.setFontWeight(QFont::Bold);

    for (const QString &pattern : patterns) {
        HighlightingRule rule;
        rule.pattern = QRegularExpression(pattern);
        rule.format = format;
        highlightingRules.append(rule);
    }
}


SqlHighlighter::SqlHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    addRule(QStringList() << "\\bSELECT\\b", Qt::darkBlue);
    addRule(QStringList() << "\\bFROM\\b" << "\\bWHERE\\b", Qt::darkCyan);
    addRule(QStringList() << "\\bINSERT\\b" << "\\bUPDATE\\b" << "\\bDELETE\\b", Qt::darkGreen);
    addRule(QStringList() << "\\bCREATE\\b" << "\\bSET\\b" << "\\bCOPY\\b", Qt::darkMagenta);
    addRule(QStringList() << "\\bALTER\\b" << "\\bDROP\\b" << "\\bTRUNCATE\\b", Qt::darkRed);
    addRule(QStringList() << "\\bJOIN\\b" << "\\bINNER\\b" << "\\bLEFT\\b" << "\\bRIGHT\\b" << "\\bFULL\\b", Qt::darkYellow);
}

void SqlHighlighter::highlightBlock(const QString &text)
{
    for (const HighlightingRule &rule : std::as_const(highlightingRules)) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
}
void JsonHighlighter::addRule(const QStringList &patterns, const QColor &color)
{
    QTextCharFormat format;
    format.setForeground(color);
    format.setFontWeight(QFont::Bold);

    for (const QString &pattern : patterns) {
        HighlightingRule rule;
        rule.pattern = QRegularExpression(pattern);
        rule.format = format;
        highlightingRules.append(rule);
    }
}


JsonHighlighter::JsonHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    addRule(QStringList() << "\\btrue\\b" << "\\bfalse\\b", Qt::darkGreen);
    addRule(QStringList() << "\\bnull\\b", Qt::darkRed);
    addRule(QStringList() << "\\b\"[^\"]+\"(?=\\s*:)", Qt::darkBlue); // Keys
    addRule(QStringList() << ":\\s*\"[^\"]*\"", Qt::darkYellow); // String values
    addRule(QStringList() << ":\\s*[0-9]+", Qt::darkMagenta); // Number values
    addRule(QStringList() << "\\[", Qt::darkCyan); // Opening brackets
    addRule(QStringList() << "\\]", Qt::darkCyan); // Closing brackets
    addRule(QStringList() << "\\{", Qt::darkCyan); // Opening braces
    addRule(QStringList() << "\\}", Qt::darkCyan); // Closing braces
}

void JsonHighlighter::highlightBlock(const QString &text)
{
    for (const HighlightingRule &rule : std::as_const(highlightingRules)) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
}

QSyntaxHighlighter* XmlHtmlHighlightStrategy::createHighlighter(QTextDocument* parent) {
    return new HtmlXmlHighlighter(parent);
}

QSyntaxHighlighter* DefaultHighlightStrategy::createHighlighter(QTextDocument* parent) {
    return new NoHighlighter(parent);
}

QSyntaxHighlighter* JsonHighlightStrategy::createHighlighter(QTextDocument* parent) {
    return new JsonHighlighter(parent);
}
