#include "AST.h"
#include "ReferenceType.h"

bool ReferenceType::equals(Type &type)
{
    return 0;
}

VariableReferenceType::VariableReferenceType(QString name) : name(name)
{
}

QString VariableReferenceType::getType()
{
    return reference() ? QString("Reference(%1)").arg(reference()->getType()) : "NullReference";
}

bool VariableReferenceType::isNonzero()
{
    return reference() ? reference()->isNonzero() : 0;
}

QString VariableReferenceType::toString()
{
    return reference() ? reference()->toString() : "{NullReference}";
}

Type *VariableReferenceType::reference()
{
    return Kernel::AST::variables.value(name, 0);
}

IndexReferenceType::IndexReferenceType(QString name, QList<Type *> indices) : indices(indices), VariableReferenceType(name)
{
}
QList<Type *> IndexReferenceType::getIndices() const
{
    return indices;
}

