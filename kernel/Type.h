//
// Created by R2 on 06.07.2015.
//

#ifndef MATHPROJECT_TYPE_H
#define MATHPROJECT_TYPE_H

#include <QString>
#include <QTextStream>

class Type {
public:
    virtual QString getType() = 0;

    virtual bool equals(Type &type) = 0;

    virtual bool isNonzero() = 0;

    virtual QString toString() {
        return QString("[%1 instance at address %2]").arg(getType()).arg((int) this);
    }

    void print(QTextStream &os) {
        os << toString();
    }

};

static inline QTextStream &operator<<(QTextStream &stream, Type &p) {
    p.print(stream);
    endl(stream);
    return stream;
}

#endif //MATHPROJECT_TYPE_H
