//
// Created by R2 on 06.07.2015.
//

#include "Function.h"
#include "ReferenceType.h"
#include <QtDebug>

Type *UserFunction::operator()(QList<Type *> args) {
    // TODO: Deal with variables
    arguments = arguments.replaceInStrings("ref ", "", Qt::CaseInsensitive);
    for (int i = 0; i < args.size(); i++) {
        if(referenceVars.contains(i + 1)) {
            VariableReferenceType *ref = dynamic_cast<VariableReferenceType*>(args[i]);
            // TODO: Error if (!ref)
            if (!ref) {
                qDebug("!ref");
                //Error::error();
            }
            referenceMap.insert(arguments[i], ref->variable());
        }
        Kernel::AST::variables.insert(arguments[i], args[i]);
    }
    qDebug() << referenceMap;
    Type *r = ast->exec();
    // References
    for(QString var : referenceMap.keys()) {
        qDebug() << "assigning " << var << " to " << referenceMap.value(var);
        Kernel::AST::variables[referenceMap.value(var)] = Kernel::AST::variables[var];
    }
    // Delete all local variables
    if (Kernel::AST::variables.empty()) return r;
    for (auto it = Kernel::AST::variables.begin();
         it != Kernel::AST::variables.end();) {
        if (it.key().isEmpty()) { it++; continue; }
        if (it.key()[0] != '$')
            Kernel::AST::variables.erase(it++);
        else it++;
    }
    return r;
}

bool UserFunction::equals(Type &type) {
    return 0;
}

bool UserFunction::isNonzero() {
    return 1;
}

Type *BuiltinFunction::operator()(QList<Type *> args) {
    return f(args);
}

bool BuiltinFunction::equals(Type &type) {
    return 0;
}

bool BuiltinFunction::isNonzero() {
    return 1;
}

QList<int> Function::getReferenceVars() const
{
    return referenceVars;
}
