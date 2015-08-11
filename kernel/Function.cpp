//
// Created by R2 on 06.07.2015.
//

#include "Function.h"

Type *UserFunction::operator()(QList<Type *> args) {
    // TODO: Deal with variables
    for (int i = 0; i < args.size(); i++) {

        Kernel::AST::variables.insert(arguments[i], args[i]);
    }
    Type *r = ast->exec();
    // Delete all local variables
    if (Kernel::AST::variables.empty()) return r;
    for (auto it = Kernel::AST::variables.begin();
         it != Kernel::AST::variables.end();) {
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
