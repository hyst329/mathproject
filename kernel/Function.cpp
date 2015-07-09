//
// Created by R2 on 06.07.2015.
//

#include "Function.h"

Type *Function::operator()(std::vector<Type *> args) {
    // TODO: Deal with variables
    return ast->exec();
}
