//
// Created by R2 on 06.07.2015.
//

#ifndef MATHPROJECT_FUNCTION_H
#define MATHPROJECT_FUNCTION_H


#include "Type.h"

class Function : Type{
    Type operator();

public:
    char *getType() {
        char *text = "Function";
        return text;
    }
};


#endif //MATHPROJECT_FUNCTION_H
