//
// Created by R2 on 06.07.2015.
//

#include "UserFunction.h"

Type *UserFunction::operator()(std::vector<Type *> args) {
    // TODO: Deal with variables
    for(int i = 0; i  < args.size(); i++){

        Kernel::AST::variables.insert(make_pair(arguments[i], args[i]));
    }
    Type* r = ast->exec();
    // Delete all local variables
    for(auto p: Kernel::AST::variables)
        if(p.first[0] != '$')
        Kernel::AST::variables.erase(p.first);
    return r;
}

bool UserFunction::equals(Type &type) {
    return 0;
}

bool UserFunction::isNonzero() {
    return 1;
}

Type *BuiltinFunction::operator()(std::vector<Type *> args) {
    return f(args);
}

bool BuiltinFunction::equals(Type &type) {
    return 0;
}

bool BuiltinFunction::isNonzero() {
    return 1;
}
