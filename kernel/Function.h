//
// Created by R2 on 06.07.2015.
//

#ifndef MATHPROJECT_FUNCTION_H
#define MATHPROJECT_FUNCTION_H

#include <vector>
#include "Type.h"
#include "AST.h"
#include <map>

class Function : Type{
    Kernel::AST *ast;
    map <string, Type*> mapKeeper;
public:
    Type *operator()(std::vector<Type *> args);

    Function(Kernel::AST *ast) : ast(ast) {
       ast->variables = &mapKeeper;
    }


    virtual bool equals(Type &type);

    virtual bool isNonzero();

    std::string getType() {
        return "Function";
    }
};


#endif //MATHPROJECT_FUNCTION_H
