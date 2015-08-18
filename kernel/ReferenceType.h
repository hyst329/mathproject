#ifndef REFERENCETYPE_H
#define REFERENCETYPE_H

#include "Type.h"

class ReferenceType : public Type
{
public:
    ReferenceType(Type *value);

    // Type interface
    QString getType();
    bool equals(Type &type);
    bool isNonzero();
    QString toString();
    Type *&reference() { return value; }
private:
    Type *value;
};

#endif // REFERENCETYPE_H
