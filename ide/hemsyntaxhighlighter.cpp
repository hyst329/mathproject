#include "hemsyntaxhighlighter.h"

HEMSyntaxHighlighter::HEMSyntaxHighlighter(QTextDocument *parent) : QSyntaxHighlighter(parent)
{

    HighlightingRule rule;
    keywordFormat.setForeground(Qt::red);
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;
    keywordPatterns << "\\bif\\b" << "\\belse\\b" << "\\bwhile\\b"
                    << "\\bfunction\\b" << "\\breturn\\b";
    for (const QString &pattern : keywordPatterns) {
        rule.pattern = QRegExp(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    functionFormat.setFontItalic(true);
    functionFormat.setForeground(Qt::darkBlue);
    rule.pattern = QRegExp("\\b[A-Za-z0-9]+(?=\\()");
    rule.format = functionFormat;
    highlightingRules.append(rule);

    numberFormat.setForeground(Qt::darkRed);
    rule.pattern = QRegExp("\\b([0-9]+\\.)?[0-9]+");
    rule.format = numberFormat;
    highlightingRules.append(rule);

    matrixFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegExp("\\b\\{[0-9\\.\\;\\,]+\\}");
    rule.format = matrixFormat;
    highlightingRules.append(rule);
}

void HEMSyntaxHighlighter::highlightBlock(const QString &text)
{
    for (const HighlightingRule &rule : highlightingRules) {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0) {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }
}

