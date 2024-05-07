#include "./headers/tst_highlightstrategytest.h"

void HighlightStrategyTest::testHtmlXmlHighlighter_data() {
    QTest::addColumn<QString>("inputText");
    QTest::addColumn<QVector<QTextCharFormat>>("expectedFormats");

    QTextCharFormat tagFormat;
    tagFormat.setForeground(Qt::darkBlue);
    tagFormat.setFontWeight(QFont::Bold);

    QTextCharFormat attrNameFormat;
    attrNameFormat.setForeground(Qt::red);
    attrNameFormat.setFontWeight(QFont::Bold);

    QTextCharFormat attrValueFormat;
    attrValueFormat.setForeground(Qt::green);
    attrValueFormat.setFontWeight(QFont::Bold);

    QTest::newRow("Tag Highlighting") << "<html><body></body></html>"
                                      << QVector<QTextCharFormat>{
                                             tagFormat, tagFormat, tagFormat, tagFormat, tagFormat, tagFormat,
                                             tagFormat, tagFormat, tagFormat, tagFormat, tagFormat, tagFormat,
                                             tagFormat, tagFormat, tagFormat, tagFormat, tagFormat, tagFormat,
                                             tagFormat, tagFormat, tagFormat, tagFormat, tagFormat, tagFormat,
                                             tagFormat, tagFormat, tagFormat, tagFormat, tagFormat, tagFormat
                                         };
    QTest::newRow("Attribute Highlighting") << "<div class='container'></div>"
                                            << QVector<QTextCharFormat>{
                                                   tagFormat, tagFormat, tagFormat, tagFormat, // "<div"
                                                   attrNameFormat, attrNameFormat, attrNameFormat, attrNameFormat, attrNameFormat, // " class"
                                                   tagFormat, // "="
                                                   attrValueFormat, attrValueFormat, attrValueFormat, attrValueFormat, attrValueFormat, attrValueFormat, attrValueFormat, attrValueFormat, attrValueFormat, attrValueFormat, // " 'container'"
                                                   tagFormat, tagFormat, tagFormat, tagFormat, tagFormat // "></div>"
                                               };
}
void HighlightStrategyTest::testSqlHighlighter_data() {
    QTest::addColumn<QString>("inputText");
    QTest::addColumn<QVector<QTextCharFormat>>("expectedFormats");

    QTextCharFormat keywordFormat;
    keywordFormat.setForeground(Qt::darkBlue);
    keywordFormat.setFontWeight(QFont::Bold);

    QTextCharFormat defaultFormat;

    QTest::newRow("Keyword Highlighting") << "SELECT * FROM table WHERE condition;"
                                          << QVector<QTextCharFormat>{
                                                 keywordFormat, keywordFormat, keywordFormat, keywordFormat, keywordFormat, keywordFormat, // "SELECT"
                                                 defaultFormat, // " "
                                                 defaultFormat, defaultFormat, // "* "
                                                 keywordFormat, keywordFormat, keywordFormat, keywordFormat, // "FROM"
                                                 defaultFormat, // " "
                                                 defaultFormat, defaultFormat, defaultFormat, defaultFormat, defaultFormat, // "table"
                                                 defaultFormat, // " "
                                                 keywordFormat, keywordFormat, keywordFormat, keywordFormat, keywordFormat, // "WHERE"
                                                 defaultFormat, // " "
                                                 defaultFormat, defaultFormat, defaultFormat, defaultFormat, defaultFormat, defaultFormat, defaultFormat, defaultFormat, defaultFormat, // "condition"
                                                 defaultFormat // ";"
                                             };
}

void HighlightStrategyTest::testJsonHighlighter_data() {
    QTest::addColumn<QString>("inputText");
    QTest::addColumn<QVector<QTextCharFormat>>("expectedFormats");

    QTextCharFormat keywordFormat;
    keywordFormat.setForeground(Qt::darkGreen);
    keywordFormat.setFontWeight(QFont::Bold);

    QTextCharFormat keyFormat;
    keyFormat.setForeground(Qt::darkBlue);

    QTextCharFormat valueFormat;
    valueFormat.setForeground(Qt::darkYellow);

    QTextCharFormat defaultFormat;

    QTest::newRow("Keyword and Value Highlighting") << "{ \"key\": \"value\" }"
                                                    << QVector<QTextCharFormat>{
                                                           defaultFormat, // "{"
                                                           defaultFormat, defaultFormat, // " \""
                                                           keyFormat, keyFormat, keyFormat, // "key"
                                                           defaultFormat, defaultFormat, // "\":"
                                                           defaultFormat, defaultFormat, // " \""
                                                           valueFormat, valueFormat, valueFormat, valueFormat, valueFormat, // "value"
                                                           defaultFormat, defaultFormat, // "\" "
                                                           defaultFormat // "}"
                                                       };
}

void HighlightStrategyTest::testHtmlXmlHighlighter() {
    QFETCH(QString, inputText);

    QTextDocument doc(inputText);
    HtmlXmlHighlighter highlighter(&doc);

    QVector<QTextCharFormat> expectedFormats(inputText.size());
    QTextCharFormat format;
    format.setForeground(Qt::darkBlue);
    format.setFontWeight(QFont::Bold);
    std::fill(expectedFormats.begin(), expectedFormats.end(), format);

    for (int i = 0; i < inputText.size(); ++i) {
        QTextCursor cursor(&doc);
        cursor.setPosition(i);
        QCOMPARE(cursor.charFormat(), expectedFormats[i]);
    }
}


void HighlightStrategyTest::testSqlHighlighter() {
    QFETCH(QString, inputText);
    QFETCH(QVector<QTextCharFormat>, expectedFormats);

    QTextDocument doc(inputText);
    SqlHighlighter highlighter(&doc);

    for (int i = 0; i < inputText.size(); ++i) {
        QTextCursor cursor(&doc);
        cursor.setPosition(i);
        QCOMPARE(cursor.charFormat(), expectedFormats[i]);
    }
}

void HighlightStrategyTest::testJsonHighlighter() {
    QFETCH(QString, inputText);
    QFETCH(QVector<QTextCharFormat>, expectedFormats);

    QTextDocument doc(inputText);
    JsonHighlighter highlighter(&doc);

    for (int i = 0; i < inputText.size(); ++i) {
        QTextCursor cursor(&doc);
        cursor.setPosition(i);
        QCOMPARE(cursor.charFormat(), expectedFormats[i]);
    }
}

