#ifndef HTMLXMLVIEWER_H
#define HTMLXMLVIEWER_H

#include "txtviewer.h"
#include "fileviewer.h"
#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QScopedPointer>

class HtmlXmlHighlighter : public QSyntaxHighlighter {
    Q_OBJECT
public:
    HtmlXmlHighlighter(QTextDocument *parent = 0);
protected:
    void highlightBlock(const QString &text) override;
private:
    struct HighlightingRule {
        QRegularExpression pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;
    void addRule(QRegularExpression pattern, QColor color, int weight);

};

class HtmlXmlViewer: public FileViewer {
    Q_OBJECT
    QScopedPointer<TxtViewer> viewer_;

public:
    HtmlXmlViewer(TxtViewer* viewer) :viewer_(viewer) {}
    bool supportsToolbar() const override { return viewer_->supportsToolbar(); }
    bool supportsPagination() const override { return viewer_->supportsPagination(); }
    void zoomIn(QWidget *currentTab,double factor) override { viewer_->zoomIn(currentTab, factor); }
    void zoomOut(QWidget *currentTab,double factor) override { viewer_->zoomOut(currentTab, factor); }

public slots:
    void open(const QString& fileName) override ;
    QWidget* display(QVariant data) override;
};

#endif // HTMLXMLVIEWER_H
