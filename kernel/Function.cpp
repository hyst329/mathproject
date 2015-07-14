//
// Created by R2 on 06.07.2015.
//

#include "Function.h"

Type *Function::operator()(std::vector<Type *> args) {
    // TODO: Deal with variables
    for(int i = 0; i  < args.size(); i++){

        ast->variables->insert(make_pair(arguments[i], args[i]));
    }
    return ast->exec();
}

bool Function::equals(Type &type) {
    return 0;
}

bool Function::isNonzero() {
    return 1;
}
