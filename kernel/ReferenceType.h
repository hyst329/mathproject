#ifndef REFERENCETYPE_H
#define REFERENCETYPE_H

#include "Type.h"

class ReferenceType : public Type
{
public:
    // Type interface
    QString getType() = 0;
    bool equals(Type &type);
    bool isNonzero() = 0;
    QString toString() = 0;
    virtual Type *reference() = 0;
};

class VariableReferenceType : public ReferenceType {
public:
    VariableReferenceType(QString name);
    virtual QString variable() const
    {
        return name;
    }    
    // Type interface
    QString getType();
    bool isNonzero();
    QString toString();
    // ReferenceType interface
    Type *reference();
protected:
    QString name;
};

class IndexReferenceType : public VariableReferenceType {
public:
    IndexReferenceType(QString name, QList<Type *> indices);
    QList<Type *> getIndices() const;

private:
    QList<Type *> indices;
};

#endif // REFERENCETYPE_H
