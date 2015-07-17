//
// Created by R2 on 06.07.2015.
//

#include "Function.h"

Type *Function::operator()(std::vector<Type *> args) {
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

bool Function::equals(Type &type) {
    return 0;
}

bool Function::isNonzero() {
    return 1;
}
