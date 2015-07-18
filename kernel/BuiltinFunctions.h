//
// Created by main on 18.07.2015.
//

#ifndef MATHPROJECT_BUILTINFUNCTIONS_H
#define MATHPROJECT_BUILTINFUNCTIONS_H

#include "Type.h"
#include <vector>

namespace Kernel {
    void initialiseBuiltins();
    Type* add(std::vector<Type*> v);
    Type* subtract(std::vector<Type*> v);
    Type* multiply(std::vector<Type*> v);
    Type* divide(std::vector<Type*> v);
    Type* print(std::vector<Type*> v);
    Type* assign(std::vector<Type*> v);
}

#endif //MATHPROJECT_BUILTINFUNCTIONS_H
