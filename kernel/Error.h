//
// Created by R2 on 15.07.2015.
//


#ifndef MATHPROJECT_ERROR_H
#define MATHPROJECT_ERROR_H

#include <QString>
#include <QMap>
#include <QTextStream>

enum ErrorType {
    ET_UNKNOWN,
    ET_SYNTAX,
    ET_FILE,
    ET_DIMENSIONS_MISMATCH,
    ET_UNKNOWN_IDENTIFIER,
    ET_UNKNOWN_FUNCTION,
    ET_ASSIGNMENT_ERROR,
    ET_LOCAL_TOPLEVEL,
    ET_INCOMPATIBLE_TYPES,
    ET_DIVISION_BY_ZERO
};

static QMap<ErrorType, QString> codes =
        {
                {ET_UNKNOWN,             "Unknown error"},
                {ET_SYNTAX,              "Syntax error: %1"},
                {ET_FILE,                "Cannot open file: %1"},
                {ET_DIMENSIONS_MISMATCH, "Matrix dimensions mismatch"},
                {ET_UNKNOWN_IDENTIFIER,  "Unknown identifier: %1"},
                {ET_UNKNOWN_FUNCTION,    "Unknown function: %1"},
                {ET_ASSIGNMENT_ERROR,    "Error in assignment"},
                {ET_LOCAL_TOPLEVEL,      "Creating local variable in top-level statement"},
                {ET_INCOMPATIBLE_TYPES,  "Incompatible types: %1 and %2"},
                {ET_DIVISION_BY_ZERO,    "Division by zero"}
        };

class Error {
    QString text;

public:
    Error(ErrorType et, QStringList &args) {
        text = QString("[%1] %2").arg(et, 3, 10, QLatin1Char('0')).arg(codes[et]);
        for (int i = 0; i < args.size(); i++) text = text.arg(args[i]);
    }

    QString getText() {
        return text;
    }

    static void error(ErrorType et, QStringList args = QStringList()) {
        Error err(et, args);
        static QTextStream cerr(stderr);
        cerr << "Error: " << err.getText() << endl;
        throw err;
    }

    static void warning(ErrorType et, QStringList args = QStringList()) {
        Error err(et, args);
        static QTextStream cerr(stderr);
        cerr << "Warning: " << err.getText() << endl;
    }
};

#endif //MATHPROJECT_ERROR_H
