#ifndef STRING_H
#define STRING_H

#include "Type.h"
#include <QString>

class StringType : public Type
{
public:
    StringType(QString data = QString()) : data(data) { }

    QString &toQString() {
        return data;
    }

    // Type interface
    QString getType() {
        return "String";
    }
    bool equals(Type &type) {
        return 0;
    }
    bool isNonzero() {
        return data.isEmpty();
    }
    QString toString() {
        return data;
    }

private:
    QString data;
};

#endif // STRING_H
