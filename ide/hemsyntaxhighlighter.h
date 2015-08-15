#ifndef HEMSYNTAXHIGHLIGHTER_H
#define HEMSYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>

class HEMSyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    HEMSyntaxHighlighter(QTextDocument *parent = 0);
    void highlightBlock(const QString &text) override;
private:
    struct HighlightingRule
    {
        QRegExp pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;
    QTextCharFormat keywordFormat, functionFormat,
                    numberFormat, matrixFormat, includeFileFormat;
    enum State {
        STATE_NORMAL = 0,
        STATE_INCLUDE = 1
    };
};

#endif // HEMSYNTAXHIGHLIGHTER_H
