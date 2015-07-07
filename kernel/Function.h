//
// Created by R2 on 06.07.2015.
//

#ifndef MATHPROJECT_FUNCTION_H
#define MATHPROJECT_FUNCTION_H


#include <vector>
#include "Type.h"

class Function : Type{
    Type *operator()(std::vector<Type *> args);

public:
    std::string getType() {
        return "Function";
    }
};


#endif //MATHPROJECT_FUNCTION_H
