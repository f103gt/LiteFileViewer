    #ifndef HIGHLIGHTSTRATEGY_H
    #define HIGHLIGHTSTRATEGY_H
    #include <QRegularExpressionMatchIterator>
    #include <QSyntaxHighlighter>

/*!
\\class HtmlXmlHighlighter
\\brief The HtmlXmlHighlighter class provides syntax highlighting for HTML and XML content.

This class inherits from QSyntaxHighlighter and implements the highlightBlock method to apply syntax highlighting rules to HTML and XML content. It uses regular expressions to match different elements and applies text formatting accordingly.

\\sa QSyntaxHighlighter
*/

    class HtmlXmlHighlighter : public QSyntaxHighlighter {
        Q_OBJECT
    public:
        /*!
    \\brief Constructor for the HtmlXmlHighlighter class.
    \\param parent The parent QTextDocument where the highlighter will be applied.
    */
        HtmlXmlHighlighter(QTextDocument *parent = 0);
    protected:
        /*!
    \\brief Applies syntax highlighting to the given block of text.
    \\param text The text block to highlight.
    */
        void highlightBlock(const QString &text) override;
    private:
        struct HighlightingRule {
            QRegularExpression pattern;
            QTextCharFormat format;
        };
        QVector<HighlightingRule> highlightingRules;
        /*!
    \\brief Adds a new highlighting rule to the highlighter.
    \\param pattern The regular expression pattern to match for highlighting.
    \\param color The color to apply to the matched text.
    \\param weight The font weight to apply to the matched text.
    */
        void addRule(QRegularExpression pattern, QColor color, int weight);

    };

    /*!
\\class SqlHighlighter
\\brief The SqlHighlighter class provides syntax highlighting for SQL queries.

This class inherits from QSyntaxHighlighter and implements the highlightBlock method to apply syntax highlighting rules to SQL queries. It highlights keywords, functions, and other SQL elements using regular expressions.

\\sa QSyntaxHighlighter
*/
    class SqlHighlighter : public QSyntaxHighlighter {
        Q_OBJECT

    public:
        /*!
    \\brief Constructor for the SqlHighlighter class.
    \\param parent The parent QTextDocument where the highlighter will be applied.
    */
        explicit SqlHighlighter(QTextDocument *parent = 0);

    protected:
        /*!
    \\brief Applies syntax highlighting to the given block of text.
    \\param text The text block to highlight.
    */
        void highlightBlock(const QString &text) override;

    private:
        struct HighlightingRule
        {
            QRegularExpression pattern;
            QTextCharFormat format;
        };
        QVector<HighlightingRule> highlightingRules;

        QTextCharFormat keywordFormat;
        /*!
    \\brief Adds a new highlighting rule to the highlighter.
    \\param patterns A list of string patterns to match for highlighting.
    \\param color The color to apply to the matched text.
    */
        void addRule(const QStringList &patterns, const QColor &color);
    };

    /*!
\\class JsonHighlighter
\\brief The JsonHighlighter class provides syntax highlighting for JSON data.

This class inherits from QSyntaxHighlighter and implements the highlightBlock method to apply syntax highlighting rules to JSON data. It highlights keys, values, and structural characters to improve the readability of JSON.

\\sa QSyntaxHighlighter
*/
    class JsonHighlighter : public QSyntaxHighlighter {
        Q_OBJECT
        void addRule(const QStringList &patterns, const QColor &color);
    public:
        /*!
    \\brief Constructor for the JsonHighlighter class.
    \\param parent The parent QTextDocument where the highlighter will be applied.
    */
       explicit JsonHighlighter(QTextDocument *parent = 0);

    protected:
        /*!
    \\brief Applies syntax highlighting to the given block of text.
    \\param text The text block to highlight.
    */
        void highlightBlock(const QString &text) override;

    private:
        struct HighlightingRule
        {
            QRegularExpression pattern;
            QTextCharFormat format;
        };
        QVector<HighlightingRule> highlightingRules;

        QTextCharFormat keywordFormat;
    };


    /*!
\\class HighlightStrategy
\\brief The HighlightStrategy class is an abstract strategy class for creating different syntax highlighters.

This class defines an interface for creating various syntax highlighters for different types of content.
Each subclass should override the createHighlighter method to return a QSyntaxHighlighter object tailored for a specific content type.

\\sa SqlHighlightStrategy, JsonHighlightStrategy, XmlHtmlHighlightStrategy, DefaultHighlightStrategy
*/


    class HighlightStrategy {
    public:
        virtual ~HighlightStrategy() {}
        virtual QSyntaxHighlighter* createHighlighter(QTextDocument* parent) = 0;
    };

    /*!
\\class SqlHighlighter
\\brief The SqlHighlighter class provides syntax highlighting for SQL queries.

This class inherits from QSyntaxHighlighter and implements the highlightBlock method to apply syntax highlighting rules to SQL queries. It highlights keywords, functions, and other SQL elements using regular expressions.

\\sa QSyntaxHighlighter
*/
    class SqlHighlightStrategy : public HighlightStrategy {
    public:
        QSyntaxHighlighter* createHighlighter(QTextDocument* parent) override {
            return new SqlHighlighter(parent);
        }
    };
    /*!
\\class JsonHighlighter
\\brief The JsonHighlighter class provides syntax highlighting for JSON data.

This class inherits from QSyntaxHighlighter and implements the highlightBlock method to apply syntax highlighting rules to JSON data. It highlights keys, values, and structural characters to improve the readability of JSON.

\\sa QSyntaxHighlighter
*/
    class JsonHighlightStrategy : public HighlightStrategy {
    public:
        QSyntaxHighlighter* createHighlighter(QTextDocument* parent) override;
    };

    /*!
\\class HtmlXmlHighlighter
\\brief The HtmlXmlHighlighter class provides syntax highlighting for HTML and XML content.

This class inherits from QSyntaxHighlighter and implements the highlightBlock method to apply syntax highlighting rules to HTML and XML content. It uses regular expressions to match different elements and applies text formatting accordingly.

\\sa QSyntaxHighlighter
*/
    class XmlHtmlHighlightStrategy : public HighlightStrategy {
    public:
        QSyntaxHighlighter* createHighlighter(QTextDocument* parent) override;
    };
    /*!
\\class NoHighlighter
\\brief The NoHighlighter class is a QSyntaxHighlighter that performs no syntax highlighting.

This class inherits from QSyntaxHighlighter but does not implement any syntax highlighting rules. It is used when no syntax highlighting is desired.

\\sa QSyntaxHighlighter
*/
    class NoHighlighter : public QSyntaxHighlighter {
        Q_OBJECT

    public:
        NoHighlighter(QTextDocument *parent = 0) : QSyntaxHighlighter(parent) {}

    protected:
        void highlightBlock(const QString &) override {}
    };
    /*!
\\class DefaultHighlightStrategy
\\brief The DefaultHighlightStrategy class implements the HighlightStrategy interface to create a no-op syntax highlighter.

This class provides a concrete implementation of the HighlightStrategy interface that does not perform any syntax highlighting. It overrides the createHighlighter method to return an instance of NoHighlighter, which is a QSyntaxHighlighter with no highlighting rules.

\\sa HighlightStrategy
*/
    class DefaultHighlightStrategy : public HighlightStrategy {
    public:
        QSyntaxHighlighter* createHighlighter(QTextDocument* parent) override;
    };


    #endif // HIGHLIGHTSTRATEGY_H
