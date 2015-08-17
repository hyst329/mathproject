#ifndef STRING_H
#define STRING_H

#include "Type.h"

class String : public Type
{
public:
    String(QString data = QString()) : data(data) { }

    QString &getData() {
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
    };
    QString toString() {
        return data;
    }

private:
    QString data;
};

#endif // STRING_H
