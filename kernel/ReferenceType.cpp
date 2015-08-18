#include "AST.h"
#include "ReferenceType.h"

ReferenceType::ReferenceType(Type *value) : value(value)
{
}

QString ReferenceType::getType()
{
    return value ? QString("Reference(%1)").arg(value->getType()) : "NullReference";
}

bool ReferenceType::equals(Type &type)
{
    return 0;
}

bool ReferenceType::isNonzero()
{
    return value ? value->isNonzero() : 0;
}

QString ReferenceType::toString()
{
    return value ? value->toString() : "NULL";
}

VariableReferenceType::VariableReferenceType(QString name) : name(name), ReferenceType(0)
{
    value = Kernel::AST::variables.value(name, 0);
}


