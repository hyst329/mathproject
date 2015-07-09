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

    Type *operator()(std::vector<Type *> args);

    Function(){
       ast->variables = &mapKeeper;
    }

public:
    std::string getType() {
        return "Function";
    }
};


#endif //MATHPROJECT_FUNCTION_H
