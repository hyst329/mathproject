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
    virtual Type *reference() { return value; }
protected:
    Type* value;
};

class VariableReferenceType : public ReferenceType {
public:
    VariableReferenceType(QString name);
    virtual QString variable() const
    {
        return name;
    }
private:
    QString name;
};

class IndexReferenceType : public VariableReferenceType {
public:
    IndexReferenceType(QString name, QList<Type *> indices);
private:
    QList<Type *> indices;
};

#endif // REFERENCETYPE_H
